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
// ID Code      : SysSource.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_SOURCE__

#include "SysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Macro of Getting Input Port Type
//--------------------------------------------------
#define GET_INPUTPORT_TYPE(x)           (tINPUT_PORT_TYPE[g_pucSourceSearchPriority[x]])

//--------------------------------------------------
// Macro of Getting Input Port Group Type
//--------------------------------------------------
#define GET_INPUTPORT_GROUP(x)          (g_pucSourceSearchGroup[g_pucSourceSearchPriority[x]])


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tINPUT_PORT_TYPE[] =
{
    _A0_INPUT_PORT_TYPE,
    _A1_INPUT_PORT_TYPE,
    _A2_INPUT_PORT_TYPE,
    _D0_INPUT_PORT_TYPE,
    _D1_INPUT_PORT_TYPE,
    _D2_INPUT_PORT_TYPE,
    _D3_INPUT_PORT_TYPE,
    _D4_INPUT_PORT_TYPE,
    _D5_INPUT_PORT_TYPE,
    _D6_INPUT_PORT_TYPE,
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSourceInfoType g_pstSourceInfo[_INPUT_PORT_VALID];
StructSourceInfoType g_stSourceInfoBackup;
// SourceInfo bit[0:2] -- Source Type
//#define _SOURCE_NONE                      0
//#define _SOURCE_VGA                       1
//#define _SOURCE_DVI                       2
//#define _SOURCE_HDMI                      3
//#define _SOURCE_DP                        4
//#define _SOURCE_MHL                       5
//#define _SOURCE_HDMI20                    6
//                                        = 000 => no Source
//                                        = 001 => VGA Source
//                                        = 010 => DVI Source
//                                        = 011 => HDMI Source
//                                        = 100 => DP Source
//                                        = 101 => Video Source
//                                        = 110 => HDMI 2.0 Source
//                                        = 111 => Dual DVI

// SourceInfo bit[3:4] -- Source Search Times
//                                     = 0~3 => Counter

// SourceInfo bit[5] -- Cable detect
//            = 0 => No
//            = 1 => Yes

// SourceInfo bit[7] -- Source Chosen
//                                      = 0 => Unchosen
//                                      = 1 => Chosen

BYTE g_ucSearchIndex;

StructInputInfoType g_stInputInfo;

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
StructSourceInfoType g_pstBgSourceInfo[_INPUT_PORT_VALID];
BYTE g_ucBgDetectIndex;
#endif

BYTE g_pucSourceSearchPriority[10] =
{
    _INPUT_PORT_SEARCH_PRI_0, _INPUT_PORT_SEARCH_PRI_1,
    _INPUT_PORT_SEARCH_PRI_2, _INPUT_PORT_SEARCH_PRI_3,
    _INPUT_PORT_SEARCH_PRI_4, _INPUT_PORT_SEARCH_PRI_5,
    _INPUT_PORT_SEARCH_PRI_6, _INPUT_PORT_SEARCH_PRI_7,
    _INPUT_PORT_SEARCH_PRI_8, _INPUT_PORT_SEARCH_PRI_9
};

BYTE g_pucSourceSearchGroup[10] =
{
    _A0_INPUT_PORT_GROUP, _A1_INPUT_PORT_GROUP,
    _A2_INPUT_PORT_GROUP, _D0_INPUT_PORT_GROUP,
    _D1_INPUT_PORT_GROUP, _D2_INPUT_PORT_GROUP,
    _D3_INPUT_PORT_GROUP, _D4_INPUT_PORT_GROUP,
    _D5_INPUT_PORT_GROUP, _D6_INPUT_PORT_GROUP
};

#if(_VGA_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeVga;
WORD g_usSourceNoCableSearchTimeVga;
#endif

#if(_HDMI_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeHdmi;
WORD g_usSourceNoCableSearchTimeHdmi;
#endif

#if(_DVI_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeDvi;
WORD g_usSourceNoCableSearchTimeDvi;
#endif

#if(_DP_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeDp;
WORD g_usSourceNoCableSearchTimeDp;

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
WORD g_usSourceDefaultSearchTimeTypeC;
WORD g_usSourceNoCableSearchTimeTypeC;
#endif
#endif

StructPortCableStatus g_stPortCableStatus;

#if(_DP_SUPPORT == _ON)
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
BYTE g_ucD6SwitchSelect = _NO_INPUT_PORT;
bit g_bD6SwitchPowerStatus = _DISABLE;
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE != _DP_EMBEDDED_SWITCH_NONE)
BYTE g_ucDpEmbeddedSwitchSelect = _NO_INPUT_PORT;
BYTE g_ucDpEmbeddedSwitchTarget = _NO_INPUT_PORT;
bit g_bDpEmbeddedSwitchEvent = _DISABLE;
#endif

bit g_bDpAutoSearchSwitch = _DISABLE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysSourceHandler(void);
void SysSourceDetectPort(BYTE ucSearchIndex);
void SysSourceClearDetectingEvent(void);
bit SysSourceKeepDetectingCheck(void);
void SysSourceSearchTimeInitial(BYTE ucSearchIndex);
void SysSourceJudge(void);
void SysSourceSwitchPort(void);
void SysSourceScanPortInitial(BYTE ucSearchIndex);
void SysSourceInitial(void);
bit SysSourceStableCheck(void);
BYTE SysSourceGetSourceType(void);
BYTE SysSourceGetInputPort(void);
BYTE SysSourceGetSpecificInputPort(BYTE ucIndex);
BYTE SysSourceGetInputPortType(BYTE ucInputPort);
BYTE SysSourceGetJudge(BYTE ucInputPort);
bit SysSourceGetPreDetect(BYTE ucInputPort);

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
BYTE SysSourceGetAudioPlaybackPort(void);
#endif

void SysSourceSwitchInputPort(BYTE ucInputPort);
void SysSourceInfoReset(void);
void SysSourceCableDetection(void);

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
void SysSourceHdmi5VDetection(void);
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
bit SysSourceCheckEmbeddedDpAutoSwitch(void);
void SysSourceEmbeddedDpSwitch(EnumSourceSearchPort enumDpPort);
#endif

bit SysSourceCheckTargetTimes(BYTE ucTargetTimes);
void SysSourceSetScanType(BYTE ucScanType);
BYTE SysSourceGetScanType(void);
BYTE SysSourceConvertSearchPort(BYTE ucInputPort);
bit SysSourceGetCableDetect(BYTE ucInputPort);
bit SysSourceGetCableStatusChange(BYTE ucInputPort);
void SysSourceCableResetProc(void);
void SysSourceFirstActiveProc(void);
void SysSourcePowerOffProc(void);
void SysSourceSetSearchPriority(EnumSourceSearchPort enumPort, EnumSourceSearchPortPriority enumSourcePriority);
void SysSourceSetSearchGroup(EnumSourceSearchPort enumPort, EnumSourceSearchGroup enumSourceGroup);
void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime);
void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime);

#if(_USB3_RETIMER_SUPPORT == _ON)
EnumTypeCCableStatus SysSourceGetTypeCCableStatusChange(void);
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
void SysSourceEizoSetPowerSavingSupport(bit bOn);
bit SysSourceGetSourceSwitchFinish(void);
void SysSourceEizoReactiveTotalSearchTime(WORD usTime);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
bit SysSourceHpGetSourceJudge(void);
BYTE SysSourceHpGetTargetSourceType(BYTE ucSearchIndex);
BYTE SysSourceHpGetTargetSearchTimes(void);
bit SysSourceHpGetSwitchPortNoCable(void);
bit SysSourceHpGetTargetPortNoSignal(void);
bit SysSourceHpGetMonitorStatusCheckProcessing(void);
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
void SysSourceBgSwitchPort(void);
void SysSourceBgJudge(void);
BYTE SysSourceBgGetInputPort(void);
bit SysSourceBgGetJudge(void);
#endif

#if(_SIGNAL_GPIO_DETECT == _ON)
void SysSourceDetectGPIO(void);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Source Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHandler(void)
{
    SysSourceCableDetection();

#if(_SIGNAL_GPIO_DETECT == _ON)
    SysSourceDetectGPIO();
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE) &&
       (GET_POWER_STATUS() == _POWER_STATUS_NORMAL))
    {
        return;
    }
#endif

    if((GET_MODE_STATE() != _MODE_STATUS_POWER_OFF) && (GET_MODE_STATE() != _MODE_STATUS_INITIAL) && (UserInterfaceGetForcePSStatus() == _FALSE))
    {
        if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE)
        {
            if(GET_SOURCE_DETECTING() == _FALSE)
            {
                SysSourceSwitchPort();
            }

            if(GET_SOURCE_SEARCH_PORT_INITIAL() == _TRUE)
            {
                SysSourceScanPortInitial(g_ucSearchIndex);

                CLR_SOURCE_SEARCH_PORT_INITIAL();
            }

            if(GET_SOURCE_SEARCH_TIME_INITIAL() == _TRUE)
            {
                SysSourceSearchTimeInitial(g_ucSearchIndex);

                CLR_SOURCE_SEARCH_TIME_INITIAL();
            }

            // Port Detection
            SysSourceDetectPort(g_ucSearchIndex);

            // Decide if this port is about to be chosen
            SysSourceJudge();
        }

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
        else if((GET_SOURCE_BG_JUDGE(g_ucBgDetectIndex) == _FALSE) &&
                (g_ucSearchIndex > 0) &&
                (GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT))
        {
            if(GET_SOURCE_DETECTING() == _FALSE)
            {
                SysSourceBgSwitchPort();
            }

            if(GET_SOURCE_SEARCH_PORT_INITIAL() == _TRUE)
            {
                SysSourceScanPortInitial(g_ucBgDetectIndex);

                CLR_SOURCE_SEARCH_PORT_INITIAL();
            }

            if(GET_SOURCE_SEARCH_TIME_INITIAL() == _TRUE)
            {
                SysSourceSearchTimeInitial(g_ucBgDetectIndex);

                CLR_SOURCE_SEARCH_TIME_INITIAL();
            }

            // Port Detection
            SysSourceDetectPort(g_ucBgDetectIndex);

            // Decide if this port is about to be chosen
            SysSourceBgJudge();
        }
#endif
    }

    CLR_MODE_STATE_CHANGE_SOURCE();
}
//--------------------------------------------------
// Description  : Source GPIO Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if(_SIGNAL_GPIO_DETECT == _ON)
void SysSourceDetectGPIO(void)
{
    BYTE ucSearchIndex = 0;
    ucSearchIndex = GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex));//GET_INPUT_PORT(g_ucSearchIndex);
    if((GET_MODE_STATE() != _MODE_STATUS_POWER_OFF) && (GET_MODE_STATE() != _MODE_STATUS_INITIAL) && (UserInterfaceGetForcePowSavStatus() == _FALSE))
    {
        if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE)
        {
            DebugMessageSystem("ucSearchIndex = ", ucSearchIndex);
            if((bH_Select == 1) && (bP_Select ==0))
            {
                DebugMessageSystem("bH_Select == 1,bP_Select ==0", 0);
                ucSearchIndex = _D3_INPUT_PORT;
            }
            if((bH_Select == 0) && (bP_Select ==1))
            {
                DebugMessageSystem("bH_Select == 0,bP_Select ==1", 0);
                ucSearchIndex = _D1_INPUT_PORT;
            }
            if((bH_Select == 1) && (bP_Select ==1))
            {
                DebugMessageSystem("bH_Select == 1,bP_Select ==1", 0);
                ucSearchIndex = UserCommonNVRamGetSystemData(_SEARCH_PORT);
            }
            if((bH_Select == 0) && (bP_Select ==0))
            {
                DebugMessageSystem("bH_Select == 0,bP_Select ==0", 0);
            }
            if(SysSourceConvertSearchPort(ucSearchIndex) != g_ucSearchIndex)
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                CLR_SOURCE_DETECTING();
                UserInterfaceSetForcePowSavStatus(_FALSE);
            }
        }
    }

}
#endif

//--------------------------------------------------
// Description  : Port Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceDetectPort(BYTE ucSearchIndex)
{
    BYTE ucSourceType = _SOURCE_NONE;
    EnumSourceSearchPort enumSearchPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex));

    switch(GET_SOURCE_SCAN_TYPE())
    {
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SOURCE_SWITCH:
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            if(GET_SOURCE_HP_SWITCH_NO_CABLE() == _TRUE)
            {
                return;
            }

            break;
#endif
        default:

            break;
    }

    SET_SOURCE_TYPE(ucSearchIndex, _SOURCE_NONE);

    switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex)))
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:

            if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerSyncProcPreDetect(enumSearchPort));
            }
            else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerSyncProcPreDetect(enumSearchPort));
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE))
                {
                    SET_SOURCE_TYPE(ucSearchIndex, SysVgaScanInputPort(enumSearchPort));
                }
            }

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _PORT_DVI:
        case _PORT_HDMI:

            if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerTMDSPSPreDetect(enumSearchPort));
            }
            else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerTMDSNormalPreDetect(enumSearchPort));
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE))
                {
                #if(_CUSTOMER == _CUS_MINDRAY)
                    ucSourceType = ScalerTMDSScanInputPort(enumSearchPort, GET_INPUTPORT_TYPE(ucSearchIndex));
                    if(ucSourceType != _SOURCE_NONE)
                    {
                        if(ScalerMeasureInputInfo(SysSourceGetSourceType(), SysSourceGetInputPort()) == _FALSE)
                        {
                            DebugMessageSystem("TMDS Measure Fail", 0);
                            ucSourceType = _SOURCE_NONE;
                        }
                    }
                    SET_SOURCE_TYPE(ucSearchIndex, ucSourceType);
                #else
                    SET_SOURCE_TYPE(ucSearchIndex, ScalerTMDSScanInputPort(enumSearchPort, GET_INPUTPORT_TYPE(ucSearchIndex)));
                #endif
                }
            }

            break;
#endif

#if(_MHL_SUPPORT == _ON)

        case _PORT_MHL:

            if(((enumSearchPort == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)) ||
               ((enumSearchPort == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)) ||
               ((enumSearchPort == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)) ||
               ((enumSearchPort == _D3_INPUT_PORT) && (GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)) ||
               ((enumSearchPort == _D4_INPUT_PORT) && (GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)) ||
               ((enumSearchPort == _D5_INPUT_PORT) && (GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)))
            {
                if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                {
                    SET_SOURCE_PREDETECT(ucSearchIndex, ScalerTMDSPSPreDetect(enumSearchPort));
                }
                else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                {
                    SET_SOURCE_PREDETECT(ucSearchIndex, ScalerTMDSNormalPreDetect(enumSearchPort));
                }

                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE))
                    {
                        SET_SOURCE_TYPE(ucSearchIndex, ScalerTMDSScanInputPort(enumSearchPort, GET_INPUTPORT_TYPE(ucSearchIndex)));
                    }
                }
            }

            else if(((enumSearchPort == _D0_INPUT_PORT) && (GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)) ||
                    ((enumSearchPort == _D1_INPUT_PORT) && (GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)) ||
                    ((enumSearchPort == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)) ||
                    ((enumSearchPort == _D3_INPUT_PORT) && (GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)) ||
                    ((enumSearchPort == _D4_INPUT_PORT) && (GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)) ||
                    ((enumSearchPort == _D5_INPUT_PORT) && (GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)))
            {
                if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                {
                    SET_SOURCE_PREDETECT(ucSearchIndex, ScalerMHLPSPreDetect(enumSearchPort));
                }
                else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                {
                    SET_SOURCE_PREDETECT(ucSearchIndex, ScalerMHLNormalPreDetect(enumSearchPort));
                }

                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE))
                    {
                        SET_SOURCE_TYPE(ucSearchIndex, ScalerTMDSScanInputPort(enumSearchPort, GET_INPUTPORT_TYPE(ucSearchIndex)));
                    }
                }
            }

            break;
#endif

#if(_DUAL_DVI_SUPPORT == _ON)

        case _PORT_DUAL_DVI:

            if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerDualLinkDVIPSPreDetect(enumSearchPort));
            }
            else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerDualLinkDVINormalPreDetect(enumSearchPort));
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE))
                {
                    SET_SOURCE_TYPE(ucSearchIndex, ScalerDualLinkDVIScanInputPort(enumSearchPort));
                }
            }

            break;

#endif

#if(_DP_SUPPORT == _ON)

        case _PORT_DP:

            if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerDpPSPreDetect(enumSearchPort));
            }
            else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                SET_SOURCE_PREDETECT(ucSearchIndex, ScalerDpNormalPreDetect(enumSearchPort));
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(ucSearchIndex) == _TRUE))
                {
                    SET_SOURCE_TYPE(ucSearchIndex, ScalerDpScanInputPort(enumSearchPort));
                }
            }

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Event to clear detection and finish flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceClearDetectingEvent(void)
{
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    // For some of HP scan type, the first loop of source search for checking monitor status needs to be done completely
    if(SysSourceHpGetMonitorStatusCheckProcessing() == _FALSE)
#endif
    {
        if(SysSourceKeepDetectingCheck() == _TRUE)
        {
            if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
            {
                SET_SOURCE_SWITCH_FINISH();
            }

            ScalerTimerActiveTimerEvent(SEC(0), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

            return;
        }
    }

    CLR_SOURCE_DETECTING();

#if((_HP_SOURCE_SCAN_SUPPORT == _ON) && (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
    CLR_SOURCE_HP_DETECTING();
#endif
}

//--------------------------------------------------
// Description  : Check Source Keep Detecting or Not
// Input Value  : None
// Output Value : _TRUE: keep detecting, _FALSE: stop detecting
//--------------------------------------------------
bit SysSourceKeepDetectingCheck(void)
{
    switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
    {
#if(_DP_SUPPORT == _ON)
        case  _PORT_DP:
            return SysDpSourceKeepDetectingCheck();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Decide how much time will be spent on the first port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSearchTimeInitial(BYTE ucSearchIndex)
{
    SET_SOURCE_DETECTING();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)

    UserInterfaceAdjustSourceSearchTime();

    if(GET_SOURCE_EIZO_INFO_RESET() == _TRUE)
    {
        ScalerTimerReactiveTimerEvent(UserInterfaceGetEizoSearchFinishTime(), _SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
        CLR_SOURCE_EIZO_INFO_RESET();
    }
#endif

    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
    {
        ScalerTimerReactiveTimerEvent(SEC(0), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
    else if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE)
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

        ScalerTimerReactiveTimerEvent(_SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }
#endif

    else if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

        switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex)))
        {
            case _PORT_VGA:

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_VGA));
#else
                ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif

                break;

            case _PORT_DVI:
            case _PORT_HDMI:
            case _PORT_DUAL_DVI:

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_TMDS));
#else
                ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif

                break;

            case _PORT_MHL:

                switch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex)))
                {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

                    case _D0_INPUT_PORT:

                        if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_MHL));
#else
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }
                        else
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_TMDS));
#else
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }

                        break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

                    case _D1_INPUT_PORT:

                        if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_MHL));
#else
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }
                        else
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_TMDS));
#else
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }

                        break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

                    case _D2_INPUT_PORT:

                        if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_MHL));
#else
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }
                        else
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_TMDS));
#else
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }

                        break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

                    case _D3_INPUT_PORT:

                        if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_MHL));
#else
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }
                        else
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_TMDS));
#else
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }

                        break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

                    case _D4_INPUT_PORT:

                        if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_MHL));
#else
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }
                        else
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_TMDS));
#else
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }

                        break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

                    case _D5_INPUT_PORT:

                        if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_MHL));
#else
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }
                        else
                        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                            SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_TMDS));
#else
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#endif
                        }

                        break;
#endif

                    default:
                        break;
                }

                break;

            case _PORT_DP:

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                SysSourceEizoReactiveTotalSearchTime(UserInterfaceAdjustSourceReactiveSearchTime(_ADJUST_PORT_DP));
#else

#if((_HP_SOURCE_SCAN_SUPPORT == _ON) && (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
                if(GET_SOURCE_HP_DETECTING() == _FALSE)
#endif
                {
#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
                    if(SysDpCheckTwoChipDataExchangePort(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex))) == _TRUE)
                    {
                        ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                    }
                    else
#elif(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                    if(SysTypeCCheckTypeCPortControllerExist(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex))) == _TRUE)
                    {
                        ScalerTimerReactiveTimerEvent(SEC(5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                    }
                    else
#endif
                    {
                        ScalerTimerReactiveTimerEvent(SEC(4), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                    }
                }
#endif

                break;

            default:
                break;
        }
    }
    else
    {
        switch(GET_SOURCE_SCAN_TYPE())
        {
            case _SOURCE_SWITCH_FIXED_PORT:
            case _SOURCE_SWITCH_AUTO_IN_GROUP:
            case _SOURCE_SWITCH_AUTO_WITHOUT_GROUP:
            case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
            case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                ScalerTimerReactiveTimerEvent(_SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
#else
                switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex)))
                {
#if(_VGA_PORT_EXIST == _ON)
                    case _PORT_VGA:

                        if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeVga, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeVga, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
                    case _PORT_HDMI:
                    case _PORT_MHL:

                        if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeHdmi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeHdmi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_DVI_PORT_EXIST == _ON)
                    case _PORT_DVI:
                    case _PORT_DUAL_DVI:

                        if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDvi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeDvi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_DP_PORT_EXIST == _ON)
                    case _PORT_DP:

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
                        if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_FIXED_PORT)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(UserInterfaceGetHpSourceSwitchOsdEventTime(_SOURCE_SWITCH_FIXED_PORT)), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
                            SET_SOURCE_HP_DETECTING();
#endif
                        }
                        else
#endif
                        {
                            if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                            {
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                                if(SysTypeCCheckTypeCPortControllerExist(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex))) == _TRUE)
                                {
                                    ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeTypeC, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                                }
                                else
#endif
                                {
                                    ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDp, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                                }
                            }
                            else
                            {
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                                if(SysTypeCCheckTypeCPortControllerExist(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex))) == _TRUE)
                                {
                                    ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeTypeC, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                                }
                                else
#endif
                                {
                                    ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeDp, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                                }
                            }
                        }

                        break;
#endif

                    default:
                        break;
                }
#endif // End of #if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

            case _SOURCE_SWITCH_HP_TIMING_CHANGE:

#if(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_F)

                if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
                {
                    ScalerTimerReactiveTimerEvent(SEC(10), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                    SET_SOURCE_HP_PORT_SWITCH_TARGET(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT)));
                }
                else
                {
                    ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                }
#else
                if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
                {
                    ScalerTimerReactiveTimerEvent(SEC(5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                }
                else
                {
                    ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                }
#endif

                break;

            case _SOURCE_SWITCH_HP_SOURCE_SCAN:
            case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:
            case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:

                switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex)))
                {
#if(_VGA_PORT_EXIST == _ON)
                    case _PORT_VGA:

                        if(GET_SOURCE_HP_FROM_TIMING_CHANGE() == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeVga, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else if(GET_SOURCE_SEARCH_TIMES(ucSearchIndex) == 0x00)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
                    case _PORT_HDMI:
                    case _PORT_MHL:

                        if((ucSearchIndex == SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) &&
                           (GET_SOURCE_HP_FROM_TIMING_CHANGE() == _TRUE))
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeHdmi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else if(GET_SOURCE_SEARCH_TIMES(ucSearchIndex) == 0x00)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_DVI_PORT_EXIST == _ON)
                    case _PORT_DVI:
                    case _PORT_DUAL_DVI:

                        if(GET_SOURCE_HP_FROM_TIMING_CHANGE() == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDvi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else if(GET_SOURCE_SEARCH_TIMES(ucSearchIndex) == 0x00)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_DP_PORT_EXIST == _ON)
                    case _PORT_DP:

                        if(GET_SOURCE_HP_FROM_TIMING_CHANGE() == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else if(GET_CABLE_DETECT(ucSearchIndex) == _TRUE)
                        {
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                            if(SysTypeCCheckTypeCPortControllerExist(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex))) == _TRUE)
                            {
                                ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeTypeC, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                            }
                            else
#endif
                            {
                                ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDp, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                            }
                        }
                        else if(GET_SOURCE_SEARCH_TIMES(ucSearchIndex) == 0x00)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

                    default:
                        break;
                }

                break;

            case _SOURCE_SWITCH_HP_SOURCE_SWITCH:
            case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:

                if(GET_SOURCE_HP_SWITCH_NO_CABLE() == _TRUE)
                {
                    DebugMessageSystem("7. No Cable Search 5secs", 0);

                    ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                }
                else if(GET_CABLE_DETECT(ucSearchIndex) == _FALSE)
                {
                    ScalerTimerReactiveTimerEvent(SEC(0.2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                }
                else
                {
                    switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex)))
                    {
#if(_VGA_PORT_EXIST == _ON)
                        case _PORT_VGA:
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeVga, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
                        case _PORT_HDMI:
                        case _PORT_MHL:
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeHdmi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
                        case _PORT_DVI:
                        case _PORT_DUAL_DVI:
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDvi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                            break;
#endif

#if(_DP_PORT_EXIST == _ON)
                        case _PORT_DP:

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
                            if(SysTypeCCheckTypeCPortControllerExist(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex))) == _TRUE)
                            {
                                ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeTypeC, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                            }
                            else
#endif
                            {
                                ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDp, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                            }

                            break;
#endif

                        default:
                            break;
                    }
                }

                break;
#endif // End of #if(_HP_SOURCE_SCAN_SUPPORT == _ON)

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Judge if the port with source will be chosen
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceJudge(void)
{
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE ucDpSwitchPortBackup = GET_D6_SWITCH_SELECT();
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:
        case _SOURCE_SWITCH_AUTO_IN_GROUP:
        case _SOURCE_SWITCH_AUTO_WITHOUT_GROUP:
        case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
        case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
#endif
            if(GET_SOURCE_TYPE(g_ucSearchIndex) != _SOURCE_NONE)
            {
#if((_HP_SOURCE_SCAN_SUPPORT == _ON) && (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
                CLR_SOURCE_HP_DETECTING();
#endif
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                // Choose Current Source to proceed
                SET_SOURCE_JUDGE(g_ucSearchIndex, _TRUE);

                CLR_SOURCE_SWITCH_FINISH();

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
                CLR_SOURCE_DETECTING();
                g_ucBgDetectIndex = g_ucSearchIndex;
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_FUJITSU_STYLE)
                CLR_SOURCE_FUJITSU_SWITCH_PORT();
#endif
                if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
                }
                else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
                }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                {
                    SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                }
                else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                {
                    SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                }
                else
                {
                    SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
                }

                if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                {
                    PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                    SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                    CLR_DP_AUTO_SEARCH_SWITCH();

                    if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                    {
                        ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                    }
                    else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                    {
                        ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                    }
                }
#endif
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
#if(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_F)
                if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_TIMING_CHANGE)
                {
                    CLR_SOURCE_JUDGE(g_ucSearchIndex);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
                    CLR_SOURCE_BG_JUDGE(g_ucBgDetectIndex);
#endif

                    if(GET_SOURCE_HP_SOURCE_JUDGE() == _TRUE)
                    {
                        CLR_SOURCE_HP_TARGET_NO_SIGNAL();

                        if(g_ucSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT)))
                        {
                            g_ucSearchIndex = 0;

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                            SET_SOURCE_HP_TIMING_CHANGE();

                            SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

                            CLR_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                            SET_MODE_RESET_TARGET(_MODE_ACTION_RESET_TO_SEARCH);

                            return;
                        }

                        SET_SOURCE_JUDGE(g_ucSearchIndex, _TRUE);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
                        CLR_SOURCE_DETECTING();
                        g_ucBgDetectIndex = g_ucSearchIndex;
#endif
                    }
                    else
                    {
                        CLR_SOURCE_DETECTING();

                        CLR_MODE_TIMING_CONFIRM();
                    }
                }
#endif
#endif
            }
            else if(GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE)
            {
                if(GET_SOURCE_SEARCH_TIME_REACTIVE() == _TRUE)
                {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
                    SET_SOURCE_EIZO_EVENT_TIME(ScalerTimerGetEventRemainTime(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING));
#endif
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                    SET_SOURCE_DETECTING();

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)

                    if((GET_SOURCE_SEARCH_CHECK_NVRAM_PORT() == _TRUE) &&
                       (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE) &&
                       (GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) != 0x00) &&
                       (((GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT)))) &&
                         (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_AUTO_IN_GROUP)) ||
                        (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_AUTO_WITHOUT_GROUP)) &&
                       (g_ucSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))))
                    {
                        g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE);

                        CLR_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                        CLR_SOURCE_SEARCH_TIME_REACTIVE();
                    }
#else
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                    CLR_SOURCE_SEARCH_TIME_REACTIVE();
#endif
                }

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                }
            }

            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SOURCE_SWITCH:
        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            if(GET_SOURCE_TYPE(g_ucSearchIndex) != _SOURCE_NONE)
            {
#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _TWO_CHIP_DATA_EXCHANGE_MODE)
                CLR_SOURCE_HP_DETECTING();
#endif
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                if(GET_SOURCE_HP_SOURCE_JUDGE() == _TRUE)
                {
                    CLR_SOURCE_HP_TARGET_NO_SIGNAL();

                    SET_SOURCE_JUDGE(g_ucSearchIndex, _TRUE);

                    CLR_SOURCE_SWITCH_FINISH();

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
                    CLR_SOURCE_DETECTING();
                    g_ucBgDetectIndex = g_ucSearchIndex;
#endif

                    if((GET_SOURCE_HP_TIMING_CHANGE() == _TRUE) &&
                       (g_ucSearchIndex == SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))))
                    {
                        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_TIMING_CHANGE);
                    }
                }
                else
                {
                    CLR_SOURCE_DETECTING();

                    CLR_MODE_TIMING_CONFIRM();
                }

                DebugMessageSystem("7. Source Judge HP Case", g_ucSearchIndex);
            }
            else if(GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE)
            {
                if(GET_SOURCE_SEARCH_TIME_REACTIVE() == _TRUE)
                {
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                    SET_SOURCE_DETECTING();

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                    CLR_SOURCE_SEARCH_TIME_REACTIVE();
                }

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                }
            }

            break;
#endif // End of #if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Port Switch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchPort(void)
{
    BYTE ucCount = 0;
    BYTE ucBackupSearchIndex = g_ucSearchIndex;

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE ucDpSwitchPortBackup = GET_D6_SWITCH_SELECT();
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                SET_SOURCE_SWITCH_FINISH();
            }

            break;

        case _SOURCE_SWITCH_AUTO_IN_GROUP:

            // Switch to the next port by search priority with group limit.
            do
            {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                    }
                }

#elif((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_FUJITSU_STYLE))

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();

                        if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
                        {
                            g_ucSearchIndex = ucBackupSearchIndex;

                            return;
                        }
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) <= 1)
                {
                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();

                        if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
                        {
                            g_ucSearchIndex = ucBackupSearchIndex;

                            return;
                        }
                    }

                    if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

                if(GET_SOURCE_ASUS_START_AUTO() == _TRUE)
                {
                    if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                        if(SysSourceCheckTargetTimes(1) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();

                            SET_SOURCE_ASUS_START_POLLING();
                        }
                    }

                    if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                    {
                        SET_SOURCE_ASUS_FIRST_START_AUTO();
                    }
                }
                else
                {
                    if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                        SET_SOURCE_SWITCH_FINISH();

                        ScalerTimerActiveTimerEvent(_SOURCE_ASUS_START_AUTO_TIME, _SYSTEM_TIMER_EVENT_SOURCE_ASUS_START_AUTO);

                        CLR_SOURCE_ASUS_START_POLLING();
                    }

                    return;
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        if(GET_MODE_STATE() != _MODE_STATUS_SEARCH)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }
                    }
                }

                if((GET_SOURCE_EIZO_PS_SUPPORT() == _TRUE) && (SysSourceCheckTargetTimes(1) == _TRUE) && (GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (GET_SOURCE_SWITCH_FINISH() == _FALSE))
                {
                    return;
                }

#endif // End of #if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

                if(GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(ucBackupSearchIndex))
                {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                    if((GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(_D0_INPUT_PORT))) == (GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(_D6_INPUT_PORT))))
                    {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)
                        if((GET_MODE_STATE() != _MODE_STATUS_SEARCH) && (GET_SOURCE_ASUS_FIRST_START_AUTO() == _TRUE))
                        {
                            ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
                            CLR_SOURCE_DP_SWITCH_TIMEOUT();
                            CLR_SOURCE_ASUS_FIRST_START_AUTO();
                        }
#else
                        if((GET_MODE_STATE() != _MODE_STATUS_SEARCH) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
                        {
                            ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
                            CLR_SOURCE_DP_SWITCH_TIMEOUT();
                        }
#endif
                        if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D6_INPUT_PORT))
                        {
                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) || (GET_SOURCE_DP_SWITCH_TIMEOUT() == _TRUE))
                            {
                                if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON) && (SysSourceGetInputPort() != GET_D6_SWITCH_SELECT()))
                                {
                                    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
                                    {
                                        ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
                                        CLR_SOURCE_DP_SWITCH_TIMEOUT();
                                    }

                                    if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                                    {
                                        SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                                    }
                                    else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                                    {
                                        SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                                    }

                                    if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                                    {
                                        PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                        SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);

                                        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                                        {
                                            CLR_DP_AUTO_SEARCH_SWITCH();
                                        }
                                        else
                                        {
                                            SET_DP_AUTO_SEARCH_SWITCH();
                                        }

                                        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                                        {
                                            ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                                        }
                                        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                                        {
                                            ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                                        }
                                    }
                                }

                                break;
                            }
                            else
                            {
                                if(SysSourceGetInputPort() == GET_D6_SWITCH_SELECT())
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                            {
                                SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
                            }

                            if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                            {
                                PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                CLR_DP_AUTO_SEARCH_SWITCH();

                                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                                {
                                    ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                                }
                                else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                                {
                                    ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                                }
                            }

                            break;
                        }
                    }
                    else // D0 DP Port and D6 DP Port are Not in the Same Group
                    {
                        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                        {
                            SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                        }
                        else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                        {
                            SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                        }

                        if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                        {
                            PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                            SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                            CLR_DP_AUTO_SEARCH_SWITCH();

                            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                            {
                                ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                            }
                            else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                            {
                                ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                            }
                        }

                        break;
                    }

#elif(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

                    if(SysSourceCheckEmbeddedDpAutoSwitch() == _TRUE)
                    {
                        break;
                    }

#else // #else of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                    break;
#endif
                }
                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                   ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                {
                    SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                }
#endif
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

#elif((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE))

                if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }
                else
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                   ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                {
                    SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                }
#endif
                if(GET_SOURCE_ASUS_START_POLLING() == _TRUE)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE)

                pData[1] = 0;

                for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                {
                    if(GET_SOURCE_SEARCH_TIMES(pData[0]) == 1)
                    {
                        pData[1]++;
                    }
                }

                if(pData[1] >= 2)
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_FUJITSU_STYLE)

                if(GET_SOURCE_FUJITSU_SWITCH_PORT() == _TRUE)
                {
                    if(g_ucSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT)))
                    {
                        g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                        for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                        {
                            CLR_SOURCE_SEARCH_TIMES(pData[0]);
                        }
                    }

                    CLR_SOURCE_FUJITSU_SWITCH_PORT();
                }

                if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }
                else
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
#endif
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            break;

        case _SOURCE_SWITCH_AUTO_WITHOUT_GROUP:

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                if(SysSourceCheckTargetTimes(1) == _TRUE)
                {
                    SET_SOURCE_SWITCH_FINISH();
                }
            }

#elif((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_FUJITSU_STYLE))

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                if(SysSourceCheckTargetTimes(1) == _TRUE)
                {
                    SET_SOURCE_SWITCH_FINISH();

                    if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
                    {
                        return;
                    }
                }
            }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) <= 1)
            {
                if(SysSourceCheckTargetTimes(1) == _TRUE)
                {
                    SET_SOURCE_SWITCH_FINISH();

                    if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
                    {
                        return;
                    }
                }

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);
                }
            }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                if(SysSourceCheckTargetTimes(1) == _TRUE)
                {
                    SET_SOURCE_SWITCH_FINISH();
                }
            }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                if(SysSourceCheckTargetTimes(1) == _TRUE)
                {
                    if(GET_MODE_STATE() != _MODE_STATUS_SEARCH)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                    }
                }
            }

            if((GET_SOURCE_EIZO_PS_SUPPORT() == _TRUE) && (SysSourceCheckTargetTimes(1) == _TRUE) && (GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (GET_SOURCE_SWITCH_FINISH() == _FALSE))
            {
                return;
            }

#endif // End of #if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

            g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

            DebugMessageSystem("7. wuanne test : Search Initial : 3", 0);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
            if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
               ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
            {
                SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
            }
#endif
            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

#elif((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE))

            if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
            {
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
            }
            else
            {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                   ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                {
                    SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                }
#endif
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
            }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
            if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
               ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
            {
                SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
            }
#endif
            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_FUJITSU_STYLE)

            if(GET_SOURCE_FUJITSU_SWITCH_PORT() == _TRUE)
            {
                if(g_ucSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT)))
                {
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        CLR_SOURCE_SEARCH_TIMES(pData[0]);
                    }
                }

                CLR_SOURCE_FUJITSU_SWITCH_PORT();
            }

            if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
            {
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
            }
            else
            {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                   ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                {
                    SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                }
#endif
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
            }
#endif
            SET_SOURCE_SEARCH_TIME_REACTIVE();

            break;

        case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
        case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

            do
            {
                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();

                        if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
                        {
                            g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
                        }
                        else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
                        {
                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
                        }

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        return;
                    }
                }

                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

                if(GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(ucBackupSearchIndex))
                {
                    break;
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            break;

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));
            }

            if((SysSourceCheckTargetTimes(1) == _TRUE) ||
               (SysSourceCheckTargetTimes(2) == _TRUE) ||
               (SysSourceCheckTargetTimes(3) == _TRUE))
            {
                CLR_SOURCE_HP_FROM_TIMING_CHANGE();

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE)
                {
                    if((GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID) && (GET_CABLE_DETECT(GET_SOURCE_HP_PORT_SWITCH_TARGET()) == _TRUE))
                    {
                        if(GET_SOURCE_TYPE(GET_SOURCE_HP_PORT_SWITCH_TARGET()) != _SOURCE_NONE)
                        {
                            g_ucSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();

                            DebugMessageSystem("7. Bingo Switch Port!!!!!!!", 0);

                            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                            return;
                        }
                    }
                    else
                    {
                        if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID)
                        {
                            if(GET_SOURCE_TYPE(GET_SOURCE_HP_PORT_SWITCH_TARGET()) != _SOURCE_NONE)
                            {
                                g_ucSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();

                                DebugMessageSystem("7. Bingo Switch Port!!!!!!!", 0);

                                SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                                SET_SOURCE_SEARCH_TIME_INITIAL();

                                SET_SOURCE_SEARCH_PORT_INITIAL();

                                SET_SOURCE_SEARCH_TIME_REACTIVE();

                                SET_SOURCE_HP_SOURCE_JUDGE();

                                CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                                SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                                return;
                            }
                        }

                        if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) != _SOURCE_NONE)
                        {
                            g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                            DebugMessageSystem("7. Bingo Eeprom!!!!!!!", g_ucSearchIndex);

                            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            return;
                        }

                        if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SOURCE_HP_DEFAULT_PORT))) != _SOURCE_NONE)
                        {
                            g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SOURCE_HP_DEFAULT_PORT));

                            DebugMessageSystem("7. Bingo Defautlt!!!!!!!", g_ucSearchIndex);

                            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            return;
                        }

                        for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                        {
                            if(GET_SOURCE_TYPE(pData[0]) != _SOURCE_NONE)
                            {
                                g_ucSearchIndex = pData[0];

                                DebugMessageSystem("7. Bingo Priority!!!!!!!", g_ucSearchIndex);

                                SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                                SET_SOURCE_SEARCH_TIME_INITIAL();

                                SET_SOURCE_SEARCH_PORT_INITIAL();

                                SET_SOURCE_SEARCH_TIME_REACTIVE();

                                SET_SOURCE_HP_SOURCE_JUDGE();

                                CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                                return;
                            }
                        }
                    }
                }
                else
                {
                    if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) != _SOURCE_NONE)
                    {
                        DebugMessageSystem("7. Bingo Eeprom Fix Port!!!!!!!", g_ucSearchIndex);

                        g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                        SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        return;
                    }
                }

                if((GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (SysSourceCheckTargetTimes(1) == _TRUE))
                {
                    pData[1] = 0;

                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        pData[1] = pData[1] | GET_CABLE_DETECT(pData[0]);
                    }

                    if(pData[1] == 0)
                    {
                        SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);
                    }
                }
            }

            if((GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _TRUE))
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID)
                {
                    DebugMessageSystem("7. Search Finish !!!!!!!!!!!!!!!!!!!", g_ucSearchIndex);
                    CLR_SOURCE_HP_TARGET_NO_SIGNAL();
                    SET_SOURCE_SWITCH_FINISH();
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    SET_SOURCE_HP_TARGET_NO_SIGNAL();
                    ScalerTimerActiveTimerEvent(SEC(5), _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
                }
            }

            if((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE) ||
               (((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)) &&
                (GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (GET_SOURCE_SWITCH_FINISH() == _FALSE)))
            {
                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;
            }
            else
            {
                g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
            }

            if(GET_MODE_STATE() == _MODE_STATUS_NOSIGNAL)
            {
                SET_SOURCE_HP_SOURCE_JUDGE();

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
                }
            }
            else if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
            {
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_TIMING_CHANGE);

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
                }
            }

            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

            break;

        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));
            }

            if(((SysSourceCheckTargetTimes(1) == _TRUE) ||
                (SysSourceCheckTargetTimes(2) == _TRUE) ||
                (SysSourceCheckTargetTimes(3) == _TRUE)))
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < (_INPUT_PORT_VALID))
                {
                    if(GET_SOURCE_TYPE(GET_SOURCE_HP_PORT_SWITCH_TARGET()) != _SOURCE_NONE)
                    {
                        g_ucSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();

                        DebugMessageSystem("7. Bingo Switch Port!!!!!!!", 0);

                        SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                        return;
                    }
                }

                if((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE) && (GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID))
                {
                    if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) != _SOURCE_NONE)
                    {
                        g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                        DebugMessageSystem("7. Bingo Eeprom!!!!!!!", g_ucSearchIndex);

                        SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        return;
                    }

                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        if(GET_SOURCE_TYPE(pData[0]) != _SOURCE_NONE)
                        {
                            g_ucSearchIndex = pData[0];

                            DebugMessageSystem("7. Bingo Priority!!!!!!!", g_ucSearchIndex);

                            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            return;
                        }
                    }
                }
            }

            if((GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _TRUE))
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID)
                {
                    DebugMessageSystem("7. Search Finish2 !!!!!!!!!!!!!!!!!!!", g_ucSearchIndex);
                    CLR_SOURCE_HP_TARGET_NO_SIGNAL();
                    SET_SOURCE_SWITCH_FINISH();
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    DebugMessageSystem("7. Switch no signal !!!!!!!!!!!!!!!!!!!", g_ucSearchIndex);
                    SET_SOURCE_HP_TARGET_NO_SIGNAL();
                    ScalerTimerActiveTimerEvent(SEC(UserInterfaceGetHpSourceSwitchOsdEventTime(_SOURCE_SWITCH_HP_SCAN_SWITCH_PORT)), _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
                }
            }

            if(((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE) && (GET_MODE_STATE() != _MODE_STATUS_SEARCH)) ||
               (((UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)) && (GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (GET_SOURCE_SWITCH_FINISH() == _FALSE)) ||
               (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _FALSE))
            {
                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;
            }
            else
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID)
                {
                    g_ucSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();
                }
            }

            if(GET_MODE_STATE() == _MODE_STATUS_NOSIGNAL)
            {
                SET_SOURCE_HP_SOURCE_JUDGE();

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
                }
            }
            else if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
            {
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_TIMING_CHANGE);

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

                if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
                {
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
                }
            }

            CLR_SOURCE_HP_TIMING_CHANGE();

            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

            break;

        case _SOURCE_SWITCH_HP_TIMING_CHANGE:

#if(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_E)

            if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
            {
                g_ucSearchIndex = 0;

                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                SET_SOURCE_SEARCH_TIME_REACTIVE();

                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                SET_SOURCE_HP_TIMING_CHANGE();

                SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

                CLR_SOURCE_HP_SOURCE_JUDGE();

                CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                return;
            }

#elif(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_F)

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
            {
                if(GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID)
                {
                    if(GET_SOURCE_TYPE(GET_SOURCE_HP_PORT_SWITCH_TARGET()) != _SOURCE_NONE)
                    {
                        g_ucSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();

                        DebugMessageSystem("7. Bingo Switch Port!!!!!!!", 0);

                        SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                        return;
                    }

                    DebugMessageSystem("7. Switch no signal !!!!!!!!!!!!!!!!!!!", g_ucSearchIndex);

                    SET_SOURCE_HP_TARGET_NO_SIGNAL();

                    ScalerTimerActiveTimerEvent(SEC((UserInterfaceGetHpSourceSwitchOsdEventTime(_SOURCE_SWITCH_HP_TIMING_CHANGE))), _SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);
                }
                else
                {
                    g_ucSearchIndex = 0;

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                    SET_SOURCE_SEARCH_TIME_REACTIVE();

                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                    SET_SOURCE_HP_FROM_TIMING_CHANGE();

                    SET_SOURCE_HP_TIMING_CHANGE();

                    SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

                    CLR_SOURCE_HP_SOURCE_JUDGE();

                    CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                    return;
                }
            }

            if(GET_SOURCE_HP_PORT_SWITCH_TARGET() > _INPUT_PORT_VALID)
            {
                DebugMessageSystem("7. Search Finish3 !!!!!!!!!!!!!!!!!!!", g_ucSearchIndex);
                CLR_SOURCE_HP_TARGET_NO_SIGNAL();
                SET_SOURCE_SWITCH_FINISH();
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
            }

            if((GET_MODE_STATE() == _MODE_STATUS_NOSIGNAL) || (GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING))
            {
                SET_SOURCE_HP_SOURCE_JUDGE();
            }
#endif

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                if(SysSourceCheckTargetTimes(1) == _TRUE)
                {
                    SET_SOURCE_SWITCH_FINISH();
                }
            }

            if(GET_MODE_STATE() == _MODE_STATUS_SEARCH)
            {
                g_ucSearchIndex = GET_SOURCE_HP_PORT_SWITCH_TARGET();
            }
            else if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE)
            {
                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;
            }
            else if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _FALSE)
            {
                g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));
            }

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            break;

        case _SOURCE_SWITCH_HP_SOURCE_SWITCH:

            if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE)
            {
                if(GET_SOURCE_HP_SWITCH_NO_CABLE() == _FALSE)
                {
                    if(GET_SOURCE_TYPE(g_ucSearchIndex) != _SOURCE_NONE)
                    {
                        for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                        {
                            CLR_SOURCE_SEARCH_TIMES(pData[0]);
                        }

                        SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

                        DebugMessageSystem("7. Switch Port with Signal", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));
                    }
                    else
                    {
                        if(GET_CABLE_DETECT(g_ucSearchIndex) == _FALSE)
                        {
                            SET_SOURCE_HP_SWITCH_NO_CABLE();

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            DebugMessageSystem("7. Switch Port No Cable", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));

                            return;
                        }
                        else
                        {
                            for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                            {
                                CLR_SOURCE_SEARCH_TIMES(pData[0]);
                                INCREASE_SOURCE_SEARCH_TIMES(pData[0]);
                            }

                            SET_SOURCE_HP_TARGET_SEARCH_TIMES(3);

                            DebugMessageSystem("7. Switch Port No Signal", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));
                        }
                    }
                }
                else
                {
                    CLR_SOURCE_HP_SWITCH_NO_CABLE();

                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        CLR_SOURCE_SEARCH_TIMES(pData[0]);
                    }

                    SET_SOURCE_HP_TARGET_SEARCH_TIMES(3);

                    DebugMessageSystem("7. Switch Port No Cable Finish", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));
                }

                g_ucSearchIndex = 0;
            }
            else
            {
                if(GET_SOURCE_TYPE(g_ucSearchIndex) == _SOURCE_NONE)
                {
                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        CLR_SOURCE_SEARCH_TIMES(pData[0]);

                        INCREASE_SOURCE_SEARCH_TIMES(pData[0]);
                    }

                    if(GET_CABLE_DETECT(g_ucSearchIndex) == _FALSE)
                    {
                        SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);
                    }
                    else
                    {
                        SET_SOURCE_HP_TARGET_SEARCH_TIMES(3);

                        g_ucSearchIndex = 0;
                    }
                }
                else
                {
                    for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                    {
                        CLR_SOURCE_SEARCH_TIMES(pData[0]);
                    }

                    SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);
                }
            }

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

            CLR_SOURCE_HP_TIMING_CHANGE();

            CLR_SOURCE_HP_SOURCE_JUDGE();

            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

            break;

        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));
            }

            if(SysSourceCheckTargetTimes(1) == _TRUE)
            {
                if((GET_SOURCE_HP_PORT_SWITCH_TARGET() < _INPUT_PORT_VALID))
                {
                    BYTE ucTemp = 0;

                    for(ucTemp = 1; ucTemp <= _INPUT_PORT_VALID; ucTemp++)
                    {
                        if(GET_SOURCE_TYPE((GET_SOURCE_HP_PORT_SWITCH_TARGET() + ucTemp) % _INPUT_PORT_VALID) != _SOURCE_NONE)
                        {
                            g_ucSearchIndex = ((GET_SOURCE_HP_PORT_SWITCH_TARGET() + ucTemp) % _INPUT_PORT_VALID);

                            DebugMessageSystem("7. Bingo Next Port!!!!!!!", g_ucSearchIndex);

                            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                            SET_SOURCE_SEARCH_TIME_INITIAL();

                            SET_SOURCE_SEARCH_PORT_INITIAL();

                            SET_SOURCE_SEARCH_TIME_REACTIVE();

                            SET_SOURCE_HP_SOURCE_JUDGE();

                            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

                            return;
                        }
                    }
                }

                // Switch to Target Search Scan Type
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);
            }

            g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

            break;

        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) < GET_SOURCE_HP_TARGET_SEARCH_TIMES())
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                DebugMessageSystem("7. == SearchIndex ==", g_ucSearchIndex);
                DebugMessageSystem("7. wuzanee test : Search Times", GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex));
            }

            if(SysSourceCheckTargetTimes(1) == _TRUE)
            {
                BYTE ucIndex = 0;

                if((GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SOURCE_HP_DEFAULT_PORT))) != _SOURCE_NONE) &&
                   (UserCommonNVRamGetSystemData(_SOURCE_HP_DEFAULT_PORT) != UserCommonNVRamGetSystemData(_SEARCH_PORT)))
                {
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SOURCE_HP_DEFAULT_PORT));

                    DebugMessageSystem("7. Bingo Defautlt!!!!!!!", g_ucSearchIndex);

                    SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

                    SET_SOURCE_SEARCH_TIME_REACTIVE();

                    SET_SOURCE_HP_SOURCE_JUDGE();

                    CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                    return;
                }

                for(ucIndex = 0; ucIndex < _INPUT_PORT_VALID; ucIndex++)
                {
                    if((GET_SOURCE_TYPE(ucIndex) != _SOURCE_NONE) &&
                       (SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT)) != ucIndex))
                    {
                        g_ucSearchIndex = ucIndex;

                        DebugMessageSystem("7. Bingo Priority!!!!!!!", g_ucSearchIndex);

                        SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        SET_SOURCE_HP_SOURCE_JUDGE();

                        CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

                        return;
                    }
                }

                if(GET_SOURCE_TYPE(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT))) != _SOURCE_NONE)
                {
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

                    DebugMessageSystem("7. Bingo Eeprom!!!!!!!", g_ucSearchIndex);

                    SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

                    SET_SOURCE_SEARCH_TIME_REACTIVE();

                    SET_SOURCE_HP_SOURCE_JUDGE();

                    CLR_SOURCE_PREDETECT(g_ucSearchIndex);

                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                    return;
                }
            }

            if((GET_MODE_STATE() == _MODE_STATUS_SEARCH) && (SysSourceCheckTargetTimes(GET_SOURCE_HP_TARGET_SEARCH_TIMES()) == _TRUE))
            {
                DebugMessageSystem("7. Search Finish !!!!!!!!!!!!!!!!!!!", g_ucSearchIndex);
                SET_SOURCE_SWITCH_FINISH();
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);
                SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));
            }

            g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

            SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_TIME_REACTIVE();

            CLR_SOURCE_PREDETECT(g_ucSearchIndex);

            break;

#endif // End of #if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Port Initial Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceScanPortInitial(BYTE ucSearchIndex)
{
    EnumSourceSearchPort enumSearchPort = GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex));
    EnumInputPortType enumPortType = GET_PORT_TYPE(GET_INPUTPORT_TYPE(ucSearchIndex));

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
    if(ucSearchIndex != g_ucSearchIndex)
    {
        ScalerSyncBgInterfaceSwitch(SysSourceGetInputPort(), GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)),
                                    enumSearchPort, enumPortType,
                                    GET_SOURCE_SEARCH_DELAY_MODE());
    }
    else
#endif
    {
        ScalerSyncInterfaceSwitch(enumSearchPort, enumPortType, GET_SOURCE_SEARCH_DELAY_MODE());
    }

    switch(enumPortType)
    {
#if(_VGA_SUPPORT == _ON)
        case _PORT_VGA:

            DebugMessageSystem("7. VGA Port Initial", 1);

            if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                ScalerSyncProcScanInitial();
            }

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _PORT_DVI:
        case _PORT_HDMI:
        case _PORT_MHL:

            DebugMessageSystem("7. TMDS Port Initial", enumPortType);

            if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                ScalerSyncTMDSScanInitial(enumSearchPort);
            }

            break;
#endif

#if(_DUAL_DVI_SUPPORT == _ON)
        case _PORT_DUAL_DVI:

            DebugMessageSystem("7. Dual DVI Initial", 1);

            if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                ScalerDualLinkDVIScanInitial(enumSearchPort);
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _PORT_DP:

            DebugMessageSystem("7. DP Port Initial", 1);

            if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                ScalerDpScanInitial(enumSearchPort);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial Source Switch Flags
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInitial(void)
{
    BYTE ucPort = 0;

    SysSourceSetSearchPriority(_NO_INPUT_PORT, _INPUT_PORT_PRIORITY_NONE);
    SysSourceSetSearchGroup(_NO_INPUT_PORT, _INPUT_PORT_GROUP_NONE);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_VGA, _SOURCE_DEFAULT_SEARCH_TIME_VGA);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_HDMI, _SOURCE_DEFAULT_SEARCH_TIME_HDMI);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_DVI, _SOURCE_DEFAULT_SEARCH_TIME_DVI);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_DP, _SOURCE_DEFAULT_SEARCH_TIME_DP);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_TYPE_C, _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_VGA, _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_HDMI, _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_DVI, _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_DP, _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_TYPE_C, _SOURCE_DEFAULT_SEARCH_TIME_TYPE_C_NO_CABLE);

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    g_ucSearchIndex = 0;

    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

    CLR_SOURCE_HP_TIMING_CHANGE();

#if(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_E)
    SET_SOURCE_HP_TARGET_SEARCH_TIMES(3);
#elif(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_F)
    SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);
#endif

    SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));
#else
    if((UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != _SOURCE_SWITCH_AUTO_IN_GROUP) &&
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != _SOURCE_SWITCH_AUTO_WITHOUT_GROUP) &&
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != _SOURCE_SWITCH_FIXED_PORT))
    {
        UserCommonNVRamRestoreSystemData();
    }

    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

    SET_SOURCE_SCAN_TYPE(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE));
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

    PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
    SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
    CLR_DP_AUTO_SEARCH_SWITCH();

    if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D6_INPUT_PORT))
    {
        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
        {
            SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
        }
        else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
        {
            SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
        }
    }
    else
    {
        SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
    }

#elif(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_1_DP)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    SET_DP_EMBEDDED_SWITCH_SELECT(_D0_INPUT_PORT);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    SET_DP_EMBEDDED_SWITCH_SELECT(_D1_INPUT_PORT);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    SET_DP_EMBEDDED_SWITCH_SELECT(_D2_INPUT_PORT);
#endif

    SET_DP_EMBEDDED_SWITCH_TARGET(GET_DP_EMBEDDED_SWITCH_SELECT());

#elif(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

    switch(SysSourceGetInputPort())
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            SET_DP_EMBEDDED_SWITCH_SELECT(_D0_INPUT_PORT);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            SET_DP_EMBEDDED_SWITCH_SELECT(_D1_INPUT_PORT);
            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:
            SET_DP_EMBEDDED_SWITCH_SELECT(_D2_INPUT_PORT);
            break;
#endif

        default:
            SET_DP_EMBEDDED_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
            break;
    }

    SET_DP_EMBEDDED_SWITCH_TARGET(GET_DP_EMBEDDED_SWITCH_SELECT());

#endif

    for(ucPort = 0; ucPort < _INPUT_PORT_VALID; ucPort++)
    {
        SET_CABLE_DETECT(ucPort, _FALSE);
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        SET_TYPE_C_ALT_MODE_DETECT(ucPort, _FALSE);
#endif
    }

#if(_DIGITAL_PORT_SUPPORT == _ON)

    if(UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH) == _TRUE)
    {
        SET_DP_DC_OFF_HPD_HIGH();
    }
    else
    {
        CLR_DP_DC_OFF_HPD_HIGH();
    }

#if(_DP_SUPPORT == _ON)
    if(UserCommonNVRamGetSystemData(_DP_AUX_DIFF_MODE) == _TRUE)
    {
        SET_DP_AUX_DIFF_MODE();
    }
    else
    {
        CLR_DP_AUX_DIFF_MODE();
    }

    SET_DP_AUX_ADJR_SETTING(UserCommonNVRamGetSystemData(_DP_AUX_ADJR_SETTING));

    SET_DP_IRQ_TIME_10US(UserCommonNVRamGetSystemData(_DP_IRQ_TIME));

#if(_DP_ILLEGAL_IDLE_PATTERN_CHECK_SUPPORT == _ON)
    if(UserCommonNVRamGetSystemData(_DP_ILLEGAL_IDLE_PATTERN_CHECK) == _TRUE)
    {
        SET_DP_ILLEGAL_IDLE_PATTERN_CHECK();
    }
    else
#endif
    {
        CLR_DP_ILLEGAL_IDLE_PATTERN_CHECK();
    }
#endif

    if(UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT) == _TRUE)
    {
        SET_HDMI_HOTPLUG_TOGGLE();
        SET_HDMI_HOTPLUG_TIME(UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
    }
    else
    {
        CLR_HDMI_HOTPLUG_TOGGLE();
        SET_HDMI_HOTPLUG_TIME(UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
    }

#if(((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)) || (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
    CLR_SOURCE_DP_SWITCH_TIMEOUT();
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
    if(UserCommonNVRamGetSystemData(_COLORIMETRY_SEAMLESS_CHANGE) == _TRUE)
    {
        CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
    }
    else
#endif
    {
        SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
    }
#endif

// HDMI FreeSync Initial
#if((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_TMDS_RX0_FREESYNC_SUPPORT(UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT));
#endif

#if((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_TMDS_RX1_FREESYNC_SUPPORT(UserInterfaceGetFreeSyncEnable(_D1_INPUT_PORT));
#endif

#if((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_TMDS_RX2_FREESYNC_SUPPORT(UserInterfaceGetFreeSyncEnable(_D2_INPUT_PORT));
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_TMDS_RX3_FREESYNC_SUPPORT(UserInterfaceGetFreeSyncEnable(_D3_INPUT_PORT));
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_TMDS_RX4_FREESYNC_SUPPORT(UserInterfaceGetFreeSyncEnable(_D4_INPUT_PORT));
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
    SET_TMDS_RX5_FREESYNC_SUPPORT(UserInterfaceGetFreeSyncEnable(_D5_INPUT_PORT));
#endif

// HDR10 Initial
#if(((_D0_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
    SET_RX0_HDR10_SUPPORT(UserInterfaceHDRGetHDR10ModeStatus(_D0_INPUT_PORT));
#endif

#if(((_D1_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
    SET_RX1_HDR10_SUPPORT(UserInterfaceHDRGetHDR10ModeStatus(_D1_INPUT_PORT));
#endif

#if(((_D2_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
    SET_RX2_HDR10_SUPPORT(UserInterfaceHDRGetHDR10ModeStatus(_D2_INPUT_PORT));
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    SET_RX3_HDR10_SUPPORT(UserInterfaceHDRGetHDR10ModeStatus(_D3_INPUT_PORT));
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    SET_RX4_HDR10_SUPPORT(UserInterfaceHDRGetHDR10ModeStatus(_D4_INPUT_PORT));
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    SET_RX5_HDR10_SUPPORT(UserInterfaceHDRGetHDR10ModeStatus(_D5_INPUT_PORT));
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_DP_HDR10_SUPPORT == _ON))
    SET_RX6_HDR10_SUPPORT(UserInterfaceHDRGetHDR10ModeStatus(_D6_INPUT_PORT));
#endif
#endif
}

//--------------------------------------------------
// Description  : Source Stable Check Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysSourceStableCheck(void)
{
    switch(GET_SOURCE_TYPE(g_ucSearchIndex))
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            return (bit)ScalerSyncProcStableDetect();
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            return ScalerTMDSStableDetect(SysSourceGetInputPort(), GET_SOURCE_TYPE(g_ucSearchIndex));
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            return (bit)ScalerDpStableDetect(SysSourceGetInputPort());
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : None
// Output Value : Source Type --> VGA/DVI/HDMI/DP
//--------------------------------------------------
BYTE SysSourceGetSourceType(void)
{
    return GET_SOURCE_TYPE(g_ucSearchIndex);
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : None
// Output Value : ucInputPort --> Input Port
//--------------------------------------------------
BYTE SysSourceGetInputPort(void)
{
    return SysSourceGetSpecificInputPort(g_ucSearchIndex);
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : Search Index
// Output Value : ucInputPort --> Input Port
//--------------------------------------------------
BYTE SysSourceGetSpecificInputPort(BYTE ucIndex)
{
    return GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucIndex));
}

//--------------------------------------------------
// Description  : Get Input Port Type
// Input Value  : Input Port
// Output Value : ucInputPort --> Input Port Type
//--------------------------------------------------
BYTE SysSourceGetInputPortType(BYTE ucInputPort)
{
    return GET_INPUTPORT_TYPE(SysSourceConvertSearchPort(ucInputPort));
}

//--------------------------------------------------
// Description  : Get Source Judge
// Input Value  : Input Port
// Output Value : ucInputPort --> Input Port Type
//--------------------------------------------------
BYTE SysSourceGetJudge(BYTE ucInputPort)
{
    return GET_SOURCE_JUDGE(SysSourceConvertSearchPort(ucInputPort));
}

//--------------------------------------------------
// Description  : Get Source predetect status
// Input Value  : Input Port
// Output Value : _TRUE if pre-detect passed
//--------------------------------------------------
bit SysSourceGetPreDetect(BYTE ucInputPort)
{
    return GET_SOURCE_PREDETECT(SysSourceConvertSearchPort(ucInputPort));
}

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
//--------------------------------------------------
// Description  : Get Current Playback Input Port
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
BYTE SysSourceGetAudioPlaybackPort(void)
{
    return SysSourceGetSpecificInputPort(GET_AUDIO_PLAYBACK_SEARCH_INDEX());
}
#endif

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : ucInputPort --> Input Port(A0,A1,D0,D1,V1)
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchInputPort(BYTE ucInputPort)
{
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE ucDpSwitchPortBackup = GET_D6_SWITCH_SELECT();
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SOURCE_SWITCH:
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            CLR_SOURCE_HP_TARGET_NO_SIGNAL();

            if(GET_SOURCE_TYPE(g_ucSearchIndex) == _SOURCE_NONE)
            {
                UserCommonNVRamSetSystemData(_SEARCH_PORT, ucInputPort);
            }

            g_ucSearchIndex = SysSourceConvertSearchPort(ucInputPort);

            DebugMessageSystem("7. OSD Switch Port to --> ", SysSourceConvertSearchPort(ucInputPort));

            if(UserCommonNVRamGetSystemData(_SOURCE_HP_AUTO_SEARCH) == _TRUE)
            {
                SET_SOURCE_HP_PORT_SWITCH_TARGET(SysSourceConvertSearchPort(ucInputPort));
            }
            else
            {
#if(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_E)
                if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_SCAN_NEXT_PORT)
                {
                    SET_SOURCE_HP_PORT_SWITCH_TARGET(SysSourceConvertSearchPort(ucInputPort));
                }
                else
                {
                    SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));
                }
#elif(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_F)
                SET_SOURCE_HP_PORT_SWITCH_TARGET(SysSourceConvertSearchPort(ucInputPort));
#endif
                UserCommonNVRamSetSystemData(_SEARCH_PORT, ucInputPort);
            }

            CLR_SOURCE_HP_SOURCE_JUDGE();

            CLR_SOURCE_HP_SWITCH_NO_CABLE();

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

            break;

        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:

            g_ucSearchIndex = 0;

            CLR_SOURCE_HP_SOURCE_JUDGE();

            CLR_SOURCE_HP_TIMING_CHANGE();

            SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

            SysSourceInfoReset();

            break;
#endif
        default:

            g_ucSearchIndex = SysSourceConvertSearchPort(ucInputPort);

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_FUJITSU_STYLE)
            SET_SOURCE_FUJITSU_SWITCH_PORT();
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

            if(SysSourceGetInputPort() == _D0_INPUT_PORT)
            {
                SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
            }
            else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
            {
                SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
            }
            else
            {
                SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
            }

            if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
            {
                PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                CLR_DP_AUTO_SEARCH_SWITCH();

                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                {
                    ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                }
                else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                {
                    ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort());
                }
            }

#elif(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

            if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)) == _PORT_DP)
            {
                pData[0] = ucInputPort;
            }
            else
            {
                pData[0] = UserInterfaceGetDpSwitchSelectPort();
            }

            // Switch to new DP port
            if(GET_DP_EMBEDDED_SWITCH_SELECT() != pData[0])
            {
                SysSourceEmbeddedDpSwitch(pData[0]);
                CLR_DP_AUTO_SEARCH_SWITCH();
            }

#endif
            break;
    }
}


//--------------------------------------------------
// Description  : Source Information Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInfoReset(void)
{
    BYTE ucCnt = 0x00;

    SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

    if(GET_MODE_STATE() != _MODE_STATUS_POWER_SAVING)
    {
        CLR_SOURCE_ASUS_START_AUTO();
        CLR_SOURCE_ASUS_FIRST_START_AUTO();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_ASUS_START_AUTO);
    }

#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
    if((GET_MODE_STATE() != _MODE_STATUS_SEARCH) || (GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE))
#endif
    {
        // Clear Source Flags
        SET_SOURCE_DETECTING();
        SET_SOURCE_SEARCH_TIME_INITIAL();
        CLR_SOURCE_SWITCH_FINISH();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
        SET_SOURCE_EIZO_INFO_RESET();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
#endif

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
        if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_MODE_STATE() == _MODE_STATUS_FACTORY) ||
           ((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE) &&
            (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE)))
#else
        if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_MODE_STATE() == _MODE_STATUS_FACTORY) ||
           (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
#endif
        {
            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

            SET_SOURCE_SEARCH_TIME_REACTIVE();
        }

        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }

    for(ucCnt = 0; ucCnt < _INPUT_PORT_VALID; ucCnt++)
    {
        // Interface Reset Process
        if((GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_SOURCE_SCAN) && (GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT) &&
           (GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_SCAN_NEXT_PORT) && (GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN))
        {
            SET_SOURCE_TYPE(ucCnt, _SOURCE_NONE);
        }

        CLR_SOURCE_SEARCH_TIMES(ucCnt);
        CLR_SOURCE_JUDGE(ucCnt);
        CLR_SOURCE_PREDETECT(ucCnt);

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
        CLR_SOURCE_BG_JUDGE(ucCnt);
#endif
    }

#if(((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)) ||\
    (_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP))
    CLR_DP_AUTO_SEARCH_SWITCH();
#endif
}

//--------------------------------------------------
// Description  : Source Cable Status Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceCableDetection(void)
{
    BYTE ucI = 0;

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
    SysSourceHdmi5VDetection();
#endif

    // Get Each Cable Status From Pin
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
    SET_A0_CABLE_STATUS(!PCB_A0_PIN());
#endif

#if(_A1_INPUT_PORT_TYPE != _A1_NO_PORT)
    SET_A1_CABLE_STATUS(!PCB_A1_PIN());
#endif

#if(_A2_INPUT_PORT_TYPE != _A2_NO_PORT)
    SET_A2_CABLE_STATUS(!PCB_A2_PIN());
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    SET_D0_CABLE_STATUS((!PCB_D0_PIN()) | PCB_D0_MHL_DETECT());
#else
    SET_D0_CABLE_STATUS(!PCB_D0_PIN());
#endif
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    SET_D1_CABLE_STATUS((!PCB_D1_PIN()) | PCB_D1_MHL_DETECT());
#else
    SET_D1_CABLE_STATUS(!PCB_D1_PIN());
#endif
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    SET_D2_CABLE_STATUS((!PCB_D2_PIN()) | PCB_D2_MHL_DETECT());
#else
    SET_D2_CABLE_STATUS(!PCB_D2_PIN());
#endif
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    SET_D3_CABLE_STATUS((!PCB_D3_PIN()) | PCB_D3_MHL_DETECT());
#else
    SET_D3_CABLE_STATUS(!PCB_D3_PIN());
#endif
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    SET_D4_CABLE_STATUS((!PCB_D4_PIN()) | PCB_D4_MHL_DETECT());
#else
    SET_D4_CABLE_STATUS(!PCB_D4_PIN());
#endif
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    SET_D5_CABLE_STATUS((!PCB_D5_PIN()) | PCB_D5_MHL_DETECT());
#else
    SET_D5_CABLE_STATUS(!PCB_D5_PIN());
#endif
#endif

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
    SET_D6_CABLE_STATUS(!PCB_D6_PIN());
#endif

    for(ucI = 0; ucI < _INPUT_PORT_VALID; ucI++)
    {
        SET_CABLE_STATUS_CHANGE(ucI, _FALSE);

        switch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)))
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

            case _A0_INPUT_PORT:

                if(GET_CABLE_DETECT(ucI) != GET_A0_CABLE_STATUS())
                {
                    ScalerTimerDelayXms(10);

                    SET_A0_CABLE_STATUS(!PCB_A0_PIN());

                    if(GET_CABLE_DETECT(ucI) != GET_A0_CABLE_STATUS())
                    {
                        SET_CABLE_DETECT(ucI, GET_A0_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Chanaged A0", ucI);
                    }
                }

                break;
#endif

#if(_A1_INPUT_PORT_TYPE != _A1_NO_PORT)

            case _A1_INPUT_PORT:

                if(GET_CABLE_DETECT(ucI) != GET_A1_CABLE_STATUS())
                {
                    ScalerTimerDelayXms(10);

                    SET_A1_CABLE_STATUS(!PCB_A1_PIN());

                    if(GET_CABLE_DETECT(ucI) != GET_A1_CABLE_STATUS())
                    {
                        SET_CABLE_DETECT(ucI, GET_A1_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Chanaged A1", ucI);
                    }
                }

                break;
#endif

#if(_A2_INPUT_PORT_TYPE != _A2_NO_PORT)

            case _A2_INPUT_PORT:

                if(GET_CABLE_DETECT(ucI) != GET_A2_CABLE_STATUS())
                {
                    ScalerTimerDelayXms(10);

                    SET_A2_CABLE_STATUS(!PCB_A2_PIN());

                    if(GET_CABLE_DETECT(ucI) != GET_A2_CABLE_STATUS())
                    {
                        SET_CABLE_DETECT(ucI, GET_A2_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Chanaged A2", ucI);
                    }
                }

                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

            case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS()) || (GET_D0_TMDS_MODE() != PCB_D0_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    SET_D0_CABLE_STATUS((!PCB_D0_PIN()) | PCB_D0_MHL_DETECT());
#else
                    SET_D0_CABLE_STATUS(!PCB_D0_PIN());
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS()) || (GET_D0_TMDS_MODE() != PCB_D0_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS())
#endif
                    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D0_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D0_TMDS_MODE(PCB_D0_MHL_DETECT());
#endif
                        if(GET_D0_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLModeMHLSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D0_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D0_INPUT_PORT, _DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D0_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D0_INPUT_PORT, _ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));
                            ScalerTMDSHotPlugEvent(_D0_INPUT_PORT);

#if((_D0_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D0_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            // HDCP2 Reset Proc
                            ScalerHdcp2ResetTMDSProc(_D0_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D0_INPUT_PORT);
                        }

#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)

                        if(GET_D0_CABLE_STATUS() == _TRUE)
                        {
#if((_D0_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D0_INPUT_PORT, _ENABLE);
#endif
                        }
                        else
                        {
#if((_D0_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D0_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            // HDCP2 Reset Proc
                            ScalerHdcp2ResetTMDSProc(_D0_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D0_INPUT_PORT);
                        }
#elif(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
                        if(GET_D0_CABLE_STATUS() != _TRUE)
                        {
                            ScalerTMDSHdcp1p4AksvClear(_D0_INPUT_PORT);
                        }
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D0_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D0", ucI);
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                        ScalerDpRestoreFakeLTLaneCount(_D0_INPUT_PORT);
#endif
                    }
                }

                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

            case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS()) || (GET_D1_TMDS_MODE() != PCB_D1_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    SET_D1_CABLE_STATUS((!PCB_D1_PIN()) | PCB_D1_MHL_DETECT());
#else
                    SET_D1_CABLE_STATUS(!PCB_D1_PIN());
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS()) || (GET_D1_TMDS_MODE() != PCB_D1_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS())
#endif
                    {
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D1_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D1_TMDS_MODE(PCB_D1_MHL_DETECT());
#endif
                        if(GET_D1_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLModeMHLSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D1_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D1_INPUT_PORT, _DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D1_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D1_INPUT_PORT, _ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));
                            ScalerTMDSHotPlugEvent(_D1_INPUT_PORT);

#if((_D1_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D1_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D1_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D1_INPUT_PORT);
                        }

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)

                        if(GET_D1_CABLE_STATUS() == _TRUE)
                        {
#if((_D1_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D1_INPUT_PORT, _ENABLE);
#endif
                        }
                        else
                        {
#if((_D1_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D1_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D1_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D1_INPUT_PORT);
                        }

#elif(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
                        if(GET_D1_CABLE_STATUS() != _TRUE)
                        {
                            ScalerTMDSHdcp1p4AksvClear(_D1_INPUT_PORT);
                        }
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D1_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D1", ucI);
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                        ScalerDpRestoreFakeLTLaneCount(_D1_INPUT_PORT);
#endif
                    }
                }

                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

            case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS()) || (GET_D2_TMDS_MODE() != PCB_D2_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    SET_D2_CABLE_STATUS((!PCB_D2_PIN()) | PCB_D2_MHL_DETECT());
#else
                    SET_D2_CABLE_STATUS(!PCB_D2_PIN());
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS()) || (GET_D2_TMDS_MODE() != PCB_D2_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS())
#endif
                    {
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D2_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D2_TMDS_MODE(PCB_D2_MHL_DETECT());
#endif
                        if(GET_D2_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLModeMHLSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D2_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D2_INPUT_PORT, _DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D2_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D2_INPUT_PORT, _ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));
                            ScalerTMDSHotPlugEvent(_D2_INPUT_PORT);

#if((_D2_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D2_INPUT_PORT, _ENABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D2_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D2_INPUT_PORT);
                        }

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT)

                        if(GET_D2_CABLE_STATUS() == _TRUE)
                        {
#if((_D2_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D2_INPUT_PORT, _ENABLE);
#endif
                        }
                        else
                        {
#if((_D2_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D2_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D2_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D2_INPUT_PORT);
                        }
#elif(_D2_INPUT_PORT_TYPE == _D2_DVI_PORT)
                        if(GET_D2_CABLE_STATUS() != _TRUE)
                        {
                            ScalerTMDSHdcp1p4AksvClear(_D2_INPUT_PORT);
                        }
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D2_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D2", ucI);
#if(_DP_RX_MI_DONGLE_SUPPORT == _ON)
                        ScalerDpRestoreFakeLTLaneCount(_D2_INPUT_PORT);
#endif
                    }
                }

                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

            case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS()) || (GET_D3_TMDS_MODE() != PCB_D3_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                    SET_D3_CABLE_STATUS((!PCB_D3_PIN()) | PCB_D3_MHL_DETECT());
#else
                    SET_D3_CABLE_STATUS(!PCB_D3_PIN());
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS()) || (GET_D3_TMDS_MODE() != PCB_D3_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS())
#endif
                    {
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D3_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D3_TMDS_MODE(PCB_D3_MHL_DETECT());
#endif
                        if(GET_D3_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLModeMHLSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D3_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D3_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));
                            ScalerTMDSHotPlugEvent(_D3_INPUT_PORT);

#if((_D3_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D3_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D3_INPUT_PORT);
                        }

#elif(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT)

                        if(GET_D3_CABLE_STATUS() == _TRUE)
                        {
#if((_D3_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _ENABLE);
#endif
                        }
                        else
                        {
#if((_D3_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D3_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D3_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D3_INPUT_PORT);
                        }
#elif(_D3_INPUT_PORT_TYPE == _D3_DVI_PORT)
                        if(GET_D3_CABLE_STATUS() != _TRUE)
                        {
                            ScalerTMDSHdcp1p4AksvClear(_D3_INPUT_PORT);
                        }
#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D3_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D3", ucI);
                    }
                }

                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS()) || (GET_D4_TMDS_MODE() != PCB_D4_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                    SET_D4_CABLE_STATUS((!PCB_D4_PIN()) | PCB_D4_MHL_DETECT());
#else
                    SET_D4_CABLE_STATUS(!PCB_D4_PIN());
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS()) || (GET_D4_TMDS_MODE() != PCB_D4_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS())
#endif
                    {
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D4_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D4_TMDS_MODE(PCB_D4_MHL_DETECT());
#endif
                        if(GET_D4_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLModeMHLSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D4_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D4_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));
                            ScalerTMDSHotPlugEvent(_D4_INPUT_PORT);

#if((_D4_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D4_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D4_INPUT_PORT);
                        }

#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT)

                        if(GET_D4_CABLE_STATUS() == _TRUE)
                        {
#if((_D4_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _ENABLE);
#endif
                        }
                        else
                        {
#if((_D4_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D4_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D4_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D4_INPUT_PORT);
                        }
#elif(_D4_INPUT_PORT_TYPE == _D4_DVI_PORT)
                        if(GET_D4_CABLE_STATUS() != _TRUE)
                        {
                            ScalerTMDSHdcp1p4AksvClear(_D4_INPUT_PORT);
                        }
#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D4_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D4", ucI);
                    }
                }

                break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_INPUT_PORT_TYPE)

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

            case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS()) || (GET_D5_TMDS_MODE() != PCB_D5_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                    SET_D5_CABLE_STATUS((!PCB_D5_PIN()) | PCB_D5_MHL_DETECT());
#else
                    SET_D5_CABLE_STATUS(!PCB_D5_PIN());
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS()) || (GET_D5_TMDS_MODE() != PCB_D5_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS())
#endif
                    {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D5_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D5_TMDS_MODE(PCB_D5_MHL_DETECT());
#endif
                        if(GET_D5_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLModeMHLSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D5_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D5_INPUT_PORT, _DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));

#if((_D5_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSHDMI2HPDRRIRQEnable(_D5_INPUT_PORT, _ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLModeHdmiSetting(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)));
                            ScalerTMDSHotPlugEvent(_D5_INPUT_PORT);

#if((_D5_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D5_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D5_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D5_INPUT_PORT);
                        }

#elif(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT)

                        if(GET_D5_CABLE_STATUS() == _TRUE)
                        {
#if((_D5_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D5_INPUT_PORT, _ENABLE);
#endif
                        }
                        else
                        {
#if((_D5_HDMI_2_0_SUPPORT == _ON) && (_TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT == _ON))
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSHDMI2HPDRRIRQEnable(_D5_INPUT_PORT, _DISABLE);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
                            ScalerHdcp2ResetTMDSProc(_D5_INPUT_PORT);
#endif
                            ScalerTMDSHdcp1p4AksvClear(_D5_INPUT_PORT);
                        }
#elif(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
                        if(GET_D5_CABLE_STATUS() != _TRUE)
                        {
                            ScalerTMDSHdcp1p4AksvClear(_D5_INPUT_PORT);
                        }
#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D5_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D5", ucI);
                    }
                }

                break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_INPUT_PORT_TYPE)

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)

            case _D6_INPUT_PORT:

                if(GET_CABLE_DETECT(ucI) != GET_D6_CABLE_STATUS())
                {
                    ScalerTimerDelayXms(10);

                    SET_D6_CABLE_STATUS(!PCB_D6_PIN());

                    if(GET_CABLE_DETECT(ucI) != GET_D6_CABLE_STATUS())
                    {
                        SET_CABLE_DETECT(ucI, GET_D6_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D6", ucI);
                    }
                }

                break;

#endif // End of #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)

            default:
                break;
        }
    }
}

#if(_DP_HDMI_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : HDMI +5V Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHdmi5VDetection(void)
{
#if(_D0_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceGetHdmi5VStatus(_D0_INPUT_PORT) == _TRUE)
        {
            if(GET_D0_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D0_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_RX0_HDMI_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D0_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D0_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX0_HDMI_HPD_ASSERTED);
                PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D0_HDMI_5V_STATUS();
        PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
    }
#endif

#if(_D1_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceGetHdmi5VStatus(_D1_INPUT_PORT) == _TRUE)
        {
            if(GET_D1_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D1_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_RX1_HDMI_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D1_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D1_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_HDMI_HPD_ASSERTED);
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D1_HDMI_5V_STATUS();
        PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
    }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceGetHdmi5VStatus(_D2_INPUT_PORT) == _TRUE)
        {
            if(GET_D2_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D2_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_RX2_HDMI_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D2_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D2_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_HDMI_HPD_ASSERTED);
                PCB_D2_HOTPLUG(_D2_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D2_HDMI_5V_STATUS();
        PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
    }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    if(GET_HDMI_HOTPLUG_TOGGLE() == _TRUE)
    {
        if(UserInterfaceGetHdmi5VStatus(_D3_INPUT_PORT) == _TRUE)
        {
            if(GET_D3_HDMI_5V_STATUS() == _FALSE)
            {
                SET_D3_HDMI_5V_STATUS();
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_RX3_HDMI_HPD_ASSERTED);
            }
        }
        else
        {
            if(GET_D3_HDMI_5V_STATUS() == _TRUE)
            {
                CLR_D3_HDMI_5V_STATUS();
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_HDMI_HPD_ASSERTED);
                PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
            }
        }
    }
    else
    {
        SET_D3_HDMI_5V_STATUS();
        PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
    }
#endif
}
#endif

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
//--------------------------------------------------
// Description  : Check auto-search status for embedded DP
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceCheckEmbeddedDpAutoSwitch(void)
{
    EnumSourceSearchPort enumCurrDpPort = SysSourceGetInputPort();

    if((GET_MODE_STATE() != _MODE_STATUS_SEARCH) &&
       (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
    {
        ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
        CLR_SOURCE_DP_SWITCH_TIMEOUT();
    }

    if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)) == _PORT_DP)
    {
        // Stop on currently-selected DP port
        if(enumCurrDpPort == GET_DP_EMBEDDED_SWITCH_SELECT())
        {
            return _TRUE;
        }

        // Switch to currently-selected DP port on non-polling mode or after timeout
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            SysSourceEmbeddedDpSwitch(enumCurrDpPort);
            CLR_DP_AUTO_SEARCH_SWITCH();

            return _TRUE;
        }
        else if(GET_SOURCE_DP_SWITCH_TIMEOUT() == _TRUE)
        {
            // Active DP switch timeout event
            ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
            CLR_SOURCE_DP_SWITCH_TIMEOUT();

            SysSourceEmbeddedDpSwitch(enumCurrDpPort);
            SET_DP_AUTO_SEARCH_SWITCH();

            return _TRUE;
        }
    }
    else
    {
        // Switch to user-selected DP port
        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
        {
            EnumSourceSearchPort enumUserPort = UserInterfaceGetDpSwitchSelectPort();

            if(enumUserPort != GET_DP_EMBEDDED_SWITCH_SELECT())
            {
                SysSourceEmbeddedDpSwitch(enumUserPort);
                CLR_DP_AUTO_SEARCH_SWITCH();
            }
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Switch embedded dp
// Input Value  : search port
// Output Value : None
//--------------------------------------------------
void SysSourceEmbeddedDpSwitch(EnumSourceSearchPort enumDpPort)
{
    ScalerDpVersionSwitch(enumDpPort, UserInterfaceGetDPVersion(enumDpPort), UserCommonInterfaceGetDpMstCapablePort());
    ScalerDpLaneCountSwitch(enumDpPort, UserInterfaceGetDpLaneCount(enumDpPort));

    ScalerDpSetHotPlugEvent(GET_DP_EMBEDDED_SWITCH_SELECT(), _DP_HPD_LOW);

    SET_DP_EMBEDDED_SWITCH_TARGET(enumDpPort);
}
#endif

//--------------------------------------------------
// Description  : Judge Source Search Times
// Input Value  : target search times
// Output Value : True --> search times of valid ports equal to target times
//--------------------------------------------------
bit SysSourceCheckTargetTimes(BYTE ucTargetTimes)
{
    BYTE ucCnt = 0x00;

    for(ucCnt = 0; ucCnt < _INPUT_PORT_VALID; ucCnt++)
    {
        if(GET_SOURCE_SEARCH_TIMES(ucCnt) != ucTargetTimes)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Scan Type for User
// Input Value  : Preferred Scan Type
// Output Value : None
//--------------------------------------------------
void SysSourceSetScanType(BYTE ucScanType)
{
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
#if(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_F)

    if(ucScanType == _SOURCE_SWITCH_HP_TIMING_CHANGE)
    {
        SET_SOURCE_HP_SOURCE_JUDGE();
    }

#endif
    if(ucScanType == _SOURCE_SWITCH_HP_SOURCE_SCAN)
    {
        CLR_SOURCE_HP_SOURCE_JUDGE();
    }
#endif

    SET_SOURCE_SCAN_TYPE(ucScanType);
}

//--------------------------------------------------
// Description  : Get Scan Type for User
// Input Value  : None
// Output Value : Current Scan Type
//--------------------------------------------------
BYTE SysSourceGetScanType(void)
{
    return GET_SOURCE_SCAN_TYPE();
}

//--------------------------------------------------
// Description  : Convert Search Port to Search Index
// Input Value  : Input Port
// Output Value : Search Index
//--------------------------------------------------
BYTE SysSourceConvertSearchPort(BYTE ucInputPort)
{
    BYTE ucTemp = 0;

    while(ucTemp < _INPUT_PORT_VALID)
    {
        if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucTemp)) == ucInputPort)
        {
            return ucTemp;
        }

        ucTemp++;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Source Cable Detect
// Input Value  : ucInputPort
// Output Value : _TRUE => Cable Detected, _FASLE => Cable Undected
//--------------------------------------------------
bit SysSourceGetCableDetect(BYTE ucInputPort)
{
    return GET_CABLE_DETECT(SysSourceConvertSearchPort(ucInputPort));
}

//--------------------------------------------------
// Description  : Get Source Cable Status Change
// Input Value  : ucInputPort
// Output Value : _TRUE => Cable Status Changed
//--------------------------------------------------
bit SysSourceGetCableStatusChange(BYTE ucInputPort)
{
    return GET_CABLE_STATUS_CHANGE(SysSourceConvertSearchPort(ucInputPort));
}

//--------------------------------------------------
// Description  : Source Reset when Cable Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceCableResetProc(void)
{
    switch(GET_SOURCE_SCAN_TYPE())
    {
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SOURCE_SWITCH:
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_TIMING_CHANGE)
            {
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);
            }

            SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Source First Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceFirstActiveProc(void)
{
    switch(GET_SOURCE_SCAN_TYPE())
    {
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SOURCE_SWITCH:
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Source Power Off Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourcePowerOffProc(void)
{
    switch(GET_SOURCE_SCAN_TYPE())
    {
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)

        case _SOURCE_SWITCH_HP_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SOURCE_SWITCH:
        case _SOURCE_SWITCH_HP_TIMING_CHANGE:
        case _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN:
        case _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT:
        case _SOURCE_SWITCH_HP_SCAN_NEXT_PORT:

            CLR_SOURCE_HP_SOURCE_JUDGE();

            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_HP_SOURCE_SCAN);

            CLR_SOURCE_HP_TIMING_CHANGE();

            CLR_SOURCE_HP_SWITCH_NO_CABLE();

            CLR_SOURCE_HP_TARGET_NO_SIGNAL();

            g_ucSearchIndex = 0;

#if(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_E)
            SET_SOURCE_HP_TARGET_SEARCH_TIMES(3);
#elif(_HP_SOURCE_SCAN_TYPE == _HP_SOURCE_SCAN_TYPE_F)
            SET_SOURCE_HP_TARGET_SEARCH_TIMES(1);
            CLR_SOURCE_HP_FROM_TIMING_CHANGE();
#endif

            SET_SOURCE_HP_PORT_SWITCH_TARGET((_INPUT_PORT_VALID + 1));

            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_HP_CANCEL_MANUAL_SWITCH_PORT);

            break;
#endif
        default:

            if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
            {
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
            }
            else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
            {
                SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
            }

            g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT));

#if((_DP_HDMI_COMPATIBLE_MODE == _ON) && (_DIGITAL_PORT_SUPPORT == _ON))

            if(GET_HDMI_HOTPLUG_TOGGLE() == _OFF)
            {
                if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))) == _D0_INPUT_PORT)
                {
                    CLR_DIGITAL_PORT_SWITCH_TO_D0();
                    SET_DIGITAL_PORT_SWITCH_TO_D1();
                    SET_DIGITAL_PORT_SWITCH_TO_D2();
                    SET_DIGITAL_PORT_SWITCH_TO_D3();
                }
                else if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))) == _D1_INPUT_PORT)
                {
                    SET_DIGITAL_PORT_SWITCH_TO_D0();
                    CLR_DIGITAL_PORT_SWITCH_TO_D1();
                    SET_DIGITAL_PORT_SWITCH_TO_D2();
                    SET_DIGITAL_PORT_SWITCH_TO_D3();
                }
                else if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))) == _D2_INPUT_PORT)
                {
                    SET_DIGITAL_PORT_SWITCH_TO_D0();
                    SET_DIGITAL_PORT_SWITCH_TO_D1();
                    CLR_DIGITAL_PORT_SWITCH_TO_D2();
                    SET_DIGITAL_PORT_SWITCH_TO_D3();
                }
                else if((GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))) == _D3_INPUT_PORT)
                {
                    SET_DIGITAL_PORT_SWITCH_TO_D0();
                    SET_DIGITAL_PORT_SWITCH_TO_D1();
                    SET_DIGITAL_PORT_SWITCH_TO_D2();
                    CLR_DIGITAL_PORT_SWITCH_TO_D3();
                }
            }
#endif
            break;
    }

#if((_HP_SOURCE_SCAN_SUPPORT == _ON) && (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
    CLR_SOURCE_HP_DETECTING();
#endif
}

//--------------------------------------------------
// Description  : Input Port Search Priority Select
// Input Value  : Priority and Input Port
// Output Value : None
//--------------------------------------------------
void SysSourceSetSearchPriority(EnumSourceSearchPort enumPort, EnumSourceSearchPortPriority enumSourcePriority)
{
    BYTE ucSearchIndexBackup = SysSourceConvertSearchPort(enumPort);
    BYTE ucInputPortBackup = SysSourceGetSpecificInputPort(enumSourcePriority);

    if((enumSourcePriority >= _INPUT_PORT_PRIORITY_NONE) || (enumPort >= _NO_INPUT_PORT) || (ucSearchIndexBackup == enumSourcePriority))
    {
        return;
    }

    SET_SOURCE_TYPE_BACKUP(GET_SOURCE_TYPE(enumSourcePriority));
    SET_SOURCE_SEARCH_TIMES_BACKUP(GET_SOURCE_SEARCH_TIMES(enumSourcePriority));
    SET_SOURCE_JUDGE_BACKUP(GET_SOURCE_JUDGE(enumSourcePriority));
    SET_SOURCE_PREDETECT_BACKUP(GET_SOURCE_PREDETECT(enumSourcePriority));
    SET_CABLE_DETECT_BACKUP(GET_CABLE_DETECT(enumSourcePriority));

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    SET_TYPE_C_ALT_MODE_DETECT_BACKUP(GET_TYPE_C_ALT_MODE_DETECT(enumSourcePriority));
#endif

    SET_CABLE_STATUS_CHANGE_BACKUP(GET_CABLE_STATUS_CHANGE(enumSourcePriority));

    SET_SOURCE_TYPE(enumSourcePriority, GET_SOURCE_TYPE(ucSearchIndexBackup));
    SET_SOURCE_SEARCH_TIMES(enumSourcePriority, GET_SOURCE_SEARCH_TIMES(ucSearchIndexBackup));
    SET_SOURCE_JUDGE(enumSourcePriority, GET_SOURCE_JUDGE(ucSearchIndexBackup));
    SET_SOURCE_PREDETECT(enumSourcePriority, GET_SOURCE_PREDETECT(ucSearchIndexBackup));
    SET_CABLE_DETECT(enumSourcePriority, GET_CABLE_DETECT(ucSearchIndexBackup));

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    SET_TYPE_C_ALT_MODE_DETECT(enumSourcePriority, GET_TYPE_C_ALT_MODE_DETECT(ucSearchIndexBackup));
#endif

    SET_CABLE_STATUS_CHANGE(enumSourcePriority, GET_CABLE_STATUS_CHANGE(ucSearchIndexBackup));

    SET_SOURCE_TYPE(ucSearchIndexBackup, GET_SOURCE_TYPE_BACKUP());
    SET_SOURCE_SEARCH_TIMES(ucSearchIndexBackup, GET_SOURCE_SEARCH_TIMES_BACKUP());
    SET_SOURCE_JUDGE(ucSearchIndexBackup, GET_SOURCE_JUDGE_BACKUP());
    SET_SOURCE_PREDETECT(ucSearchIndexBackup, GET_SOURCE_PREDETECT_BACKUP());
    SET_CABLE_DETECT(ucSearchIndexBackup, GET_CABLE_DETECT_BACKUP());

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
    SET_TYPE_C_ALT_MODE_DETECT(ucSearchIndexBackup, GET_TYPE_C_ALT_MODE_DETECT_BACKUP());
#endif

    SET_CABLE_STATUS_CHANGE(ucSearchIndexBackup, GET_CABLE_STATUS_CHANGE_BACKUP());

    if(enumSourcePriority == g_ucSearchIndex)
    {
        g_ucSearchIndex = ucSearchIndexBackup;
    }
    else if(ucSearchIndexBackup == g_ucSearchIndex)
    {
        g_ucSearchIndex = enumSourcePriority;
    }

    g_pucSourceSearchPriority[enumSourcePriority] = enumPort;
    g_pucSourceSearchPriority[ucSearchIndexBackup] = ucInputPortBackup;
}

//--------------------------------------------------
// Description  : Input Port Search Group Select
// Input Value  : Group and Input Port
// Output Value : None
//--------------------------------------------------
void SysSourceSetSearchGroup(EnumSourceSearchPort enumPort, EnumSourceSearchGroup enumSourceGroup)
{
    if((enumPort >= _NO_INPUT_PORT) || (enumSourceGroup >= _INPUT_PORT_GROUP_NONE))
    {
        return;
    }

    g_pucSourceSearchGroup[enumPort] = enumSourceGroup;
}

//--------------------------------------------------
// Description  : Input Port Default Search Time Setting
// Input Value  : enumInputType --> VGA/HDMI/DVI/DP
///               usDefaultSearchTime --> Default Search Time
// Output Value : None
//--------------------------------------------------
void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime)
{
    switch(enumInputType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_VGA:
            g_usSourceDefaultSearchTimeVga = usDefaultSearchTime;
            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_HDMI:
            g_usSourceDefaultSearchTimeHdmi = usDefaultSearchTime;
            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DVI:
            g_usSourceDefaultSearchTimeDvi = usDefaultSearchTime;
            break;
#endif

#if(_DP_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DP:
            g_usSourceDefaultSearchTimeDp = usDefaultSearchTime;
            break;

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_TYPE_C:
            g_usSourceDefaultSearchTimeTypeC = usDefaultSearchTime;
            break;
#endif
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Input Port No Cable Search Time Setting
// Input Value  : enumInputType --> VGA/HDMI/DVI/DP
///               usNoCableSearchTime --> No Cable Search Time
// Output Value : None
//--------------------------------------------------
void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime)
{
    switch(enumInputType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_VGA:
            g_usSourceNoCableSearchTimeVga = usNoCableSearchTime;
            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_HDMI:
            g_usSourceNoCableSearchTimeHdmi = usNoCableSearchTime;
            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DVI:
            g_usSourceNoCableSearchTimeDvi = usNoCableSearchTime;
            break;
#endif

#if(_DP_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DP:
            g_usSourceNoCableSearchTimeDp = usNoCableSearchTime;
            break;

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
        case _SOURCE_INPUT_TYPE_TYPE_C:
            g_usSourceNoCableSearchTimeTypeC = usNoCableSearchTime;
            break;
#endif
#endif

        default:
            break;
    }
}

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check Type C Cable Status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
EnumTypeCCableStatus SysSourceGetTypeCCableStatusChange(void)
{
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    if(GET_CABLE_STATUS_CHANGE(SysSourceConvertSearchPort(_D0_INPUT_PORT)) == _TRUE)
    {
        if(GET_CABLE_DETECT(SysSourceConvertSearchPort(_D0_INPUT_PORT)) == _TRUE)
        {
            return _TYPE_C_CABLE_PLUG;
        }
        else
        {
            return _TYPE_C_CABLE_UNPLUG;
        }
    }
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    if(GET_CABLE_STATUS_CHANGE(SysSourceConvertSearchPort(_D1_INPUT_PORT)) == _TRUE)
    {
        if(GET_CABLE_DETECT(SysSourceConvertSearchPort(_D1_INPUT_PORT)) == _TRUE)
        {
            return _TYPE_C_CABLE_PLUG;
        }
        else
        {
            return _TYPE_C_CABLE_UNPLUG;
        }
    }
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    if(GET_CABLE_STATUS_CHANGE(SysSourceConvertSearchPort(_D6_INPUT_PORT)) == _TRUE)
    {
        if(GET_CABLE_DETECT(SysSourceConvertSearchPort(_D6_INPUT_PORT)) == _TRUE)
        {
            return _TYPE_C_CABLE_PLUG;
        }
        else
        {
            return _TYPE_C_CABLE_UNPLUG;
        }
    }
#endif
    return _TYPE_C_CABLE_UNCHANGE;
}
#endif

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
//--------------------------------------------------
// Description  : Eizo Power Saving Support Selection
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void SysSourceEizoSetPowerSavingSupport(bit bOn)
{
    if(bOn == _ON)
    {
        SET_SOURCE_EIZO_PS_SUPPORT();
    }
    else
    {
        CLR_SOURCE_EIZO_PS_SUPPORT();
    }
}

//--------------------------------------------------
// Description  : Report SysSource Search Finish Flag
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceGetSourceSwitchFinish(void)
{
    return GET_SOURCE_SWITCH_FINISH();
}

//--------------------------------------------------
// Description  : Reactive Total Search time
// Input Value  : usTime    --> Unit in 1ms, range in 0.01 ~ 61 sec
// Output Value : None
//--------------------------------------------------
void SysSourceEizoReactiveTotalSearchTime(WORD usTime)
{
    WORD usSearchTime = 0;

    switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
    {
#if(_VGA_PORT_EXIST == _ON)
        case _PORT_VGA:
            usSearchTime = g_usSourceDefaultSearchTimeVga;
            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _PORT_HDMI:
        case _PORT_MHL:
            usSearchTime = g_usSourceDefaultSearchTimeHdmi;
            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _PORT_DVI:
        case _PORT_DUAL_DVI:
            usSearchTime = g_usSourceDefaultSearchTimeDvi;
            break;
#endif

#if(_DP_PORT_EXIST == _ON)
        case _PORT_DP:
            usSearchTime = g_usSourceDefaultSearchTimeDp;
            break;
#endif

        default:
            break;
    }

    if(usTime <= usSearchTime)
    {
        ScalerTimerReactiveTimerEvent(GET_SOURCE_EIZO_EVENT_TIME(), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }
    else
    {
        ScalerTimerReactiveTimerEvent(usTime, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

        PDATA_WORD(0) = ScalerTimerGetEventRemainTime(_SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);

        ScalerTimerReactiveTimerEvent((PDATA_WORD(0) + (usTime - GET_SOURCE_EIZO_EVENT_TIME())), _SYSTEM_TIMER_EVENT_SOURCE_EIZO_SEARCH_FINISH);
    }
}
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HP Source Judge Flag
// Input Value  : None
// Output Value : True --> HP Judge
//--------------------------------------------------
bit SysSourceHpGetSourceJudge(void)
{
    return (bit)GET_SOURCE_HP_SOURCE_JUDGE();
}

//--------------------------------------------------
// Description  : Get Target Source Type
// Input Value  : Target SearchIndex
// Output Value : Target Souce Type
//--------------------------------------------------
BYTE SysSourceHpGetTargetSourceType(BYTE ucSearchIndex)
{
    return GET_SOURCE_TYPE(ucSearchIndex);
}

//--------------------------------------------------
// Description  : Get Target Source Search Times
// Input Value  : None
// Output Value : Target Source Search Times
//--------------------------------------------------
BYTE SysSourceHpGetTargetSearchTimes(void)
{
    return GET_SOURCE_HP_TARGET_SEARCH_TIMES();
}

//--------------------------------------------------
// Description  : Get Switch Port Cable Status
// Input Value  : None
// Output Value : True --> No Cable
//--------------------------------------------------
bit SysSourceHpGetSwitchPortNoCable(void)
{
    return GET_SOURCE_HP_SWITCH_NO_CABLE();
}

//--------------------------------------------------
// Description  : Get Switch Port Nosignal Status
// Input Value  : None
// Output Value : True --> Show Monitor Status
//--------------------------------------------------
bit SysSourceHpGetTargetPortNoSignal(void)
{
    return GET_SOURCE_HP_TARGET_NO_SIGNAL();
}

//--------------------------------------------------
// Description  : Get HP Monitor Status Check Is Processing or Not
// Input Value  : None
// Output Value : True --> HP Monitor Status Check Is Processing
//--------------------------------------------------
bit SysSourceHpGetMonitorStatusCheckProcessing(void)
{
    if((GET_MODE_STATE() == _MODE_STATUS_SEARCH) &&
       ((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_SOURCE_SCAN) ||
        (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN) ||
        (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT) ||
        (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_HP_SCAN_NEXT_PORT)))
    {
        if((SysSourceCheckTargetTimes(1) == _FALSE) && (GET_SOURCE_HP_SOURCE_JUDGE() == _FALSE))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Port Switch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBgSwitchPort(void)
{
    BYTE ucCount = 0;
    BYTE ucBackupSearchIndex = g_ucBgDetectIndex;

    do
    {
        g_ucBgDetectIndex = (g_ucBgDetectIndex + 1) % _INPUT_PORT_VALID;

        if(g_ucBgDetectIndex < g_ucSearchIndex)
        {
            break;
        }

        ucCount++;
    }
    while(ucCount < _INPUT_PORT_VALID);

    if(g_ucBgDetectIndex != ucBackupSearchIndex)
    {
        SET_SOURCE_SEARCH_TIME_INITIAL();

        SET_SOURCE_SEARCH_PORT_INITIAL();

        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

        SET_SOURCE_SEARCH_TIME_REACTIVE();
    }
}

//--------------------------------------------------
// Description  : Judge if the port with source will be chosen
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceBgJudge(void)
{
    if(GET_SOURCE_TYPE(g_ucBgDetectIndex) != _SOURCE_NONE)
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

        // Choose Current Source to proceed
        SET_SOURCE_BG_JUDGE(g_ucBgDetectIndex, _TRUE);

        DebugMessageSystem("Background source judge!!", g_ucBgDetectIndex);
    }
    else if(GET_SOURCE_PREDETECT(g_ucBgDetectIndex) == _TRUE)
    {
        if(GET_SOURCE_SEARCH_TIME_REACTIVE() == _TRUE)
        {
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

            SET_SOURCE_DETECTING();

            SET_SOURCE_SEARCH_TIME_INITIAL();

            SET_SOURCE_SEARCH_PORT_INITIAL();

            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

            CLR_SOURCE_SEARCH_TIME_REACTIVE();
        }
    }
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : None
// Output Value : ucInputPort --> Input Port
//--------------------------------------------------
BYTE SysSourceBgGetInputPort(void)
{
    return SysSourceGetSpecificInputPort(g_ucBgDetectIndex);
}

//--------------------------------------------------
// Description  : Get Background Detection Judge or Not
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysSourceBgGetJudge(void)
{
    return GET_SOURCE_BG_JUDGE(g_ucBgDetectIndex);
}
#endif
