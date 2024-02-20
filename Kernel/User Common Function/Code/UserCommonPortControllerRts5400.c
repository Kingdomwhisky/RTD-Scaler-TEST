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
// ID Code      : UserCommonPortControllerRts5400.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLER5400__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definition of Type-C 5400 Related Macro
//--------------------------------------------------
#define GET_TYPE_C_5400_DATA_ROLE(x)                        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumDataRole)
#define SET_TYPE_C_5400_DATA_ROLE(x, y)                     (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].enumDataRole = (y))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfSrcCap)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(x, y)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfSrcCap = (y))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(x, y)          (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].enumPdoType)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(x, y, z)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].enumPdoType = (z))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(x, y)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxVoltage)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(x, y, z)    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxVoltage = (z))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(x, y)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMinVoltage)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(x, y, z)    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMinVoltage = (z))

#define GET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(x, y)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxCurrent)
#define SET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(x, y, z)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxCurrent = (z))

#define GET_TYPE_C_5400_PARTNER_SNK_CAP_CNT(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfSnkCap)
#define SET_TYPE_C_5400_PARTNER_SNK_CAP_CNT(x, y)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b3NumOfSnkCap = (y))

#define GET_TYPE_C_5400_PARTNER_SNK_CAP_TYPE(x, y)          (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].enumPdoType)
#define SET_TYPE_C_5400_PARTNER_SNK_CAP_TYPE(x, y, z)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].enumPdoType = (z))

#define GET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MAX(x, y)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxVoltage)
#define SET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MAX(x, y, z)    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxVoltage = (z))

#define GET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MIN(x, y)       (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMinVoltage)
#define SET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MIN(x, y, z)    (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMinVoltage = (z))

#define GET_TYPE_C_5400_PARTNER_SNK_CAP_CUR(x, y)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxCurrent)
#define SET_TYPE_C_5400_PARTNER_SNK_CAP_CUR(x, y, z)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].pstPartnerPdo[y].ucMaxCurrent = (z))

#define GET_TYPE_C_5400_I2C_ENABLED_FLG(x)                  (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1I2CEnabledFlag)
#define SET_TYPE_C_5400_I2C_ENABLED_FLG(x)                  (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1I2CEnabledFlag = _TRUE)
#define CLR_TYPE_C_5400_I2C_ENABLED_FLG(x)                  (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1I2CEnabledFlag = _FALSE)

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#define GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoAltModeFlag)
#define SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoAltModeFlag = _TRUE)
#define CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(x)           (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoAltModeFlag = _FALSE)

#define GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(x)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag)
#define SET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(x)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag = _TRUE)
#define CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(x)        (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1DetectLenovoDeviceTypeFlag = _FALSE)

#define GET_TYPE_C_5400_LENOVO_VDM_RECEIVED(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1LenovoVdmReceived)
#define SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1LenovoVdmReceived = _TRUE)
#define CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(x)              (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].b1LenovoVdmReceived = _FALSE)

#define GET_TYPE_C_5400_LENOVO_DOCK_EVENT(x)                (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucLenovoDockingEvent)
#define SET_TYPE_C_5400_LENOVO_DOCK_EVENT(x, y)             (g_pstTypeC5400Info[SysTypeCGetTypeCIndex(x)].ucLenovoDockingEvent = (y))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumTypeCDataRole enumDataRole;
    StructTypeCUserPDO pstPartnerPdo[7];
    BYTE b3NumOfSrcCap : 3;
    BYTE b3NumOfSnkCap : 3;
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    BYTE b1DetectLenovoAltModeFlag : 1;
    BYTE b1DetectLenovoDeviceTypeFlag : 1;
    BYTE ucLenovoDockingEvent;
    BYTE b1LenovoVdmReceived : 1;
#endif
    BYTE b1I2CEnabledFlag : 1;
}StructPortController5400Info;

//****************************************************************************
// CODE TABLES
//****************************************************************************
// Write Command && Read Command
#if(_TYPE_C_RTS5400_SERIES_SPEC_VER_SEL >= _RTS5400_SERIES_FW_SPEC_VERSION_V0D7)
code StructSMBusWRGetICStatus tSMBusWrCmdGetICStatus[1] = {{0x3A, 0x03, 0x08, 0x00, 0x01}};
code StructSMBusRDGetICStatus tSMBusRdCmdGetICStatus[1] = {{0x80, 0x02, 0x00}};

code StructSMBusWRReadDPLanes tSMBusWrCmdReadDpCapVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0C}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDpCapVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0C}};
code StructSMBusRDReadDPLanesCfg tSMBusRdCmdDPCapVdo[1] = {{0x80, 0x05, 0x45, 0x04, 0x00, 0x00}};

code StructSMBusWRGetStatus tSMBusWrGetStatus[1] = {{0x09, 0x03, 0x00, 0x00, 0x0E}};
code StructSMBusRDGetStatus tSMBusRDGetStatus[1] = {{0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPCfgVdoSelf[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0E}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPCfgVdoPartner[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0E}};
code StructSMBusRDReadDPLanesCfg tSMBusRdCmdReadDPCfgVdo[1] = {{0x80, 0x05, 0x06, 0x04, 0x00, 0x00}};
#else
code StructSMBusWRGetICStatus tSMBusWrCmdGetICStatus[1] = {{0x3A, 0x01, 0x14}};
code StructSMBusRDGetICStatus tSMBusRdCmdGetICStatus[1] = {{0x80, 0x15, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif

code StructSMBusWRSetDPLanes tSMBusWrCmdSetDPCapVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0C, 0x45, 0x00, 0x08, 0x00}};

code StructSMBusWRSetDPLanes tSMBusWrCmdSetDPCfgVdoSelf[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0E, 0x05, 0x04, 0x00, 0x00}};

code StructSMBusWRSetDPMultiFunction tSMBusWrCmdSetDPMultiFunction[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0D, 0x18, 0x00, 0x00, 0x00}};
code StructSMBusWRReadDPMultiFunction tSMBusWrCmdReadDPMultiFunction[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0D}};
code StructSMBusRDReadDPMultiFunction tSMBusRdCmdDPMultiFunction[1] = {{0x80, 0x05, 0x08, 0x00, 0x00, 0x00}};

code StructSMBusWRReconnect tSMBusWrCmdSetReconnect[1] = {{0x08, 0x03, 0x1F, 0x00, 0x01}};

code StructSMBusRDCommandReadyStatus tSMBusRdCmdCommandReadyStatus[1] = {{0x00, 0x00}};

code StructSMBusRDReadDPLanes tSMBusRdCmdDPlanes[1] = {{0x80, 0x05, 0x45, 0x00, 0x08, 0x00}};

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
code StructSMBusWRGetPartnerPdo tSMBusWrCmdGetPartnerSrcPdo[1] = {{0x08, 0x03, 0x83, 0x00, 0xE3}};
code StructSMBusWRGetPartnerPdo tSMBusWrCmdGetPartnerSnkPdo[1] = {{0x08, 0x03, 0x83, 0x00, 0xE2}};
code StructSMBusRDGetPartnerPdo tSMBusRdCmdGetPartnerPdo[1] = {{0x80, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWRGetPdoStatus tSMBusWrCmdGetPdoPartnerStatus[1] = {{0x08, 0x02, 0xA7, 0x00}};
code StructSMBusRDGetPdoStatus tSMBusRdCmdGetPdoPartnerStatus[1] = {{0x80, 0x05, 0x00, 0x00, 0x00, 0x00}};
#endif

code StructSMBusWRGetCableInfo tSMBusWrCmdGetCableInfo[1] = {{0x08, 0x01, 0xA8}};
code StructSMBusRDGetCableInfo tSMBusRdCmdGetCableInfo[1] = {{0x80, 0x05, 0x00, 0x00, 0x00, 0x00}};

code StructSMBusWREnableVenderCommand tSMBusWrCmdEnableVenderCommand[1] = {{0x01, 0x03, 0xDA, 0x0B, 0x01}};

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
code StructSMBusWRGetLenovoInfo tSMBusWrCmdGetLenovoInfo[1] = {{0x08, 0x02, 0xE0, 0x00}};
code StructSMBusRDGetLenovoInfo tSMBusRdCmdGetLenovoInfo[1] = {{0x80, 0x03, 0x00, 0x00}};

code StructSMBusWRGetLenovoVdm tSMBusWrCmdGetLenovoVdm[1] = {{0x08, 0x02, 0x99, 0x00}};
code StructSMBusRDGetLenovoVdm tSMBusRdCmdGetLenovoVdm[1] = {{0x80, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSendLenovoVdmAck tSMBusWrCmdSendLenovoVdmAck[1] = {{0x08, 0x0E, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusWRSendLenovoVdmReq tSMBusWrCmdSendLenovoVdmReq[1] = {{0x08, 0x06, 0x19, 0x00, 0x00, 0x00, 0xEF, 0x17}};
#endif

code StructSMBusWRAckCCCI tSMBusWrCmdAckCCCI[1] = {{0x0A, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructPortController5400Info g_pstTypeC5400Info[_TYPE_C_PORT_VALID];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit UserCommonPortControllerGet5400I2CEnabledFlag(BYTE ucInputPort);
void UserCommonPortControllerSet5400I2CEnabledFlag(BYTE ucInputPort);
void UserCommonPortControllerClr5400I2CEnabledFlag(BYTE ucInputPort);
bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort);

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void);
#endif
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void);
#endif
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void);
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void);
#endif
#endif

bit UserCommonPortControllerGet5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment);
EnumTypeCPowerRole UserCommonPortControllerGet5400PowerRole(BYTE ucInputPort);
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort);
bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo);
bit UserCommonPortControllerWrite5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType);
bit UserCommonPortControllerRead5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType);
EnumTypeCPinCfgType UserCommonPortControllerDecode5400PinAssignment(BYTE ucPdInfo);

bit UserCommonPortController5400Reconnect(BYTE ucInputPort);
bit UserCommonPortControllerConfig5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
bit UserCommonPortControllerConfig5400MultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
BYTE UserCommonPortControllerGet5400PartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
StructTypeCUserPDO UserCommonPortControllerGet5400PartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
bit UserCommonPortControllerGet5400PdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent);
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
void UserCommonPortController5400LenovoAltModeReset(BYTE ucInputPort);
void UserCommonPortControllerSet5400LenovoAltModeDetection(BYTE ucInputPort);
void UserCommonPortControllerSet5400LenovoDeviceTypeDetection(BYTE ucInputPort);
EnumTypeCLenovoAltModeStatus UserCommonPortControllerGet5400LenovoAltModeReady(BYTE ucInputPort);
EnumTypeCLenovoDeviceType UserCommonPortControllerGet5400LenovoDeviceType(BYTE ucInputPort);
StructTypeCLenovoSysEvent UserCommonPortControllerGet5400LenovoSystemEvent(BYTE ucInputPort);
void UserCommonPortControllerSet5400LenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
bit UserCommonPortControllerCheck5400LenovoDockingEventBusy(BYTE ucInputPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get 5400 Port Controller I2C Communication Enabled Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
bit UserCommonPortControllerGet5400I2CEnabledFlag(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            return GET_TYPE_C_5400_I2C_ENABLED_FLG(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            return GET_TYPE_C_5400_I2C_ENABLED_FLG(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            return GET_TYPE_C_5400_I2C_ENABLED_FLG(_D6_INPUT_PORT);

            break;
#endif

        default:

            return _FALSE;

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set 5400 Port Controller I2C Communication Enabled Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400I2CEnabledFlag(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            SET_TYPE_C_5400_I2C_ENABLED_FLG(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            SET_TYPE_C_5400_I2C_ENABLED_FLG(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            SET_TYPE_C_5400_I2C_ENABLED_FLG(_D6_INPUT_PORT);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Clr 5400 Port Controller I2C Communication Enabled Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerClr5400I2CEnabledFlag(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            CLR_TYPE_C_5400_I2C_ENABLED_FLG(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            CLR_TYPE_C_5400_I2C_ENABLED_FLG(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            CLR_TYPE_C_5400_I2C_ENABLED_FLG(_D6_INPUT_PORT);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Enable 5400 Port Controller Vender Command
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerEnable5400VenderCommand(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdEnableVenderCommand[0].ucCommandCode, 1, tSMBusWrCmdEnableVenderCommand[0].ucDataLength + 1, &(tSMBusWrCmdEnableVenderCommand[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D0 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD0CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ATTACH;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D0_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        if(SysTypeCGetCcAttach(_D0_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D0_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D0 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D0 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD0AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D0_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D0_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        if(SysTypeCGetAltModeReady(_D0_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D0_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D0 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif  // End of #if(_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D1 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD1CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Current Lit Up Port is _D1_INPUT_PORT,
    if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TRUE;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D1_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        if(SysTypeCGetCcAttach(_D1_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D1_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D1 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D1 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD1AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D1_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D1_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        if(SysTypeCGetAltModeReady(_D1_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D1_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D1 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif // End of #if(_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
#if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
//--------------------------------------------------
// Description  : Get D6 CC Attached Info
// Input Value  : ucInputPort --> Inputput
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAttachStatus UserCommonPortControllerGetD6CcAttachByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Current Lit Up Port is _D6_INPUT_PORT,
    if((SysSourceGetInputPort() == _D6_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ATTACH;
    }

    // Use I2C to Update CC Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D6_DP_TYPE_C_DETECT_CC_ATTACH() == _FALSE)
    {
        if(SysTypeCGetCcAttach(_D6_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }

    // CLR Type-C Detect CC Attach Flag, Wait At Least 500ms to Read 5400 Info Via IIC
    CLR_D6_DP_TYPE_C_DETECT_CC_ATTACH();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _5400_CC_ATTACH, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ATTACH)
        {
            return _TYPE_C_ATTACH;
        }
        else
        {
            return _TYPE_C_UNATTACH;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D6 CC Attach By IIC Fail", 0);

        return _TYPE_C_UNATTACH;
    }
}

//--------------------------------------------------
// Description  : Get D6 Alt Mode Ready Info Through I2C
// Input Value  : None
// Output Value : CC Attach (_TRUE / _FALSE)
//--------------------------------------------------
EnumTypeCAltModeStatus UserCommonPortControllerGetD6AltModeReadyByI2C(void)
{
    BYTE ucReadInfo = 0x00;

    // Return _TRUE if D0 Port is Currently Lit Up From DP Source
    if((SysSourceGetInputPort() == _D6_INPUT_PORT) && (SysSourceGetSourceType() == _SOURCE_DP))
    {
        return _TYPE_C_ALT_MODE_READY;
    }

    // Use I2C to Update Alt. Mode Status Every 500ms, Otherwise Return Status in Source Handler
    if(GET_D6_DP_TYPE_C_DETECT_ALT_MODE() == _FALSE)
    {
        if(SysTypeCGetAltModeReady(_D6_INPUT_PORT) == _TRUE)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }

    // CLR Type-C Detect Alt Mode Flag, Wait At Least 500ms to Read 5400 PD Info Via IIC
    CLR_D6_DP_TYPE_C_DETECT_ALT_MODE();
    ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPE_C_CABLE_DETECT);

    // Read 5400 Info Via IIC Command
    if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _5400_ALT_MODE_READY, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_ALT_MODE_READY)
        {
            return _TYPE_C_ALT_MODE_READY;
        }
        else
        {
            return _TYPE_C_ALT_MODE_NOT_READY;
        }
    }
    else
    {
        DebugMessageSystem("8. Read 5400 D6 Alt Mode Ready By IIC Fail", 0);

        return _TYPE_C_ALT_MODE_NOT_READY;
    }
}

#endif // End of #if(_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)
#endif // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)


//--------------------------------------------------
// Description  : Return Port Controller Alt Mode Pin Assignment to SysTypeC
// Input Value  : None
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit UserCommonPortControllerGet5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinAssignment)
{
    BYTE ucDataRole = 0x00;
    BYTE ucPinAssignment = _TYPE_C_PIN_ASSIGNMENT_NONE;

    // Get Data Role Info
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _5400_DATA_ROLE, &ucDataRole) == _FAIL)
    {
        return _FAIL;
    }

    // Set Data Role
    DebugMessageSystem("8. Get 5400 Data Role = ", ucDataRole);

    if(ucDataRole == _TYPE_C_DFP_U)
    {
        SET_TYPE_C_5400_DATA_ROLE(ucInputPort, _TYPE_C_DFP_U);
    }
    else
    {
        SET_TYPE_C_5400_DATA_ROLE(ucInputPort, _TYPE_C_UFP_U);
    }

    // Get Pin Assignment
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _5400_PIN_ASSIGNMENT, &ucPinAssignment) == _FAIL)
    {
        return _FAIL;
    }

    *penumPinAssignment = (EnumTypeCPinCfgType)ucPinAssignment;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Return Port Controller Power Role to SysTypeC
// Input Value  : ucInputPort --> Inputput
// Output Value : EnumTypeCPowerRole (_TYPE_C_POWER_SNK / _TYPE_C_POWER_SRC / _TYPE_C_POWER_ROLE_NONE)
//--------------------------------------------------
EnumTypeCPowerRole UserCommonPortControllerGet5400PowerRole(BYTE ucInputPort)
{
    EnumTypeCPowerRole enumTypeCPowerRole = _TYPE_C_POWER_ROLE_NONE;
    BYTE ucReadInfo = 0x00;

    // Get Power Role Info
    if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _5400_POWER_ROLE, &ucReadInfo) == _SUCCESS)
    {
        if(ucReadInfo == _TYPE_C_POWER_SRC)
        {
            enumTypeCPowerRole = _TYPE_C_POWER_SRC;
        }
        else
        {
            enumTypeCPowerRole = _TYPE_C_POWER_SNK;
        }

        DebugMessageSystem("8. Get 5400 Power Role = ", enumTypeCPowerRole);
    }
    else
    {
        DebugMessageSystem("8. Read 5400 Power Role By IIC Fail", ucInputPort);
    }

    return enumTypeCPowerRole;
}

//--------------------------------------------------
// Description  : Get Port Controller Slave Address
// Input Value  : ucInputPort --> Input Port
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        case _D1_INPUT_PORT:
            return _D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        case _D6_INPUT_PORT:
            return _D6_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;

        default:
            break;
    }

    return _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR;
}

//--------------------------------------------------
// Description  : Read 5400/5411 Info by SMBus
// Input Value  : None
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerGet5400InfoByI2C(BYTE ucInputPort, Enum5400InfoType enum5400InfoType, BYTE *pucReadInfo)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Write Command to 5400 According to Different Required Info Type
    if(UserCommonPortControllerWrite5400Command(ucInputPort, ucSlaveAddr, enum5400InfoType) == _FAIL)
    {
        DebugMessageSystem("8. IIC Write Command to 5400 Fail", 0);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        DebugMessageSystem("8. IIC Polling 5400 Fail", 0);

        return _FAIL;
    }

    // Read Info From 5400 According to Different Required Info Type
    if(UserCommonPortControllerRead5400Command(ucInputPort, ucSlaveAddr, enum5400InfoType) == _FAIL)
    {
        DebugMessageSystem("8. IIC Read 5400 Info Fail", 0);

        return _FAIL;
    }

    // Decode Required Info According to Required Info
    switch(enum5400InfoType)
    {
        case _5400_CC_ATTACH:

            if((g_unSMBusRdDataPool.stRdGetICStatus.ucPDTypeCStatus & _BIT3) == _BIT3)
            {
                *pucReadInfo = _TYPE_C_ATTACH;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UNATTACH;
            }

            break;

        case _5400_ALT_MODE_READY:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & 0x07) == 0x06)
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_READY;
            }
            else
            {
                *pucReadInfo = _TYPE_C_ALT_MODE_NOT_READY;
            }

            break;

        case _5400_DATA_ROLE:

            if(((g_unSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT2) || ((g_unSMBusRdDataPool.stRdGetStatus.ucByte10_DFP_UFP & (_BIT2 | _BIT1 | _BIT0)) == _BIT1))
            {
                *pucReadInfo = _TYPE_C_DFP_U;
            }
            else
            {
                *pucReadInfo = _TYPE_C_UFP_U;
            }

            break;

        case _5400_POWER_ROLE:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte4 & (_BIT6)) == _BIT6)
            {
                *pucReadInfo = _TYPE_C_POWER_SRC;
            }
            else
            {
                *pucReadInfo = _TYPE_C_POWER_SNK;
            }

            break;

        case _5400_CONNECT_FUJITSU:

            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & _BIT7) == _BIT7)
            {
                *pucReadInfo = _TRUE;
            }
            else
            {
                *pucReadInfo = _FALSE;
            }

            break;

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        // Required Info Include Lenovo Alt Mode Status and VDM Received Info
        case _5400_LENOVO_ALT_MODE_STATUS:

            // Lenovo Mode Entered or Not
            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte13_AltModeStatus & _BIT7) == _BIT7)
            {
                *pucReadInfo = _TYPE_C_LENOVO_ALT_MODE_READY;
            }
            else
            {
                *pucReadInfo = _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            // VDM Received or Not
            if((g_unSMBusRdDataPool.stRdGetStatus.ucByte3 & _BIT1) == _BIT1)
            {
                *(pucReadInfo + 1) = _TRUE;
            }
            else
            {
                *(pucReadInfo + 1) = _FALSE;
            }

            break;

        case _5400_LENOVO_DEVICE_TYPE:

            *pucReadInfo = g_unSMBusRdDataPool.stRdGetLenovoInfo.ucByte0_DeviceType;

            break;

        case _5400_LENOVO_SYSTEM_EVENT:

            // Only Response to SOP Get Status Request
            if(((g_unSMBusRdDataPool.stRdGetLenovoVdm.ucByte0 & 0x03) == 0x00) && (g_unSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader0 == 0x10) && (g_unSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader2 == 0xEF) && (g_unSMBusRdDataPool.stRdGetLenovoVdm.ucVdmHeader3 == 0x17))
            {
                *pucReadInfo = g_unSMBusRdDataPool.stRdGetLenovoVdm.ucByte6;
                *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetLenovoVdm.ucByte7;
            }
            else
            {
                return _FAIL;
            }

            break;
#endif

        case _5400_PIN_ASSIGNMENT:

            *pucReadInfo = (BYTE)(UserCommonPortControllerDecode5400PinAssignment(g_unSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgPinConfig));

            if(*pucReadInfo == _TYPE_C_PIN_ASSIGNMENT_NONE)
            {
                return _FAIL;
            }

            break;

        case _5400_CABLE_VID:

            // ========================= Example ===========================
            // BYTE ucVidInfo[2] = {0x00, 0x00};
            // UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_CABLE_VID, &ucVidInfo);
            // ucVidInfo[0] = Vid_High / ucVidInfo[1] = Vid_Low
            // =============================================================
            *pucReadInfo = g_unSMBusRdDataPool.stRdGetCableInfo.ucVid_High;
            *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetCableInfo.ucVid_Low;

            break;

        case _5400_CABLE_PID:

            *pucReadInfo = g_unSMBusRdDataPool.stRdGetCableInfo.ucPid_High;
            *(pucReadInfo + 1) = g_unSMBusRdDataPool.stRdGetCableInfo.ucPid_Low;

            break;

        default:

            return _FAIL;

            break;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write SMBus Command to 5400
// Input Value  : ucInputPort, ucSlaveAddr, enum5400InfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerWrite5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType)
{
    bit bResult = _FAIL;

    switch(enum5400InfoType)
    {
        case _5400_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetICStatus[0].ucCommandCode, 1, tSMBusWrCmdGetICStatus[0].ucDataLength + 1, &(tSMBusWrCmdGetICStatus[0].ucDataLength), ucInputPort);

            break;

        case _5400_ALT_MODE_READY:
        case _5400_DATA_ROLE:
        case _5400_POWER_ROLE:
        case _5400_CONNECT_FUJITSU:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrGetStatus[0].ucCommandCode, 1, tSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrGetStatus[0].ucDataLength), ucInputPort);

            break;

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _5400_LENOVO_ALT_MODE_STATUS:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrGetStatus[0].ucCommandCode, 1, tSMBusWrGetStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrGetStatus[0].ucDataLength), ucInputPort);

            break;

        case _5400_LENOVO_DEVICE_TYPE:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetLenovoInfo[0].ucCommandCode, 1, tSMBusWrCmdGetLenovoInfo[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetLenovoInfo[0].ucDataLength), ucInputPort);

            break;

        case _5400_LENOVO_SYSTEM_EVENT:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetLenovoVdm[0].ucCommandCode, 1, tSMBusWrCmdGetLenovoVdm[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetLenovoVdm[0].ucDataLength), ucInputPort);

            break;
#endif

        case _5400_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            if(GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_DFP_U)
            {
                bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdReadDPCfgVdoSelf[0].ucCommandCode, 1, tSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdReadDPCfgVdoSelf[0].ucDataLength), ucInputPort);
            }
            else
            {
                bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdReadDPCfgVdoPartner[0].ucCommandCode, 1, tSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdReadDPCfgVdoPartner[0].ucDataLength), ucInputPort);
            }

            break;

        case _5400_CABLE_VID:
        case _5400_CABLE_PID:

            bResult = UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetCableInfo[0].ucCommandCode, 1, tSMBusWrCmdGetCableInfo[0].ucDataLength + 1, &(tSMBusWrCmdGetCableInfo[0].ucDataLength), ucInputPort);

            break;

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Read Info From 5400
// Input Value  : ucInputPort, ucSlaveAddr, enum5400InfoType
// Output Value : Communication Result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerRead5400Command(BYTE ucInputPort, BYTE ucSlaveAddr, Enum5400InfoType enum5400InfoType)
{
    bit bResult = _FAIL;

    switch(enum5400InfoType)
    {
        case _5400_CC_ATTACH:

            // UserCommonPortControllerGetPCStatus : tSMBusWrCmdGetICStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetICStatus[0].ucCommandCode, 1, tSMBusRdCmdGetICStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetICStatus.ucByte7), ucInputPort);

            g_unSMBusRdDataPool.stRdGetICStatus.ucCommandCode = tSMBusRdCmdGetICStatus[0].ucCommandCode;

            break;

        case _5400_ALT_MODE_READY:
        case _5400_DATA_ROLE:
        case _5400_POWER_ROLE:
        case _5400_CONNECT_FUJITSU:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRDGetStatus[0].ucCommandCode, 1, tSMBusRDGetStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetStatus.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetStatus.ucCommandCode = tSMBusRDGetStatus[0].ucCommandCode;

            break;

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
        case _5400_LENOVO_ALT_MODE_STATUS:

            // UserCommonPortControllerGetStatus : tSMBusWrGetStatus
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRDGetStatus[0].ucCommandCode, 1, tSMBusRDGetStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetStatus.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetStatus.ucCommandCode = tSMBusRDGetStatus[0].ucCommandCode;

            break;

        case _5400_LENOVO_DEVICE_TYPE:

            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetLenovoInfo[0].ucCommandCode, 1, tSMBusRdCmdGetLenovoInfo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetLenovoInfo.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetLenovoInfo.ucCommandCode = tSMBusRdCmdGetLenovoInfo[0].ucCommandCode;

            break;

        case _5400_LENOVO_SYSTEM_EVENT:

            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetLenovoVdm[0].ucCommandCode, 1, tSMBusRdCmdGetLenovoVdm[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetLenovoVdm.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetLenovoVdm.ucCommandCode = tSMBusRdCmdGetLenovoVdm[0].ucCommandCode;

            break;
#endif

        case _5400_PIN_ASSIGNMENT:

            // UserCommonPortControllerGetPCCfgVdoSelf (tSMBusWrCmdReadDPCfgVdoSelf) + UserCommonPortControllerGetCapVdoSrc (tSMBusWrCmdReadDPCfgVdoPartner)
            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdReadDPCfgVdo[0].ucCommandCode, 1, tSMBusRdCmdReadDPCfgVdo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdDPlanesCfg.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdDPlanesCfg.ucCommandCode = tSMBusRdCmdReadDPCfgVdo[0].ucCommandCode;

            break;

        case _5400_CABLE_VID:
        case _5400_CABLE_PID:

            bResult = UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetCableInfo[0].ucCommandCode, 1, tSMBusRdCmdGetCableInfo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetCableInfo.ucDataLength), ucInputPort);

            g_unSMBusRdDataPool.stRdGetCableInfo.ucCommandCode = tSMBusRdCmdGetCableInfo[0].ucCommandCode;

            break;

        default:

            break;
    }

    return bResult;
}

//--------------------------------------------------
// Description  : Decode Pin Assignment According to 5400 PD Info
// Input Value  : ucPdInfo --> Data Role BYTE From PD Info
// Output Value : EnumTypeCPinCfgtType : _TYPE_C_PIN_ASSIGNMENT_C / D / E
//--------------------------------------------------
EnumTypeCPinCfgType UserCommonPortControllerDecode5400PinAssignment(BYTE ucPdInfo)
{
    // Is it possible to Merge DFP/UFP Flow together, and maybe use "Switch case"
    if((ucPdInfo & _BIT5) == _BIT5) // Pin Assignment F 2 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_F;
    }
    else if((ucPdInfo & _BIT4) == _BIT4) // Pin Assignment E (google cable case)
    {
        return _TYPE_C_PIN_ASSIGNMENT_E;
    }
    else if((ucPdInfo & _BIT3) == _BIT3) // Pin Assignment D 2 lane only, Spec require sink report capability include C  mode
    {
        return _TYPE_C_PIN_ASSIGNMENT_D;
    }
    else if((ucPdInfo & _BIT2) == _BIT2) // Pin Assignment C 4 lane only
    {
        return _TYPE_C_PIN_ASSIGNMENT_C;
    }
    else
    {
        DebugMessageSystem("8. Decode 5400 Pin Assignment Info Error", ucPdInfo);
        return _TYPE_C_PIN_ASSIGNMENT_NONE;
    }
}

//--------------------------------------------------
// Description  : Ask User Port Controller to Reconnect
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortController5400Reconnect(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdSetReconnect[0].ucCommandCode, 1, tSMBusWrCmdSetReconnect[0].ucDataLength + 1, &(tSMBusWrCmdSetReconnect[0].ucDataLength), ucInputPort) == _FAIL)
    {
        DebugMessageSystem("ReConnet Fail Wr fail", 1);

        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 500, ucInputPort) == _FAIL)
    {
        DebugMessageSystem("ReConnet Polling Fail ", 1);

        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Config Pin Assignment to 5400 Port Controller
// Input Value  : ucInputPort / ucPinAssignment / ucDataRole
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfig5400PinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment)
{
    StructSMBusWRSetDPLanes stDpLaneConfigPar;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_DFP_U)
    {
        memcpy(&stDpLaneConfigPar, &tSMBusWrCmdSetDPCfgVdoSelf[0], tSMBusWrCmdSetDPCfgVdoSelf[0].ucDataLength + 2);

        stDpLaneConfigPar.ucDPCapVDOByte1 = enumPinAssignment;
    }
    else
    {
        memcpy(&stDpLaneConfigPar, &tSMBusWrCmdSetDPCapVdoSelf[0], tSMBusWrCmdSetDPCapVdoSelf[0].ucDataLength + 2);

        stDpLaneConfigPar.ucDPCapVDOByte2 = enumPinAssignment;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stDpLaneConfigPar.ucCommandCode, 1, stDpLaneConfigPar.ucDataLength + 1, &stDpLaneConfigPar.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Config Multi-Function Bit to 5400 Port Controller
// Input Value  : ucInputPort / Nulti-Function Bit
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfig5400MultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction)
{
    StructSMBusWRSetDPMultiFunction stMultiFunction;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    memcpy(&stMultiFunction, &tSMBusWrCmdSetDPMultiFunction[0], tSMBusWrCmdSetDPMultiFunction[0].ucDataLength + 2);

    // Only UFP Shoud Set Multi Function Preferred Bit
    // BIT[7:5] Reserved, BIT[6] : Exit Mode, BIT[5] USB Config Req, BIT[4] Multi-Function, BIT[3] DP Enable, BIT[2] Power Low, BIT[1:0] Connect Status (b'10 UFP_D Connected)
    if((GET_TYPE_C_5400_DATA_ROLE(ucInputPort) == _TYPE_C_UFP_U) && (enumMultiFunction == _TYPE_C_MULTI_FUNC_PREFER))
    {
        // Set to Multifunction Prefer
        stMultiFunction.ucDPCapVDOByte0 = 0x1A;
    }
    else
    {
        // Set to Multifunction Not Prefer
        stMultiFunction.ucDPCapVDOByte0 = 0x0A;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stMultiFunction.ucCommandCode, 1, stMultiFunction.ucDataLength + 1, &stMultiFunction.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

#if(_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Number of Partner Src/Snk PDOs
// Input Value  : ucInputPort
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Number of PDO Counts (1~7)
//--------------------------------------------------
BYTE UserCommonPortControllerGet5400PartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    BYTE ucPdoCnt = 0;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);
    BYTE pucData[30];
    BYTE ucIndex = 0;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Execute Write Command
        if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetPartnerSrcPdo[0].ucCommandCode, 1, tSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetPartnerSrcPdo[0].ucDataLength), ucInputPort) == _FAIL)
        {
            return ucPdoCnt;
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Execute Write Command
        if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetPartnerSnkPdo[0].ucCommandCode, 1, tSMBusWrCmdGetPartnerSnkPdo[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetPartnerSnkPdo[0].ucDataLength), ucInputPort) == _FAIL)
        {
            return ucPdoCnt;
        }
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return ucPdoCnt;
    }

    // Read Back Device Reply Data
    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetPartnerPdo[0].ucCommandCode, 1, tSMBusRdCmdGetPartnerPdo[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetPartnerPdo.ucDataLength), ucInputPort) == _FAIL)
    {
        return ucPdoCnt;
    }

    // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
    g_unSMBusRdDataPool.stRdGetPartnerPdo.ucCommandCode = tSMBusRdCmdGetPartnerPdo[0].ucCommandCode;

    ucPdoCnt = g_unSMBusRdDataPool.stRdGetPartnerPdo.ucDataLength / 4;

    memcpy(pucData, &g_unSMBusRdDataPool.stRdGetPartnerPdo, g_unSMBusRdDataPool.stRdGetPartnerPdo.ucDataLength + 2);

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        // Set Number Of Capabilities (Number Of Data Objects)
        SET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort, ucPdoCnt);

        for(ucIndex = 0; ucIndex < ucPdoCnt; ucIndex++)
        {
            // Set PDO Type
            SET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucIndex, ((pucData[ucIndex * 4 + 5] & (_BIT7 | _BIT6)) >> 6));

            if(GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucIndex) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
                SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucIndex, (((pucData[ucIndex * 4 + 5] & 0x01) << 7) | ((pucData[ucIndex * 4 + 4] & 0xFE) >> 1)));
                SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(ucInputPort, ucIndex, pucData[ucIndex * 4 + 3]);
                SET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, ucIndex, pucData[ucIndex * 4 + 2] & 0x7F);
            }
            else
            {
                // Set PDO Voltage (Unit 50mV to 100mV) and Current (Unit 10mA  to 50mA)
                SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucIndex, (BYTE)((((pucData[ucIndex * 4 + 4] & 0x0F) << 6) | ((pucData[ucIndex * 4 + 3] & 0xFC) >> 2)) / 2));
                SET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(ucInputPort, ucIndex, GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucIndex));
                SET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, ucIndex, (BYTE)((((pucData[ucIndex * 4 + 3] & 0x03) << 8) | (pucData[ucIndex * 4 + 2])) / 5));
            }
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        // Set Number Of Capabilities (Number Of Data Objects)
        SET_TYPE_C_5400_PARTNER_SNK_CAP_CNT(ucInputPort, ucPdoCnt);

        for(ucIndex = 0; ucIndex < ucPdoCnt; ucIndex++)
        {
            // Set PDO Type
            SET_TYPE_C_5400_PARTNER_SNK_CAP_TYPE(ucInputPort, ucIndex, ((pucData[ucIndex * 4 + 5] & (_BIT7 | _BIT6)) >> 6));

            if(GET_TYPE_C_5400_PARTNER_SNK_CAP_TYPE(ucInputPort, ucIndex) == _PD_3_PROGRAMMABLE_PDO)
            {
                // Set PDO Voltage (Unit 100mV) and Current (Unit 50mA)
                SET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MAX(ucInputPort, ucIndex, (((pucData[ucIndex * 4 + 5] & 0x01) << 7) | ((pucData[ucIndex * 4 + 4] & 0xFE) >> 1)));
                SET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MIN(ucInputPort, ucIndex, pucData[ucIndex * 4 + 3]);
                SET_TYPE_C_5400_PARTNER_SNK_CAP_CUR(ucInputPort, ucIndex, pucData[ucIndex * 4 + 2] & 0x7F);
            }
            else
            {
                // Set PDO Voltage (Unit 50mV to 100mV) and Current (Unit 10mA  to 50mA)
                SET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MAX(ucInputPort, ucIndex, (BYTE)((((pucData[ucIndex * 4 + 4] & 0x0F) << 6) | ((pucData[ucIndex * 4 + 3] & 0xFC) >> 2)) / 2));
                SET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MIN(ucInputPort, ucIndex, GET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MAX(ucInputPort, ucIndex));
                SET_TYPE_C_5400_PARTNER_SNK_CAP_CUR(ucInputPort, ucIndex, (BYTE)((((pucData[ucIndex * 4 + 3] & 0x03) << 8) | (pucData[ucIndex * 4 + 2])) / 5));
            }
        }
    }

    return ucPdoCnt;
}

//--------------------------------------------------
// Description  : Get Partner Source/Sink PDO Info
// Input Value  : ucInputPort, enumPowerRole(_TYPE_C_POWER_SRC/SNK) / ucPdoIndex : 1~7
// Output Value : StructTypeCUserPDO (Voltage Unit = 100mV / Current = 50mA)
//--------------------------------------------------
StructTypeCUserPDO UserCommonPortControllerGet5400PartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex)
{
    StructTypeCUserPDO stTypeCPartnetPdo;

    // Reset Default Value to Fix PDO w/ 0V @ 0A
    stTypeCPartnetPdo.enumPdoType = _PD_FIX_SUPPLY_PDO;
    stTypeCPartnetPdo.ucMaxVoltage = 0;
    stTypeCPartnetPdo.ucMinVoltage = 0;
    stTypeCPartnetPdo.ucMaxCurrent = 0;

    if(enumPowerRole == _TYPE_C_POWER_SRC)
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TYPE_C_5400_PARTNER_SRC_CAP_CNT(ucInputPort)))
        {
            stTypeCPartnetPdo.enumPdoType = GET_TYPE_C_5400_PARTNER_SRC_CAP_TYPE(ucInputPort, ucPdoIndex - 1);

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCPartnetPdo.ucMaxVoltage = GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MAX(ucInputPort, ucPdoIndex - 1);
            stTypeCPartnetPdo.ucMinVoltage = GET_TYPE_C_5400_PARTNER_SRC_CAP_VOL_MIN(ucInputPort, ucPdoIndex - 1);

            // Get Current in Macro (Unit = 50mA)
            stTypeCPartnetPdo.ucMaxCurrent = GET_TYPE_C_5400_PARTNER_SRC_CAP_CUR(ucInputPort, ucPdoIndex - 1);
        }
    }
    else if(enumPowerRole == _TYPE_C_POWER_SNK)
    {
        if((ucPdoIndex >= 1) && (ucPdoIndex <= GET_TYPE_C_5400_PARTNER_SNK_CAP_CNT(ucInputPort)))
        {
            stTypeCPartnetPdo.enumPdoType = GET_TYPE_C_5400_PARTNER_SNK_CAP_TYPE(ucInputPort, ucPdoIndex - 1);

            // Get Voltage in Macro (Unit = 100mV)
            stTypeCPartnetPdo.ucMaxVoltage = GET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MAX(ucInputPort, ucPdoIndex - 1);
            stTypeCPartnetPdo.ucMinVoltage = GET_TYPE_C_5400_PARTNER_SNK_CAP_VOL_MIN(ucInputPort, ucPdoIndex - 1);

            // Get Current in Macro (Unit = 50mA)
            stTypeCPartnetPdo.ucMaxCurrent = GET_TYPE_C_5400_PARTNER_SNK_CAP_CUR(ucInputPort, ucPdoIndex - 1);
        }
    }

    return stTypeCPartnetPdo;
}

//--------------------------------------------------
// Description  : Read 5400 PDO Status
// Input Value  : ucInputPort, Voltage (100mV) / Current (50mA)
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerGet5400PdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetPdoPartnerStatus[0].ucCommandCode, 1, tSMBusWrCmdGetPdoPartnerStatus[0].ucDataLength + 1, ((BYTE *)&tSMBusWrCmdGetPdoPartnerStatus[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Read Back Device Reply Data
    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetPdoPartnerStatus[0].ucCommandCode, 1, tSMBusRdCmdGetPdoPartnerStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetPdoStatus.ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
    g_unSMBusRdDataPool.stRdGetPdoStatus.ucCommandCode = tSMBusRdCmdGetPdoPartnerStatus[0].ucCommandCode;


    // Convert Voltage From 50mV to 100mV
    *pucVoltage = (((g_unSMBusRdDataPool.stRdGetPdoStatus.ucByte1 & 0xFC) >> 2) + ((g_unSMBusRdDataPool.stRdGetPdoStatus.ucByte2 & 0x0F) << 6)) / 2;

    // Convert Curent From 10mA to 50mA
    *pucCurrent = (g_unSMBusRdDataPool.stRdGetPdoStatus.ucByte0 + ((g_unSMBusRdDataPool.stRdGetPdoStatus.ucByte1 & 0x03) << 8)) / 5;

    return _SUCCESS;
}
#endif

#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
//--------------------------------------------------
// Description  : 5400 Port Controller Lenovo Alt Mode Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonPortController5400LenovoAltModeReset(BYTE ucInputPort)
{
    SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(ucInputPort);
    SET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(ucInputPort);
    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(ucInputPort);
    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort, 0x00);
}

//--------------------------------------------------
// Description  : Set 5400 Port Controller Lenovo Alt Mode I2C Detection Flag
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400LenovoAltModeDetection(BYTE ucInputPort)
{
    SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(ucInputPort);
}

//--------------------------------------------------
// Description  : Set 5400 Port Controller Lenovo Device Type I2C Detection Flag
// Input Value  : ucInputPort --> Inputput
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400LenovoDeviceTypeDetection(BYTE ucInputPort)
{
    SET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(ucInputPort);
}

//--------------------------------------------------
// Description  : Get 5400 Port Controller Lenovo Alt Mode Ready Info
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Alt Mode Ready Status (_TYPE_C_LENOVO_ALT_MODE_READY / _TYPE_C_LENOVO_ALT_MODE_NOT_READY)
//--------------------------------------------------
EnumTypeCLenovoAltModeStatus UserCommonPortControllerGet5400LenovoAltModeReady(BYTE ucInputPort)
{
    BYTE pucModeInfo[2] = {0x00, 0x00};

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D0_INPUT_PORT) == _FALSE)
            {
                return SysTypeCGetLenovoAltModeReady(_D0_INPUT_PORT);
            }

            // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
            if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
            {
                // Clr Type-C Detect Lenovo Alt Mode Flag, Wait At Least 50ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D0_INPUT_PORT);
                ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_ALT_MODE_DETECT);
            }

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_LENOVO_ALT_MODE_STATUS, pucModeInfo) == _SUCCESS)
            {
                if(pucModeInfo[0] == _TYPE_C_LENOVO_ALT_MODE_READY)
                {
                    if(pucModeInfo[1] == _TRUE)
                    {
                        SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D0_INPUT_PORT);
                    }
                    else
                    {
                        CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D0_INPUT_PORT);
                    }

                    return _TYPE_C_LENOVO_ALT_MODE_READY;
                }
                else
                {
                    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D0_INPUT_PORT);
                    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(_D0_INPUT_PORT, 0x00);

                    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                DebugMessageSystem("8. Read 5400 D0 Lenovo Alt Mode Ready By IIC Fail", 0);

                return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D1_INPUT_PORT) == _FALSE)
            {
                return SysTypeCGetLenovoAltModeReady(_D1_INPUT_PORT);
            }

            // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
            if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
            {
                // Clr Type-C Detect Lenovo Alt Mode Flag, Wait At Least 50ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D1_INPUT_PORT);
                ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_ALT_MODE_DETECT);
            }

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _5400_LENOVO_ALT_MODE_STATUS, pucModeInfo) == _SUCCESS)
            {
                if(pucModeInfo[0] == _TYPE_C_LENOVO_ALT_MODE_READY)
                {
                    if(pucModeInfo[1] == _TRUE)
                    {
                        SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D1_INPUT_PORT);
                    }
                    else
                    {
                        CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D1_INPUT_PORT);
                    }

                    return _TYPE_C_LENOVO_ALT_MODE_READY;
                }
                else
                {
                    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D1_INPUT_PORT);
                    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(_D1_INPUT_PORT, 0x00);

                    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                DebugMessageSystem("8. Read 5400 D1 Lenovo Alt Mode Ready By IIC Fail", 0);

                return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            // Update Lenovo Alt. Mode Status Every 50ms, Otherwise Return Last Status
            if(GET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D6_INPUT_PORT) == _FALSE)
            {
                return SysTypeCGetLenovoAltModeReady(_D6_INPUT_PORT);
            }

            // If Lenovo Alt Mode Urgent Event Occur, Always Update Lenovo Alt. Mode Status
            if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _FALSE)
            {
                // Clr Type-C Detect Lenovo Alt Mode Flag, Wait At Least 50ms to Read 5400 PD Info Via IIC
                CLR_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(_D6_INPUT_PORT);
                ScalerTimerActiveTimerEvent(50, _SYSTEM_TIMER_EVENT_D6_TYPE_C_LENOVO_ALT_MODE_DETECT);
            }

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _5400_LENOVO_ALT_MODE_STATUS, pucModeInfo) == _SUCCESS)
            {
                if(pucModeInfo[0] == _TYPE_C_LENOVO_ALT_MODE_READY)
                {
                    if(pucModeInfo[1] == _TRUE)
                    {
                        SET_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D6_INPUT_PORT);
                    }
                    else
                    {
                        CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D6_INPUT_PORT);
                    }

                    return _TYPE_C_LENOVO_ALT_MODE_READY;
                }
                else
                {
                    CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(_D6_INPUT_PORT);
                    SET_TYPE_C_5400_LENOVO_DOCK_EVENT(_D6_INPUT_PORT, 0x00);

                    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
                }
            }
            else
            {
                DebugMessageSystem("8. Read 5400 D6 Lenovo Alt Mode Ready By IIC Fail", 0);

                return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

        default:

            return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;

            break;
    }

    return _TYPE_C_LENOVO_ALT_MODE_NOT_READY;
}

//--------------------------------------------------
// Description  : Get Port Partner Lenovo Device Type from 5400 Port Controller
// Input Value  : ucInputPort --> Inputput
// Output Value : Lenovo Device Type
//--------------------------------------------------
EnumTypeCLenovoDeviceType UserCommonPortControllerGet5400LenovoDeviceType(BYTE ucInputPort)
{
    BYTE ucDeviceType = 0x00;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D0_INPUT_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D0_INPUT_PORT) == _FALSE)
            {
                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D0_INPUT_PORT);
            ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D0_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D0_INPUT_PORT, _5400_LENOVO_DEVICE_TYPE, &ucDeviceType) == _SUCCESS)
            {
                return (EnumTypeCLenovoDeviceType)ucDeviceType;
            }
            else
            {
                DebugMessageSystem("8. Read 5400 Lenovo Device Type By IIC Fail", 0);

                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            break;
#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D1_INPUT_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D1_INPUT_PORT) == _FALSE)
            {
                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D1_INPUT_PORT);
            ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D1_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D1_INPUT_PORT, _5400_LENOVO_DEVICE_TYPE, &ucDeviceType) == _SUCCESS)
            {
                return (EnumTypeCLenovoDeviceType)ucDeviceType;
            }
            else
            {
                DebugMessageSystem("8. Read 5400 Lenovo Device Type By IIC Fail", 0);

                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            break;
#endif  // End of #if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)
        case _D6_INPUT_PORT:

            // Detect Port Partner Lenovo Device Type Every 100ms, Otherwise Return _TYPE_C_LENOVO_DEVICE_TYPE_NONE
            if(GET_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D6_INPUT_PORT) == _FALSE)
            {
                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            // Clr Type-C Detect Lenovo Device Type Flag, Wait At Least 100ms to Read 5400 PD Info Via IIC
            CLR_TYPE_C_5400_DETECT_LENOVO_DEVICE_TYPE(_D6_INPUT_PORT);
            ScalerTimerActiveTimerEvent(100, _SYSTEM_TIMER_EVENT_D6_TYPE_C_LENOVO_DEVICE_TYPE_DETECT);

            // Read 5400 Info Via IIC Command
            if(UserCommonPortControllerGet5400InfoByI2C(_D6_INPUT_PORT, _5400_LENOVO_DEVICE_TYPE, &ucDeviceType) == _SUCCESS)
            {
                return (EnumTypeCLenovoDeviceType)ucDeviceType;
            }
            else
            {
                DebugMessageSystem("8. Read 5400 Lenovo Device Type By IIC Fail", 0);

                return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
            }

            break;
#endif  // End of #if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES)

        default:

            return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;

            break;
    }

    return _TYPE_C_LENOVO_DEVICE_TYPE_NONE;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Get System Event (Including System Acknowledge)
// Input Value  : ucInputPort
// Output Value : StructTypeCLenovoSysEvent
//--------------------------------------------------
StructTypeCLenovoSysEvent UserCommonPortControllerGet5400LenovoSystemEvent(BYTE ucInputPort)
{
    StructTypeCLenovoSysEvent stLenovoSysEvent = {_TYPE_C_LENOVO_SYS_DC_MODE, _TYPE_C_LENOVO_SYS_STATE_NONE, _FALSE, 0x00, 0x00};
    StructSMBusWRAckCCCI stAckCCCI;
    StructSMBusWRSendLenovoVdmAck stSendGetStatusAck;
    BYTE pucSystemInfo[2] = {0x00, 0x00};
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(GET_TYPE_C_5400_LENOVO_VDM_RECEIVED(ucInputPort) == _TRUE)
    {
        if(UserCommonPortControllerGet5400InfoByI2C(ucInputPort, _5400_LENOVO_SYSTEM_EVENT, pucSystemInfo) == _SUCCESS)
        {
            if(pucSystemInfo[0] == 0xFF)
            {
                pucSystemInfo[0] = 0x00;
            }

            if(pucSystemInfo[1] == 0xFF)
            {
                pucSystemInfo[1] = 0x00;
            }

            stLenovoSysEvent.b1SystemEvent = (bit)(pucSystemInfo[0] & _BIT0);
            stLenovoSysEvent.enumSystemState = (pucSystemInfo[0] & (_BIT3 | _BIT2 | _BIT1)) >> 1;
            stLenovoSysEvent.enumSystemPowerMode = (pucSystemInfo[0] & _BIT4) >> 4;
            stLenovoSysEvent.b3SystemReserved = (pucSystemInfo[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5;
            stLenovoSysEvent.ucSystemAcknowlegde = pucSystemInfo[1];

            memcpy(&stSendGetStatusAck, &tSMBusWrCmdSendLenovoVdmAck[0], tSMBusWrCmdSendLenovoVdmAck[0].ucDataLength + 2);

            // -------- Data Obj 0 : VDM Header --------
            // [31:16] Lenovo VID = 0x17EF
            // [15] Struct. VDM = 1, [14:13] VDM Ver = 2b'01 , [12:11] Rsv., [10:8] Obj. Pos = b'000, [7:0] VDM CMD = Get Status Acl (0x50)
            stSendGetStatusAck.ucVdmHeader0 = 0x50;
            stSendGetStatusAck.ucVdmHeader1 = 0xA0;
            stSendGetStatusAck.ucVdmHeader2 = 0xEF;
            stSendGetStatusAck.ucVdmHeader3 = 0x17;

            // -------- Data Obj 1 : Get Status Ack VDO1-----
            // [31:24] Docking Event, [23:16] System Acknowledge
            // [15:8] System Event, [7:0] Docking Acknowledge
            stSendGetStatusAck.ucByte4 = pucSystemInfo[0];
            stSendGetStatusAck.ucByte5 = pucSystemInfo[0];
            stSendGetStatusAck.ucByte6 = pucSystemInfo[1] & 0xFE;
            stSendGetStatusAck.ucByte7 = GET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort);

            // -------- Data Obj 2 : Get Status Ack VDO2-----
            // [31:28] FW Ver. = 0, [27:24] Rsv., [23:16] Power Source
            // [15:12] Function Capability, [11:0] Rsv.
            stSendGetStatusAck.ucByte8 = 0x00;
            stSendGetStatusAck.ucByte9 = 0xC0;
            stSendGetStatusAck.ucByte10 = 0x30;
            stSendGetStatusAck.ucByte11 = 0x00;

            // Ask 5400 to Send Get Status Ack
            // Execute Write Command
            if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stSendGetStatusAck.ucCommandCode, 1, stSendGetStatusAck.ucDataLength + 1, &stSendGetStatusAck.ucDataLength, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            // Polling Write Command Operation Status
            if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            SET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort, 0x00);
            CLR_TYPE_C_5400_LENOVO_VDM_RECEIVED(ucInputPort);

            // Cancel Lenovo Alt Mode Urgent Event if System Acknowledge Received
            if((pucSystemInfo[1] & _BIT0) == _BIT0)
            {
                if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _TRUE)
                {
                    CLR_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT();
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_TYPE_C_LENOVO_ALT_MODE_URGENT_EVENT_TIMEOUT);
                }
            }

            memcpy(&stAckCCCI, &tSMBusWrCmdAckCCCI[0], tSMBusWrCmdAckCCCI[0].ucDataLength + 2);

            stAckCCCI.ucByte3 = 0x02;

            // Acknowledge 5400 that VDM Has been Received and Processed
            // Execute Write Command
            if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stAckCCCI.ucCommandCode, 1, stAckCCCI.ucDataLength + 1, &stAckCCCI.ucDataLength, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }

            // Polling Write Command Operation Status
            if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
            {
                return stLenovoSysEvent;
            }
        }
    }

    return stLenovoSysEvent;
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Set Docking Event
// Input Value  : ucInputPort, stLenovoDockEvent
// Output Value : None
//--------------------------------------------------
void UserCommonPortControllerSet5400LenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent)
{
    StructSMBusWRSendLenovoVdmReq stSendAttn;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    if(stLenovoDockEvent.b1DockingEvent == _TRUE)
    {
        SET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort, (((BYTE)stLenovoDockEvent.b4DockingReserved << 4) | (stLenovoDockEvent.enumDockingPowerSwitch << 2) | ((BYTE)stLenovoDockEvent.b1DockingWolRequest << 1) | (BYTE)stLenovoDockEvent.b1DockingEvent));

        memcpy(&stSendAttn, &tSMBusWrCmdSendLenovoVdmReq[0], tSMBusWrCmdSendLenovoVdmReq[0].ucDataLength + 2);

        stSendAttn.ucVdmHeader0 = 0x06;
        stSendAttn.ucVdmHeader1 = 0xA1;

        // Execute Write Command
        if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stSendAttn.ucCommandCode, 1, stSendAttn.ucDataLength + 1, &stSendAttn.ucDataLength, ucInputPort) == _FAIL)
        {
            return;
        }

        // Polling Write Command Operation Status
        if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
        {
            return;
        }

        SET_TYPE_C_5400_DETECT_LENOVO_ALT_MODE(ucInputPort);
        SET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT();
        ScalerTimerActiveTimerEvent(300, _SYSTEM_TIMER_EVENT_TYPE_C_LENOVO_ALT_MODE_URGENT_EVENT_TIMEOUT);
    }
}

//--------------------------------------------------
// Description  : Type C Lenovo Alt Mode Check if Last Docking Event has been Sent
// Input Value  : ucInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit UserCommonPortControllerCheck5400LenovoDockingEventBusy(BYTE ucInputPort)
{
    if(GET_TYPE_C_5400_LENOVO_DOCK_EVENT(ucInputPort) == 0x00)
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}
#endif // End of #if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
#endif // End of #if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

