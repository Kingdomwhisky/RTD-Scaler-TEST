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
// ID Code      : ScalerCommonSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_SYNC__

#include "ScalerCommonFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Macros of HDR Support
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#define SET_HDR10_INFO_DATA(x)                              (g_stHDR10SaticMetadata = (x))
#define CLR_HDR10_INFO_DATA()                               (memset(&g_stHDR10SaticMetadata, 0, sizeof(StructHDR10StaticMetaData)))
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
#define SET_FREESYNC_II_INFO_DATA(x)                        (g_stFreeSyncIIMetadata = (x))
#define CLR_FREESYNC_II_INFO_DATA()                         (memset(&g_stFreeSyncIIMetadata, 0, sizeof(StructFreeSyncIIInfo)))
#endif


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE data pData_EXINT[6];
bit g_bPsWakeupHpd;
WORD g_usInputPixelClk;
WORD g_usTmdsOffLineMeasureClk;

BYTE g_ucDpRx0LTStatus = _DP_LINK_TRAINING_NONE;
BYTE g_ucDpRx1LTStatus = _DP_LINK_TRAINING_NONE;
bit g_bDpRx0NormalLTSetPhyFinish = _FALSE;
bit g_bDpRx1NormalLTSetPhyFinish = _FALSE;

#if(_D0_DP_EXIST == _ON)
bit g_bDpMSTRx0BackupLinkStatusFlg_INT;
BYTE g_pucDpRx0LinkStatusBackup_INT[3];
bit g_bDpRx0HdcpCheckEnable;
#endif

#if(_D1_DP_EXIST == _ON)
bit g_bDpMSTRx1BackupLinkStatusFlg_INT;
BYTE g_pucDpRx1LinkStatusBackup_INT[3];
bit g_bDpRx1HdcpCheckEnable;
#endif

#if(_DP_SUPPORT == _ON)
bit g_bDpMstDCOffHPDToggleHoldFlag;
bit g_bDpDCOffHPDToggleFlag;
StructDpCableStatus g_stDpCableStatus;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)

bit g_bDpDCOffHPDHigh = 0;
BYTE g_ucDigitalSwitch;
BYTE g_ucHDMIHotPlug;

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
StructDpHdmiCompatibleInfo g_stDpHdmiCompatibleInfo;
#endif

#if(_DP_TX_SUPPORT == _ON)
BYTE idata g_pucHdcpAksvBackup[5];
#endif

#if(_DP_SUPPORT == _ON)
StructDPCapSwitchInfo g_stDpCapSwitch;
StructDPMarginLinkInfo g_stDpMarginLink;

StructDpPortHpdAssertType g_stHpdType =
{
#if(_D0_DP_EXIST == _ON)
    _DP_HPD_NONE,
#endif
#if(_D1_DP_EXIST == _ON)
    _DP_HPD_NONE,
#endif
#if(_D2_DP_EXIST == _ON)
    _DP_HPD_NONE,
#endif
};

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
#if(_D0_DP_EXIST == _ON)
bit g_bDpRx0HdcpHandshakeWOCap = _FALSE;
#endif
#if(_D1_DP_EXIST == _ON)
bit g_bDpRx1HdcpHandshakeWOCap = _FALSE;
#endif
#endif

StructDpAuxSetting g_stDpAuxSetting =
{
    _DP_AUX_INITIAL_DIFF_MODE,
    _DP_AUX_INITIAL_ADJR,
};

BYTE g_ucDpIrqTime_10us;
bit g_bDpIllegalIdlePatternCheck = _FALSE;

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
volatile BYTE data g_ucDpRxHpdIrqAssertT2EventDelayXus_Counter;
BYTE data g_ucDpRxHpdIrqAssertT2EventDelay5usI;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
volatile bit g_bDpD0HpdIrqAssertT2Event = _FALSE;
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
volatile bit g_bDpD1HpdIrqAssertT2Event = _FALSE;
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
volatile bit g_bDpD2HpdIrqAssertT2Event = _FALSE;
#endif

#endif
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
StructDPTxStatusInfo g_stDpTxStatus;
StructDpTxColorInfo g_stDpTxColorInfo;
#endif

#if(_FREESYNC_SUPPORT == _ON)

#if(_DP_FREESYNC_SUPPORT == _ON)
StructDPFREESYNCENABLE g_stDpFREESYNCInfo;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
BYTE g_ucHDMIFREESYNCVCPReceive;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
StructHDMIFREESYNCENABLE g_stHDMIFREESYNCInfo;
#endif

WORD g_usFREESYNCVFreq_max;
WORD g_usFREESYNCVFreq_min;
bit g_bFREESYNCSPDInfoReceive;
bit g_bFREESYNCGetIVFInfo;
#endif

bit g_bDigitalColorInfoChangeReset;

#if(((_D0_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF)) || ((_HDMI_SUPPORT == _ON) && (_TMDS_PAGE2_COMBO_EXIST == _ON)))
StructDigitalColorInfo g_stTMDSRx0ColorInfo;
StructDigitalColorInfoChanged g_stTMDSRx0ColorInfoChanged;
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
StructDigitalColorInfo g_stTMDSRx1ColorInfo;
StructDigitalColorInfoChanged g_stTMDSRx1ColorInfoChanged;
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
StructDigitalColorInfo g_stTMDSRx2ColorInfo;
StructDigitalColorInfoChanged g_stTMDSRx2ColorInfoChanged;
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
StructDigitalColorInfo g_stTMDSRx3ColorInfo;
StructDigitalColorInfoChanged g_stTMDSRx3ColorInfoChanged;
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
StructDigitalColorInfo g_stTMDSRx4ColorInfo;
StructDigitalColorInfoChanged g_stTMDSRx4ColorInfoChanged;
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
StructDigitalColorInfo g_stTMDSRx5ColorInfo;
StructDigitalColorInfoChanged g_stTMDSRx5ColorInfoChanged;
#endif

#if(_D0_DP_EXIST == _ON)
StructDigitalColorInfo g_stDpRx0ColorInfo;
StructDigitalColorInfoChanged g_stDpRx0ColorInfoChanged;
#endif

#if(_D1_DP_EXIST == _ON)
StructDigitalColorInfo g_stDpRx1ColorInfo;
StructDigitalColorInfoChanged g_stDpRx1ColorInfoChanged;
#endif
#endif

#if(_HDR10_SUPPORT == _ON)
StructHDR10StaticMetaData g_stHDR10SaticMetadata;
StructHDR10Setting g_stHDR10Setting;
StructHDR10PortSettingInfo g_stHDR10PortSettingInfo;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
StructFreeSyncIIInfo g_stFreeSyncIIMetadata;
StructFreeSyncIIInfo g_stFreeSyncIISetting;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
WORD g_usDDCDebounceCnt;

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
StructTmdsZ0ToggleFlag g_stTmdsToggleZ0Flag;
#endif

#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
BYTE g_ucCheckUrgentEventOccured;
#endif

#if(_HDMI_SUPPORT == _ON)
BYTE g_pucTMDSRxAviInfo[6];
StructHdmiRxPsWakeupHpd g_stHdmiPsWakeupHPD;
#endif

#if(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
BYTE xdata g_ucFlashISPProPort                                       _at_ 0xE000;
#endif
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
bit g_bAIOModernStandbyMode = _FALSE;
#endif


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
bit ScalerSyncGetFREESYNCEnable(void);

#if((_DEBUG_MESSAGE_SUPPORT == _OFF) && (_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
BYTE ScalerSyncGetHDMIFREESYNCVcp_EXINT1(void);
void ScalerSyncSetHDMIFREESYNCVcp_EXINT1(BYTE ucVcpCode);
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
void ScalerSyncGetColorInfoFrame(EnumSourceSearchPort enumSourceSearchPort, EnumDPGetRSV0InfoStatus enumDPGetRSV0InfoStatus);

#if(_HDR10_SUPPORT == _ON)
bit ScalerSyncHDR10CheckPortStatus(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerSyncHDR10GetCurrentStatus(StructHDR10StaticMetaData *pstHDRSaticMetadata, EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
void ScalerSyncDPInfoFrameRSV0Check(EnumSourceSearchPort enumSourceSearchPort, EnumDPGetRSV0InfoStatus enumDPGetRSV0InfoStatus);
void ScalerSyncDpSecDataResetProc(BYTE ucInputPort);
void ScalerSyncDpHDRReset(void);
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
bit ScalerSyncFreeSyncIICheckPortStatus(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerSyncFreeSyncIIGetCurrentStatus(StructFreeSyncIIInfo *pstFreeSyncIIMetadata, EnumSourceSearchPort enumSourceSearchPort);
#endif
#endif

#if(_DP_SUPPORT == _ON)
bit ScalerSyncDpCheckUrgentHotPlugEventExist(void);
void ScalerSyncDpCapabilitySwitchProc(void);
bit ScalerSyncDpVersionChange(EnumSourceSearchPort enumSourceSearchPort, EnumDpVersionType enumDpVersion);

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
void ScalerSyncDpMarginLinkCapabilitySwitchProc(void);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
bit ScalerSyncDpFreesyncCapabilitySwitchProc(BYTE ucInputPort);
#endif

void ScalerSyncDpFakeLTProtect(void);
bit ScalerSyncDpCableStatus(EnumSourceSearchPort enumInputPort);
void ScalerSyncDpSetCableStatus(EnumSourceSearchPort enumInputPort, bit bStatus);
void ScalerSyncDpCheckHdcpEnable(void);

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
void ScalerSyncDpHpdIrqAssertTimer2EventProc_EXINT(void);
void ScalerSyncDpAuxManualModeSetting_EXINT(EnumDpAuxManualModeSetting enumSetting);
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
void ScalerSyncDpRepeaterPowerOffReset(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerSyncDpRxSinkCountUpdateProc(EnumSourceSearchPort enumInputPort);
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction);
bit ScalerSyncDpTxCloneOutputPortCheck(BYTE ucInputPort);
void ScalerSyncDpTxHdcpUpstreamSwitchProc(BYTE ucInputPort);
EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void);
bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void);

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
bit ScalerSyncDpHdcpDownstreamReAuthCheck(void);
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
EnumDpRxHdcp2UpstreamAuthStatus ScalerSyncDpHdcp2GetUpstreamEvent(void);
bit ScalerSyncDpHdcp2GetContentStreamManagementStatus(void);
bit ScalerSyncDpGetHdcp2ModeStatus(void);
void ScalerSyncDpHdcpRepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_DP_MST_SUPPORT == _ON)
bit ScalerSyncDpFakePowerSavingCheck(void);
bit ScalerSyncDpFakePowerOffCheck(EnumSourceSearchPort enumInputPort);
void ScalerSyncDpSourceWritePowerUpProc(void);
void ScalerSyncDpRxClrSourceWritePowerUp(EnumSourceSearchPort enumInputPort);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable);
void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray);
#endif

EnumHDCPType ScalerSyncHdcpCheckEnabled(BYTE ucInputPort);
void ScalerSyncGDIPowerProc(EnumPowerAction enumPowerAction);
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
bit ScalerSyncCheckUrgentEvent(void);
bit ScalerSyncGetUrgentEventFlg(void);
void ScalerSyncClrUrgentEventFlg(void);
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
void ScalerSyncDdcDetectDebounce_EXINT1(void);
BYTE ScalerSyncDdcDetect_EXINT1(void);
void ScalerSyncTMDSScanInitial(BYTE ucInputPort);
#if(_HDMI_SUPPORT == _ON)
void ScalerSyncTMDSEdidSwitch(BYTE ucPortSelect);
bit ScalerSyncHDMIDdcCheckBusy(BYTE ucInputPort, EnumTMDSDdcDebounceType enumTmdsDdcDebounceType, BYTE ucDebounceTimeScale, WORD usDebounceTimePeriod);
#endif
void ScalerSyncTMDSHPDToggleProc(void);
#endif

#if(_MHL_SUPPORT == _ON)
bit ScalerSyncMHLVBusPowerExist(void);
#endif

void ScalerSyncActiveProc(BYTE ucSourceType);
void ScalerSyncResetProc(BYTE ucInputPort);
void ScalerSyncPowerProc(EnumPowerAction enumPowerAction);
void ScalerSyncInterfaceSwitch(BYTE ucInputPort, BYTE ucPortType, BYTE ucSourceSearchDelayMode);
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
void ScalerSyncBgInterfaceSwitch(BYTE ucInputPort, BYTE ucInputPortType, BYTE ucDetectPort, BYTE ucDetectPortType, BYTE ucSourceSearchDelayMode);
#endif
void ScalerSyncSetDdcForceNack(BYTE ucInputPort, bit bSelect);
bit ScalerSyncGetDdcForceNackStatus(BYTE ucInputPort);

#if(((_D0_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF)) || ((_HDMI_SUPPORT == _ON) && (_TMDS_PAGE2_COMBO_EXIST == _ON)))
void ScalerSyncTMDSRx0HdmiVideoSetting(void);
void ScalerSyncTMDSRx0HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx0HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx0HdmiQuantizationSetting(void);
#endif

bit ScalerSyncTMDSRx0HdmiColorInfoChanged(void);
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
void ScalerSyncTMDSRx1HdmiVideoSetting(void);
void ScalerSyncTMDSRx1HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx1HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx1HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx1HdmiColorInfoChanged(void);
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
void ScalerSyncTMDSRx2HdmiVideoSetting(void);
#endif

void ScalerSyncTMDSRx2HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx2HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx2HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx2HdmiColorInfoChanged(void);
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
void ScalerSyncTMDSRx3HdmiVideoSetting(void);
#endif

void ScalerSyncTMDSRx3HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx3HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx3HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx3HdmiColorInfoChanged(void);
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
void ScalerSyncTMDSRx4HdmiVideoSetting(void);
#endif

void ScalerSyncTMDSRx4HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx4HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx4HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx4HdmiColorInfoChanged(void);
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
void ScalerSyncTMDSRx5HdmiVideoSetting(void);
void ScalerSyncTMDSRx5HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx5HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx5HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx5HdmiColorInfoChanged(void);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
bit ScalerSyncDigitalGetColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerSyncDigitalGetColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerSyncDigitalGetQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
void ScalerSyncDigitalClrColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
void ScalerSyncDigitalClrColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
void ScalerSyncDigitalClrQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)
bit ScalerSyncVGAUseEmbeddedEDID(void);
void ScalerSyncVGADdcCheckBusyAndForceNack(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get FREESYNC Mode Enabled
// Input Value  : None
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
bit ScalerSyncGetFREESYNCEnable(void)
{
    return GET_FREESYNC_ENABLED();
}

#if((_DEBUG_MESSAGE_SUPPORT == _OFF) && (_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get HDMI FREESYNC VCP
// Input Value  : None
// Output Value : HDMI FREESYNC VCP
//                False --> Disabled
//--------------------------------------------------
BYTE ScalerSyncGetHDMIFREESYNCVcp_EXINT1(void) using 2
{
    return GET_HDMI_FREESYNC_VCP();
}

//--------------------------------------------------
// Description  : Set HDMI FREESYNC VCP
// Input Value  : HDMI FREESYNC VCP
// Output Value : None
//--------------------------------------------------
void ScalerSyncSetHDMIFREESYNCVcp_EXINT1(BYTE ucVcpCode) using 2
{
    g_ucHDMIFREESYNCVCPReceive = ucVcpCode;
}
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDR Infoframe RSV0 Check
// Input Value  : Input source port
// Output Value : None
//--------------------------------------------------
void ScalerSyncGetColorInfoFrame(EnumSourceSearchPort enumSourceSearchPort, EnumDPGetRSV0InfoStatus enumDPGetRSV0InfoStatus)
{
#if(_HDR10_SUPPORT == _ON)
    StructHDR10StaticMetaData stHDR10InfoData;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    StructFreeSyncIIInfo stFreeSyncIIData;
#endif

#if(_HDR10_SUPPORT == _ON)
    memset(&stHDR10InfoData, 0, sizeof(stHDR10InfoData));
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    memset(&stFreeSyncIIData, 0, sizeof(stFreeSyncIIData));
#endif

    enumDPGetRSV0InfoStatus = enumDPGetRSV0InfoStatus;

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    ScalerSyncDPInfoFrameRSV0Check(enumSourceSearchPort, enumDPGetRSV0InfoStatus);
#endif

#if(_HDR10_SUPPORT == _ON)
    // Get current HDR status
    ScalerSyncHDR10GetCurrentStatus(&stHDR10InfoData, enumSourceSearchPort);

    SET_HDR10_INFO_DATA(stHDR10InfoData);
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    // Get current FreeSync II status
    ScalerSyncFreeSyncIIGetCurrentStatus(&stFreeSyncIIData, enumSourceSearchPort);

    SET_FREESYNC_II_INFO_DATA(stFreeSyncIIData);
#endif
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current HDR data enable status
// Input Value  : enumSourceSearchPort --> Input port
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSyncHDR10CheckPortStatus(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
#if(_D0_HDMI_SUPPORT == _ON)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            if(_DP_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D1_INPUT_PORT:
#if(_D1_HDMI_SUPPORT == _ON)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            if(_DP_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_HDMI_SUPPORT == _ON)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(_DP_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_HDMI_SUPPORT == _ON)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_HDMI_SUPPORT == _ON)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_HDMI_SUPPORT == _ON)
            if(_HDMI_HDR10_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        default:
            return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Current HDR data
// Input Value  : stHDRSaticMetadata --> HDR data
//                enumSourceSearchPort --> Input port
// Output Value : _FALSE: no receive
//--------------------------------------------------
bit ScalerSyncHDR10GetCurrentStatus(StructHDR10StaticMetaData *pstHDRSaticMetadata, EnumSourceSearchPort enumSourceSearchPort)
{
    if(ScalerSyncHDR10CheckPortStatus(enumSourceSearchPort) == _TRUE)
    {
        bit bHDRInfoReceive = 0;
        BYTE pucHDRInfoData[_HW_DP_INFOFRAME_RSV0_LENGTH];

        memset(pucHDRInfoData, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);

        switch(enumSourceSearchPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_DP_HDR10_SUPPORT == _ON)
            case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            case _D6_INPUT_PORT:
#endif

                bHDRInfoReceive = GET_DP_RX0_HDR_INFO_FRAME_RECEIVED();
                memcpy(pucHDRInfoData, g_pucDPRx0HDR10Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
                break;
#endif // End of #if(_DP_HDR10_SUPPORT == _ON)

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_DP_HDR10_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                bHDRInfoReceive = GET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                memcpy(pucHDRInfoData, g_pucDPRx1HDR10Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
                break;

#endif // End of #if(_DP_HDR10_SUPPORT == _ON)

#elif(_D1_HDMI_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
            case _D1_INPUT_PORT:

#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
                bHDRInfoReceive = GET_HDMI_RX0_HDR10_INFO_FRAME_RECEIVED();
#else
                bHDRInfoReceive = GET_HDMI_RX1_HDR10_INFO_FRAME_RECEIVED();
#endif

                GET_TMDSRX1_HDR10_DATA(pucHDRInfoData);

                break;
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#endif


#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if(_DP_HDR10_SUPPORT == _ON)
            case _D2_INPUT_PORT:

                // RL6492: _DIGITAL_PORT_COMBO_PHY_D1_D2
                bHDRInfoReceive = GET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
                memcpy(pucHDRInfoData, g_pucDPRx1HDR10Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
                break;
#endif // End of #if(_DP_HDR10_SUPPORT == _ON)

#elif(_D2_HDMI_SUPPORT == _ON)

#if(_HDMI_HDR10_SUPPORT == _ON)
            case _D2_INPUT_PORT:

#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
                bHDRInfoReceive = GET_HDMI_RX0_HDR10_INFO_FRAME_RECEIVED();
#else
                bHDRInfoReceive = GET_HDMI_RX2_HDR10_INFO_FRAME_RECEIVED();
#endif

                GET_TMDSRX2_HDR10_DATA(pucHDRInfoData);

                break;
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)

#endif

#if(_D3_HDMI_SUPPORT == _ON)
#if(_HDMI_HDR10_SUPPORT == _ON)
            case _D3_INPUT_PORT:

                bHDRInfoReceive = GET_HDMI_RX3_HDR10_INFO_FRAME_RECEIVED();

                GET_TMDSRX3_HDR10_DATA(pucHDRInfoData);

                break;
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)
#endif

#if(_D4_HDMI_SUPPORT == _ON)
#if(_HDMI_HDR10_SUPPORT == _ON)
            case _D4_INPUT_PORT:

                bHDRInfoReceive = GET_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED();

                GET_TMDSRX4_HDR10_DATA(pucHDRInfoData);

                break;
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)
#endif

#if(_D5_HDMI_SUPPORT == _ON)
#if(_HDMI_HDR10_SUPPORT == _ON)
            case _D5_INPUT_PORT:

                bHDRInfoReceive = GET_HDMI_RX5_HDR10_INFO_FRAME_RECEIVED();

                GET_TMDSRX5_HDR10_DATA(pucHDRInfoData);

                break;
#endif // End of #if(_HDMI_HDR10_SUPPORT == _ON)
#endif

            default:
                break;
        }

        // Check HDR Version/ Length & InfoFrame receive bit
        if((pucHDRInfoData[0] == 0x01) && (pucHDRInfoData[1] == 0x1A) && (bHDRInfoReceive == _TRUE))
        {
            pstHDRSaticMetadata->ucEOTF = pucHDRInfoData[2];
            pstHDRSaticMetadata->ucStaticMetadataID = pucHDRInfoData[3];

            pstHDRSaticMetadata->usDisplayPrimariesX0 = ((WORD)(pucHDRInfoData[5] << 8) | (pucHDRInfoData[4]));
            pstHDRSaticMetadata->usDisplayPrimariesY0 = ((WORD)(pucHDRInfoData[7] << 8) | (pucHDRInfoData[6]));

            pstHDRSaticMetadata->usDisplayPrimariesX1 = ((WORD)(pucHDRInfoData[9] << 8) | (pucHDRInfoData[8]));
            pstHDRSaticMetadata->usDisplayPrimariesY1 = ((WORD)(pucHDRInfoData[11] << 8) | (pucHDRInfoData[10]));

            pstHDRSaticMetadata->usDisplayPrimariesX2 = ((WORD)(pucHDRInfoData[13] << 8) | (pucHDRInfoData[12]));
            pstHDRSaticMetadata->usDisplayPrimariesY2 = ((WORD)(pucHDRInfoData[15] << 8) | (pucHDRInfoData[14]));

            pstHDRSaticMetadata->usWhitePointX = ((WORD)(pucHDRInfoData[17] << 8) | (pucHDRInfoData[16]));
            pstHDRSaticMetadata->usWhitePointY = ((WORD)(pucHDRInfoData[19] << 8) | (pucHDRInfoData[18]));

            pstHDRSaticMetadata->usMaxDisplayMasteringLv = ((WORD)(pucHDRInfoData[21] << 8) | (pucHDRInfoData[20]));
            pstHDRSaticMetadata->usMinDisplayMasteringLv = ((WORD)(pucHDRInfoData[23] << 8) | (pucHDRInfoData[22]));

            pstHDRSaticMetadata->usMaxCLL = ((WORD)(pucHDRInfoData[25] << 8) | (pucHDRInfoData[24]));
            pstHDRSaticMetadata->usMaxFALL = ((WORD)(pucHDRInfoData[27] << 8) | (pucHDRInfoData[26]));

            return _TRUE;
        }
    }

    pstHDRSaticMetadata->ucEOTF = 0x00;
    pstHDRSaticMetadata->ucStaticMetadataID = 0x00;

    pstHDRSaticMetadata->usDisplayPrimariesX0 = 0x0000;
    pstHDRSaticMetadata->usDisplayPrimariesY0 = 0x0000;

    pstHDRSaticMetadata->usDisplayPrimariesX1 = 0x0000;
    pstHDRSaticMetadata->usDisplayPrimariesY1 = 0x0000;

    pstHDRSaticMetadata->usDisplayPrimariesX2 = 0x0000;
    pstHDRSaticMetadata->usDisplayPrimariesY2 = 0x0000;

    pstHDRSaticMetadata->usWhitePointX = 0x0000;
    pstHDRSaticMetadata->usWhitePointY = 0x0000;

    pstHDRSaticMetadata->usMaxDisplayMasteringLv = 0x0000;
    pstHDRSaticMetadata->usMinDisplayMasteringLv = 0x0000;

    pstHDRSaticMetadata->usMaxCLL = 0x0000;
    pstHDRSaticMetadata->usMaxFALL = 0x0000;

    return _FALSE;
}
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDR Infoframe RSV0 Check
// Input Value  : Input source port
// Output Value : None
//--------------------------------------------------
void ScalerSyncDPInfoFrameRSV0Check(EnumSourceSearchPort enumSourceSearchPort, EnumDPGetRSV0InfoStatus enumDPGetRSV0InfoStatus)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            switch(enumDPGetRSV0InfoStatus)
            {
                case _DP_GET_RSV0_INFO_INITIAL:
                default:

                    ScalerDpRx0InfoFrameRSV0Check();

                    break;

                case _DP_GET_RSV0_INFO_ACTIVE:

                    if(GET_DP_RX0_RSV0_DETECTING() == _FALSE)
                    {
                        SET_DP_RX0_RSV0_DETECTING();
                        ScalerDpRx0InfoFrameRSV0Check();

#if(_DP_FREESYNC_SUPPORT == _ON)
                        // Activate Packet Detection Event
                        ScalerTimerActiveTimerEvent(130, _SCALER_TIMER_EVENT_DP_RX0_RSV0_PACKET_DETECT);
#else
                        // Activate Packet Detection Event
                        ScalerTimerActiveTimerEvent(((WORD)2 * 10000 / GET_INPUT_TIMING_VFREQ()), _SCALER_TIMER_EVENT_DP_RX0_RSV0_PACKET_DETECT);
#endif
                    }

                    break;
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            switch(enumDPGetRSV0InfoStatus)
            {
                case _DP_GET_RSV0_INFO_INITIAL:
                default:

                    ScalerDpRx1InfoFrameRSV0Check();

                    break;

                case _DP_GET_RSV0_INFO_ACTIVE:

                    if(GET_DP_RX1_RSV0_DETECTING() == _FALSE)
                    {
                        SET_DP_RX1_RSV0_DETECTING();
                        ScalerDpRx1InfoFrameRSV0Check();

#if(_DP_FREESYNC_SUPPORT == _ON)
                        // Activate Packet Detection Event
                        ScalerTimerActiveTimerEvent(130, _SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#else
                        // Activate Packet Detection Event
                        ScalerTimerActiveTimerEvent(((WORD)2 * 10000 / GET_INPUT_TIMING_VFREQ()), _SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#endif
                    }

                    break;
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _D2_INPUT_PORT:

            switch(enumDPGetRSV0InfoStatus)
            {
                case _DP_GET_RSV0_INFO_INITIAL:
                default:

                    ScalerDpRx1InfoFrameRSV0Check();

                    break;

                case _DP_GET_RSV0_INFO_ACTIVE:

                    if(GET_DP_RX1_RSV0_DETECTING() == _FALSE)
                    {
                        SET_DP_RX1_RSV0_DETECTING();
                        ScalerDpRx1InfoFrameRSV0Check();

#if(_DP_FREESYNC_SUPPORT == _ON)
                        // Activate Packet Detection Event
                        ScalerTimerActiveTimerEvent(130, _SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#else
                        // Activate Packet Detection Event
                        ScalerTimerActiveTimerEvent(((WORD)2 * 10000 / GET_INPUT_TIMING_VFREQ()), _SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#endif
                    }

                    break;
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Audio Secondary Data Reset Process
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpSecDataResetProc(BYTE ucInputPort)
{
#if(_AUDIO_SUPPORT == _ON)
    WORD usVolume = 0;

    if(ucInputPort == ScalerAudioGetDigitalAudioPortMapping())
    {
        usVolume = ((WORD) ScalerGetBit(P8_A5_DVC_GAIN_MSB, (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ScalerGetByte(P8_A6_DVC_GAIN_LSB);

        ScalerAudioMuteProc(_ON, usVolume);
        ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

#if(_EMBEDDED_DAC_SUPPORT == _ON)
        ScalerAudioDACNormalToDepop();
#endif
    }
#endif

    ScalerDpSecDataReset(ucInputPort);
}

//--------------------------------------------------
// Description  : DP HDR Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpHDRReset(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerDpRx0SetInitialRSV0InfoType();
#if(_DP_HDR10_SUPPORT == _ON)
    memset(g_pucDPRx0HDR10Backup, 0, sizeof(g_pucDPRx0HDR10Backup));
#endif
    memset(g_pucDPRx0RSV0Backup, 0, sizeof(g_pucDPRx0RSV0Backup));
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
    ScalerDpRx1SetInitialRSV0InfoType();
#if(_DP_HDR10_SUPPORT == _ON)
    memset(g_pucDPRx1HDR10Backup, 0, sizeof(g_pucDPRx1HDR10Backup));
#endif
    memset(g_pucDPRx1RSV0Backup, 0, sizeof(g_pucDPRx1RSV0Backup));
#endif
}
#endif // End of #if(_DP_ULTRA_HDR_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current FreeSync II data enable status
// Input Value  : enumSourceSearchPort --> Input port
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerSyncFreeSyncIICheckPortStatus(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
#if(_D0_HDMI_SUPPORT == _ON)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            if(_DP_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_HDMI_SUPPORT == _ON)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            if(_DP_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif

            break;

        case _D2_INPUT_PORT:
#if(_D2_HDMI_SUPPORT == _ON)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(_DP_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif

            break;

        case _D3_INPUT_PORT:
#if(_D3_HDMI_SUPPORT == _ON)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_HDMI_SUPPORT == _ON)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_HDMI_SUPPORT == _ON)
            if(_HDMI_FREESYNC_II_SUPPORT == _OFF)
            {
                return _FALSE;
            }
#endif
            break;

        default:
            return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Current FreeSync II data
// Input Value  : pstFreeSyncIIMetadata --> FreeSync II data
//                enumSourceSearchPort --> Input port
// Output Value : _FALSE: no receive
//--------------------------------------------------
bit ScalerSyncFreeSyncIIGetCurrentStatus(StructFreeSyncIIInfo *pstFreeSyncIIMetadata, EnumSourceSearchPort enumSourceSearchPort)
{
    if(ScalerSyncFreeSyncIICheckPortStatus(enumSourceSearchPort) == _TRUE)
    {
        bit bFreeSyncIIInfoReceive = 0;
        BYTE pucFreeSyncIIInfoData[_HW_DP_INFOFRAME_RSV0_LENGTH];

        memset(pucFreeSyncIIInfoData, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);

        switch(enumSourceSearchPort)
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_DP_FREESYNC_II_SUPPORT == _ON)
            case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            case _D6_INPUT_PORT:
#endif

#if(_DP_HDR10_SUPPORT == _ON)
                bFreeSyncIIInfoReceive = GET_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED();
#else
                bFreeSyncIIInfoReceive = _TRUE;
#endif
                memcpy(pucFreeSyncIIInfoData, g_pucDPRx0RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
                break;
#endif // End of #if(_DP_FREESYNC_II_SUPPORT == _ON)

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_DP_FREESYNC_II_SUPPORT == _ON)
            case _D1_INPUT_PORT:

#if(_DP_HDR10_SUPPORT == _ON)
                bFreeSyncIIInfoReceive = GET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
#else
                bFreeSyncIIInfoReceive = _TRUE;
#endif
                memcpy(pucFreeSyncIIInfoData, g_pucDPRx1RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
                break;
#endif // End of #if(_DP_FREESYNC_II_SUPPORT == _ON)

#elif(_D1_HDMI_SUPPORT == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
            case _D1_INPUT_PORT:

#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
                bFreeSyncIIInfoReceive = GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED();
#else
                bFreeSyncIIInfoReceive = GET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED();
#endif

                GET_TMDSRX1_FREESYNCII_DATA(pucFreeSyncIIInfoData);

                break;
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if(_DP_FREESYNC_II_SUPPORT == _ON)
            case _D2_INPUT_PORT:

#if(_DP_HDR10_SUPPORT == _ON)
                // RL6492: _DIGITAL_PORT_COMBO_PHY_D1_D2
                bFreeSyncIIInfoReceive = GET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
#else
                bFreeSyncIIInfoReceive = _TRUE;
#endif
                memcpy(pucFreeSyncIIInfoData, g_pucDPRx1RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
                break;
#endif // End of #if(_DP_FREESYNC_II_SUPPORT == _ON)

#elif(_D2_HDMI_SUPPORT == _ON)

#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
            case _D2_INPUT_PORT:

#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
                bFreeSyncIIInfoReceive = GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED();
#else
                bFreeSyncIIInfoReceive = GET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED();
#endif

                GET_TMDSRX2_FREESYNCII_DATA(pucFreeSyncIIInfoData);
                break;
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)

#endif

#if(_D3_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
            case _D3_INPUT_PORT:

                bFreeSyncIIInfoReceive = GET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED();
                GET_TMDSRX3_FREESYNCII_DATA(pucFreeSyncIIInfoData);
                break;
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#endif

#if(_D4_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
            case _D4_INPUT_PORT:

                bFreeSyncIIInfoReceive = GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
                GET_TMDSRX4_FREESYNCII_DATA(pucFreeSyncIIInfoData);
                break;
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#endif

#if(_D5_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_II_SUPPORT == _ON)
            case _D5_INPUT_PORT:

                bFreeSyncIIInfoReceive = GET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED();
                GET_TMDSRX5_FREESYNCII_DATA(pucFreeSyncIIInfoData);
                break;
#endif // End of #if(_HDMI_FREESYNC_II_SUPPORT == _ON)
#endif

            default:
                break;
        }

        // Check HDR Version/ Length & InfoFrame receive bit
        if((bFreeSyncIIInfoReceive == _TRUE) && (pucFreeSyncIIInfoData[1] == 0x1A) && (pucFreeSyncIIInfoData[2] == 0x00) && (pucFreeSyncIIInfoData[3] == 0x00))
        {
            pstFreeSyncIIMetadata->b1NativeColorSpaceEnable = (bit)(pucFreeSyncIIInfoData[6] & _BIT3);
            pstFreeSyncIIMetadata->b1BacklightControlEnable = (bit)(pucFreeSyncIIInfoData[6] & _BIT4);
            pstFreeSyncIIMetadata->b1LocalDimmingDisable = (bit)(pucFreeSyncIIInfoData[6] & _BIT5);
            pstFreeSyncIIMetadata->b5EOTFType = (pucFreeSyncIIInfoData[9] & 0x1F);
            pstFreeSyncIIMetadata->ucBacklightControlRatio = pucFreeSyncIIInfoData[10];

            return _TRUE;
        }
    }

    pstFreeSyncIIMetadata->b1NativeColorSpaceEnable = 0;
    pstFreeSyncIIMetadata->b1BacklightControlEnable = 0;
    pstFreeSyncIIMetadata->b1LocalDimmingDisable = 0;
    pstFreeSyncIIMetadata->b5EOTFType = 0x00;
    pstFreeSyncIIMetadata->ucBacklightControlRatio = 0x00;

    return _FALSE;
}
#endif // End of #if(_FREESYNC_II_SUPPORT == _ON)

#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Check Hot Plug Event Exist
// Input Value  : None
// Output Value : _TRUE -> Exist; _FALSE -> Not Exist
//--------------------------------------------------
bit ScalerSyncDpCheckUrgentHotPlugEventExist(void)
{
#if(_D0_DP_EXIST == _ON)
    if((GET_DP_RX0_HOTPLUG_ASSERT_TYPE() != _DP_HPD_NONE) && (GET_DP_RX0_HOTPLUG_ASSERT_TYPE() > _DP_HPD_LOW))
    {
        return _TRUE;
    }

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
    if((ScalerTypeCRx0PdGetHPDQueue(ScalerTypeCRx0PdGetHPDQueReadPointer()) == _PD_HPD_HIGH) ||
       (ScalerTypeCRx0PdGetHPDQueue(ScalerTypeCRx0PdGetHPDQueReadPointer()) == _PD_HPD_LOW))
    {
        return _TRUE;
    }
#endif
#endif

#if(_D1_DP_EXIST == _ON)
    if((GET_DP_RX1_HOTPLUG_ASSERT_TYPE() != _DP_HPD_NONE) && (GET_DP_RX1_HOTPLUG_ASSERT_TYPE() > _DP_HPD_LOW))
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpCapabilitySwitchProc(void)
{
#if(_D0_DP_EXIST == _ON)
    bit bDPRx0DoLongHotPlug = _FALSE;
#endif

#if(_D1_DP_EXIST == _ON)
    bit bDPRx1DoLongHotPlug = _FALSE;
#endif

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
    ScalerSyncDpMarginLinkCapabilitySwitchProc();
#endif

    if(GET_DP_RX_CAPABILITY_SWITCHED() == _TRUE)
    {
        // D0 Port Version Switch
#if(_D0_DP_EXIST == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            if(ScalerSyncDpFreesyncCapabilitySwitchProc(GET_DP_EMBEDDED_SWITCH_SELECT()) == _TRUE)
            {
                bDPRx0DoLongHotPlug = _TRUE;
            }
#else
            if(ScalerSyncDpFreesyncCapabilitySwitchProc(_D0_INPUT_PORT) == _TRUE)
            {
                bDPRx0DoLongHotPlug = _TRUE;
            }
#endif
#endif

            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D0_PORT_TARGET_LANE_COUNT())
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D0_PORT_TARGET_LANE_COUNT());

                bDPRx0DoLongHotPlug = _TRUE;
            }

            if(GET_DP_RX_D0_EDID_SWITCH() == _TRUE)
            {
                CLR_DP_RX_D0_EDID_SWITCH();

                bDPRx0DoLongHotPlug = _TRUE;
            }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            CLR_DP_RX_D6_EDID_SWITCH();
#endif

#if(_DP_MST_SUPPORT == _ON)
            if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && (GET_DP_RX_D0_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
            {
                SET_DP_RX_D0_PORT_TARGET_VERSION(_DP_VERSION_1_2);
            }
#endif

            if(ScalerSyncDpVersionChange(_D0_INPUT_PORT, GET_DP_RX_D0_PORT_TARGET_VERSION()) == _TRUE)
            {
#if(_DP_MST_SUPPORT == _ON)
                if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
                   (GET_DP_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
                   (GET_DP_RX_REPLY_BUF_FREE() == _FALSE))
                {
                    return;
                }
#endif
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());

#if(_DP_MST_SUPPORT == _ON)
                if(GET_DP_RX_D0_PORT_TARGET_VERSION() == _DP_VERSION_1_1)
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                }
#endif

                bDPRx0DoLongHotPlug = _TRUE;
            }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            else
            {
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());
            }
#endif
        }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            if(ScalerSyncDpFreesyncCapabilitySwitchProc(_D6_INPUT_PORT) == _TRUE)
            {
                bDPRx0DoLongHotPlug = _TRUE;
            }
#endif

            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D6_PORT_TARGET_LANE_COUNT())
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D6_PORT_TARGET_LANE_COUNT());

                bDPRx0DoLongHotPlug = _TRUE;
            }

            if(GET_DP_RX_D6_EDID_SWITCH() == _TRUE)
            {
                CLR_DP_RX_D6_EDID_SWITCH();

                bDPRx0DoLongHotPlug = _TRUE;
            }

            CLR_DP_RX_D0_EDID_SWITCH();

#if(_DP_MST_SUPPORT == _ON)
            if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT) && (GET_DP_RX_D6_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
            {
                SET_DP_RX_D6_PORT_TARGET_VERSION(_DP_VERSION_1_2);
            }
#endif

            if(ScalerSyncDpVersionChange(_D6_INPUT_PORT, GET_DP_RX_D6_PORT_TARGET_VERSION()) == _TRUE)
            {
#if(_DP_MST_SUPPORT == _ON)
                if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
                   (GET_DP_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
                   (GET_DP_RX_REPLY_BUF_FREE() == _FALSE))
                {
                    return;
                }
#endif
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());

#if(_DP_MST_SUPPORT == _ON)
                if(GET_DP_RX_D6_PORT_TARGET_VERSION() == _DP_VERSION_1_1)
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                }
#endif

                bDPRx0DoLongHotPlug = _TRUE;
            }
            else
            {
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());
            }
        }
#endif

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
        if(GET_DP_RX0_TARGET_HDCP_CAPABILITY() != ScalerDpRx0CheckHdcpCapability())
        {
            if(GET_DP_RX0_TARGET_HDCP_CAPABILITY() == _ENABLE)
            {
                DebugMessageRx0("Rx0 got the HDCP!", 0);

                ScalerDpHdcpCtrlDpcdSwitch(_D0_INPUT_PORT);

                // Check if source doing HDCP handshake while HDCP capability disable
                if(GET_DP_RX0_HDCP_HANDSHAKE_WO_CAP() == _TRUE)
                {
                    CLR_DP_RX0_HDCP_HANDSHAKE_WO_CAP();

                    bDPRx0DoLongHotPlug = _TRUE;
                }
            }
        }
#endif // End of #if(_DP_HDCP_ARBITER_SUPPORT == _ON)

#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))
        if((bDPRx0DoLongHotPlug == _TRUE) && (GET_DP_RX0_ALT_MODE_HPD_STAUTS() == _HIGH))
#else
        if((bDPRx0DoLongHotPlug == _TRUE) && (PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH))
#endif
        {
#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
            {
                ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRx0SetHotPlugEvent(_DP_LONG_HPD_EVENT);
            }
        }

#endif // End of #if(_D0_DP_EXIST == _ON)


        // D1 Port Version Switch
#if(_D1_DP_EXIST == _ON)

#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
        if(ScalerSyncDpFreesyncCapabilitySwitchProc(GET_DP_EMBEDDED_SWITCH_SELECT()) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#else
        if(ScalerSyncDpFreesyncCapabilitySwitchProc(_D1_INPUT_PORT) == _TRUE)
        {
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif
#endif

        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D1_PORT_TARGET_LANE_COUNT())
        {
            ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D1_PORT_TARGET_LANE_COUNT());

            bDPRx1DoLongHotPlug = _TRUE;
        }

        if(GET_DP_RX_D1_EDID_SWITCH() == _TRUE)
        {
            CLR_DP_RX_D1_EDID_SWITCH();

            bDPRx1DoLongHotPlug = _TRUE;
        }

#if(_DP_MST_SUPPORT == _ON)
        if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT) && (GET_DP_RX_D1_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
        {
            SET_DP_RX_D1_PORT_TARGET_VERSION(_DP_VERSION_1_2);
        }
#endif

        if(ScalerSyncDpVersionChange(_D1_INPUT_PORT, GET_DP_RX_D1_PORT_TARGET_VERSION()) == _TRUE)
        {
#if(_DP_MST_SUPPORT == _ON)
            if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
               (GET_DP_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
               (GET_DP_RX_REPLY_BUF_FREE() == _FALSE))
            {
                return;
            }
#endif
            ScalerDpRx1ChangeDpcdVersion(GET_DP_RX_D1_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());

#if(_DP_MST_SUPPORT == _ON)
            if(GET_DP_RX_D1_PORT_TARGET_VERSION() == _DP_VERSION_1_1)
            {
                CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                CLR_DP_RX1_CHECK_AUX_CH_POWER_STATUS();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
            }
#endif

            bDPRx1DoLongHotPlug = _TRUE;
        }

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
        if(GET_DP_RX1_TARGET_HDCP_CAPABILITY() != ScalerDpRx1CheckHdcpCapability())
        {
            if(GET_DP_RX1_TARGET_HDCP_CAPABILITY() == _ENABLE)
            {
                DebugMessageRx1("Rx1 got the HDCP!", 0);

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE != _DP_EMBEDDED_SWITCH_NONE)
                ScalerDpHdcpCtrlDpcdSwitch(GET_DP_EMBEDDED_SWITCH_SELECT());
#else
                ScalerDpHdcpCtrlDpcdSwitch(_D1_INPUT_PORT);
#endif

                // Check if source doing HDCP handshake while HDCP capability disable
                if(GET_DP_RX1_HDCP_HANDSHAKE_WO_CAP() == _TRUE)
                {
                    CLR_DP_RX1_HDCP_HANDSHAKE_WO_CAP();

                    bDPRx1DoLongHotPlug = _TRUE;
                }
            }
        }
#endif // End of #if(_DP_HDCP_ARBITER_SUPPORT == _ON)

#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
        if((bDPRx1DoLongHotPlug == _TRUE) &&
           (((GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)) ||
            ((GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT) && (PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH))))
#else
        if((bDPRx1DoLongHotPlug == _TRUE) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH))
#endif
        {
#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
            {
                ScalerDpRx1SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
            }
            else
#endif
            {
                ScalerDpRx1SetHotPlugEvent(_DP_LONG_HPD_EVENT);
            }
        }

#endif // End of #if(_D1_DP_EXIST == _ON)


        // Mst Port Switch
#if((_DP_MST_SUPPORT == _ON) && (_DP_MST_AUTO_SEARCH_SUPPORT == _OFF))

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        // Target MST Port != Current Capable Port or External-Switching port case
        if(((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_NO_PORT) && (g_enumDpMSTCapablePort != _DP_MST_NO_PORT)) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && (g_enumDpMSTCapablePort == _DP_MST_NO_PORT)) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (g_bDpMSTD6Capable == _TRUE))) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT) && (g_enumDpMSTCapablePort == _DP_MST_NO_PORT)) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT) && ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (g_bDpMSTD6Capable == _FALSE))))
#else
        if(GET_DP_RX_TARGET_MST_PORT() != g_enumDpMSTCapablePort)
#endif
        {
            DebugMessageMst("MST Cap Switch", GET_DP_RX_TARGET_MST_PORT());

#if(_D0_DP_EXIST == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
            {
                // No Port or Rx1 or Rx6 => Rx0
                // RX0 => NO Port or RX1 or Rx6
                if(((g_enumDpMSTCapablePort != _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT)) ||
                   ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() != _DP_MST_RX0_PORT)))
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);

                    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
                    {
#if(_DP_MST_CAP_ON_TO_OFF_NO_HPD == _ON)
                        if((g_enumDpMSTCapablePort != _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT))
#endif
                        {
                            ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
                        }
                    }

                    DebugMessageMst("MST Switch Long Plug : 1", GET_DP_RX_TARGET_MST_PORT());
                }

                if(GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT)
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), _DP_MST_RX0_PORT);
                }
                else
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), _DP_MST_NO_PORT);
                }
            }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
                // No Port or Rx0 or Rx1 => Rx6
                // RX6 => NO Port or RX0 or Rx1
                if(((g_enumDpMSTCapablePort != _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT)) ||
                   ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() != _DP_MST_RX6_PORT)))
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_STATUS();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);

                    if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
                    {
#if(_DP_MST_CAP_ON_TO_OFF_NO_HPD == _ON)
                        if((g_enumDpMSTCapablePort != _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT))
#endif
                        {
                            ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
                        }
                    }

                    DebugMessageMst("MST Switch Long Plug : 2", GET_DP_RX_TARGET_MST_PORT());
                }

                if(GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT)
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), _DP_MST_RX6_PORT);
                }
                else
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), _DP_MST_NO_PORT);
                }
            }
#endif

#endif

#if(_D1_DP_EXIST == _ON)

            // No Port or Rx0 or Rx6 => Rx1
            // RX1 => NO Port or RX0 or Rx6
            if(((g_enumDpMSTCapablePort != _DP_MST_RX1_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT)) ||
               ((g_enumDpMSTCapablePort == _DP_MST_RX1_PORT) && (GET_DP_RX_TARGET_MST_PORT() != _DP_MST_RX1_PORT)))
            {
                CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                CLR_DP_RX1_CHECK_AUX_CH_POWER_STATUS();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);

                if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
                {
#if(_DP_MST_CAP_ON_TO_OFF_NO_HPD == _ON)
                    if((g_enumDpMSTCapablePort != _DP_MST_RX1_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT))
#endif
                    {
                        ScalerDpRx1SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
                    }
                }
            }

            if(GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT)
            {
                ScalerDpRx1ChangeDpcdVersion(GET_DP_RX_D1_PORT_TARGET_VERSION(), _DP_MST_RX1_PORT);
            }
            else
            {
                ScalerDpRx1ChangeDpcdVersion(GET_DP_RX_D1_PORT_TARGET_VERSION(), _DP_MST_NO_PORT);
            }
#endif

#if(_DP_TX_SUPPORT == _ON)

            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                pData[0] = (GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() << 1);

                SET_DP_TX_DPCD_111(pData);

#if(_DP_FREESYNC_SUPPORT == _ON)
                // Clear freesync enable bit
                ScalerDpTxAuxNativeRead(0x00, 0x01, 0x07, 1, pData);

                if((pData[0] & _BIT7) == _BIT7)
                {
                    pData[0] &= ~_BIT7;
                    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x07, 1, pData);
                }
#endif
            }
#endif

            ScalerDpRxMstInitial(GET_DP_RX_TARGET_MST_PORT());
        }
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if((_DP_TX_SUPPORT == _ON) && (_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON))
        ScalerDpTxBlockStatusCheck();
#endif

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)

#if(_D0_DP_EXIST == _ON)
        // Align 0220Xh & 0000Xh
        for(pData[0] = 0x02; pData[0] <= 0x0F; pData[0]++)
        {
            ScalerDpRx0SetDpcdValue(0x00, 0x22, pData[0], ScalerDpRx0GetDpcdInfo(0x00, 0x00, pData[0]));
        }
#endif// End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)
        // Align 0220Xh & 0000Xh
        for(pData[0] = 0x02; pData[0] <= 0x0F; pData[0]++)
        {
            ScalerDpRx1SetDpcdValue(0x00, 0x22, pData[0], ScalerDpRx1GetDpcdInfo(0x00, 0x00, pData[0]));
        }
#endif// End of #if(_D1_DP_EXIST == _ON)

#endif

        CLR_DP_RX_CAPABILITY_SWITCHED();
    }
}

//--------------------------------------------------
// Description  : Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSyncDpVersionChange(EnumSourceSearchPort enumSourceSearchPort, EnumDpVersionType enumDpVersion)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:
        case _D6_INPUT_PORT:

            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
            {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                if(ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x00) != enumDpVersion)
#else
                if(enumDpVersion != _DP_VERSION_1_4)
#endif
                {
                    return _TRUE;
                }
            }
            else
            {
#if((_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON) && (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI))
                // For Eizo Type-C case, DP version is always set to DP1.2, so check the 00080h value instead of DP version
                if(ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x80) == 0x00)
                {
                    if(enumDpVersion > _DP_VERSION_1_1)
                    {
                        return _TRUE;
                    }
                }
                else
                {
                    if(enumDpVersion == _DP_VERSION_1_1)
                    {
                        return _TRUE;
                    }
                }
#else
                if(ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) != enumDpVersion)
                {
                    return _TRUE;
                }
#endif
            }

            break;
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:

            if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
            {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                if(ScalerDpRx1GetDpcdInfo(0x00, 0x22, 0x00) != enumDpVersion)
#else
                if(enumDpVersion != _DP_VERSION_1_4)
#endif
                {
                    return _TRUE;
                }
            }
            else
            {
#if((_EIZO_CUSTOMIZED_VALUE_OF_DPCD_SUPPORT == _ON) && (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_MINI))
                // For Eizo Type-C case, DP version is always set to DP1.2, so check the 00080h value instead of DP version
                if(ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x80) == 0x00)
                {
                    if(enumDpVersion > _DP_VERSION_1_1)
                    {
                        return _TRUE;
                    }
                }
                else
                {
                    if(enumDpVersion == _DP_VERSION_1_1)
                    {
                        return _TRUE;
                    }
                }
#else
                if(ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x00) != enumDpVersion)
                {
                    return _TRUE;
                }
#endif
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Margin Link Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpMarginLinkCapabilitySwitchProc(void)
{
#if((_D0_DP_EXIST == _ON) && (_DP_HBR2_MARGIN_LINK_SUPPORT == _ON))
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) &&
       (ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _FALSE) &&
       ((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) < _D0_DP_LINK_CLK_RATE)))
#else
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx0DPCD02201hValue < _D0_DP_LINK_CLK_RATE)))
#endif
        {
            if(_D0_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif
            DebugMessageRx0("Flag Clear_Hotplug Event_D0", _D0_DP_LINK_CLK_RATE);
        }
    }
    else if((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) &&
            (ScalerSyncDpCableStatus(_D6_INPUT_PORT) == _FALSE) &&
            ((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D6_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) < _D6_DP_LINK_CLK_RATE)))
#else
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D6_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx0DPCD02201hValue < _D6_DP_LINK_CLK_RATE)))
#endif
        {
            if(_D6_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D6_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D6_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx0DPCD02201hValue = _D6_DP_LINK_CLK_RATE;
#endif
            DebugMessageRx0("Flag Clear_Hotplug Event_D6", _D6_DP_LINK_CLK_RATE);
        }
    }
#else
    if((ScalerSyncDpCableStatus(_D0_INPUT_PORT) == _FALSE) && ((ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx0GetDpcdInfo(0x00, 0x22, 0x01) < _D0_DP_LINK_CLK_RATE)))
#else
        if(((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x01) < _D0_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx0DPCD02201hValue < _D0_DP_LINK_CLK_RATE)))
#endif
        {
            if(_D0_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x01, _D0_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx0SetDpcdValue(0x00, 0x22, 0x01, _D0_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx0DPCD02201hValue = _D0_DP_LINK_CLK_RATE;
#endif
            DebugMessageRx0("Flag Clear_Hotplug Event_D0", _D0_DP_LINK_CLK_RATE);
        }
    }
#endif
#endif

#if((_D1_DP_EXIST == _ON) && (_DP_HBR2_MARGIN_LINK_SUPPORT == _ON))
    if((ScalerSyncDpCableStatus(_D1_INPUT_PORT) == _FALSE) && ((ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x00) >= _DP_VERSION_1_2) || (ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7)))
    {
#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
        if(((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01) < _D1_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (ScalerDpRx1GetDpcdInfo(0x00, 0x22, 0x01) < _D1_DP_LINK_CLK_RATE)))
#else
        if(((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == 0x00) && (ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01) < _D1_DP_LINK_CLK_RATE)) ||
           ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x0E, _BIT7) == _BIT7) && (g_ucDpRx1DPCD02201hValue < _D1_DP_LINK_CLK_RATE)))
#endif
        {
            if(_D1_DP_LINK_CLK_RATE >= _DP_HIGH_SPEED2_540MHZ)
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _D1_DP_LINK_CLK_RATE);
            }

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            ScalerDpRx1SetDpcdValue(0x00, 0x22, 0x01, _D1_DP_LINK_CLK_RATE);
#else
            // When Define Extended Rx Cap Should Set DPCD 0x02201
            g_ucDpRx1DPCD02201hValue = _D1_DP_LINK_CLK_RATE;
#endif
            DebugMessageRx1("Flag Clear_Hotplug Event_D1", _D1_DP_LINK_CLK_RATE);
        }
    }
#endif
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Freesync Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerSyncDpFreesyncCapabilitySwitchProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            if(GET_DP_RX0_FREESYNC_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_RX0_FREESYNC_CAPABILITY_SWITCH();

                if(GET_DP_RX0_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
                {
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, _BIT6);
#endif
                }
                else
                {
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, 0x00);
#endif
                }

                return _TRUE;
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if(GET_DP_RX1_FREESYNC_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_RX1_FREESYNC_CAPABILITY_SWITCH();

                if(GET_DP_RX1_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
                {
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, _BIT6);
#endif
#else
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, _BIT6);
#endif
#endif
                }
                else
                {
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, 0x00);
#endif
#else
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, 0x00);
#endif
#endif
                }

                return _TRUE;
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            if(GET_DP_RX2_FREESYNC_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_RX2_FREESYNC_CAPABILITY_SWITCH();

                if(GET_DP_RX2_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
                {
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, _BIT6);
#endif
#else
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, _BIT6);
#endif
#endif
                }
                else
                {
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, 0x00);
#endif
#else
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx1SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, 0x00);
#endif
#endif
                }

                return _TRUE;
            }

            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:

            if(GET_DP_RX6_FREESYNC_CAPABILITY_SWITCH() == _TRUE)
            {
                CLR_DP_RX6_FREESYNC_CAPABILITY_SWITCH();

                if(GET_DP_RX6_FREESYNC_SUPPORT() == _FREESYNC_SUPPORT_ON)
                {
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, _BIT6);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, _BIT6);
#endif
                }
                else
                {
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x07, ~_BIT6, 0x00);

#if(_HW_DP_DPCD_EXT_CAP_PHYSICAL_ADDRESS_SUPPORT == _ON)
                    ScalerDpRx0SetDpcdBitValue(0x00, 0x22, 0x07, ~_BIT6, 0x00);
#endif
                }

                return _TRUE;
            }

            break;
#endif

        default:

            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP Fake LT Protect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpFakeLTProtect(void)
{
#if(_D0_DP_EXIST == _ON)
    // DP Fake LT Protect
    ScalerDpRx0FakeLTProtect();
#endif

#if(_D1_DP_EXIST == _ON)
    // DP Fake LT Protect
    ScalerDpRx1FakeLTProtect();
#endif
}

//--------------------------------------------------
// Description  : DP Port Cable Pre-Status
// Input Value  : enumInputPort
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerSyncDpCableStatus(EnumSourceSearchPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            return g_stDpCableStatus.b1D0Status;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return g_stDpCableStatus.b1D1Status;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            return g_stDpCableStatus.b1D2Status;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            return g_stDpCableStatus.b1D6Status;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Set Cable Pre-Status
// Input Value  : enumInputPort, bStatus
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpSetCableStatus(EnumSourceSearchPort enumInputPort, bit bStatus)
{
    bStatus = bStatus;

    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            g_stDpCableStatus.b1D0Status = bStatus;

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            g_stDpCableStatus.b1D1Status = bStatus;

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            g_stDpCableStatus.b1D2Status = bStatus;

            break;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            g_stDpCableStatus.b1D6Status = bStatus;

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Port Check Hdcp Enable Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpCheckHdcpEnable(void)
{
#if(_D0_DP_EXIST == _ON)
    // Check HDCP Enable Status
    if(ScalerDpRx0HdcpCheckEnabled() == _TRUE)
    {
        SET_DP_RX0_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX0_HDCP_CHECK_ENABLE();
    }
#endif

#if(_D1_DP_EXIST == _ON)
    // Check HDCP Enable Status
    if(ScalerDpRx1HdcpCheckEnabled() == _TRUE)
    {
        SET_DP_RX1_HDCP_CHECK_ENABLE();
    }
    else
    {
        CLR_DP_RX1_HDCP_CHECK_ENABLE();
    }
#endif
}

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
//--------------------------------------------------
// Description  : Irq Assert Timer2 Event Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void ScalerSyncDpHpdIrqAssertTimer2EventProc_EXINT(void)
{
    //=======================================================
    // 1. HPD High Process
    //=======================================================

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    if(g_ucTimerQuarterCount == 0)
#endif
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        if(GET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_LOW)
            {
                PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);

                CLR_DP_D0_HPD_IRQ_ASSERT_T2_EVENT();
            }
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(GET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_LOW)
            {
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

                CLR_DP_D1_HPD_IRQ_ASSERT_T2_EVENT();
            }
        }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        if(GET_DP_D2_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_LOW)
            {
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);

                CLR_DP_D2_HPD_IRQ_ASSERT_T2_EVENT();
            }
        }
#endif
    }

    //=======================================================
    // 2. HPD Low Process
    //=======================================================

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    if(g_ucTimerQuarterCount == 1)
#endif
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        if(GET_DP_D0_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH)
            {
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)
                DP_RX_HPD_IRQ_ASSERT_T2_DELAY();
#endif

                PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
            }
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(GET_DP_D1_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
            {
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)
                DP_RX_HPD_IRQ_ASSERT_T2_DELAY();
#endif

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
            }
        }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        if(GET_DP_D2_HPD_IRQ_ASSERT_T2_EVENT() == _TRUE)
        {
            if(PCB_D2_HOTPLUG_DETECT() == _D2_HOT_PLUG_HIGH)
            {
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)
                DP_RX_HPD_IRQ_ASSERT_T2_DELAY();
#endif

                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
            }
        }
#endif
    }
}
#pragma restore

//--------------------------------------------------
// Description  : Timer2 Aux Mode Backup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void ScalerSyncDpAuxManualModeSetting_EXINT(EnumDpAuxManualModeSetting enumSetting)
{
    if(enumSetting == _DP_AUX_MANUAL_MODE_SET)
    {
#if(_D0_DP_EXIST == _ON)
        g_ucDpRx0AuxModeBackup_EXINT = ScalerGetBit_EXINT(PB7_D0_AUX_MODE_SET, _BIT1);

        SET_DP_RX0_AUX_MANUAL_MODE_EXINT();
#endif

#if(_D1_DP_EXIST == _ON)
        g_ucDpRx1AuxModeBackup_EXINT = ScalerGetBit_EXINT(PBA_D0_AUX_MODE_SET, _BIT1);

        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
#endif
    }
    else if(enumSetting == _DP_AUX_MANUAL_MODE_RECOVER)
    {
#if(_D0_DP_EXIST == _ON)
        if(g_ucDpRx0AuxModeBackup_EXINT == _BIT1)
        {
            SET_DP_RX0_AUX_AUTO_MODE_EXINT();
        }
#endif

#if(_D1_DP_EXIST == _ON)
        if(g_ucDpRx1AuxModeBackup_EXINT == _BIT1)
        {
            SET_DP_RX1_AUX_AUTO_MODE_EXINT();
        }
#endif
    }
}
#pragma restore
#endif // End of #if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : Dp Repeater Power Off Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpRepeaterPowerOffReset(void)
{
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR))
    CLR_DP_RX0_PS_AUX_TOGGLE();

    ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_RESET);
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR))
    CLR_DP_RX1_PS_AUX_TOGGLE()

    ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_RESET);
#endif
}
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Sink count Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpRxSinkCountUpdateProc(EnumSourceSearchPort enumInputPort)
{
    if(GET_DP_TX_DOWNSTREAM_SINK_COUNT_CHANGE() == _TRUE)
    {
        CLR_DP_TX_DOWNSTREAM_SINK_COUNT_CHANGE();

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_DP_DPCD_DFP_PRESENT_REF_TO == _DP_MST_CAPABILITY)
        if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
#endif
        {
            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) == 0x00)
            {
                if(enumInputPort == _D0_INPUT_PORT)
                {
                    ScalerDpRx0UpdateSinkCount(GET_DP_TX_DOWNSTREAM_SINK_COUNT() + 1);
                }
                else
                {
                    ScalerDpRx0UpdateSinkCount(1);
                }
            }
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_DP_DPCD_DFP_PRESENT_REF_TO == _DP_MST_CAPABILITY)
        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x21, _BIT0) == _BIT0)
#endif
        {
            if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT1) == 0x00)
            {
                if(enumInputPort == _D1_INPUT_PORT)
                {
                    ScalerDpRx1UpdateSinkCount(GET_DP_TX_DOWNSTREAM_SINK_COUNT() + 1);
                }
                else
                {
                    ScalerDpRx1UpdateSinkCount(1);
                }
            }
        }
#endif
    }
}
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx PowerProc
// Input Value  : EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            ScalerDpTxInitial();

            // Power CMU PHY But use power down mode
            ScalerGDIPhyTxCMUPowerDownMode();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

            // Power Down Tx Aux
            ScalerDpTxAuxPowerOffProc();

            // Set DPTx Force To Idle Pattern
            ScalerDpTxForceIdlePatternSetting();

            // Power Down Tx Reset
            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);

            CLR_DP_TX_DOWNSTREAM_INFO_READY();

            // Power Down ML PHY
            ScalerGDIPhyTxMLPowerOff();

            // Power CMU PHY
            ScalerGDIPhyTxCMUPowerOff();

            // Clear HPD IRQ Flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

            // Clear IRQ HPD Type Flag
            CLR_DP_TX_IRQ_HPD_TYPE();
            CLR_DP_TX_IRQ_HPD_TYPE_INT();
            CLR_DP_TX_IRQ_HPD_DETECTED();
            CLR_DP_TX_IRQ_HDCP_TYPE();

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            CLR_DP_TX_HDCP2_IRQ_TYPE();
#endif

            break;

        case _POWER_ACTION_PS_TO_OFF:

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Decide Current Port DPTx whether Can Output or not
// Input Value  : InputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpTxCloneOutputPortCheck(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#endif

#if((_HW_DP_TX_VSC_SDP_TRANSMIT_SUPPORT == _OFF) && (_HDR10_SUPPORT == _ON))
    if(GET_HDR10_EOTF_SETTING() != _HDR_INFO_EOTF_TRADITIONAL_GAMMA_SDR)
    {
        return _FALSE;
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Hdcp Port Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpTxHdcpUpstreamSwitchProc(BYTE ucInputPort)
{
#if(_DP_MST_SUPPORT == _ON)
#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
    {
        SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D0_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_D0_PORT);
#endif

        return;
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D1_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_D1_PORT);
#endif

        return;
    }
#endif
#endif

#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if((ucInputPort == _D0_INPUT_PORT) || (ucInputPort == _D6_INPUT_PORT))
    {
        if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
        {
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D0_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_D0_PORT);
#endif

            return;
        }
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(ucInputPort == _D1_INPUT_PORT)
    {
        if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_END_REBUILD_PHY))
        {
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D1_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_D1_PORT);
#endif

            return;
        }
    }
#endif

    SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_NO_PORT);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
    SET_DP_RX_HDCP2_UPSTREAM_PORT(_HDCP_NO_PORT);
#endif
}

//--------------------------------------------------
// Description  : Get Upstream HDCP event
// Input Value  : None
// Output Value : EnumDPRxHDCPUpstreamAuthStatus
//--------------------------------------------------
EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void)
{
#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_RX0_HDCP_UPSTREAM_EVENT();
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_RX1_HDCP_UPSTREAM_EVENT();
    }
#endif

    return _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Get Upstream HDCP status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void)
{
#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return ((ScalerDpRx0HdcpCheckValid() == _TRUE) && (ScalerDpRx0HDCPCheckLvp() == _TRUE));
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return ((ScalerDpRx1HdcpCheckValid() == _TRUE) && (ScalerDpRx1HDCPCheckLvp() == _TRUE));
    }
#endif

    return _FALSE;
}

#if(_DP_HDCP14_CTS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Downstream HDCP Reauth Execute or not
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcpDownstreamReAuthCheck(void)
{
#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        // In SST mode
        if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == 0x00)
        {
            return ((ScalerDpRx0HdcpCheckValid() == _TRUE) && (ScalerDpRx0HDCPCheckLvp() == _TRUE));
        }
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        // In SST mode
        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == 0x00)
        {
            return ((ScalerDpRx1HdcpCheckValid() == _TRUE) && (ScalerDpRx1HDCPCheckLvp() == _TRUE));
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Upstream HDCP2 event
// Input Value  : None
// Output Value : EnumDpRxHdcp2UpstreamAuthStatus
//--------------------------------------------------
EnumDpRxHdcp2UpstreamAuthStatus ScalerSyncDpHdcp2GetUpstreamEvent(void)
{
#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_RX0_HDCP2_UPSTREAM_EVENT();
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_RX1_HDCP2_UPSTREAM_EVENT();
    }
#endif

    return _DP_RX_HDCP2_UPSTREAM_AUTH_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Get Upstream HDCP2 ContentStreamManagementStatus
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcp2GetContentStreamManagementStatus(void)
{
#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        if(GET_DP_RX0_HDCP2_MODE() == _ENABLE)
        {
            return GET_DP_RX0_HDCP2_CONTENT_STREAM_MANAGEMENT();
        }
        else
        {
            return GET_DP_RX0_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT();
        }
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        if(GET_DP_RX1_HDCP2_MODE() == _ENABLE)
        {
            return GET_DP_RX1_HDCP2_CONTENT_STREAM_MANAGEMENT();
        }
        else
        {
            return GET_DP_RX1_HDCP2_HDCP1_CONTENT_STREAM_MANAGEMENT();
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DP HDCP2.2 Mode Status
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerSyncDpGetHdcp2ModeStatus(void)
{
#if((_D0_DP_EXIST == _ON) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_RX0_HDCP2_MODE();
    }
#endif

#if(_D1_DP_EXIST == _ON)
    if(GET_DP_RX_HDCP2_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_RX1_HDCP2_MODE();
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Change DP HDCP2.2 Repeater Capable Base On DPTX Clone Status
// Input Value  : InputPort, PortType, Clone Mode or not
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpHdcpRepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType)
{
#if(_D0_DP_EXIST == _ON)
    ScalerDpRx0Hdcp2RepeaterCapableProc(ucInputPort, ucPortType);
#endif

#if(_D1_DP_EXIST == _ON)
    ScalerDpRx1Hdcp2RepeaterCapableProc(ucInputPort, ucPortType);
#endif
}
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx Fake Power Saving Check
// Input Value  : None
// Output Value : True  --> Fake Power Saving
//                False --> Power Saving
//--------------------------------------------------
bit ScalerSyncDpFakePowerSavingCheck(void)
{
    if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
    {
        if(GET_DP_SOURCE_FIRST_POWER_ON() == _TRUE)
        {
            return _TRUE;
        }

        // Source writes 00600h = 0x01, go to fake power saving for 3s.
        if(GET_DP_RX_MST_SOURCE_WRITE_POWER_UP() != _DP_SOURCE_WRITE_POWER_UP_NONE)
        {
            return _TRUE;
        }

        if(GET_DP_CHECK_AUX_CH_POWER_STATUS() == _DP_RX_AUX_POWER_STATUS_OFF)
        {
            return _FALSE;
        }

        if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT0) == _BIT0)
        {
            return _TRUE;
        }

        if(GET_DP_RX_MST_MODE_STATE() != _DP_RX_MST_MODE_STATUS_NONE_MSG)
        {
            return _TRUE;
        }

        // Check if MSG Processing or Stream Propagating
        if((ScalerDpRxMstCheckMsgTransition() == _TRUE) || (GET_REG_DP_DPCD_INFO(0x00, 0x02, 0xC1) != 0))
        {
            return _TRUE;
        }

        return GET_DP_LT_STATUS_CHCEK();
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Rx Fake Power Off Check
// Input Value  : enumInputPort
// Output Value : True  --> Fake Power Off
//                False --> Power Off
//--------------------------------------------------
bit ScalerSyncDpFakePowerOffCheck(EnumSourceSearchPort enumInputPort)
{
    CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD();

    if(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (enumInputPort == _D0_INPUT_PORT)) ||
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
       ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (enumInputPort == _D6_INPUT_PORT)) ||
#endif
       ((g_enumDpMSTCapablePort == _DP_MST_RX1_PORT) && (enumInputPort == _D1_INPUT_PORT)))
    {
        // Let MSG keep proccessing
        if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) == _BIT1)
        {
            // Keep HPD high if upstream is source
            if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT2) == _BIT2)
            {
                // DP Rx MST DC OFF HPD Toggle Not Process
                SET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD();
            }

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check if Event is Valid
// Input Value  : ucEventIndex --> Event to be checked
// Output Value : Validity(_TRUE/_FALSE)
//--------------------------------------------------
void ScalerSyncDpSourceWritePowerUpProc(void)
{
#if(_D0_DP_EXIST == _TRUE)
    if(GET_DP_RX0_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TRIGGERED)
    {
        DebugMessageRx0("Rx0 Source Writes 600h = 0x01", 0);

        ScalerTimerReactiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX0_SOURCE_WRITE_POWER_UP_TIMEOUT);

        SET_DP_RX0_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE);
    }
#endif

#if(_D1_DP_EXIST == _TRUE)
    if(GET_DP_RX1_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TRIGGERED)
    {
        DebugMessageRx1("Rx1 Source Writes 600h = 0x01", 0);

        ScalerTimerReactiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX1_SOURCE_WRITE_POWER_UP_TIMEOUT);

        SET_DP_RX1_SOURCE_WRITE_POWER_UP(_DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE);
    }
#endif
}

//--------------------------------------------------
// Description  : Clear Source Write Power Up
// Input Value  : EnumInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpRxClrSourceWritePowerUp(EnumSourceSearchPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            CLR_DP_RX0_SOURCE_WRITE_POWER_UP();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            CLR_DP_RX1_SOURCE_WRITE_POWER_UP();

            break;
#endif

        default:

            break;
    }
}
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable DownLoad DPTx HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Key download port
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, _BIT3);
    }
    else
    {
        // Disable Key download port
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : DownLoad TX HDCP AKsv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    for(pData[0] = ucSubAddr; pData[0] < ucLength; pData[0]++)
    {
        g_pucHdcpAksvBackup[pData[0]] = pucReadArray[pData[0]];
    }

    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[0]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[1]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[2]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[3]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[4]);
}

//--------------------------------------------------
// Description  : DownLoad TX HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray)
{
    ScalerWrite(PBB_32_DP_HDCP_KEY_DL_PORT, usLength, pucReadArray, _NON_AUTOINC);
}
#endif

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : Input Port
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
EnumHDCPType ScalerSyncHdcpCheckEnabled(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            if(ScalerDpHdcpCheckValid(ucInputPort) == _TRUE)
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(GET_DP_RX0_HDCP2_MODE() == _TRUE)
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX0_HDCP2_REPEATER_CAPABLE() == _TRUE)
                    {
                        return _HDCP_22_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_22;
                    }
                }
                else
#endif
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX0_HDCP_REPEATER_SUPPORT() == _TRUE)
                    {
                        return _HDCP_14_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_14;
                    }
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#else // Else of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D0_TMDS_SUPPORT == _ON)
            if(ScalerTMDSHdcpEnabled(ucInputPort) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)))
                if(GET_TMDS_RX0_HDCP2_MODE() == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif // End of #if(_D0_TMDS_SUPPORT == _ON)
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            break;

        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            if(ScalerDpHdcpCheckValid(ucInputPort) == _TRUE)
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(GET_DP_RX1_HDCP2_MODE() == _TRUE)
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX1_HDCP2_REPEATER_CAPABLE() == _TRUE)
                    {
                        return _HDCP_22_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_22;
                    }
                }
                else
#endif
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE)
                    {
                        return _HDCP_14_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_14;
                    }
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#else

#if(_D1_TMDS_SUPPORT == _ON)
            if(ScalerTMDSHdcpEnabled(ucInputPort) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)))
                if(GET_TMDS_RX1_HDCP2_MODE() == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif

#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
            if(ScalerDpHdcpCheckValid(ucInputPort) == _TRUE)
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(GET_DP_RX1_HDCP2_MODE() == _TRUE)
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX1_HDCP2_REPEATER_CAPABLE() == _TRUE)
                    {
                        return _HDCP_22_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_22;
                    }
                }
                else
#endif
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE)
                    {
                        return _HDCP_14_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_14;
                    }
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#else

#if(_D2_TMDS_SUPPORT == _ON)
            if(ScalerTMDSHdcpEnabled(ucInputPort) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)))
                if(GET_TMDS_RX2_HDCP2_MODE() == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif

#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_TMDS_SUPPORT == _ON)
            if(ScalerTMDSHdcpEnabled(ucInputPort) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)))
                if(GET_TMDS_RX3_HDCP2_MODE() == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_TMDS_SUPPORT == _ON)
            if(ScalerTMDSHdcpEnabled(ucInputPort) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)))
                if(GET_TMDS_RX4_HDCP2_MODE() == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_TMDS_SUPPORT == _ON)
            if(ScalerTMDSHdcpEnabled(ucInputPort) == _TRUE)
            {
#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)))
                if(GET_TMDS_RX5_HDCP2_MODE() == _TRUE)
                {
                    return _HDCP_22;
                }
                else
#endif
                {
                    return _HDCP_14;
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;

        case _D6_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            if(ScalerDpHdcpCheckValid(ucInputPort) == _TRUE)
            {
#if(_DP_HDCP_2_2_SUPPORT == _ON)
                if(GET_DP_RX0_HDCP2_MODE() == _TRUE)
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX0_HDCP2_REPEATER_CAPABLE() == _TRUE)
                    {
                        return _HDCP_22_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_22;
                    }
                }
                else
#endif
                {
#if(_DP_TX_SUPPORT == _ON)
                    if(GET_DP_RX0_HDCP_REPEATER_SUPPORT() == _TRUE)
                    {
                        return _HDCP_14_REPEATER;
                    }
                    else
#endif
                    {
                        return _HDCP_14;
                    }
                }
            }
            else
            {
                return _HDCP_NONE;
            }
#endif
            break;
        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : GDI Power Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncGDIPowerProc(EnumPowerAction enumPowerAction)
{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, enumPowerAction);
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, enumPowerAction);
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, enumPowerAction);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, enumPowerAction);
#endif
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_URGENT_EVENT_CHECK_MODE == _ON)
//--------------------------------------------------
// Description  : Check Urgent Event Occur
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerSyncCheckUrgentEvent(void)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    if(ScalerDpRxMstCheckMsgTransition() == _TRUE)
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
    if(GET_HDCP_2_2_AUTHENTICATION_ACTIVE() == _TRUE)
    {
        DebugMessageHDCP2("HDCP2 Urgent", g_ucHdcp2AuthActive);

        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif

#if(_DP_SUPPORT == _ON)
    if(ScalerSyncDpCheckUrgentHotPlugEventExist() == _TRUE)
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    if((ScalerTypeCGetCcAttach(_D0_INPUT_PORT) == _TYPE_C_ATTACH) && (ScalerTypeCRx0PdGetSRCCapSentStatus() == _FALSE) && (ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC))
    {
        return _TRUE;
    }
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON)
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
    if(GET_TYPE_C_5400_LENOVO_ALT_MODE_URGENT_EVENT() == _TRUE)
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif
#endif
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Urgent Event Occured Flag
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerSyncGetUrgentEventFlg(void)
{
    return GET_URGENT_EVENT_OCCUR_FLG();
}

//--------------------------------------------------
// Description  : Clear Urgent Event Occured Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncClrUrgentEventFlg(void)
{
    CLR_URGENT_EVENT_OCCUR_FLG();
}
#endif // End of #if(_URGENT_EVENT_CHECK_MODE == _ON)

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS DDC Debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void ScalerSyncDdcDetectDebounce_EXINT1(void) using 2
{
    WORD usDebounceCnt = 0;

    // Debounce 300us
    for(usDebounceCnt = 0; usDebounceCnt < g_usDDCDebounceCnt; usDebounceCnt++) {};
}
#pragma restore

//--------------------------------------------------
// Description  : TMDS Power Saving Detect DDC Handshake
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerSyncDdcDetect_EXINT1(void) using 2
{
#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC0)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC0)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC0)))

    // DDC0 Detect SCL Toggle
    if((MCU_FFE4_DDC0_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        ScalerSyncDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 30us
        DELAY_30US_EXINT();

        // Double check SCL Toggle again
        if((MCU_FFE4_DDC0_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

#if((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC0))
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
            {
                SET_TMDS_RX0_DDC_DETECTED();
            }
#elif((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC0))
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                SET_TMDS_RX1_DDC_DETECTED();
            }
#elif((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC0))
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                SET_TMDS_RX2_DDC_DETECTED();
            }
#endif

            return _TRUE;
        }
    }
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC1)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC1)))

    // DDC1 Detect SCL Toggle
    if((MCU_FFE5_DDC1_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        ScalerSyncDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 30us
        DELAY_30US_EXINT();

        // Double check SCL Toggle again
        if((MCU_FFE5_DDC1_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

#if((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC1))
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
            {
                SET_TMDS_RX0_DDC_DETECTED();
            }
#elif((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1))
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                SET_TMDS_RX1_DDC_DETECTED();
            }
#elif((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC1))
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                SET_TMDS_RX2_DDC_DETECTED();
            }
#endif
            return _TRUE;
        }
    }
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC2)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC2)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC2)))

    // DDC2 Detect SCL Toggle
    if((MCU_FE69_DDC2_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        ScalerSyncDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 30us
        DELAY_30US_EXINT();

        // Double check SCL Toggle again
        if((MCU_FE69_DDC2_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE69_DDC2_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

#if((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC2))
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
            {
                SET_TMDS_RX0_DDC_DETECTED();
            }
#elif((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC2))
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                SET_TMDS_RX1_DDC_DETECTED();
            }
#elif((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC2))
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                SET_TMDS_RX2_DDC_DETECTED();
            }
#endif
            return _TRUE;
        }
    }
#endif

#if((_D3_TMDS_SUPPORT == _ON) && (_D3_DDC_CHANNEL_SEL == _DDC3))

    // DDC3 Detect SCL Toggle
    if((MCU_FE72_DDC3_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        ScalerSyncDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        MCU_FE72_DDC3_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 30us
        DELAY_30US_EXINT();

        // Double check SCL Toggle again
        if((MCU_FE72_DDC3_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE72_DDC3_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE72_DDC3_EDID_IRQ |= _BIT2;

            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                SET_TMDS_RX3_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D4_TMDS_SUPPORT == _ON) && (_D4_DDC_CHANNEL_SEL == _DDC4))

    // DDC4 Detect SCL Toggle
    if((MCU_FE7B_DDC4_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        ScalerSyncDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 30us
        DELAY_30US_EXINT();

        // Double check SCL Toggle again
        if((MCU_FE7B_DDC4_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE7B_DDC4_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;

            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                SET_TMDS_RX4_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D5_TMDS_SUPPORT == _ON) && (_D5_DDC_CHANNEL_SEL == _DDC5))

    // DDC5 Detect SCL Toggle
    if((MCU_FE84_DDC5_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        ScalerSyncDdcDetectDebounce_EXINT1();

        // Clear SCL Toggle
        MCU_FE84_DDC5_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 30us
        DELAY_30US_EXINT();

        // Double check SCL Toggle again
        if((MCU_FE84_DDC5_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE84_DDC5_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE84_DDC5_EDID_IRQ |= _BIT2;

            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
            {
                SET_TMDS_RX5_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSScanInitial(BYTE ucInputPort)
{
    // Set Power normal DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_NORMAL;

    ScalerTMDSInitial(ucInputPort);

    ScalerTMDSInterruptInitial(ucInputPort);
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS EDID Switch
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSEdidSwitch(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
        // For User, DVI and DUAL_DVI Port can not pull HPD
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        case _D0_INPUT_PORT:

            if(GET_D0_CABLE_STATUS() == _TRUE)
            {
                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_EDID_SWITCH);
            }
            break;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        case _D1_INPUT_PORT:

            if(GET_D1_CABLE_STATUS() == _TRUE)
            {
                SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_EDID_SWITCH);
            }
            break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        case _D2_INPUT_PORT:

            if(GET_D2_CABLE_STATUS() == _TRUE)
            {
                SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_EDID_SWITCH);
            }
            break;
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        case _D3_INPUT_PORT:

            if(GET_D3_CABLE_STATUS() == _TRUE)
            {
                SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_EDID_SWITCH);
            }
            break;
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        case _D4_INPUT_PORT:

            if(GET_D4_CABLE_STATUS() == _TRUE)
            {
                SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_EDID_SWITCH);
            }
            break;
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        case _D5_INPUT_PORT:

            if(GET_D5_CABLE_STATUS() == _TRUE)
            {
                SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_EDID_SWITCH);
            }
            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DDC channel Idle
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerSyncHDMIDdcCheckBusy(BYTE ucInputPort, EnumTMDSDdcDebounceType enumTmdsDdcDebounceType, BYTE ucDebounceTimeScale, WORD usDebounceTimePeriod)
{
    WORD ustemp = 0;

    switch(ucInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                // Disable SCL Toggle IRQ
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT3;
                MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif

#if(_D0_DDC_CHANNEL_SEL == _DDC1)
                // Disable SCL Toggle IRQ
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT3;
                MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif

#if(_D0_DDC_CHANNEL_SEL == _DDC2)
                // Disable SCL Toggle IRQ
                MCU_FE69_DDC2_EDID_IRQ &= ~_BIT3;
                MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif
            }
            return _TRUE;
            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                // Disable SCL Toggle IRQ
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT3;
                MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif

#if(_D1_DDC_CHANNEL_SEL == _DDC1)
                // Disable SCL Toggle IRQ
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT3;
                MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif

#if(_D1_DDC_CHANNEL_SEL == _DDC2)
                // Disable SCL Toggle IRQ
                MCU_FE69_DDC2_EDID_IRQ &= ~_BIT3;
                MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif
            }
            return _TRUE;
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                // Disable SCL Toggle IRQ
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT3;
                MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif

#if(_D2_DDC_CHANNEL_SEL == _DDC1)
                // Disable SCL Toggle IRQ
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT3;
                MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif

#if(_D2_DDC_CHANNEL_SEL == _DDC2)
                // Disable SCL Toggle IRQ
                MCU_FE69_DDC2_EDID_IRQ &= ~_BIT3;
                MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
#endif
            }
            return _TRUE;
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FE72_DDC3_EDID_IRQ &= ~_BIT3;
                MCU_FE72_DDC3_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FE72_DDC3_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE72_DDC3_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FE72_DDC3_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE72_DDC3_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
            }
            return _TRUE;
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FE7B_DDC4_EDID_IRQ &= ~_BIT3;
                MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FE7B_DDC4_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FE7B_DDC4_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
            }
            return _TRUE;
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FE84_DDC5_EDID_IRQ &= ~_BIT3;
                MCU_FE84_DDC5_EDID_IRQ |= _BIT2;

                if(enumTmdsDdcDebounceType == _DELAY_30US_TIMESCALE)
                {
                    // Set a Polling Duration: 30us*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay 30us
                        DELAY_30US();

                        if((MCU_FE84_DDC5_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(enumTmdsDdcDebounceType == _DELAY_XMS_TIMESCALE)
                {
                    // Set a Polling Duration: ucDebounceTimeScale(ms)*usDebounceTimePeriod
                    for(ustemp = 0; ustemp < usDebounceTimePeriod; ustemp++)
                    {
                        // Delay (ucDebounceTimeScale) ms for IIC 100k
                        ScalerTimerDelayXms(ucDebounceTimeScale);

                        if((MCU_FE84_DDC5_EDID_IRQ & _BIT2) == _BIT2)
                        {
                            MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
            }
            return _TRUE;
            break;
#endif

        default:

            return _TRUE;
            break;
    }
    return _TRUE;
}

#endif // End of #if(_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS HPD Toggle Process
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSHPDToggleProc(void)
{
    BYTE ucI = 0;
    BYTE ucPortNum = 0;

    StructTmdsHpdSequence pstTmdsHpdSeq[] =
    {
        // dummy Input_Port, HPD_Time
        {_NO_INPUT_PORT, _TMDS_HPD_TIME_NONE},

#if(_D0_TMDS_SUPPORT == _ON)
        {_NO_INPUT_PORT, _TMDS_HPD_TIME_NONE},
#endif
#if(_D1_TMDS_SUPPORT == _ON)
        {_NO_INPUT_PORT, _TMDS_HPD_TIME_NONE},
#endif
#if(_D2_TMDS_SUPPORT == _ON)
        {_NO_INPUT_PORT, _TMDS_HPD_TIME_NONE},
#endif
#if(_D3_TMDS_SUPPORT == _ON)
        {_NO_INPUT_PORT, _TMDS_HPD_TIME_NONE},
#endif
#if(_D4_TMDS_SUPPORT == _ON)
        {_NO_INPUT_PORT, _TMDS_HPD_TIME_NONE},
#endif
#if(_D5_TMDS_SUPPORT == _ON)
        {_NO_INPUT_PORT, _TMDS_HPD_TIME_NONE},
#endif
    };

#if(_D0_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        pstTmdsHpdSeq[1 + ucPortNum].enumPort = _D0_INPUT_PORT;

        if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        ScalerTMDSBeforeHotPlugEventProc(_D0_INPUT_PORT);

        ucPortNum ++;
        CLR_TMDS_RX0_HPD_TRIGGER_EVENT();
    }
#endif

#if(_D1_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        pstTmdsHpdSeq[1 + ucPortNum].enumPort = _D1_INPUT_PORT;

        if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        ScalerTMDSBeforeHotPlugEventProc(_D1_INPUT_PORT);

        ucPortNum ++;
        CLR_TMDS_RX1_HPD_TRIGGER_EVENT();
    }
#endif

#if(_D2_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        pstTmdsHpdSeq[1 + ucPortNum].enumPort = _D2_INPUT_PORT;

        if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        ScalerTMDSBeforeHotPlugEventProc(_D2_INPUT_PORT);

        ucPortNum ++;
        CLR_TMDS_RX2_HPD_TRIGGER_EVENT();
    }
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX3_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        pstTmdsHpdSeq[1 + ucPortNum].enumPort = _D3_INPUT_PORT;

        if(GET_TMDS_RX3_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_RX3_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if(GET_TMDS_RX3_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        ScalerTMDSBeforeHotPlugEventProc(_D3_INPUT_PORT);

        ucPortNum ++;
        CLR_TMDS_RX3_HPD_TRIGGER_EVENT();
    }
#endif

#if(_D4_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        pstTmdsHpdSeq[1 + ucPortNum].enumPort = _D4_INPUT_PORT;

        if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        ScalerTMDSBeforeHotPlugEventProc(_D4_INPUT_PORT);

        ucPortNum ++;
        CLR_TMDS_RX4_HPD_TRIGGER_EVENT();
    }
#endif

#if(_D5_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        pstTmdsHpdSeq[1 + ucPortNum].enumPort = _D5_INPUT_PORT;

        if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }
        else if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_HDCP_2_2_HPD_TIME;
        }
        else if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() == _TMDS_HPD_EDID_SWITCH)
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = _TMDS_EDID_SWITCH_HPD_TIME;
        }
        else
        {
            pstTmdsHpdSeq[1 + ucPortNum].usHpdTime = GET_HDMI_HOTPLUG_TIME();
        }

        ScalerTMDSBeforeHotPlugEventProc(_D5_INPUT_PORT);

        ucPortNum ++;
        CLR_TMDS_RX5_HPD_TRIGGER_EVENT();
    }
#endif

    if(ucPortNum == 0)
    {
        return;
    }

    // Bubble sort for reorder squence (HPD time short -> long)
    for(pData[0] = 1; pData[0] < ucPortNum; pData[0] ++)
    {
        for(pData[1] = 1; pData[1] <= (ucPortNum - pData[0]); pData[1] ++)
        {
            if(pstTmdsHpdSeq[pData[1]].usHpdTime > pstTmdsHpdSeq[pData[1] + 1].usHpdTime)
            {
                pstTmdsHpdSeq[0] = pstTmdsHpdSeq[pData[1]];
                pstTmdsHpdSeq[pData[1]] = pstTmdsHpdSeq[pData[1] + 1];
                pstTmdsHpdSeq[pData[1] + 1] = pstTmdsHpdSeq[0];
            }
        }
    }

    // Reset the dummy seq time for first HPD delay calculation
    pstTmdsHpdSeq[0].usHpdTime = 0;

    // Low Process
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
        {
            // Skip low process of this turn
            continue;
        }

        switch(pstTmdsHpdSeq[ucI].enumPort)
        {
#if(_D0_TMDS_SUPPORT == _ON)

            case _D0_INPUT_PORT:

                ScalerTMDSHotPlugLowProc(_D0_INPUT_PORT);
                break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)

            case _D1_INPUT_PORT:

                ScalerTMDSHotPlugLowProc(_D1_INPUT_PORT);
                break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)

            case _D2_INPUT_PORT:

                ScalerTMDSHotPlugLowProc(_D2_INPUT_PORT);
                break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)

            case _D3_INPUT_PORT:

                ScalerTMDSHotPlugLowProc(_D3_INPUT_PORT);
                break;
#endif

#if(_D4_TMDS_SUPPORT == _ON)

            case _D4_INPUT_PORT:

                ScalerTMDSHotPlugLowProc(_D4_INPUT_PORT);
                break;
#endif

#if(_D5_TMDS_SUPPORT == _ON)

            case _D5_INPUT_PORT:

                ScalerTMDSHotPlugLowProc(_D5_INPUT_PORT);
                break;
#endif

            default:
                break;
        }
    }

    // High Process
    for(ucI = 1; ucI <= ucPortNum; ucI ++)
    {
        if(pstTmdsHpdSeq[ucI].usHpdTime == _TMDS_HPD_TIME_NONE)
        {
            // Skip high process of this turn
            continue;
        }

        switch(pstTmdsHpdSeq[ucI].enumPort)
        {
#if(_D0_TMDS_SUPPORT == _ON)

            case _D0_INPUT_PORT:

                ScalerTMDSHotPlugHighProc(_D0_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                ScalerTMDSAfterHotPlugEventProc(_D0_INPUT_PORT);
                break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)

            case _D1_INPUT_PORT:

                ScalerTMDSHotPlugHighProc(_D1_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                ScalerTMDSAfterHotPlugEventProc(_D1_INPUT_PORT);
                break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)

            case _D2_INPUT_PORT:

                ScalerTMDSHotPlugHighProc(_D2_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                ScalerTMDSAfterHotPlugEventProc(_D2_INPUT_PORT);
                break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)

            case _D3_INPUT_PORT:

                ScalerTMDSHotPlugHighProc(_D3_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                ScalerTMDSAfterHotPlugEventProc(_D3_INPUT_PORT);
                break;
#endif

#if(_D4_TMDS_SUPPORT == _ON)

            case _D4_INPUT_PORT:

                ScalerTMDSHotPlugHighProc(_D4_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                ScalerTMDSAfterHotPlugEventProc(_D4_INPUT_PORT);
                break;
#endif

#if(_D5_TMDS_SUPPORT == _ON)

            case _D5_INPUT_PORT:

                ScalerTMDSHotPlugHighProc(_D5_INPUT_PORT, pstTmdsHpdSeq[ucI].usHpdTime - pstTmdsHpdSeq[ucI - 1].usHpdTime);

                ScalerTMDSAfterHotPlugEventProc(_D5_INPUT_PORT);
                break;
#endif

            default:
                break;
        }
    }
}
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_MHL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MHL VBus Power Exist
// Input Value  : None
// Output Value : _TRUE : VBUS Power Exist
//--------------------------------------------------
bit ScalerSyncMHLVBusPowerExist(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    if(PCB_GET_D0_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(PCB_GET_D1_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    if(PCB_GET_D2_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    if(PCB_GET_D3_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(PCB_GET_D4_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(PCB_GET_D5_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Process Required to be Performed for Active State
// Input Value  : Current Source Type
// Output Value : None
//--------------------------------------------------
void ScalerSyncActiveProc(BYTE ucSourceType)
{
#if(_DDR_BURN_IN_TEST == _ON)
    ScalerSyncDDRBurnInCRCTest();
#endif

    switch(ucSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            break;
#endif

#if(_DVI_SUPPORT == _ON)
        case _SOURCE_DVI:
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_HDMI:

            ScalerTMDSHdmiAVMuteProc();

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Sync reset Process for Mode Reset
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncResetProc(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

#if(_DP_SUPPORT == _ON)
    ScalerDpResetProc();
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_HDMI_SUPPORT == _ON)
    ScalerTMDSHdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);
#endif

    ScalerTMDSResetProc();
#endif

#if(_FREESYNC_SUPPORT == _ON)
    CLR_FREESYNC_ENABLED();
    SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(_FALSE);
#endif

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    ScalerSyncDpHDRReset();
#endif

#if(_HDR10_SUPPORT == _ON)
    CLR_HDR10_INFO_DATA();
    CLR_HDR10_SETTING_DATA();
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    CLR_FREESYNC_II_INFO_DATA();
    CLR_FREESYNC_II_SETTING_DATA();
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
    // Turn Off Color Functions
    if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
    {
        ScalerSyncDigitalClrColorimetryChanged(ucInputPort);
        ScalerSyncDigitalClrColorimetryExtChanged(ucInputPort);
        ScalerSyncDigitalClrQuantizationChanged(ucInputPort);
    }
#endif
}

//--------------------------------------------------
// Description  : Power Process for Interface
// Input Value  : Power Action
// Output Value : None
//--------------------------------------------------
void ScalerSyncPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

#if(_ADC_SUPPORT == _ON)
            ScalerSyncAdcPowerProc(enumPowerAction);
#endif

            // GDI Bandgap Enable
            ScalerGDIPhyBandgap(_ON);

#if(_DP_SUPPORT == _ON)
            ScalerDpPowerSwitch(enumPowerAction);
#endif

#if(_FREESYNC_SUPPORT == _ON)
            ScalerSyncFREESYNCTestPinEnable();
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_PS_TO_NORMAL)
            {
                ScalerTMDSClkLaneZ0StopToggle();
            }
#endif

            if((enumPowerAction == _POWER_ACTION_PS_TO_NORMAL) || (enumPowerAction == _POWER_ACTION_OFF_TO_FAKE_OFF))
            {
#if(_DIGITAL_PORT_SUPPORT == _ON)
                ScalerSyncGDIPowerProc(enumPowerAction);
#endif
            }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            // Clear Urgent Event Occured Flag When System Flow Is Runing to Normal
            ScalerSyncClrUrgentEventFlg();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if(_ADC_SUPPORT == _ON)
            ScalerSyncAdcPowerProc(enumPowerAction);
#endif

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_DP_SUPPORT == _ON)
            ScalerDpPowerSwitch(enumPowerAction);
#elif(_HDMI_CEC_SUPPORT == _OFF)
            ScalerGDIPhyBandgap(_OFF);
#endif

#if(_EMBEDDED_DP_TX_SUPPORT == _ON)
            ScalerSyncEmbeddedDpTxPowerProc(enumPowerAction);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
            ScalerSyncGDIPowerProc(enumPowerAction);
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
            ScalerTMDSClkLaneZ0StartToggle();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_ADC_SUPPORT == _ON)
            ScalerSyncAdcPowerProc(enumPowerAction);
#endif

#if(_MHL_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_AC_ON_TO_OFF)
            {
                ScalerGDIPhyBandgap(_ON);
            }
#endif

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_EMBEDDED_DP_TX_SUPPORT == _ON)
            ScalerSyncEmbeddedDpTxPowerProc(enumPowerAction);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
            ScalerSyncGDIPowerProc(enumPowerAction);
#endif

#if(_DP_SUPPORT == _ON)
            ScalerSyncDpCheckHdcpEnable();
            ScalerDpPowerSwitch(enumPowerAction);
#elif(_HDMI_CEC_SUPPORT == _OFF)
            ScalerGDIPhyBandgap(_OFF);
#endif

#if((_DP_SUPPORT != _ON) && (_DVI_SUPPORT != _ON))
            EX0 = 0;
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_PS_TO_OFF)
            {
                ScalerTMDSClkLaneZ0StopToggle();
            }
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

#if(_DP_SUPPORT == _ON)
            ScalerDpPowerSwitch(enumPowerAction);
#endif

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Switch Between Interfaces
// Input Value  : Current Input Port, Target Source Type, Source Search Mode
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceSwitch(BYTE ucInputPort, BYTE ucPortType, BYTE ucSourceSearchDelayMode)
{
    ucSourceSearchDelayMode = ucSourceSearchDelayMode;
    ucPortType = ucPortType;

#if(_ADC_SUPPORT == _ON)
    if(ucPortType != _PORT_VGA)
    {
        ScalerSyncAdcApllPowerDown();
    }
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    if((ucPortType != _PORT_DVI) && (ucPortType != _PORT_HDMI) &&
       (ucPortType != _PORT_MHL) && (ucPortType != _PORT_DUAL_DVI))
    {
        ScalerTMDSFreqDetectDisable();
    }
#endif

#if(_DP_SUPPORT == _ON)
    ScalerDpFakeLinkTrainingSetting(ucInputPort);
#endif

    switch(ucInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

        case _A0_INPUT_PORT:
        case _A1_INPUT_PORT:
        case _A2_INPUT_PORT:

            if(ucInputPort == _A0_INPUT_PORT)
            {
                PCB_VGA_SWITCH_A0();
            }
            else if(ucInputPort == _A1_INPUT_PORT)
            {
                PCB_VGA_SWITCH_A1();
            }
            else if(ucInputPort == _A2_INPUT_PORT)
            {
                PCB_VGA_SWITCH_A2();
            }

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }

            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_HDCP_ARBITER_SUPPORT == _ON))
                ScalerDpHdcpCapSwitch(_D0_INPUT_PORT);
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
            {
                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX0_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);
            }

#else // Else of #if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE) || (GET_TMDS_RX0_PS_WAKEUP_HPD_TOGGLE() == _TRUE)))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D0_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);
                    CLR_TMDS_RX0_PS_WAKEUP_HPD_TOGGLE();
                }
            }
#endif

#endif // End of #if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D0_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

        case _D1_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_HDCP_ARBITER_SUPPORT == _ON))
                ScalerDpHdcpCapSwitch(_D1_INPUT_PORT);
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
            {
                SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX1_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);
            }

#else // Else of #if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE) || (GET_TMDS_RX1_PS_WAKEUP_HPD_TOGGLE() == _TRUE)))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D1_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);
                    CLR_TMDS_RX1_PS_WAKEUP_HPD_TOGGLE();
                }
            }
#endif

#endif // End of #if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D1_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

        case _D2_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_HDCP_ARBITER_SUPPORT == _ON))
                ScalerDpHdcpCapSwitch(_D2_INPUT_PORT);
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
            {
                SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX2_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);
            }

#else // Else of #if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE) || (GET_TMDS_RX2_PS_WAKEUP_HPD_TOGGLE() == _TRUE)))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D2_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);
                    CLR_TMDS_RX2_PS_WAKEUP_HPD_TOGGLE();
                }
            }
#endif

#endif // End of #if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D2_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#endif
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

        case _D3_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
            {
                SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX3_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);
            }

#else // Else of #if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE) || (GET_TMDS_RX3_PS_WAKEUP_HPD_TOGGLE() == _TRUE)))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D3_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);
                    CLR_TMDS_RX3_PS_WAKEUP_HPD_TOGGLE();
                }
            }
#endif

#endif // End of #if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D3_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D3_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D3_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#endif
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

        case _D4_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
            {
                SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX4_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);
            }

#else // Else of #if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE) || (GET_TMDS_RX4_PS_WAKEUP_HPD_TOGGLE() == _TRUE)))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D4_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);
                    CLR_TMDS_RX4_PS_WAKEUP_HPD_TOGGLE();
                }
            }
#endif

#endif // End of #if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

            ScalerGDIPhyDigitalPhySwitch(_D4_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#endif
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

        case _D5_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
            {
                SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX5_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);
            }

#else // Else of #if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && ((GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE) || (GET_TMDS_RX5_PS_WAKEUP_HPD_TOGGLE() == _TRUE)))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D5_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);
                    CLR_TMDS_RX5_PS_WAKEUP_HPD_TOGGLE();
                }
            }
#endif

#endif // End of #if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

            ScalerGDIPhyDigitalPhySwitch(_D5_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

            break;
#endif
        default:
            break;
    }
}

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch Between Interfaces
// Input Value  : Current Input Port, Current Input Port Type, Background Detct Port, Detect Source Type, Source Search Mode
// Output Value : None
//--------------------------------------------------
void ScalerSyncBgInterfaceSwitch(BYTE ucInputPort, BYTE ucInputPortType, BYTE ucDetectPort, BYTE ucDetectPortType, BYTE ucSourceSearchDelayMode)
{
    ucSourceSearchDelayMode = ucSourceSearchDelayMode;
    ucDetectPortType = ucDetectPortType;

#if(_ADC_SUPPORT == _ON)
    if((ucDetectPortType != _PORT_VGA) && (ucInputPortType != _PORT_VGA))
    {
        ScalerSyncAdcApllPowerDown();
    }
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    if((ucDetectPortType != _PORT_DVI) && (ucDetectPortType != _PORT_HDMI) &&
       (ucDetectPortType != _PORT_MHL) && (ucDetectPortType != _PORT_DUAL_DVI) &&
       (ucInputPortType != _PORT_DVI) && (ucInputPortType != _PORT_HDMI) &&
       (ucInputPortType != _PORT_MHL) && (ucInputPortType != _PORT_DUAL_DVI))
    {
        ScalerTMDSFreqDetectDisable();
    }
#endif

    switch(ucDetectPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

        case _A0_INPUT_PORT:
        case _A1_INPUT_PORT:
        case _A2_INPUT_PORT:

            if(ucDetectPort == _A0_INPUT_PORT)
            {
                PCB_VGA_SWITCH_A0();
            }
            else if(ucDetectPort == _A1_INPUT_PORT)
            {
                PCB_VGA_SWITCH_A1();
            }
            else if(ucDetectPort == _A2_INPUT_PORT)
            {
                PCB_VGA_SWITCH_A2();
            }

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE) && (ucInputPort != _D0_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE) && (ucInputPort != _D1_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE) && (ucInputPort != _D2_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE) && (ucInputPort != _D3_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE) && (ucInputPort != _D4_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE) && (ucInputPort != _D5_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_NORMAL_TO_OFF);
                }
#endif
            }

            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE) && (ucInputPort != _D1_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE) && (ucInputPort != _D2_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE) && (ucInputPort != _D3_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE) && (ucInputPort != _D4_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE) && (ucInputPort != _D5_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
            {
                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX0_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);
            }

#else // Else of #if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D0_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);
                }
            }
#endif

#endif // End of #if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D0_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D0_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

        case _D1_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE) && (ucInputPort != _D0_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE) && (ucInputPort != _D2_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE) && (ucInputPort != _D3_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE) && (ucInputPort != _D4_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE) && (ucInputPort != _D5_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
            {
                SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX1_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);
            }

#else // Else of #if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D1_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);
                }
            }
#endif

#endif // End of #if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D1_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

        case _D2_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE) && (ucInputPort != _D0_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

                if((GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE) && (ucInputPort != _D1_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE) && (ucInputPort != _D3_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE) && (ucInputPort != _D4_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE) && (ucInputPort != _D5_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
            {
                SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX2_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);
            }

#else // Else of #if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D2_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);
                }
            }
#endif

#endif // End of #if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D2_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D2_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#endif
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

        case _D3_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE) && (ucInputPort != _D0_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE) && (ucInputPort != _D1_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE) && (ucInputPort != _D2_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE) && (ucInputPort != _D4_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE) && (ucInputPort != _D5_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

#if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
            {
                SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX3_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);
            }

#else // Else of #if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D3_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);
                }
            }
#endif

#endif // End of #if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _OFF)

            ScalerGDIPhyDigitalPhySwitch(_D3_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
            {
#if(_DP_HDMI_COMPATIBLE_MODE == _ON)

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
                if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D3_HDMI_5V_STATUS() == _TRUE))
                {
                    PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                    PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#elif(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
                {
                    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D3_HDMI_5V_STATUS() == _TRUE))
                    {
                        PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
                        ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                        ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
                        PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
                    }
                    else
                    {
                        ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                    }
                }
                else
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
                }
#else
                ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
#endif

#else // Else of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)

                ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);

#endif // End of #if(_DP_HDMI_COMPATIBLE_MODE == _ON)
            }

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#endif
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

        case _D4_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE) && (ucInputPort != _D0_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE) && (ucInputPort != _D1_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE) && (ucInputPort != _D2_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE) && (ucInputPort != _D3_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE) && (ucInputPort != _D5_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
            {
                SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX4_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);
            }

#else // Else of #if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D4_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);
                }
            }
#endif

#endif // End of #if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

            ScalerGDIPhyDigitalPhySwitch(_D4_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }
#endif
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

        case _D5_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE) && (ucInputPort != _D0_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D0_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE) && (ucInputPort != _D1_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D1_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if((GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE) && (ucInputPort != _D2_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D2_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE) && (ucInputPort != _D3_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D3_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if((GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE) && (ucInputPort != _D4_INPUT_PORT))
                {
                    ScalerGDIPhyPowerProc(_D4_INPUT_PORT, _POWER_ACTION_SWITCH_INTERFACE_TO_OFF);
                }
#endif
            }

#if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
            {
                SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);
            }
#endif
            if(GET_TMDS_RX5_TOGGLE_Z0_EVENT() == _TRUE)
            {
                SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
                ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);
            }

#else // Else of #if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE))
            {
#if(_TMDS_DDC_CHECK_BUSY_BEFORE_HPD == _ON)
                if(ScalerSyncHDMIDdcCheckBusy(_D5_INPUT_PORT, _DELAY_XMS_TIMESCALE, 25, 8) == _FALSE)
#endif
                {
                    SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                    ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);
                }
            }
#endif

#endif // End of #if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

            ScalerGDIPhyDigitalPhySwitch(_D5_INPUT_PORT);

            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
            {
                ScalerGDIPhyPowerProc(_D5_INPUT_PORT, _POWER_ACTION_OFF_TO_NORMAL);
            }

            break;
#endif
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Set DDC channel Force nack
// Input Value  : bSelect --> _ON: force nack
// Output Value : NONE
//--------------------------------------------------
void ScalerSyncSetDdcForceNack(BYTE ucInputPort, bit bSelect)
{
    if(bSelect == _ON)
    {
        switch(ucInputPort)
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:

#if(_HW_PC99_VGADDC2_SUPPORT == _ON)
                if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
                {
                    // ADC_DDC2 Force Nack
                    MCU_FD37_ADC_DDC2_EDID_IRQ |= _BIT5;
                }
                else
#endif
                {
                    // A0 DDC force Nack
                    MCU_FFE7_VGA_EDID_IRQ |= _BIT5;
                }
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC0 force nack
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
#endif
                }
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC1 force nack
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
#endif
                }
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC2 force nack
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
#endif
                }
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC3 force nack
                    MCU_FE72_DDC3_EDID_IRQ |= _BIT5;
                }

                break;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC4 force nack
                    MCU_FE7B_DDC4_EDID_IRQ |= _BIT5;
                }

                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC5 force nack
                    MCU_FE84_DDC5_EDID_IRQ |= _BIT5;
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
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:

                // A0 DDC nack off
                MCU_FFE7_VGA_EDID_IRQ &= ~_BIT5;

#if(_HW_PC99_VGADDC2_SUPPORT == _ON)
                // ADC_DDC2 nack off
                MCU_FD37_ADC_DDC2_EDID_IRQ &= ~_BIT5;
#endif
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D0_AUX_DDC_CHANNEL == _D0_AUX_MAP_DDC0_PIN)

                // Disable DDC0 Force Nack
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT2;

#elif(_D0_AUX_DDC_CHANNEL == _D0_AUX_MAP_DDC1_PIN)

                // Disable DDC1 Force Nack
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control for Link Layer CTS
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT2;

#elif(_D0_AUX_DDC_CHANNEL == _D0_AUX_MAP_DDC2_PIN)

                // Disable DDC2 Force Nack
                MCU_FE69_DDC2_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control for Link Layer CTS
                MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT2;
#endif

#elif(_D0_TMDS_SUPPORT == _ON)

#if((_D0_INPUT_PORT_TYPE != _D0_MHL_PORT) && (_D0_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384))

                // Enable Segment Control
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT2;
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT2;
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT2;
#endif

#elif(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC nack off
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ &= ~_BIT5;
#endif
                }
#endif
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D1_AUX_DDC_CHANNEL == _D1_AUX_MAP_DDC0_PIN)
                // Disable DDC0 Force Nack
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT2;

#elif(_D1_AUX_DDC_CHANNEL == _D1_AUX_MAP_DDC1_PIN)
                // Disable DDC1 Force Nack
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control for Link Layer CTS
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT2;

#elif(_D1_AUX_DDC_CHANNEL == _D1_AUX_MAP_DDC2_PIN)
                // Disable DDC2 Force Nack
                MCU_FE69_DDC2_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control for Link Layer CTS
                MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT2;
#endif

#elif(_D1_TMDS_SUPPORT == _ON)

#if((_D1_INPUT_PORT_TYPE != _D1_MHL_PORT) && (_D1_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384))

                // Enable Segment Control
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT2;
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT2;
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT2;
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC nack off
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ &= ~_BIT5;
#endif
                }
#endif
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if(_D2_AUX_DDC_CHANNEL == _D2_AUX_MAP_DDC0_PIN)

                // Disable DDC0 Force Nack
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT2;

#elif(_D2_AUX_DDC_CHANNEL == _D2_AUX_MAP_DDC1_PIN)

                // Disable DDC1 Force Nack
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT2;

#elif(_D2_AUX_DDC_CHANNEL == _D2_AUX_MAP_DDC2_PIN)

                // Disable DDC2 Force Nack
                MCU_FE69_DDC2_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control
                MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT2;
#endif

#elif(_D2_TMDS_SUPPORT == _ON)

#if((_D2_INPUT_PORT_TYPE != _D2_MHL_PORT) && (_D2_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384))

                // Enable Segment Control
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT2;
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT2;
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT2;
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC nack off
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                    MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                    MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                    MCU_FE69_DDC2_EDID_IRQ &= ~_BIT5;
#endif
                }
#endif
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:

#if((_D3_INPUT_PORT_TYPE != _D3_MHL_PORT) && (_D3_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384))
                // Enable Segment Control
                MCU_FE6F_DDC3_DDC_CONTROL_2 |= _BIT2;
#elif(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC3 nack off
                    MCU_FE72_DDC3_EDID_IRQ &= ~_BIT5;
                }

                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:

#if((_D4_INPUT_PORT_TYPE != _D4_MHL_PORT) && (_D4_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384))
                // Enable Segment Control
                MCU_FE78_DDC4_DDC_CONTROL_2 |= _BIT2;
#elif(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC4 nack off
                    MCU_FE7B_DDC4_EDID_IRQ &= ~_BIT5;
                }

                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:

#if((_D5_INPUT_PORT_TYPE != _D5_MHL_PORT) && (_D5_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_384))
                // Enable Segment Control
                MCU_FE81_DDC5_DDC_CONTROL_2 |= _BIT2;
#elif(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC5 nack off
                    MCU_FE84_DDC5_EDID_IRQ &= ~_BIT5;
                }

                break;
#endif

            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Get DDC channel Force nack Status
// Input Value  : ucInputPort
// Output Value : _TRUE --> Force Nack State
//--------------------------------------------------
bit ScalerSyncGetDdcForceNackStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

        case _A0_INPUT_PORT:

#if(_HW_PC99_VGADDC2_SUPPORT == _ON)
            if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
            {
                if((MCU_FD37_ADC_DDC2_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if((MCU_FFE7_VGA_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }

            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

            if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // DDC0 force nack
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                if((MCU_FFE4_DDC0_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                if((MCU_FFE5_DDC1_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                if((MCU_FE69_DDC2_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#endif
            }
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

            if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // DDC1 force nack
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                if((MCU_FFE4_DDC0_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                if((MCU_FFE5_DDC1_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                if((MCU_FE69_DDC2_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#endif
            }
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

            if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // DDC2 force nack
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                if((MCU_FFE4_DDC0_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                if((MCU_FFE5_DDC1_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                if((MCU_FE69_DDC2_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#endif
            }
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

            if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                if((MCU_FE72_DDC3_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                if((MCU_FE7B_DDC4_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

            if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                if((MCU_FE84_DDC5_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

#if(((_D0_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF)) || ((_HDMI_SUPPORT == _ON) && (_TMDS_PAGE2_COMBO_EXIST == _ON)))
//--------------------------------------------------
// Description  : TMDS Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiVideoSetting(void)
{
    if(GET_HDMI_RX0_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx0("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx0("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx0("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx0("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx0("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx0("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx0("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx0("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx0("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx0("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx0("Get Pixel Repetition 6", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx0("Get Pixel Repetition 7", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx0("Get Pixel Repetition 8", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx0("Get Pixel Repetition 9", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx0("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx0HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx0HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx0SetPorchColor(GET_COLOR_SPACE());
}

//--------------------------------------------------
// Description  : TMDS Rx0 HDMI Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx0("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX0_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx0("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX0_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx0("Get Colorimetry YCC_ITUR_BT709", 0x00);

                SET_TMDS_RX0_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx0("Get Colorimetry Extended", 0x00);

                SET_TMDS_RX0_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx0HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX0_COLORIMETRY_PREVALUE(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_TMDS_RX0_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx0("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx0("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx0HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx0 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx0("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx0("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx0("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx0("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx0("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx0("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx0("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx0("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx0 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        SET_TMDS_RX0_QUANTIZATION_PREVALUE(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_TMDS_RX0_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx0("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx0("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx0("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx0("Get RGB LIMIT RANGE", 0x00);

                SET_TMDS_RX0_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx0("Get RGB FULL RANGE", 0x00);

                SET_TMDS_RX0_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx0("Get RGB DEFAULT RANGE", 0x00);

                SET_TMDS_RX0_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx0("Get RGB RESERVED RANGE", 0x00);

                SET_TMDS_RX0_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx0("Get RGB RANGE Error", 0x00);

                SET_TMDS_RX0_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx0 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx0HdmiColorInfoChanged(void)
{
    // Check Color Space
    if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE())
    {
        DebugMessageRx0("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_TMDS_RX0_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx0("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            BYTE pucTemp[2];

            pucTemp[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_TMDS_RX0_COLORIMETRY_PREVALUE();

            ScalerSyncTMDSRx0HdmiColorimetrySetting();

            if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_TMDS_RX0_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_TMDS_RX0_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx0("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    BYTE pucTemp[2];

                    pucTemp[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_TMDS_RX0_COLORIMETRY_EXT_PREVALUE();

                    ScalerSyncTMDSRx0HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_TMDS_RX0_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx0("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                BYTE pucTemp[2];

                pucTemp[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_TMDS_RX0_QUANTIZATION_PREVALUE();

                ScalerSyncTMDSRx0HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_TMDS_RX0_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_TMDS_RX0_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx0("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx0HdmiQuantizationSetting();

                SET_TMDS_RX0_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
//--------------------------------------------------
// Description  : TMDS Rx1 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiVideoSetting(void)
{
    if(GET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
#if(_D1_INPUT_PORT_TMDS_MAC_PAGE == _PAGE70)
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
#else
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));
#endif

        pData[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx1("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx1("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx1("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx1("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx1("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx1("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx1("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx1("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx1("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx1("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx1("Get Pixel Repetition 6", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx1("Get Pixel Repetition 7", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx1("Get Pixel Repetition 8", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx1("Get Pixel Repetition 9", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx1("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx1HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx1HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        if(GET_TMDS_RX1_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
#if(_D1_INPUT_PORT_TMDS_MAC_PAGE == _PAGE70)
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
#else
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
#endif
        }
        else
#endif

        {
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
#if(_D1_INPUT_PORT_TMDS_MAC_PAGE == _PAGE70)
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
#else
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
#endif
        }

        // Disable down sampling
#if(_D1_INPUT_PORT_TMDS_MAC_PAGE == _PAGE70)
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_50_PORT_PAGE70_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#else
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif

        SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx1SetPorchColor(GET_COLOR_SPACE());
}

//--------------------------------------------------
// Description  : TMDS Rx1 HDMI Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx1("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX1_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx1("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX1_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx1("Get Colorimetry 709", 0x00);

                SET_TMDS_RX1_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx1("Get Colorimetry Extended", 0x00);

                SET_TMDS_RX1_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx1HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX1_COLORIMETRY_PREVALUE(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_TMDS_RX1_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx1("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx1("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx1HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx1 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx1("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx1("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx1("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx1("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx1("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx1("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx1("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx1("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx1 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        SET_TMDS_RX1_QUANTIZATION_PREVALUE(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_TMDS_RX1_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx1("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx1("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx1("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx1("Get RGB LIMIT RANGE", 0x00);

                SET_TMDS_RX1_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx1("Get RGB FULL RANGE", 0x00);

                SET_TMDS_RX1_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx1("Get RGB DEFAULT RANGE", 0x00);

                SET_TMDS_RX1_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx1("Get RGB RESERVED RANGE", 0x00);

                SET_TMDS_RX1_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx1("Get RGB RANGE Error", 0x00);

                SET_TMDS_RX1_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx1 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx1HdmiColorInfoChanged(void)
{
    // Check Color Space
    if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE())
    {
        DebugMessageRx1("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_TMDS_RX1_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx1("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            BYTE pucTemp[2];

            pucTemp[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_TMDS_RX1_COLORIMETRY_PREVALUE();

            ScalerSyncTMDSRx1HdmiColorimetrySetting();

            if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_TMDS_RX1_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_TMDS_RX1_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx1("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    BYTE pucTemp[2];

                    pucTemp[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_TMDS_RX1_COLORIMETRY_EXT_PREVALUE();

                    ScalerSyncTMDSRx1HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_TMDS_RX1_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_TMDS_RX1_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_TMDS_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx1("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                BYTE pucTemp[2];

                pucTemp[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_TMDS_RX1_QUANTIZATION_PREVALUE();

                ScalerSyncTMDSRx1HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_TMDS_RX1_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_TMDS_RX1_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx1("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx1HdmiQuantizationSetting();

                SET_TMDS_RX1_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : TMDS Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiVideoSetting(void)
{
    if(GET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx2("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx2("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx2("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx2("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx2("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx2("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx2("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx2("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx2("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx2("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx2("Get Pixel Repetition 6", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx2("Get Pixel Repetition 7", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx2("Get Pixel Repetition 8", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx2("Get Pixel Repetition 9", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx2("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx2HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx2HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        if(GET_TMDS_RX2_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx2SetPorchColor(GET_COLOR_SPACE());
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx2 HDMI Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx2("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX2_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx2("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX2_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx2("Get Colorimetry 709", 0x00);

                SET_TMDS_RX2_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx2("Get Colorimetry Extended", 0x00);

                SET_TMDS_RX2_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx2HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX2_COLORIMETRY_PREVALUE(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_TMDS_RX2_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx2("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx2("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx2HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx2 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx2("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx2("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx2("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx2("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx2("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx2("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx2("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx2("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx2 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        SET_TMDS_RX2_QUANTIZATION_PREVALUE(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_TMDS_RX2_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx2("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx2("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx2("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx2("Get RGB LIMIT RANGE", 0x00);

                SET_TMDS_RX2_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx2("Get RGB FULL RANGE", 0x00);

                SET_TMDS_RX2_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx2("Get RGB DEFAULT RANGE", 0x00);

                SET_TMDS_RX2_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx2("Get RGB RESERVED RANGE", 0x00);

                SET_TMDS_RX2_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx2("Get RGB RANGE Error", 0x00);

                SET_TMDS_RX2_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx2 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx2HdmiColorInfoChanged(void)
{
    // Check Color Space
    if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE())
    {
        DebugMessageRx2("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_TMDS_RX2_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx2("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            BYTE pucTemp[2];

            pucTemp[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_TMDS_RX2_COLORIMETRY_PREVALUE();

            ScalerSyncTMDSRx2HdmiColorimetrySetting();

            if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_TMDS_RX2_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_TMDS_RX2_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx2("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    BYTE pucTemp[2];

                    pucTemp[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_TMDS_RX2_COLORIMETRY_EXT_PREVALUE();

                    ScalerSyncTMDSRx2HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_TMDS_RX2_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_TMDS_RX2_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_TMDS_RX2_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx2("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                BYTE pucTemp[2];

                pucTemp[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_TMDS_RX2_QUANTIZATION_PREVALUE();

                ScalerSyncTMDSRx2HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_TMDS_RX2_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_TMDS_RX2_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx2("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx2HdmiQuantizationSetting();

                SET_TMDS_RX2_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : TMDS Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiVideoSetting(void)
{
    if(GET_HDMI_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx3("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx3("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx3("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx3("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx3("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx3("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx3("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx3("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx3("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx3("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx3("Get Pixel Repetition 6", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx3("Get Pixel Repetition 7", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx3("Get Pixel Repetition 8", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx3("Get Pixel Repetition 9", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx3("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx3HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx3HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
        if(GET_TMDS_RX3_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx3SetPorchColor(GET_COLOR_SPACE());
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx3 HDMI Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx3("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx3("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx3("Get Colorimetry 709", 0x00);

                SET_TMDS_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx3("Get Colorimetry Extended", 0x00);

                SET_TMDS_RX3_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx3HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX3_COLORIMETRY_PREVALUE(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_TMDS_RX3_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx3("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx3("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx3HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx3 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx3("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx3("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx3("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx3("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx3("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx3("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx3("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx3("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx3 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        SET_TMDS_RX3_QUANTIZATION_PREVALUE(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_TMDS_RX3_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx3("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx3("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx3("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx3("Get RGB LIMIT RANGE", 0x00);

                SET_TMDS_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx3("Get RGB FULL RANGE", 0x00);

                SET_TMDS_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx3("Get RGB DEFAULT RANGE", 0x00);

                SET_TMDS_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx3("Get RGB RESERVED RANGE", 0x00);

                SET_TMDS_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx3("Get RGB RANGE Error", 0x00);

                SET_TMDS_RX3_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx3 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx3HdmiColorInfoChanged(void)
{
    // Check Color Space
    if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE())
    {
        DebugMessageRx3("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_TMDS_RX3_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx3("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            BYTE pucTemp[2];

            pucTemp[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_TMDS_RX3_COLORIMETRY_PREVALUE();

            ScalerSyncTMDSRx3HdmiColorimetrySetting();

            if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_TMDS_RX3_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_TMDS_RX3_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx3("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    BYTE pucTemp[2];

                    pucTemp[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_TMDS_RX3_COLORIMETRY_EXT_PREVALUE();

                    ScalerSyncTMDSRx3HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_TMDS_RX3_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_TMDS_RX3_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_TMDS_RX3_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx3("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                BYTE pucTemp[2];

                pucTemp[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_TMDS_RX3_QUANTIZATION_PREVALUE();

                ScalerSyncTMDSRx3HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_TMDS_RX3_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_TMDS_RX3_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx3("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx3HdmiQuantizationSetting();

                SET_TMDS_RX3_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : TMDS Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiVideoSetting(void)
{
    if(GET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx4("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx4("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx4("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx4("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx4("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx4("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx4("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx4("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx4("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx4("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx4("Get Pixel Repetition 6", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx4("Get Pixel Repetition 7", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx4("Get Pixel Repetition 8", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx4("Get Pixel Repetition 9", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx4("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx4HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx4HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
        if(GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx4SetPorchColor(GET_COLOR_SPACE());
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx4 HDMI Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx4("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx4("Get Colorimetry 709", 0x00);

                SET_TMDS_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("Get Colorimetry Extended", 0x00);

                SET_TMDS_RX4_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx4HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX4_COLORIMETRY_PREVALUE(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_TMDS_RX4_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx4HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx4 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx4("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx4("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx4("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx4("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx4 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        SET_TMDS_RX4_QUANTIZATION_PREVALUE(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_TMDS_RX4_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx4("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx4("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx4("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx4("Get RGB LIMIT RANGE", 0x00);

                SET_TMDS_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx4("Get RGB FULL RANGE", 0x00);

                SET_TMDS_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx4("Get RGB DEFAULT RANGE", 0x00);

                SET_TMDS_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx4("Get RGB RESERVED RANGE", 0x00);

                SET_TMDS_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx4("Get RGB RANGE Error", 0x00);

                SET_TMDS_RX4_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx4 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx4HdmiColorInfoChanged(void)
{
    // Check Color Space
    if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE())
    {
        DebugMessageRx4("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_TMDS_RX4_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx4("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            BYTE pucTemp[2];

            pucTemp[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_TMDS_RX4_COLORIMETRY_PREVALUE();

            ScalerSyncTMDSRx4HdmiColorimetrySetting();

            if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_TMDS_RX4_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_TMDS_RX4_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx4("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    BYTE pucTemp[2];

                    pucTemp[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_TMDS_RX4_COLORIMETRY_EXT_PREVALUE();

                    ScalerSyncTMDSRx4HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_TMDS_RX4_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_TMDS_RX4_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_TMDS_RX4_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx4("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                BYTE pucTemp[2];

                pucTemp[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_TMDS_RX4_QUANTIZATION_PREVALUE();

                ScalerSyncTMDSRx4HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_TMDS_RX4_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_TMDS_RX4_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx4("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx4HdmiQuantizationSetting();

                SET_TMDS_RX4_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_TMDS_COMBO_EXIST == _OFF))
//--------------------------------------------------
// Description  : TMDS Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiVideoSetting(void)
{
    if(GET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx5("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx5("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx5("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx5("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx5("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx5("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx5("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx5("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx5("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx5("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            case _AVI_PIXEL_REPETITION_6:

                DebugMessageRx5("Get Pixel Repetition 6", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_6);

                break;

            case _AVI_PIXEL_REPETITION_7:

                DebugMessageRx5("Get Pixel Repetition 7", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_7);

                break;

            case _AVI_PIXEL_REPETITION_8:

                DebugMessageRx5("Get Pixel Repetition 8", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_8);

                break;

            case _AVI_PIXEL_REPETITION_9:

                DebugMessageRx5("Get Pixel Repetition 9", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_9);

                break;

            default:

                DebugMessageRx5("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx5HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx5HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if(GET_TMDS_RX5_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_50_PORT_PAGE74_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx5SetPorchColor(GET_COLOR_SPACE());
}

//--------------------------------------------------
// Description  : TMDS Rx5 HDMI Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx5("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX5_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_00);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx5("Get Colorimetry YCC_SMPTE_170M", 0x00);

                SET_TMDS_RX5_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_01);

                SET_COLORIMETRY(_COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx5("Get Colorimetry 709", 0x00);

                SET_TMDS_RX5_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_10);

                SET_COLORIMETRY(_COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx5("Get Colorimetry Extended", 0x00);

                SET_TMDS_RX5_COLORIMETRY_PREVALUE(_AVI_COLORIMETRY_11);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx5HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX5_COLORIMETRY_PREVALUE(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY));

        switch(GET_TMDS_RX5_COLORIMETRY_PREVALUE())
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx5("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx5("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_EXT);

                ScalerSyncTMDSRx5HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx5 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        SET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        // Get extended colorimetry
        switch(GET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx5("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx5("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx5("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx5("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx5("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx5("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        SET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY));

        switch(GET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE())
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx5("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx5("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx5 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        SET_TMDS_RX5_QUANTIZATION_PREVALUE(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION));

        switch(GET_TMDS_RX5_QUANTIZATION_PREVALUE())
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx5("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx5("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx5("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_YCC_QUANTIZATION_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx5("Get RGB LIMIT RANGE", 0x00);

                SET_TMDS_RX5_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_LIMITED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx5("Get RGB FULL RANGE", 0x00);

                SET_TMDS_RX5_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx5("Get RGB DEFAULT RANGE", 0x00);

                SET_TMDS_RX5_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_DEFAULT);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx5("Get RGB RESERVED RANGE", 0x00);

                SET_TMDS_RX5_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_RESERVED);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx5("Get RGB RANGE Error", 0x00);

                SET_TMDS_RX5_QUANTIZATION_PREVALUE(_AVI_RGB_QUANTIZATION_FULL);

                SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx5 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx5HdmiColorInfoChanged(void)
{
    // Check Color Space
    if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE())
    {
        DebugMessageRx5("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != GET_TMDS_RX5_COLORIMETRY_PREVALUE())
    {
        DebugMessageRx5("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            BYTE pucTemp[2];

            pucTemp[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = GET_TMDS_RX5_COLORIMETRY_PREVALUE();

            ScalerSyncTMDSRx5HdmiColorimetrySetting();

            if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_TMDS_RX5_COLORIMETRY_CHANGED();
                }
            }
            else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_TMDS_RX5_COLORIMETRY_CHANGED();
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY() == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != GET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE())
            {
                DebugMessageRx5("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    BYTE pucTemp[2];

                    pucTemp[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = GET_TMDS_RX5_COLORIMETRY_EXT_PREVALUE();

                    ScalerSyncTMDSRx5HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_TMDS_RX5_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                    else if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_TMDS_RX5_COLORIMETRY_EXT_CHANGED();
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != GET_TMDS_RX5_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx5("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                BYTE pucTemp[2];

                pucTemp[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = GET_TMDS_RX5_QUANTIZATION_PREVALUE();

                ScalerSyncTMDSRx5HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_TMDS_RX5_QUANTIZATION_CHANGED();
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != GET_TMDS_RX5_QUANTIZATION_PREVALUE())
        {
            DebugMessageRx5("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx5HdmiQuantizationSetting();

                SET_TMDS_RX5_QUANTIZATION_CHANGED();
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Digital Get Colorimetry Changed
// Input Value  : EnumSourceSearchPort
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncDigitalGetColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            return GET_DP_RX0_COLORIMETRY_CHANGED();
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            return GET_TMDS_RX0_COLORIMETRY_CHANGED();
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            return GET_DP_RX0_COLORIMETRY_CHANGED();
#else
            return GET_DP_RX1_COLORIMETRY_CHANGED();
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            return GET_TMDS_RX1_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            return GET_DP_RX0_COLORIMETRY_CHANGED();
#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
            return GET_DP_RX1_COLORIMETRY_CHANGED();
#else
            return GET_DP_RX2_COLORIMETRY_CHANGED();
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            return GET_TMDS_RX2_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            return GET_TMDS_RX3_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            return GET_TMDS_RX4_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            return GET_TMDS_RX5_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Digital Get Colorimetry Extended Changed
// Input Value  : EnumSourceSearchPort
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncDigitalGetColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            return GET_DP_RX0_COLORIMETRY_EXT_CHANGED();
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            return GET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            return GET_DP_RX0_COLORIMETRY_EXT_CHANGED();
#else
            return GET_DP_RX1_COLORIMETRY_EXT_CHANGED();
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            return GET_TMDS_RX1_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            return GET_DP_RX0_COLORIMETRY_EXT_CHANGED();
#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
            return GET_DP_RX1_COLORIMETRY_EXT_CHANGED();
#else
            return GET_DP_RX2_COLORIMETRY_EXT_CHANGED();
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            return GET_TMDS_RX2_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            return GET_TMDS_RX3_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            return GET_TMDS_RX4_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            return GET_TMDS_RX5_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Digital Get Quantization Changed
// Input Value  : EnumSourceSearchPort
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncDigitalGetQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            return GET_DP_RX0_QUANTIZATION_CHANGED();
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            return GET_TMDS_RX0_QUANTIZATION_CHANGED();
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            return GET_DP_RX0_QUANTIZATION_CHANGED();
#else
            return GET_DP_RX1_QUANTIZATION_CHANGED();
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            return GET_TMDS_RX1_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            return GET_DP_RX0_QUANTIZATION_CHANGED();
#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
            return GET_DP_RX1_QUANTIZATION_CHANGED();
#else
            return GET_DP_RX2_QUANTIZATION_CHANGED();
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            return GET_TMDS_RX2_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            return GET_TMDS_RX3_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            return GET_TMDS_RX4_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            return GET_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            return GET_TMDS_RX5_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Digital Clr Colorimetry Changed
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            CLR_DP_RX0_COLORIMETRY_CHANGED();
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            CLR_TMDS_RX0_COLORIMETRY_CHANGED();
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            CLR_DP_RX0_COLORIMETRY_CHANGED();
#else
            CLR_DP_RX1_COLORIMETRY_CHANGED();
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            CLR_TMDS_RX1_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            CLR_DP_RX0_COLORIMETRY_CHANGED();
#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
            CLR_DP_RX1_COLORIMETRY_CHANGED();
#else
            CLR_DP_RX2_COLORIMETRY_CHANGED();
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            CLR_TMDS_RX2_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            CLR_TMDS_RX3_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            CLR_TMDS_RX4_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_CHANGED();
#else
            CLR_TMDS_RX5_COLORIMETRY_CHANGED();
#endif
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Digital Clr Colorimetry Extended Changed
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            CLR_DP_RX0_COLORIMETRY_EXT_CHANGED();
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            CLR_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            CLR_DP_RX0_COLORIMETRY_EXT_CHANGED();
#else
            CLR_DP_RX1_COLORIMETRY_EXT_CHANGED();
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            CLR_TMDS_RX1_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            CLR_DP_RX0_COLORIMETRY_EXT_CHANGED();
#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
            CLR_DP_RX1_COLORIMETRY_EXT_CHANGED();
#else
            CLR_DP_RX2_COLORIMETRY_EXT_CHANGED();
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            CLR_TMDS_RX2_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            CLR_TMDS_RX3_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            CLR_TMDS_RX4_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_COLORIMETRY_EXT_CHANGED();
#else
            CLR_TMDS_RX5_COLORIMETRY_EXT_CHANGED();
#endif
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Digital Clr Quantization Changed
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            CLR_DP_RX0_QUANTIZATION_CHANGED();
#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)
            CLR_TMDS_RX0_QUANTIZATION_CHANGED();
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            CLR_DP_RX0_QUANTIZATION_CHANGED();
#else
            CLR_DP_RX1_QUANTIZATION_CHANGED();
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            CLR_TMDS_RX1_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)
            CLR_DP_RX0_QUANTIZATION_CHANGED();
#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)
            CLR_DP_RX1_QUANTIZATION_CHANGED();
#else
            CLR_DP_RX2_QUANTIZATION_CHANGED();
#endif

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            CLR_TMDS_RX2_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            CLR_TMDS_RX3_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            CLR_TMDS_RX4_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)
#if(_TMDS_PAGE2_COMBO_EXIST == _ON)
            CLR_TMDS_RX0_QUANTIZATION_CHANGED();
#else
            CLR_TMDS_RX5_QUANTIZATION_CHANGED();
#endif
#endif
            break;

        default:
            break;
    }
}
#endif

#if(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)
//--------------------------------------------------
// Description  : Check VGA use embedded EDID
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerSyncVGAUseEmbeddedEDID(void)
{
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
    return _TRUE;
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check VGA DDC channel idle
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncVGADdcCheckBusyAndForceNack(void)
{
#if(_VGA_PORT_EXIST == _ON)
    WORD usTemp = 0;

#if(_HW_PC99_VGADDC2_SUPPORT == _ON)
    if(GET_A0_DDC_CHANNEL_SEL() == _VGA_DDC2)
    {
        MCU_FD37_ADC_DDC2_EDID_IRQ |= _BIT2;

        // set a polling duration
        for(usTemp = 0; usTemp < 1500; usTemp++)
        {
            // Delay 30us
            DELAY_30US();

            if((MCU_FD37_ADC_DDC2_EDID_IRQ & _BIT2) == _BIT2)
            {
                MCU_FD37_ADC_DDC2_EDID_IRQ |= _BIT2;
            }
            else
            {
                break;
            }
        }

        if((MCU_FD37_ADC_DDC2_EDID_IRQ & _BIT2) == _BIT2)
        {
            DebugMessageScaler("Warning :  VGA DDC2 wait SCL idle timeout", 0);
        }
    }
    else
#endif
    {
        MCU_FFE7_VGA_EDID_IRQ |= _BIT2;

        // set a polling duration
        for(usTemp = 0; usTemp < 1500; usTemp++)
        {
            // Delay 30us
            DELAY_30US();

            if((MCU_FFE7_VGA_EDID_IRQ & _BIT2) == _BIT2)
            {
                MCU_FFE7_VGA_EDID_IRQ |= _BIT2;
            }
            else
            {
                break;
            }
        }

        if((MCU_FFE7_VGA_EDID_IRQ & _BIT2) == _BIT2)
        {
            DebugMessageScaler("Warning :  VGA DDC wait SCL idle timeout", 0);
        }
    }

    // Force nack Ddc Channel
    ScalerSyncSetDdcForceNack(_A0_INPUT_PORT, _ON);
#endif
}
#endif // End of #if(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)

