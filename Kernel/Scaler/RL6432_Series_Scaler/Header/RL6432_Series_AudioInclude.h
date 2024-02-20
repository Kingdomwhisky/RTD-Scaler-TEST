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
// ID Code      : RL6432_Series_AudioInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if((_D0_HDMI_SUPPORT == _ON) || (_D0_DP_EXIST == _ON))
#define GET_AUDIO_D0_ICODE_RELOADED()               (bit)(g_stAudioD0DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D0_ICODE_RELOADED()               (g_stAudioD0DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D0_ICODE_RELOADED()               (g_stAudioD0DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D0_SAMPLING_FREQ()                (g_stAudioD0DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D0_SAMPLING_FREQ(x)               (g_stAudioD0DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D0_PACKET_DETECT()                (bit)(g_stAudioD0DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D0_PACKET_DETECT()                (g_stAudioD0DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D0_PACKET_DETECT()                (g_stAudioD0DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D0_DIGITAL_AUDIO_SOURCE()               (g_stAudioD0DigtalInfo.b2AudioDigitalSource)
#define SET_D0_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD0DigtalInfo.b2AudioDigitalSource = (x))
#endif

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_DP_EXIST == _ON))
#define GET_AUDIO_D1_ICODE_RELOADED()               (bit)(g_stAudioD1DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D1_ICODE_RELOADED()               (g_stAudioD1DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D1_ICODE_RELOADED()               (g_stAudioD1DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D1_SAMPLING_FREQ()                (g_stAudioD1DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D1_SAMPLING_FREQ(x)               (g_stAudioD1DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D1_PACKET_DETECT()                (bit)(g_stAudioD1DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D1_PACKET_DETECT()                (g_stAudioD1DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D1_PACKET_DETECT()                (g_stAudioD1DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D1_DIGITAL_AUDIO_SOURCE()               (g_stAudioD1DigtalInfo.b2AudioDigitalSource)
#define SET_D1_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD1DigtalInfo.b2AudioDigitalSource = (x))
#endif

#if(_D2_HDMI_SUPPORT == _ON)
#define GET_AUDIO_D2_ICODE_RELOADED()               (bit)(g_stAudioD2DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D2_ICODE_RELOADED()               (g_stAudioD2DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D2_ICODE_RELOADED()               (g_stAudioD2DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D2_SAMPLING_FREQ()                (g_stAudioD2DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D2_SAMPLING_FREQ(x)               (g_stAudioD2DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D2_PACKET_DETECT()                (bit)(g_stAudioD2DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D2_PACKET_DETECT()                (g_stAudioD2DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D2_PACKET_DETECT()                (g_stAudioD2DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D2_DIGITAL_AUDIO_SOURCE()               (g_stAudioD2DigtalInfo.b2AudioDigitalSource)
#define SET_D2_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD2DigtalInfo.b2AudioDigitalSource = (x))
#endif

#if(_D3_HDMI_SUPPORT == _ON)
#define GET_AUDIO_D3_ICODE_RELOADED()               (bit)(g_stAudioD3DigtalInfo.b1AudioICodeReloaded)
#define SET_AUDIO_D3_ICODE_RELOADED()               (g_stAudioD3DigtalInfo.b1AudioICodeReloaded = _TRUE)
#define CLR_AUDIO_D3_ICODE_RELOADED()               (g_stAudioD3DigtalInfo.b1AudioICodeReloaded = _FALSE)

#define GET_AUDIO_D3_SAMPLING_FREQ()                (g_stAudioD3DigtalInfo.b4AudioSamplingFreq)
#define SET_AUDIO_D3_SAMPLING_FREQ(x)               (g_stAudioD3DigtalInfo.b4AudioSamplingFreq = (x))

#define GET_AUDIO_D3_PACKET_DETECT()                (bit)(g_stAudioD3DigtalInfo.b1AudioDetected)
#define SET_AUDIO_D3_PACKET_DETECT()                (g_stAudioD3DigtalInfo.b1AudioDetected = _TRUE)
#define CLR_AUDIO_D3_PACKET_DETECT()                (g_stAudioD3DigtalInfo.b1AudioDetected = _FALSE)

#define GET_D3_DIGITAL_AUDIO_SOURCE()               (g_stAudioD3DigtalInfo.b2AudioDigitalSource)
#define SET_D3_DIGITAL_AUDIO_SOURCE(x)              (g_stAudioD3DigtalInfo.b2AudioDigitalSource = (x))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_D0_DP_EXIST == _ON)
extern StructAudioDigitalInfo g_stAudioD0DigtalInfo;
#endif

#if(_D1_DP_EXIST == _ON)
extern StructAudioDigitalInfo g_stAudioD1DigtalInfo;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
extern StructAudioDigitalInfo g_stAudioD2DigtalInfo;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
extern StructAudioDigitalInfo g_stAudioD3DigtalInfo;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
extern StructAudioDigitalInfo g_stAudioD4DigtalInfo;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
extern StructAudioDigitalInfo g_stAudioD5DigtalInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerAudioDigitalAudioInitial(void);
extern void ScalerAudioDisableAudioPLL(void);
extern EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort);
extern void ScalerAudioDigitalOutputMute(bit bMute);
extern void ScalerAudioWatchDogProc(bit bOn, BYTE ucInputPort);
extern void ScalerAudioLoadStableICodeEvent(EnumScalerTimerEventID enumEventID);
extern EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void);

#if(_HDMI_SUPPORT == _ON)
#if(_D2_HDMI_SUPPORT == _ON)
extern EnumAudioSamplingFreqType ScalerAudioD2SamplingFreqDetect(void);
#endif
#endif

#if(_DP_SUPPORT == _ON)

#if(_D0_DP_EXIST == _ON)
extern void ScalerAudioD0SetAudioPLL(void);
#endif

#if(_D1_DP_EXIST == _ON)
extern void ScalerAudioD1SetAudioPLL(void);
#endif

#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
extern BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort);
#endif
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)
