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
// ID Code      : ScalerCommonSyncInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of DP/HDMI HotPlug Toggle Support
//--------------------------------------------------
#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Digital Input Port Switch
//--------------------------------------------------
#define GET_DIGITAL_PORT_SWITCH_TO_D0()                         ((g_ucDigitalSwitch & _BIT5) >> 5)
#define SET_DIGITAL_PORT_SWITCH_TO_D0()                         (g_ucDigitalSwitch |= _BIT5)
#define CLR_DIGITAL_PORT_SWITCH_TO_D0()                         (g_ucDigitalSwitch &= ~_BIT5)

#define GET_DIGITAL_PORT_SWITCH_TO_D1()                         ((g_ucDigitalSwitch & _BIT4) >> 4)
#define SET_DIGITAL_PORT_SWITCH_TO_D1()                         (g_ucDigitalSwitch |= _BIT4)
#define CLR_DIGITAL_PORT_SWITCH_TO_D1()                         (g_ucDigitalSwitch &= ~_BIT4)

#define GET_DIGITAL_PORT_SWITCH_TO_D2()                         ((g_ucDigitalSwitch & _BIT3) >> 3)
#define SET_DIGITAL_PORT_SWITCH_TO_D2()                         (g_ucDigitalSwitch |= _BIT3)
#define CLR_DIGITAL_PORT_SWITCH_TO_D2()                         (g_ucDigitalSwitch &= ~_BIT3)

#define GET_DIGITAL_PORT_SWITCH_TO_D3()                         ((g_ucDigitalSwitch & _BIT2) >> 2)
#define SET_DIGITAL_PORT_SWITCH_TO_D3()                         (g_ucDigitalSwitch |= _BIT2)
#define CLR_DIGITAL_PORT_SWITCH_TO_D3()                         (g_ucDigitalSwitch &= ~_BIT2)

#define GET_DIGITAL_PORT_SWITCH_TO_D4()                         ((g_ucDigitalSwitch & _BIT1) >> 1)
#define SET_DIGITAL_PORT_SWITCH_TO_D4()                         (g_ucDigitalSwitch |= _BIT1)
#define CLR_DIGITAL_PORT_SWITCH_TO_D4()                         (g_ucDigitalSwitch &= ~_BIT1)

#define GET_DIGITAL_PORT_SWITCH_TO_D5()                         ((g_ucDigitalSwitch & _BIT0) >> 0)
#define SET_DIGITAL_PORT_SWITCH_TO_D5()                         (g_ucDigitalSwitch |= _BIT0)
#define CLR_DIGITAL_PORT_SWITCH_TO_D5()                         (g_ucDigitalSwitch &= ~_BIT0)

#define GET_DIGITAL_PORT_SWITCH_TO_D6()                         ((g_ucDigitalSwitch & _BIT6) >> 6)
#define SET_DIGITAL_PORT_SWITCH_TO_D6()                         (g_ucDigitalSwitch |= _BIT6)
#define CLR_DIGITAL_PORT_SWITCH_TO_D6()                         (g_ucDigitalSwitch &= ~_BIT6)

#define GET_DP_DC_OFF_HPD_HIGH()                                (g_bDpDCOffHPDHigh)
#define SET_DP_DC_OFF_HPD_HIGH()                                (g_bDpDCOffHPDHigh = _TRUE)
#define CLR_DP_DC_OFF_HPD_HIGH()                                (g_bDpDCOffHPDHigh = _FALSE)

#define GET_PS_WAKEUP_HPD_TOGGLE()                              (g_bPsWakeupHpd)
#define SET_PS_WAKEUP_HPD_TOGGLE()                              (g_bPsWakeupHpd = _TRUE)
#define CLR_PS_WAKEUP_HPD_TOGGLE()                              (g_bPsWakeupHpd = _FALSE)

#define GET_HDMI_HOTPLUG_TOGGLE()                               ((g_ucHDMIHotPlug & _BIT7) >> 7)
#define SET_HDMI_HOTPLUG_TOGGLE()                               (g_ucHDMIHotPlug |= _BIT7)
#define CLR_HDMI_HOTPLUG_TOGGLE()                               (g_ucHDMIHotPlug &= ~_BIT7)

#define GET_HDMI_HOTPLUG_TIME()                                 ((WORD)(g_ucHDMIHotPlug & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) * 100)
#define SET_HDMI_HOTPLUG_TIME(x)                                (g_ucHDMIHotPlug = (g_ucHDMIHotPlug & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x))

#define GET_DP_AUX_DIFF_MODE()                                  (g_stDpAuxSetting.b1DpAuxMode)
#define SET_DP_AUX_DIFF_MODE()                                  (g_stDpAuxSetting.b1DpAuxMode = _TRUE)
#define CLR_DP_AUX_DIFF_MODE()                                  (g_stDpAuxSetting.b1DpAuxMode = _FALSE)

#define GET_DP_AUX_ADJR_SETTING()                               (g_stDpAuxSetting.b4DpAuxAdjrSet)
#define SET_DP_AUX_ADJR_SETTING(x)                              (g_stDpAuxSetting.b4DpAuxAdjrSet = (x))

#define GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD()                  (g_bDpMstDCOffHPDToggleHoldFlag)
#define SET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD()                  (g_bDpMstDCOffHPDToggleHoldFlag = _TRUE)
#define CLR_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD()                  (g_bDpMstDCOffHPDToggleHoldFlag = _FALSE)

//--------------------------------------------------
// Macro of Digital color info change
//--------------------------------------------------
#define GET_DIGITAL_COLOR_INFO_CHANGE_RESET()                   (g_bDigitalColorInfoChangeReset)
#define SET_DIGITAL_COLOR_INFO_CHANGE_RESET()                   (g_bDigitalColorInfoChangeReset = _TRUE)
#define CLR_DIGITAL_COLOR_INFO_CHANGE_RESET()                   (g_bDigitalColorInfoChangeReset = _FALSE)


#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP IRQ Time Setting
//--------------------------------------------------
#define GET_DP_IRQ_TIME_10US()                                  (g_ucDpIrqTime_10us)
#define SET_DP_IRQ_TIME_10US(x)                                 (g_ucDpIrqTime_10us = (x))

#define GET_DP_DC_OFF_HPD_TOGGLE_FLAG()                         (g_bDpDCOffHPDToggleFlag)
#define SET_DP_DC_OFF_HPD_TOGGLE_FLAG()                         (g_bDpDCOffHPDToggleFlag = 1)
#define CLR_DP_DC_OFF_HPD_TOGGLE_FLAG()                         (g_bDpDCOffHPDToggleFlag = 0)

//--------------------------------------------------
// Definitions of DP Illegal Idle Pattern Check
//--------------------------------------------------
#define GET_DP_ILLEGAL_IDLE_PATTERN_CHECK()                     (g_bDpIllegalIdlePatternCheck)
#define SET_DP_ILLEGAL_IDLE_PATTERN_CHECK()                     (g_bDpIllegalIdlePatternCheck = _TRUE)
#define CLR_DP_ILLEGAL_IDLE_PATTERN_CHECK()                     (g_bDpIllegalIdlePatternCheck = _FALSE)
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
#define GET_D0_HDMI_5V_STATUS()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D0Hdmi5VStatus))
#define SET_D0_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D0Hdmi5VStatus = 1)
#define CLR_D0_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D0Hdmi5VStatus = 0)

#define GET_D1_HDMI_5V_STATUS()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D1Hdmi5VStatus))
#define SET_D1_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D1Hdmi5VStatus = 1)
#define CLR_D1_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D1Hdmi5VStatus = 0)

#define GET_D2_HDMI_5V_STATUS()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D2Hdmi5VStatus))
#define SET_D2_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D2Hdmi5VStatus = 1)
#define CLR_D2_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D2Hdmi5VStatus = 0)

#define GET_D3_HDMI_5V_STATUS()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D3Hdmi5VStatus))
#define SET_D3_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D3Hdmi5VStatus = 1)
#define CLR_D3_HDMI_5V_STATUS()                                 (g_stDpHdmiCompatibleInfo.b1D3Hdmi5VStatus = 0)

#define GET_D0_HDMI_PS_WAKEUP()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D0HdmiPSWakeUp))
#define SET_D0_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D0HdmiPSWakeUp = 1)
#define CLR_D0_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D0HdmiPSWakeUp = 0)

#define GET_D1_HDMI_PS_WAKEUP()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D1HdmiPSWakeUp))
#define SET_D1_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D1HdmiPSWakeUp = 1)
#define CLR_D1_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D1HdmiPSWakeUp = 0)

#define GET_D2_HDMI_PS_WAKEUP()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D2HdmiPSWakeUp))
#define SET_D2_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D2HdmiPSWakeUp = 1)
#define CLR_D2_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D2HdmiPSWakeUp = 0)

#define GET_D3_HDMI_PS_WAKEUP()                                 ((bit)(g_stDpHdmiCompatibleInfo.b1D3HdmiPSWakeUp))
#define SET_D3_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D3HdmiPSWakeUp = 1)
#define CLR_D3_HDMI_PS_WAKEUP()                                 (g_stDpHdmiCompatibleInfo.b1D3HdmiPSWakeUp = 0)
#endif

#endif

//--------------------------------------------------
// Macro of FreeSync
//--------------------------------------------------
#if(_FREESYNC_SUPPORT == _ON)
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
#define GET_DP_RX0_FREESYNC_SUPPORT()                           (g_stDpFREESYNCInfo.enumDPRX0FREESYNCSupport)
#define SET_DP_RX0_FREESYNC_SUPPORT(x)                          (g_stDpFREESYNCInfo.enumDPRX0FREESYNCSupport = (x))

#define GET_DP_RX1_FREESYNC_SUPPORT()                           (g_stDpFREESYNCInfo.enumDPRX1FREESYNCSupport)
#define SET_DP_RX1_FREESYNC_SUPPORT(x)                          (g_stDpFREESYNCInfo.enumDPRX1FREESYNCSupport = (x))

#define GET_DP_RX2_FREESYNC_SUPPORT()                           (g_stDpFREESYNCInfo.enumDPRX2FREESYNCSupport)
#define SET_DP_RX2_FREESYNC_SUPPORT(x)                          (g_stDpFREESYNCInfo.enumDPRX2FREESYNCSupport = (x))

#define GET_DP_RX6_FREESYNC_SUPPORT()                           (g_stDpFREESYNCInfo.enumDPRX6FREESYNCSupport)
#define SET_DP_RX6_FREESYNC_SUPPORT(x)                          (g_stDpFREESYNCInfo.enumDPRX6FREESYNCSupport = (x))
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
#define GET_TMDS_RX0_FREESYNC_SUPPORT()                         (g_stHDMIFREESYNCInfo.enumHDMIRX0FREESYNCSupport)
#define SET_TMDS_RX0_FREESYNC_SUPPORT(x)                        (g_stHDMIFREESYNCInfo.enumHDMIRX0FREESYNCSupport = (x))

#define GET_TMDS_RX1_FREESYNC_SUPPORT()                         (g_stHDMIFREESYNCInfo.enumHDMIRX1FREESYNCSupport)
#define SET_TMDS_RX1_FREESYNC_SUPPORT(x)                        (g_stHDMIFREESYNCInfo.enumHDMIRX1FREESYNCSupport = (x))

#define GET_TMDS_RX2_FREESYNC_SUPPORT()                         (g_stHDMIFREESYNCInfo.enumHDMIRX2FREESYNCSupport)
#define SET_TMDS_RX2_FREESYNC_SUPPORT(x)                        (g_stHDMIFREESYNCInfo.enumHDMIRX2FREESYNCSupport = (x))

#define GET_TMDS_RX3_FREESYNC_SUPPORT()                         (g_stHDMIFREESYNCInfo.enumHDMIRX3FREESYNCSupport)
#define SET_TMDS_RX3_FREESYNC_SUPPORT(x)                        (g_stHDMIFREESYNCInfo.enumHDMIRX3FREESYNCSupport = (x))

#define GET_TMDS_RX4_FREESYNC_SUPPORT()                         (g_stHDMIFREESYNCInfo.enumHDMIRX4FREESYNCSupport)
#define SET_TMDS_RX4_FREESYNC_SUPPORT(x)                        (g_stHDMIFREESYNCInfo.enumHDMIRX4FREESYNCSupport = (x))

#define GET_TMDS_RX5_FREESYNC_SUPPORT()                         (g_stHDMIFREESYNCInfo.enumHDMIRX5FREESYNCSupport)
#define SET_TMDS_RX5_FREESYNC_SUPPORT(x)                        (g_stHDMIFREESYNCInfo.enumHDMIRX5FREESYNCSupport = (x))
#endif // End of #if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
#endif // End of #if(_FREESYNC_SUPPORT == _ON)


//--------------------------------------------------
// Macro of HDR10 Setting
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)
#define GET_HDR10_EOTF_SETTING()                                (g_stHDR10Setting.enumHDR10EOTFSetting)
#define SET_HDR10_EOTF_SETTING(x)                               (g_stHDR10Setting.enumHDR10EOTFSetting = (x))

#define GET_HDR10_MAX_LV_SETTING()                              (g_stHDR10Setting.enumHDR10MaxLVSetting)
#define SET_HDR10_MAX_LV_SETTING(x)                             (g_stHDR10Setting.enumHDR10MaxLVSetting = (x))

#define GET_RX0_HDR10_SUPPORT()                                 (g_stHDR10PortSettingInfo.enumHDR10RX0Support)
#define SET_RX0_HDR10_SUPPORT(x)                                (g_stHDR10PortSettingInfo.enumHDR10RX0Support = (x))

#define GET_RX1_HDR10_SUPPORT()                                 (g_stHDR10PortSettingInfo.enumHDR10RX1Support)
#define SET_RX1_HDR10_SUPPORT(x)                                (g_stHDR10PortSettingInfo.enumHDR10RX1Support = (x))

#define GET_RX2_HDR10_SUPPORT()                                 (g_stHDR10PortSettingInfo.enumHDR10RX2Support)
#define SET_RX2_HDR10_SUPPORT(x)                                (g_stHDR10PortSettingInfo.enumHDR10RX2Support = (x))

#define GET_RX3_HDR10_SUPPORT()                                 (g_stHDR10PortSettingInfo.enumHDR10RX3Support)
#define SET_RX3_HDR10_SUPPORT(x)                                (g_stHDR10PortSettingInfo.enumHDR10RX3Support = (x))

#define GET_RX4_HDR10_SUPPORT()                                 (g_stHDR10PortSettingInfo.enumHDR10RX4Support)
#define SET_RX4_HDR10_SUPPORT(x)                                (g_stHDR10PortSettingInfo.enumHDR10RX4Support = (x))

#define GET_RX5_HDR10_SUPPORT()                                 (g_stHDR10PortSettingInfo.enumHDR10RX5Support)
#define SET_RX5_HDR10_SUPPORT(x)                                (g_stHDR10PortSettingInfo.enumHDR10RX5Support = (x))

#define GET_RX6_HDR10_SUPPORT()                                 (g_stHDR10PortSettingInfo.enumHDR10RX6Support)
#define SET_RX6_HDR10_SUPPORT(x)                                (g_stHDR10PortSettingInfo.enumHDR10RX6Support = (x))
#endif

//--------------------------------------------------
// Macro of FreeSync Enable
//--------------------------------------------------
#if(_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_SPD_INFO_FRAME_RECEIVED()                  (g_bFREESYNCSPDInfoReceive)
#define SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(x)                 (g_bFREESYNCSPDInfoReceive = (x))

#define GET_FREESYNC_IVF_INFO()                                 (g_bFREESYNCGetIVFInfo)
#define SET_FREESYNC_IVF_INFO(x)                                (g_bFREESYNCGetIVFInfo = (x))

#define GET_FREESYNC_VFREQ_MAX()                                (g_usFREESYNCVFreq_max)
#define SET_FREESYNC_VFREQ_MAX(x)                               (g_usFREESYNCVFreq_max = (x))

#define GET_FREESYNC_VFREQ_MIN()                                (g_usFREESYNCVFreq_min)
#define SET_FREESYNC_VFREQ_MIN(x)                               (g_usFREESYNCVFreq_min = (x))

#if((_DP_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
#define GET_FREESYNC_ENABLED()                                  ((bit)(GET_DP_FREESYNC_ENABLED() | GET_HDMI_FREESYNC_ENABLED()))
#define CLR_FREESYNC_ENABLED()                                  {\
                                                                    CLR_DP_FREESYNC_ENABLED();\
                                                                    CLR_HDMI_FREESYNC_ENABLED();\
                                                                }
#elif(_DP_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_ENABLED()                                  (GET_DP_FREESYNC_ENABLED())
#define CLR_FREESYNC_ENABLED()                                  {\
                                                                    CLR_DP_FREESYNC_ENABLED();\
                                                                }
#else
#define GET_FREESYNC_ENABLED()                                  (GET_HDMI_FREESYNC_ENABLED())
#define CLR_FREESYNC_ENABLED()                                  {\
                                                                    CLR_HDMI_FREESYNC_ENABLED();\
                                                                }
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_FREESYNC_ENABLED()                               (g_stDpFREESYNCInfo.b1DPFREESYNCEnable)
#define SET_DP_FREESYNC_ENABLED()                               (g_stDpFREESYNCInfo.b1DPFREESYNCEnable = _ENABLE)
#define CLR_DP_FREESYNC_ENABLED()                               (g_stDpFREESYNCInfo.b1DPFREESYNCEnable = _DISABLE)
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#define GET_HDMI_FREESYNC_ENABLED()                             (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable)
#define SET_HDMI_FREESYNC_ENABLED()                             (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable = _ENABLE)
#define CLR_HDMI_FREESYNC_ENABLED()                             (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable = _DISABLE)
#endif

#endif

//--------------------------------------------------
// Macro of FreeSyncII Setting
//--------------------------------------------------
#if(_FREESYNC_II_SUPPORT == _ON)
#define GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING()            (g_stFreeSyncIISetting.b1NativeColorSpaceEnable)
#define SET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(x)           (g_stFreeSyncIISetting.b1NativeColorSpaceEnable = (x))

#define GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING()      (g_stFreeSyncIISetting.b1BacklightControlEnable)
#define SET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(x)     (g_stFreeSyncIISetting.b1BacklightControlEnable = (x))

#define GET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING()         (g_stFreeSyncIISetting.b1LocalDimmingDisable)
#define SET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(x)        (g_stFreeSyncIISetting.b1LocalDimmingDisable = (x))

#define GET_FREESYNC_II_EOTF_TYPE_SETTING()                     (g_stFreeSyncIISetting.b5EOTFType)
#define SET_FREESYNC_II_EOTF_TYPE_SETTING(x)                    (g_stFreeSyncIISetting.b5EOTFType = (x))

#define GET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING()       (g_stFreeSyncIISetting.ucBacklightControlRatio)
#define SET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING(x)      (g_stFreeSyncIISetting.ucBacklightControlRatio = (x))
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
#define GET_AIO_MODERN_STANDBY_MODE()                           (g_bAIOModernStandbyMode)
#define SET_AIO_MODERN_STANDBY_MODE()                           (g_bAIOModernStandbyMode = _TRUE)
#define CLR_AIO_MODERN_STANDBY_MODE()                           (g_bAIOModernStandbyMode = _FALSE)
#endif


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
extern BYTE g_ucDigitalSwitch;
extern bit g_bDpDCOffHPDHigh;
extern BYTE g_ucHDMIHotPlug;
extern bit g_bDigitalColorInfoChangeReset;
extern bit g_bPsWakeupHpd;
#if(_DP_SUPPORT == _ON)
extern StructDPMarginLinkInfo g_stDpMarginLink;
extern StructDpAuxSetting g_stDpAuxSetting;
extern BYTE g_ucDpIrqTime_10us;
extern bit g_bDpIllegalIdlePatternCheck;
extern bit g_bDpMstDCOffHPDToggleHoldFlag;
extern bit g_bDpDCOffHPDToggleFlag;
#endif

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
extern StructDpHdmiCompatibleInfo g_stDpHdmiCompatibleInfo;
#endif

#endif

#if(_FREESYNC_SUPPORT == _ON)
#if((_DP_FREESYNC_SUPPORT == _ON) || (_DP_FREESYNC_II_SUPPORT == _ON))
extern StructDPFREESYNCENABLE g_stDpFREESYNCInfo;
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
extern StructHDMIFREESYNCENABLE g_stHDMIFREESYNCInfo;
#endif

extern WORD g_usFREESYNCVFreq_max;
extern bit g_bFREESYNCSPDInfoReceive;
extern bit g_bFREESYNCGetIVFInfo;
#endif

#if(_HDR10_SUPPORT == _ON)
extern StructHDR10StaticMetaData g_stHDR10SaticMetadata;
extern StructHDR10Setting g_stHDR10Setting;
extern StructHDR10PortSettingInfo g_stHDR10PortSettingInfo;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
extern StructFreeSyncIIInfo g_stFreeSyncIIMetadata;
#endif

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
extern bit g_bAIOModernStandbyMode;
#endif


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
extern bit ScalerSyncGetFREESYNCEnable(void);

#if((_DEBUG_MESSAGE_SUPPORT == _OFF) && (_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE ScalerSyncGetHDMIFREESYNCVcp_EXINT1(void);
extern void ScalerSyncSetHDMIFREESYNCVcp_EXINT1(BYTE ucVcpCode);
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerSyncGetColorInfoFrame(EnumSourceSearchPort enumSourceSearchPort, EnumDPGetRSV0InfoStatus enumDPGetRSV0InfoStatus);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_SUPPORT == _ON)
extern void ScalerSyncDpCapabilitySwitchProc(void);
extern void ScalerSyncDpFakeLTProtect(void);
extern bit ScalerSyncDpCableStatus(EnumSourceSearchPort enumInputPort);
extern void ScalerSyncDpSetCableStatus(EnumSourceSearchPort enumInputPort, bit bStatus);

#if(_DP_IRQ_HPD_MODE == _DP_IRQ_HPD_T2_MODE)
extern void ScalerSyncDpHpdIrqAssertTimer2EventProc_EXINT(void);
#endif

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
extern void ScalerSyncDpRepeaterPowerOffReset(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerSyncDpRxSinkCountUpdateProc(EnumSourceSearchPort enumInputPort);
#endif

#endif

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerSyncDpTxCloneOutputPortCheck(BYTE ucInputPort);
extern void ScalerSyncDpTxHdcpUpstreamSwitchProc(BYTE ucInputPort);
extern void ScalerSyncDpHdcpRepeaterCapableProc(BYTE ucInputPort, BYTE ucPortType);

#if(_DP_MST_SUPPORT == _ON)
#endif
#endif

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerSyncDpFakePowerSavingCheck(void);
extern bit ScalerSyncDpFakePowerOffCheck(EnumSourceSearchPort enumInputPort);
extern void ScalerSyncDpSourceWritePowerUpProc(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable);
extern void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray);
#endif

extern EnumHDCPType ScalerSyncHdcpCheckEnabled(BYTE ucInputPort);
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_URGENT_EVENT_CHECK_MODE == _ON)
extern bit ScalerSyncCheckUrgentEvent(void);
extern bit ScalerSyncGetUrgentEventFlg(void);
extern void ScalerSyncClrUrgentEventFlg(void);
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern BYTE ScalerSyncDdcDetect_EXINT1(void);
extern void ScalerSyncTMDSScanInitial(BYTE ucInputPort);

#if(_HDMI_SUPPORT == _ON)
extern void ScalerSyncTMDSEdidSwitch(BYTE ucPortSelect);
extern bit ScalerSyncHDMIDdcCheckBusy(BYTE ucInputPort, EnumTMDSDdcDebounceType enumTmdsDdcDebounceType, BYTE ucDebounceTimeScale, WORD usDebounceTimePeriod);
#endif
extern void ScalerSyncTMDSHPDToggleProc(void);
#endif

#if(_MHL_SUPPORT == _ON)
extern bit ScalerSyncMHLVBusPowerExist(void);
#endif

extern void ScalerSyncActiveProc(BYTE ucSourceType);
extern void ScalerSyncPowerProc(EnumPowerAction enumPowerAction);
extern void ScalerSyncInterfaceSwitch(BYTE ucInputPort, BYTE ucPortType, BYTE ucSourceSearchDelayMode);
#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern void ScalerSyncBgInterfaceSwitch(BYTE ucInputPort, BYTE ucInputPortType, BYTE ucDetectPort, BYTE ucDetectPortType, BYTE ucSourceSearchDelayMode);
#endif
extern void ScalerSyncSetDdcForceNack(BYTE ucInputPort, bit bSelect);
extern bit ScalerSyncGetDdcForceNackStatus(BYTE ucInputPort);

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern bit ScalerSyncDigitalGetColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerSyncDigitalGetColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerSyncDigitalGetQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerSyncDigitalClrColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerSyncDigitalClrColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerSyncDigitalClrQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_HW_FLASH_ACCESS_METHOD == _XDATA_MAP_ACCESS)
extern bit ScalerSyncVGAUseEmbeddedEDID(void);
extern void ScalerSyncVGADdcCheckBusyAndForceNack(void);
#endif

