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
// ID Code      : SysMain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __MAIN__

#include "SysInclude.h"

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
void main(void);
void SysMainSystemInitial(void);
bit SysMainSytemPowerDetect(void);

#if(_ALS_TYPE != _SENSER_NONE)
void SysMainAlsHandler(void);
#endif

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
void SysMainBackLightSensorHandler(void);
#endif

#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
void SysMainStartUserCode(BYTE ucBankAddress);
#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
void SysMainPictureInit(void);
void SysMainPictureHandler(void);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : The main function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void main(void)
{
    do
    {
        SysMainSystemInitial();

        while(SysMainSytemPowerDetect() == _TRUE)
        {
            UserInterfaceKeyHandler();
            SysPowerHandler();
            SysJudgeHandler();

#if(_ALS_TYPE != _SENSER_NONE)
            SysMainAlsHandler();            
#endif

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
            SysMainBackLightSensorHandler();
#endif

#if(_AUDIO_SUPPORT == _ON)
            SysAudioHandler();
#endif
            SysTimerHandler();
            SysSourceHandler();
            SysModeHandler();

#if(_MHL_SUPPORT == _ON)
            SysMHLMscHandler();
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCHandler();

#endif

#if(_DP_SUPPORT == _ON)
            SysDpRxHandler();
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
            SysTMDSRxHandler();

#if(_HDMI_CEC_SUPPORT == _ON)
            SysCecHandler();
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
            SysDpTxHandler();
#endif

#if(_EMBEDDED_DP_TX_SUPPORT == _ON)
            SysDpEmbeddedTxHandler();
#endif

#if(_DP_MST_SUPPORT == _ON)
            SysDpMstHandler();
#endif

#if(_HDMI_TX_SUPPORT == _ON)
            SysHdmiTxHandler();
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
            ScalerHdcp2Handler();
#endif

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
            ScalerBBHandler();
#endif

#if(_AUTO_TEST_SUPPORT == _ON)
            SysAutotestHandler();
#endif

            UserCommonInterfaceOsdHandler();

#if(_DDCCI_CODE_REDUCTION == _OFF)
            UserCommonDdcciHandler();
#endif
            SysColorHandler();
            ScalerDebug();

#if(_CUSTOMER == _CUS_TOSHIBA)
            SysMainPictureHandler(); 
#endif            
        }
    }
    while(_TRUE);
}

//--------------------------------------------------
// Description  : System AC on initial flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainSystemInitial(void)
{
#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) &&\
    (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
    ScalerMcuBootInitial();

    SysMainStartUserCode(UserInterfaceGetUserCodeLocation());
#endif

    ScalerMcuInitial();

    ScalerPinshareInitial();

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_EXTERNAL)

    UserCommonSignExterMoveKey();

#elif(_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL)

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
    UserCommonSignHandler();
    SysMainStartUserCode(UserCommonSignGetSwitchUserBank());
#elif(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
    UserCommonSignInterMoveKey();
#endif

#endif

    ScalerTimerInitialTimerEvent();

    UserCommonInterfaceInitial();

    ScalerMcuDdcRamEnable();

    SysSourceInitial();

    SysPowerInitial();

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    ScalerIRHWModeInitial();
#endif

#if(_ALS_TYPE != _SENSER_NONE)
    ALS_Initial();
#endif

#if(_BACKLIGHT_SENSOR == _ON)
    InitTsl2561();
#elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
    InitBacklightSensor();
#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
    SysMainPictureInit();
#endif

    SET_POWER_STATUS(_POWER_STATUS_AC_ON);

    if(UserCommonNVRamGetSystemData(_MONITOR_POWER_STATUS) == _ON)
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
    }
    else
    {
        SET_TARGET_POWER_STATUS(_POWER_STATUS_OFF);
    }
    SET_MODE_STATE(_MODE_STATUS_POWER_OFF);
}

//--------------------------------------------------
// Description  : System power detect
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysMainSytemPowerDetect(void)
{
    return PCB_POWER_5V_DETECT();
}

#if(_ALS_TYPE != _SENSER_NONE)
void SysMainAlsHandler(void)
{
    if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
        ScalerTimerActiveTimerEvent(SEC(0.04), _USER_TIMER_EVENT_ALS_ADJUST);
}
#endif

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
void SysMainBackLightSensorHandler(void)
{
    if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
    {
#if(_BACKLIGHT_SENSOR == _ON)    
        ScalerTimerActiveTimerEvent(SEC(0.04), _USER_TIMER_EVENT_BACKLIGHTSENSOR_ADJUST);
#elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
        ScalerTimerActiveTimerEvent(SEC(0.2), _USER_TIMER_EVENT_BACKLIGHTSENSOR_ADJUST);
#endif
    }
}
#endif


#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
//--------------------------------------------------
// Description  : Switch bank and jump to user code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMainStartUserCode(BYTE ucBankAddress)
{
#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
    // Set bank offset for user code
    SET_BANK_SWITCH_OFFSET(ucBankAddress);
#endif

    // Switch current bank
    MCU_FFFF_PBANK_SWITCH = ucBankAddress;

    // The below code is used here to ignore the pre-read code of mcu
    _nop_();
    _nop_();
    _nop_();
    _nop_();

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
    // Reset FW after switched to user code
    ((void (*)(void))0x0000)();
#endif
}
#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
bit g_bDVIPin20CurState = 0;
bit g_bDVIPin20PreState = 0;

void SysMainPictureInit(void)
{
    g_bDVIPin20PreState = g_bDVIPin20CurState = bPin20DVI;
    if(g_bDVIPin20CurState == _HIGH)
        Set_1600_1024_State(_ON);
    else
        Set_1600_1024_State(_OFF);
}

void SysMainPictureHandler(void)
{
#if(TOSHIBA_DC_POWER == _OFF)
    if(UserInterfaceGetAspectRatioType() == _ASPECT_RATIO_1280x1024)
    {
        if(((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 1024)) || \
            ((GET_INPUT_TIMING_HWIDTH() == 1600) && (GET_INPUT_TIMING_VHEIGHT() == 900)))
        {
            if(GET_MODE_STATE() == _MODE_STATUS_ACTIVE)
            {
                g_bDVIPin20CurState = bPin20DVI;
                if(g_bDVIPin20CurState != g_bDVIPin20PreState)
                {
                    g_bDVIPin20PreState = g_bDVIPin20CurState;
                    if(g_bDVIPin20CurState == _HIGH)
                        Set_1600_1024_State(_ON);
                    else
                        Set_1600_1024_State(_OFF);

#if(_ASPECT_RATIO_SUPPORT == _ON)
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
                }
            }
        }
    }
#endif 
}

#endif

