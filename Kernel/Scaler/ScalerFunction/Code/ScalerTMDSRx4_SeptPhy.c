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
// ID Code      : ScalerTMDSRx4_SeptPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D4_TMDS_SUPPORT == _ON)
void ScalerTMDSRx4DviVideoSetting(void);
void ScalerTMDSRx4FirstActiveProc(BYTE ucSourceType);
void ScalerTMDSRx4PowerOffProc(void);
void ScalerTMDSRx4SetPorchColor(EnumColorSpace enumColorFormat);
BYTE ScalerTMDSRx4TMDSVideoDetect(bit bWait);
void ScalerTMDSRx4TMDSVideoDetectEvent(void);

#if(_D4_HDMI_SUPPORT == _ON)
bit ScalerTMDSRx4HdmiAviPixelRepInfoChanged(void);
BYTE ScalerTMDSRx4HdmiGetAVIInfo(EnumAviInfoContent enumContent);
BYTE ScalerTMDSRx4HdmiGetColorDepth(void);
void ScalerTMDSRx4HdmiPacketDetect(bit bWait);
void ScalerTMDSRx4HdmiPacketDetectEvent(void);
void ScalerTMDSRx4HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
bit ScalerTMDSRx4HdmiDeepColorProc(WORD usTmdsClkCnt);
bit ScalerTMDSRx4HdmiWaitDeepColorPllLock(void);
#endif

#endif

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
bit ScalerTMDSRx4TMDSNormalPreDetect(void);
bit ScalerTMDSRx4TMDSPSPreDetect(void);
#endif

#endif

void ScalerTMDSRx4HotPlugLowProc(void);
void ScalerTMDSRx4HotPlugHighProc(WORD usHpdTime);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D4_TMDS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Video Setting
// Input Value  : Source Type
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4DviVideoSetting(void)
{
    // Manual Set Color Space and disable pixel repetition
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Disable Down Sampling
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Waiting for Down Sampling Effect
    ScalerTimerDelayXms(20);

    SET_COLOR_SPACE(_COLOR_SPACE_RGB);
    SET_COLOR_RGB_QUANTIZATION_RANGE(_RGB_QUANTIZATION_FULL_RANGE);

    ScalerTMDSRx4SetPorchColor(GET_COLOR_SPACE());
}
//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4FirstActiveProc(BYTE ucSourceType)
{
    ucSourceType = ucSourceType;
}
//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4PowerOffProc(void)
{
    // Disable EDID read/ SCL toggle IRQ
    MCU_FE7B_DDC4_EDID_IRQ = ((MCU_FE7B_DDC4_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));

    ScalerTMDSRx4FreqDetectDisable();
}
//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    ScalerSetBit(P73_B9_TMDS_OUT_CTRL, ~_BIT7, 0x00);

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P73_BA_TMDS_ROUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P73_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P73_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P73_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
    else
    {
        ScalerSetByte(P73_BA_TMDS_ROUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P73_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BC_TMDS_GOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P73_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P73_BE_TMDS_BOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P73_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
}
//--------------------------------------------------
// Description  : Detect TMDS video mode
// Input Value  : bWait => Whether to wait then read
// Output Value : TMDS video type
//--------------------------------------------------
BYTE ScalerTMDSRx4TMDSVideoDetect(bit bWait)
{
    BYTE ucTemp = _TMDS_VIDEO_DATA_NONE;

    if(bWait == _WAIT)
    {
        // Wait at least 1 frame for HW auto update TMDS video RGBHV valid value
        ScalerTimerPollingFlagProc(45, P73_A4_TMDS_CTRL, _BIT3, _TRUE);

        // Wait for HW update DE flag
        if(ScalerTimerPollingFlagProc(20, P73_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // H/Vsync received
            if(ScalerGetBit(P73_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        CLR_TMDS_RX4_RGBHV_DETECTING();

        return ucTemp;
    }
    else
    {
        // R/G/B data detected
        if(ScalerGetBit(P73_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            // H/Vsync received
            if(ScalerGetBit(P73_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        // Clear video Detection Flag
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        SET_TMDS_RX4_RGBHV_DETECTING();

        // Activate TMDS video Detection Event
        ScalerTimerActiveTimerEvent(45, _SCALER_TIMER_EVENT_RX4_TMDS_VIDEO_DETECT);

        return ucTemp;
    }
}
//--------------------------------------------------
// Description  : TMDS video Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4TMDSVideoDetectEvent(void)
{
    CLR_TMDS_RX4_RGBHV_DETECTING();
}

#if(_D4_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect HDMI AVI pixel repetition
// Input Value  : None
// Output Value : _TRUE => Current Info is different from previous setting
//--------------------------------------------------
bit ScalerTMDSRx4HdmiAviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_TMDS_RX4_AVI_PIXEL_REPETITION())
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSRx4HdmiGetAVIInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x04, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x05, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x06, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x06, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x08, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:

                return ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x04, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x06, _BIT7) >> 7);

            case _AVI_INFO_PIXEL_REPETITION:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x08, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x05, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:

                return (ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x07, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

            default:

                break;
        }
    }

    return 0xFF;
}
//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : None
// Output Value : Received Color Depth
//--------------------------------------------------
BYTE ScalerTMDSRx4HdmiGetColorDepth(void)
{
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        return _COLOR_DEPTH_12_BITS;
    }

    if(GET_HDMI_RX4_GCP_RECEIVED() == _TRUE)
    {
        if(ScalerGetBit(P73_B4_TMDS_DPC0, 0x07) == 0x05)
        {
            return _COLOR_DEPTH_10_BITS;
        }
        else if(ScalerGetBit(P73_B4_TMDS_DPC0, 0x07) == 0x06)
        {
            return _COLOR_DEPTH_12_BITS;
        }
        else if(ScalerGetBit(P73_B4_TMDS_DPC0, 0x07) == 0x07)
        {
            return _COLOR_DEPTH_16_BITS;
        }
    }

    return _COLOR_DEPTH_8_BITS;
}
//--------------------------------------------------
// Description  : Detect HDMI Info Frame
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4HdmiPacketDetect(bit bWait)
{
    if(bWait == _WAIT)
    {
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P73_CC_HDMI_GPVS, (_BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // Both GCP & AVI infoframe packet have been received
            if(ScalerGetBit(P73_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
            {
                SET_HDMI_RX4_GCP_RECEIVED();

                SET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();
            }
            // Only AVI infoframe packet have been received
            else if(ScalerGetBit(P73_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT5)
            {
                SET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();

                // Polling more time to wait GCP when AVI IF has been received.
                if(ScalerTimerPollingFlagProc(180, P73_CC_HDMI_GPVS, _BIT6, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX4_GCP_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX4_GCP_RECEIVED();
                }
            }
            // Only GCP Packet have been received
            else if(ScalerGetBit(P73_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT6)
            {
                SET_HDMI_RX4_GCP_RECEIVED();

                // Polling more time to wait AVI IF when GCP has been received.
                if(ScalerTimerPollingFlagProc(180, P73_CC_HDMI_GPVS, _BIT5, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();
                }
            }
        }
        // Neither AVI infoframe nor GCP packet received
        else
        {
            CLR_HDMI_RX4_GCP_RECEIVED();

            CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_II_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
        // Polling 3 frame for detect Packet signals
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerTimerPollingDataBitFlagProc(130, P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT7, _TRUE) == _TRUE))
#else
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingDataBitFlagProc(130, P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT7, _TRUE) == _TRUE)
#endif
        {
            SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
        }
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingDataBitFlagProc(130, P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT6, _TRUE) == _TRUE)
        {
            SET_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        // Wait at least 3 frame for HW auto update color depth value
        ScalerTimerDelayXms(130);

        CLR_HDMI_RX4_PACKET_DETECTING();
    }
    else
    {
        if(ScalerGetBit(P73_CC_HDMI_GPVS, _BIT6) == _BIT6)
        {
            ScalerTMDSRx4HdmiWatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_RX4_GCP_RECEIVED();

            // Clear Detection Flag
            ScalerSetBit(P73_CC_HDMI_GPVS, ~(_BIT6 | _BIT5), _BIT6);
        }
        else
        {
            ScalerTMDSRx4HdmiWatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_RX4_GCP_RECEIVED();
        }

        if(ScalerGetBit(P73_CC_HDMI_GPVS, _BIT5) == _BIT5)
        {
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

            ScalerTMDSRx4HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();

            // Clear Detection Flag
            ScalerSetBit(P73_CC_HDMI_GPVS, ~(_BIT6 | _BIT5), _BIT5);
        }
        else
        {
            // Mannal Set Color Space and disable pixel  repetition
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerTMDSRx4HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();
        }

#if((_HDMI_FREESYNC_SUPPORT == _ON) || (_HDMI_FREESYNC_II_SUPPORT == _ON))
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_II_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT7) == _BIT7))
#else
        if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT7) == _BIT7)
#endif
        {
            SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();

            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
        {
            CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED();
        }
#endif

#if(_HDMI_HDR10_SUPPORT == _ON)
        if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, _BIT6) == _BIT6)
        {
            SET_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED();

            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT6);
        }
        else
        {
            CLR_HDMI_RX4_HDR10_INFO_FRAME_RECEIVED();
        }
#endif

        SET_HDMI_RX4_PACKET_DETECTING();

        // Activate Packet Detection Event
        ScalerTimerActiveTimerEvent(130, _SCALER_TIMER_EVENT_RX4_TMDS_HDMI_PACKET_DETECT);
    }
}
//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4HdmiPacketDetectEvent(void)
{
    CLR_HDMI_RX4_PACKET_DETECTING();
}
//--------------------------------------------------
// Description  : Hdmi Enable Watch Dog
// Input Value  : ucWDType => Watch Dog type, bEnable => Enable watch dog flag
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4HdmiWatchDog(BYTE ucWDType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD) && (GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE))
        {
            if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, _BIT0) == 0x00)
            {
                // Clear AVI Info Frame Variation flag
                ScalerSetBit(P73_CC_HDMI_GPVS, ~(_BIT6 | _BIT5 | _BIT0), _BIT0);

                // Enable Color Space/ Colorimetry Change Detection
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_45_PORT_PAGE73_HDMI_PVGCR0, ~(_BIT3 | _BIT0), (_BIT3 | _BIT0));

                // Enable AVI Info Frame Variation Watch Dog
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, ~_BIT0, _BIT0);
            }
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            if(ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, _BIT7) == 0x00)
            {
                // CLR AVMute Flag
                ScalerSetBit(P73_CB_HDMI_SR, ~_BIT7, _BIT7);

                // Enable AVMute WD
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT7, _BIT7);
            }
        }
    }
    else
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            // Disable packet variation Watch Dog
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, ~_BIT0, 0x00);

            ScalerSetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_45_PORT_PAGE73_HDMI_PVGCR0, 0x00);

            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_46_PORT_PAGE73_HDMI_PVGCR1, ~_BIT0, 0x00);
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            // Disable AV Mute Watch Dog
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_31_PORT_PAGE73_HDMI_WDCR0, ~_BIT7, 0x00);
        }
    }
}

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : HDMI Deep Color Proc
// Input Value  : void
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx4HdmiDeepColorProc(WORD usTmdsClkCnt)
{
    // Setting Deep Color PLL
    if(ScalerTMDSRx4HdmiSetDeepColorPll(usTmdsClkCnt, GET_COLOR_DEPTH()) == _FALSE)
    {
        return _FALSE;
    }

    // Wait for Phase lock
    if(ScalerTMDSRx4HdmiWaitDeepColorPllLock() == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}
//--------------------------------------------------
// Description  : Wait for Deep Color PLL Phase Lock
// Input Value  : None
// Output Value : _TRUE = > Phase Locked
//--------------------------------------------------
bit ScalerTMDSRx4HdmiWaitDeepColorPllLock(void)
{
    BYTE ucTemp = 0;

    do
    {
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // Delay for PLL Phase Lock
        ScalerTimerDelayXms(2);

        ucTemp++;
    }
    while((ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_82_PORT_PAGE73_HDMI_DPC_SET2, _BIT1) != 0) && (ucTemp <= 15));

    if(ucTemp > 15)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
//--------------------------------------------------
// Description  : Signal PreDetection for TMDS(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx4TMDSNormalPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX4_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx4("7. Normal D4 DDC", 0);

        CLR_TMDS_RX4_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE7B_DDC4_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX4_DDC_DETECTED() != _TRUE))
    {
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT3;

        CLR_TMDS_RX4_DDC_DETECTED();
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_RX4_PHY_SET() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx4TMDSPSPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX4_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx4("7. PowerSaving D4 DDC", 0);

        CLR_TMDS_RX4_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX4_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE7B_DDC4_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX4_DDC_DETECTED() != _TRUE))
    {
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P73_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P73_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX4_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}
#endif

#endif

//--------------------------------------------------
// Description  : HPD Low Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx4HotPlugLowProc(void)
{
    // MHL mode of MHL PORT can not pull HPD
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D4_CABLE_STATUS() == _TRUE) && (GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D4_CABLE_STATUS() == _TRUE))
#endif
    {
        PCB_D4_HOTPLUG(_D4_HOT_PLUG_LOW);

        ScalerTMDSRx4SwitchSlaveAddr();
    }
}

//--------------------------------------------------
// Description  : HPD High Process
// Input Value  : usHpdTime
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx4HotPlugHighProc(WORD usHpdTime)
{
    // MHL mode of MHL PORT can not pull HPD
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D4_CABLE_STATUS() == _TRUE) && (GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D4_CABLE_STATUS() == _TRUE))
#endif
    {
        ScalerTimerDelayXms(usHpdTime);

        PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
    }
}
#endif
