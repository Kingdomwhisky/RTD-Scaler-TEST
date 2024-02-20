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
// ID Code      : RTD2014UserInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE__

#include "UserCommonInclude.h"
#include "RTD2014UserHDMIEdid.h"
#include "RTD2014UserDPEdid.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _USER_SHOW_LOGO_STEP                    18 // frames

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

#if(_DP_FREESYNC_SUPPORT == _ON)
#define _USER_DP_DRR_CLK_MARGIN                 (1)
#define _USER_DP_DRR_HTOTAL_MARGIN              (1)

#define GET_DRR_IHWIDTH(x)                      (tDrrFreeSyncDpTimingInfo[(x)].usIHwidth)
#define GET_DRR_IVHEIGHT(x)                     (tDrrFreeSyncDpTimingInfo[(x)].usIVheight)
#define GET_DRR_IHTOTAL(x)                      (tDrrFreeSyncDpTimingInfo[(x)].usIHtotal)
#define GET_DRR_ICLK(x)                         (tDrrFreeSyncDpTimingInfo[(x)].usPixelClk)
#define GET_DRR_IVFREQ(x)                       (tDrrFreeSyncDpTimingInfo[(x)].usIVfreq)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
StructDrrFreeSyncDpTimingInfo code tDrrFreeSyncDpTimingInfo[] =
{
    // Hwidth, Vheight, Htotal, Pixel clk (0.1M), Vfreq (0.1Hz)
    {1920, 1080, 2200, 1485, 600},
    {2560, 1440, 2720, 2415, 600},

    // Established Timing Info
    {720,  400,  888,  283,  702},//720 x 400 at 70Hz - IBM VGA
    {720,  400,  907,  355,  882},//720 x 400 at 88Hz - IBM XGA2
    {640,  480,  800,  251,  600},//640 x 480 at 60Hz - IBM VGA
    {640,  480,  864,  302,  667},//640 x 480 at 67Hz - Mac II
    {640,  480,  832,  315,  728},//640 x 480 at 72Hz - VESA
    {640,  480,  840,  315,  750},//640 x 480 at 75Hz - VESA
    {800,  600,  1024, 360,  562},//800 x 600 at 56Hz - VESA
    {800,  600,  1056, 400,  603},//800 x 600 at 60Hz - VESA
    {800,  600,  1040, 500,  722},//800 x 600 at 72Hz - VESA
    {800,  600,  1056, 495,  750},//800 x 600 at 75Hz - VESA
    {832,  624,  1152, 572,  745},//832 x 624 at 75Hz - Mac II
    {1024, 768,  1264, 898,  870},//1024 x 768 at 43Hz - IBM 8514a
    {1024, 768,  1344, 650,  600},//1024 x 768 at 60Hz - VESA
    {1024, 768,  1328, 750,  700},//1024 x 768 at 70Hz - VESA
    {1024, 768,  1312, 787,  750},//1024 x 768 at 75Hz - VESA
    {1280, 1024, 1688, 1350, 750},//1280 x 1024 at 75Hz - VESA
    {1152, 870,  1456, 1000, 750},//1152 x 870 at 75Hz - Mac II
};
#endif

//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#if(_SHARPNESS_SUPPORT == _ON)
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
#endif // End of #if(_SHARPNESS_SUPPORT == _ON)

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

#if(_HDR10_SUPPORT == _ON)
BYTE code tCOLOR_ULTRAVIVID_SETTING_HDR[] =
{
#include "./UltraVivid/UltraVividTableHDR.h"
};
#endif
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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// for RTD Tool IIC Debug
//-------------------------------------------------------
#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
bit UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue);
#endif

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
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
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
extern EnumUSBPDSupportStatus UserInterfaceGetUSBPDSupportStatus(void);
extern EnumUSBPSSupportStatus UserInterfaceGetUSBPSSupportStatus(void);
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
void UserInterfaceAdjustWaitPanelT4(void);
void UserInterfaceAdjustWaitPanelT5(void);

//-------------------------------------------------------
//
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

EnumColorSpace UserInterfaceGetColorFormat(void);

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
BYTE UserInterfaceGetHpSourceSwitchOsdEventTime(BYTE ucSourceScanType);
#endif

#if(_OVERSCAN_SUPPORT == _ON)
bit UserInterfaceGetOverScanStatus(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
EnumAspectRatioType UserInterfaceGetAspectRatioType(void);
void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio);
void UserInterfaceAdjustAspectRatio(void);
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
WORD UserInterfaceGetAspectRatioMinDVHeight(void);
#endif

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

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
void UserInterfaceMbrBacklightAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl, WORD usDVTotal);
void UserInterfaceMbrAdimAdjust(EnumMbrBacklightMode enumBacklightMode);
EnumMbrBacklightMode UserInterfaceMbrGetBacklightMode(void);
BYTE UserInterfaceMbrGetBacklightDuty(void);
BYTE UserInterfaceMbrGetBacklightPos(void);
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
EnumRtkAdvMbrUserStatus UserInterfaceGetRtkAdvMbrSetting(void);
#endif
#endif

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
void UserInterfaceDisplayInitialization(void);
void UserInterfaceAdjustInputTiming(void);

#if(_UNDERSCAN_SUPPORT == _ON)
bit UserInterfaceAdjustUnderScan(void);
#endif

void UserInterfaceAdjustDisplayTiming(void);

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

#if(_DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW == _ON)
EnumDPMSTPort UserInterfaceGetDpMstTargetPort(void);
#endif

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
EnumAudioInputSource UserInterfaceGetAudioSource(void);
bit UserInterfaceGetAudioMuteStatus(void);
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

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
void UserInterfaceAdjustBacklight(BYTE ucBacklight);
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
void UserInterfaceAdjustBeforeDimmingCalibration(void);
void UserInterfaceAdjustAfterDimmingCalibration(void);
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
void UserInterfaceAdjustLDBoostCalibration(bit bBoost);
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
// Description  : User timer event process
// Input Value  : Event ID
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

        case _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO:
            OsdDispDisableOsd();
            SET_OSD_LOGO_ON(_OFF);

#if(_INSTANT_TIMER_EVENT_0 == _ON)
            ScalerTimer0SetTimerCount(_TIMER_OFF);
#endif

#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
#else
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);
#endif
            ScalerDDomainBackgroundEnable(_ENABLE);
            ScalerDDomainPatternGenEnable(_DISABLE);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOCABLE_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSIGNAL_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG);
            break;

        case _USER_TIMER_EVENT_GO_TO_POWER_SAVING:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_DISABLE:
            OsdDispDisableOsd();
            break;

        case _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON:
            SET_PANELPOWERSTATUS(_READY_FOR_BACKLIGHT);
            break;

        case _USER_TIMER_EVENT_PANEL_POWER_OFF:
            SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);
            break;

#if(_VGA_SUPPORT == _ON)
        case _USER_TIMER_EVENT_DO_AUTO_COLOR:
            CLR_KEY_HOLD();
            OsdDisplayAutoBalanceProc();
            break;
#endif

        case _USER_TIMER_EVENT_PANEL_USED_TIMER:
            RTDFactoryPanelUsedTimer();
            break;

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
        case _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE:
            UserAdjustHLWinType5Move();
            break;
#endif

        case _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT:
            OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNHIGHLIGHT);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT:
            CLR_KEY_HOLD();

            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_TRUE);
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
            }
            else
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DP_VERSIOM_MSG);
            }

            break;

#if(_HDMI_CEC_SUPPORT == _ON)
        case _USER_TIMER_EVENT_CEC_LA_POLLING:

            g_bCecLaPollingStart = 1;
            g_ucCecLaCnt = 0;
            break;
#endif


#if(_FREESYNC_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ:
            if((GET_OSD_STATE() == _MENU_INFORMATION) && (ScalerSyncGetFREESYNCEnable() == _TRUE))
            {
                g_ucFontPointer1 = GET_FREESYNC_OSD_ADDRESS();
                OsdPropPutString(ROW(14 + 1), COL(16), _PFONT_PAGE_1, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
            }
            break;
#endif
#if(_FREEZE_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG:
            OsdFuncDisableOsd();
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_OSD_STATE() != _MENU_NONE))
            {
                OsdFuncShowOSDAfterClosedFreezeMsg();
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
                SET_FREEZE_DISABLE_MSG_STATE(_OFF);
#endif
            }
            break;
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        case _USER_TIMER_EVENT_HDR_BOOST:
            g_bHdrBoost = _FALSE;
            break;

        case _USER_TIMER_EVENT_HDR_COOL:
            g_bHdrBoost = _TRUE;
            break;
#endif
        default:
            break;
    }
}

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
//--------------------------------------------------
// Description  : User Debug Tool Page IIC
// Input Value  : Event ID
// Output Value : None
//--------------------------------------------------
bit UserInterfaceDebugIIC(BYTE ucType, BYTE *pucDdcciArray, BYTE *pucReturnValue)
{
    bit bDebugMode = _FALSE;

    pucDdcciArray = pucDdcciArray;
    pucReturnValue = pucReturnValue;

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    if(bDebugMode == _FALSE)
    {
        bDebugMode = ExternalDeviceInterfaceLedDriverDebug(ucType, pucDdcciArray, pucReturnValue);
    }
#endif

    return bDebugMode;
}
#endif

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
    if(GET_OSD_LOGO_ON() == _ON)
    {
        if(g_ucLogoTimerCounter != 0xFF)
        {
            g_ucLogoTimerCounter++;
        }

        switch(g_ucLogoTimerCounter)
        {
            case _USER_SHOW_LOGO_STEP:
            case (_USER_SHOW_LOGO_STEP * 2):
            case (_USER_SHOW_LOGO_STEP * 3):
            case (_USER_SHOW_LOGO_STEP * 4):
            case (_USER_SHOW_LOGO_STEP * 5):
            case (_USER_SHOW_LOGO_STEP * 6):
            case (_USER_SHOW_LOGO_STEP * 7):

                ScalerOsdSetTransparency_EXINT(0xFF - (g_ucLogoTimerCounter / _USER_SHOW_LOGO_STEP) * 36);

                break;

            default:

                break;
        }
    }
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

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get Source Opcode is HDMI freesync
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(void) using 2
{
    if(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE] == _HDMI_FREESYNC_MCCS_VCP)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
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
    BYTE ucHdmiVer = OsdFuncGetHdmiPortVersion(ucInputPort);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    if((GET_OSD_FREE_SYNC_STATUS() == _ON))
    {
        enumIndex += ((_HDMI_HDR10_SUPPORT == _ON) ? 0x06 : 0x03);
    }
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
    if((UserInterfaceHDRGetHDR10ModeStatus(ucInputPort) != _HDR10_MODE_OFF))
    {
        enumIndex += 0x03;
    }
#endif

    switch(ucHdmiVer)
    {
        case _HDMI_1P4:
            break;

        case _HDMI_2P0:
            enumIndex += 0x01;
            break;

        case _HDMI_2P1:
            enumIndex += 0x02;
            break;

        default:
            break;
    }
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
#endif // #if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

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
#endif // #if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

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
#endif // #if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

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
#endif // #if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

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
#endif // #if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

#if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
        case _D6_INPUT_PORT_EDID:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

            memset(MCU_DDCRAM_D6, 0, _D6_EMBEDDED_DDCRAM_MAX_SIZE);
            memcpy(MCU_DDCRAM_D6, tDP_EDID_TABLE[UserAdjustGetDpEdidIndex(_D6_INPUT_PORT)], _D6_EMBEDDED_DDCRAM_MAX_SIZE);

#endif
            break;
#endif // #if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)

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
    EnumUSBPDSupportStatus enumUSBPDSupportStatus = _USB_PD_DISABLE;

    if(GET_OSD_USB3_RETIMER_PD_WAKEUP() == _TRUE)
    {
        enumUSBPDSupportStatus = _USB3_PD_ENABLE;
    }
    else
    {
        enumUSBPDSupportStatus = _USB_PD_DISABLE;
    }

    return enumUSBPDSupportStatus;
}

//--------------------------------------------------
// Description  : Get USB3 Retimer PS Support Status
// Input Value  : void
// Output Value : EnumUSBPSSupportStatus
//--------------------------------------------------
EnumUSBPSSupportStatus UserInterfaceGetUSBPSSupportStatus(void)
{
    EnumUSBPSSupportStatus enumUSBPSSupportStatus = _USB_PS_DISABLE;

    if(GET_OSD_USB3_RETIMER_PS_WAKEUP() == _TRUE)
    {
        enumUSBPSSupportStatus = _USB3_PS_ENABLE;
    }
    else
    {
        enumUSBPSSupportStatus = _USB_PS_DISABLE;
    }

    return enumUSBPSSupportStatus;
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
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Tx HDCP Aksv By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
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
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2RRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2DcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2EKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP2.2 TX KEY -- RRMODN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetDpTxHdcp2NPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
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

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T4
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT4(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_OFF_T4);
}

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
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
        bUncall = tFLASH_PARTITION_BOOTTABLE[0];
#endif

        UserInterfaceGetDisplaySettingBacklightAction();

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
        ExternalDeviceInterfaceLedDriverPwm(_DEVICE_LED_DRIVER_PWM_ALL, 0, _DEVICE_CALI_OFF);
#if(_LD_HDR10_BOOST_SUPPORT == _ON)
        ExternalDeviceInterfaceLedDriverPwmArrayBoostMode(0, 100);
#else
        ExternalDeviceInterfaceLedDriverPwmArray(0);
#endif
        ExternalDeviceInterfaceLedDriverPwmEnable(_ENABLE);
        ExternalDeviceInterfaceLedDriverBacklight(0);
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

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        UserCommonInterfacceMbrGetCurrentBacklightMode();
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
    PCB_PWM_SETTING();
    RTDNVRamStartup();

    UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), UserCommonNVRamGetSystemData(_SEARCH_PORT));
    RTDKeyInitial();
    SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);

    // Adjust Backlight
    UserAdjustBacklight(GET_OSD_BACKLIGHT());

    // Adjust IR Decode
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    UserAdjusIR();
#endif
    SET_OSD_DOUBLE_SIZE(GET_OSD_NVRAM_DOUBLE_SIZE());

#if(_USB3_RETIMER_SUPPORT == _ON)

    // Initilize PSPD USB Function marco
    SET_OSD_USB3_RETIMER_PD_WAKEUP(_TRUE);
    SET_OSD_USB3_RETIMER_PS_WAKEUP(_TRUE);

    // Initilize Hub Input Port
    // If we realize the Hub UFP Switch with OSD Button, we shold set initial value to NVRam
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

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    ScalerTimer0SetTimerCount(_TIMER_OFF);
#endif
}

//--------------------------------------------------
// Description  : Keypad Led Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed)
{
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
}


//--------------------------------------------------
// Description  : User OSD Get LogoOn
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetLogoStatus(void)
{
    return (GET_OSD_LOGO_ON());
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

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get whether to by pass normal active process
// Input Value  : None
// Output Value : _TRUE => By pass normal active process
//--------------------------------------------------
bit UserInterfaceGetActiveByPassStatus(void)
{
    if((GET_OSD_STATE() == _MENU_COLOR_FORMAT) || (GET_OSD_STATE() == _MENU_COLOR_FORMAT_ADJUST))
    {
        return _FALSE;
    }

    if(GET_OSD_STATE() != _MENU_NONE)
    {
        return _TRUE;
    }

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
        SET_FORCE_POW_SAV_STATUS(_FALSE);

        if(SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT)
        {
            SysSourceSwitchInputPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
        }

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
    return (GET_FORCE_POW_SAV_STATUS());
}

//--------------------------------------------------
// Description  : User Check Into Power Saving
// Input Value  : None
// Output Value : True --> User Check Ready to Power Saving
//--------------------------------------------------
bit UserInterfaceGetIntoPSStatus(void)
{
    if(ScalerOsdGetOsdEnable() == _TRUE)
    {
        return _FALSE;
    }

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

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() != UserInterfaceGetRotationDegree()) ||
       (GET_ROT_DISP_SIZE() != UserInterfaceGetRotationDisplayType()))
    {
        return _DISABLE;
    }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_ROT_TYPE() != _ROT_DISABLE)
#endif
    {
        if(GET_DISP_LATENCY_RATIO() != UserInterfaceGetDisplayLatencyRatio())
        {
            return _DISABLE;
        }
    }
#endif

    return _ENABLE;

#endif
}

//--------------------------------------------------
// Description  : Get OSD Color Format
// Input Value  : None
// Output Value : Color Format
//--------------------------------------------------
EnumColorSpace UserInterfaceGetColorFormat(void)
{
    EnumColorSpace enumColorSpace = ScalerColorGetColorSpace();

#if(_COLOR_FORMAT_CONVERT == _ON)
    switch(SysSourceGetSourceType())
    {
        case _SOURCE_VGA:
        case _SOURCE_DVI:
            enumColorSpace = GET_OSD_COLOR_FORMAT();
            break;

        default:
            break;
    }
#endif

    if(ScalerColorGetColorSpaceRGB(enumColorSpace) == _TRUE)
    {
        return _COLOR_SPACE_RGB;
    }
    else
    {
        return _COLOR_SPACE_YPBPR;
    }
}

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HP Source Switch Event Time
// Input Value  : Source Scan Type
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetHpSourceSwitchOsdEventTime(BYTE ucSourceScanType)
{
    ucSourceScanType = ucSourceScanType;
    return 0;
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

#if(_OVERSCAN_DP_SUPPORT != _ON)
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
// Input Value  : None
// Output Value : aspect ration type
//--------------------------------------------------
EnumAspectRatioType UserInterfaceGetAspectRatioType(void)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE())
    {
        case _OSD_ASPECT_RATIO_16_BY_9:
        case _OSD_ASPECT_RATIO_4_BY_3:
        case _OSD_ASPECT_RATIO_5_BY_4:

            return _ASPECT_RATIO_FIXED;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
        case _OSD_ASPECT_RATIO_ORIGIN:

            return _ASPECT_RATIO_ORIGIN;
        case _OSD_ASPECT_RATIO_USER:
            return _ASPECT_RATIO_ORIGIN;
#endif

        default:
        case _OSD_ASPECT_RATIO_FULL:

            return _ASPECT_RATIO_FULL;
    }
}

//--------------------------------------------------
// Description  : Get user H/V aspect ratio values
// Input Value  : enumSelRegion --> select region
//                usHRatio, usVRatio --> aspect ratio
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE())
    {
        default:
            break;

        case _OSD_ASPECT_RATIO_16_BY_9:
            *pusHRatio = 16;
            *pusVRatio = 9;
            break;

        case _OSD_ASPECT_RATIO_4_BY_3:
            *pusHRatio = 4;
            *pusVRatio = 3;
            break;

        case _OSD_ASPECT_RATIO_5_BY_4:
            *pusHRatio = 5;
            *pusVRatio = 4;
            break;
    }
}

//--------------------------------------------------
// Description  : User defined aspect ratio process
// Input Value  : select region
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAspectRatio(void)
{
}

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//--------------------------------------------------
// Description  : User defined minimum dvheight for aspect ratio
//                use 1:1 for example
// Input Value  : None
// Output Value : usMinDvheight
//--------------------------------------------------
WORD UserInterfaceGetAspectRatioMinDVHeight(void)
{
    WORD usMinDvheight = (GET_INPUT_TIMING_VHEIGHT() < GET_MDOMAIN_OUTPUT_VHEIGHT()) ? GET_INPUT_TIMING_VHEIGHT() : GET_MDOMAIN_OUTPUT_VHEIGHT();
    // return 0 if disable the function
    return usMinDvheight;
}
#endif

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
    if(GET_OSD_ASPECT_RATIO_TYPE() == _OSD_ASPECT_RATIO_USER)
    {
        return 0xCC;
    }
    else
    {
        return 0xFF;
    }
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
#if (_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_HOR_MIRROR:
            return _ROT_HOR_MIRROR;
#endif
#if (_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_VER_MIRROR:
            return _ROT_VER_MIRROR;
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
#endif

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

#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust backlight setting
// Input Value  : Backlight Mode, Backlight On/Off
// Output Value : None
//--------------------------------------------------
void UserInterfaceMbrBacklightAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl, WORD usDVTotal)
{
    BYTE ucBacklightDuty = 0; // Backlight ON percentage
    BYTE ucBacklightPos = 0; // Backlight Position percentage
    WORD usStrobeVWidth = 0; // Backlight ON lines
    WORD usStrobeVPos = 0; // Backlight ON Position (lines)

    DebugMessageScaler("MBR: bLightCtrl", bLightCtrl);
    DebugMessageScaler("MBR: VTotal", usDVTotal);
    DebugMessageScaler("MBR: ucBacklightDuty", GET_OSD_MBR_DUTY());
    DebugMessageScaler("MBR: ucBacklightPos", GET_OSD_MBR_POSITION());

    switch(enumBacklightMode)
    {
        //=================================================================
        // User customized motion blur reduction mode
        //=================================================================
        case _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR:
            /*
             Strobe Backlight Position
               _____       ________________________     _____
              |     |     |                        |   |     |
              |VSync|_____|         Duty           |___|VSync|___
                         Pos                   Pos + Duty

               _____                        ________________________
              |     |                      |                        |
              |VSync|______________________|         Duty           |___
                                          Pos                  Pos + Duty
            */

            if(bLightCtrl == _LIGHT_CONTROL_ON)
            {
                // Backlight strobe ctrl (Tcon local enable...)
                ucBacklightDuty = GET_OSD_MBR_DUTY();
                ucBacklightPos = GET_OSD_MBR_POSITION();
                usStrobeVPos = (WORD)((DWORD)ucBacklightPos * usDVTotal / 100L);
                usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * usDVTotal / 100L);
                if(ucBacklightDuty == 100)
                {
                    ScalerTconAdjustByIndex(_PCB_MBR_TCON_PIN, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
                }
                else
                {
                    ScalerTconAdjustByIndex(_PCB_MBR_TCON_PIN, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth) % usDVTotal);
                }
                ScalerTconEnableByIndex(_PCB_MBR_TCON_PIN, _ENABLE);
            }
            else
            {
                // Setting in _LIGHT_CONTROL_OFF case
                ScalerTconEnableByIndex(_PCB_MBR_TCON_PIN, _DISABLE);
            }
            break;

        //=================================================================
        // Constant backlight mode
        //=================================================================
        default:
        case _BACKLIGHT_MODE_CONSTANT:
            if(bLightCtrl == _LIGHT_CONTROL_ON)
            {
                // Backlight Ctrl
                // Set TCON to always ON and/or disable strobe ctrl pins...
                ScalerTconAdjustByIndex(_PCB_MBR_TCON_PIN, 0x0000, 0x1FFF, 0x0000, 0x3FFF);

                ScalerTconEnableByIndex(_PCB_MBR_TCON_PIN, _ENABLE);
            }
            else
            {
                // Setting in _LIGHT_CONTROL_OFF case
                ScalerTconEnableByIndex(_PCB_MBR_TCON_PIN, _DISABLE);
            }
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Backlight ADIM (normally controled by scaler PWM)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceMbrAdimAdjust(EnumMbrBacklightMode enumBacklightMode)
{
    switch(enumBacklightMode)
    {
        // In strobe backlight case, set scaler PWM to full duty
        case _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR:
        case _BACKLIGHT_MODE_STROBE_DRR_MBR:
        case _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR:
            PCB_PWM_SETTING();
            PCB_BACKLIGHT_PWM(0xFF);
            break;

        // In constant backlight case, set scaler PWM according to user setting
        case _BACKLIGHT_MODE_CONSTANT:
        default:
            PCB_PWM_SETTING();
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
            break;
    }
}

//--------------------------------------------------
// Description  : Judge MBR Backlight Mode
// Input Value  : None
// Output Value : Backlight Mode
//--------------------------------------------------
EnumMbrBacklightMode UserInterfaceMbrGetBacklightMode(void)
{
    if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_DISABLE) // Constant backlight
    {
        return _BACKLIGHT_MODE_CONSTANT;
    }
    else if(GET_OSD_MBR_STATUS() == _OSD_MBR_USER_ENABLE) // User want to control backlight
    {
        return _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR;
    }
    else if(GET_OSD_MBR_STATUS() == _OSD_RTK_ADV_MBR_USER_ENABLE)
    {
#if((_FREESYNC_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        if((ScalerSyncGetFREESYNCEnable() == _TRUE) && (UserCommonInterfaceMbrDrrGetHWSupport() == _TRUE))
        {
            return _BACKLIGHT_MODE_STROBE_DRR_MBR;
        }
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        if(ScalerMbrGetAdvMbrStatus() == _ENABLE)
        {
            return _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR;
        }
#endif
        return _BACKLIGHT_MODE_CONSTANT;
    }

    return _BACKLIGHT_MODE_CONSTANT;
}

//--------------------------------------------------
// Description  : Get User MBR Backlight Duty
// Input Value  : None
// Output Value : Backlight Duty
//--------------------------------------------------
BYTE UserInterfaceMbrGetBacklightDuty(void)
{
    return (BYTE)GET_OSD_MBR_DUTY();
}

//--------------------------------------------------
// Description  : Get User MBR Backlight Position
// Input Value  : None
// Output Value : Backlight Position
//--------------------------------------------------
BYTE UserInterfaceMbrGetBacklightPos(void)
{
    return (BYTE)GET_OSD_MBR_POSITION();
}


#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Motion Blur Reduction Function
//                Accroding to User Selection
// Input Value  : None
// Output Value : _RTK_ADV_MBR_USER_DISABLE/_RTK_ADV_MBR_USER_ENABLE
//--------------------------------------------------
EnumRtkAdvMbrUserStatus UserInterfaceGetRtkAdvMbrSetting(void)
{
    if((GET_OSD_MBR_STATUS() == _OSD_RTK_ADV_MBR_USER_ENABLE) && (GET_INPUT_TIMING_VFREQ() >= _RTK_ADV_MBR_MIN_ENABLE_IVF))
    {
        return _RTK_ADV_MBR_USER_ENABLE;
    }

    return _RTK_ADV_MBR_USER_DISABLE;
}
#endif // End of #if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#endif // End of #if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)

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
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustInputTiming(void)
{
}

#if(_UNDERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceAdjustUnderScan(void)
{
    if((GET_INPUT_TIMING_HWIDTH() == 640) && (GET_INPUT_TIMING_VHEIGHT() == 350))
    {
        SET_UNDERSCAN_VHEIGHT(400);
        return _TRUE;
    }

    return _FALSE;
}
#endif

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

#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
//--------------------------------------------------
// Description  : User Judge if Quantization Range is Full or Limited
// Input Value  : EnumDisplayRegion --> display region
//                ucQuanRange --> quantization status
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization)
{
#if(_HDR10_SUPPORT == _ON)
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
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
    else
#endif
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
    switch(enumColorYCCQuantization)
    {
        case _YCC_QUANTIZATION_FULL_RANGE:
        case _YCC_QUANTIZATION_RESERVED:
        default:

            return _TRUE;

        case _YCC_QUANTIZATION_LIMIT_RANGE:

            return _FALSE;
    }
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
    if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_OTHER_RESET))
    {
        // Set Color Conversion
        switch(SysSourceGetInputPort())
        {
            case _A0_INPUT_PORT:

                SET_OSD_COLOR_FORMAT(GET_VGA_COLOR_FORMAT_STATUS());

                break;

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
            case _D0_INPUT_PORT:
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
            case _D1_INPUT_PORT:
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DVI_PORT)
            case _D2_INPUT_PORT:
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DVI_PORT)
            case _D3_INPUT_PORT:
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) ||\
    (_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DVI_PORT))
                SET_OSD_COLOR_FORMAT(GET_DVI_COLOR_FORMAT_STATUS());
                break;
#endif

            default:

                if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _TRUE)
                {
                    SET_OSD_COLOR_FORMAT(_COLOR_SPACE_RGB);
                }
                else
                {
                    SET_OSD_COLOR_FORMAT(_COLOR_SPACE_YPBPR);
                }

                break;
        }
    }

    // Adjust Color Space
    SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);

    // Adjust UltraVivid
#if(_ULTRA_VIVID_SUPPORT == _ON)
    UserInterfaceAdjustUltraVividProc(_DB_APPLY_NO_POLLING);
#else

    // Adjust Y-Peaking
#if(_YPEAKING_SUPPORT == _ON)
    UserInterfaceAdjustYpeaking();
#endif

#endif

    // Adjust Sharpness
#if(_SHARPNESS_SUPPORT == _ON)
    UserCommonAdjustSharpness(SysSourceGetInputPort());
#endif

    // Adjust Backlight
    UserAdjustBacklight(GET_OSD_BACKLIGHT());

    // Adjust Brightness & Contrast
    RTDNVRamLoadBriCon(SysSourceGetSourceType());

    // Adjust Transparency
    ScalerOsdSetTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // User Adjust Background Color
    ScalerDDomainBackgroundSetColor(0, 0, 0);

#if(_PCM_FUNCTION == _ON)
#if(_HDR10_SUPPORT == _ON)
    if((GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE) || (GET_OSD_HDR_MODE() == _HDR10_MODE_FORCE_2084))
#else
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
#endif
    {
#if(_BRIGHTNESS_SUPPORT == _ON)
        ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        if(GET_OSD_PCM_STATUS() == _PCM_OSD_SOFT_PROFT)
        {
            ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
        }
        else
        {
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
        }
#endif  // End of #if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))

    }
    else
#endif  // End of #if(_PCM_FUNCTION == _ON)
    {

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

        // Adjust Gamma On/Off
#if(_GAMMA_FUNCTION == _ON)
        if(GET_OSD_GAMMA() == _GAMMA_OFF)
        {
            UserCommonAdjustGammaRegionEnable(_FUNCTION_OFF);

#if(_RGB_GAMMA_FUNCTION == _ON)
            ScalerColorRGBOutputGammaEnable(_FUNCTION_OFF);
#endif
        }
        else
        {
            UserCommonAdjustGammaRegionEnable(_FUNCTION_ON);

#if(_RGB_GAMMA_FUNCTION == _ON)
            ScalerColorRGBOutputGammaEnable(_FUNCTION_ON);
#endif
        }
#endif  // End of #if(_GAMMA_FUNCTION == _ON)

        // Adjust Hue & Saturation
#if(_GLOBAL_HUE_SATURATION == _ON)
        if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_VIVID)
        {
            UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), 140);
        }
        else
        {
            UserAdjustGlobalHueSat((SWORD)GET_OSD_HUE(), GET_OSD_SATURATION());
        }
#endif  // End of #if(_GLOBAL_HUE_SATURATION == _ON)

        // Adjuset Brightness & Contrast
#if(_BRIGHTNESS_SUPPORT == _ON)
        UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(GET_OSD_CONTRAST());
#endif
    }

    // Adjust ICM On/Off
#if(_ICM_SUPPORT == _ON)
    if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_STANDARD)
    {
        ScalerColorICMEnable(_FUNCTION_OFF);
    }
    else
    {
        ScalerColorICMEnable(_FUNCTION_ON);
    }
#endif

    // Adjust DCC On/Off
#if(_DCC_FUNCTION == _ON)
    if((GET_OSD_COLOR_EFFECT() == _COLOREFFECT_STANDARD) || (GET_OSD_COLOR_EFFECT() == _COLOREFFECT_USER))
    {
        ScalerColorDCCEnable(_FUNCTION_OFF);
    }
    else
    {
        ScalerColorDCCEnable(_FUNCTION_ON);
    }
#endif

#if(_OD_SUPPORT == _ON)
    ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
    ScalerODEnable(GET_OSD_OD_STATUS());
#endif

    // Adjust DCC Table
#if(_DCC_FUNCTION == _ON)
    UserAdjustDCC(GET_OSD_COLOR_EFFECT());
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    if(GET_OSD_PANEL_UNIFORMITY() == _OFF)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
    }
    else
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_ON);
    }
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    // Adjust Highlight Window Effect Space
    UserAdjustHighLightWindowEffectSpace();

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    if(GET_OSD_ASPECT_RATIO_TYPE() != _OSD_ASPECT_RATIO_ORIGIN)
#endif
    {
        if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
        {
            ScalerColorHLWEnable(_FUNCTION_OFF, _DB_APPLY_NONE);
        }
        else
        {
            UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
            ScalerColorHLWEnable(_FUNCTION_ON, _DB_APPLY_NONE);
        }
    }
#endif  // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
}


#if(_ULTRA_VIVID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustUltraVivid(void)
{
    BYTE ucUltraVividStatus = GET_OSD_ULTRA_VIVID_STATUS();

    // Wait for D-domain DB apply ready
    ScalerColorWaitDDomainDBApply();

#if(_HDR10_SUPPORT == _ON)
    if((UserCommonHDRGetHDR10Status() == _HDR10_ON) && (GET_OSD_HDR_SHARPNESS() == _ON))
    {
        ScalerColorUltraVividAdjust(tCOLOR_ULTRAVIVID_SETTING_HDR, GET_CURRENT_BANK_NUMBER());
    }
    else
#endif
    {
        if(ucUltraVividStatus != _ULTRA_VIVID_OFF)
        {
            ScalerColorUltraVividAdjust(tCOLOR_ULTRAVIVID_SETTING_TABLE[ucUltraVividStatus - 1], GET_CURRENT_BANK_NUMBER());
        }
        else
        {
            ScalerColorUltraVividEnable(_FUNCTION_OFF, _DB_APPLY_NONE);
        }
    }
}

//--------------------------------------------------
// Description  : UltraVivid Proccess
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustUltraVividProc(EnumDBApply enumDBApply)
{
#if(_HDR10_SUPPORT == _ON)
    if((UserCommonHDRGetHDR10Status() == _HDR10_ON) && (GET_OSD_HDR_SHARPNESS() == _ON))
    {
        UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), enumDBApply);
    }
    else
#endif
    {
        if(GET_OSD_ULTRA_VIVID_STATUS() == _ULTRA_VIVID_OFF)
        {
            UserCommonAdjustUltraVivid(_FUNCTION_OFF, UserCommonInterfaceGetColorFormat(), enumDBApply);
        }
        else
        {
            UserCommonAdjustUltraVivid(_FUNCTION_ON, UserCommonInterfaceGetColorFormat(), enumDBApply);
        }
    }
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
#endif

#if(_DCR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust DCR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustDCRHandler(void)
{
    if(GET_OSD_DCR_STATUS() == _ON)
    {
#if(_LOCAL_DIMMING_SUPPORT == _ON)
        if(UserInterfaceGetLocalDimmingStatus() == _LD_ENABLE)
        {
            BYTE pucDCRResult[_TOTAL_REGION];
            memset(pucDCRResult, 255UL, _TOTAL_REGION);
            ScalerColorDCRLocalDimmingReadResult(pucDCRResult);
        }
        else
#endif
        {
            PDATA_DWORD(0) = ScalerColorDCRReadResult(_DCR_ABOVE_TH1_NUM);
        }
    }
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
#if(_SIX_COLOR_SUPPORT == _ON)
    BYTE ucIndex = 0;
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    // Uniformity parameters setting
    ScalerColorPanelUniformityInitial();

    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
    {
        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
    }
#endif

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);

#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        UserAdjustPCM(GET_OSD_PCM_STATUS());
    }
    else
#endif
    {
#if(_GAMMA_FUNCTION == _ON)
        // Adjust Gamma Table
        UserAdjustGamma(GET_OSD_GAMMA());
#endif
    }

#if(_RGB_3D_GAMMA == _ON)
    UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
    UserAdjustSCM(GET_OSD_COLOR_EFFECT());
#endif

    // Adjust ICM Table
#if(_ICM_SUPPORT == _ON)
    UserAdjustICM(GET_OSD_COLOR_EFFECT());
#endif

    // Adjust DCR Threshold & Source
#if(_DCR_SUPPORT == _ON)

#if(_DCR_BIT_MODE == _DCR_GEN_1_0_10BIT)
    ScalerColorDCRAdjust(_DCR_THESHOLD1, _DCR_THESHOLD2, _MEASURE_AVERAGE);
#elif((_DCR_BIT_MODE == _DCR_GEN_0_0_8BIT) || (_DCR_BIT_MODE == _DCR_GEN_0_1_8BIT))
    ScalerColorDCRAdjust((_DCR_THESHOLD1 >> 2), (_DCR_THESHOLD2 >> 2), _MEASURE_AVERAGE);
#endif

#endif

    // Adjust Six Color Hue / Saturation
#if(_SIX_COLOR_SUPPORT == _ON)
    if(GET_OSD_COLOR_EFFECT() == _COLOREFFECT_USER)
    {
        for(ucIndex = 0; ucIndex < 6; ucIndex++)
        {
            SET_OSD_SIX_COLOR(ucIndex);
            OsdDisplaySixColorGetOneColor(ucIndex);
            ScalerColorSixColorAdjust(ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
        }

        ScalerColorSixColorInitial();
    }
#endif

#if(_OD_SUPPORT == _ON)
    UserAdjustOD();
#endif

    // Adjust Highlight Window Border
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWBorderAdjust(_HL_WIN_BORDER_SIZE, 255, 0, 0);

    ScalerColorHLWBorderEnable(_ON, _ON, _ON, _ON);
#endif

#if(_SDR_TO_HDR_SUPPORT == _ON)
    UserAdjustSDRToHDR(GET_OSD_SDR_TO_HDR());
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
        UserCommonInterfaceDdcciSwitch(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());

        if(GET_FAIL_SAFE_MODE() == _TRUE)
        {
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG);
        }
        else
        {
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_ACTIVE_DO_ONE_TIME_MSG);
        }
    }

#if((_OD_SUPPORT == _ON) && (_FREESYNC_SUPPORT == _ON))
    UserAdjustOD();
#endif

#if(_FREEZE_SUPPORT == _ON)
    UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
#endif

    ScalerDDomainBackgroundEnable(_DISABLE);
}

//--------------------------------------------------
// Description  : OSD Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdResetProc(void)
{
    // Disable OSD
    if(GET_OSD_LOGO_ON() == _OFF)
    {
        OsdDispDisableOsd();
    }

    SET_OSD_LOGO_ON(_OFF);

    // Cancel Timer Events
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_AUTO_COLOR);
#if (_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
#endif
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
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
    g_usAdjustValue = ucAutoPercentage;
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
#if(_AUDIO_SUPPORT == _ON)
        case _MHL_RCP_VOLUME_UP:

            if(GET_OSD_VOLUME() < 100)
            {
                SET_OSD_VOLUME(GET_OSD_VOLUME() + 1);
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;

        case _MHL_RCP_VOLUME_DOWN:

            if(GET_OSD_VOLUME() > 0)
            {
                SET_OSD_VOLUME(GET_OSD_VOLUME() - 1);
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;

        case _MHL_RCP_MUTE:
        case _MHL_RCP_MUTE_FUNCTION:

            SET_OSD_VOLUME_MUTE(!GET_OSD_VOLUME_MUTE());

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioMuteSwitch();
            }
            break;

        case _MHL_RCP_RESTORE_VOLUME_FUNCTION:

            SET_OSD_VOLUME(50);

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;
#endif

        default:
            return _FALSE;
    }

    return _TRUE;
}
#endif // End of #if(_MHL_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Decide whether to Enable FREESYNC Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort)
{
    enumSourcePort = enumSourcePort;

#if((_FREESYNC_SUPPORT == _ON) || (_FREESYNC_II_SUPPORT == _ON))
    if(GET_OSD_FREE_SYNC_STATUS() == _TRUE)
    {
        return _FREESYNC_SUPPORT_ON;
    }
#endif
    return _FREESYNC_SUPPORT_OFF;
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

            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D0)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_4;
            }
            break;

#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D1)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_4;
            }
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D1)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D2_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_4;
            }
            break;
#endif


#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D6)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_4;
            }
            break;
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
            return UserCommonNVRamGetSystemData(_DP_D0_LANES);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            return UserCommonNVRamGetSystemData(_DP_D1_LANES);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:
            return UserCommonNVRamGetSystemData(_DP_D2_LANES);
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:
            return UserCommonNVRamGetSystemData(_DP_D6_LANES);
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

#endif

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
    if((SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT) && (GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP))
#endif
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        if((GET_OSD_DP_MST() == _MST_D0) && (SysSourceGetInputPort() == _D0_INPUT_PORT))
        {
            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_MST(_MST_OFF);

                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX0_PORT;
            }
        }
        else
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        if((GET_OSD_DP_MST() == _MST_D1) && (SysSourceGetInputPort() == _D1_INPUT_PORT))
        {
            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_MST(_MST_OFF);

                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX1_PORT;
            }
        }
        else
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
        if((GET_OSD_DP_MST() == _MST_D6) && (SysSourceGetInputPort() == _D6_INPUT_PORT))
        {
            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_MST(_MST_OFF);

                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX6_PORT;
            }
        }
        else
#endif

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _ON)
        if(GET_OSD_DP_MST() == _MST_AUTO)
        {
            return _DP_MST_AUTO_PORT;
        }
        else
#endif
        {
            return _DP_MST_NO_PORT;
        }
    }

    return _DP_MST_NO_PORT;
}

#if(_DP_MST_CAP_ON_INACTIVE_PORT_HPD_LOW == _ON)
//--------------------------------------------------
// Description  : Get Dp MST Target Port
// Input Value  : None
// Output Value : _DP_MST_RX0 or _DP_MST_RX1
//--------------------------------------------------
EnumDPMSTPort UserInterfaceGetDpMstTargetPort(void)
{
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
    if(GET_OSD_DP_MST() == _MST_D0)
    {
        if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
        {
            return _DP_MST_NO_PORT;
        }
        else
        {
            return _DP_MST_RX0_PORT;
        }
    }
    else
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
    if(GET_OSD_DP_MST() == _MST_D1)
    {
        if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
        {
            return _DP_MST_NO_PORT;
        }
        else
        {
            return _DP_MST_RX1_PORT;
        }
    }
    else
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
    if(GET_OSD_DP_MST() == _MST_D6)
    {
        if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
        {
            return _DP_MST_NO_PORT;
        }
        else
        {
            return _DP_MST_RX6_PORT;
        }
    }
    else
#endif
    {
        return _DP_MST_NO_PORT;
    }

    return _DP_MST_NO_PORT;
}
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetDpCloneOutputStatus(void)
{
    if(GET_OSD_CLONE_MODE() == _OFF)
    {
        return _FALSE;
    }

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
    UserAdjustEmbeddedDpSwitch();
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
#if(_EMBEDDED_DAC_SUPPORT == _ON)
        if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
#endif
        {
#if(_LINE_IN_SUPPORT == _ON)
            if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
            {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
                {
#if((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN))
                    return _TRUE;
#endif
                }
#endif
                if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) ||
                   ((SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING) && (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK)))
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(UserInterfaceGetAudioSource() == _DIGITAL_AUDIO)
                {
                    if(ScalerAudioGetAudioDetected(SysSourceGetInputPort()) == _TRUE)
                    {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                        if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
                        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                            if(ScalerAudioGetDigitalAudioSource(SysSourceGetInputPort()) == _DIGITAL_AUDIO_SOURCE_DP)
                            {
                                // When Fixed Port, should not play DP Audio at different port
                                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetAudioPlaybackPort() == SysSourceGetInputPort()))
                                {
                                    return _TRUE;
                                }
                            }
#endif
                        }
#endif
                        if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) || (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK))
                        {
                            return _TRUE;
                        }
                    }
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User OSD Get Audio Source
// Input Value  : None
// Output Value : _DIGITAL_AUDIO or _LINE_IN_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserInterfaceGetAudioSource(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
    {
        return _DIGITAL_AUDIO;
    }
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        return _LINE_IN_AUDIO;
    }
#endif

    switch(SysSourceGetInputPort())
    {
        case _A0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
        case _D0_INPUT_PORT:
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
        case _D1_INPUT_PORT:
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
        case _D2_INPUT_PORT:
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
        case _D3_INPUT_PORT:
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
        case _D4_INPUT_PORT:
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
        case _D5_INPUT_PORT:
#endif

#if(_LINE_IN_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            if(UserInterfaceGetAudioStandAloneStatus() == _FALSE)
#endif
            {
                // Don't switch audio source if input source is not found
                if(SysSourceGetSourceType() == _SOURCE_NONE)
                {
                    return ScalerAudioGetInputSource();
                }
            }

            return _LINE_IN_AUDIO;
#else
            return _NO_AUDIO_SOURCE;
#endif // End of #if(_LINE_IN_SUPPORT == _ON)

        default:

#if(_LINE_IN_SUPPORT == _ON)
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            // Don't Switch Audio Source if Line In is Currently Playing unless Digital Source is found
            if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
            {
                if((SysSourceGetSourceType() == _SOURCE_NONE) && (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK) && (ScalerAudioGetInputSource() == _LINE_IN_AUDIO))
                {
                    return _LINE_IN_AUDIO;
                }
            }
#endif
            return GET_OSD_AUDIO_SOURCE();
#else
            return _DIGITAL_AUDIO;
#endif // End of #if(_LINE_IN_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : Get Current Audio Mute Status
// Input Value  : Node
// Output Value : Node
//--------------------------------------------------
bit UserInterfaceGetAudioMuteStatus(void)
{
    return GET_OSD_VOLUME_MUTE();
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
    return UserAdjustAudioVolumeMapping(GET_OSD_VOLUME());
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
    return GET_OSD_AUDIO_STAND_ALONE();
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
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if(SysSourceGetAudioPlaybackPort() != SysSourceGetInputPort())
#endif
            {
                DebugMessageAudio("User Audio Reset Process", 0x00);

                SysAudioMuteProc(_ON);
                ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

                SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
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
            ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

            SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
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
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
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
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // OGC/OCC/DICOM
    {
    }
}
//--------------------------------------------------
// Description  : User function Backlight Adjust for Calibration
// Input Value  : 0(Min Backlight) ~ 255(Max Backlight)
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBacklight(BYTE ucBacklight)
{
    UserAdjustBacklight(_BACKLIGHT_MIN + ((DWORD)(_BACKLIGHT_MAX - _BACKLIGHT_MIN) * ucBacklight) / 255);
}
#endif

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function Before Calibration Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBeforeDimmingCalibration(void)
{
}

//--------------------------------------------------
// Description  : User function After Calibration Start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAfterDimmingCalibration(void)
{
}
#endif

#if(_LD_HDR10_BOOST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User function For LD Boost White Pattern
// Input Value  : _ON/_OFF
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustLDBoostCalibration(bit bBoost)
{
    BYTE usBoostGain = (DWORD)_LOCAL_DIMMING_MAXCLL * 100 / _LOCAL_DIMMING_MAXFALL;
    WORD usBoostPWM;

    usBoostPWM = (DWORD)_DEVICE_LED_DRIVER_PWM_MAX * usBoostGain / 100;
    if(bBoost == _ON) // turn on boost
    {
        ExternalDeviceInterfaceLedDriverPwm(_DEVICE_LED_DRIVER_PWM_ALL, usBoostPWM, _DEVICE_CALI_ON);
    }
    else // turn off boost
    {
        ExternalDeviceInterfaceLedDriverPwm(_DEVICE_LED_DRIVER_PWM_ALL, _DEVICE_LED_DRIVER_PWM_MAX, _DEVICE_CALI_ON);
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
#if(_ULTRA_VIVID_SUPPORT == _ON)
    switch(GET_OSD_ULTRA_VIVID_STATUS())
    {
        case _ULTRA_VIVID_L:
            ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x0E, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
            break;

        case _ULTRA_VIVID_M:
            ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x41, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
            break;

        case _ULTRA_VIVID_H:
        default:
            ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x7E, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
            break;
    }
#else
    // ScalerColorYpeakingAdjust(_YPEAKING_TABLE_MODE, 0x00, _YPEAKING_NO_DIV, tYPEAKING_TABLE[0], _YPEAKING_TABLE_SIZE, GET_CURRENT_BANK_NUMBER());
    ScalerColorYpeakingAdjust(_YPEAKING_GAIN_MODE, 0x41, _YPEAKING_N_DIV32, _NULL_POINTER, 0x00, 0x00);
#endif
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
    return GET_OSD_DDCCI_STATUS();
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

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : GET AIO Modern Standby Mode Status
// Input Value  : None
// Output Value : EnumDDCCIDebugMode:_DEBUG_MODE / _DDCCI_MODE
//--------------------------------------------------
EnumAIOModernStandbyMode UserInterfaceGetAIOModernStandbyMode(void)
{
    return _AIO_MODERN_STANDBY_MODE_DISABLE;
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp FreeSync Get IVFmax From Look Up Table
// Input Value  : IVF(unit: 0.1Hz)
// Output Value : _DP_FREESYNC_WITH_IVF_MAX: Get IVF
//--------------------------------------------------
EnumDrrFreeSyncDpGetIVF UserInterfaceDisplayDpFreeSyncGetIVFmaxFromLut(WORD *pusVfreqMax)
{
    BYTE ucIndex = 0;
    WORD usPixelClk = ScalerSyncGetInputPixelClk();
    WORD usRefHtotalHBound = 0;
    WORD usRefHtotalLBound = 0;
    WORD usPixelClkHBound = usPixelClk;
    WORD usPixelClkLBound = usPixelClk;

    // Htotal margin
    PDATA_WORD(0) = ((DWORD)_USER_DP_DRR_HTOTAL_MARGIN * GET_INPUT_TIMING_HTOTAL() / 100);
    usRefHtotalHBound = (GET_INPUT_TIMING_HTOTAL() + PDATA_WORD(0));
    usRefHtotalLBound = (GET_INPUT_TIMING_HTOTAL() - PDATA_WORD(0));

    // Pixel clk margin
    PDATA_WORD(0) = ((DWORD)_USER_DP_DRR_CLK_MARGIN * usPixelClk / 100);
    usPixelClkHBound += PDATA_WORD(0);
    usPixelClkLBound -= PDATA_WORD(0);

    for(ucIndex = 0; ucIndex < (sizeof(tDrrFreeSyncDpTimingInfo) / sizeof(tDrrFreeSyncDpTimingInfo[0])); ucIndex++)
    {
        if((GET_DRR_IHWIDTH(ucIndex) == GET_INPUT_TIMING_HWIDTH()) && (GET_DRR_IVHEIGHT(ucIndex) == GET_INPUT_TIMING_VHEIGHT()) &&
           ((GET_DRR_IHTOTAL(ucIndex) <= usRefHtotalHBound) && (GET_DRR_IHTOTAL(ucIndex) >= usRefHtotalLBound)) &&
           ((GET_DRR_ICLK(ucIndex) <= usPixelClkHBound) && (GET_DRR_ICLK(ucIndex) >= usPixelClkLBound)))
        {
            *pusVfreqMax = GET_DRR_IVFREQ(ucIndex);

            DebugMessageScaler("ucIndex if Drr user define timing ", ucIndex);
            return _DP_FREESYNC_WITH_IVF_MAX;
        }
    }

    *pusVfreqMax = 0;
    return _DP_FREESYNC_WITHOUT_IVF_MAX;
}
#endif


#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
