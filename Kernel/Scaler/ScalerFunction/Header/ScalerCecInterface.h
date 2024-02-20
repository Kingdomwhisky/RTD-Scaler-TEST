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
// ID Code      : ScalerCecInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define GET_CEC_RX_READ_DONE()                 (g_stCecGeneralCtrl.bReadDone)
#define SET_CEC_RX_READ_DONE()                 (g_stCecGeneralCtrl.bReadDone = 1)
#define CLR_CEC_RX_READ_DONE()                 (g_stCecGeneralCtrl.bReadDone = 0)

#define GET_CEC_TX_START()                     (g_stCecGeneralCtrl.bCecTxStart)
#define SET_CEC_TX_START()                     (g_stCecGeneralCtrl.bCecTxStart = 1)
#define CLR_CEC_TX_START()                     (g_stCecGeneralCtrl.bCecTxStart = 0)

#define GET_CEC_RX_MSG_ANALYZING()             (g_stCecGeneralCtrl.bCecRxInfoAnalyzing)
#define SET_CEC_RX_MSG_ANALYZING()             (g_stCecGeneralCtrl.bCecRxInfoAnalyzing = 1)
#define CLR_CEC_RX_MSG_ANALYZING()             (g_stCecGeneralCtrl.bCecRxInfoAnalyzing = 0)

//----------------------------------------------------------------------------
// Macro of CEC Opcode
//----------------------------------------------------------------------------
typedef enum
{
    _CEC_OPCODE_FEATURE_ABORT = 0x00,
    _CEC_OPCODE_POLLING_MESSAGE = 0x01,
    _CEC_OPCODE_IMAGE_VIEW_ON = 0x04,
    _CEC_OPCODE_TUNER_STEP_INCREMENT = 0x05,
    _CEC_OPCODE_TUNER_STEP_DECREMENT = 0x06,
    _CEC_OPCODE_TUNER_DEVICE_STATUS = 0x07,
    _CEC_OPCODE_RECORD_OFF = 0x09,
    _CEC_OPCODE_RECORD_STATUS = 0x0A,
    _CEC_OPCODE_RECORD_ON = 0x0B,
    _CEC_OPCODE_TEXT_VIEW_ON = 0x0D,
    _CEC_OPCODE_GIVE_DECK_STATUS = 0x1A,
    _CEC_OPCODE_DECK_STATUS = 0x1B,
    _CEC_OPCODE_SET_MENU_LANGUAGE = 0x32,
    _CEC_OPCODE_CLEAR_ANALOGUE_TIMER = 0x33,
    _CEC_OPCODE_SET_ANALOGUE_TIMER = 0x34,
    _CEC_OPCODE_TIMER_STATUS = 0x35,
    _CEC_OPCODE_STANDBY = 0x36,
    _CEC_OPCODE_DECK_CONTROL = 0x42,
    _CEC_OPCODE_TIMER_CLEARED_STATUS = 0x43,
    _CEC_OPCODE_USER_CONTROL_PRESSED = 0x44,
    _CEC_OPCODE_USER_CONTROL_RELEASED = 0x45,
    _CEC_OPCODE_GIVE_OSD_NAME = 0x46,
    _CEC_OPCODE_SET_OSD_NAME = 0x47,
    _CEC_OPCODE_SET_OSD_STRING = 0x64,
    _CEC_OPCODE_SET_TIMER_PROGRAM_TITLE = 0x67,
    _CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST = 0x70,
    _CEC_OPCODE_GIVE_AUDIO_STATUS = 0x71,
    _CEC_OPCODE_SET_SYSTEM_AUDIO_MODE = 0x72,
    _CEC_OPCODE_REPORT_AUDIO_STATUS = 0x7A,
    _CEC_OPCODE_GIVE_SYSTEM_AUDIO_MODE_STATUS = 0x7D,
    _CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS = 0x7E,
    _CEC_OPCODE_ROUTING_CHANGE = 0x80,
    _CEC_OPCODE_ROUTING_INFORMATION = 0x81,
    _CEC_OPCODE_ACTIVE_SOURCE = 0x82,
    _CEC_OPCODE_GIVE_PHYSICAL_ADDRESS = 0x83,
    _CEC_OPCODE_REPORT_PHYSICAL_ADDRESS = 0x84,
    _CEC_OPCODE_REQUEST_ACTIVE_SOURCE = 0x85,
    _CEC_OPCODE_SET_STREAM_PATH = 0x86,
    _CEC_OPCODE_DEVICE_VENDOR_ID = 0x87,
    _CEC_OPCODE_VENDOR_COMMAND = 0x89,
    _CEC_OPCODE_VENDOR_REMOTE_BUTTON_DOWN = 0x8A,
    _CEC_OPCODE_VENDOR_REMOTE_BUTTON_UP = 0x8B,
    _CEC_OPCODE_GIVE_DEVICE_VENDOR_ID = 0x8C,
    _CEC_OPCODE_MENU_REQUEST = 0x8D,
    _CEC_OPCODE_MENU_STATUS = 0x8E,
    _CEC_OPCODE_GIVE_DEVICE_POWER_STATUS = 0x8F,
    _CEC_OPCODE_REPORT_POWER_STATUS = 0x90,
    _CEC_OPCODE_GET_MENU_LANGUAGE = 0x91,
    _CEC_OPCODE_SELECT_ANALOGUE_SERVICE = 0x92,
    _CEC_OPCODE_SELECT_DIGITAL_SERVICE = 0x93,
    _CEC_OPCODE_SET_DIGITAL_TIMER = 0x97,
    _CEC_OPCODE_CLEAR_DIGITAL_TIMER = 0x99,
    _CEC_OPCODE_SET_AUDIO_RATE = 0x9A,
    _CEC_OPCODE_INACTIVE_SOURCE = 0x9D,
    _CEC_OPCODE_CEC_VERSION = 0x9E,
    _CEC_OPCODE_GET_CEC_VERSION = 0x9F,
    _CEC_OPCODE_VENDOR_COMMAND_WITH_ID = 0xA0,
    _CEC_OPCODE_CLEAR_EXTERNAL_TIMER = 0xA1,
    _CEC_OPCODE_SET_EXTERNAL_TIMER = 0xA2,
    _CEC_OPCODE_REPORT_SHORT_AUDIO_DESCRIPTOR = 0xA3,
    _CEC_OPCODE_REQUEST_SHORT_AUDIO_DESCRIPTOR = 0xA4,
    _CEC_OPCODE_INITIAL_ARC = 0xC0,
    _CEC_OPCODE_REPORT_ARC_INITIATED = 0xC1,
    _CEC_OPCODE_REPORT_ARC_TERMINATED = 0xC2,
    _CEC_OPCODE_REQUEST_ARC_INITIATION = 0xC3,
    _CEC_OPCODE_REQUEST_ARC_TERMINATION = 0xC4,
    _CEC_OPCODE_TERMINATE_ARC = 0xC5,
    _CEC_OPCODE_NONE = 0xFD,
    _CEC_OPCODE_ABORT_MESSAGE = 0xFF
} EnumCECOpCode;

// Operand                          Enum
// Abort Reason                     -
// Analogue Broadcast Type          -
// Analogue Frequency
// ASCII Digit
// ASCII
// Audio Format ID and Code
// Audio Rate                       -
// Audio Status                     -
// Boolean                          -
// Broadcast System
// CEC Version                      -
// CEC Channel Identifier           -
// Day of Month
// Deck Control Mode                -
// Deck Info                        -
// Device Type                      -
// Digital Service Identification   -
//   Broadcast System               -
// Display Control
// Duration
// External Physical Address
// External Plug
// External Source Specifier        -
// Hour
// Feature Opcode
// Language
// Menu Request Type                -
// Menu State                       -
// Minute
// Month of Year
// New Address
// Original Address
// OSD Name
// OSD String
// Physical Address
// Play Mode                        -
// Power Status                     -
// Program Title String
// Record Source                    -
// Record Status Info               -
// Record Sequence                  -
// Reserved Bit
// Short Audio Descriptor
// Status Request                   -
// Start Time
// System Audio Status              -
// Time
// Timer Cleared Status Data        -
// Timer Status Data
//   Timer Overlap Warning          -
//   Media Info                     -
//   Programmed Indicator           -
//   Programmed Info                -
//   Not Programmed Error Info      -
// Tuner Device Info
//   Recording Flag                 -
//   Tuner Display Info             -
// UI Broadcast Type
// UI Command
// UI Function Media
// UI Function Select A/V Input
// UI Function Select Audio Input
// UI Sound Presentation Control
// Vendor ID
// Vendor Specific Data
// Vendor Specific RC Code


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern volatile StructCecRxReceivedInfo g_stCecRxReceivedInfo;
extern StructCecTxTransmitInfo g_stCecTxTransmitInfo;
extern volatile StructCecGeneralCtrl g_stCecGeneralCtrl;


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerCecInitial(void);
extern void ScalerCecRxProcess(void);
extern void ScalerCecTxProcess(void);
extern void ScalerCecFunctionEnable(bit bEnable);
extern void ScalerCecRxClrIMsgAnalyzingFlag(void);
extern bit ScalerCecRxGetMsgAnalyzingFlag(void);
extern EnumCecTxEvent ScalerCecTxGetTransmitResult(void);
extern EnumCecTxState ScalerCecGetTxState(void);
extern void ScalerCecIntHandler_EXINT0(void);

#endif
