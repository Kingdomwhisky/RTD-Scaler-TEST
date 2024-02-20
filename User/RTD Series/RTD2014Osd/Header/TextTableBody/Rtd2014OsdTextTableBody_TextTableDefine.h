code BYTE *tOSD_TABLE_LANGUAGE_TEXT[] =
{
tsOsdNull,
tsOsdPicture,
tsOsdDisplay,
tsOsdColor,
tsOsdAdvance,
tsOsdInput,
tsOsdAudio,
tsOsdOther,
tsOsdInformation,
tsOsdFactory,
tsOsdBacklight,
tsOsdBrightness,
tsOsdContrast,
tsOsdSharpness,
tsOsdAutoAdjust,
tsOsdHPosition,
tsOsdVPosition,
tsOsdClock,
tsOsdPhase,
tsOsdDispRotate,
tsOsdDispLatency,
tsOsdPanelUniformity,
tsOsdGamma,
tsOsdTemperature,
tsOsdColorEffect,
tsOsdDemo,
tsOsdColorFormat,
tsOsdPcm,
tsOsdHue,
tsOsdSaturation,
tsOsdAspectRatio,
tsOsdOverScan,
tsOsdOverDrive,
tsOsdDcr,
tsOsdDdcci,
tsOsdUltraVivid,
tsOsdDpOption,
tsOsdDpMst,
tsOsdDpResolution,
tsOsdCloneMode,
#if(_FREESYNC_II_SUPPORT == _ON)
tsOsdFreeSync2,
#endif //#if(_FREESYNC_II_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _OFF)
tsOsdFreeSync,
#endif //#if(_FREESYNC_II_SUPPORT == _OFF)

tsOsdFreeze,
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
tsOsdTypeCConfig,
#endif //#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

#if(_HDR10_SUPPORT == _ON)
tsOsdUltraHdr,
tsOsdUltraHdrMode,
tsOsdDarkEnhance,
tsOsdSharpnessEnhance,
tsOsdColorEnhance,
tsOsdLightEnhance,
#endif //#if(_HDR10_SUPPORT == _ON)

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
tsOsdLocalDimming,
#endif //#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)

#if(_PIXEL_SHIFT_SUPPORT == _ON)
tsOsdPixelShifting,
#endif //#if(_PIXEL_SHIFT_SUPPORT == _ON)

tsOsdHdmiVersion,
#if(_SDR_TO_HDR_SUPPORT == _ON)
tsOsdSdrToHdr,
#endif //#if(_SDR_TO_HDR_SUPPORT == _ON)

tsOsdAutoSelect,
tsOsdVolume,
tsOsdMute,
tsOsdStandAlong,
tsOsdAudioSource,
tsOsdSoundMode,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
tsOsdAudioSelfTest,
#endif //#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

tsOsdReset,
tsOsdMenuTime,
tsOsdOsdHPosition,
tsOsdOsdVPosition,
tsOsdLanguage,
tsOsdTransparency,
tsOsdRotate,
tsOsdUserMode,
tsOsdPresetMode,
tsOsdPleaseWait,
tsOsdNoCable,
tsOsdNoSignal,
tsOsdNoSupport,
tsOsdAutoColor,
tsOsdGoToPowerSaving,
tsOsdPass,
tsOsdFail,
tsOsdStr480i,
tsOsdStr480p,
tsOsdStr576i,
tsOsdStr576p,
tsOsdStr720p,
tsOsdStr1080i,
tsOsdStr1080p,
};	//*tOSD_TABLE_LANGUAGE_TEXT

