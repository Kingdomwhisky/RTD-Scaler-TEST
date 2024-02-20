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
// ID Code      : SysTypeC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_TYPC_C__

#include "SysInclude.h"
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Time of Type-C Cable Recheck After Reconnected When DP_TYPE_C_CONNECTION_CHECK_WAY != _DISCRETE_PORT_CTRL_USE_GPIO
//--------------------------------------------------
#define _TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME         500 // Restart time 0.5s for after type-c reconnected
#define _TYPE_C_ENABLE_BILLBOARD_TIME                   1000 // Timeout Enable Billboard After CC Attach

#define GET_TYPE_C_STATE(x)                             (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumTypeCState)
#define SET_TYPE_C_STATE(x, y)                          (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumTypeCState = (y))

#define GET_TYPE_C_ORIENTATION(x)                       (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumOrientation)
#define SET_TYPE_C_ORIENTATION(x, y)                    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumOrientation = (y))

#define GET_TYPE_C_PIN_ASSIGNMENT(x)                    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumSPinAssignment)
#define SET_TYPE_C_PIN_ASSIGNMENT(x, y)                 (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumSPinAssignment = (y))

#define GET_TYPE_C_CAPABILITY_CHG(x)                    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag)
#define SET_TYPE_C_CAPABILITY_CHG(x, y)                 (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag = (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag | (y)))
#define CLR_TYPE_C_CAPABILITY_CHG(x, y)                 (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag = (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].ucCapChangeFlag & (~(y))))

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_TYPE_C_LENOVO_ALT_MODE_STATUS(x)            (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumLenovoAltModeStatus)
#define SET_TYPE_C_LENOVO_ALT_MODE_STATUS(x, y)         (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumLenovoAltModeStatus = (y))

#define GET_TYPE_C_LENOVO_DEVICE_TYPE(x)                (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumLenovoDeviceType)
#define SET_TYPE_C_LENOVO_DEVICE_TYPE(x, y)             (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].enumLenovoDeviceType = (y))

#define GET_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(x)    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].b1LenovoRcvDeviceTypeTimeout)
#define SET_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(x)    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].b1LenovoRcvDeviceTypeTimeout = _TRUE)
#define CLR_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(x)    (g_pstTypeCStatus[SysTypeCGetTypeCIndex(x)].b1LenovoRcvDeviceTypeTimeout = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _TYPE_C_UNATTACH_STATE = 0x00,
    _TYPE_C_ATTACHED_STATE = 0x01,
    _TYPE_C_DP_ALT_MODE_READY_STATE = 0x02,
    _TYPE_C_RECONNECT_STATE = 0x03,
}EnumTypeCState;

// USB Type-C Related Status
typedef struct
{
    EnumTypeCState enumTypeCState;
    // -----------------------------
    EnumTypeCPinCfgType enumSPinAssignment;
    // -----------------------------
    BYTE ucCapChangeFlag;
    // -----------------------------
    EnumTypeCOrientation enumOrientation;
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    EnumTypeCLenovoAltModeStatus enumLenovoAltModeStatus;
    EnumTypeCLenovoDeviceType enumLenovoDeviceType;
    BYTE b1LenovoRcvDeviceTypeTimeout : 1;
#endif
}StructTypeCStatus;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTypeCStatus g_pstTypeCStatus[_TYPE_C_PORT_VALID];

#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
StructUsbHubInfo g_stD0UsbHubInfo;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
StructUsbHubInfo g_stD1UsbHubInfo;
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
StructUsbHubInfo g_stD6UsbHubInfo;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysTypeCInitial(void);
void SysTypeCHandler(void);
void SysTypeCUFPHandler(BYTE ucInputPort);
void SysTypeCPowerSwitch(EnumPowerAction enumSwitch);
EnumPdoCheck SysTypeCSetPortCtrlSourceCap(BYTE ucInputPort);
void SysTypeCSetPortCtrlSinkCap(BYTE ucInputPort);
void SysTypeCSetPortCtrlRequest(BYTE ucInputPort);
EnumTypeCAttachStatus SysTypeCGetPortControllerCcAttach(BYTE ucInputPort);
EnumTypeCAltModeStatus SysTypeCGetPortControllerAltModeReady(BYTE ucInputPort);
EnumTypeCOrientation SysTypeCGetPortControllerOrientation(BYTE ucInputPort);
bit SysTypeCGetPortControllerPinAssignment(BYTE ucInputPort);
EnumTypeCPowerRole SysTypeCGetPortControllerPowerRole(BYTE ucInputPort);
void SysTypeCSetDpLaneMapping(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation);
bit SysTypeCheckCapabilityChange(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability);
void SysTypeCPinAssignmentCapabilityChangeProc(BYTE ucInputPort);
void SysTypeCSrcCapabilityChangeProc(BYTE ucInputPort);
bit SysTypeCReconnectSupport(BYTE ucInputPort);
bit SysTypeCReconnect(BYTE ucInputPort);
void SysTypeCReconnectTransition(BYTE ucInputPort);
bit SysTypeCUpdatePortControllerConfig(BYTE ucInputPort);
BYTE SysTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
StructTypeCUserPDO SysTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
bit SysTypeCGetPdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent);
bit SysTypeCGetCcAttach(BYTE ucInputPort);
bit SysTypeCGetAltModeReady(BYTE ucInputPort);
EnumTypeCPinCfgType SysTypeCGetPinAssignment(BYTE ucInputPort);
BYTE SysTypeCGetTypeCIndex(BYTE ucInputPort);
#if(_DP_PORT_EXIST == _ON)
bit SysTypeCCheckTypeCPortControllerExist(BYTE ucInputPort);
#endif
EnumDpLaneCount SysTypeCGetAltModeLaneCnt(EnumTypeCPinCfgType enumPinAssignment);
void SysTypeCSwitchOSDLaneCount(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount);
void SysTypeCSetCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability);
void SysTypeCClrCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability);

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
void SysTypeCAltModeHandler(BYTE ucInputPort);
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
void SysTypeCLenovoAltModeReset(BYTE ucInputPort);
EnumTypeCLenovoAltModeStatus SysTypeCGetPortControllerLenovoAltModeReady(BYTE ucInputPort);
EnumTypeCLenovoDeviceType SysTypeCGetPortControllerLenovoDeviceType(BYTE ucInputPort);
void SysTypeCActiveLenovoRcvDeviceTypeTimerEvent(BYTE ucInputPort, WORD usTimeoutCnt);
void SysTypeCCancelLenovoRcvDeviceTypeTimerEvent(BYTE ucInputPort);
void SysTypeCSetLenovoRcvDeviceTypeTimeout(BYTE ucInputPort);
StructTypeCLenovoSysEvent SysTypeCGetPortControllerLenovoSystemEvent(BYTE ucInputPort);
void SysTypeCSetPortControllerLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
bit SysTypeCCheckPortControllerLenovoDockingEventBusy(BYTE ucInputPort);
EnumTypeCLenovoAltModeStatus SysTypeCGetLenovoAltModeReady(BYTE ucInputPort);
EnumTypeCLenovoDeviceType SysTypeCGetLenovoDeviceType(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
EnumTypeCAcerAltModeStatus SysTypeCGetPortControllerAcerAltModeReady(BYTE ucInputPort);
StructTypeCAcerSysEvent SysTypeCGetPortControllerAcerSystemEvent(BYTE ucInputPort);
void SysTypeCSetPortControllerAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent stAcerUserEvent);
EnumTypeCAcerBusyStatus SysTypeCCheckPortControllerAcerUserEventBusy(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
EnumTypeCHpAltModeStatus SysTypeCGetPortControllerHpAltModeReady(BYTE ucInputPort);
StructTypeCHpSysEvent SysTypeCGetPortControllerHpSystemEvent(BYTE ucInputPort);
void SysTypeCSetPortControllerHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent stHpUserEvent);
EnumTypeCHpBusyStatus SysTypeCCheckPortControllerHpUserEventBusy(BYTE ucInputPort);
EnumTypeCHpAltModeStatus SysTypeCGetHpAltModeReady(BYTE ucInputPort);
#endif
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

#if(((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)))
void SysTypeCSwitchToUnattachState(BYTE ucInputPort);
#endif
void SysTypeCCancelUnattachTimerEvent(BYTE ucInputPort);

#if(_BILLBOARD_SUPPORT == _ON)
void SysTypeCStartBillboardTimer(BYTE ucInputPort, WORD usTimeoutCnt);
void SysTypeCCancelBillboardTimer(BYTE ucInputPort);
void SysTypeCBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif

#if(_DP_USB_HUB_SUPPORT == _ON)
void SysTypeCUsbHubProc(BYTE ucInputPort);
#endif
#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCUsbHubDetectProc(BYTE ucInputPort);
void SysTypeCUsbHubConfigProc(BYTE ucInputPort, BYTE ucDpLanes);
WORD SysTypeCGetUsbHubSetU3ReadyDelayTime(BYTE ucInputPort);

#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCD0UsbHubDetectProc(void);
#endif
#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCD1UsbHubDetectProc(void);
#endif
#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
void SysTypeCD6UsbHubDetectProc(void);
#endif

void SysTypeCOsdHubProc(void);
#endif

#if(_DP_USB_HUB_SUPPORT == _ON)
void SysTypeCHubInputSwitchProc(BYTE ucInputPort);
#endif

#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TypeC AC On Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCInitial(void)
{
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    SET_TYPE_C_STATE(_D0_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
    SET_TYPE_C_ORIENTATION(_D0_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
    SET_TYPE_C_PIN_ASSIGNMENT(_D0_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);
    SysTypeCClrCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_ALL_STATUS_CHG);
    SysTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_HUB_INPUT_SWITCH_CHG);
    SysTypeCSetPortCtrlSourceCap(_D0_INPUT_PORT);
    SysTypeCSetPortCtrlSinkCap(_D0_INPUT_PORT);
    SysTypeCSetPortCtrlRequest(_D0_INPUT_PORT);

    DebugMessageSystem("8. [TYPE C] <Step 0/2> D0 CC Unattach", _TYPE_C_ATTACHED_STATE);

#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
    UserCommonPortControllerSetD0I2CDetection();
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    SysTypeCLenovoAltModeReset(_D0_INPUT_PORT);
#endif
#endif  // End Of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    SET_TYPE_C_STATE(_D1_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
    SET_TYPE_C_ORIENTATION(_D1_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
    SET_TYPE_C_PIN_ASSIGNMENT(_D1_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);
    SysTypeCClrCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_ALL_STATUS_CHG);
    SysTypeCSetCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_HUB_INPUT_SWITCH_CHG);
    SysTypeCSetPortCtrlSourceCap(_D1_INPUT_PORT);
    SysTypeCSetPortCtrlSinkCap(_D1_INPUT_PORT);
    SysTypeCSetPortCtrlRequest(_D1_INPUT_PORT);

    DebugMessageSystem("8. [TYPE C] <Step 0/2> D1 CC Unattach", _TYPE_C_ATTACHED_STATE);

#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
    UserCommonPortControllerSetD1I2CDetection();
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    SysTypeCLenovoAltModeReset(_D1_INPUT_PORT);
#endif
#endif // End Of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    SET_TYPE_C_STATE(_D6_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
    SET_TYPE_C_ORIENTATION(_D6_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
    SET_TYPE_C_PIN_ASSIGNMENT(_D6_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);
    SysTypeCClrCapabilityChangeFlag(_D6_INPUT_PORT, _TYPE_C_ALL_STATUS_CHG);
    SysTypeCSetCapabilityChangeFlag(_D6_INPUT_PORT, _TYPE_C_HUB_INPUT_SWITCH_CHG);
    SysTypeCSetPortCtrlSourceCap(_D6_INPUT_PORT);
    SysTypeCSetPortCtrlSinkCap(_D6_INPUT_PORT);
    SysTypeCSetPortCtrlRequest(_D6_INPUT_PORT);

    DebugMessageSystem("8. [TYPE C] <Step 0/2> D6 CC Unattach", _TYPE_C_ATTACHED_STATE);

#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
    UserCommonPortControllerSetD6I2CDetection();
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    SysTypeCLenovoAltModeReset(_D6_INPUT_PORT);
#endif
#endif // End Of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : PD/CC Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCHandler(void)
{
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    // 1. Run PD/CC Proc (For Embedded Port Controller Only)
    ScalerTypeCHandler(_D0_INPUT_PORT, GET_MODE_STATE());

#if(_USB3_RETIMER_SUPPORT == _ON)
    ScalerUSB3RetimerHandler(GET_POWER_STATUS());
#endif
#endif

    // 2. Run DFP Proc According to Port Controller Status (For All Type-C Ports)
    SysTypeCUFPHandler(_D0_INPUT_PORT);

#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
    // 3. Run Hub Proc to Detect if Any Device Connect to Hub
    SysTypeCUsbHubProc(_D0_INPUT_PORT);
#endif
#endif  // End Of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCHandler(_D1_INPUT_PORT, GET_MODE_STATE());
#endif

    SysTypeCUFPHandler(_D1_INPUT_PORT);

#if(_D1_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
    SysTypeCUsbHubProc(_D1_INPUT_PORT);
#endif
#endif  // End Of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)


#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    ScalerTypeCHandler(_D6_INPUT_PORT, GET_MODE_STATE());
#endif

    SysTypeCUFPHandler(_D6_INPUT_PORT);

#if(_D6_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
    SysTypeCUsbHubProc(_D6_INPUT_PORT);
#endif
#endif  // End Of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Type-C Handler Used to Sync Port Controller and Scaler
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCUFPHandler(BYTE ucInputPort)
{
    switch(GET_TYPE_C_STATE(ucInputPort))
    {
        case _TYPE_C_UNATTACH_STATE:

            // Check if CC Attached
            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                DebugMessageSystem("8. [TYPE C] <Step 1/2> CC Attach, Alt Mode Not Ready", _TYPE_C_UNATTACH_STATE);

                SET_TYPE_C_ORIENTATION(ucInputPort, SysTypeCGetPortControllerOrientation(ucInputPort));
                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_ATTACHED_STATE);

#if(_BILLBOARD_SUPPORT == _ON)
                // Enable Billboard Function if Alt Mode Not Successfully Entered
                SysTypeCStartBillboardTimer(ucInputPort, _TYPE_C_ENABLE_BILLBOARD_TIME);
#endif
            }
            else
            {
#if(_BILLBOARD_SUPPORT == _ON)
                // Cancel Timer Event(TURN ON BB)
                SysTypeCCancelBillboardTimer(ucInputPort);

                // Disable Billboard When CC Unattach
                SysTypeCBillboardControl(ucInputPort, _TYPE_C_BB_DISABLE);
#endif
            }

            break;

        case _TYPE_C_ATTACHED_STATE:

            // Check if CC Attached
            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                // Check if PD Has Entered DP Alt. Mode (Wait For PD Power Contract / Swap / Alt Mode Flow)
                if(SysTypeCGetPortControllerAltModeReady(ucInputPort) == _TYPE_C_ALT_MODE_READY)
                {
#if(_BILLBOARD_SUPPORT == _ON)
                    // Cancel Timer Event(TURN ON BB)
                    SysTypeCCancelBillboardTimer(ucInputPort);
#endif

                    // 1. Get Alt. Mode Pin Assignment and Proc Related Setting (Lane Mapping or Swap)
                    if(SysTypeCGetPortControllerPinAssignment(ucInputPort) == _SUCCESS)
                    {
                        // 2. Get Port Ctrl Orientatioin
                        SET_TYPE_C_ORIENTATION(ucInputPort, SysTypeCGetPortControllerOrientation(ucInputPort));

                        // 3. Set DP lANE Mapping According to Pin Assignment and Orientation
                        SysTypeCSetDpLaneMapping(ucInputPort, GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort), GET_TYPE_C_ORIENTATION(ucInputPort));

                        // 4. Update OSD Lane Count According to Alt. Mode Pin Assignment
                        SysTypeCSwitchOSDLaneCount(ucInputPort, SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));
                        // SysTypeCSwitchSysDataLaneCount();

                        // 5. Switch DP Lane Count According to Alt. Mode Pin Assignment
                        ScalerDpLaneCountSwitch(ucInputPort, SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));
                        DebugMessageSystem("8. [TYPE C] ==========> Set DP Lane Count", SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));

                        // 6. Switch DP EDID According to Alt. Mode Pin Assignment
                        UserCommonInterfaceTypeCPinAssignSuccessProc(ucInputPort, GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort));

                        DebugMessageSystem("8. [TYPE C] <Step 2/2> Alt Mode Ready", _TYPE_C_ATTACHED_STATE);

                        SET_TYPE_C_STATE(ucInputPort, _TYPE_C_DP_ALT_MODE_READY_STATE);
                    }
                }
                else
                {
                    if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_SRC_CAP_CHG) == _TRUE)
                    {
                        // Check Whether Source Capability Has Been Changed or Not
                        SysTypeCSrcCapabilityChangeProc(ucInputPort);
                    }
                }
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_ATTACHED_STATE);

                SysTypeCSetPortCtrlRequest(ucInputPort);
                SET_TYPE_C_ORIENTATION(ucInputPort, _TYPE_C_ORIENTATION_NONE);
                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_UNATTACH_STATE);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
                SysTypeCLenovoAltModeReset(ucInputPort);
#endif
            }

            break;

        case _TYPE_C_DP_ALT_MODE_READY_STATE:

            // Check if CC Attached
            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                // Check Whether Pin Assignment Capability Has Been Changeed or Not
                if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG) == _TRUE)
                {
                    DebugMessageSystem("8. [TYPE C] ==========> Cap Change : Checking U3 Mode and Pin Assignment E Support Status. . .", _TYPE_C_DP_ALT_MODE_READY_STATE);
                    SysTypeCPinAssignmentCapabilityChangeProc(ucInputPort);
                }
                else
                {
                    // 1. Check if Still in DP Alt Mode
                    if(SysTypeCGetPortControllerAltModeReady(ucInputPort) != _TYPE_C_ALT_MODE_READY)
                    {
                        DebugMessageSystem("8. [TYPE C] <Step 1/2> CC Attach, Alt Mode Not Ready", _TYPE_C_DP_ALT_MODE_READY_STATE);

                        // Config Lane Mapping to USB + DP Mode, and Back to Attached State to Wait for Alt. Mode Ready
                        SET_TYPE_C_STATE(ucInputPort, _TYPE_C_ATTACHED_STATE);
                    }

                    // 2. Check Whether Source Capability Has Been Changed or Not
                    if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_SRC_CAP_CHG) == _TRUE)
                    {
                        SysTypeCSrcCapabilityChangeProc(ucInputPort);
                    }
                }
            }
            else
            {
                DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_DP_ALT_MODE_READY_STATE);

                SysTypeCSetPortCtrlRequest(ucInputPort);
                SET_TYPE_C_ORIENTATION(ucInputPort, _TYPE_C_ORIENTATION_NONE);
                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_UNATTACH_STATE);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
                SysTypeCLenovoAltModeReset(ucInputPort);
#endif
            }

            break;

        case _TYPE_C_RECONNECT_STATE:

            if(SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH)
            {
                if(SysTypeCGetPortControllerAltModeReady(ucInputPort) == _TYPE_C_ALT_MODE_READY)
                {
                    if(SysTypeCReconnect(ucInputPort) == _SUCCESS)
                    {
                        // State Transition After Reconnect
                        SysTypeCReconnectTransition(ucInputPort);
                    }
                }
                else
                {
                    SET_TYPE_C_STATE(ucInputPort, _TYPE_C_ATTACHED_STATE);
                    DebugMessageSystem("8. [TYPE C] <Step 1/2> CC Attach, Alt Mode Not Ready", _TYPE_C_RECONNECT_STATE);
                }
            }
            else
            {
                // If Port Controller Switch to Unattach in 500ms, Cancel Unatach Timer Event
                SysTypeCCancelUnattachTimerEvent(ucInputPort);

                SysTypeCSetPortCtrlRequest(ucInputPort);
                SET_TYPE_C_ORIENTATION(ucInputPort, _TYPE_C_ORIENTATION_NONE);
                SET_TYPE_C_STATE(ucInputPort, _TYPE_C_UNATTACH_STATE);
                DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
                SysTypeCLenovoAltModeReset(ucInputPort);
#endif
            }

            break;

        default:

            // Error Handling ?????

            break;
    }

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
    if((GET_TYPE_C_STATE(ucInputPort) == _TYPE_C_ATTACHED_STATE) || (GET_TYPE_C_STATE(ucInputPort) == _TYPE_C_DP_ALT_MODE_READY_STATE))
    {
        SysTypeCAltModeHandler(ucInputPort);
    }
#endif
}

//--------------------------------------------------
// Description  : Set Capability Change Power Switch Proc
// Input Value  : enumSwitch
// Output Value : None
//--------------------------------------------------
void SysTypeCPowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_FAKE_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Embedded Type-C : Update Port Ctrl. Pin Assignment
            if(SysTypeCUpdatePortControllerConfig(_D0_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========x Power Switch, Update Embedded Type-C Config Fail ! ! !", enumSwitch);
            }
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            if(UserCommonPortControllerGetPowerOnReconnectStatus(enumSwitch) == _TYPE_C_PORT_CTRL_RECONNECT)
            {
                // 5400/User Port Ctrl : Set Capability Change Flag to Check Pin Assignment
                SysTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
            }

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // 5400 Port Ctrl  : Clr I2C Communication Enabled Flag
            UserCommonPortControllerClr5400I2CEnabledFlag(_D0_INPUT_PORT);
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Embedded Type-C : Update Port Ctrl. Pin Assignment
            if(SysTypeCUpdatePortControllerConfig(_D1_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========x Power Switch, Update Embedded Type-C Config Fail ! ! !", enumSwitch);
            }
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            if(UserCommonPortControllerGetPowerOnReconnectStatus(enumSwitch) == _TYPE_C_PORT_CTRL_RECONNECT)
            {
                // 5400/User Port Ctrl : Set Capability Change Flag to Check Pin Assignment
                SysTypeCSetCapabilityChangeFlag(_D1_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
            }

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // 5400 Port Ctrl  : Clr I2C Communication Enabled Flag
            UserCommonPortControllerClr5400I2CEnabledFlag(_D1_INPUT_PORT);
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Embedded Type-C : Update Port Ctrl. Pin Assignment
            if(SysTypeCUpdatePortControllerConfig(_D6_INPUT_PORT) != _SUCCESS)
            {
                DebugMessageSystem("8. [TYPE C] ==========x Power Switch, Update Embedded Type-C Config Fail ! ! !", enumSwitch);
            }
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            if(UserCommonPortControllerGetPowerOnReconnectStatus(enumSwitch) == _TYPE_C_PORT_CTRL_RECONNECT)
            {
                // 5400/User Port Ctrl : Set Capability Change Flag to Check Pin Assignment
                SysTypeCSetCapabilityChangeFlag(_D6_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
            }

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // 5400 Port Ctrl  : Clr I2C Communication Enabled Flag
            UserCommonPortControllerClr5400I2CEnabledFlag(_D6_INPUT_PORT);
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            ScalerTypeCPowerSwitch(enumSwitch);
#endif
#if(_USB3_RETIMER_SUPPORT == _ON)
            if(ScalerUSB3RetimerGetHubUfpStatus() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                ScalerUSB3RetimerPowerSwitch(enumSwitch);
            }
#endif

            DebugMessageSystem("8. [TYPE C] ==========> Power Switch, Set Cap Change ! ! !", enumSwitch);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            ScalerTypeCPowerSwitch(enumSwitch);
#endif
#if(_USB3_RETIMER_SUPPORT == _ON)
            if(ScalerUSB3RetimerGetHubUfpStatus() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                ScalerUSB3RetimerPowerSwitch(enumSwitch);
            }
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            ScalerTypeCPowerSwitch(enumSwitch);
#endif
#if(_USB3_RETIMER_SUPPORT == _ON)
            if(ScalerUSB3RetimerGetHubUfpStatus() == _HUB_UFP_TYPE_C_INPUT_PORT)
            {
                ScalerUSB3RetimerPowerSwitch(enumSwitch);
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Initial State Set Up Port Ctrl SRC Capability
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
EnumPdoCheck SysTypeCSetPortCtrlSourceCap(BYTE ucInputPort)
{
    BYTE ucPdoCount = 0;
    BYTE ucPdoIndex = 0;
    StructTypeCUserPDO stTypeCUserPdo;
    EnumPdoCheck enumSrcCapPdoChange = _TYPE_C_PDO_NO_CHANGE;
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
    StructTypeCUserProtectInfo stTypeCUserProtectInfo;
#endif

    ucPdoCount = ucPdoCount;
    ucPdoIndex = ucPdoIndex;
    stTypeCUserPdo = stTypeCUserPdo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

            // 1. Get PDO Info From User / Kernel
            if(UserCommonInterfaceTypeCPdoReference(_D0_INPUT_PORT, _TYPE_C_POWER_SRC) == _TYPE_C_PDO_FROM_USER)
            {
                // 2. Get Max Power [Unit = 0.1 W]
                ScalerTypeCSetMaxPower(_D0_INPUT_PORT, UserCommonInterfaceTypeCGetMaxPower(_D0_INPUT_PORT));

                // 3. Get Total Number of PDO (Enumeration Range 1 ~ 7)
                ucPdoCount = UserCommonInterfaceTypeCGetPdoCount(_D0_INPUT_PORT, _TYPE_C_POWER_SRC);
                if(ScalerTypeCCheckPdoCountChange(_D0_INPUT_PORT, ucPdoCount) == _TYPE_C_PDO_CHANGE)
                {
                    ScalerTypeCSetPdoCnt(_D0_INPUT_PORT, _TYPE_C_POWER_SRC, ucPdoCount);
                    enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;
                }

                // 4. Get PDO Info and Write to Port Controller
                for(ucPdoIndex = 1; ucPdoIndex <= ucPdoCount; ucPdoIndex++)
                {
                    // Set PDO to Default Value
                    stTypeCUserPdo.enumPdoType = _PD_FIX_SUPPLY_PDO;
                    stTypeCUserPdo.ucMaxCurrent = 0;
                    stTypeCUserPdo.ucMaxVoltage = 0;
                    stTypeCUserPdo.ucMinVoltage = 0;

                    // Get User 1st - 7th Src PDO Info
                    UserCommonInterfaceTypeCGetPdoInfo(_D0_INPUT_PORT, _TYPE_C_POWER_SRC, ucPdoIndex, &stTypeCUserPdo);

                    if(ScalerTypeCCheckPdoChange(_D0_INPUT_PORT, ucPdoIndex, stTypeCUserPdo) == _TYPE_C_PDO_CHANGE)
                    {
                        if(stTypeCUserPdo.enumPdoType == _PD_FIX_SUPPLY_PDO)
                        {
                            ScalerTypeCSetFixPdo(_D0_INPUT_PORT, _TYPE_C_POWER_SRC, ucPdoIndex, stTypeCUserPdo.ucMaxVoltage, stTypeCUserPdo.ucMaxCurrent);
                        }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                        else if(stTypeCUserPdo.enumPdoType == _PD_3_PROGRAMMABLE_PDO)
                        {
                            ScalerTypeCSetPpsPdo(_D0_INPUT_PORT, _TYPE_C_POWER_SRC, ucPdoIndex, stTypeCUserPdo.ucMinVoltage, stTypeCUserPdo.ucMaxVoltage, stTypeCUserPdo.ucMaxCurrent);
                        }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)

                        enumSrcCapPdoChange = _TYPE_C_PDO_CHANGE;

                        // Debug Message
                        DebugMessageSystem("8. [TYPE C] <PDO> ======== PDO Num ========", ucPdoIndex);
                        DebugMessageSystem("8. [TYPE C] <PDO> Voltage (1V)", (stTypeCUserPdo.ucMaxVoltage / 10));
                        DebugMessageSystem("8. [TYPE C] <PDO> Current (0.01A)", ((stTypeCUserPdo.ucMaxCurrent * 10) / 2));
                    }
                }
            }
            else
            {
                // Source PDO Defined By Kernel (PDP = 27W / 5V@3A + 9V@3A)
                ScalerTypeCSetPdoByKernel(_D0_INPUT_PORT, _TYPE_C_POWER_SRC);
            }

#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
            ucPdoCount = ScalerTypeCGetPdoCnt(_D0_INPUT_PORT, _TYPE_C_POWER_SRC);

            for(ucPdoIndex = 1; ucPdoIndex <= ucPdoCount; ucPdoIndex++)
            {
                UserCommonInterfaceTypeCGetProtectInfo(_D0_INPUT_PORT, ucPdoIndex, &stTypeCUserProtectInfo);
                ScalerTypeCSetProtectInfo(_D0_INPUT_PORT, ucPdoIndex, stTypeCUserProtectInfo);
            }
#endif

#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }

    return enumSrcCapPdoChange;
}

//--------------------------------------------------
// Description  : Initial State Set Up Port Ctrl SNK Capability
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCSetPortCtrlSinkCap(BYTE ucInputPort)
{
    BYTE ucPdoCount = 0;
    BYTE ucPdoIndex = 0;
    StructTypeCUserPDO stTypeCUserPdo;

    ucPdoCount = ucPdoCount;
    ucPdoIndex = ucPdoIndex;
    stTypeCUserPdo = stTypeCUserPdo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

            // 1. Get PDO Info From User / Kernel
            if(UserCommonInterfaceTypeCPdoReference(_D0_INPUT_PORT, _TYPE_C_POWER_SNK) == _TYPE_C_PDO_FROM_USER)
            {
                // Get Sink PDO Count from User
                ucPdoCount = UserCommonInterfaceTypeCGetPdoCount(_D0_INPUT_PORT, _TYPE_C_POWER_SNK);
                ScalerTypeCSetPdoCnt(_D0_INPUT_PORT, _TYPE_C_POWER_SNK, ucPdoCount);

                // 4. Get PDO Info and Write to Port Controller
                for(ucPdoIndex = 1; ucPdoIndex <= ucPdoCount; ucPdoIndex++)
                {
                    // Set PDO to Default Value
                    stTypeCUserPdo.enumPdoType = _PD_FIX_SUPPLY_PDO;
                    stTypeCUserPdo.ucMaxCurrent = 0;
                    stTypeCUserPdo.ucMaxVoltage = 0;
                    stTypeCUserPdo.ucMinVoltage = 0;

                    // Get User 1st - 7th Sink PDO Info
                    UserCommonInterfaceTypeCGetPdoInfo(_D0_INPUT_PORT, _TYPE_C_POWER_SNK, ucPdoIndex, &stTypeCUserPdo);

                    if(stTypeCUserPdo.enumPdoType == _PD_FIX_SUPPLY_PDO)
                    {
                        ScalerTypeCSetFixPdo(_D0_INPUT_PORT, _TYPE_C_POWER_SNK, ucPdoIndex, stTypeCUserPdo.ucMaxVoltage, stTypeCUserPdo.ucMaxCurrent);
                    }
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
                    else if(stTypeCUserPdo.enumPdoType == _PD_3_PROGRAMMABLE_PDO)
                    {
                        ScalerTypeCSetPpsPdo(_D0_INPUT_PORT, _TYPE_C_POWER_SNK, ucPdoIndex, stTypeCUserPdo.ucMinVoltage, stTypeCUserPdo.ucMaxVoltage, stTypeCUserPdo.ucMaxCurrent);
                    }
#endif  // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)

                    // Debug Message
                    DebugMessageSystem("8. [TYPE C] <PDO> ======== PDO Num ========", ucPdoIndex);
                    DebugMessageSystem("8. [TYPE C] <PDO> Voltage (1V)", (stTypeCUserPdo.ucMaxVoltage / 10));
                    DebugMessageSystem("8. [TYPE C] <PDO> Current (0.01A)", ((stTypeCUserPdo.ucMaxCurrent * 10) / 2));
                }
            }
            else
            {
                // Sink PDO Defined By Kernel (5V @ 500mA)
                ScalerTypeCSetPdoByKernel(_D0_INPUT_PORT, _TYPE_C_POWER_SNK);
            }
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Content of Port Ctrl Request When Receive Src Cap
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCSetPortCtrlRequest(BYTE ucInputPort)
{
    // Default Request 5V @ 500mA
    StructTypeCUserRDO stTypeCUserRdo = {_TYPE_C_PDO_NUM_1, 50, 50, _FALSE, _FALSE};
    stTypeCUserRdo = stTypeCUserRdo;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

            // 1. Get RDO Info From User / Kernel
            if(UserCommonInterfaceTypeCRdoReference(_D0_INPUT_PORT) == _TYPE_C_RDO_FROM_USER)
            {
                // Get User Request Info
                UserCommonInterfaceTypeCGetRdoInfo(_D0_INPUT_PORT, &stTypeCUserRdo);
            }

            // Set Request Info to Embedded Port Ctrl
            ScalerTypeCSetRdo(_D0_INPUT_PORT, stTypeCUserRdo);

            // Request Embedded TypeC to Send Src Cap
            ScalerTypeCSetPdSystemEvent(_D0_INPUT_PORT, _PD_SYS_EVENT_SEND_REQUEST);

            // Debug Message
            DebugMessageSystem("8. [TYPE C] <RDO> Object Position =", stTypeCUserRdo.enumObjPos);
            DebugMessageSystem("8. [TYPE C] <RDO> Info1 (Fix PDO = Op Cur in 10mA / PPS PDO = Vol in 20mV)", stTypeCUserRdo.usReqInfo1);
            DebugMessageSystem("8. [TYPE C] <RDO> Info2 (Fix PDO = Max Cur in 10mA / PPS PDO = Op. Cur in 50mA)", stTypeCUserRdo.usReqInfo2);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get Port Controller CC Attached Info (5400 & User : From GPIO / Embedded From : CC Attach Flag)
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach Status (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus SysTypeCGetPortControllerCcAttach(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetCcAttach(ucInputPort);

#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetCcAttach(ucInputPort);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetCcAttach(ucInputPort);

#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetCcAttach(ucInputPort);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetCcAttach(ucInputPort);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetCcAttach(ucInputPort);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _TYPE_C_UNATTACH;

            break;
    }
    return _TYPE_C_UNATTACH;
}

//--------------------------------------------------
// Description  : Get Port Controller DP Alt. Mode Ready Info (5400 & User : From GPIO / Embedded From : DP Alt Mode Ready Flag)
// Input Value  : ucInputPort --> Inputput
// Output Value : DP Alt Mode Ready Status (_TYPE_C_ALT_MODE_READY / _TYPE_C_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAltModeStatus SysTypeCGetPortControllerAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAltModeReady(ucInputPort);
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetAltModeReady(ucInputPort);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAltModeReady(ucInputPort);
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetAltModeReady(ucInputPort);
#endif
            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAltModeReady(ucInputPort);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerGetAltModeReady(ucInputPort);
#endif
            break;
#endif

        default:

            return _TYPE_C_ALT_MODE_NOT_READY;

            break;
    }
    return _TYPE_C_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Get Port Controller Orientation
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
EnumTypeCOrientation SysTypeCGetPortControllerOrientation(BYTE ucInputPort)
{
    EnumTypeCOrientation enumOrientation = _TYPE_C_ORIENTATION_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumOrientation = ScalerTypeCGetOrientation(_D0_INPUT_PORT);
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER))
            enumOrientation = UserCommonPortControllerGetUserOrientation(_D0_INPUT_PORT);
#else
            enumOrientation = _TYPE_C_ORIENTATION_UNFLIP;
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumOrientation = ScalerTypeCGetOrientation(_D1_INPUT_PORT);
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER))
            enumOrientation = UserCommonPortControllerGetUserOrientation(_D1_INPUT_PORT);
#else
            enumOrientation = _TYPE_C_ORIENTATION_UNFLIP;
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumOrientation = ScalerTypeCGetOrientation(_D6_INPUT_PORT);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER))
            enumOrientation = UserCommonPortControllerGetUserOrientation(_D6_INPUT_PORT);
#else
            enumOrientation = _TYPE_C_ORIENTATION_UNFLIP;
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            DebugMessageSystem("8. [TYPE C] ==========X SysTypeC Get Port Ctrl Orientation with Invalid Port :", ucInputPort);

            break;
    }

    DebugMessageSystem("8. [TYPE C] ==========> Get Port Ctrl Orientation:", enumOrientation);
    return enumOrientation;
}

//--------------------------------------------------
// Description  : Get Port Controller Pin Assignment (5400 & User : From I2C / Embedded From : Pin Assignment Flag)
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
bit SysTypeCGetPortControllerPinAssignment(BYTE ucInputPort)
{
    EnumTypeCPinCfgType enumPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            if(ScalerTypeCGetPinAssignment(_D0_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerGet5400PinAssignment(_D0_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            if(UserCommonPortControllerGetUserPinAssignment(_D0_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#endif
            {
                DebugMessageSystem("8. [TYPE C] ==========> Get Port Ctrl Pin Assignment (C:4 / D:8):", enumPinAssignment);

                SET_TYPE_C_PIN_ASSIGNMENT(_D0_INPUT_PORT, enumPinAssignment);

                return _SUCCESS;
            }
            else
            {
                SET_TYPE_C_PIN_ASSIGNMENT(_D0_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);

                return _FAIL;
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            if(ScalerTypeCGetPinAssignment(_D1_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerGet5400PinAssignment(_D1_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            if(UserCommonPortControllerGetUserPinAssignment(_D1_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#endif
            {
                DebugMessageSystem("8. [TYPE C] ==========> SysTypeC Get Port Ctrl Pin Assignment :", enumPinAssignment);

                SET_TYPE_C_PIN_ASSIGNMENT(_D1_INPUT_PORT, enumPinAssignment);

                return _SUCCESS;
            }
            else
            {
                SET_TYPE_C_PIN_ASSIGNMENT(_D1_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);

                return _FAIL;
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            if(ScalerTypeCGetPinAssignment(_D6_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            if(UserCommonPortControllerGet5400PinAssignment(_D6_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            if(UserCommonPortControllerGetUserPinAssignment(_D6_INPUT_PORT, &enumPinAssignment) == _SUCCESS)
#endif
            {
                DebugMessageSystem("8. [TYPE C] ==========> SysTypeC Get Port Ctrl Pin Assignment :", enumPinAssignment);

                SET_TYPE_C_PIN_ASSIGNMENT(_D6_INPUT_PORT, enumPinAssignment);

                return _SUCCESS;
            }
            else
            {
                SET_TYPE_C_PIN_ASSIGNMENT(_D6_INPUT_PORT, _TYPE_C_PIN_ASSIGNMENT_NONE);

                return _FAIL;
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            DebugMessageSystem("8. [TYPE C] ==========X SysTypeC Get Port Corl with Invalid Port :", ucInputPort);

            SET_TYPE_C_PIN_ASSIGNMENT(ucInputPort, _TYPE_C_PIN_ASSIGNMENT_NONE);

            return _FAIL;

            break;
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : Get Port Controller Power Role (Do Not Continually Call This Function)
// Input Value  : ucInputPort --> Inputput
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC / _TYPE_C_POWER_ROLE_NONE)
//--------------------------------------------------
EnumTypeCPowerRole SysTypeCGetPortControllerPowerRole(BYTE ucInputPort)
{
    EnumTypeCPowerRole enumTypeCPowerRole = _TYPE_C_POWER_ROLE_NONE;

    if(SysTypeCGetCcAttach(ucInputPort) == _FALSE)
    {
        return enumTypeCPowerRole;
    }

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumTypeCPowerRole = ScalerTypeCGetPowerRole(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            enumTypeCPowerRole = UserCommonPortControllerGet5400PowerRole(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            enumTypeCPowerRole = UserCommonPortControllerGetUserPowerRole(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumTypeCPowerRole = ScalerTypeCGetPowerRole(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            enumTypeCPowerRole = UserCommonPortControllerGet5400PowerRole(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            enumTypeCPowerRole = UserCommonPortControllerGetUserPowerRole(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumTypeCPowerRole = ScalerTypeCGetPowerRole(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            enumTypeCPowerRole = UserCommonPortControllerGet5400PowerRole(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            enumTypeCPowerRole = UserCommonPortControllerGetUserPowerRole(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            DebugMessageSystem("8. [TYPE C] ==========X SysTypeC Get Port Ctrl Power Role with Invalid Port :", ucInputPort);

            break;
    }

    DebugMessageSystem("8. [TYPE C] ==========> Get Port Ctrl Power Role:", enumTypeCPowerRole);
    return enumTypeCPowerRole;
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping According to 5400 / User Pin Assignment
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCSetDpLaneMapping(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment, EnumTypeCOrientation enumOrientation)
{
    ucInputPort = ucInputPort;
    enumPinAssignment = enumPinAssignment;
    enumOrientation = enumOrientation;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

            // Adjust Lane Mapping According to User Port Controller Pin Assignment and Orientation
            DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping :", enumPinAssignment);

            UserCommonPortControllerPinMappingSetting(ucInputPort, enumPinAssignment, enumOrientation);
#endif

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

            // Adjust Lane Mapping According to User Port Controller Pin Assignment and Orientation
            DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping :", enumPinAssignment);

            UserCommonPortControllerPinMappingSetting(ucInputPort, enumPinAssignment, enumOrientation);
#endif

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))

            // Adjust Lane Mapping According to User Port Controller Pin Assignment and Orientation
            DebugMessageSystem("8. [TYPE C] ==========> Adjust Lane Mapping :", enumPinAssignment);

            UserCommonPortControllerPinMappingSetting(ucInputPort, enumPinAssignment, enumOrientation);
#endif

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            DebugMessageSystem("8. [TYPE C] ==========X SysTypeC Set Lane Mapping with Invalid Port :", ucInputPort);

            break;
    }
}

//--------------------------------------------------
// Description  : Check if Specific Capability Has Been Changed
// Input Value  : ucInputPort --> Inputput, ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
bit SysTypeCheckCapabilityChange(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability)
{
    switch(enumCapability)
    {
        case _TYPE_C_HUB_INPUT_SWITCH_CHG:

            if((GET_TYPE_C_CAPABILITY_CHG(ucInputPort) & _TYPE_C_HUB_INPUT_SWITCH_CHG) == _TYPE_C_HUB_INPUT_SWITCH_CHG)
            {
#if(_USB3_RETIMER_SUPPORT == _ON)
                // Updata Hub UFP Status marco
                ScalerUSB3RetimerSetHubUfpStatus(UserCommonPortControllerGetHubInputPort(ucInputPort));
#endif

                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;

        case _TYPE_C_PIN_ASSIGNMENT_CAP_CHG:

            if((GET_TYPE_C_CAPABILITY_CHG(ucInputPort) & _TYPE_C_PIN_ASSIGNMENT_CAP_CHG) == _TYPE_C_PIN_ASSIGNMENT_CAP_CHG)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;

        case _TYPE_C_SRC_CAP_CHG:

            if((GET_TYPE_C_CAPABILITY_CHG(ucInputPort) & _TYPE_C_SRC_CAP_CHG) == _TYPE_C_SRC_CAP_CHG)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Reconfig, and Switch to Reconnect State if Current Config does not Match the Latest Requirement
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCPinAssignmentCapabilityChangeProc(BYTE ucInputPort)
{
    // 1. Update Prot Controller (5400/User/Embedded) Config
    if(SysTypeCUpdatePortControllerConfig(ucInputPort) == _SUCCESS)
    {
        // 2. Check if Port Ctrl Support Reconnect or Not
        if(SysTypeCReconnectSupport(ucInputPort) == _TRUE)
        {
            // 3. Switch to Reconnect State if Current Config does not Match the Latest Requirement
            switch(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort))
            {
                case _TYPE_C_PIN_ASSIGNMENT_C:

                    if(UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_ON)
                    {
                        SET_TYPE_C_STATE(ucInputPort, _TYPE_C_RECONNECT_STATE);
                        DebugMessageSystem("8. [TYPE C] ==========> U3 Mode Mismatch, RECONNECT", 0);
                    }

                    break;

                case _TYPE_C_PIN_ASSIGNMENT_D:

                    if(UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_OFF)
                    {
                        SET_TYPE_C_STATE(ucInputPort, _TYPE_C_RECONNECT_STATE);
                        DebugMessageSystem("8. [TYPE C] ==========> U3 Mode Mismatch, RECONNECT", 0);
                    }

                    break;

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
                case _TYPE_C_PIN_ASSIGNMENT_E:

                    if(UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(ucInputPort) == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF)
                    {
                        SET_TYPE_C_STATE(ucInputPort, _TYPE_C_RECONNECT_STATE);
                        DebugMessageSystem("8. [TYPE C] ==========> Pin Assignment E Support Mismatch, RECONNECT", 0);
                    }

                    break;
#endif

                default:

                    break;
            }
        }

        // 4. Clear Pin Assignment Capability Change Flag
        SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_PIN_ASSIGNMENT_CAP_CHG);
        DebugMessageSystem("8. [TYPE C] ==========> Update Config Successfully, Clear Pin Assignment Cap Change", 1);
    }
}

//--------------------------------------------------
// Description  : Request Port Controller to Re-Send Src Capability Message
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCSrcCapabilityChangeProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // Request Embedded TypeC to Send Src Cap
            ScalerTypeCSetPdSystemEvent(_D0_INPUT_PORT, _PD_SYS_EVENT_SEND_SRC_CAP);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            break;
#endif

        default:

            break;
    }

    // Clear Source Capability Change Flag
    SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_SRC_CAP_CHG);
}

//--------------------------------------------------
// Description  : Check Port Controller Support Reconnect or not
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_TRUE / _FALSE)
//--------------------------------------------------
bit SysTypeCReconnectSupport(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return _TRUE;

#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerReconnectSupport(_D0_INPUT_PORT);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return _TRUE;

#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerReconnectSupport(_D1_INPUT_PORT);
#endif
            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return _TRUE;

#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerReconnectSupport(_D6_INPUT_PORT);
#endif
            break;
#endif

        default:

            return _FALSE;

            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Request Port Controller to Reconnect
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
bit SysTypeCReconnect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCReconnect(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortController5400Reconnect(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerUserReconnect(_D0_INPUT_PORT);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCReconnect(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortController5400Reconnect(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerUserReconnect(_D1_INPUT_PORT);
#endif
            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCReconnect(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortController5400Reconnect(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerUserReconnect(_D6_INPUT_PORT);
#endif
            break;
#endif

        default:

            return _FAIL;

            break;
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : Transit Type C State After Reconnect Success
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
void SysTypeCReconnectTransition(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            // Set TypeC State to Unattach
            SET_TYPE_C_ORIENTATION(_D0_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
            SET_TYPE_C_STATE(_D0_INPUT_PORT, _TYPE_C_UNATTACH_STATE);

            // Restart CC Attach & Alt. Mode Ready Detection By I2C Later
            UserCommonPortControllerRestartD0I2CDetection(_TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
            SysTypeCLenovoAltModeReset(_D0_INPUT_PORT);
#endif
#else
            // If Port Controller Not Switch to Unattach in 500ms, Force Switch to Unattach State
            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_UNATTACH);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            // Set TypeC State to Unattach
            SET_TYPE_C_ORIENTATION(_D1_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
            SET_TYPE_C_STATE(_D1_INPUT_PORT, _TYPE_C_UNATTACH_STATE);

            // Restart CC Attach & Alt. Mode Ready Detection By I2C Later
            UserCommonPortControllerRestartD1I2CDetection(_TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
            SysTypeCLenovoAltModeReset(_D1_INPUT_PORT);
#endif
#else
            // If Port Controller Not Switch to Unattach in 500ms, Force Switch to Unattach State
            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_UNATTACH);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
            // Set TypeC State to Unattach
            SET_TYPE_C_ORIENTATION(_D6_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
            SET_TYPE_C_STATE(_D6_INPUT_PORT, _TYPE_C_UNATTACH_STATE);

            // Restart CC Attach & Alt. Mode Ready Detection By I2C Later
            UserCommonPortControllerRestartD6I2CDetection(_TYPE_C_RESTART_CHECK_CABLE_STATUS_TIME);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
            SysTypeCLenovoAltModeReset(_D6_INPUT_PORT);
#endif
#else
            // If Port Controller Not Switch to Unattach in 500ms, Force Switch to Unattach State
            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_UNATTACH);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Update Port Controller Configuration
// Input Value  : ucInputPort --> Inputput
// Output Value : Reconnect Status (_SUCCESS / _FAIL)
//--------------------------------------------------
bit SysTypeCUpdatePortControllerConfig(BYTE ucInputPort)
{
    // Default Set U3 Mode to OFF and Pin Assignment E Support Status to ON
    EnumTypeCU3ModeType enumU3Mode = _TYPE_C_U3_OFF;
    EnumTypeCMultiFuncStatus enumMultiFunc = _TYPE_C_MULTI_FUNC_NOT_PREFER;
    EnumTypeCPinAssignmentESupportStatus enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON;
    EnumTypeCPinCfgCapType enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_NONE;

    // Update U3 Mode / Multi-Function Bit (From User)
    if(UserInterfaceTypeCGetOsdU3ModeSelection(ucInputPort) == _TYPE_C_U3_ON)
    {
        enumU3Mode = _TYPE_C_U3_ON;
        enumMultiFunc = _TYPE_C_MULTI_FUNC_PREFER;
    }

#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    // Update Pin Assignment E Support Capability (From User)
    if(UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(ucInputPort) == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF)
    {
        enumPinAssignmentESupportStatus = _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF;
    }
#endif

    // Update Pin Assignment Capability (From User)
    enumPinAssignmentCap = UserInterfaceTypeCGetPinConfigType(ucInputPort, enumU3Mode, enumPinAssignmentESupportStatus);

    if(enumPinAssignmentCap == _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT)
    {
        // Use Kernal Default Setting if User Select Follow Kernel Setting
        if(enumU3Mode == _TYPE_C_U3_ON)
        {
            if(enumPinAssignmentESupportStatus == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
            {
                enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CDE;
            }
            else
            {
                enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CD;
            }
        }
        else
        {
            if(enumPinAssignmentESupportStatus == _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON)
            {
                enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_CE;
            }
            else
            {
                enumPinAssignmentCap = _TYPE_C_PIN_ASSIGNMENT_CAP_C;
            }
        }
    }

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCUpdateConfig(_D0_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerUpdateConfig(_D0_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#endif
            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCUpdateConfig(_D1_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerUpdateConfig(_D1_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#endif
            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCUpdateConfig(_D6_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))
            return UserCommonPortControllerUpdateConfig(_D6_INPUT_PORT, enumMultiFunc, enumPinAssignmentCap);
#endif
            break;
#endif

        default:

            return _FAIL;

            break;
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : Get Port Controller Number of Partner Src/Snk PDOs
// Input Value  : ucInputPort
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE SysTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0;

    ucInputPort = ucInputPort;
    enumPowerRole = enumPowerRole;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ucPdoCnt = ScalerTypeCGetPartnerPdoCnt(_D0_INPUT_PORT, enumPowerRole);
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            ucPdoCnt = UserCommonPortControllerGet5400PartnerPdoCnt(_D0_INPUT_PORT, enumPowerRole);
#endif

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ucPdoCnt = ScalerTypeCGetPartnerPdoCnt(_D1_INPUT_PORT, enumPowerRole);
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            ucPdoCnt = UserCommonPortControllerGet5400PartnerPdoCnt(_D1_INPUT_PORT, enumPowerRole);
#endif

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ucPdoCnt = ScalerTypeCGetPartnerPdoCnt(_D6_INPUT_PORT, enumPowerRole);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            ucPdoCnt = UserCommonPortControllerGet5400PartnerPdoCnt(_D6_INPUT_PORT, enumPowerRole);
#endif

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Get Port Controller Partner Source/Sink PDO Info
// Input Value  : ucInputPort, enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 50mA)
//--------------------------------------------------
StructTypeCUserPDO SysTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnerPdo;

    // Reset Default Value to Fix PDO w/ 0V @ 0A
    stTypeCPartnerPdo.enumPdoType = _PD_FIX_SUPPLY_PDO;
    stTypeCPartnerPdo.ucMaxVoltage = 0;
    stTypeCPartnerPdo.ucMinVoltage = 0;
    stTypeCPartnerPdo.ucMaxCurrent = 0;

    ucInputPort = ucInputPort;
    enumPowerRole = enumPowerRole;
    ucPdoIndex = ucPdoIndex;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stTypeCPartnerPdo = ScalerTypeCGetPartnerPdo(_D0_INPUT_PORT, enumPowerRole, ucPdoIndex);
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            // Partner Source/Sink PDO Info is Updated from 5400 when Using "SysTypeCGetPartnerPdoCnt" to Get Num of Partner Source/Sink PDO
            stTypeCPartnerPdo = UserCommonPortControllerGet5400PartnerPdo(_D0_INPUT_PORT, enumPowerRole, ucPdoIndex);
#endif

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stTypeCPartnerPdo = ScalerTypeCGetPartnerPdo(_D1_INPUT_PORT, enumPowerRole, ucPdoIndex);
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            // Partner Source/Sink PDO Info is Updated from 5400 when Using "SysTypeCGetPartnerPdoCnt" to Get Num of Partner Source/Sink PDO
            stTypeCPartnerPdo = UserCommonPortControllerGet5400PartnerPdo(_D1_INPUT_PORT, enumPowerRole, ucPdoIndex);
#endif

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stTypeCPartnerPdo = ScalerTypeCGetPartnerPdo(_D6_INPUT_PORT, enumPowerRole, ucPdoIndex);
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            // Partner Source/Sink PDO Info is Updated from 5400 when Using "SysTypeCGetPartnerPdoCnt" to Get Num of Partner Source/Sink PDO
            stTypeCPartnerPdo = UserCommonPortControllerGet5400PartnerPdo(_D6_INPUT_PORT, enumPowerRole, ucPdoIndex);
#endif

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
    return stTypeCPartnerPdo;
}

//--------------------------------------------------
// Description  : Get Port Controller Negotiated Voltage / Current
// Input Value  : ucInputPort, Voltage (100mV) / Current (50mA)
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit SysTypeCGetPdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent)
{
    ucInputPort = ucInputPort;
    *pucVoltage = *pucVoltage;
    *pucCurrent = *pucCurrent;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // CC Attached, Power Contract Established : Return Negotiated Voltage & Current
            // CC Attached, No Power Contract : Return 5V / Current According to Rp Value
            // CC Unattached : Return FAIL
            if(ScalerTypeCGetPdoStatus(_D0_INPUT_PORT, pucVoltage, pucCurrent) == _SUCCESS)
            {
                return _SUCCESS;
            }
            else
#elif((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            // Power Contract Established & Port Partner is Source : Return Negotiated Voltage & Current
            // No Power Contract or Port Partner is Sink : Return FAIL
            if(UserCommonPortControllerGet5400PdoStatus(_D0_INPUT_PORT, pucVoltage, pucCurrent) == _SUCCESS)
            {
                return _SUCCESS;
            }
            else
#endif
            {
                return _FAIL;
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // CC Attached, Power Contract Established : Return Negotiated Voltage & Current
            // CC Attached, No Power Contract : Return 5V / Current According to Rp Value
            // CC Unattached : Return FAIL
            if(ScalerTypeCGetPdoStatus(_D1_INPUT_PORT, pucVoltage, pucCurrent) == _SUCCESS)
            {
                return _SUCCESS;
            }
            else
#elif((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            // Power Contract Established & Port Partner is Source : Return Negotiated Voltage & Current
            // No Power Contract or Port Partner is Sink : Return FAIL
            if(UserCommonPortControllerGet5400PdoStatus(_D1_INPUT_PORT, pucVoltage, pucCurrent) == _SUCCESS)
            {
                return _SUCCESS;
            }
            else
#endif
            {
                return _FAIL;
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            // CC Attached, Power Contract Established : Return Negotiated Voltage & Current
            // CC Attached, No Power Contract : Return 5V / Current According to Rp Value
            // CC Unattached : Return FAIL
            if(ScalerTypeCGetPdoStatus(_D6_INPUT_PORT, pucVoltage, pucCurrent) == _SUCCESS)
            {
                return _SUCCESS;
            }
            else
#elif((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
            // Power Contract Established & Port Partner is Source : Return Negotiated Voltage & Current
            // No Power Contract or Port Partner is Sink : Return FAIL
            if(UserCommonPortControllerGet5400PdoStatus(_D6_INPUT_PORT, pucVoltage, pucCurrent) == _SUCCESS)
            {
                return _SUCCESS;
            }
            else
#endif
            {
                return _FAIL;
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _FAIL;

            break;
    }
    return _FAIL;
}

//--------------------------------------------------
// Description  : Return CC Attached Status to SysSource According to SysTypeC State
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach Status (_TRUE / _FALSE)
//--------------------------------------------------
bit SysTypeCGetCcAttach(BYTE ucInputPort)
{
    switch(GET_TYPE_C_STATE(ucInputPort))
    {
        case _TYPE_C_ATTACHED_STATE:
        case _TYPE_C_DP_ALT_MODE_READY_STATE:
        case _TYPE_C_RECONNECT_STATE:

            return _TRUE;

            break;

        case _TYPE_C_UNATTACH_STATE:

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
            return ScalerTypeCRx0CcGetACOnDeviceDetect();
#else
            return _FALSE;
#endif

            break;

        default:

            return _FALSE;

            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Return Alt Mode Ready Statsu to SysSource According to SysTypeC State
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach Status (_TRUE / _FALSE)
//--------------------------------------------------
bit SysTypeCGetAltModeReady(BYTE ucInputPort)
{
    switch(GET_TYPE_C_STATE(ucInputPort))
    {
        case _TYPE_C_DP_ALT_MODE_READY_STATE:
        case _TYPE_C_RECONNECT_STATE:

            return _TRUE;

            break;

        case _TYPE_C_UNATTACH_STATE:
        case _TYPE_C_ATTACHED_STATE:
        default:

            return _FALSE;

            break;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Return Port Controller Negotiated Pin Assignment
// Input Value  : ucInputPort --> Inputput
// Output Value : Pin Assignment (Retern None When Alt Mode Not Ready Yet)
//--------------------------------------------------
EnumTypeCPinCfgType SysTypeCGetPinAssignment(BYTE ucInputPort)
{
    EnumTypeCPinCfgType enumPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    if(SysTypeCGetAltModeReady(ucInputPort) == _TRUE)
    {
        enumPinAssignment = GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort);
    }

    return enumPinAssignment;
}

//--------------------------------------------------
// Description  : Trnaslate ucInputPort into Type-C Port Index For Macro Usage
// Input Value  : ucInputPort
// Output Value : Type-C Port Index
//--------------------------------------------------
BYTE SysTypeCGetTypeCIndex(BYTE ucInputPort)
{
    BYTE ucIndex = 0x00;

#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(ucInputPort == _D0_INPUT_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(ucInputPort == _D1_INPUT_PORT)
    {
        return ucIndex;
    }
    else
    {
        ucIndex = ucIndex + 1;
    }

#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

    if(ucInputPort == _D6_INPUT_PORT)
    {
        return ucIndex;
    }

#endif

    // ucInputPort Invalid : Show Warning Message
    DebugMessageSystem("8. [TYPE C] ==========X Invalid InputPort For TypeC Index", ucInputPort);

    return ucIndex;
}

#if(_DP_PORT_EXIST == _ON)
//--------------------------------------------------
// Description  : Check if Specific ucInputPort is TypeC Port Controller or Not
// Input Value  : ucInputPort
// Output Value : Type-C Connector _TRUE / _FALSE
//--------------------------------------------------
bit SysTypeCCheckTypeCPortControllerExist(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON))
            return _TRUE;
#else
            return _FALSE;
#endif
            break;

        case _D1_INPUT_PORT:
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON))
            return _TRUE;
#else
            return _FALSE;
#endif
            break;

        default:

            return _FALSE;

            break;
    }
    return _FALSE;
}
#endif // End of #if((_DP_PORT_EXIST == _ON) && (_SOURCE_AUTO_SEARCH_STYLE != _SOURCE_POLLING_IN_SEARCH_STATE))

//--------------------------------------------------
// Description  : Trnaslate Alt. Mode Pin Assignment to DP Lane Count
// Input Value  : ucPinAssignment
// Output Value : EnumDpLaneCount -> _DP_LINK_1_LANE / _DP_LINK_2_LANE / _DP_LINK_4_LANE
//--------------------------------------------------
EnumDpLaneCount SysTypeCGetAltModeLaneCnt(EnumTypeCPinCfgType enumPinAssignment)
{
    EnumDpLaneCount enumAltModeLaneCnt = _DP_LINK_4_LANE;
    switch(enumPinAssignment)
    {
        case _TYPE_C_PIN_ASSIGNMENT_C:
        case _TYPE_C_PIN_ASSIGNMENT_E:

            enumAltModeLaneCnt = _DP_LINK_4_LANE;

            break;

        case _TYPE_C_PIN_ASSIGNMENT_D:

            enumAltModeLaneCnt = _DP_LINK_2_LANE;

            break;


        default:

            break;
    }

    return enumAltModeLaneCnt;
}

//--------------------------------------------------
// Description  : Update OSD Lane Count
// Input Value  : ucInputPort --> Inputput, enumDpLaneCount : _DP_LINK_1_LANE / _DP_LINK_2_LANE / _DP_LINK_4_LANE
// Output Value : NONE
//--------------------------------------------------
void SysTypeCSwitchOSDLaneCount(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            UserCommonNVRamSetSystemData(_DP_D0_LANES, enumDpLaneCount);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            UserCommonNVRamSetSystemData(_DP_D1_LANES, enumDpLaneCount);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            UserCommonNVRamSetSystemData(_DP_D6_LANES, enumDpLaneCount);

            break;
#endif

        default:
            break;
    }

    UserCommonNVRamSaveSystemData();
}

//--------------------------------------------------
// Description  : Set Capability Change Flag
// Input Value  : ucInputPort --> Inputput, enumCapability --> Target Capability
// Output Value : NONE
//--------------------------------------------------
void SysTypeCSetCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            SET_TYPE_C_CAPABILITY_CHG(_D0_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            SET_TYPE_C_CAPABILITY_CHG(_D1_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            SET_TYPE_C_CAPABILITY_CHG(_D6_INPUT_PORT, enumCapability);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clear Capability Change Flag
// Input Value  : ucInputPort --> Inputput, enumCapability --> Target Capability
// Output Value : NONE
//--------------------------------------------------
void SysTypeCClrCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            CLR_TYPE_C_CAPABILITY_CHG(_D0_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            CLR_TYPE_C_CAPABILITY_CHG(_D1_INPUT_PORT, enumCapability);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            CLR_TYPE_C_CAPABILITY_CHG(_D6_INPUT_PORT, enumCapability);

            break;
#endif

        default:
            break;
    }
}

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Do TypeC Alt Mode Handler Process According to Port Controller Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCAltModeHandler(BYTE ucInputPort)
{
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_VENDOR_ALT_MODE_NONE)
    ucInputPort = ucInputPort;
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};
    StructTypeCLenovoDockEvent stLenovoDockEvent = {_TYPE_C_LENOVO_DOCK_POWER_SWITCH_NONE, _FALSE, _FALSE, 0x00};

    // Check if Lenovo VDM Function is Supported According to Device Type from Port Partner
    if(((GET_TYPE_C_LENOVO_DEVICE_TYPE(ucInputPort) != _TYPE_C_LENOVO_DEVICE_TYPE_NONE) && (GET_TYPE_C_LENOVO_DEVICE_TYPE(ucInputPort) != _TYPE_C_LENOVO_DESKTOP_PC)) || (GET_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(ucInputPort) == _TRUE))
    {
        return;
    }

    // Get Lenovo Alt Mode Status from Port Ctrl
    SET_TYPE_C_LENOVO_ALT_MODE_STATUS(ucInputPort, SysTypeCGetPortControllerLenovoAltModeReady(ucInputPort));

    if(GET_TYPE_C_LENOVO_ALT_MODE_STATUS(ucInputPort) == _TYPE_C_LENOVO_ALT_MODE_READY)
    {
        if(GET_TYPE_C_LENOVO_DEVICE_TYPE(ucInputPort) != _TYPE_C_LENOVO_DESKTOP_PC)
        {
            // If Port Controller Not Receive Device Type in 8 sec, Set Type C to Receive Lenovo Device Type Timeout
            SysTypeCActiveLenovoRcvDeviceTypeTimerEvent(ucInputPort, 8000);

            // Get Lenovo Device Type from Port Ctrl
            SET_TYPE_C_LENOVO_DEVICE_TYPE(ucInputPort, SysTypeCGetPortControllerLenovoDeviceType(ucInputPort));
        }
        else
        {
            // Cancel Timer Event Which Set Type C to Receive Lenovo Device Type Timeout
            SysTypeCCancelLenovoRcvDeviceTypeTimerEvent(ucInputPort);
            CLR_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(ucInputPort);

            // Get LenovoSysEvent (Including System Acknowledge) from Port Ctrl
            stLenovoSysEvent = SysTypeCGetPortControllerLenovoSystemEvent(ucInputPort);

            if((stLenovoSysEvent.b1SystemEvent == _TRUE) || ((stLenovoSysEvent.ucSystemAcknowlegde & _BIT0) == _BIT0))
            {
                // Set LenovoSysEvent (Including System Acknowledge) to User
                UserCommonInterfaceTypeCLenovoAltModeHandler(ucInputPort, stLenovoSysEvent);
            }

            // Check if Last Docking Event has been Sent
            if(SysTypeCCheckPortControllerLenovoDockingEventBusy(ucInputPort) == _FALSE)
            {
                // Get LenovoDockEvent from User
                UserCommonInterfaceTypeCGetLenovoDockingEvent(ucInputPort, &stLenovoDockEvent);

                // Set LenovoDockEvent to Port Ctrl
                SysTypeCSetPortControllerLenovoDockingEvent(ucInputPort, stLenovoDockEvent);
            }
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
    StructTypeCAcerSysEvent stAcerSysEvent = {_TYPE_C_ACER_SYS_EVENT_NONE, {0x00}, 0x00};
    StructTypeCAcerUserEvent stAcerUserEvent = {_TYPE_C_ACER_USER_EVENT_NONE, {0x00}, 0x00};

    if(SysTypeCGetPortControllerAcerAltModeReady(ucInputPort) == _TYPE_C_ACER_ALT_MODE_READY)
    {
        // Get Acer System Event from Port Ctrl and Send to User
        stAcerSysEvent = SysTypeCGetPortControllerAcerSystemEvent(ucInputPort);

        if(stAcerSysEvent.enumEvent != _TYPE_C_ACER_SYS_EVENT_NONE)
        {
            UserCommonInterfaceTypeCAcerAltModeHandler(ucInputPort, stAcerSysEvent);
        }

        // Check if Acer User Event is NOT Busy
        if(SysTypeCCheckPortControllerAcerUserEventBusy(ucInputPort) == _TYPE_C_ACER_USER_EVENT_NOT_BUSY)
        {
            // Get Acer User Event from User and Send to Port Ctrl
            UserCommonInterfaceTypeCGetAcerUserEvent(ucInputPort, &stAcerUserEvent);
            SysTypeCSetPortControllerAcerUserEvent(ucInputPort, stAcerUserEvent);
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};
    StructTypeCHpUserEvent stHpUserEvent = {_TYPE_C_HP_USER_EVENT_NONE, {0x00}, 0x00};

    if(SysTypeCGetPortControllerHpAltModeReady(ucInputPort) == _TYPE_C_HP_ALT_MODE_READY)
    {
        // Get Hp System Event from Port Ctrl and Send to User
        stHpSysEvent = SysTypeCGetPortControllerHpSystemEvent(ucInputPort);

        if(stHpSysEvent.enumEvent != _TYPE_C_HP_SYS_EVENT_NONE)
        {
            UserCommonInterfaceTypeCHpAltModeHandler(ucInputPort, stHpSysEvent);
        }

        // Check if Hp User Event is NOT Busy
        if(SysTypeCCheckPortControllerHpUserEventBusy(ucInputPort) == _TYPE_C_HP_USER_EVENT_NOT_BUSY)
        {
            // Get Hp User Event from User and Send to Port Ctrl
            UserCommonInterfaceTypeCGetHpUserEvent(ucInputPort, &stHpUserEvent);
            SysTypeCSetPortControllerHpUserEvent(ucInputPort, stHpUserEvent);
        }
    }
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
}

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Reset
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void SysTypeCLenovoAltModeReset(BYTE ucInputPort)
{
    SET_TYPE_C_LENOVO_ALT_MODE_STATUS(ucInputPort, _TYPE_C_LENOVO_ALT_MODE_NOT_READY);
    SET_TYPE_C_LENOVO_DEVICE_TYPE(ucInputPort, _TYPE_C_LENOVO_DEVICE_TYPE_NONE);
    CLR_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(ucInputPort);

#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
    UserCommonPortController5400LenovoAltModeReset(ucInputPort);
#endif
}

//--------------------------------------------------
// Description  : Get Port Controller Lenovo Alt Mode Ready Info
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus SysTypeCGetPortControllerLenovoAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetLenovoAltModeReady(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerGet5400LenovoAltModeReady(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerGetUserLenovoAltModeReady(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetLenovoAltModeReady(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerGet5400LenovoAltModeReady(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerGetUserLenovoAltModeReady(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetLenovoAltModeReady(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerGet5400LenovoAltModeReady(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerGetUserLenovoAltModeReady(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;

            break;
    }

    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type from Port Controller
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType SysTypeCGetPortControllerLenovoDeviceType(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetLenovoDeviceType(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerGet5400LenovoDeviceType(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerGetUserLenovoDeviceType(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetLenovoDeviceType(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerGet5400LenovoDeviceType(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerGetUserLenovoDeviceType(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetLenovoDeviceType(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerGet5400LenovoDeviceType(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerGetUserLenovoDeviceType(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;

            break;
    }

    return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
}

//--------------------------------------------------
// Description  : Active Timer Event Which Set Type C to Receive Lenovo Device Type Timeout
// Input Value  : ucInputPort, Timer Timeout Count
// Output Value : NONE
//--------------------------------------------------
void SysTypeCActiveLenovoRcvDeviceTypeTimerEvent(BYTE ucInputPort, WORD usTimeoutCnt)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D6_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Cancel Timer Event Which Set Type C to Receive Lenovo Device Type Timeout
// Input Value  : ucInputPort --> Inputput
// Output Value : NONE
//--------------------------------------------------
void SysTypeCCancelLenovoRcvDeviceTypeTimerEvent(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D6_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set Type C to Receive Lenovo Device Type Timeout
// Input Value  : ucInputPort --> Inputput
// Output Value : NONE
//--------------------------------------------------
void SysTypeCSetLenovoRcvDeviceTypeTimeout(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            SET_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            SET_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            SET_TYPE_C_LENOVO_RCV_DEVICE_TYPE_TIMEOUT(_D6_INPUT_PORT);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : ucInputPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent SysTypeCGetPortControllerLenovoSystemEvent(BYTE ucInputPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stLenovoSysEvent = ScalerTypeCGetLenovoSystemEvent(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            stLenovoSysEvent = UserCommonPortControllerGet5400LenovoSystemEvent(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            stLenovoSysEvent = UserCommonPortControllerGetUserLenovoSystemEvent(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stLenovoSysEvent = ScalerTypeCGetLenovoSystemEvent(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            stLenovoSysEvent = UserCommonPortControllerGet5400LenovoSystemEvent(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            stLenovoSysEvent = UserCommonPortControllerGetUserLenovoSystemEvent(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stLenovoSysEvent = ScalerTypeCGetLenovoSystemEvent(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            stLenovoSysEvent = UserCommonPortControllerGet5400LenovoSystemEvent(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            stLenovoSysEvent = UserCommonPortControllerGetUserLenovoSystemEvent(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

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
void SysTypeCSetPortControllerLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetLenovoDockingEvent(_D0_INPUT_PORT, stLenovoDockEvent);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            UserCommonPortControllerSet5400LenovoDockingEvent(_D0_INPUT_PORT, stLenovoDockEvent);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            UserCommonPortControllerSetUserLenovoDockingEvent(_D0_INPUT_PORT, stLenovoDockEvent);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetLenovoDockingEvent(_D1_INPUT_PORT, stLenovoDockEvent);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            UserCommonPortControllerSet5400LenovoDockingEvent(_D1_INPUT_PORT, stLenovoDockEvent);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            UserCommonPortControllerSetUserLenovoDockingEvent(_D1_INPUT_PORT, stLenovoDockEvent);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetLenovoDockingEvent(_D6_INPUT_PORT, stLenovoDockEvent);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            UserCommonPortControllerSet5400LenovoDockingEvent(_D6_INPUT_PORT, stLenovoDockEvent);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            UserCommonPortControllerSetUserLenovoDockingEvent(_D6_INPUT_PORT, stLenovoDockEvent);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : ucInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysTypeCCheckPortControllerLenovoDockingEventBusy(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCCheckLenovoDockingEventBusy(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerCheck5400LenovoDockingEventBusy(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerCheckUserLenovoDockingEventBusy(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCCheckLenovoDockingEventBusy(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerCheck5400LenovoDockingEventBusy(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerCheckUserLenovoDockingEventBusy(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCCheckLenovoDockingEventBusy(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            return UserCommonPortControllerCheck5400LenovoDockingEventBusy(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            return UserCommonPortControllerCheckUserLenovoDockingEventBusy(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Return Lenovo Alt Mode Ready Status to User
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus SysTypeCGetLenovoAltModeReady(BYTE ucInputPort)
{
    return GET_TYPE_C_LENOVO_ALT_MODE_STATUS(ucInputPort);
}

//--------------------------------------------------
// Description  : Return Port Partner Lenovo Device Type to User
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType SysTypeCGetLenovoDeviceType(BYTE ucInputPort)
{
    return GET_TYPE_C_LENOVO_DEVICE_TYPE(ucInputPort);
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
//--------------------------------------------------
// Description  : Get Port Controller Acer Alt Mode Ready Info
// Input Value  : ucInputPort --> Inputput
// Output Value : Acer Alt Mode Ready Status (_TYPE_C_ACER_ALT_MODE_READY / _TYPE_C_ACER_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCAcerAltModeStatus SysTypeCGetPortControllerAcerAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAcerAltModeReady(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // return UserCommonPortControllerGet5400AcerAltModeReady(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // return UserCommonPortControllerGetUserAcerAltModeReady(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAcerAltModeReady(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // return UserCommonPortControllerGet5400AcerAltModeReady(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // return UserCommonPortControllerGetUserAcerAltModeReady(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetAcerAltModeReady(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // return UserCommonPortControllerGet5400AcerAltModeReady(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // return UserCommonPortControllerGetUserAcerAltModeReady(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _TYPE_C_ACER_ALT_MODE_NOT_READY;

            break;
    }

    return _TYPE_C_ACER_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCAcerSysEvent
//--------------------------------------------------
StructTypeCAcerSysEvent SysTypeCGetPortControllerAcerSystemEvent(BYTE ucInputPort)
{
    StructTypeCAcerSysEvent stAcerSysEvent = {_TYPE_C_ACER_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stAcerSysEvent = ScalerTypeCGetAcerSystemEvent(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // stAcerSysEvent = UserCommonPortControllerGet5400AcerSystemEvent(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // stAcerSysEvent = UserCommonPortControllerGetUserAcerSystemEvent(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stAcerSysEvent = ScalerTypeCGetAcerSystemEvent(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // stAcerSysEvent = UserCommonPortControllerGet5400AcerSystemEvent(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // stAcerSysEvent = UserCommonPortControllerGetUserAcerSystemEvent(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stAcerSysEvent = ScalerTypeCGetAcerSystemEvent(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // stAcerSysEvent = UserCommonPortControllerGet5400AcerSystemEvent(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // stAcerSysEvent = UserCommonPortControllerGetUserAcerSystemEvent(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

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
void SysTypeCSetPortControllerAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent stAcerUserEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetAcerUserEvent(_D0_INPUT_PORT, stAcerUserEvent);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // UserCommonPortControllerSet5400AcerUserEvent(_D0_INPUT_PORT, stAcerUserEvent);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // UserCommonPortControllerSetUserAcerUserEvent(_D0_INPUT_PORT, stAcerUserEvent);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetAcerUserEvent(_D1_INPUT_PORT, stAcerUserEvent);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // UserCommonPortControllerSet5400AcerUserEvent(_D1_INPUT_PORT, stAcerUserEvent);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // UserCommonPortControllerSetUserAcerUserEvent(_D1_INPUT_PORT, stAcerUserEvent);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetAcerUserEvent(_D6_INPUT_PORT, stAcerUserEvent);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // UserCommonPortControllerSet5400AcerUserEvent(_D6_INPUT_PORT, stAcerUserEvent);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // UserCommonPortControllerSetUserAcerUserEvent(_D6_INPUT_PORT, stAcerUserEvent);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Acer Alt Mode Check if Last User Event has been Sent
// Input Value  : ucInputPort
// Output Value : Acer User Event Busy Status (_TYPE_C_ACER_USER_EVENT_BUSY / _TYPE_C_ACER_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCAcerBusyStatus SysTypeCCheckPortControllerAcerUserEventBusy(BYTE ucInputPort)
{
    EnumTypeCAcerBusyStatus enumCheckBusyResult = _TYPE_C_ACER_USER_EVENT_NOT_BUSY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumCheckBusyResult = ScalerTypeCCheckAcerUserEventBusy(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // enumCheckBusyResult = UserCommonPortControllerCheck5400AcerUserEventBusy(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // enumCheckBusyResult = UserCommonPortControllerCheckUserAcerUserEventBusy(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumCheckBusyResult = ScalerTypeCCheckAcerUserEventBusy(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // enumCheckBusyResult = UserCommonPortControllerCheck5400AcerUserEventBusy(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // enumCheckBusyResult = UserCommonPortControllerCheckUserAcerUserEventBusy(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumCheckBusyResult = ScalerTypeCCheckAcerUserEventBusy(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // enumCheckBusyResult = UserCommonPortControllerCheck5400AcerUserEventBusy(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // enumCheckBusyResult = UserCommonPortControllerCheckUserAcerUserEventBusy(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            enumCheckBusyResult = _TYPE_C_ACER_USER_EVENT_NOT_BUSY;

            break;
    }

    return enumCheckBusyResult;
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
//--------------------------------------------------
// Description  : Get Port Controller Hp Alt Mode Ready Info
// Input Value  : ucInputPort --> Inputput
// Output Value : Hp Alt Mode Ready Status (_TYPE_C_HP_ALT_MODE_READY / _TYPE_C_HP_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCHpAltModeStatus SysTypeCGetPortControllerHpAltModeReady(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetHpAltModeReady(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // return UserCommonPortControllerGet5400HpAltModeReady(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // return UserCommonPortControllerGetUserHpAltModeReady(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetHpAltModeReady(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // return UserCommonPortControllerGet5400HpAltModeReady(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // return UserCommonPortControllerGetUserHpAltModeReady(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            return ScalerTypeCGetHpAltModeReady(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // return UserCommonPortControllerGet5400HpAltModeReady(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // return UserCommonPortControllerGetUserHpAltModeReady(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            return _TYPE_C_HP_ALT_MODE_NOT_READY;

            break;
    }

    return _TYPE_C_HP_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Get System Event
// Input Value  : ucInputPort
// Output Value : StructTypeCHpSysEvent
//--------------------------------------------------
StructTypeCHpSysEvent SysTypeCGetPortControllerHpSystemEvent(BYTE ucInputPort)
{
    StructTypeCHpSysEvent stHpSysEvent = {_TYPE_C_HP_SYS_EVENT_NONE, {0x00}, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stHpSysEvent = ScalerTypeCGetHpSystemEvent(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // stHpSysEvent = UserCommonPortControllerGet5400HpSystemEvent(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // stHpSysEvent = UserCommonPortControllerGetUserHpSystemEvent(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stHpSysEvent = ScalerTypeCGetHpSystemEvent(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // stHpSysEvent = UserCommonPortControllerGet5400HpSystemEvent(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // stHpSysEvent = UserCommonPortControllerGetUserHpSystemEvent(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            stHpSysEvent = ScalerTypeCGetHpSystemEvent(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // stHpSysEvent = UserCommonPortControllerGet5400HpSystemEvent(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // stHpSysEvent = UserCommonPortControllerGetUserHpSystemEvent(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

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
void SysTypeCSetPortControllerHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent stHpUserEvent)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetHpUserEvent(_D0_INPUT_PORT, stHpUserEvent);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // UserCommonPortControllerSet5400HpUserEvent(_D0_INPUT_PORT, stHpUserEvent);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // UserCommonPortControllerSetUserHpUserEvent(_D0_INPUT_PORT, stHpUserEvent);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetHpUserEvent(_D1_INPUT_PORT, stHpUserEvent);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // UserCommonPortControllerSet5400HpUserEvent(_D1_INPUT_PORT, stHpUserEvent);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // UserCommonPortControllerSetUserHpUserEvent(_D1_INPUT_PORT, stHpUserEvent);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            ScalerTypeCSetHpUserEvent(_D6_INPUT_PORT, stHpUserEvent);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // UserCommonPortControllerSet5400HpUserEvent(_D6_INPUT_PORT, stHpUserEvent);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // UserCommonPortControllerSetUserHpUserEvent(_D6_INPUT_PORT, stHpUserEvent);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type C Hp Alt Mode Check if Last User Event has been Sent
// Input Value  : ucInputPort
// Output Value : Hp User Event Busy Status (_TYPE_C_HP_USER_EVENT_BUSY / _TYPE_C_HP_USER_EVENT_NOT_BUSY)
//--------------------------------------------------
EnumTypeCHpBusyStatus SysTypeCCheckPortControllerHpUserEventBusy(BYTE ucInputPort)
{
    EnumTypeCHpBusyStatus enumCheckBusyResult = _TYPE_C_HP_USER_EVENT_NOT_BUSY;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumCheckBusyResult = ScalerTypeCCheckHpUserEventBusy(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // enumCheckBusyResult = UserCommonPortControllerCheck5400HpUserEventBusy(_D0_INPUT_PORT);
#elif(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // enumCheckBusyResult = UserCommonPortControllerCheckUserHpUserEventBusy(_D0_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumCheckBusyResult = ScalerTypeCCheckHpUserEventBusy(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // enumCheckBusyResult = UserCommonPortControllerCheck5400HpUserEventBusy(_D1_INPUT_PORT);
#elif(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // enumCheckBusyResult = UserCommonPortControllerCheckUserHpUserEventBusy(_D1_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
            enumCheckBusyResult = ScalerTypeCCheckHpUserEventBusy(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
            // enumCheckBusyResult = UserCommonPortControllerCheck5400HpUserEventBusy(_D6_INPUT_PORT);
#elif(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)
            // enumCheckBusyResult = UserCommonPortControllerCheckUserHpUserEventBusy(_D6_INPUT_PORT);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

        default:

            enumCheckBusyResult = _TYPE_C_HP_USER_EVENT_NOT_BUSY;

            break;
    }

    return enumCheckBusyResult;
}

//--------------------------------------------------
// Description  : Return Hp Alt Mode Ready Status to User
// Input Value  : ucInputPort --> Inputput
// Output Value : Hp Alt Mode Ready Status (_TYPE_C_HP_ALT_MODE_READY / _TYPE_C_HP_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCHpAltModeStatus SysTypeCGetHpAltModeReady(BYTE ucInputPort)
{
    return SysTypeCGetPortControllerHpAltModeReady(ucInputPort);
}
#endif  // End of #if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#endif // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

#if(((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)))
//--------------------------------------------------
// Description  : Set Type C State to Unattach State
// Input Value  : ucInputPort --> Inputput
// Output Value : NONE
//--------------------------------------------------
void SysTypeCSwitchToUnattachState(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D0_INPUT_PORT:

            SET_TYPE_C_ORIENTATION(_D0_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
            SET_TYPE_C_STATE(_D0_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
            DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
            SysTypeCLenovoAltModeReset(_D0_INPUT_PORT);
#endif

            break;
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D1_INPUT_PORT:

            SET_TYPE_C_ORIENTATION(_D1_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
            SET_TYPE_C_STATE(_D1_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
            DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
            SysTypeCLenovoAltModeReset(_D1_INPUT_PORT);
#endif

            break;
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D6_INPUT_PORT:

            SET_TYPE_C_ORIENTATION(_D6_INPUT_PORT, _TYPE_C_ORIENTATION_NONE);
            SET_TYPE_C_STATE(_D6_INPUT_PORT, _TYPE_C_UNATTACH_STATE);
            DebugMessageSystem("8. [TYPE C] <Step 0/2> CC Unattach", _TYPE_C_RECONNECT_STATE);

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
            SysTypeCLenovoAltModeReset(_D6_INPUT_PORT);
#endif

            break;
#endif

        default:
            break;
    }
}
#endif  // End of #if(((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)) || ((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS)))

//--------------------------------------------------
// Description  : Cancel Timer Event Which Set Type C to Unattach State
// Input Value  : ucInputPort --> Inputput
// Output Value : NONE
//--------------------------------------------------
void SysTypeCCancelUnattachTimerEvent(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D0_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D0_TYPE_C_UNATTACH);

            break;
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D1_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D1_TYPE_C_UNATTACH);

            break;
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_USE_SMBUS))
        case _D6_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D6_TYPE_C_UNATTACH);

            break;
#endif

        default:

            break;
    }
}

#if(_BILLBOARD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Start Billboard ON Timer
// Input Value  : ucInputPort / Timer Timeout Count
// Output Value : None
//--------------------------------------------------
void SysTypeCStartBillboardTimer(BYTE ucInputPort, WORD usTimeoutCnt)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT == _ON))
        case _D0_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D0_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT))

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT == _ON))
        case _D1_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D1_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT))

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT == _ON))
        case _D6_INPUT_PORT:

            ScalerTimerActiveTimerEvent(usTimeoutCnt, _SYSTEM_TIMER_EVENT_D6_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT))

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type-C Cancel Billboard ON Timer
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void SysTypeCCancelBillboardTimer(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT == _ON))
        case _D0_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D0_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_BILLBOARD_SUPPORT == _ON))

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT == _ON))
        case _D1_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D1_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D1_BILLBOARD_SUPPORT == _ON))

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT == _ON))
        case _D6_INPUT_PORT:

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_D6_ENABLE_BILLBOARD);

            break;
#endif  // End of #if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D6_BILLBOARD_SUPPORT == _ON))

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Type-C Billboard Control
// Input Value  : _TYPE_C_BB_DISABLE / _TYPE_C_BB_ENABLE
// Output Value : None
//--------------------------------------------------
void SysTypeCBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D0_INPUT_PORT:
#if(_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER)
            // Turn On Scaler Billboard
            ScalerBBPllPower(enumAtion);
#elif((_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT))
            // Turn On Hub Billboard
            UserCommonUsbHubBillboardControl(_D0_INPUT_PORT, enumAtion);
#endif
            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D1_INPUT_PORT:

#if(_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER)
            // Turn On Scaler Billboard
            ScalerBBPllPower(enumAtion);

#elif((_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT))
            // Turn On Hub Billboard
            UserCommonUsbHubBillboardControl(_D1_INPUT_PORT, enumAtion);
#endif
            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
        case _D6_INPUT_PORT:

#if(_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER)
            // Turn On Scaler Billboard
            ScalerBBPllPower(enumAtion);

#elif((_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT))
            // Turn On Hub Billboard
            UserCommonUsbHubBillboardControl(_D6_INPUT_PORT, enumAtion);
#endif
            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

        default:

            break;
    }
}
#endif // End of #if(_BILLBOARD_SUPPORT == _ON)

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Usb Hub Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCUsbHubProc(BYTE ucInputPort)
{
#if(_USB3_RETIMER_SUPPORT == _ON)
    // Process Hub UFP Switch
    if(SysTypeCheckCapabilityChange(ucInputPort, _TYPE_C_HUB_INPUT_SWITCH_CHG) == _TRUE)
    {
        SysTypeCHubInputSwitchProc(ucInputPort);
        SysTypeCClrCapabilityChangeFlag(ucInputPort, _TYPE_C_HUB_INPUT_SWITCH_CHG);

        DebugMessageSystem("9. [USB HUB] Hub UFP Switch To", ScalerUSB3RetimerGetHubUfpStatus());
    }
#endif

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    // Detect Hub Connected Device Only When : "CC Attached" & "(Alt Mode Not Ready) or (Alt Mode Ready & Pin D)"
    if((UserInterfaceTypeCHubProcSupport(ucInputPort) == _TRUE) && (SysTypeCGetPortControllerCcAttach(ucInputPort) == _TYPE_C_ATTACH))
    {
        SysTypeCUsbHubDetectProc(ucInputPort);
        SysTypeCUsbHubConfigProc(ucInputPort, SysTypeCGetAltModeLaneCnt(GET_TYPE_C_PIN_ASSIGNMENT(ucInputPort)));
    }
#endif
}
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect Usb Hub Info
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void SysTypeCUsbHubDetectProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            SysTypeCD0UsbHubDetectProc();

            break;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            SysTypeCD1UsbHubDetectProc();

            break;
#endif


#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            SysTypeCD6UsbHubDetectProc();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Type-C Dp Lanes
// Input Value  : ucInputPort --> Input Port
//                ucDpLanes   --> Target Dp Lanes
// Output Value : None
//--------------------------------------------------
void SysTypeCUsbHubConfigProc(BYTE ucInputPort, BYTE ucDpLanes)
{
    if(ucDpLanes == _DP_LINK_2_LANE)
    {
        switch(ucInputPort)
        {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                if(GET_D0_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D0_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D0_INPUT_PORT), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                if(GET_D1_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D1_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D1_INPUT_PORT), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D6_INPUT_PORT:

                if(GET_D6_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D6_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D6_INPUT_PORT), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);
                    }
                }

                break;
#endif

            default:
                break;
        }
    }
    else
    {
        switch(ucInputPort)
        {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                if(GET_D0_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D0_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D0_INPUT_PORT), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                if(GET_D1_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D1_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D1_INPUT_PORT), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
            case _D6_INPUT_PORT:

                if(GET_D6_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D6_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SysTypeCGetUsbHubSetU3ReadyDelayTime(_D6_INPUT_PORT), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);
                    }
                }

                break;
#endif
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Set Usb Hub Config U3 Delay Time
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Info
//--------------------------------------------------
WORD SysTypeCGetUsbHubSetU3ReadyDelayTime(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(_D0_INPUT_PORT) == _TRUE)
            {
                return SEC(0);
            }
            else
            {
                return SEC(2);
            }
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(_D1_INPUT_PORT) == _TRUE)
            {
                return SEC(0);
            }
            else
            {
                return SEC(2);
            }
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            if(UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(_D6_INPUT_PORT) == _TRUE)
            {
                return SEC(0);
            }
            else
            {
                return SEC(2);
            }
#endif

        default:
            break;
    }

    return SEC(0);
}

#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCD0UsbHubDetectProc(void)
{
    CLR_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D0_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D0_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if(GET_D0_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE)
            {
                CLR_D0_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D0_INPUT_PORT), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);

                if(UserCommonUsbHubDetectDFPStatus(_D0_INPUT_PORT) == _HUB_DSP_DEVICE_CHANGE)
                {
                    SET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

                    DebugMessageSystem("8. [TYPE C] <HUB> D0 Hub Info Change", GET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG());
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCD1UsbHubDetectProc(void)
{
    CLR_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D1_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D1_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if(GET_D1_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE)
            {
                CLR_D1_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D1_INPUT_PORT), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);

                if(UserCommonUsbHubDetectDFPStatus(_D1_INPUT_PORT) == _HUB_DSP_DEVICE_CHANGE)
                {
                    SET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

                    DebugMessageSystem("8. [TYPE C] <HUB> D1 Hub Info Change", GET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG);
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCD6UsbHubDetectProc(void)
{
    CLR_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D6_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D6_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if(GET_D6_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE)
            {
                CLR_D6_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D6_INPUT_PORT), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);

                if(UserCommonUsbHubDetectDFPStatus(_D6_INPUT_PORT) == _HUB_DSP_DEVICE_CHANGE)
                {
                    SET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

                    DebugMessageSystem("8. [TYPE C] <HUB> D6 Hub Info Change", GET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG);
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : For OSD Handler to do Process According to USB Hub Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTypeCOsdHubProc(void)
{
#if(_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    if(GET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG() == _HUB_DSP_DEVICE_CHANGE)
    {
        UserInterfaceTypeCOsdHubProc(_D0_INPUT_PORT);

        // 1. Get Latest Source Capability from Port Controller
        if(SysTypeCSetPortCtrlSourceCap(_D0_INPUT_PORT) == _TYPE_C_PDO_CHANGE)
        {
            // 2. Set Flag to Request Port Ctrl to Re-Send Source Capability Message
            SysTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_SRC_CAP_CHG);
        }

        CLR_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
    }
#endif

#if(_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    if(GET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG() == _HUB_DSP_DEVICE_CHANGE)
    {
        UserInterfaceTypeCOsdHubProc(_D1_INPUT_PORT);

        CLR_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
    }
#endif

#if(_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
    if(GET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG() == _HUB_DSP_DEVICE_CHANGE)
    {
        UserInterfaceTypeCOsdHubProc(_D6_INPUT_PORT);

        CLR_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
    }
#endif
}

#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Control Retimer/Hub Enable/Disable
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void SysTypeCHubInputSwitchProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
        case _D0_INPUT_PORT:

            ScalerUSB3RetimerHubUfpSwitchProc(ScalerUSB3RetimerGetHubUfpStatus());

            break;
#endif

        default:

            break;
    }
}
#endif // End of #if(_USB3_RETIMER_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

