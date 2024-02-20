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
// ID Code      : RL6492_Series_Audio.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_AUDIO_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructAudioDigitalInfo g_stAudioD0DigtalInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerAudioGetAudioDetected(BYTE ucInputPort);
EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort);
bit ScalerAudioLPCMCheckData(BYTE ucInputPort);
void ScalerAudioWatchDogProc(bit bOn, BYTE ucInputPort);
EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void);

#if(_HDMI_SUPPORT == _ON)
bit ScalerAudioLPCMCheckInfo(BYTE ucInputPort);
#endif

#if(_DP_SUPPORT == _ON)
void ScalerAudioDPDigitalOutputProc(bit bEnable, BYTE ucInputPort);
bit ScalerAudioDPGetMuteProc(BYTE ucInputPort);
void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort);
void ScalerAudioDpAudioEnable_EXINT0(bit bEnable, BYTE ucInputPort);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort);
bit ScalerAudioGetDpStandaloneAudioStatus(BYTE ucInputPort);
#endif
#endif

#if(_LINE_IN_SUPPORT == _ON)
void ScalerAudioADCInitial(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
void ScalerAudioInternalAudioGenSwitch(bit bOn, BYTE ucInputPort);
bit ScalerAudioGetInternalAudioGenEnable(BYTE ucInputPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Audio Detected
// Input Value  : None
// Output Value : TRUE => Audio Detected
//--------------------------------------------------
bit ScalerAudioGetAudioDetected(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerAudioD0GetAudioDetected();

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Detect Audio Sampling Freq
// Input Value  : ucInputPort
// Output Value : Audio Sampling Freq
//--------------------------------------------------
EnumAudioSamplingFreqPacket ScalerAudioSamplingFreqDetect(BYTE ucInputPort)
{
    EnumAudioSamplingFreqType enumSamplingFreqType = _AUDIO_FREQ_NO_AUDIO;

    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            enumSamplingFreqType = ScalerAudioD0SamplingFreqDetect();

            break;

        default:
            break;
    }

    return ScalerAudioGetSamplingFreqPacket(enumSamplingFreqType);
}

//--------------------------------------------------
// Description  : Check Audio whether Audio LPCM By Audio Data
// Input Value  : ucSourceType
// Output Value : _TRUE => LPCM
//--------------------------------------------------
bit ScalerAudioLPCMCheckData(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
            {
                if(ScalerGetBit(P2_CB_HDMI_SR, _BIT4) == 0x00)
                {
                    return _TRUE;
                }
            }
            else
            {
                pData[0] = ScalerGetByte(PB6_B0_DP_AUD_CTRL);

                if((((pData[0] & _BIT5) == 0x00) && ((pData[0] & _BIT4) == _BIT4)) ||
                   (((pData[0] & _BIT5) == _BIT5) && ((pData[0] & _BIT4) == 0x00)))
                {
                    return _TRUE;
                }
            }

            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Audio Watch Dog Proc
// Input Value  : bOn
// Output Value : None
//--------------------------------------------------
void ScalerAudioWatchDogProc(bit bOn, BYTE ucInputPort)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) != _AUDIO_FROM_ADC_PORT)
#endif
    {
        switch(ucInputPort)
        {
            case _D0_INPUT_PORT:
            case _D1_INPUT_PORT:
            case _D2_INPUT_PORT:

                ScalerAudioD0WatchDogProc(bOn);
                DebugMessageAudio("Audio D0: WatchDog", bOn);

                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Get Current Audio Port
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
EnumSourceSearchPort ScalerAudioGetDigitalAudioPortMapping(void)
{
    switch(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT))
    {
        case _AUDIO_FROM_D0_PORT:

            return _D0_INPUT_PORT;

        case _AUDIO_FROM_D1_PORT:

            return _D1_INPUT_PORT;

        case _AUDIO_FROM_D2_PORT:

            return _D2_INPUT_PORT;

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Audio whether Audio LPCM By Info Frame
// Input Value  : ucSourceType
// Output Value : _TRUE => LPCM
//--------------------------------------------------
bit ScalerAudioLPCMCheckInfo(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            ScalerGetDataPortByte(P2_CD_HDMI_PSAP, 0x15, 1, pData, _NON_AUTOINC);

            if(((pData[0] & 0xF0) == 0x00) || ((pData[0] & 0xF0) == 0x10))
            {
                return _TRUE;
            }

            break;

        default:
            break;
    }

    return _FALSE;
}
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Audio Digital Output Process
// Input Value  : Enable and Input port
// Output Value : None
//--------------------------------------------------
void ScalerAudioDPDigitalOutputProc(bit bEnable, BYTE ucInputPort)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) != _AUDIO_FROM_ADC_PORT)
#endif
    {
        switch(ucInputPort)
        {
            case _D0_INPUT_PORT:
            case _D1_INPUT_PORT:
            case _D2_INPUT_PORT:

                ScalerAudioD0DPDigitalOutputProc(bEnable);
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Check if Mute Audio
// Input Value  : ucInputPort
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerAudioDPGetMuteProc(BYTE ucInputPort)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) == _AUDIO_FROM_ADC_PORT)
    {
        return _FALSE;
    }
#endif

    if(GET_REG_D0_MAC_SWITCH_TO_HDMI() == _TRUE)
    {
        return _FALSE;
    }

    switch(ucInputPort)
    {
#if(_D0_DP_EXIST == _ON)
        case _D0_INPUT_PORT:

            if(GET_REG_DP_RX0_MAC_ASSIGNED() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

#if(_D1_DP_EXIST == _ON)
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            if(GET_REG_DP_RX1_MAC_ASSIGNED() == _TRUE)
            {
                return _TRUE;
            }

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Enable DP audio FSM
// Input Value  : Enable or Disable, Input Port
// Output Value : None
//--------------------------------------------------
void ScalerAudioDpAudioEnable(bit bEnable, BYTE ucInputPort)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetDigitalAudioPort(_AUDIO_DAC_OUT) != _AUDIO_FROM_ADC_PORT)
#endif
    {
        switch(ucInputPort)
        {
            case _D0_INPUT_PORT:
            case _D1_INPUT_PORT:
            case _D2_INPUT_PORT:

                ScalerSetBit(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, ((BYTE)bEnable) << 7);
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Enable DP audio FSM
// Input Value  : Enable or Disable, Input Port
// Output Value : None
//--------------------------------------------------
void ScalerAudioDpAudioEnable_EXINT0(bit bEnable, BYTE ucInputPort) using 1
{
#if(_LINE_IN_SUPPORT == _ON)
    if(ScalerAudioGetDigitalAudioPort_EXINT0(_AUDIO_DAC_OUT) != _AUDIO_FROM_ADC_PORT)
#endif
    {
        switch(ucInputPort)
        {
            case _D0_INPUT_PORT:
            case _D1_INPUT_PORT:
            case _D2_INPUT_PORT:

                ScalerSetBit_EXINT(PB6_74_AUD_FSM_CTRL_0, ~_BIT7, ((BYTE)bEnable) << 7);
                break;

            default:
                break;
        }
    }
}
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
//--------------------------------------------------
// Description  : Get Current Digital Audio Source
// Input Value  : None
// Output Value : Digital Audio Source
//--------------------------------------------------
BYTE ScalerAudioGetDigitalAudioSource(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return GET_D0_DIGITAL_AUDIO_SOURCE();

        default:
            break;
    }

    return _DIGITAL_AUDIO_SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Get Dp audio Status for Sleep Audio
// Input Value  : Input Port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerAudioGetDpStandaloneAudioStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ((GET_REG_D0_MAC_SWITCH_TO_HDMI() == _FALSE) ? _TRUE : _FALSE);

        default:
            break;
    }

    return _FALSE;
}
#endif
#endif

#if(_LINE_IN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Audio ADC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerAudioADCInitial(void)
{
    // Enable ADDA Loop, High Pass Filter and Set ADC ZCD Type
    ScalerSetBit(P6_B4_AD_CTRL, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT6 | _BIT3));

    // Power On ADC
    ScalerSetBit(P6_B0_REG_ADC_POWER, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Power On Mbias
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
    // Power On Input Buffer
    ScalerSetBit(P6_C0_REG_DAC_POWER0, ~_BIT2, _BIT2);
#endif

    // Adj ADC OP Noise Cancellation Clock and Enable ADC Op Offset Cancellation
    ScalerSetBit(P6_B2_REG_ADC_CTRL, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));

    // Set ADC Front End Gain(-5dB)
    ScalerSetByte(P6_B3_REG_AFE_GAIN, 0x77);

    // Bypass Input Buffer
    ScalerSetBit(P6_B0_REG_ADC_POWER, ~_BIT0, _BIT0);

    // ADC Unmute and Set Boost Gain
    ScalerSetByte(P6_B5_AD_MUTE, 0x00);

    // Set AD Gail of L Ch
    ScalerSetBit(P6_B6_AD_GAIN_L, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_BOOST_GAIN_DB);

    // Set AD Gail of R Ch
    ScalerSetBit(P6_B7_AD_GAIN_R, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _LINE_IN_BOOST_GAIN_DB);

    // Set Double Buffer
    ScalerSetBit(P6_B6_AD_GAIN_L, ~_BIT7, _BIT7);

    // Set Sampling Frequency "48kHz" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E2_AD_SPDIF_CS_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _AUDIO_SPDIF_FS_48KHZ);

    // Set Channel Count "2 ch" For S/PDIF Output From ADC In
    ScalerSetBit(P6_E3_AD_SPDIF_CS_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Enable I2S Output for ADC In and Swap LR channel for I2S
    ScalerSetBit(P6_E7_AD_I2S_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
}
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Auido Speaker Testing Process
// Input Value  : Enable or Disable
// Output Value : None
//--------------------------------------------------
void ScalerAudioInternalAudioGenSwitch(bit bOn, BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            ScalerAudioD0InternalAudioGenSwitch(bOn);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Whether Internal Audio Pattern Gen is Enabled
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerAudioGetInternalAudioGenEnable(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
        case _D1_INPUT_PORT:
        case _D2_INPUT_PORT:

            return ScalerAudioD0GetInternalAudioGenEnable();

        default:
            break;
    }

    return _DISABLE;
}
#endif // End of #if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
#endif // End of #if(_AUDIO_SUPPORT == _ON)

