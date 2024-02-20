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
// ID Code      : BeaconUserInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "BeaconUserModeTable.h"
#include "BeaconUserInterfaceHDR.h"
#include "BeaconUserInterfaceDimming.h"
#include "BeaconUserInterfaceLocalDimming.h"
#include "BeaconUserInterfaceGlobalDimming.h"

#if(_OSD_TYPE == _BEACON_OSD)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of VGA Filter Table
//--------------------------------------------------
#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
#define _DIGITAL_FILTER_ENHANCE_PHASE_TABLE         "DigFilterEnhancePhaseTable.h"
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
#define _RINGING_FILTER_TABLE                       "RingingFilterTable.h"
#endif

//--------------------------------------------------
// Definitions of Flash Item Length For Each Page
//--------------------------------------------------
#define _DATA_ITEM_LENGTH                           16
#define _PAGE_INFO_LENGTH                           16

//---------------------------------------------------------
// OSD Rotate Type
//---------------------------------------------------------
#define _OSD_ROTATE_OFF                             0
#define _OSD_ROTATE_SOFTWARE                        1
#define _OSD_ROTATE_HARDWARE                        2

//--------------------------------------------------
// Definitions of DCR THD Setting
//--------------------------------------------------
#define _DCR_THESHOLD1                              0x20
#define _DCR_THESHOLD2                              0x180

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
//--------------------------------------------------
// Macro for Lenovo Alt Mode Docking Event Queue Control
//--------------------------------------------------
#define GET_D0_TYPE_C_DOCK_EVENT_QUEUE(x)           (g_stDockEventQueue.pstDockEvent[x])
#define SET_D0_TYPE_C_DOCK_EVENT_QUEUE(x)           (g_stDockEventQueue.pstDockEvent[g_stDockEventQueue.b2DockEventTail] = (x))
#define CLR_D0_TYPE_C_DOCK_EVENT_QUEUE()            (memset(&g_stDockEventQueue.pstDockEvent[g_stDockEventQueue.b2DockEventHead], 0, sizeof(StructTypeCLenovoDockEvent)))

#define GET_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stDockEventQueue.b2DockEventCnt)
#define ADD_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stDockEventQueue.b2DockEventCnt += 1)
#define SUB_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stDockEventQueue.b2DockEventCnt -= 1)
#define CLR_D0_TYPE_C_DOCK_EVENT_CNT()              (g_stDockEventQueue.b2DockEventCnt = 0)

#define GET_D0_TYPE_C_DOCK_EVENT_HEAD()             (g_stDockEventQueue.b2DockEventHead)
#define ADD_D0_TYPE_C_DOCK_EVENT_HEAD()             (g_stDockEventQueue.b2DockEventHead = (g_stDockEventQueue.b2DockEventHead + 1) % 3)
#define CLR_D0_TYPE_C_DOCK_EVENT_HEAD()             (g_stDockEventQueue.b2DockEventHead = 0)

#define GET_D0_TYPE_C_DOCK_EVENT_TAIL()             (g_stDockEventQueue.b2DockEventTail)
#define ADD_D0_TYPE_C_DOCK_EVENT_TAIL()             (g_stDockEventQueue.b2DockEventTail = (g_stDockEventQueue.b2DockEventTail + 1) % 3)
#define CLR_D0_TYPE_C_DOCK_EVENT_TAIL()             (g_stDockEventQueue.b2DockEventTail = 0)
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
#define GET_D0_TYPE_C_ACER_USER_EVENT()             (g_stUsbTypeCAcerUserEvent.enumEvent)
#define SET_D0_TYPE_C_ACER_USER_EVENT(x)            (g_stUsbTypeCAcerUserEvent.enumEvent = (g_stUsbTypeCAcerUserEvent.enumEvent | (x)))
#define CLR_D0_TYPE_C_ACER_USER_EVENT(x)            (g_stUsbTypeCAcerUserEvent.enumEvent = (g_stUsbTypeCAcerUserEvent.enumEvent & (~(x))))

#define GET_D0_TYPE_C_ACER_USER_VDM_CNT()           (g_stUsbTypeCAcerUserEvent.b3VdmCnt)
#define SET_D0_TYPE_C_ACER_USER_VDM_CNT(x)          (g_stUsbTypeCAcerUserEvent.b3VdmCnt = (x))

#define GET_D0_TYPE_C_ACER_USER_VDM_DATA(x)         (g_stUsbTypeCAcerUserEvent.pucVdmData[x])
#define SET_D0_TYPE_C_ACER_USER_VDM_DATA(x, y)      (g_stUsbTypeCAcerUserEvent.pucVdmData[x] = (y))
#endif

#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
#define GET_D0_TYPE_C_HP_USER_EVENT()               (g_stUsbTypeCHpUserEvent.enumEvent)
#define SET_D0_TYPE_C_HP_USER_EVENT(x)              (g_stUsbTypeCHpUserEvent.enumEvent = (g_stUsbTypeCHpUserEvent.enumEvent | (x)))
#define CLR_D0_TYPE_C_HP_USER_EVENT(x)              (g_stUsbTypeCHpUserEvent.enumEvent = (g_stUsbTypeCHpUserEvent.enumEvent & (~(x))))

#define GET_D0_TYPE_C_HP_USER_VDM_CNT()             (g_stUsbTypeCHpUserEvent.b3VdmCnt)
#define SET_D0_TYPE_C_HP_USER_VDM_CNT(x)            (g_stUsbTypeCHpUserEvent.b3VdmCnt = (x))

#define GET_D0_TYPE_C_HP_USER_VDM_DATA(x)           (g_stUsbTypeCHpUserEvent.pucVdmData[x])
#define SET_D0_TYPE_C_HP_USER_VDM_DATA(x, y)        (g_stUsbTypeCHpUserEvent.pucVdmData[x] = (y))
#endif
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
//--------------------------------------------------
// MACRO for Type-C Port Controller
//--------------------------------------------------
#define GET_TYPE_C_PORT_CTRL_POWER_OFF_FLG()        (g_bTypeCPortControllerPowerOffFlag)
#define SET_TYPE_C_PORT_CTRL_POWER_OFF_FLG()        (g_bTypeCPortControllerPowerOffFlag = _TRUE)
#define CLR_TYPE_C_PORT_CTRL_POWER_OFF_FLG()        (g_bTypeCPortControllerPowerOffFlag = _FALSE)
#endif
#endif
#endif

//--------------------------------------------------
// Definitions of Motion Blur Reduction
//--------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#define _RTK_ADV_MBR_MIN_ENABLE_IVF                 600
#endif
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
extern BYTE code tFLASH_PARTITION_BOOTTABLE[];
#endif

extern code void (*OperationTable[][4])(void);

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
extern bit g_bTypeCPortControllerPowerOffFlag;
#endif
#endif

#if(_HDMI_CEC_SUPPORT == _ON)
extern bit g_bCecLaPollingStart;
extern BYTE g_ucCecLaCnt;
#endif

#if(_ALS_TYPE != _SENSER_NONE)
extern DWORD xdata lux_confirmed;
#endif

#if(_BACKLIGHT_SENSOR == _ON)
extern BYTE xdata sensor_brightness_flag;
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FLASH_ITEMID_VGA_ADC_DATA = 0x0000, // 0
    _FLASH_ITEMID_YPBPR_ADC_DATA,
    _FLASH_ITEMID_SYSTEM_DATA,
    _FLASH_ITEMID_PANEL_INDEX,
    _FLASH_ITEMID_OSD_DATA_START,
    _FLASH_ITEMID_OSD_DATA_0 = _FLASH_ITEMID_OSD_DATA_START,
    _FLASH_ITEMID_OSD_DATA_1, // 5
    _FLASH_ITEMID_OSD_DATA_END = _FLASH_ITEMID_OSD_DATA_1,
    _FLASH_ITEMID_BRICON_SRC0_VGA,
    _FLASH_ITEMID_BRICON_SRC1_VIDEO,
    _FLASH_ITEMID_BRICON_SRC2_DVI,
    _FLASH_ITEMID_BRICON_SRC3_HDMI,
    _FLASH_ITEMID_BRICON_SRC4_DP, // 10
    _FLASH_ITEMID_COLORPROC0_9300,
    _FLASH_ITEMID_COLORPROC1_7500,
    _FLASH_ITEMID_COLORPROC2_6500,
    _FLASH_ITEMID_COLORPROC3_5800,
    _FLASH_ITEMID_COLORPROC4_SRGB, // 15
    _FLASH_ITEMID_COLORPROC5_USER,
    _FLASH_ITEMID_SIXCOLOR_DATA,
    _FLASH_ITEMID_PANEL_DATA,
#if(_USER_BEACON_FACTORY_OSD == _ON)
    _FLASH_ITEMID_FACTORY_DATA,//19
    _FLASH_ITEMID_FACTORY_SN0,//20
    _FLASH_ITEMID_FACTORY_SN1,//21
#endif
    _FLASH_ITEMID_MODE_USER_DATA, // 19
    _FLASH_ITEMID_MODE_USER_DATA_END = _FLASH_ITEMID_MODE_USER_DATA + _MODE_SLOT_AMOUNT - 1, // 34
    _FLASH_ITEMID_OTHER_USER_DATA_START,
    _FLASH_ITEMID_OTHER_USER_DATA_0 = _FLASH_ITEMID_OTHER_USER_DATA_START,
    _FLASH_ITEMID_OTHER_USER_DATA_END = _FLASH_ITEMID_OTHER_USER_DATA_0,
} EnumFlashItemIDType;

//--------------------------------------------------
// Struct for Lenovo Alt Mode Docking Event Queue
//--------------------------------------------------
typedef struct
{
    BYTE b2DockEventCnt : 2;
    BYTE b2DockEventHead : 2;
    BYTE b2DockEventTail : 2;
    StructTypeCLenovoDockEvent pstDockEvent[3];
}StructTypeCLenovoDockEventQueue;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ALS_TYPE != _SENSER_NONE)
extern void ALS_Initial(void);
extern BYTE GetFinalLuxValueFromAlsAve(void);
#if(_CUSTOMER != _CUS_MINDRAY)
void AdjustBackLightAccordingLux(void);
#endif
#endif

#if(_BACKLIGHT_SENSOR == _ON)
extern void AutoAdjBacklight2561(void);
extern WORD read2561(void);
#endif

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
extern bit readSensorValue(void);
extern WORD Get12BitPwmDuty(void);
extern void CAdjustSensorBacklight(WORD ucSensorBacklight);
extern void BacklightSensorHandler(void);
extern void updateTargetSenorValue(void);
extern void ClearDiffValueBySetMidPwm(void);
extern SWORD GetDifferencePwmValue(void);
#endif
//----------------------------------------------------------------------------------------
// Extern functions from UserAdjust.c
//----------------------------------------------------------------------------------------
#ifndef __USER_ADJUST__
extern void UserInterfaceRestoreEepromEdid(void);
extern void UserInterfaceRestoreFlashEdid(void);

//-------------------------------------------------------
// Y-Peaking
//-------------------------------------------------------
#if(_YPEAKING_SUPPORT == _ON)
extern void UserInterfaceAdjustYpeaking(void);
#endif

//-------------------------------------------------------
// OD measure
//-------------------------------------------------------
#if(_FREESYNC_OD_MEASURE == _ON)
extern void UserAdjustFREESYNCODMeasure(void);
#endif


//-------------------------------------------------------
// Adjust Backlight
//-------------------------------------------------------
extern void UserAdjustBacklight(WORD usBacklight);

//-------------------------------------------------------
// Dp Load Edid Related
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
extern EnumEdidSelection UserAdjustGetDpEdidIndex(BYTE ucInputPort);
#endif

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern void UserAdjustAudioMuteSwitch(void);
extern void UserAdjustAudioVolume(BYTE ucVolume);
extern WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

//-------------------------------------------------------
// DCR
//-------------------------------------------------------
#if(_DCR_SUPPORT == _ON)
extern void UserInterfaceAdjustDCRHandler(void);
#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
extern void UserAdjustDCRTHD(void);
#endif
#endif

//-------------------------------------------------------
// DCC
//-------------------------------------------------------
#if(_DCC_FUNCTION == _ON)
extern void UserAdjustDCC(BYTE ucColorEffect);
#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_DCC_HISTOGRM_INFO == _ON)
extern void UserInterfaceDCCHistogramHandler(void);
#endif

//-------------------------------------------------------
// IAPS
//-------------------------------------------------------
#if(_IAPS_SUPPORT == _ON)
extern void UserInterfaceAdjustIAPSHandler(void);
#endif

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
#if(_ICM_SUPPORT == _ON)
extern void UserAdjustICM(BYTE ucColorEffect);
#endif

#if(_SCM_SUPPORT == _ON)
extern void UserAdjustSCM(BYTE ucColorEffect);
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
extern void UserAdjustColorEffectMode(void);
#endif

//-------------------------------------------------------
// CTS / BRI
//-------------------------------------------------------
#if(_CONTRAST_SUPPORT == _ON)
extern void UserAdjustContrast(WORD usContrast);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
extern void UserAdjustBrightness(WORD usBrightness);
#endif

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION == _ON)
extern void UserAdjustGlobalHueSat(SWORD shHue, WORD usSat);
#endif

//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_SUPPORT == _ON)
extern void UserAdjustOD(void);
#endif

//-------------------------------------------------------
// HLW
//-------------------------------------------------------
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
extern void UserAdjustHLWinType(BYTE ucHLWinType);
extern void UserAdjustHLWinType5Move(void);
extern void UserAdjustHighLightWindowEffectSpace(void);
#endif

//-------------------------------------------------------
// IR
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
extern void UserAdjusIR(void);
#endif

//-------------------------------------------------------
// DP
//-------------------------------------------------------
#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
extern void UserAdjustEmbeddedDpSwitch(void);
#endif

//-------------------------------------------------------
// Type-C Port Controller
//-------------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
extern void UserAjustTypeCPowerControl(EnumPowerAction enumSwitch);
#endif
#endif
#endif

//-------------------------------------------------------
// HDR
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_DP_HDR10_SUPPORT == _ON) && (_DP_SUPPORT == _ON))
extern void UserAdjustHdrCheckDpVersion(WORD usHdrMode);
#endif

//-------------------------------------------------------
// SDRToHDR
//-------------------------------------------------------
#if(_SDR_TO_HDR_SUPPORT == _ON)
extern void UserAdjustSDRToHDR(bit bOn);
#endif
#endif // End of #ifndef __USER_ADJUST__

#ifndef __USER_ADJUST_3D_GAMMA__
//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------
#if(_RGB_3D_GAMMA == _ON)
extern void UserAdjust3DGamma(BYTE uc3DGammaMode);
#endif
#endif

#ifndef __USER_ADJUST_OUTPUT_GAMMA__
//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------
#if(_GAMMA_FUNCTION == _ON)
extern void UserAdjustGamma(BYTE ucGamma);
#endif
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
#if(_GAMMA_IN_FLASH_BANK == _OFF)
extern void CAdjustLUTGamma(BYTE *pGammaTableArray, BYTE ucBankNum);
#endif
extern void CAdjustGammaZero(void);
extern void CAdjustGammaTmp(BYTE ucGamma,BYTE ucColorTempType);
#if(_GAMMA_IN_FLASH_BANK == _ON)
extern void UserCommonFlashLoadGamma(BYTE ucGammaIndex,BYTE ucColorTempIndex);
#if(BEACON_GAMMA_TYPE != Gamma_default)
extern void UserCommonAdjustGammaRGBValue(BYTE *pucGammaTableArray);
extern BYTE UserCommonAdjustGammaBank(BYTE ucGammaIndex, BYTE ucColorTempIndex);
extern BYTE *UserCommonAdjustGammaAddr(BYTE ucGammaIndex, BYTE ucColorTempIndex);
#if(BEACON_GAMMA_TYPE == Gamma_9x2CT_2Bank)
extern WORD UserCommonAdjustGammaAddrData(BYTE ucGammaIndex, BYTE ucColorTempIndex);
extern BYTE *UserCommonAdjust14BitGammaAddr(BYTE ucGammaIndex, BYTE ucColorTempIndex);
#endif
#else
#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
extern void UserCommonFlashSaveGamma(BYTE ucGammaIndex, WORD usDataIndex, BYTE ucDataCount, BYTE *pDataArray);
#endif
extern void UserCommonFlashRestoreGamma(void);
#endif
#endif
extern void RTDFlashRestoreDitherData(void);
#endif
//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
extern void UserAdjustPCM(BYTE ucPCM);
#endif

//-------------------------------------------------------
// Pixel Shift
//-------------------------------------------------------
#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern void UserAdjustPixelShifting(void);
#endif

#endif

#ifndef __USER_ADJUST_RGB_GAMMA__
//-------------------------------------------------------
// RGB Output Gamma
//-------------------------------------------------------
#if(_RGB_GAMMA_FUNCTION == _ON)
extern void UserAdjustRGBGamma(BYTE ucGamma);
#endif
#endif


#ifndef __USER_ADJUST_UNIFORMITY__
//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------
#if(_UNIFORMITY_SUPPORT == _ON)
extern void UserAdjustPanelUniformityMode(BYTE ucUniformity);
#endif
#endif


#if(_BACKLIGHT_SENSOR == _ON)
extern void UserAdjustSetSensorbacklightvalue(BYTE SenserBrightnessFlag);
#endif

#if(_HDMI_SPLITTER_1X2_EN == _ON)
extern void UserAdjust_HdmiSplitter_Init(void);
extern void UserAdjust_HdmiSplitter_SetData(BYTE Data1st,BYTE Data2nd);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserInterface.c
//----------------------------------------------------------------------------------------
#ifndef __USER_INTERFACE__

#if(Dynamic_Show_NoSignal_NoSupport == _ON)
extern BYTE xdata g_Dynamic_Show_x;
extern BYTE xdata g_Dynamic_Show_y;
extern BYTE xdata g_Dynamic_Show_flag;
#endif

extern void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// INT
//-------------------------------------------------------
#if(_INSTANT_TIMER_EVENT_0 == _ON)
extern void UserInterfaceTimer0InstantAccess_EXINT(void);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
extern void UserInterfaceTimer1InstantAccess_EXINT(void);
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
extern void UserInterfaceTimer2InstantAccess_EXINT(void);
#endif

#if(_UART_SUPPORT == _ON)
extern void UserInterfaceUartIntHandler_SERIALPORT(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern BYTE UserInterfaceGetDdcciStatus_EXINT1(void);
extern BYTE UserInterfaceGetFactoryCommand_EXINT1(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(void);
#endif
#endif

//-------------------------------------------------------
// EDID & HDCP
//-------------------------------------------------------
#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern EnumHdmiEdidLocation UserInterfaceGetMultiHdmiEdidLocated(BYTE ucInputport, BYTE ucEdidIndex);
extern EnumEdidSelection UserInterfaceGetMultiHdmiEdidIndex(BYTE ucInputPort);
#endif

#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
extern void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
extern void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_DP_TX_SUPPORT == _ON)
extern void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
extern void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void UserInterfaceGetDpTxHdcp2RRMODNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetDpTxHdcp2DcpLlcNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetDpTxHdcp2EKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserInterfaceGetDpTxHdcp2NPinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif
#endif


//-------------------------------------------------------
// Wait for Panel Power Sequence Delay
//-------------------------------------------------------
#if(_PANEL_POWER_SEQUENCE_CONTROL_BY_USER == _ON)
extern void UserInterfacePanelPowerAction(BYTE ucEvent);
#endif

extern void UserInterfaceAdjustWaitPanelT1(void);
extern void UserInterfaceAdjustWaitPanelT2(void);
extern void UserInterfaceAdjustWaitPanelT3(void);
extern void UserInterfaceAdjustWaitPanelT4(void);
extern void UserInterfaceAdjustWaitPanelT5(void);

#if(_SIGNAL_GPIO_DETECT == _ON)
extern void UserInterfaceSetForcePowSavStatus(bit bOnOff);
extern bit UserInterfaceGetForcePowSavStatus(void);
#endif
//-------------------------------------------------------
// Misc
//-------------------------------------------------------
extern void UserInterfaceUncallFunction(void);
extern void UserInterfaceInitial(void);

extern void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
extern void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed);

//-------------------------------------------------------
// User Information
//-------------------------------------------------------
extern bit UserInterfaceGetLogoStatus(void);
extern bit UserInterfaceGetdNoSupportStatus(void);
extern bit UserInterfaceGetDclkNoSupportStatus(void);
extern bit UserInterfaceGetActiveByPassStatus(void);
extern bit UserInterfaceGetCableResetStatus(void);
extern bit UserInterfaceGetForcePSStatus(void);
extern bit UserInterfaceGetIntoPSStatus(void);
extern EnumUserForceFakePS UserInterfaceGetFakePSStatus(void);
extern EnumUserForceFakePowerOff UserInterfaceGetFakePowerOffStatus(void);
extern bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType);
extern bit UserInterfaceGetDisplaySettingBacklightAction(void);

extern EnumColorSpace UserInterfaceGetColorFormat(void);

#if(_OVERSCAN_SUPPORT == _ON)
extern bit UserInterfaceGetOverScanStatus(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern EnumAspectRatioType UserInterfaceGetAspectRatioType(void);
extern void UserInterfaceGetAspectRatio(WORD *pusHRatio, WORD *pusVRatio);
extern void UserInterfaceAdjustAspectRatio(void);
#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
extern WORD UserInterfaceGetAspectRatioMinDVHeight(void);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern BYTE UserInterfaceGetAspectRatioOriginalRatio(void);
#endif

#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern EnumRotationType UserInterfaceGetRotationDegree(void);
extern EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE UserInterfaceGetDisplayLatencyRatio(void);
#endif

#if(_FRC_SUPPORT == _ON)
extern void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

#if(_OD_SUPPORT == _ON)
extern EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void);
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
extern void UserInterfaceUpdateDDR3PhaseData(void);
#endif

#if(_USER_SYSTEM_EEPROM_CUSTOMIZATION == _ON)
extern bit UserInterfaceSystemEepromReadCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit UserInterfaceSystemEepromWriteCustomProc(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
extern void UserInterfaceDisplayInitialization(void);
extern void UserInterfaceAdjustInputTiming(void);
extern void UserInterfaceAdjustDisplayTiming(void);

#if(_UNDERSCAN_SUPPORT == _ON)
extern bit UserInterfaceAdjustUnderScan(void);
#endif

//-------------------------------------------------------
// Color
//-------------------------------------------------------
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
extern bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
extern bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumColorYCCQuantization enumColorYCCQuantization);
#endif

extern void UserInterfaceAdjustActiveByPassColorProc(void);
extern void UserInterfaceAdjustColorProc(void);

#if(_ULTRA_VIVID_SUPPORT == _ON)
extern void UserInterfaceAdjustUltraVivid(void);
extern void UserInterfaceAdjustUltraVividProc(EnumDBApply enumDBApply);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
extern code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSourceSearchPort enumSourceSearchPort);
extern BYTE UserInterfaceGetSharpnessCoefBankNum(void);
extern bit UserInterfaceSharpnessBypassCheck(void);
#endif
//-------------------------------------------------------
// Osd
//-------------------------------------------------------
extern void UserInterfaceAdjustOsdPowerOnInitial(void);
extern void UserInterfaceAdjustOsdActiveProc(void);
extern void UserInterfaceAdjustOsdResetProc(void);

//-------------------------------------------------------
// Interfaces
//-------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex);
extern bit UserInterfaceGetLoadModeTableDefaultStatus(void);
extern bit UserInterfaceGetFirstAutoConfigStatus(void);
extern void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage);

extern bit UserInterfaceSkipAutoVpos(void);
extern bit UserInterfaceSkipAutoHpos(void);
#endif

#if(_MHL_SUPPORT == _ON)
extern bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

extern EnumFreeSyncSupport UserInterfaceGetFreeSyncEnable(EnumSourceSearchPort enumSourcePort);

#if(_DP_SUPPORT == _ON)
extern EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
extern EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
extern EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
extern void UserInterfaceEmbeddedDpSwitch(void);
#endif
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_FREESYNC_SUPPORT == _ON)
extern EnumDrrFreeSyncDpGetIVF UserInterfaceDisplayDpFreeSyncGetIVFmaxFromLut(WORD *pusVfreqMax);
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
extern EnumUSBPDSupportStatus UserInterfaceGetUSBPDSupportStatus(void);
extern EnumUSBPSSupportStatus UserInterfaceGetUSBPSSupportStatus(void);
#endif

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
extern void UserInterfaceUartHandler(void);
#endif

//-------------------------------------------------------
// AUDIO
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioReadyToPlayStatus(void);
extern bit UserInterfaceGetAudioMuteStatus(void);
extern EnumAudioInputSource UserInterfaceGetAudioSource(void);
extern bit UserInterfaceGetAudioNonLPCMStatus(void);
extern WORD UserInterfaceGetAudioVolume(void);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
extern EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
extern bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

extern void UserInterfaceAdjustAudioResetProc(void);
extern void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
extern void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);
#endif // End of #if(_AUDIO_SUPPORT == _ON)
#endif // End of #ifndef __USER_INTERFACE__

//-------------------------------------------------------
// Motion Blur Reduction
//-------------------------------------------------------
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern void UserInterfaceMbrBacklightAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl, WORD usDVTotal);
extern void UserInterfaceMbrAdimAdjust(EnumMbrBacklightMode enumBacklightMode);
extern EnumMbrBacklightMode UserInterfaceMbrGetBacklightMode(void);
extern BYTE UserInterfaceMbrGetBacklightDuty(void);
extern BYTE UserInterfaceMbrGetBacklightPos(void);
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
extern EnumRtkAdvMbrUserStatus UserInterfaceGetRtkAdvMbrSetting(void);
#endif
#endif

//-------------------------------------------------------
// RTD2014UserInterfaceCec.c
//-------------------------------------------------------
extern void UserInterfaceCecReceivedNotify(StructCecRxReceivedInfo *pstCecRxInfo);
extern bit UserInterfaceCecTransmitInfoPrepare(StructCecTxTransmitInfo *pstCecTxInfo);
extern void UserInterfaceCecHighLevelFlow(void);

//-------------------------------------------------------
// RTD2014UserTypeCInterface.c
//-------------------------------------------------------
#ifndef __USER_TYPECINTERFACE__

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
extern EnumTypeCU3ModeType UserInterfaceTypeCGetOsdU3ModeSelection(BYTE ucInputPort);
#if(_TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_SWITCH_SUPPORT == _ON)
extern EnumTypeCPinAssignmentESupportStatus UserInterfaceTypeCGetOsdPinAssignmentESupportSelection(BYTE ucInputPort);
#endif

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern bit UserInterfaceTypeCHubProcSupport(BYTE ucInputPort);
extern void UserInterfaceTypeCOsdHubProc(BYTE ucInputPort);
extern WORD UserInterfaceTypeCUsbHubSetPollingStep(BYTE ucInputPort);
extern bit UserInterfaceTypeCUsbHubDetectDFPStatusUserFlow(BYTE ucInputPort);
extern bit UserInterfaceTypeCUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
extern EnumHubDspDetectStatus UserInterfaceTypeCUsbHubDetectDFPStatus(BYTE ucInputPort);
#if(_BILLBOARD_HUB_SUPPORT == _ON)
extern void UserInterfaceTypeCUsbHubBillboardControl(BYTE ucInputPort, EnumBillboardCtrl enumAtion);
#endif
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)

#if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))
extern EnumTypeCAttachStatus UserInterfaceTypeCGetPortControllerCcAttach(BYTE ucInputPort);
extern EnumTypeCAltModeStatus UserInterfaceTypeCGetPortControllerAltModeReady(BYTE ucInputPort);
#endif  // End of #if((_PORT_CTRL_RTS_DET_CONNECTION_BY_USER == _ON) || (_PORT_CTRL_USER_DET_CONNECTION_BY_USER == _ON))

#if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)
#if(_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER)
extern EnumTypeCOrientation UserInterfaceTypeCGetPortControllerOrientation(BYTE ucInputPort);
#endif
extern EnumTypeCPowerRole UserInterfaceTypeCPortControllerGetUserPowerRole(BYTE ucInputPort);
extern bit UserInterfaceTypeCPortControllerReconnect(BYTE ucInputPort);
extern bit UserInterfaceTypeCPortControllerConfigUserPinAssignment(BYTE ucInputPort, EnumTypeCPinCfgCapType enumPinAssignment);
extern bit UserInterfaceTypeCPortControllerConfigUserMultiFunction(BYTE ucInputPort, EnumTypeCMultiFuncStatus enumMultiFunction);
extern EnumTypeCUserPortCtrlFailureType UserInterfaceTypeCGetPinCfgType(BYTE ucInputPort, EnumTypeCPinCfgType *penumPinCfgtype);
#if((_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON) && (_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE))
extern EnumTypeCLenovoAltModeStatus UserInterfaceTypeCPortControllerGetUserLenovoAltModeReady(BYTE ucInputPort);
extern EnumTypeCLenovoDeviceType UserInterfaceTypeCPortControllerGetUserLenovoDeviceType(BYTE ucInputPort);
extern void UserInterfaceTypeCPortControllerSetUserLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent stLenovoDockEvent);
extern StructTypeCLenovoSysEvent UserInterfaceTypeCPortControllerGetUserLenovoSystemEvent(BYTE ucInputPort);
extern bit UserInterfaceTypeCPortControllerCheckUserLenovoDockingEventBusy(BYTE ucInputPort);
#endif
#endif // End of #if(_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON)

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern void UserInterfaceTypeCPinAssignSuccessProc(BYTE ucInputPort, EnumTypeCPinCfgType enumPinAssignment);
#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern void UserInterfaceTypeCGetLenovoDockingEvent(BYTE ucInputPort, StructTypeCLenovoDockEvent *pstLenovoDockEvent);
extern void UserInterfaceTypeCLenovoAltModeHandler(BYTE ucInputPort, StructTypeCLenovoSysEvent stLenovoSysEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_ACER_ALT_MODE)
extern void UserInterfaceTypeCGetAcerUserEvent(BYTE ucInputPort, StructTypeCAcerUserEvent *pstAcerUserEvent);
extern void UserInterfaceTypeCAcerAltModeHandler(BYTE ucInputPort, StructTypeCAcerSysEvent stAcerSysEvent);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern void UserInterfaceTypeCGetHpUserEvent(BYTE ucInputPort, StructTypeCHpUserEvent *pstHpUserEvent);
extern void UserInterfaceTypeCHpAltModeHandler(BYTE ucInputPort, StructTypeCHpSysEvent stHpSysEvent);
#endif
#endif  // End of #if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
extern EnumTypeCEmbPdoReference UserInterfaceTypeCPdoReference(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
extern EnumTypeCEmbRdoReference UserInterfaceTypeCRdoReference(BYTE ucInputPort);
extern WORD UserInterfaceTypeCGetMaxPower(BYTE ucInputPort);
extern EnumTypeCPdoNumber UserInterfaceTypeCGetPdoCount(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
extern void UserInterfaceTypeCGetSrcPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSrcPdo);
extern void UserInterfaceTypeCGetSnkPdoInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserPDO *pstTypeCUserSnkPdo);
extern void UserInterfaceTypeCGetRdoInfo(BYTE ucInputPort, StructTypeCUserRDO *pstTypeCUserRdo);
#if(_TYPE_C_EMB_VBUS_PROTECT_MODE == _VBUS_PROTECT_BY_USER)
extern void UserInterfaceTypeCGetProtectInfo(BYTE ucInputPort, BYTE ucPdoIndex, StructTypeCUserProtectInfo *pstTypeCUserProtectInfo);
#endif
#if(_DP_USB_HUB_SUPPORT == _ON)
extern EnumHubInputPort UserInterfaceTypeCHubInputPort(BYTE ucInputPort);
#endif
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)

#if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
extern EnumTypeCPortCtrlReconnectSupport UserInterfaceTypeCPortControllerReconnectSupport(BYTE ucInputPort);
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_NONE)
extern EnumTypeCPortCtrlReconnectStatus UserInterfaceTypeCPortControllerGetPowerOnReconnectStatus(EnumPowerAction enumSwitch);
#endif
#endif // End of #if((_PORT_CONTROLLER_RTS5400_SERIES_SUPPORT == _ON) || (_PORT_CONTROLLER_USERDECITION_SUPPORT == _ON))
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
#endif // End of #ifndef __USER_TYPECINTERFACE__

#endif// #if(_OSD_TYPE == _BEACON_OSD)

