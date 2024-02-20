/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2017>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : Rtd2014OsdTextLengthTable.h
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2014_OSD)
//--------------------------------------------------
// Text Length Table
//--------------------------------------------------
WORD code tsTextLengthOsdNull[] =
{
26,
15,
};	//tsTextLengthOsdNull

WORD code tsTextLengthOsdPicture[] =
{
50,
29,
};	//tsTextLengthOsdPicture

WORD code tsTextLengthOsdDisplay[] =
{
53,
30,
};	//tsTextLengthOsdDisplay

WORD code tsTextLengthOsdColor[] =
{
38,
30,
};	//tsTextLengthOsdColor

WORD code tsTextLengthOsdAdvance[] =
{
63,
29,
};	//tsTextLengthOsdAdvance

WORD code tsTextLengthOsdInput[] =
{
36,
30,
};	//tsTextLengthOsdInput

WORD code tsTextLengthOsdAudio[] =
{
42,
30,
};	//tsTextLengthOsdAudio

WORD code tsTextLengthOsdOther[] =
{
40,
30,
};	//tsTextLengthOsdOther

WORD code tsTextLengthOsdInformation[] =
{
83,
30,
};	//tsTextLengthOsdInformation

WORD code tsTextLengthOsdFactory[] =
{
57,
30,
};	//tsTextLengthOsdFactory

WORD code tsTextLengthOsdBacklight[] =
{
66,
30,
};	//tsTextLengthOsdBacklight

WORD code tsTextLengthOsdBrightness[] =
{
77,
30,
};	//tsTextLengthOsdBrightness

WORD code tsTextLengthOsdContrast[] =
{
64,
44,
};	//tsTextLengthOsdContrast

WORD code tsTextLengthOsdSharpness[] =
{
76,
44,
};	//tsTextLengthOsdSharpness

WORD code tsTextLengthOsdAutoAdjust[] =
{
89,
57,
};	//tsTextLengthOsdAutoAdjust

WORD code tsTextLengthOsdHPosition[] =
{
72,
60,
};	//tsTextLengthOsdHPosition

WORD code tsTextLengthOsdVPosition[] =
{
73,
60,
};	//tsTextLengthOsdVPosition

WORD code tsTextLengthOsdClock[] =
{
39,
30,
};	//tsTextLengthOsdClock

WORD code tsTextLengthOsdPhase[] =
{
44,
30,
};	//tsTextLengthOsdPhase

WORD code tsTextLengthOsdDispRotate[] =
{
85,
60,
};	//tsTextLengthOsdDispRotate

WORD code tsTextLengthOsdDispLatency[] =
{
94,
60,
};	//tsTextLengthOsdDispLatency

WORD code tsTextLengthOsdPanelUniformity[] =
{
120,
75,
};	//tsTextLengthOsdPanelUniformity

WORD code tsTextLengthOsdGamma[] =
{
55,
55,
};	//tsTextLengthOsdGamma

WORD code tsTextLengthOsdTemperature[] =
{
93,
30,
};	//tsTextLengthOsdTemperature

WORD code tsTextLengthOsdColorEffect[] =
{
88,
60,
};	//tsTextLengthOsdColorEffect

WORD code tsTextLengthOsdDemo[] =
{
41,
30,
};	//tsTextLengthOsdDemo

WORD code tsTextLengthOsdColorFormat[] =
{
94,
60,
};	//tsTextLengthOsdColorFormat

WORD code tsTextLengthOsdPcm[] =
{
33,
33,
};	//tsTextLengthOsdPcm

WORD code tsTextLengthOsdHue[] =
{
28,
30,
};	//tsTextLengthOsdHue

WORD code tsTextLengthOsdSaturation[] =
{
76,
45,
};	//tsTextLengthOsdSaturation

WORD code tsTextLengthOsdAspectRatio[] =
{
94,
44,
};	//tsTextLengthOsdAspectRatio

WORD code tsTextLengthOsdOverScan[] =
{
73,
73,
};	//tsTextLengthOsdOverScan

WORD code tsTextLengthOsdOverDrive[] =
{
73,
59,
};	//tsTextLengthOsdOverDrive

WORD code tsTextLengthOsdDcr[] =
{
34,
59,
};	//tsTextLengthOsdDcr

WORD code tsTextLengthOsdDdcci[] =
{
47,
47,
};	//tsTextLengthOsdDdcci

WORD code tsTextLengthOsdUltraVivid[] =
{
74,
74,
};	//tsTextLengthOsdUltraVivid

WORD code tsTextLengthOsdDpOption[] =
{
72,
51,
};	//tsTextLengthOsdDpOption

WORD code tsTextLengthOsdDpMst[] =
{
58,
58,
};	//tsTextLengthOsdDpMst

WORD code tsTextLengthOsdDpResolution[] =
{
101,
66,
};	//tsTextLengthOsdDpResolution

WORD code tsTextLengthOsdCloneMode[] =
{
82,
30,
};	//tsTextLengthOsdCloneMode

#if(_FREESYNC_II_SUPPORT == _ON)
WORD code tsTextLengthOsdFreeSync2[] =
{
81,
81,
};	//tsTextLengthOsdFreeSync2

#endif //#if(_FREESYNC_II_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _OFF)
WORD code tsTextLengthOsdFreeSync[] =
{
72,
72,
};	//tsTextLengthOsdFreeSync

#endif //#if(_FREESYNC_II_SUPPORT == _OFF)

WORD code tsTextLengthOsdFreeze[] =
{
47,
30,
};	//tsTextLengthOsdFreeze

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
WORD code tsTextLengthOsdTypeCConfig[] =
{
105,
87,
};	//tsTextLengthOsdTypeCConfig

#endif //#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

#if(_HDR10_SUPPORT == _ON)
WORD code tsTextLengthOsdUltraHdr[] =
{
73,
73,
};	//tsTextLengthOsdUltraHdr

WORD code tsTextLengthOsdUltraHdrMode[] =
{
115,
115,
};	//tsTextLengthOsdUltraHdrMode

WORD code tsTextLengthOsdDarkEnhance[] =
{
100,
60,
};	//tsTextLengthOsdDarkEnhance

WORD code tsTextLengthOsdSharpnessEnhance[] =
{
109,
74,
};	//tsTextLengthOsdSharpnessEnhance

WORD code tsTextLengthOsdColorEnhance[] =
{
104,
60,
};	//tsTextLengthOsdColorEnhance

WORD code tsTextLengthOsdLightEnhance[] =
{
102,
60,
};	//tsTextLengthOsdLightEnhance

#endif //#if(_HDR10_SUPPORT == _ON)

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
WORD code tsTextLengthOsdLocalDimming[] =
{
103,
59,
};	//tsTextLengthOsdLocalDimming

#endif //#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)

#if(_PIXEL_SHIFT_SUPPORT == _ON)
WORD code tsTextLengthOsdPixelShifting[] =
{
92,
60,
};	//tsTextLengthOsdPixelShifting

#endif //#if(_PIXEL_SHIFT_SUPPORT == _ON)

WORD code tsTextLengthOsdHdmiVersion[] =
{
96,
71,
};	//tsTextLengthOsdHdmiVersion

#if(_SDR_TO_HDR_SUPPORT == _ON)
WORD code tsTextLengthOsdSdrToHdr[] =
{
95,
95,
};	//tsTextLengthOsdSdrToHdr

#endif //#if(_SDR_TO_HDR_SUPPORT == _ON)

WORD code tsTextLengthOsdAutoSelect[] =
{
83,
57,
};	//tsTextLengthOsdAutoSelect

WORD code tsTextLengthOsdVolume[] =
{
54,
30,
};	//tsTextLengthOsdVolume

WORD code tsTextLengthOsdMute[] =
{
35,
30,
};	//tsTextLengthOsdMute

WORD code tsTextLengthOsdStandAlong[] =
{
89,
29,
};	//tsTextLengthOsdStandAlong

WORD code tsTextLengthOsdAudioSource[] =
{
96,
30,
};	//tsTextLengthOsdAudioSource

WORD code tsTextLengthOsdSoundMode[] =
{
88,
60,
};	//tsTextLengthOsdSoundMode

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
WORD code tsTextLengthOsdAudioSelfTest[] =
{
111,
111,
};	//tsTextLengthOsdAudioSelfTest

#endif //#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

WORD code tsTextLengthOsdReset[] =
{
42,
30,
};	//tsTextLengthOsdReset

WORD code tsTextLengthOsdMenuTime[] =
{
77,
59,
};	//tsTextLengthOsdMenuTime

WORD code tsTextLengthOsdOsdHPosition[] =
{
108,
96,
};	//tsTextLengthOsdOsdHPosition

WORD code tsTextLengthOsdOsdVPosition[] =
{
109,
96,
};	//tsTextLengthOsdOsdVPosition

WORD code tsTextLengthOsdLanguage[] =
{
71,
30,
};	//tsTextLengthOsdLanguage

WORD code tsTextLengthOsdTransparency[] =
{
102,
45,
};	//tsTextLengthOsdTransparency

WORD code tsTextLengthOsdRotate[] =
{
50,
30,
};	//tsTextLengthOsdRotate

WORD code tsTextLengthOsdUserMode[] =
{
82,
82,
};	//tsTextLengthOsdUserMode

WORD code tsTextLengthOsdPresetMode[] =
{
95,
67,
};	//tsTextLengthOsdPresetMode

WORD code tsTextLengthOsdPleaseWait[] =
{
84,
45,
};	//tsTextLengthOsdPleaseWait

WORD code tsTextLengthOsdNoCable[] =
{
64,
60,
};	//tsTextLengthOsdNoCable

WORD code tsTextLengthOsdNoSignal[] =
{
67,
45,
};	//tsTextLengthOsdNoSignal

WORD code tsTextLengthOsdNoSupport[] =
{
82,
45,
};	//tsTextLengthOsdNoSupport

WORD code tsTextLengthOsdAutoColor[] =
{
78,
57,
};	//tsTextLengthOsdAutoColor

WORD code tsTextLengthOsdGoToPowerSaving[] =
{
147,
90,
};	//tsTextLengthOsdGoToPowerSaving

WORD code tsTextLengthOsdPass[] =
{
35,
35,
};	//tsTextLengthOsdPass

WORD code tsTextLengthOsdFail[] =
{
24,
24,
};	//tsTextLengthOsdFail

WORD code tsTextLengthOsdStr480i[] =
{
30,
30,
};	//tsTextLengthOsdStr480i

WORD code tsTextLengthOsdStr480p[] =
{
37,
37,
};	//tsTextLengthOsdStr480p

WORD code tsTextLengthOsdStr576i[] =
{
30,
30,
};	//tsTextLengthOsdStr576i

WORD code tsTextLengthOsdStr576p[] =
{
37,
37,
};	//tsTextLengthOsdStr576p

WORD code tsTextLengthOsdStr720p[] =
{
37,
37,
};	//tsTextLengthOsdStr720p

WORD code tsTextLengthOsdStr1080i[] =
{
36,
36,
};	//tsTextLengthOsdStr1080i

WORD code tsTextLengthOsdStr1080p[] =
{
43,
43,
};	//tsTextLengthOsdStr1080p

code WORD *tOSD_TABLE_LANGUAGE_TEXT_LENGTH[] =
{
tsTextLengthOsdNull,
tsTextLengthOsdPicture,
tsTextLengthOsdDisplay,
tsTextLengthOsdColor,
tsTextLengthOsdAdvance,
tsTextLengthOsdInput,
tsTextLengthOsdAudio,
tsTextLengthOsdOther,
tsTextLengthOsdInformation,
tsTextLengthOsdFactory,
tsTextLengthOsdBacklight,
tsTextLengthOsdBrightness,
tsTextLengthOsdContrast,
tsTextLengthOsdSharpness,
tsTextLengthOsdAutoAdjust,
tsTextLengthOsdHPosition,
tsTextLengthOsdVPosition,
tsTextLengthOsdClock,
tsTextLengthOsdPhase,
tsTextLengthOsdDispRotate,
tsTextLengthOsdDispLatency,
tsTextLengthOsdPanelUniformity,
tsTextLengthOsdGamma,
tsTextLengthOsdTemperature,
tsTextLengthOsdColorEffect,
tsTextLengthOsdDemo,
tsTextLengthOsdColorFormat,
tsTextLengthOsdPcm,
tsTextLengthOsdHue,
tsTextLengthOsdSaturation,
tsTextLengthOsdAspectRatio,
tsTextLengthOsdOverScan,
tsTextLengthOsdOverDrive,
tsTextLengthOsdDcr,
tsTextLengthOsdDdcci,
tsTextLengthOsdUltraVivid,
tsTextLengthOsdDpOption,
tsTextLengthOsdDpMst,
tsTextLengthOsdDpResolution,
tsTextLengthOsdCloneMode,
#if(_FREESYNC_II_SUPPORT == _ON)
tsTextLengthOsdFreeSync2,
#endif //#if(_FREESYNC_II_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _OFF)
tsTextLengthOsdFreeSync,
#endif //#if(_FREESYNC_II_SUPPORT == _OFF)

tsTextLengthOsdFreeze,
#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
tsTextLengthOsdTypeCConfig,
#endif //#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)

#if(_HDR10_SUPPORT == _ON)
tsTextLengthOsdUltraHdr,
tsTextLengthOsdUltraHdrMode,
tsTextLengthOsdDarkEnhance,
tsTextLengthOsdSharpnessEnhance,
tsTextLengthOsdColorEnhance,
tsTextLengthOsdLightEnhance,
#endif //#if(_HDR10_SUPPORT == _ON)

#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
tsTextLengthOsdLocalDimming,
#endif //#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)

#if(_PIXEL_SHIFT_SUPPORT == _ON)
tsTextLengthOsdPixelShifting,
#endif //#if(_PIXEL_SHIFT_SUPPORT == _ON)

tsTextLengthOsdHdmiVersion,
#if(_SDR_TO_HDR_SUPPORT == _ON)
tsTextLengthOsdSdrToHdr,
#endif //#if(_SDR_TO_HDR_SUPPORT == _ON)

tsTextLengthOsdAutoSelect,
tsTextLengthOsdVolume,
tsTextLengthOsdMute,
tsTextLengthOsdStandAlong,
tsTextLengthOsdAudioSource,
tsTextLengthOsdSoundMode,
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
tsTextLengthOsdAudioSelfTest,
#endif //#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)

tsTextLengthOsdReset,
tsTextLengthOsdMenuTime,
tsTextLengthOsdOsdHPosition,
tsTextLengthOsdOsdVPosition,
tsTextLengthOsdLanguage,
tsTextLengthOsdTransparency,
tsTextLengthOsdRotate,
tsTextLengthOsdUserMode,
tsTextLengthOsdPresetMode,
tsTextLengthOsdPleaseWait,
tsTextLengthOsdNoCable,
tsTextLengthOsdNoSignal,
tsTextLengthOsdNoSupport,
tsTextLengthOsdAutoColor,
tsTextLengthOsdGoToPowerSaving,
tsTextLengthOsdPass,
tsTextLengthOsdFail,
tsTextLengthOsdStr480i,
tsTextLengthOsdStr480p,
tsTextLengthOsdStr576i,
tsTextLengthOsdStr576p,
tsTextLengthOsdStr720p,
tsTextLengthOsdStr1080i,
tsTextLengthOsdStr1080p,
};	//*tOSD_TABLE_LANGUAGE_TEXT_LENGTH

#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)

