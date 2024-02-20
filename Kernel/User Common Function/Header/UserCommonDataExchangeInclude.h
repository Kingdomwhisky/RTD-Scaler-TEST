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
// ID Code      : UserCommonDataExchangeInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Finished Check Code
//--------------------------------------------------
#define _DATA_EXCHANGE_FINISHED_CHECK_CODE0                 0x22
#define _DATA_EXCHANGE_FINISHED_CHECK_CODE1                 0xAA

//--------------------------------------------------
// Definitions of Translator Receivr Ready Check Code
//--------------------------------------------------
#define _DATA_EXCHANGE_START_CHECK_CODE0                    0x55
#define _DATA_EXCHANGE_START_CHECK_CODE1                    0x66

//--------------------------------------------------
// Definitions of IIC Tx Max Effective Data Length, Not Include 3 BYTE Header
//--------------------------------------------------
#define _DATA_EXCHAGNE_ADD_HEADER_LEN                       3
#define _DATA_EXCHAGNE_MAX_DATA_LEN                         (_TWO_CHIP_EXCHANGE_RXBUF_LENGTH - _DATA_EXCHAGNE_ADD_HEADER_LEN)

//--------------------------------------------------
// Definitions of IIC Rx Protocol Items
//--------------------------------------------------
#define _DATA_EXCHAGNE_RX_COMMAND_DATA_TYPE                 0
#define _DATA_EXCHAGNE_RX_LENGTH                            1
#define _DATA_EXCHAGNE_RX_COMMAND_TYPE                      2
#define _DATA_EXCHAGNE_RX_START_ADDR                        3

//--------------------------------------------------
// MACRO for Data Exchange Item Event Message
//--------------------------------------------------
#define SET_DATA_EXCHANGE_EVENT_MESSAGE(x)                  {\
                                                                UserCommonDataExchangeSetEvent(x);\
                                                            }

#define GET_DATA_EXCHANGE_EVENT_MESSAGE()                   (UserCommonDataExchangeGetEvent())

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Data Exchange Type
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_NONE = 0x00,
    _DATA_EXCHANGE_DATA_KERNEL,
    _DATA_EXCHANGE_DATA_USER,
    _DATA_EXCHANGE_END,
} EnumDataExchangeTypeGroup;

//--------------------------------------------------
// Enumerations of Data Exchange Item Type
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_ITEM_NONE = 0x00,
    _DATA_EXCHANGE_ITEM_SINGLE,
    _DATA_EXCHANGE_ITEM_MULTI,
} EnumDataExchangeItemType;

//--------------------------------------------------
// Enumerations of Data Exchange Type
//--------------------------------------------------
typedef enum
{
    //--------------------------------------------------
    // Data Exchange Command None
    //--------------------------------------------------
    _DATA_EXCHAGNE_CMD_NONE = 0x00,

    //--------------------------------------------------
    // Data Exchange Notify Updevice Start Transmit
    //--------------------------------------------------
    _DATA_EXCHAGNE_CMD_NOTIFY_UP_DEVICE_INIT_START,

    //--------------------------------------------------
    // Data Exchange Data Transmit Only
    //--------------------------------------------------
    _DATA_EXCHAGNE_CMD_AC_ON_START,
    _DATA_EXCHAGNE_CMD_POWER_STATUS,
    _DATA_EXCHAGNE_CMD_DDC_CI_MODE,
    _DATA_EXCHAGNE_CMD_DCOFF_HPD_MODE,
    _DATA_EXCHAGNE_CMD_AUX_DIFF_MODE,
    _DATA_EXCHAGNE_CMD_AUX_ADJR_MODE,
    _DATA_EXCHAGNE_CMD_DP_IRQ_TIME,
    _DATA_EXCHAGNE_CMD_U3_ON_OFF,
    _DATA_EXCHAGNE_CMD_DP_FREESYNC_STATUS,
    _DATA_EXCHAGNE_CMD_DP_VERSION,
    _DATA_EXCHAGNE_CMD_MST_ON_OFF,
    _DATA_EXCHAGNE_CMD_PIN_ASSIGNMENT_E_SUPPORT_ON_OFF,
    _DATA_EXCHAGNE_CMD_FINISHED_CHECK,
    _DATA_EXCHAGNE_CMD_AC_ON_END,

    //--------------------------------------------------
    // Data Exchange Misc
    //--------------------------------------------------
    _DATA_EXCHAGNE_CMD_ALL_DATA_RESET,
    _DATA_EXCHAGNE_CMD_MULTI_ITEMS,

    //--------------------------------------------------
    // Data Exchange Transmit & Reply
    //--------------------------------------------------
    _DATA_EXCHAGNE_CMD_PAIRING_START,
    _DATA_EXCHAGNE_CMD_PAIRING_LT,
    _DATA_EXCHAGNE_CMD_PAIRING_TYPE_C_FW_VERSION,
    _DATA_EXCHAGNE_CMD_PAIRING_END,

    //--------------------------------------------------
    // Data Exchange User Define
    //--------------------------------------------------
    _DATA_EXCHAGNE_CMD_USER_DEFINE,

    //--------------------------------------------------
    // Include User Command Define Header
    //--------------------------------------------------
    _DATA_EXCHAGNE_USER_CMD_START,
#ifdef _USER_DATA_EXCHANGE_INCLUDE
#include _USER_DATA_EXCHANGE_INCLUDE
#endif
    _DATA_EXCHAGNE_USER_CMD_END,

    //--------------------------------------------------
    // Data Exchange Command End
    //--------------------------------------------------
    _DATA_EXCHAGNE_CMD_END,
} EnumDataExchangeCmdType;

//--------------------------------------------------
// Structure of Exchange Data Item
//--------------------------------------------------
typedef struct
{
    BYTE ucCheckCode0;
    BYTE ucCheckCode1;
} StructDataExchangeInitStartCheck;

typedef struct
{
    BYTE b1PowerStatus : 1;
} StructDataExchangePowerStatus;

typedef struct
{
    BYTE b1DdcciStatus : 1;
} StructDataExchangeDdcciMode;

typedef struct
{
    BYTE b1DPHotPlugDCOffHigh : 1;
} StructDataExchangeDcoffHpdMode;

typedef struct
{
    BYTE b1DPAuxDiffMode : 1;
} StructDataExchangeAuxDiffMode;

typedef struct
{
    BYTE b4DPAuxAdjrSetting : 4;
} StructDataExchangeAuxAdjr;

typedef struct
{
    BYTE ucDpIrqTime_10us;
} StructDataExchangeIrqTime;

//--------------------------------------------------
// Enumerations of Type-C U3 Mode Status
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_U3_ON = 0,
    _DATA_EXCHANGE_U3_OFF = 1,
}EnumDataExchangeU3Type;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
typedef struct
{
    EnumDataExchangeU3Type enumTypeCU3OnOff;
} StructDataExchangeU3Mode;
#endif

//--------------------------------------------------
// Enumerations of FREESYNC Support
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_OFF = 0x00,
    _DATA_EXCHANGE_DP_FREESYNC_SUPPORT_ON,
} EnumDataExchangeFreeSyncSupport;

#if(_DP_FREESYNC_SUPPORT == _ON)
typedef struct
{
    EnumDataExchangeFreeSyncSupport enumFreeSyncOnOff;
} StructDataExchangeDpFreesync;
#endif

//--------------------------------------------------
// Enumerations of Data Exchange DP Version
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_DP_VERSION_1_0 = 0x10,
    _DATA_EXCHANGE_DP_VERSION_1_1 = 0x11,
    _DATA_EXCHANGE_DP_VERSION_1_2 = 0x12,
    _DATA_EXCHANGE_DP_VERSION_1_4 = 0x14,
} EnumDataExchangeDPVerType;

//--------------------------------------------------
// Enumerations of Data Exchange MST On/Off
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_DP_MST_NO_PORT,
    _DATA_EXCHANGE_DP_MST_RX0_PORT,
} EnumDataExchangeDPMSTPort;

typedef struct
{
    EnumDataExchangeDPVerType enumVersion;
    EnumDataExchangeDPMSTPort enumMstPort;
} StructDataExchangeDpVersion;

#if(_DP_MST_SUPPORT == _ON)
typedef struct
{
    EnumDataExchangeDPMSTPort enumMstPort;
} StructDataExchangeDpMstOnOff;
#endif

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment E Support Option
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_PIN_ASSIGNMENT_E_SUPPORT_ON = 0,
    _DATA_EXCHANGE_PIN_ASSIGNMENT_E_SUPPORT_OFF = 1,
}EnumDataExchangePinAssignmentESupportOnOff;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
typedef struct
{
    EnumDataExchangePinAssignmentESupportOnOff enumPinAssignmentESupportOnOff;
} StructDataExchangePinAssignmentESupportOnOff;
#endif
#endif

typedef struct
{
    BYTE ucCheckCode0;
    BYTE ucCheckCode1;
} StructDataExchangeFinished;

typedef struct
{
    StructDataExchangeDdcciMode stDdcciStatus;
    StructDataExchangeDcoffHpdMode stDcoffHpdMode;
    StructDataExchangeAuxDiffMode stAuxDiffMode;
    StructDataExchangeAuxAdjr stAuxAdjr;
    StructDataExchangeIrqTime stIrqTime;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    StructDataExchangeU3Mode stU3Mode;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    StructDataExchangeDpFreesync stDpFreeSync;
#endif

    StructDataExchangeDpVersion stDpVersion;

#if(_DP_MST_SUPPORT == _ON)
    StructDataExchangeDpMstOnOff stMstOnOff;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    StructDataExchangePinAssignmentESupportOnOff stPinAssignmentESupportOnOff;
#endif
#endif
} StructDataExchangeAllDataReset;

typedef struct
{
    StructDataExchangePowerStatus stPowerStatus;
    StructDataExchangeDdcciMode stDdcciStatus;
    StructDataExchangeDcoffHpdMode stDcoffHpdMode;
    StructDataExchangeAuxDiffMode stAuxDiffMode;
    StructDataExchangeAuxAdjr stAuxAdjr;
    StructDataExchangeIrqTime stIrqTime;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    StructDataExchangeU3Mode stU3Mode;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    StructDataExchangeDpFreesync stDpFreeSync;
#endif

    StructDataExchangeDpVersion stDpVersion;

#if(_DP_MST_SUPPORT == _ON)
    StructDataExchangeDpMstOnOff stMstOnOff;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    StructDataExchangePinAssignmentESupportOnOff stPinAssignmentESupportOnOff;
#endif
#endif

} StructDataExchangeMultiOsdItems;

//--------------------------------------------------
// Structure of Exchange Pairing Data Item
//--------------------------------------------------
typedef struct
{
    BYTE ucDpcd_103;
    BYTE ucDpcd_104;
    BYTE ucDpcd_105;
    BYTE ucDpcd_106;
    BYTE ucDpcd_202;
    BYTE ucDpcd_203;
} StructDataExchangePairingLTReply;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
typedef struct
{
    BYTE ucMainVersion;
    BYTE ucSubVersion1;
    BYTE ucSubVersion2;
} StructDataExchangePairingTypeCFwVersionReply;
#endif

//--------------------------------------------------
// Structure of Exchange User Command Item
//--------------------------------------------------
typedef struct
{
    // For User Command, + 2 is used for extra header occupied address
    BYTE pucData[_DATA_EXCHAGNE_MAX_DATA_LEN + 2];
}StructDataExchangeUserDefineCmd;

//--------------------------------------------------
// Unior for All Request Message Info
//--------------------------------------------------
typedef union
{
    StructDataExchangeInitStartCheck stInitStartCheck;
    StructDataExchangePowerStatus stPowerStatus;
    StructDataExchangeDdcciMode stDdcciMode;
    StructDataExchangeDcoffHpdMode stDcoffHpdMode;
    StructDataExchangeAuxDiffMode stAuxDiffMode;
    StructDataExchangeAuxAdjr stAuxAdjr;
    StructDataExchangeIrqTime stIrqTime;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    StructDataExchangeU3Mode stU3Mode;
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
    StructDataExchangeDpFreesync stDpFreeSync;
#endif

    StructDataExchangeDpVersion stDpVersion;

#if(_DP_MST_SUPPORT == _ON)
    StructDataExchangeDpMstOnOff stMstOnOff;
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
    StructDataExchangePinAssignmentESupportOnOff stPinAssignmentESupportOnOff;
#endif
#endif

    StructDataExchangeFinished stFinishedCheck;
    StructDataExchangeAllDataReset stOsdReset;

    // Pairing Data Item
    StructDataExchangePairingLTReply stPairingLTResult;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
    StructDataExchangePairingTypeCFwVersionReply stPairingTypeCFwVersionResult;
#endif

    StructDataExchangeUserDefineCmd stUserDefineCmd;
}UnionDataExchangeDataItem;

//--------------------------------------------------
// Structure of Command Type
//--------------------------------------------------
typedef struct
{
    UnionDataExchangeDataItem unionDataExchangeItem;
    EnumDataExchangeCmdType enumEvent; // Data Change Event
    BYTE ucCommandCount;
}StructDataExchange;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDataExchange g_stD0DataExchange;
extern StructDataExchangeMultiOsdItems g_stMultiOsdItems;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonDataExchangeInit(void);
extern void UserCommonDataExchangeHandler(void);
extern bit UserCommonDataExchangeReadReply(BYTE *pucArray, BYTE ucLength);
extern void UserCommonDataExchangeSetEvent(EnumDataExchangeCmdType enumEvent);
extern EnumDataExchangeCmdType UserCommonDataExchangeGetEvent(void);
extern bit UserCommonDataExchangeSendDataUser(EnumDataExchangeCmdType enumCmdType, BYTE *pucWriteDataArray, BYTE ucLength);
extern bit UserCommonDataExchangeGetDataUser(EnumDataExchangeCmdType enumCmdType, BYTE *pucGetDataArray, BYTE ucLength);
extern bit UserCommonDataExchangeGetDataKernel(EnumDataExchangeCmdType enumCmdType, BYTE *pucGetDataArray, BYTE ucLength);
#endif // End of #if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)

