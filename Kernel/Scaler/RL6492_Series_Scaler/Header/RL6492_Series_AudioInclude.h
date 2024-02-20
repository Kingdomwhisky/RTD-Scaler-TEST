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
// ID Code      : RL6492_Series_AudioInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Definition of VCO Frequency of Audio PLL With Frequency Up
//----------------------------------------------------------------------------
#define _AUDIO_PLL_VCO                              378000 // 1KHz,

//----------------------------------------------------------------------------
// Definition of Offset of Audio PLL With Path1 and Frequency Up
//----------------------------------------------------------------------------
#define _HDMI_SAMPLING_FREQ_32K_GROUP_D_CODE        0xD847
#define _HDMI_SAMPLING_FREQ_44K_GROUP_D_CODE        0x2CC8
#define _HDMI_SAMPLING_FREQ_48K_GROUP_D_CODE        0xD847

#define _DP_SAMPLING_FREQ_32K_GROUP_D_CODE          0x29E0
#define _DP_SAMPLING_FREQ_44K_GROUP_D_CODE          0xD334
#define _DP_SAMPLING_FREQ_48K_GROUP_D_CODE          0x29E0

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

#define GET_AUDIO_CURRENT_MAC_TYPE()                (g_stAudioD0DigtalInfo.b1AudioCurrentMAC)
#define SET_AUDIO_CURRENT_MAC_TYPE(x)               (g_stAudioD0DigtalInfo.b1AudioCurrentMAC = (x))

#define SET_AUDIO_PLL_SOURCE_MUX()                  {\
                                                        ScalerSetBit(P2_AB_TMDS_ACC2, ~_BIT0, ((GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE) ? _BIT0 : 0x00));\
                                                        if(ScalerGetBit(P2_AB_TMDS_ACC2, _BIT0) == _BIT0)\
                                                        {\
                                                            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_10_PORT_PAGE2_HDMI_CMCR, ~_BIT4, _BIT4);\
                                                        }\
                                                        else\
                                                        {\
                                                            if(ScalerGetBit(PB6_74_AUD_FSM_CTRL_0, _BIT7) == _BIT7)\
                                                            {\
                                                                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, 0x00);\
                                                                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, _BIT7);\
                                                            }\
                                                        }\
                                                    }

#define SET_AUDIO_HDMI_TRACKING_BOUNDARY_DISTANCE() {\
                                                        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_1B_PORT_PAGE2_HDMI_FBR, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));\
                                                        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_A0_PORT_PAGE2_HDMI_AFIFO_SET, ~_BIT6, 0x00);\
                                                    }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructAudioDigitalInfo g_stAudioD0DigtalInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort);
extern void ScalerAudioWatchDogProc(bit bOn, BYTE ucInputPort);
extern EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void);

#if(_DP_SUPPORT == _ON)
extern void ScalerAudioDPDigitalOutputProc(bit bEnable, BYTE ucInputPort);
extern void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort);
extern void ScalerAudioDpAudioEnable_EXINT0(bit bEnable, BYTE ucInputPort);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
extern BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort);
#endif
#endif

#endif // End of #if(_AUDIO_SUPPORT == _ON)
