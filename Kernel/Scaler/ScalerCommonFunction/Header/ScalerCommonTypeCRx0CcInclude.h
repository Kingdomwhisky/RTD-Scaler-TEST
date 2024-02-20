/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonTypeCRx0CcInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Type C Related Definition
//--------------------------------------------------

// TYPE C Connection Mode
#define _TYPE_C_HW_MODE                         0x00
#define _TYPE_C_FW_MODE                         0x01

// Definitions of TYPE C Configuration Channel
#define _TYPE_C_CC1                             0x00
#define _TYPE_C_CC2                             0x01

// Definitions of TYPE C Debounce Type
#define _TYPE_C_CC                              0x00
#define _TYPE_C_PD                              0x01

// Definitions of CONNECT / DISCONNECT
#define _TYPE_C_DISCONNECT                      0x00
#define _TYPE_C_CONNECT                         0x01

// Definition of Default OCP Ratio
#define _TYPE_C_DEF_OCP_RATIO                   105 // Unit:%

//--------------------------------------------------
// Type C Related MACRO
//--------------------------------------------------
#define GET_RX0_REG_CC_STATE()                  (ScalerGetByte(P66_33_CC_HW_FSM) & (0x1F))

#define GET_TYPE_C_RX0_ATTACH_STATUS()          (g_stTpcInfo.b3AttachStatus)
#define SET_TYPE_C_RX0_ATTACH_STATUS(x)         (g_stTpcInfo.b3AttachStatus = (x))

#define GET_CC_RX0_CONNECT_EN()                 ((bit)(g_stTpcInfo.b1ConnectEnable))
#define SET_CC_RX0_CONNECT_EN()                 (g_stTpcInfo.b1ConnectEnable = _TRUE)
#define CLR_CC_RX0_CONNECT_EN()                 (g_stTpcInfo.b1ConnectEnable = _FALSE)

#define GET_RX0_CC1_R()                         (g_stTpcInfo.b3CC1Resistor)         // _OPEN / _RA / _RD / _RP_DEF / _RP_1P5A / _RP_3A
#define SET_RX0_CC1_R(x)                        (g_stTpcInfo.b3CC1Resistor = (x))

#define GET_RX0_CC2_R()                         (g_stTpcInfo.b3CC2Resistor)         // _OPEN / _RA / _RD / _RP_DEF / _RP_1P5A / _RP_3A
#define SET_RX0_CC2_R(x)                        (g_stTpcInfo.b3CC2Resistor = (x))

#define GET_CC_RX0_ORIENTATION()                (g_stTpcInfo.enumOrientation)       // _TYPE_C_ORIENTATION_UNFLIP / _TYPE_C_ORIENTATION_FLIP
#define SET_CC_RX0_ORIENTATION(x)               (g_stTpcInfo.enumOrientation = (x))

#define GET_CC_RX0_RA_EXIST()                   ((bit)(g_stTpcInfo.b1RaExist))
#define SET_CC_RX0_RA_EXIST()                   (g_stTpcInfo.b1RaExist = _TRUE)
#define CLR_CC_RX0_RA_EXIST()                   (g_stTpcInfo.b1RaExist = _FALSE)

#define GET_CC_RX0_ATTACHED()                   (g_stTpcInfo.enumCCAttached)
#define SET_CC_RX0_ATTACHED()                   (g_stTpcInfo.enumCCAttached = _TYPE_C_ATTACH)
#define CLR_CC_RX0_ATTACHED()                   (g_stTpcInfo.enumCCAttached = _TYPE_C_UNATTACH)

#define GET_CC_RX0_DEF_CUR()                    ((WORD)(g_stTpcInfo.b10DefCurrent))
#define SET_CC_RX0_DEF_CUR(x)                   (g_stTpcInfo.b10DefCurrent = (x))

#define GET_CC_RX0_DEF_OCP_CUR()                ((WORD)(g_stTpcInfo.usDefOcpCurrent))
#define SET_CC_RX0_DEF_OCP_CUR(x)               (g_stTpcInfo.usDefOcpCurrent = (x))

#define GET_RX0_VCONN_STATUS()                  ((bit)(g_stTpcInfo.b1VconnStatus))
#define SET_RX0_VCONN_STATUS(x)                 (g_stTpcInfo.b1VconnStatus = (x))

#define GET_TYPE_C_ERROR_RECOVERY()             ((bit)(g_stTpcInfo.b1Error))
#define SET_TYPE_C_ERROR_RECOVERY()             (g_stTpcInfo.b1Error = _TRUE)
#define CLR_TYPE_C_ERROR_RECOVERY()             (g_stTpcInfo.b1Error = _FALSE)

#define GET_RX0_SRC_FRSWAP_STATUS()             ((bit)(g_stTpcInfo.b1FRSrcEnable))
#define SET_RX0_SRC_FRSWAP_STATUS(x)            (g_stTpcInfo.b1FRSrcEnable = (x))

#define GET_RX0_SNK_FRSWAP_STATUS()             ((bit)(g_stTpcInfo.b1FRSnkEnable))
#define SET_RX0_SNK_FRSWAP_STATUS(x)            (g_stTpcInfo.b1FRSnkEnable = (x))

#define GET_CC_RX0_UNATTACH_DEBOUNCE()          (g_stTpcInfo.ucUnattachDebounce)
#define ADD_CC_RX0_UNATTACH_DEBOUNCE()          (g_stTpcInfo.ucUnattachDebounce += 1)
#define CLR_CC_RX0_UNATTACH_DEBOUNCE()          (g_stTpcInfo.ucUnattachDebounce = 0)

#define GET_TYPE_C_RX0_DRP_CONNECT_MODE()       ((bit)(g_stTpcInfo.b1DRPConnectMode))
#define SET_TYPE_C_RX0_DRP_CONNECT_MODE()       (g_stTpcInfo.b1DRPConnectMode = _TRUE)
#define CLR_TYPE_C_RX0_DRP_CONNECT_MODE()       (g_stTpcInfo.b1DRPConnectMode = _FALSE)

#define GET_TYPE_C_RX0_AC_ON_RECONNECT()        ((bit)(g_stTpcInfo.b1AcOnReconnect))
#define SET_TYPE_C_RX0_AC_ON_RECONNECT()        (g_stTpcInfo.b1AcOnReconnect = _TRUE)
#define CLR_TYPE_C_RX0_AC_ON_RECONNECT()        (g_stTpcInfo.b1AcOnReconnect = _FALSE)

#define GET_TYPE_C_RX0_AC_ON_DEVICE_DETECT()    (g_stTpcInfo.b1DeviceDetect)
#define SET_TYPE_C_RX0_AC_ON_DEVICE_DETECT(x)   (g_stTpcInfo.b1DeviceDetect = (x))
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumeration Of USB-C
//--------------------------------------------------
typedef enum
{
    _EMB_TPC_INITAIL = 0x00,
    _EMB_TPC_UNATTACH = 0x01,
    _EMB_TPC_CONNECTING = 0x02,
    _EMB_TPC_CONNECTTED = 0x03,
    _EMB_TPC_ATTACHED = 0x04,
}EnumEmbTypeCState;

// Enumeration Of CC Pin Deglitch Unit
typedef enum
{
    _TYPE_C_UNIT_1US = 0x00,
    _TYPE_C_UNIT_10US = 0x01,
    _TYPE_C_UNIT_100US = 0x02,
    _TYPE_C_UNIT_1MS = 0x03,
}EnumDeglitchUnit;

// Enumeration Of CC State Machine
typedef enum
{
    _IDLE = 0x00,
    _UNATTACHED_SNK = 0x01,
    _ATTACHWAIT_SNK = 0x02,
    _ATTACHED_SNK = 0x03,
    _UNATTACHED_SRC = 0x04,
    _ATTACHWAIT_SRC = 0x05,
    _ATTACHED_SRC = 0x06,
    _TRY_SRC = 0x07,
    _TRY_WAIT_SNK = 0x08,
    _TRY_SNK = 0x09,
    _TRY_WAIT_SRC = 0x0A,
    _UNATTACHED_ACCESSORY = 0x0B,
    _ATTACH_WAIT_ACCESSORY = 0x0C,
    _POWER_ACCESSORY = 0x0D,
    _UNSUPORTED_ACCESSORY = 0x0E,
    _DEBUG_ACCESSORY_SNK = 0x0F,
    _AUDIO_ACCESSORY = 0x10,
    _AUDIO_ACCESSORY_SRC = 0x11,
    _DEBUG_ACCESSORY_SRC = 0x12,
}EnumTypeCAttachState;

// Enumeration of CC PIN Detected Resistor
typedef enum
{
    _DET_OPEN = 0x00,
    _DET_RA = 0x01,
    _DET_RD = 0x02,
    _DET_RP_DEF = 0x03,
    _DET_RP_1P5A = 0x04,
    _DET_RP_3P0A = 0x05,
}EnumCCDetResistor;

// Enumeration of CC PIN SNK Set Resistor
typedef enum
{
    _SET_RD = 0x00,
    _SET_RA = 0x01,
}EnumCCSnkSetResistor;

// Enumeration of CC PIN SRC Set Resistor
typedef enum
{
    _SET_RP_DEF = 0x00,
    _SET_RP_1P5A = 0x01,
    _SET_RP_3P0A = 0x02,
}EnumCCSrcSetResistor;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTypeCInfo g_stTpcInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTypeCRx0CcClkSel(BYTE ucClockSel);
extern void ScalerTypeCRx0CcHandler(BYTE ucModeState);
extern void ScalerTypeCRx0CcIntHandler_EXINT0(void);
extern BYTE ScalerTypeCRx0CcIntClrCheck_EXINT0(void);
extern void ScalerTypeCRx0CcTimerEventProc(EnumScalerTimerEventID enumEventID);
extern void ScalerTypeCRx0CcVconnControl(bit bAction);
extern void ScalerTypeCRx0CcVconnControl_EXINT0(bit bAction);
extern void ScalerTypeCRx0CcVconnControl_WDINT(bit bAction);
extern void ScalerTypeCRx0CcVbusDetCtrl(bit bAction);
extern void ScalerTypeCRx0CcVbusDetCtrl_EXINT0(bit bAction);
extern void ScalerTypeCRx0CcVbusDetCtrl_WDINT(bit bAction);
extern BYTE ScalerTypeCRx0CcDetResistor(void);
extern void ScalerTypeCRx0CcSwitchPowerRole(BYTE ucTargetRole);
extern void ScalerTypeCRx0CcSwitchPowerRole_EXINT0(BYTE ucTargetRole);
extern void ScalerTypeCRx0CcPowerSwitch(EnumPowerAction enumPowerAction);

