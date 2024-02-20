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
// ID Code      : NoneUserInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE__

#include "UserCommonInclude.h"
#include "NoneUserHDMIEdid.h"
#include "NoneUserDPEdid.h"

#if(_OSD_TYPE == _NONE_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _EDID_VENDOR_SPEC_0                     160
#define _EDID_CHKSUM                            255

//-------------------------------------------------------
//  Definitions of RCP Key Codes
//-------------------------------------------------------
#define _MHL_RCP_VOLUME_UP                      0x41
#define _MHL_RCP_VOLUME_DOWN                    0x42
#define _MHL_RCP_MUTE                           0x43
#define _MHL_RCP_MUTE_FUNCTION                  0x65
#define _MHL_RCP_RESTORE_VOLUME_FUNCTION        0x66

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable0.h"
};

BYTE code tSU_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable2.h"
};

BYTE code tSU_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable4.h"
};

BYTE code tSU_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable6.h"
};

BYTE code tSU_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable8.h"
};

code BYTE *tSCALE_128TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_128_TAPS_0,        tSU_COEF_128_TAPS_2,        tSU_COEF_128_TAPS_4,        tSU_COEF_128_TAPS_6,        tSU_COEF_128_TAPS_8,
};
#endif // End of #if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))

#if(_HSU_128TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table8.h"
};

code BYTE *tSCALE_128TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_128_TAPS_0,        tSU_1to1_COEF_128_TAPS_2,        tSU_1to1_COEF_128_TAPS_4,        tSU_1to1_COEF_128_TAPS_6,        tSU_1to1_COEF_128_TAPS_8,
};
#endif // End of #if(_HSU_128TAPS_SUPPORT == _ON)

#if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable0.h"
};

BYTE code tSU_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable2.h"
};

BYTE code tSU_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable4.h"
};

BYTE code tSU_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable6.h"
};

BYTE code tSU_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable8.h"
};

code BYTE *tSCALE_96TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_96_TAPS_0,        tSU_COEF_96_TAPS_2,        tSU_COEF_96_TAPS_4,        tSU_COEF_96_TAPS_6,        tSU_COEF_96_TAPS_8,
};
#endif // End of #if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))

#if(_HSU_96TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table8.h"
};

code BYTE *tSCALE_96TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_96_TAPS_0,        tSU_1to1_COEF_96_TAPS_2,        tSU_1to1_COEF_96_TAPS_4,        tSU_1to1_COEF_96_TAPS_6,        tSU_1to1_COEF_96_TAPS_8,
};
#endif // End of #if(_HSU_96TAPS_SUPPORT == _ON)

#if(_ULTRA_VIVID_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ULTRAVIVID TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tCOLOR_ULTRAVIVID_SETTING_L[] =
{
#include "./UltraVivid/UltraVividTableL.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_M[] =
{
#include "./UltraVivid/UltraVividTableM.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_H[] =
{
#include "./UltraVivid/UltraVividTableH.h"
};

code BYTE *tCOLOR_ULTRAVIVID_SETTING_TABLE[] =
{
    tCOLOR_ULTRAVIVID_SETTING_L,
    tCOLOR_ULTRAVIVID_SETTING_M,
    tCOLOR_ULTRAVIVID_SETTING_H,
};
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if(_YPEAKING_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Ypeaking Coefficient Table
//----------------------------------------------------------------------------------------------------
#include "YPeakingTable.h"

code BYTE *tYPEAKING_TABLE[] =
{
    tYPK_COEF_1,
};
#endif // End of #if(_YPEAKING_SUPPORT == _ON)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_UART_SUPPORT == _ON)
BYTE g_pucUartData[5];
#endif

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
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// INT
//-------------------------------------------------------
#if(_INSTANT_TIMER_EVENT_0 == _ON)
void UserInterfaceTimer0InstantAccess_EXINT(void);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
void UserInterfaceTimer1InstantAccess_EXINT(void);
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
void UserInterfaceTimer2InstantAccess_EXINT(void);
#endif

#if(_UART_SUPPORT == _ON)
void UserInterfaceUartIntHandler_SERIALPORT(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
BYTE UserInterfaceGetDdcciStatus_EXINT1(void);
BYTE UserInterfaceGetFactoryCommand_EXINT1(void);
#if(_HDMI_FREESYNC_SUPPORT == _ON)
BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(void);
#endif
#endif

//-------------------------------------------------------
// EDID & HDCP
//-------------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
EnumHdmiEdidLocation UserInterfaceGetMultiHdmiEdidLocated(BYTE ucInputport, BYTE ucEdidIndex);
EnumEdidSelection UserInterfaceGetMultiHdmiEdidIndex(BYTE ucInputPort);
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort);
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
EnumUSBPDSupportStatus UserInterfaceGetUSBPDSupportStatus(void);
EnumUSBPSSupportStatus UserInterfaceGetUSBPSSupportStatus(void);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_DP_TX_SUPPORT == _ON)
void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
void UserInterfaceGetDpTxHdcp2RRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetDpTxHdcp2DcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetDpTxHdcp2EKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetDpTxHdcp2NPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif
#endif

//-------------------------------------------------------
// Wait for Panel Power Sequence Delay
//-------------------------------------------------------
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
void UserInterfacePanelPowerAction(BYTE ucEvent);
#endif

void UserInterfaceAdjustWaitPanelT1(void);
void UserInterfaceAdjustWaitPanelT2(void);
void UserInterfaceAdjustWaitPanelT3(void);
#if(_PANEL_TYPE != _PANEL_NONE)
void UserInterfaceAdjustWaitPanelT4(void);
#endif
void UserInterfaceAdjustWaitPanelT5(void);

//-------------------------------------------------------
// Misc
//-------------------------------------------------------
void UserInterfaceUncallFunction(void);
void UserInterfaceInitial(void);

void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed);

//-------------------------------------------------------
// User Information
//-------------------------------------------------------
bit UserInterfaceGetLogoStatus(void);
bit UserInterfaceGetdNoSupportStatus(void);
bit UserInterfaceGetDclkNoSupportStatus(void);
bit UserInterfaceGetActiveByPassStatus(void);
bit UserInterfaceGetCableResetStatus(void);
bit UserInterfaceGetForcePSStatus(void);
bit UserInterfaceGetIntoPSStatus(void);
EnumUserForceFakePS UserInterfaceGetFakePSStatus(void);
EnumUserForceFakePowerOff UserInterfaceGetFakePowerOffStatus(void);
bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType);
bit UserInterfaceGetDisplaySettingBacklightAction(void);

#if(_TRANSLATOR_SUPPORT == _OFF)
EnumColorSpace UserInterfaceGetColorFormat(void);
#endif

#if(_OVERSCAN_SUPPORT == _ON)
bit UserInterfaceGetOverScanStatus(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
EnumAspectRatioType UserInterfaceGetAspectRatioType(void);
void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio);
void UserInterfaceAdjustAspectRatio(void);

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
BYTE UserInterfaceGetAspectRatioOriginalRatio(void);
BYTE UserInterfaceGetAspectRatioOriginalRatioSmall(void);
#endif

#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
EnumRotationType UserInterfaceGetRotationDegree(void);
EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
BYTE UserInterfaceGetDisplayLatencyRatio(void);
#endif

#if(_FRC_SUPPORT == _ON)
void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

#if(_OD_SUPPORT == _ON)
EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void);
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
void UserInterfaceUpdateDDR3PhaseData(void);
#endif

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
bit UserInterfaceSystemEepromReadCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
bit UserInterfaceSystemEepromWriteCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
void UserInterfaceDisplayInitialization(void);
void UserInterfaceAdjustInputTiming(void);
void UserInterfaceAdjustDisplayTiming(void);

#if(_UNDERSCAN_SUPPORT == _ON)
bit UserInterfaceAdjustUnderScan(void);
#endif

//-------------------------------------------------------
// Color
//-------------------------------------------------------
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumColorYCCQuantization enumColorYCCQuantization);
#endif

void UserInterfaceAdjustActiveByPassColorProc(void);
void UserInterfaceAdjustColorProc(void);

#if(_ULTRA_VIVID_SUPPORT == _ON)
void UserInterfaceAdjustUltraVivid(void);
void UserInterfaceAdjustUltraVividProc(EnumDBApply enumDBApply);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSourceSearchPort enumSourceSearchPort);
BYTE UserInterfaceGetSharpnessCoefBankNum(void);
bit UserInterfaceSharpnessBypassCheck(void);
#endif

#if(_DCR_SUPPORT == _ON)
void UserInterfaceAdjustDCRHandler(void);
#endif

#if(_DCC_HISTOGRM_INFO == _ON)
void UserInterfaceDCCHistogramHandler(void);
#endif

#if(_IAPS_SUPPORT == _ON)
void UserInterfaceAdjustIAPSHandler(void);
#endif

//-------------------------------------------------------
// Osd
//-------------------------------------------------------
void UserInterfaceAdjustOsdPowerOnInitial(void);
void UserInterfaceAdjustOsdActiveProc(void);
void UserInterfaceAdjustOsdResetProc(void);

//-------------------------------------------------------
// Interfaces
//-------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex);
bit UserInterfaceGetLoadModeTableDefaultStatus(void);
bit UserInterfaceGetFirstAutoConfigStatus(void);
void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage);

#if(_VGA_FORCE_DISPLAY == _ON)
BYTE UserInterfaceModeSearchModeVGA(void);
#endif

bit UserInterfaceSkipAutoVpos(void);
bit UserInterfaceSkipAutoHpos(void);
#endif

#if(_MHL_SUPPORT == _ON)
bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort);

#if(_DP_SUPPORT == _ON)
EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
bit UserInterfaceGetDpCloneOutputStatus(void);
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) || (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
BYTE UserInterfaceGetDpSwitchSelectPort(void);
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
void UserInterfaceEmbeddedDpSwitch(void);
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
EnumDpHpdToggleMode UserInterfaceGetDpDcOnHpdMode(void);
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
bit UserInterfaceGetHdmi5VStatus(BYTE ucInputPort);
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
bit UserInterfaceAdjustOsdCheckTotalSearchFinish(void);
void UserInterfaceAdjustSourceSearchTime(void);
WORD UserInterfaceAdjustSourceReactiveSearchTime(EnumSourceAdjustReactiveTimePortType enumSourceAdjustReactiveTimePortType);
WORD UserInterfaceGetEizoSearchFinishTime(void);
#endif

//-------------------------------------------------------
// AUDIO
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
bit UserInterfaceGetAudioReadyToPlayStatus(void);
bit UserInterfaceGetAudioMuteStatus(void);
EnumAudioInputSource UserInterfaceGetAudioSource(void);
bit UserInterfaceGetAudioNonLPCMStatus(void);
WORD UserInterfaceGetAudioVolume(void);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void);
bit UserInterfaceGetAudioDACKeepDepopState(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

void UserInterfaceAdjustAudioResetProc(void);
void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
void UserInterfaceSwapExternalAudioCodecInput(bit bSwap);
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
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
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
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
#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
#endif

#if(_YPEAKING_SUPPORT == _ON)
void UserInterfaceAdjustYpeaking(void);
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
EnumDDCCIDebugMode UserInterfaceGetDdcciMode(void);
EnumDataExchangeRepeaterPowerState UserInterfaceGetRepeaterIntoPowerOff(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _USER_TIMER_EVENT_KEY_REPEAT_ENABLE:
            SET_KEYREPEATSTART();
            break;

        case _USER_TIMER_EVENT_KEY_SCAN_READY:
            SET_KEYSCANREADY();
            break;

        case _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON:
            SET_PANELPOWERSTATUS(_READY_FOR_BACKLIGHT);
            break;

        case _USER_TIMER_EVENT_PANEL_POWER_OFF:
            break;

        case _USER_TIMER_EVENT_PANEL_USED_TIMER:
            break;

        default:
            break;
    }
}

#if(_INSTANT_TIMER_EVENT_0 == _ON)
//--------------------------------------------------
// Description  : Action in Timer0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer0InstantAccess_EXINT(void)
{
}
#pragma restore
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
//--------------------------------------------------
// Description  : Action in Timer1 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer1InstantAccess_EXINT(void)
{
}
#pragma restore
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
//--------------------------------------------------
// Description  : Action in Timer2 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer2InstantAccess_EXINT(void)
{
}
#pragma restore
#endif

#if(_UART_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Action in Serial Port0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUartIntHandler_SERIALPORT(void)
{
    if(GET_UART_RECEIVE_STATUS() == _TRUE)
    {
        g_pucUartData[0] = GET_UART_DATA();

        CLR_UART_RECEIVE_STATUS();
    }
}
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get DDC-CI Status for Int1
// Input Value  : ucDataType --> Data Type in StructSystemData
// Output Value : ucValue --> Value of the Input Data Type
//--------------------------------------------------
BYTE UserInterfaceGetDdcciStatus_EXINT1(void) using 2
{
    return GET_OSD_DDCCI_STATUS();
}

//--------------------------------------------------
// Description  : Get Data from DDCCI Buffer defined by user
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetFactoryCommand_EXINT1(void) using 2
{
    return _FALSE;
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Source Opcode is HDMI freesync
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(void) using 2
{
    return _FALSE;
}
#endif // #if(_HDMI_FREESYNC_SUPPORT == _ON)
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get the HDMI Port Edid location
// Input Value  : EDID Index
// Output Value : External/ Embedded Edid
//--------------------------------------------------
EnumHdmiEdidLocation UserInterfaceGetMultiHdmiEdidLocated(BYTE ucInputport, BYTE ucEdidIndex)
{
    return tEdidMultiLocatedTable[ucInputport][ucEdidIndex];
}

//--------------------------------------------------
// Description  : Get the Mapping of Edid index of Function Application
// Input Value  : ucInputPort
// Output Value : Edid Index Enum
//--------------------------------------------------
EnumEdidSelection UserInterfaceGetMultiHdmiEdidIndex(BYTE ucInputPort)
{
    EnumEdidSelection enumIndex = _EDID_INDEX_0;

    return enumIndex;
}
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Embedded EDID Data
// Input Value  : Input Port EDID Select
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort)
{
    switch(enumInputPort)
    {
        case _A0_INPUT_PORT_EDID:
            break;

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D0_INPUT_PORT_EDID:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D0, tDP_EDID_TABLE[UserAdjustGetDpEdidIndex(_D0_INPUT_PORT)], _D0_EMBEDDED_DDCRAM_MAX_SIZE);

#elif(_D0_HDMI_SUPPORT == _ON)

#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D0_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D0_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(MCU_DDCRAM_D0, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D0_INPUT_PORT)], _D0_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memset(MCU_DDCRAM_D0, 0, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D0, tHDMI_EDID_FHD_TABLE, _D0_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

#endif
            break;
#endif // #if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D1_INPUT_PORT_EDID:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D1, tDP_EDID_TABLE[UserAdjustGetDpEdidIndex(_D1_INPUT_PORT)], _D1_EMBEDDED_DDCRAM_MAX_SIZE);

#elif(_D1_HDMI_SUPPORT == _ON)

#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D1_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D1_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(MCU_DDCRAM_D1, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D1_INPUT_PORT)], _D1_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memset(MCU_DDCRAM_D1, 0, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D1, tHDMI_EDID_FHD_TABLE, _D1_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

#endif
            break;
#endif //#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D2_INPUT_PORT_EDID:

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

            memset(MCU_DDCRAM_D2, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D2, tDP_EDID_TABLE[UserAdjustGetDpEdidIndex(_D2_INPUT_PORT)], _D2_EMBEDDED_DDCRAM_MAX_SIZE);

#elif(_D2_HDMI_SUPPORT == _ON)

#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D2_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D2_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memset(MCU_DDCRAM_D2, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(MCU_DDCRAM_D2, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D2_INPUT_PORT)], _D2_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memset(MCU_DDCRAM_D2, 0, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D2, tHDMI_EDID_FHD_TABLE, _D2_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

#endif
            break;
#endif //#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D3_INPUT_PORT_EDID:

#if(_D3_HDMI_SUPPORT == _ON)

#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D3_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D3_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(MCU_DDCRAM_D3, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D3_INPUT_PORT)], _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memset(MCU_DDCRAM_D3, 0, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D3, tHDMI_EDID_FHD_TABLE, _D3_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

#endif
            break;
#endif //#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D4_INPUT_PORT_EDID:

#if(_D4_HDMI_SUPPORT == _ON)

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D4_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D4_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(MCU_DDCRAM_D4, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D4_INPUT_PORT)], _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memset(MCU_DDCRAM_D4, 0, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D4, tHDMI_EDID_FHD_TABLE, _D4_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

#endif
            break;
#endif //#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D5_INPUT_PORT_EDID:

#if(_D5_HDMI_SUPPORT == _ON)

#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)
            if(UserCommonInterfaceHDMIGetMultiEdidLocated(_D5_INPUT_PORT, UserInterfaceGetMultiHdmiEdidIndex(_D5_INPUT_PORT)) != _HDMI_EDID_EXTERNAL)
            {
                memset(MCU_DDCRAM_D5, 0, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
                memcpy(MCU_DDCRAM_D5, tHDMI_EDID_TABLE[UserInterfaceGetMultiHdmiEdidIndex(_D5_INPUT_PORT)], _D5_EMBEDDED_DDCRAM_MAX_SIZE);
            }
#else
            memset(MCU_DDCRAM_D5, 0, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D5, tHDMI_EDID_FHD_TABLE, _D5_EMBEDDED_DDCRAM_MAX_SIZE);
#endif

#endif
            break;
#endif //#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D6_INPUT_PORT_EDID:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            memset(MCU_DDCRAM_D6, 0, _D6_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D6, tDP_EDID_TABLE[UserAdjustGetDpEdidIndex(_D6_INPUT_PORT)], _D6_EMBEDDED_DDCRAM_MAX_SIZE);
#endif
            break;
#endif //#if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

        case _D0_INPUT_PORT_MHL_EDID:
            break;

        case _D1_INPUT_PORT_MHL_EDID:
            break;

        case _D2_INPUT_PORT_MHL_EDID:
            break;

        case _D3_INPUT_PORT_MHL_EDID:
            break;

        case _D4_INPUT_PORT_MHL_EDID:
            break;

        case _D5_INPUT_PORT_MHL_EDID:
            break;

        default:
            break;
    }
}
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get USB3 Retimer PD Support Status
// Input Value  : void
// Output Value : EnumUSBPDSupportStatus
//--------------------------------------------------
EnumUSBPDSupportStatus UserInterfaceGetUSBPDSupportStatus(void)
{
    return _USB_PD_DISABLE;
}

//--------------------------------------------------
// Description  : Get USB3 Retimer PS Support Status
// Input Value  : void
// Output Value : EnumUSBPSSupportStatus
//--------------------------------------------------
EnumUSBPSSupportStatus UserInterfaceGetUSBPSSupportStatus(void)
{
    return _USB_PS_DISABLE;
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
//--------------------------------------------------
// Description  : Get HDCP Bksv By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Tx HDCP Aksv By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2RRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2DcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2EKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2NPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
}
#endif // End of #if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
//--------------------------------------------------
// Description  : Power Power On/Off Sequence
// Input Value  : ucEvent --> _PANEL_ON
//                            _PANEL_OFF
//                            _BACKLIGHT_ON
//                            _BACKLIGHT_OFF
// Output Value : None
//--------------------------------------------------
void UserInterfacePanelPowerAction(BYTE ucEvent)
{
    ucEvent = ucEvent;
}
#endif

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT1(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_ON_T1);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT2(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerTimerDelayXms(_PANEL_POWER_ON_T2);

#elif(_PANEL_STYLE == _PANEL_VBO)

    ScalerDisplayVboPollingHotPlug(_PANEL_POWER_ON_T2);

#elif(_PANEL_STYLE == _PANEL_DPTX)

    ScalerDisplayDPTxPollingHotPlug(_PANEL_POWER_ON_T2);

#endif
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT3(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_ON_T3);
}

#if(_PANEL_TYPE != _PANEL_NONE)
//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T4
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT4(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_OFF_T4);
}
#endif

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T5
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT5(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_OFF_T5);
}

//--------------------------------------------------
// Description  : Uncall Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUncallFunction(void)
{
    bit bUncall = _FALSE;

    if(bUncall == _TRUE)
    {
#if(_AUDIO_SUPPORT == _ON)
        UserInterfaceGetAudioMuteStatus();
#endif
        UserInterfaceAdjustWaitPanelT2();
        UserInterfaceAdjustWaitPanelT5();

        UserInterfaceGetDisplaySettingBacklightAction();

#if(_TRANSLATOR_SUPPORT == _ON)
        UserInterfaceGetDclkNoSupportStatus();
        UserInterfaceGetDisplaySettingBacklightAction();
        UserInterfaceDisplayInitialization();
        UserInterfaceAdjustDisplayTiming();
        UserInterfaceAdjustInputTiming();
        UserInterfaceAdjustActiveByPassColorProc();
        UserInterfaceAdjustColorProc();
        UserAdjustBacklight(0);
#if(_AUDIO_SUPPORT == _ON)
        UserInterfaceGetAudioVolume();
        UserInterfaceAdjustAudioAmpMuteProc(0);
        UserAdjustAudioVolume(0);
        UserAdjustAudioMuteSwitch();
        UserAdjustAudioVolumeMapping(0);
#endif
#endif

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        // TypeC Connect On, Port Ctrl Off UserInterface Functions
        UserInterfaceTypeCGetOsdU3ModeSelection(_D0_INPUT_PORT);
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
        UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(_D0_INPUT_PORT);
#endif
#endif

#if(_DP_SUPPORT == _ON)
        UserCommonInterfaceDpGetEdidNativeTimingBw(_NO_PORT_EDID);
#endif

#if(_FORCE_D_DOMAIN_DB_APPLY == _ON)
#if((_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_II) || (_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_III))
        UserCommonInterfaceForceUsingDDomainDB();
#endif
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
        UserAdjustGetDpEdidIndex(_D0_INPUT_PORT);
#endif
    }
}

//--------------------------------------------------
// Description  : User Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceInitial(void)
{
    // Call Uncalled Function for Compile Warning
    UserInterfaceUncallFunction();

    PCB_PWM_SETTING();
    NoneNVRamStartup();

#if(_DP_MST_SUPPORT == _ON)
    UserCommonInterfaceMstRx0Rx1switch(UserCommonInterfaceGetDpMstCapablePort());
#endif

#if(_FACTORY_RTD_QC_SUPPORT == _ON)

    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, _SOURCE_SWITCH_FIXED_PORT);
    UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _ON);

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
    UserCommonNVRamSetSystemData(_SEARCH_PORT, _A0_INPUT_PORT);
#elif(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
    UserCommonNVRamSetSystemData(_SEARCH_PORT, _D0_INPUT_PORT);
#elif(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
    UserCommonNVRamSetSystemData(_SEARCH_PORT, _D1_INPUT_PORT);
#else
    UserCommonNVRamSetSystemData(_SEARCH_PORT, _A0_INPUT_PORT);
#endif
#endif

    ScalerMcuDdcciSwitchPort(_DEBUG_MODE, UserCommonNVRamGetSystemData(_SEARCH_PORT));
    NoneKeyInitial();
    SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);

#if(_TRANSLATOR_SUPPORT == _OFF)
    // Adjust Backlight
    UserAdjustBacklight(0x80);
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
    //Initilize Hub Input Port
    SET_USER_USB_HUB_UFP_SWITCH(_HUB_UFP_TYPE_C_INPUT_PORT);
    SysTypeCSetCapabilityChangeFlag(_D0_INPUT_PORT, _TYPE_C_HUB_INPUT_SWITCH_CHG);
#endif
}

//--------------------------------------------------
// Description  : User Power Switch
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            // Port Controller Power Control
            UserAjustTypeCPowerControl(enumSwitch);
#endif
#endif

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_ON);

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            // Port Controller Power Control
            UserAjustTypeCPowerControl(enumSwitch);
#endif
#endif

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            // Port Controller Power Control
            UserAjustTypeCPowerControl(enumSwitch);
#endif
#endif

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_ON);

            // Set Monitor Power On Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _ON);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            // Port Controller Power Control
            UserAjustTypeCPowerControl(enumSwitch);
#endif
#endif

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            // Port Controller Power Control
            UserAjustTypeCPowerControl(enumSwitch);
#endif
#endif

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_PS_TO_OFF:

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            // Port Controller Power Control
            UserAjustTypeCPowerControl(enumSwitch);
#endif
#endif

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
            // Port Controller Power Control
            UserAjustTypeCPowerControl(enumSwitch);
#endif
#endif

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_SAVING);

            // Panel pown down.
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : Keypad Led Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)

    ucKeyPadLed = ucKeyPadLed;

#else

    switch(ucKeyPadLed)
    {
        case _LED_POWER_ON:
            PCB_LED_ON();
            break;

        case _LED_POWER_ACTIVE:
            PCB_LED_ACTIVE();
            break;

        case _LED_POWER_SEARCH:
            PCB_LED_IDLE();
            break;

        case _LED_POWER_SAVING:
            PCB_LED_POWER_SAVING();
            break;

        case _LED_POWER_NOSUPPORT:
            PCB_LED_ACTIVE();
            break;

        case _LED_POWER_NOSUPPORT_SAVING:
            PCB_LED_POWER_SAVING();
            break;

        case _LED_POWER_OFF:
            PCB_LED_OFF();
            break;

        case _LED_ALL_OFF:
            PCB_LED_OFF();
            break;

        case _LED_TYPE_1:
            PCB_LED_TYPE1();
            break;

        case _LED_TYPE_2:
            PCB_LED_TYPE2();
            break;

        case _LED_TYPE_3:
            PCB_LED_TYPE3();
            break;

        case _LED_TYPE_4:
            PCB_LED_TYPE4();
            break;

        case _LED_TYPE_5:
            PCB_LED_TYPE5();
            break;

        case _LED_TYPE_FLASH:
            PCB_LED_TYPE_FLASH();
            break;

        default:
            break;
    }

#endif  // End of #if(_FACTORY_RTD_QC_SUPPORT == _OFF)
}

//--------------------------------------------------
// Description  : User OSD Get LogoOn
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetLogoStatus(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Whther to support this timing
// Input Value  : None
// Output Value : TRUE => Go to No Support State
//--------------------------------------------------
bit UserInterfaceGetdNoSupportStatus(void)
{
    // Add User No Support Check
    return _FALSE;
}

//--------------------------------------------------
// Description  : For User to Check Whether to Support Current DCLK
// Input Value  : None
// Output Value : _TRUE => No Support
//--------------------------------------------------
bit UserInterfaceGetDclkNoSupportStatus(void)
{
#if(_TRANSLATOR_SUPPORT == _OFF)

    if((GET_D_MAX_CLK_FREQ() > ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ)) ||
       (GET_D_MIN_CLK_FREQ() < ((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ)))
    {
        DebugMessageScaler("D Clock Exceed Panel Supported Range", GET_D_CLK_FREQ());
        return _TRUE;
    }

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_DOSMODE_ONLY_SUPPORT == _ON))
    if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)
    {
        if((GET_INPUT_TIMING_HWIDTH() > 800) ||
           (GET_INPUT_TIMING_VHEIGHT() > 600))
        {
            DebugMessageScaler("FRC only supports dos-mode timing", 0);
            return _TRUE;
        }
    }
#endif

#endif // End of #if(_TRANSLATOR_SUPPORT == _OFF)

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get whether to by pass normal active process
// Input Value  : None
// Output Value : _TRUE => By pass normal active process
//--------------------------------------------------
bit UserInterfaceGetActiveByPassStatus(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : User Define Whether Cable Status Should Reset
// Input Value  : None
// Output Value : _TRUE => Reset
//--------------------------------------------------
bit UserInterfaceGetCableResetStatus(void)
{
    if((SysSourceGetCableStatusChange(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE) &&
       ((!(SysModeGetModeState() == _MODE_STATUS_SEARCH)) || (SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT)) == _TRUE)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Forced Power Saving Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetForcePSStatus(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : User Check Into Power Saving
// Input Value  : None
// Output Value : True --> User Check Ready to Power Saving
//--------------------------------------------------
bit UserInterfaceGetIntoPSStatus(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : User Setting Fake Power Saving
// Input Value  : None
// Output Value : _USER_FORCE_FAKE_PS --> User Set Power Status into Fake Power Saving
//                _USER_FORCE_POWER_SAVING    --> User Set Power Status into Power saving
//--------------------------------------------------
EnumUserForceFakePS UserInterfaceGetFakePSStatus(void)
{
    return _USER_FORCE_POWER_SAVING;
}

//--------------------------------------------------
// Description  : User Setting Fake Power Status
// Input Value  : None
// Output Value : _USER_FORCE_FAKE_POWER_OFF ==> Fake Power Off
//                _USER_FORCE_POWER_OFF ==> Power off
//--------------------------------------------------
EnumUserForceFakePowerOff UserInterfaceGetFakePowerOffStatus(void)
{
    return _USER_FORCE_POWER_OFF;
}

//--------------------------------------------------
// Description  : Check Whther ADC Data is Reasonable
// Input Value  : LOAD or SAVE
// Output Value : _TRUE => Reasonable
//--------------------------------------------------
bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType)
{
    switch(enumNvramCheckType)
    {
#if(_VGA_SUPPORT == _ON)
        case _CHECK_ADC_LOAD:

            if(g_stAdcData.ucAdcPGA >= 0xF0)
            {
                // Assign Prefered Value
                g_stAdcData.ucAdcPGA = 8;
            }

            break;

        case _CHECK_ADC_SAVE:

            if(g_stAdcData.ucAdcPGA >= 0xF0)
            {
                return _FAIL;
            }
            break;
#endif

        case _CHECK_SYSTEM_DATA_LOAD:
        case _CHECK_SYSTEM_DATA_SAVE:
        case _CHECK_MODE_USER_DATA_LOAD:
        case _CHECK_MODE_USER_DATA_SAVE:

            break;

        default:
            break;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Get backlight staus when performing display setting
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserInterfaceGetDisplaySettingBacklightAction(void)
{
#if((_PANEL_STYLE == _PANEL_DPTX) ||\
    (_PANEL_STYLE == _PANEL_VBO))

    return _DISABLE;

#else

    return _ENABLE;

#endif
}

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get OSD Color Format
// Input Value  : display Region
// Output Value : Color Format
//--------------------------------------------------
EnumColorSpace UserInterfaceGetColorFormat(void)
{
    // If no color format select in OSD return system color space
    return ScalerColorGetColorSpace();
}
#endif

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Overscan
// Input Value  : Current Input Timing
// Output Value : Modified Input Timing
//--------------------------------------------------
bit UserInterfaceGetOverScanStatus(void)
{
    bit bDoOverScan = _FALSE;
    BYTE ucTemp = 0;
    WORD code tusOverscanEnTable[][3] =
    {
        // VFreq, HWidth, VHeight,
        {600,  640,  480},    // 480p
        {600,  720,  480},    // 480p
        {600,  960,  480},    // 480p
        {600, 1440,  480},    // 480p

        {500,  720,  576},    // 576p
        {500,  768,  576},    // 576p
        {500,  960,  576},    // 576p
        {500, 1280,  576},    // 576p
        {500, 1440,  576},    // 576p
        {500, 1280,  720},    // 720p
        {600, 1280,  720},    // 720p
        {500, 1920,  1080},   // 1080p
        {600, 1920,  1080},   // 1080p

        // Don't delete it, and place it at last.
        {  0,    0,    0},
    };

    if(GET_OSD_OVERSCAN_STATUS() == _OFF)
    {
        return _FALSE;
    }

    // Decide whether to do over scan
    switch(SysSourceGetSourceType())
    {
#if(_OVERSCAN_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Interlaced and YUV Timing Always do overscan
            if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
            {
                bDoOverScan = _TRUE;
                break;
            }

            if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_RGB)
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(GET_INPUT_TIMING_VFREQ() - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(GET_INPUT_TIMING_HWIDTH() - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (GET_INPUT_TIMING_VHEIGHT() == tusOverscanEnTable[ucTemp][2]))
                {
                    bDoOverScan = _TRUE;
                    break;
                }

                ucTemp++;
            }

            break;
#endif // End of #if(_OVERSCAN_VGA_SUPPORT == _ON)

#if(_OVERSCAN_DVI_SUPPORT != _ON)
        case _SOURCE_DVI:
            break;
#endif

#if(_OVERSCAN_HDMI_SUPPORT != _ON)
        case _SOURCE_HDMI:
            break;
#endif

#if(_OVERSCAN_DP_SUPPORT == _ON)
        case _SOURCE_DP:
            break;
#endif

        default:
#if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))
            // Interlaced and YUV Timing Always do overscan
            if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
            {
                bDoOverScan = _TRUE;
                break;
            }

            if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _TRUE)
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(GET_INPUT_TIMING_VFREQ() - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(GET_INPUT_TIMING_HWIDTH() - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (GET_INPUT_TIMING_VHEIGHT() == tusOverscanEnTable[ucTemp][2]))
                {
                    bDoOverScan = _TRUE;
                    break;
                }

                ucTemp++;
            }
#endif // End of #if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))

            break;
    }

    return bDoOverScan;
}

#endif // End of #if(_OVERSCAN_SUPPORT == _ON)

#if(_ASPECT_RATIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Aspect Ratio
// Input Value  : enumSelRegion --> select region
// Output Value : aspect ration type
//--------------------------------------------------
EnumAspectRatioType UserInterfaceGetAspectRatioType(void)
{
    return _ASPECT_RATIO_FULL;
}

//--------------------------------------------------
// Description  : Get user H/V aspect ratio values
// Input Value  : enumSelRegion --> select region
//                usHRatio, usVRatio --> aspect ratio
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio)
{
    pusHRatio = pusHRatio;
    pusVRatio = pusVRatio;
}

//--------------------------------------------------
// Description  : User defined aspect ratio process
// Input Value  : select region
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAspectRatio(void)
{
}

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get aspect original mode ratio
// Input Value  : select region
// Output Value : Retion display ratio in aspect ratio original mode (0x00 ~ 0xFF)
//--------------------------------------------------
BYTE UserInterfaceGetAspectRatioOriginalRatio(void)
{
    return 0xFF;
}

//--------------------------------------------------
// Description  : Get reduced aspect ratio in original mode
// Input Value  : select region
// Output Value : Retion display ratio in aspect ratio original mode (0x00 ~ 0xFF)
//--------------------------------------------------
BYTE UserInterfaceGetAspectRatioOriginalRatioSmall(void)
{
    return 0xFF;
}
#endif
#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get current rotation degree
// Input Value  : None
// Output Value : rotation degree
//--------------------------------------------------
EnumRotationType UserInterfaceGetRotationDegree(void)
{
    switch(GET_OSD_DISP_ROTATE())
    {
        default:
        case _DISP_ROTATE_0:
            return _ROT_DISABLE;

#if (_DISPLAY_ROTATION_90_SUPPORT == _ON)
        case _DISP_ROTATE_90:
            return _ROT_CW90;
#endif
#if (_DISPLAY_ROTATION_180_SUPPORT == _ON)
        case _DISP_ROTATE_180:
            return _ROT_CW180;
#endif
#if (_DISPLAY_ROTATION_270_SUPPORT == _ON)
        case _DISP_ROTATE_270:
            return _ROT_CW270;
#endif
    }
}

//--------------------------------------------------
// Description  : Get current rotation type
// Input Value  : None
// Output Value : rotation type
//--------------------------------------------------
EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void)
{
    switch(GET_OSD_DISP_ROTATION_SIZE_TYPE())
    {
        default:
        case _OSD_ROTATE_DISPLAY_FULL:
            return _ROT_FULL;

        case _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL:
            return _ROT_PIXEL_BY_PIXEL;

        case _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO:
            return _ROT_KEEP_SRC_ASPECT_RATIO;
    }
}
#endif  // #if(_DISPLAY_ROTATION_SUPPORT == _ON)

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Display Latency Ratio
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetDisplayLatencyRatio(void)
{
    switch(GET_OSD_LATENCY())
    {
        default:
            break;

        case _LATENCY_L:
            return 0;   // 0%

        case _LATENCY_M:
            return 50;  // 50%

        case _LATENCY_H:
            return 100; // 100%
    }

    return 0;
}
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Max/Min Freq according to latency
// Input Value  : None
// Output Value : max/min freq
//--------------------------------------------------
void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq)
{
    pstDVCustomizedFreq = pstDVCustomizedFreq;

#if(_MN_FINE_TUNE_LASTLINE_SUPPORT == _ON)
    if((SysSourceGetInputPort() == _A0_INPUT_PORT) ||
       (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
        pstDVCustomizedFreq->b1FORCETOFREERUN = _ENABLE;
    }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    switch (GET_OSD_LATENCY())
    {
        default:
        case _LATENCY_H:
        case _LATENCY_M:
        case _LATENCY_L:

            pstDVCustomizedFreq->usMaxFreq = _PANEL_MAX_FRAME_RATE;
            pstDVCustomizedFreq->usTypFreq = _PANEL_TYP_FRAME_RATE;
            pstDVCustomizedFreq->usMinFreq = _PANEL_MIN_FRAME_RATE;
            break;
    }
#endif
}
#endif

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OD enable status
// Input Value  : None
// Output Value : function enable status
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void)
{
    return GET_OSD_OD_STATUS();
}
#endif


#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
//--------------------------------------------------
// Description  : Get DDR3 Phase From GPIO or DDCCI command
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUpdateDDR3PhaseData(void)
{
    StructDDR3PhaseInfo stUserVedorDdr3PhaseData = {_DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1, _DDR3_READ_DQ_DLYN_TAP};
    ScalerPLLGetDDR3PhaseData(&stUserVedorDdr3PhaseData);
}
#endif

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
//--------------------------------------------------
// Description  : User Custom Check Proc when System Eeprom Read
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserInterfaceSystemEepromReadCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : User Custom Check Proc when System Eeprom Write
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserInterfaceSystemEepromWriteCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucWriteArray = pucWriteArray;
    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Modify display Timing Based on User Requirement
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayInitialization(void)
{
}

//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : Current Input Timing Info
// Output Value : Modified Input Timing
//--------------------------------------------------
void UserInterfaceAdjustInputTiming(void)
{
}

//--------------------------------------------------
// Description  : Modify Display Timing Based on User Requirement
// Input Value  : Current Display Timing Info
// Output Value : Modified Display Timing
//--------------------------------------------------
void UserInterfaceAdjustDisplayTiming(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)
    // Check display format resolution according to LVDS port count
    SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + (GET_MDOMAIN_OUTPUT_HSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() - (GET_MDOMAIN_OUTPUT_HWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HBSTART() + (GET_MDOMAIN_OUTPUT_HBSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HBWIDTH() - (GET_MDOMAIN_OUTPUT_HBWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
#endif
}

#if(_UNDERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceAdjustUnderScan(void)
{
    return _FALSE;
}
#endif

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
//--------------------------------------------------
// Description  : User Judge if Quantization Range is Full or Limited
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization)
{
    switch(enumColorRGBQuantization)
    {
        case _RGB_QUANTIZATION_FULL_RANGE:
        case _RGB_QUANTIZATION_DEFAULT_RANGE:
        case _RGB_QUANTIZATION_RESERVED:
        default:

            return _FALSE;

        case _RGB_QUANTIZATION_LIMIT_RANGE:

            return _TRUE;
    }
}
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Judge if YCC Quantization Range is Full or Limited
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumColorYCCQuantization enumColorYCCQuantization)
{
    return (enumColorYCCQuantization == _YCC_QUANTIZATION_FULL_RANGE);
}
#endif

//--------------------------------------------------
// Description  : Set Color in pass normal active process
// Input Value  : None
// Output Value : void
//--------------------------------------------------
void UserInterfaceAdjustActiveByPassColorProc(void)
{
    return;
}

//--------------------------------------------------
// Description  : Set User Required Color Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustColorProc(void)
{
#if(_TRANSLATOR_SUPPORT == _OFF)
    // Adjust Color Space
    SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_NONE);

    // Adjust Backlight
    UserAdjustBacklight(0x80);

    // Adjust Brightness & Contrast
#if(_BRIGHTNESS_SUPPORT == _ON)
#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
    UserAdjustBrightness(0x200);
#else
    UserAdjustBrightness(0x080);
#endif
#endif // End of #if(_BRIGHTNESS_SUPPORT == _ON)

#if(_CONTRAST_SUPPORT == _ON)
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
    UserAdjustContrast(0x800);
#else
    UserAdjustContrast(0x080);
#endif
#endif // End of #if(_CONTRAST_SUPPORT == _ON)

    // Adjust Sharpness
#if(_SHARPNESS_SUPPORT == _ON)
    UserCommonAdjustSharpness(SysSourceGetInputPort());
#endif

    // Adjust Transparency
    ScalerOsdSetTransparency(2);
    ScalerOsdSetTransparencyType(_OSD_TRANSPARENCY_DISABLE);

    // Adjust Gamma On/Off
#if(_GAMMA_FUNCTION == _ON)
    UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);
#endif

#if(_RGB_GAMMA_FUNCTION == _ON)
    ScalerColorRGBOutputGammaEnable(_FUNCTION_OFF);
#endif

    // Adjust Hue & Saturation
#if(_GLOBAL_HUE_SATURATION == _ON)
    UserAdjustGlobalHueSat(_DEFAULT_HUE, _DEFAULT_SATURATION);
#endif

    // Adjust ICM On/Off
#if(_ICM_SUPPORT == _ON)
    ScalerColorICMEnable(_FUNCTION_OFF);
#endif

    // Adjust DCC On/Off
#if(_COLOR_IP_DCC == _ON)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

    // Adjust Ypeaking On/Off
#if(_YPEAKING_SUPPORT == _ON)
    ScalerColorYpeaking(_OFF);
#endif

    // Adjust Highlight Window Type & On/Off
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_NO_POLLING);
#endif

#if(_OD_SUPPORT == _ON)
    ScalerODAdjustDeltaGain(0x40);
#endif // End of #if(_OD_SUPPORT == _ON)

    // Adjust UltraVivid
#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorUltraVividEnable(_FUNCTION_OFF, _DB_APPLY_POLLING);
#endif
#endif // End of #if(_TRANSLATOR_SUPPORT == _OFF)
}

#if(_ULTRA_VIVID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustUltraVivid(void)
{
    BYTE ucUltraVividStatus = 1;

    ScalerColorUltraVividEnable(_FUNCTION_OFF, _DB_APPLY_NONE);
    ScalerColorUltraVividAdjust(tCOLOR_ULTRAVIVID_SETTING_TABLE[ucUltraVividStatus - 1], GET_CURRENT_BANK_NUMBER());
}

//--------------------------------------------------
// Description  : UltraVivid Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustUltraVividProc(EnumDBApply enumDBApply)
{
    ScalerColorUltraVividEnable(_FUNCTION_OFF, enumDBApply);
}
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Sharpness Coef
// Input Value  : SU Coef Type
// Output Value : SU Coef
//--------------------------------------------------
code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    switch(enumSUCoefType)
    {
#if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))
        case _H_V_SU_128TAPS_NORMAL:
            return tSCALE_128TAPS_NORMAL_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif

#if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
        case _H_V_SU_96TAPS_NORMAL:
            return tSCALE_96TAPS_NORMAL_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif

#if(_HSU_128TAPS_SUPPORT == _ON)
        case _H_SU_128TAPS_1_TO_1:
            return tSCALE_128TAPS_1to1_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif

#if(_HSU_96TAPS_SUPPORT == _ON)
        case _H_SU_96TAPS_1_TO_1:
            return tSCALE_96TAPS_1to1_COEF_TABLE[GET_OSD_SHARPNESS()];
#endif
        default:
            return _NULL_POINTER;
    }
}

//--------------------------------------------------
// Description  : Get Sharpness Coef BankNum
// Input Value  : None
// Output Value : BankNum
//--------------------------------------------------
BYTE UserInterfaceGetSharpnessCoefBankNum(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

//--------------------------------------------------
// Description  : User Bypass Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSharpnessBypassCheck(void)
{
    return _FALSE;
}
#endif // End of #if(_SHARPNESS_SUPPORT == _ON)

#if(_DCR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust DCR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustDCRHandler(void)
{
#if(_LOCAL_DIMMING_SUPPORT == _ON)
    BYTE pucDCRResult[_TOTAL_REGION];
    memset(pucDCRResult, 255UL, _TOTAL_REGION);
    ScalerColorDCRLocalDimmingReadResult(pucDCRResult);
#else
    PDATA_DWORD(0) = ScalerColorDCRReadResult(_DCR_ABOVE_TH1_NUM);
#endif
}
#endif // End of #if(_DCR_SUPPORT == _ON)

#if(_DCC_HISTOGRM_INFO == _ON)
//--------------------------------------------------
// Description  : User Adjust DCC Histogram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDCCHistogramHandler(void)
{
}
#endif // End of #if(_DCC_HISTOGRM_INFO == _ON)

#if(_IAPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust IAPS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustIAPSHandler(void)
{
}
#endif // End of #if(_IAPS_SUPPORT == _ON)

//--------------------------------------------------
// Description  : OSD Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdPowerOnInitial(void)
{
    // Adjust Dither Table
    ///UserAdjustLoadDitherTable();

    // Adjust DCR Threshold & Source
#if(_DCR_SUPPORT == _ON)

#if(_DCR_BIT_MODE == _DCR_GEN_1_0_10BIT)
    ScalerColorDCRAdjust(_DCR_THESHOLD1, _DCR_THESHOLD2, _MEASURE_AVERAGE);
#elif((_DCR_BIT_MODE == _DCR_GEN_0_0_8BIT) || (_DCR_BIT_MODE == _DCR_GEN_0_1_8BIT))
    ScalerColorDCRAdjust((_DCR_THESHOLD1 >> 2), (_DCR_THESHOLD2 >> 2), _MEASURE_AVERAGE);
#endif

#endif

    // Adjust Highlight Window Border
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWBorderAdjust((_HLW_BORDER_BOTTOM | _HLW_BORDER_LEFT | _HLW_BORDER_RIGHT | _HLW_BORDER_TOP), 255, 0, 0);
#endif

#if(_OD_SUPPORT == _ON)
    UserAdjustOD();
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
#if(_AUDIO_SUPPORT == _ON)
    // Set Default Audio Volume
    ScalerAudioDigitalAdjustVolume(0xFFFF);
#endif
#endif
}

//--------------------------------------------------
// Description  : OSD Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdActiveProc(void)
{
    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
    {
        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        UserCommonNVRamSaveSystemData();
    }

    if(UserInterfaceGetActiveByPassStatus() == _FALSE)
    {
        // DDCCI switch to active port
        ScalerMcuDdcciSwitchPort(_ON, SysSourceGetInputPort());

#if(_VGA_SUPPORT == _ON)
        if((SysSourceGetSourceType() == _SOURCE_VGA) && (UserInterfaceGetFirstAutoConfigStatus() == _TRUE))
        {
            ///SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
        }
#endif
    }

#if(_TRANSLATOR_SUPPORT == _OFF)
    ScalerDDomainBackgroundEnable(_DISABLE);
#endif

#if(_FREEZE_SUPPORT == _ON)
    UserCommonAdjustDisplayFreeze(_OFF);
#endif
}

//--------------------------------------------------
// Description  : OSD Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdResetProc(void)
{
}


#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check ModeIndex
// Input Value  : System ModeIndex
// Output Value : ModeIndex
//--------------------------------------------------
BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex)
{
    if((ucModeIndex == _MODE_640x480_60HZ) || (ucModeIndex == _MODE_720x480_60HZ_GTF) || (ucModeIndex == _MODE_720x480p_60HZ))
    {
        if(GET_INPUT_TIMING_VSYNCWIDTH() <= 4)
        {
            ucModeIndex = _MODE_640x480_60HZ;

            DebugMessageAnalog("Detected by Special Case to 640x480-60", _MODE_640x480_60HZ);
        }
        else if((GET_INPUT_TIMING_H_POLARITY() == _FALSE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_720x480_60HZ_GTF;

            DebugMessageAnalog("Detected by Special Case to 720x480-60_GTF", _MODE_720x480_60HZ_GTF);
        }
        else
        {
            ucModeIndex = _MODE_720x480p_60HZ;

            DebugMessageAnalog("Detected by Special Case to 720x480-60", _MODE_720x480p_60HZ);
        }
    }

    if((ucModeIndex == _MODE_720x400_70HZ) || (ucModeIndex == _MODE_640x400_70HZ))
    {
        if((GET_INPUT_TIMING_H_POLARITY() == _TRUE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_640x350_70HZ;

            DebugMessageAnalog("Detected by Special Case to _MODE_640x350_70HZ", _MODE_640x350_70HZ);
        }
    }

    if((ucModeIndex == _MODE_640x400_85HZ) || (ucModeIndex == _MODE_720x400_85HZ))
    {
        if((GET_INPUT_TIMING_H_POLARITY() == _TRUE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_640x350_85HZ;
        }

        DebugMessageAnalog("Detected by Special Case to _MODE_640x350_85HZ", _MODE_640x350_85HZ);
    }

    return ucModeIndex;
}

//--------------------------------------------------
// Description  : Check Load Mode Table Value
// Input Value  : None
// Output Value : _TURE -> Force Load Mode Table Value
//--------------------------------------------------
bit UserInterfaceGetLoadModeTableDefaultStatus(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check VGA First Auto Config
// Input Value  : None
// Output Value : _TRUE => Do Auto Config
//--------------------------------------------------
bit UserInterfaceGetFirstAutoConfigStatus(void)
{
    if((GET_VGA_MODE_DO_FIRST_AUTO() == _TRUE) &&
       (GET_INPUT_TIMING_HWIDTH() > 720))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Percentage of AutoConfig
// Input Value  : Percentage
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage)
{
    ucAutoPercentage = ucAutoPercentage;
}

#if(_VGA_FORCE_DISPLAY == _ON)
//--------------------------------------------------
// Description  : VGA Mode Search User Flow
// Input Value  : None
// Output Value : Mode Number
//--------------------------------------------------
BYTE UserInterfaceModeSearchModeVGA(void)
{
    return 0;
}
#endif

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for V position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSkipAutoVpos(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for H position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSkipAutoHpos(void)
{
    return _FALSE;
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#if(_MHL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User RCP Handler
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode)
{
    // Check RCP Key Code
    switch(ucKeyCode)
    {
        default:
            return _FALSE;
            break;
    }

    return _TRUE;
}
#endif


//--------------------------------------------------
// Description  : Decide whether to Enable FREESYNC Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort)
{
    enumSourcePort = enumSourcePort;

#if(_FREESYNC_SUPPORT == _ON)
    return _FREESYNC_SUPPORT_ON;
#else
    return _FREESYNC_SUPPORT_OFF;
#endif
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : RCP Key Code
// Output Value : DP_VERSION_1_1 or DP_VERSION_1_2
//--------------------------------------------------
EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

#if(_D0_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_1_4;
#else
            return _DP_VERSION_1_2;
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

#if(_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED3_810MHZ)
            return _DP_VERSION_1_4;
#else
            return _DP_VERSION_1_2;
#endif
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            return _DP_VERSION_1_2;
#endif
        default:

            break;
    }

    return _DP_VERSION_1_1;
}

//--------------------------------------------------
// Description  : Get DP Lane Count
// Input Value  : InputPort
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            return _D0_DP_MAIN_LINK_LANES;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            return _D1_DP_MAIN_LINK_LANES;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:
            return _D2_DP_MAIN_LINK_LANES;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:
            return _D6_DP_MAIN_LINK_LANES;
#endif
        default:
            break;
    }

    return _DP_LINK_4_LANE;
}

//--------------------------------------------------
// Description  : Get Dp MST Capable Port
// Input Value  : None
// Output Value : _DP_MST_RX0 or _DP_MST_RX1
//--------------------------------------------------
EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void)
{
#if(_DP_MST_SUPPORT == _OFF)

    return _DP_MST_NO_PORT;
#else

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE != _D1_DP_PORT))

#if(_D0_DP_MST_PORT_SUPPORT == _ON)
    if(UserInterfaceGetDPVersion(_D0_INPUT_PORT) >= _DP_VERSION_1_2)
    {
        return _DP_MST_RX0_PORT;
    }
    else
#endif
    {
        return _DP_MST_NO_PORT;
    }
#elif((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D0_INPUT_PORT_TYPE != _D0_DP_PORT))

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
    if(UserInterfaceGetDPVersion(_D1_INPUT_PORT) >= _DP_VERSION_1_2)
    {
        return _DP_MST_RX1_PORT;
    }
    else
#endif
    {
        return _DP_MST_NO_PORT;
    }
#elif((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

    if(SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT)
    {
#if(_D0_DP_MST_PORT_SUPPORT == _ON)
        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
        {
            if(UserInterfaceGetDPVersion(_D0_INPUT_PORT) >= _DP_VERSION_1_2)
            {
                return _DP_MST_RX0_PORT;
            }
            else
            {
                return _DP_MST_NO_PORT;
            }
        }
        else
#endif

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
        if(SysSourceGetInputPort() == _D1_INPUT_PORT)
        {
            if(UserInterfaceGetDPVersion(_D1_INPUT_PORT) >= _DP_VERSION_1_2)
            {
                return _DP_MST_RX1_PORT;
            }
            else
            {
                return _DP_MST_NO_PORT;
            }
        }
        else
#endif
        {
            return _DP_MST_NO_PORT;
        }
    }

    return _DP_MST_NO_PORT;
#endif // End of #if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE != _D1_DP_PORT))
#endif // End of #if(_DP_MST_SUPPORT == _OFF)
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetDpCloneOutputStatus(void)
{
    return _TRUE;
}
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) || (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
//--------------------------------------------------
// Description  : User Select Externel DP Switch
// Input Value  : None
// Output Value : Only Return _Dx_INPUT_PORT Defined as DP Port
//--------------------------------------------------
BYTE UserInterfaceGetDpSwitchSelectPort(void)
{
    return _D0_INPUT_PORT;
}
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : User flow for embedded DP switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceEmbeddedDpSwitch(void)
{
}
#endif

#if(_DP_DC_ON_HPD_CONTROL_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DC On DP HPD Toggle Mode Control By User
// Input Value  : None
// Output Value : EnumDpHpdToggleMode
//--------------------------------------------------
EnumDpHpdToggleMode UserInterfaceGetDpDcOnHpdMode(void)
{
    return _DP_HPD_TOGGLE_NORMAL;
}
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : User Report HDMI +5V Status
// Input Value  : D0/D1/D2 Port
// Output Value : _TURE --> +5V exist
//--------------------------------------------------
bit UserInterfaceGetHdmi5VStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _TRUE;
        case _D1_INPUT_PORT:
            return _TRUE;
        case _D2_INPUT_PORT:
            return _TRUE;
        case _D3_INPUT_PORT:
            return _TRUE;
        default:
            return _TRUE;
    }
}
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
//--------------------------------------------------
// Description  : User check search is finish or not
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit UserInterfaceAdjustOsdCheckTotalSearchFinish(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Determine the search time of each source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustSourceSearchTime(void)
{
}

//--------------------------------------------------
// Description  : Determine the search time of each source
// Input Value  : Input Port Type
// Output Value : Search Reative Time
//--------------------------------------------------
WORD UserInterfaceAdjustSourceReactiveSearchTime(EnumSourceAdjustReactiveTimePortType enumSourceAdjustReactiveTimePortType)
{
    switch(enumSourceAdjustReactiveTimePortType)
    {
        case _ADJUST_PORT_VGA:

            return SEC(2);

        case _ADJUST_PORT_TMDS:

            return SEC(4.5);

        case _ADJUST_PORT_MHL:

            return SEC(6);

        case _ADJUST_PORT_DP:

            return SEC(4);

        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : User Report Eizo Search Finish Time
// Input Value  : None
// Output Value : Search Finish Time
//--------------------------------------------------
WORD UserInterfaceGetEizoSearchFinishTime(void)
{
    return 0;
}
#endif

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Determine whether to User is Ready to play audio
// Input Value  : None
// Output Value : _TRUE => Free to Play
//--------------------------------------------------
bit UserInterfaceGetAudioReadyToPlayStatus(void)
{
    if(UserInterfaceGetAudioMuteStatus() != _ON)
    {
        if(UserInterfaceGetAudioSource() == _DIGITAL_AUDIO)
        {
            if(ScalerAudioGetAudioDetected(SysSourceGetInputPort()) == _TRUE)
            {
                if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) || (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK))
                {
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Current Audio Mute Status
// Input Value  : Node
// Output Value : Node
//--------------------------------------------------
bit UserInterfaceGetAudioMuteStatus(void)
{
    return _OFF;
}

//--------------------------------------------------
// Description  : User OSD Get Audio Source
// Input Value  : None
// Output Value : _DIGITAL_AUDIO or _LINE_IN_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserInterfaceGetAudioSource(void)
{
    switch(SysSourceGetSourceType())
    {
        case _SOURCE_HDMI:
        case _SOURCE_DP:

            return _DIGITAL_AUDIO;

        case _SOURCE_VGA:
        case _SOURCE_DVI:

            return _LINE_IN_AUDIO;

        default:

            break;
    }
    return _LINE_IN_AUDIO;
}

//--------------------------------------------------
// Description  : User Decide whether to play non-LPCM Audio
// Input Value  : None
// Output Value : _ON => Mute Audio
//--------------------------------------------------
bit UserInterfaceGetAudioNonLPCMStatus(void)
{
    if(ScalerAudioLPCMCheckData(SysSourceGetInputPort()) == _TRUE)
    {
#if(_HDMI_SUPPORT == _ON)
        if(SysSourceGetSourceType() == _SOURCE_HDMI)
        {
            if(ScalerAudioLPCMCheckInfo(SysSourceGetInputPort()) == _TRUE)
            {
                return _OFF;
            }
            else
            {
                return _ON;
            }
        }
#endif

        return _OFF;
    }

    return _ON;
}

//--------------------------------------------------
// Description  : Get Current Audio Volume
// Input Value  : None
// Output Value : Current Volume
//--------------------------------------------------
WORD UserInterfaceGetAudioVolume(void)
{
    return 0x3FFF;
}

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DAC Output Switch
// Input Value  : None
// Output Value : EnumAudioDACOutput
//--------------------------------------------------
EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void)
{
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _ON) && (_DAC_HP_OUTPUT_SUPPORT == _ON))
    return _AUDIO_DAC_OUTPUT_BOTH;
#elif(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
    return _AUDIO_DAC_OUTPUT_SPEAKER;
#elif(_DAC_HP_OUTPUT_SUPPORT == _ON)
    return _AUDIO_DAC_OUTPUT_HEADPHONE;
#endif
}

//--------------------------------------------------
// Description  : Get if Keep Audio Depop State
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceGetAudioDACKeepDepopState(void)
{
    return _FALSE;
}
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current Audio Stand Alone Status
// Input Value  : enumPowStatus
// Output Value : Node
//--------------------------------------------------
bit UserInterfaceGetAudioStandAloneStatus(void)
{
    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : User Audio Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAudioResetProc(void)
{
#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
    {
        // if Currently playing digital audio
        if((SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK) && (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO))
        {
#if(((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
            if(SysSourceGetAudioPlaybackPort() != SysSourceGetInputPort())
#endif
            {
                DebugMessageAudio("User Audio Reset Process", 0x00);

                SysAudioMuteProc(_ON);
            }
        }
    }
    else
#endif
    {
        if(SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK)
        {
            DebugMessageAudio("User Audio Reset Process", 0x00);

            SysAudioMuteProc(_ON);
        }
    }
}

//--------------------------------------------------
// Description  : Audio Power Process
// Input Value  : enumPowStatus
// Output Value : Node
//--------------------------------------------------
void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus)
{
    if(enumPowStatus == _POWER_STATUS_NORMAL)
    {
        // Add User interface function

    }
    else if(enumPowStatus == _POWER_STATUS_SAVING)
    {
        // Add User interface function
    }
    else
    {
        // Add User interface function
    }
}

//--------------------------------------------------
// Description  : Control User Audio Mute Process
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAudioAmpMuteProc(bit bMute)
{
    bMute = bMute;

#if(_EMBEDDED_DAC_SUPPORT == _ON)
#if((_DAC_SPEAKER_OUTPUT_SUPPORT == _ON) && (_DAC_HP_OUTPUT_SUPPORT == _ON))
    if(UserInterfaceGetAudioDACOutput() == _AUDIO_DAC_OUTPUT_BOTH)
#elif(_DAC_SPEAKER_OUTPUT_SUPPORT == _ON)
    if(UserInterfaceGetAudioDACOutput() == _AUDIO_DAC_OUTPUT_SPEAKER)
#elif(_DAC_HP_OUTPUT_SUPPORT == _ON)
    if(UserInterfaceGetAudioDACOutput() == _AUDIO_DAC_OUTPUT_HEADPHONE)
#endif
    {
        PCB_AMP_MUTE(bMute);
    }
#endif
}

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
//--------------------------------------------------
// Description  : Swap External Audio Codec Input for Line in
// Input Value  : _TRUE or _FALSE
// Output Value : None
//--------------------------------------------------
void UserInterfaceSwapExternalAudioCodecInput(bit bSwap)
{
    if(bSwap == _TRUE)
    {
        // Swap External Audio Codec Input(L/R)
    }
    else
    {
        // No Swap External Audio Codec Input(L/R)
    }
}
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
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
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            if(GET_OSD_D1_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            if(GET_OSD_D6_TYPE_C_U3_MODE() == _TYPE_C_U3_ON)
            {
                return _TRUE;
            }
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
    ucInputPort = ucInputPort;
    return 0;
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
#endif

#if(_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return _FALSE;
#endif

#if(_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            return _FALSE;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Adjust Type-C Dp Lanes
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn)
{
    ucInputPort = ucInputPort;
    bEn = bEn;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Config Config Proc
// Input Value  : None
// Output Value : None
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
    ucInputPort = ucInputPort;
    StructTypeCLenovoSysEvent stLenovoSysEvent;

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
    ucInputPort = ucInputPort;
    enumPowerRole = enumPowerRole;
    return _TYPE_C_PDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Get TypeC RDO From User / Kernel
// Input Value  : ucInputPort --> Input Port
// Output Value : return RDO from USER / KERNEL
//--------------------------------------------------
EnumTypeCEmbRdoReference UserInterfaceTypeCRdoReference(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;
    return _TYPE_C_RDO_FROM_KERNEL;
}

//--------------------------------------------------
// Description  : Embedded Port Controller Max Power
// Input Value  : ucInputPort --> Input Port
// Output Value : return Max Power (Unit = 0.1W)
//--------------------------------------------------
WORD UserInterfaceTypeCGetMaxPower(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // Default Max Power = 270 * 0.1 = 27W
    return 270;
}

//--------------------------------------------------
// Description  : Embedded Port Controller PDO Count
// Input Value  : ucInputPort --> Input Port
//              : enumPowerRole --> _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : return Number of PDOs
//--------------------------------------------------
EnumTypeCPdoNumber UserInterfaceTypeCGetPdoCount(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole)
{
    ucInputPort = ucInputPort;
    enumPowerRole = enumPowerRole;

    // Default PDO Count = 2
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
    ucInputPort = ucInputPort;
    ucPdoIndex = ucPdoIndex;
    pstTypeCUserSrcPdo = pstTypeCUserSrcPdo;
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
    ucInputPort = ucInputPort;
    ucPdoIndex = ucPdoIndex;
    pstTypeCUserSnkPdo = pstTypeCUserSnkPdo;
}

//--------------------------------------------------
// Description  : Kernel Get Embedded Port Controller Request Info
// Input Value  : ucInputPort --> Input Port
//                *pstTypeCUserRdo --> Request Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceTypeCGetRdoInfo(BYTE ucInputPort, StructTypeCUserRDO *pstTypeCUserRdo)
{
    ucInputPort= ucInputPort;
    pstTypeCUserRdo = pstTypeCUserRdo;
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
    ucInputPort = ucInputPort;
    ucPdoIndex = ucPdoIndex;
    pstTypeCUserProtectInfo = pstTypeCUserProtectInfo;
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

            enumHubInputPort = GET_USER_USB_HUB_UFP_SWITCH();

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

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : User function Before Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
    }
    else // OGC/OCC/DICOM
    {
    }
}

//--------------------------------------------------
// Description  : User function After Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
    }
    else // OGC/OCC/DICOM
    {
    }
}
#endif

#if(_YPEAKING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Ypeaking Table
// Input Value  : Request Ypeaking Table
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustYpeaking(void)
{
    ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x41, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
}
#endif // End of #if(_YPEAKING_SUPPORT == _ON)

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// Description  : Get DDC-CI Mode
// Input Value  : None
// Output Value : EnumDDCCIDebugMode:_DEBUG_MODE / _DDCCI_MODE
//--------------------------------------------------
EnumDDCCIDebugMode UserInterfaceGetDdcciMode(void)
{
    return _DDCCI_MODE;
}

//--------------------------------------------------
// Description  : Get Repeater Into Power Off Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumDataExchangeRepeaterPowerState UserInterfaceGetRepeaterIntoPowerOff(void)
{
    return _DATA_EXCHANGE_REPEATER_POWER_NORMAL;
}
#endif
#endif //#if(_OSD_TYPE == _NONE_OSD)
