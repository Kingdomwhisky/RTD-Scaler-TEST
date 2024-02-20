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
// ID Code      : NoneOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_OSD__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_OSD)

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
StructOsdInfo g_stOsdInfo;
BYTE g_ucLogoTimerCounter;

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
BYTE g_ucUartKeyState;
#endif

BYTE g_stSourceList[_INPUT_PORT_VALID];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserOsdHandler(void);
void NoneOsdSystemFlowProc(void);
void NoneOsdEventMsgProc(void);
bit BeaconCheckSourceValid(EnumSourceSearchPort ucPort);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserOsdHandler(void)
{
    NoneOsdSystemFlowProc();
    NoneOsdEventMsgProc();
}

//--------------------------------------------------
// Description  : OSD system flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneOsdSystemFlowProc(void)
{
#if (_USER_SHOW_DEBUG_OSD == _ON)

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
    g_ucDebugValue[0] = (BYTE)((GET_TARGET_SENSOR() >> 8) & 0x00FF);
    g_ucDebugValue[8] = (BYTE)(GET_TARGET_SENSOR() & 0x00FF);

    g_ucDebugValue[1] = (BYTE)(GET_SENSOR_BACKLIGHT()>>8);
    g_ucDebugValue[9] = (BYTE)(GET_SENSOR_BACKLIGHT()&0xFF);

    g_ucDebugValue[3] = (BYTE)(GET_CURRENT_SENSOR()>>8);
    g_ucDebugValue[11] = (BYTE)(GET_CURRENT_SENSOR()&0xFF);    

    g_ucDebugValue[4] = (BYTE)(Get12BitPwmDuty()>>8);
    g_ucDebugValue[12] = (BYTE)(Get12BitPwmDuty()&0xFF); 

    g_ucDebugValue[5] = (BYTE)((GetDifferencePwmValue() + 0x800)>>8);
    g_ucDebugValue[13] = (BYTE)((GetDifferencePwmValue() + 0x800)&0xFF);

#endif

    if((g_ucBeaconFacOsdShowFlag == _OFF) && (GET_OSD_STATE() == _BEACON_OSD_NONE))
    {
        /*
        BeaconFactoryFuncLoadText(2, 0, 0, BeaconDebugShowHex(g_ucDdcciRxBuf[1]));
        BeaconFactoryFuncLoadText(3, 0, 0, BeaconDebugShowHex(g_ucDdcciRxBuf[2]));
        BeaconFactoryFuncLoadText(4, 0, 0, BeaconDebugShowHex(g_ucDdcciRxBuf[3]));
        BeaconFactoryFuncLoadText(5, 0, 0, BeaconDebugShowHex(g_ucDdcciRxBuf[4]));
        BeaconFactoryFuncLoadText(6, 0, 0, BeaconDebugShowHex(g_ucDdcciRxBuf[5]));
        BeaconFactoryFuncLoadText(7, 0, 0, BeaconDebugShowHex(g_ucDdcciRxBuf[6]));
        BeaconFactoryFuncLoadText(8, 0, 0, BeaconDebugShowHex(g_ucDdcciRxBuf[7]));*/
        //BeaconFactoryFuncLoadText(8, 10, 0, BeaconDebugShowHex(GET_CHECK_STATE()));
        //COL0	
        BeaconFactoryFuncLoadText(0, 0, 0, BeaconDebugShowHex(g_ucDebugValue[0]));
        BeaconFactoryFuncLoadText(1, 0, 0, BeaconDebugShowHex(g_ucDebugValue[1]));
        BeaconFactoryFuncLoadText(2, 0, 0, BeaconDebugShowHex(g_ucDebugValue[2]));
        BeaconFactoryFuncLoadText(3, 0, 0, BeaconDebugShowHex(g_ucDebugValue[3]));
        BeaconFactoryFuncLoadText(4, 0, 0, BeaconDebugShowHex(g_ucDebugValue[4]));
        BeaconFactoryFuncLoadText(5, 0, 0, BeaconDebugShowHex(g_ucDebugValue[5]));
        BeaconFactoryFuncLoadText(6, 0, 0, BeaconDebugShowHex(g_ucDebugValue[6]));
        BeaconFactoryFuncLoadText(7, 0, 0, BeaconDebugShowHex(g_ucDebugValue[7]));
        //COL1	
        BeaconFactoryFuncLoadText(0, 5, 0, BeaconDebugShowHex(g_ucDebugValue[8]));
        BeaconFactoryFuncLoadText(1, 5, 0, BeaconDebugShowHex(g_ucDebugValue[9]));
        BeaconFactoryFuncLoadText(2, 5, 0, BeaconDebugShowHex(g_ucDebugValue[10]));
        BeaconFactoryFuncLoadText(3, 5, 0, BeaconDebugShowHex(g_ucDebugValue[11]));
        BeaconFactoryFuncLoadText(4, 5, 0, BeaconDebugShowHex(g_ucDebugValue[12]));
        BeaconFactoryFuncLoadText(5, 5, 0, BeaconDebugShowHex(g_ucDebugValue[13]));
        BeaconFactoryFuncLoadText(6, 5, 0, BeaconDebugShowHex(g_ucDebugValue[14]));
        BeaconFactoryFuncLoadText(7, 5, 0, BeaconDebugShowHex(g_ucDebugValue[15]));
        //COL2	
        BeaconFactoryFuncLoadText(0, 10, 0, BeaconDebugShowHex(g_ucDebugValue[16]));
        BeaconFactoryFuncLoadText(1, 10, 0, BeaconDebugShowHex(g_ucDebugValue[17]));
        BeaconFactoryFuncLoadText(2, 10, 0, BeaconDebugShowHex(g_ucDebugValue[18]));
        BeaconFactoryFuncLoadText(3, 10, 0, BeaconDebugShowHex(g_ucDebugValue[19]));
        BeaconFactoryFuncLoadText(4, 10, 0, BeaconDebugShowHex(g_ucDebugValue[20]));
        BeaconFactoryFuncLoadText(5, 10, 0, BeaconDebugShowHex(g_ucDebugValue[21]));
        BeaconFactoryFuncLoadText(6, 10, 0, BeaconDebugShowHex(g_ucDebugValue[22]));
        BeaconFactoryFuncLoadText(7, 10, 0, BeaconDebugShowHex(g_ucDebugValue[23]));
        //COL3	
        BeaconFactoryFuncLoadText(0, 15, 0, BeaconDebugShowHex(g_ucDebugValue[24]));
        BeaconFactoryFuncLoadText(1, 15, 0, BeaconDebugShowHex(g_ucDebugValue[25]));
        BeaconFactoryFuncLoadText(2, 15, 0, BeaconDebugShowHex(g_ucDebugValue[26]));
        BeaconFactoryFuncLoadText(3, 15, 0, BeaconDebugShowHex(g_ucDebugValue[27]));
        BeaconFactoryFuncLoadText(4, 15, 0, BeaconDebugShowHex(g_ucDebugValue[28]));
        BeaconFactoryFuncLoadText(5, 15, 0, BeaconDebugShowHex(g_ucDebugValue[29]));
        BeaconFactoryFuncLoadText(6, 15, 0, BeaconDebugShowHex(g_ucDebugValue[30]));
        BeaconFactoryFuncLoadText(7, 15, 0, BeaconDebugShowHex(g_ucDebugValue[31]));
        //COL4	
        BeaconFactoryFuncLoadText(0, 20, 0, BeaconDebugShowHex(g_ucDebugValue[32]));
        BeaconFactoryFuncLoadText(1, 20, 0, BeaconDebugShowHex(g_ucDebugValue[33]));
        BeaconFactoryFuncLoadText(2, 20, 0, BeaconDebugShowHex(g_ucDebugValue[34]));
        BeaconFactoryFuncLoadText(3, 20, 0, BeaconDebugShowHex(g_ucDebugValue[35]));
        BeaconFactoryFuncLoadText(4, 20, 0, BeaconDebugShowHex(g_ucDebugValue[36]));
        BeaconFactoryFuncLoadText(5, 20, 0, BeaconDebugShowHex(g_ucDebugValue[37]));
        BeaconFactoryFuncLoadText(6, 20, 0, BeaconDebugShowHex(g_ucDebugValue[38]));
        BeaconFactoryFuncLoadText(7, 20, 0, BeaconDebugShowHex(g_ucDebugValue[39]));


        //BeaconFactoryFuncLoadText(10, 0, 0, BeaconDebugShowHex(g_ucPraStatus));
        BeaconFactoryFuncLoadText(11, 0, 0, BeaconDebugShowHex(g_ucDebugValue[39]));
    }

    if((SysModeGetModeState()>=_MODE_STATUS_ACTIVE)&&(SysModeGetModeState()<=_MODE_STATUS_POWER_SAVING)&&(SysModeGetModeStateChange()== _TRUE))   
    {
        BeaconDebugOsdInitial();
    }

#endif

    if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
    {
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
        BeaconFactoryDdcciCommand();
#endif
        if(SysModeGetModeStateChange() == _TRUE)
        {
            RTDNVRamSaveOSDData();
        }
    }

    switch(SysPowerGetPowerStatus())
    {
        case _POWER_STATUS_OFF:
#if(_CUSTOMER == _CUS_TOSHIBA)
            ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_POWER_OFF_LED_INVERT);            
#endif
            break;

        case _POWER_STATUS_SAVING:

            break;

        case _POWER_STATUS_NORMAL:

            break;

        default:

            break;
    }

#if((Dynamic_Show_NoSignal_NoSupport == _ON) && (_USER_SHOW_DEBUG_OSD == _OFF))
    if(SysModeGetModeStateChange() == _TRUE)
    {
        if((SysModeGetModeState() != _MODE_STATUS_SEARCH)&&(SysModeGetModeState() != _MODE_STATUS_NOSIGNAL))
        {
            if((GET_OSD_STATE() - (_PAGE2_AMOUNT + 1)) != _BEACON_ADVANCED_OSD_COLOR_1)
            {
                SET_OSD_ITEM_INDEX(0);
                ScalerOsdDisableOsd();
                BeaconFuncCloseWindow(_OSD_WINDOW_ALL);
                SET_OSD_STATE(_BEACON_OSD_NONE);
                g_ucOsdWidth = 0;
                g_ucOsdHeight = 0;
                DebugMessageSystem("CancelTimer SHOW_NO_SIGNAL",0);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_SET_OSD_POSITION);
            }
        }
    }
#endif

    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:

            break;

        case _MODE_STATUS_INITIAL:
            {
                //get valid source index
                BYTE i = 0;
                EnumSourceSearchPort ucPort = _A0_INPUT_PORT;
                EnumSourceSearchPort index = _A0_INPUT_PORT;
                memset(g_stSourceList, 0xFF, _INPUT_PORT_VALID);
                for(i=0; i<_INPUT_PORT_VALID; i++)
                {
                    for(ucPort=index; ucPort<_NO_INPUT_PORT; ucPort++)
                    {
                        if(BeaconCheckSourceValid(ucPort) == _TRUE)
                        {
                            index = ucPort + 1;
                            g_stSourceList[i] = (BYTE)ucPort;
                            break;
                        }
                    }

                    if(g_stSourceList[i] == 0xFF)
                    {
                        break;
                    }
                }
            }
            break;

        case _MODE_STATUS_SEARCH:
            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(Dynamic_Show_NoSignal_NoSupport == _ON)
                //for no support display
                if(GET_OSD_ITEM_INDEX() == 0)
                    ScalerTimerActiveTimerEvent(_NOSIGNAL_DELAY_TIME, _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
#endif
                UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
            }
            break;

        case _MODE_STATUS_DISPLAY_SETTING:

            break;

        case _MODE_STATUS_ACTIVE:
            if(SysModeGetModeStateChange() == _TRUE)
            {
            
                if(GET_FACTORY_BURN()==_ON)
                {
                    SET_FACTORY_BURN(_OFF);
                    BeaconFactorySaveData();
                }
                UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);
            }

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_FACTORY_MODE);
#endif

#if(_DCR_SUPPORT == _ON)
            UserCommonAdjustDCR();
#endif
            break;

        case _MODE_STATUS_NOSUPPORT:
        case _MODE_STATUS_NOSIGNAL:            
#if(_CUSTOMER == _CUS_TOSHIBA)
            if(SysModeGetModeState() == _MODE_STATUS_NOSUPPORT)
                ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_LED_INVERT);
#endif

            if(SysModeGetModeStateChange()== _TRUE)
            {
#if(_USER_BEACON_FACTORY_OSD == _ON)
                if(GET_FACTORY_BURN()==_ON)
                {
                    DebugMessageSystem("BurnInPattern 1",0);
                    ScalerTimerActiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_BURN_IN);
                    return;
                }
#endif

#if(_CUSTOMER == _CUS_MINDRAY)
#if(_USER_AC_ON_DELAY_SHOW_NO_SIGNAL == _ON)
                if(GET_DELAY_SHOW_NOSIGNAL() == _ON)
                {
                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                    ScalerTimerActiveTimerEvent(_NOSIGNAL_DELAY_TIME, _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
                }
                else
                {
                    ScalerTimerActiveTimerEvent(_NOSIGNAL_DELAY_TIME, _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
                }
#else
            //  if(GET_OSD_ITEM_INDEX() == 0)//
            //      ScalerTimerActiveTimerEvent(_NOSIGNAL_DELAY_TIME - SEC(1.5), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
            //  else
            //      ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                ScalerTimerActiveTimerEvent(_NOSIGNAL_DELAY_TIME, _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
#endif

#else

#if(_USER_AC_ON_DELAY_SHOW_NO_SIGNAL == _ON)
                if(GET_DELAY_SHOW_NOSIGNAL() == _ON)
                {
                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                    ScalerTimerActiveTimerEvent((_USER_AC_ON_NO_SIGNAL_DELAY_SEC - SEC(1.5)), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
                }
#else
            //  if(GET_OSD_ITEM_INDEX() == 0)//
            //      ScalerTimerActiveTimerEvent(_NOSIGNAL_DELAY_TIME - SEC(1.5), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
            //  else
            //      ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                ScalerTimerActiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);//no cable
#endif
#endif
            }

            break;

        case _MODE_STATUS_POWER_SAVING:

            break;

        case _MODE_STATUS_FACTORY:

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
            NoneFactoryQCFlow(SysSourceGetInputPort());
#endif

            break;

        default:

            break;
    }

    if((GET_KEYMESSAGE() < _KEY_AMOUNT)&&((SysModeGetModeState() == _MODE_STATUS_ACTIVE)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)))
    {
#if(_KEY_FUNCTION_BUG == _ON)
        if(GET_PANELPOWERSTATUS() == _PANEL_POWER_OFF_STATE)
        {
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
        }
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);//Osd_wakeup_20151223 add

#endif
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_SET_OSD_POSITION);
#if(_USER_BEACON_FACTORY_OSD == _ON)
        if(g_ucBeaconFacOsdShowFlag)
        {
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
            BeaconFactoryOsdMenuOperation();
#if(_KEY_FUNCTION_BUG == _ON)
            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
#endif
        }
        else
#endif
        {
#if(_CUSTOMER == _CUS_TOSHIBA)
            if((GET_OSD_STATE()  >_BEACON_ADVANCED_OSD_NONE) && (GET_OSD_STATE()  < _BEACON_ADVANCED_OSD_ADJUST_SETTING_END) \
                && (GET_KEYMESSAGE() ==  _EXIT_KEY_MESSAGE))
            {

            }
            else
#endif
            {
                (*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();
#if(_EN_LOCK_FUCTION == _ON)
                if(GET_FACTORY_LOCK_STATE() == _ON)
                {
                    ScalerTimerReactiveTimerEvent(SEC(5), _USER_TIMER_EVENT_OSD_DISABLE);
                }
                else
#endif
                {
                    //Disable osd
#if(_USER_SHOW_DEBUG_OSD == _OFF)
#if(_CUSTOMER == _CUS_TOSHIBA)
                    ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
#else
                    if((GET_OSD_STATE() == _BEACON_HOTKEY_OSD_1)||(GET_OSD_STATE() == _BEACON_HOTKEY_OSD_2))
                    {
                        ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
#endif
#endif
                }
            }
        }
    }

#if(_USER_BEACON_FACTORY_OSD == _ON)
    if(g_ucBeaconFacOsdShowFlag == _ON)
    {
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    }
#endif

    if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
    {
#if(_USER_ADC_ADJUST_BY_RESISTOR == _ON)
        BeaconFuncAdcAdjustScan();
#endif

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
        UserInterfaceUartHandler();
#endif
    }

#if(_DDC_DETECT_EN == _ON)
    if(PCB_DDC_USE_GPIO_DETECT() == 0)
    {
        if(ScalerGetBit(0xFF22, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2))
        {
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _D3_INPUT_PORT);
            SET_FORCE_DDC_STUTAS(_TRUE);
        }
    }
    else
    {
        if(GET_FORCE_DDC_STUTAS() == _TRUE)
        {
            switch(GET_FACTORY_DDCCI_CHANNEL())
            {
                case 0:
                    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
                    break;
            #if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
                case 1:
                    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _A0_INPUT_PORT);  
                    break;
            #endif

            #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                case 2:         
                    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _D0_INPUT_PORT);
                    break;
            #endif

            #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                case 3:         
                    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _D1_INPUT_PORT);
                    break;
            #endif

            #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)    
                case 4:
                    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), _D3_INPUT_PORT);
                    break;
            #endif

                default:
                    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS(), SysSourceGetInputPort());
                    break;
            }
            
            SET_FORCE_DDC_STUTAS(_FALSE);
        }
    }
#endif
    
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneOsdEventMsgProc(void)
{
    switch(GET_OSD_EVENT_MESSAGE())
    {

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_DO_AUTO_CONFIG_MSG:
            BeaconDisplayAutoProc(_OSDEVENT_DO_AUTO_CONFIG_MSG);
            UserCommonAutoConfig();
            ScalerOsdDisableOsd();
            break;
            
        case _OSDEVENT_DO_AUTO_COLOR_MSG:
            BeaconDisplayAutoProc(_OSDEVENT_DO_AUTO_COLOR_MSG);
            BeaconFactoryAutoColor();
            ScalerOsdDisableOsd();
            break;

        case _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG:
            UserCommonNVRamSaveModeUserData();
            break;
#endif  
        case _OSDEVENT_SAVE_OSD_USER_DATA_MSG:
            ScalerTimerReactiveTimerEvent(SEC(1.2), _USER_TIMER_EVENT_OSD_SAVE_USER_DATA);
            break;
            
        default:
            break;
    }

        SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}

//--------------------------------------------------
// Description  : check source valid
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit BeaconCheckSourceValid(EnumSourceSearchPort ucPort)
{
    bit ret = _FALSE;
    switch(ucPort)
    {
        case _A0_INPUT_PORT:
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _A1_INPUT_PORT:
#if(_A1_INPUT_PORT_TYPE != _A1_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _A2_INPUT_PORT:
#if(_A2_INPUT_PORT_TYPE != _A2_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _D2_INPUT_PORT:
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _D3_INPUT_PORT:
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _D4_INPUT_PORT:
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            ret = _TRUE;
#endif
            break;

        case _D6_INPUT_PORT:
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
            ret = _TRUE;
#endif
            break;

        default:
            break;
    }

    return ret;
}

//--------------------------------------------------
// Description  : Menu None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
void MenuNone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_ULTRA_VIVID_SUPPORT == _ON)
            UserCommonAdjustUltraVivid(_FUNCTION_OFF, _COLOR_SPACE_RGB, _DB_APPLY_POLLING);
#endif

#if(_GAMMA_FUNCTION == _ON)
            UserAdjustGamma(0);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            ScalerColorHLWAdjust(0, 0, 0, 0, _DB_APPLY_NONE);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
            UserCommonAdjustAspectRatio();
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioMuteSwitch();
            UserAdjustAudioVolume(0);
#endif
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
            UserAdjustColorEffectMode();
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserAdjustHLWinType(0);
            UserAdjustHLWinType5Move();
            UserAdjustHighLightWindowEffectSpace();
#endif

#if(_INSTANT_TIMER_EVENT_0 == _ON)
            ScalerTimer0SetTimerCount(16);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            ScalerColorHLWBorderEnable(_OFF, _OFF, _OFF, _OFF);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            UserCommonAutoConfig();
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                // Perform auto-color for RGB
                if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
                {
                    ScalerAutoGetAutoColorResult(&g_stAdcData);
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                    // Calculate YPbPr gain/offset using formula
                    g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                    // Restore RGB gain/offset
                    ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
                }
                else
                {
                    UserCommonNVRamRestoreADCSetting();
                }
            }
#endif // End of #if(_VGA_SUPPORT == _ON)
            break;

        case _EXIT_KEY_MESSAGE:
            // auto adjust
#if(_VGA_SUPPORT == _ON)
            if((SysModeGetModeState() == _MODE_STATUS_ACTIVE) && (GET_FAIL_SAFE_MODE() == _FALSE) && (SysSourceGetSourceType() == _SOURCE_VGA))
            {
//                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
            }
#endif

            break;

        default:
            break;
    }
}
*/
void BeaconOsdNoneMenu(void)
{
//RTD2486AD_OSD_ISSUE_20151214 cancel
/*
#if(_SCALER_TYPE == _RL6297_SERIES)
    if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)//RTD2486AD_OSD_ISSUE_20151211 add
#endif
*/
/*
#if((_EMBEDDED_DDCRAM_A0_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) && (_EMBEDDED_DDCRAM_A0_SIZE != _EDID_SIZE_NONE))
    ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_GPIO);	
#endif
#if((_EMBEDDED_DDCRAM_D0_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) && (_EMBEDDED_DDCRAM_D0_SIZE != _EDID_SIZE_NONE))
    ScalerPinshareGpioDdcPinSwitch((_D0_DDC_CHANNEL_SEL == _DDC3) ? _DDC3_SWITCH_GPIO : _DDC2_SWITCH_GPIO);
#endif
#if((_EMBEDDED_DDCRAM_D1_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) && (_EMBEDDED_DDCRAM_D1_SIZE != _EDID_SIZE_NONE))
    ScalerPinshareGpioDdcPinSwitch((_D1_DDC_CHANNEL_SEL == _DDC3) ? _DDC3_SWITCH_GPIO : _DDC2_SWITCH_GPIO);
#endif
    SET_SW_IIC_STATUS(_IIC_D1_EEPROM);

    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

    if(ScalerMcuIICStart(0xa0) == _FAIL)
    {
        g_ucDebugValue[0]=0x33;
    }
    else
        g_ucDebugValue[0]=0x34;

    ScalerMcuIICStop();


    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

#if((_EMBEDDED_DDCRAM_A0_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) && (_EMBEDDED_DDCRAM_A0_SIZE != _EDID_SIZE_NONE))
    ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);
#endif
#if((_EMBEDDED_DDCRAM_D0_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) && (_EMBEDDED_DDCRAM_D0_SIZE != _EDID_SIZE_NONE))
    ScalerPinshareGpioDdcPinSwitch((_D0_DDC_CHANNEL_SEL == _DDC3) ? _DDC3_SWITCH_DDC : _DDC2_SWITCH_DDC);
#endif
#if((_EMBEDDED_DDCRAM_D1_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) && (_EMBEDDED_DDCRAM_D1_SIZE != _EDID_SIZE_NONE))
    ScalerPinshareGpioDdcPinSwitch((_D1_DDC_CHANNEL_SEL == _DDC3) ? _DDC3_SWITCH_DDC : _DDC2_SWITCH_DDC);
#endif	
*/  
//UserInterfaceNVRamRestoreEdid();
#if(_EN_LOCK_FUCTION == _ON)
    if(GET_FACTORY_LOCK_STATE() == _ON)
    {
        BeaconDisplayLockProc();
    }
    else
#endif
    {
        BeaconMainOsdDisplayProc();
    }
}

#if(_CUSTOMER != _CUS_TOSHIBA)
void BeaconOsdNoneLeft(void)
{
//  SWIIC_D0_EEPROM_SDA = 0;
#if(_EN_LOCK_FUCTION == _ON)
    if(GET_FACTORY_LOCK_STATE() == _ON)
    {
        BeaconDisplayLockProc();
    }
    else
#endif
    {
        BeaconHotkeyContrastDisplayProc();
    }
}
void BeaconOsdNoneRight(void)
{
//  SWIIC_D0_EEPROM_SDA = 1;
#if(_EN_LOCK_FUCTION == _ON)
    if(GET_FACTORY_LOCK_STATE() == _ON)
    {
        BeaconDisplayLockProc();
    }
    else
#endif
    {
#if(_ALS_TYPE != _SENSER_NONE)
        if(GET_FACTORY_ALS() == _ON)
            return;
#endif
        BeaconHotkeyBacklightDisplayProc();
    }
}

void BeaconOsdNoneExit(void)
{
    BeaconExitItem();
}
#endif

//--------------------------------------------------
// Description  : 
// Input Value  : 
// Output Value : 
//--------------------------------------------------

void BeaconMenuItem(void)
{
#if(_CUSTOMER != _CUS_TOSHIBA) 
    BYTE ucLanguage;
    BYTE ucRealGammaNum;
#endif

    switch(GET_OSD_STATE())
    {
//SOURCE_MENU_ADJUST_20160127 start
        case _BEACON_OSD_6://Source
            SET_BACKUP_OSD_VALUE(BeaconFuncJudgeSourceType());
            SET_OSD_STATE(GET_OSD_STATE() + _PAGE1_AMOUNT + 1);
            BeaconMenuItemSelColor(GET_OSD_STATE());
            break;
//SOURCE_MENU_ADJUST_20160127 end
        case _BEACON_OSD_7://Auto adjust
            BeaconMenuItemSelColor(GET_OSD_STATE() + _PAGE1_AMOUNT + 1);
            BeaconMenuAutoAdjust();
            BeaconMenuItemSelColor(GET_OSD_STATE());
            break;
#if(_CUSTOMER != _CUS_TOSHIBA)
        case _BEACON_OSD_8://Default
            BeaconMenuItemSelColor(GET_OSD_STATE() + _PAGE1_AMOUNT + 1);
            ucLanguage = GET_OSD_LANGUAGE();
            ucRealGammaNum = GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE();
            BeaconFuncResetOSD();
            if(GET_OSD_LANGUAGE()!= ucLanguage)
            {
                BeaconFuncClearFont(ROW(1),COL(_MAIN_OSD_ITEM_COL_START),WIDTH(_MAIN_OSD_FONT_COL_SIZE),HEIGHT(10));
                //Draw Color
                BeaconMenuItemSelColor(GET_OSD_STATE());
                //Draw Menu title
                BeaconFuncCompressLoadText(ROW(1), COL(8), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_TITEL_STR);

                //Draw Menu content
                BeaconFuncCompressLoadText(ROW(_MAIN_OSD_ITEM_ROW_START), COL(_MAIN_OSD_ITEM_COL_START), GET_OSD_LANGUAGE() ,tOSD_BEACON_MAIN_TEXT_STR);
            }
            //Draw parameter
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_1), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_2), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_GAMMA_SELECT_TYPE == 0)
        #if(_USER_PROJECT_TYPE == UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM)
            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START-2), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_GAMMA[GET_OSD_GAMMA()]);    
        #else
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_GAMMA(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        #endif        
#elif(_GAMMA_SELECT_TYPE == 1)
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),GET_OSD_GAMMA()+8, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            if(GET_OSD_GAMMA() == _GAMMA_1)
            {
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_1, _WRITE_BYTE1);
            }
            else
            {
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_2, _WRITE_BYTE1);
            }
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
#elif(_GAMMA_SELECT_TYPE == 2)
            BeaconFuncClearFont(BeaconItemRow(_BEACON_OSD_3), COL(14),WIDTH(_MAIN_OSD_FONT_COL_SIZE-15),HEIGHT(1));
            if(GET_OSD_GAMMA() == _GAMMA_1)
            {
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(14),1,_D, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(15),1,_I, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(16),1,_C, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_O, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_M, _WRITE_BYTE1);
            }
            else if(GET_OSD_GAMMA() == _GAMMA_2)
            {
                BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),8, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_1, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
            }
            else
            {
                BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),GET_OSD_GAMMA()+7, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_2, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
            }
#endif

            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_4), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_5), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() ,tOSD_BEACON_MAIN_LANGUAGE);
            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_6), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_SOURCE[BeaconFuncJudgeSourceType()]);
            /*
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                BeaconMenuAutoAdjust();
            }
            */
            UserInterfaceAdjustColorProc();
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
            if((GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE())!= ucRealGammaNum)
            {
                CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
            }
#endif
            BeaconMenuItemSelColor(GET_OSD_STATE());
#if(_BACKLIGHT_SENSOR == _ON)
#if(_CUSTOMER == _CUS_TOSHIBA)
            g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)];
#else
            g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default;
#endif
            UserAdjustSetSensorbacklightvalue(0); 
#endif
            break;
#endif
        case _BEACON_OSD_9://Exit
            BeaconExitItem();
            break;
        default:
            SET_OSD_STATE(GET_OSD_STATE() + _PAGE1_AMOUNT + 1);
            BeaconMenuItemSelColor(GET_OSD_STATE());
            break;
    }

}

void BeaconSelectNextItem(void)
{    
    SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_OSD_SELECT_END-1,_BEACON_OSD_NONE+1,_ON));

    if(((SysSourceGetSourceType() != _SOURCE_VGA)||(SysModeGetModeState()== _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))&&(GET_OSD_STATE()==_BEACON_OSD_7))
    {
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_OSD_SELECT_END-1,_BEACON_OSD_NONE+1,_ON));
    }
#if(_ON_SIGNAL_PORT == _ON)
    if(GET_OSD_STATE()==_BEACON_OSD_6)
    {
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_OSD_SELECT_END-1,_BEACON_OSD_NONE+1,_ON));
        if(((SysSourceGetSourceType() != _SOURCE_VGA)||(SysModeGetModeState()== _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))&&(GET_OSD_STATE()==_BEACON_OSD_7))
        {
            SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_OSD_SELECT_END-1,_BEACON_OSD_NONE+1,_ON));
        }
    }
#endif

#if(_ALS_TYPE != _SENSER_NONE)
    if(GET_FACTORY_ALS() == _ON)
    {
        if(GET_OSD_STATE()==_BEACON_OSD_1)
            SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_OSD_SELECT_END-1,_BEACON_OSD_NONE+1,_ON));

    }
#endif

    BeaconMenuItemSelColor(GET_OSD_STATE());
}

void BeaconMenuExit(void) 
{
    //SOURCE_MENU_ADJUST_20160127 start
    switch(GET_OSD_STATE() - (_PAGE1_AMOUNT + 1))
    {

        case _BEACON_OSD_6:
            if(GET_BACKUP_OSD_VALUE() == BeaconFuncJudgeSourceType())
            {
                break;
            }

            if(GET_BACKUP_OSD_VALUE() < _INPUT_PORT_VALID)
            {
                if(g_stSourceList[GET_BACKUP_OSD_VALUE()] >= _NO_INPUT_PORT)
                {
                    break;
                }
                
                SysSourceSwitchInputPort(g_stSourceList[GET_BACKUP_OSD_VALUE()]);
                
                SET_FORCE_POW_SAV_STATUS(_FALSE);
                //SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);//FAC_ADD_SOURCE_DET_ON_OFF_20151223 cancel
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
                    (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
                    UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
                    UserCommonNVRamSaveSystemData();//SOURCE_FIRST_SEARCH_PORT_201512114 add
                }
                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            break;


        default:
            break;
    }
    //SOURCE_MENU_ADJUST_20160127 end
    SET_OSD_STATE(GET_OSD_STATE() - (_PAGE1_AMOUNT + 1)); 
    BeaconMenuItemSelColor(GET_OSD_STATE());
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);

}

void BeaconExitItem(void)
{
    GET_OSD_STATE() = _BEACON_OSD_NONE;
    ScalerOsdDisableOsd();
#if(_USER_SHOW_DEBUG_OSD == _ON)
    BeaconDebugOsdInitial();//Refresh data
    return;
#if 0//(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
    UserCheckEepromIsNormal();
#endif
#endif
    //Osd_wakeup_20151223 start (for show no signal)
#if(_USER_BEACON_FACTORY_OSD == _ON)
    if((GET_FACTORY_BURN()==_OFF)&&((SysModeGetModeState() == _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)))
    {
#if 0
        ScalerTimerActiveTimerEvent(SEC(0.1), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
#endif
    }
    //Osd_wakeup_20151223 end
#endif	
}

void BeaconNoAction(void) 
{
    return;
}

void BeaconBacklightAdjust(void)
{

    SET_OSD_BACKLIGHT(BeaconFuncValueChange(GET_OSD_BACKLIGHT(),_OSD_BriCon_RANGE,0,_OFF));
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_1), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_BACKLIGHT_SENSOR == _ON)
    UserAdjustSetSensorbacklightvalue(1);
#endif
    
}

void BeaconContrastAdjust(void)
{
    SET_OSD_CONTRAST(BeaconFuncValueChange(GET_OSD_CONTRAST(),_OSD_BriCon_RANGE,0,_OFF));
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_2), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustContrast(GET_OSD_CONTRAST());
}

void BeaconGammaAdjust(void)
{
        SET_OSD_GAMMA(BeaconFuncValueChange(GET_OSD_GAMMA(),_GAMMA_AMOUNT,_GAMMA_1,_ON));

#if(_GAMMA_SELECT_TYPE == 0)
    #if(_USER_PROJECT_TYPE == UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM)
        BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START-2), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_GAMMA[GET_OSD_GAMMA()]);    
    #else
        BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_GAMMA(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    #endif    
#elif(_GAMMA_SELECT_TYPE == 1)
        BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),GET_OSD_GAMMA()+8, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        if(GET_OSD_GAMMA() == _GAMMA_1)
        {
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_1, _WRITE_BYTE1);
        }
        else
        {
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_2, _WRITE_BYTE1);
        }
        BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
#elif(_GAMMA_SELECT_TYPE == 2)
        BeaconFuncClearFont(BeaconItemRow(_BEACON_OSD_3), COL(14),WIDTH(_MAIN_OSD_FONT_COL_SIZE-15),HEIGHT(1));
        if(GET_OSD_GAMMA() == _GAMMA_1)
        {
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(14),1,_D, _WRITE_BYTE1);
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(15),1,_I, _WRITE_BYTE1);
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(16),1,_C, _WRITE_BYTE1);
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_O, _WRITE_BYTE1);
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_M, _WRITE_BYTE1);
        }
        else if(GET_OSD_GAMMA() == _GAMMA_2)
        {
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),8, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_1, _WRITE_BYTE1);
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
        }
        else
        {
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),GET_OSD_GAMMA()+7, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_2, _WRITE_BYTE1);
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
        }

#endif
#if(_GAMMA_FUNCTION == _ON)
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
    CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#else
   // ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

   // ScalerColorOutputGamma(_OFF);
    
    if(GET_OSD_GAMMA() != _GAMMA_OFF)
    {
        UserAdjustGamma(GET_OSD_GAMMA());

      //  ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
      //  ScalerColorOutputGamma(_ON);
    }
#endif
#endif // End of #if(_GAMMA_FUNCTION == _ON)

}

void BeaconColorTempAdjust(void)
{

    SET_COLOR_TEMP_TYPE(BeaconFuncValueChange(GET_COLOR_TEMP_TYPE(),_CT_COLORTEMP_AMOUNT,0,_ON));

    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_4), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
    UserAdjustContrast(GET_OSD_CONTRAST());

#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
#if(_BACKLIGHT_SENSOR == _ON)
    UserAdjustSetSensorbacklightvalue(1);
#endif
#endif
    
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
    CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif
}


void BeaconLanguageAdjust(void)
{
#if(_CUSTOMER == _CUS_TOSHIBA)
    SET_OSD_LANGUAGE(BeaconFuncValueChange(GET_OSD_LANGUAGE(),7,0,_ON));
    if(GET_OSD_LANGUAGE() == 1)
    {
        SET_OSD_LANGUAGE(BeaconFuncValueChange(GET_OSD_LANGUAGE(),7,0,_ON));
    }
#else
    SET_OSD_LANGUAGE(BeaconFuncValueChange(GET_OSD_LANGUAGE(),1,0,_ON));
#endif
    // Character Command initial
    //ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((_CP_WHITE<< 4) | _CP_BG), (WORD)(_MAIN_OSD_FONT_COL_SIZE * _MAIN_OSD_FONT_ROW_SIZE));
    BeaconFuncClearFont(ROW(1),COL(_MAIN_OSD_ITEM_COL_START),WIDTH(_MAIN_OSD_FONT_COL_SIZE),HEIGHT(10));

    //Draw Color
    BeaconMenuItemSelColor(GET_OSD_STATE());

    //Draw Menu title
    BeaconFuncCompressLoadText(ROW(1), COL(8), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_TITEL_STR);

    //Draw Menu content
    BeaconFuncCompressLoadText(ROW(_MAIN_OSD_ITEM_ROW_START), COL(_MAIN_OSD_ITEM_COL_START), GET_OSD_LANGUAGE() ,tOSD_BEACON_MAIN_TEXT_STR);

    //Draw parameter
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_1), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_2), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#if(_USER_PROJECT_TYPE == UNITED_RTD2785_C23_LG_LM240WU8_SLE1_2LVDS_PWM)
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START-2), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_GAMMA[GET_OSD_GAMMA()]);    
#else
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_GAMMA(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#endif   
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_4), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_5), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_LANGUAGE);
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_6), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_SOURCE[BeaconFuncJudgeSourceType()]);

}

void BeaconSourceAdjust(void)
{
#if 0
    SET_BACKUP_OSD_VALUE(BeaconFuncValueChange(GET_BACKUP_OSD_VALUE(),1920,0,_ON));
    BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_6), COL(15),GET_BACKUP_OSD_VALUE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_4));
    return;
#endif

//SOURCE_MENU_ADJUST_20160127 start
#if 0//(_PCB_TYPE == _RL6297_BEACON_RTD2486AD_1HDP)
    SET_BACKUP_OSD_VALUE(BeaconFuncValueChange(GET_BACKUP_OSD_VALUE(),_INPUT_PORT_VALID-1,1,_ON));
#else
    SET_BACKUP_OSD_VALUE(BeaconFuncValueChange(GET_BACKUP_OSD_VALUE(),_INPUT_PORT_VALID-1,0,_ON));
#endif
//SOURCE_MENU_ADJUST_20160127 end
    BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_6), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_SOURCE[GET_BACKUP_OSD_VALUE()]);
}

void BeaconMenuAutoAdjust(void)
{
#if(_VGA_SUPPORT == _ON)
    if(SysSourceGetSourceType() == _SOURCE_VGA)
    {                    
        UserCommonAutoConfig();
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
    }
#endif
}

//Advanced OSD 
void BeaconAdvancedPageMenu(void)
{
    switch(GET_OSD_STATE())
    {
        case _BEACON_ADVANCED_OSD_SELECT_COLOR:
            SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_COLOR+1); 
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _OFF)
            SET_OSD_STATE(_BEACON_ADVANCED_OSD_COLOR_3); 
#endif
            BeaconADColorMenuItemSelColor(GET_OSD_STATE());
            break;
        case _BEACON_ADVANCED_OSD_SELECT_IMAGE:
            SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_IMAGE+1); 
            BeaconADImageMenuItemSelColor(GET_OSD_STATE());
            break;
        case _BEACON_ADVANCED_OSD_SELECT_SETTING:
            SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_SETTING+1); 
            BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
            break;
        default:
            break;
    }
}

void BeaconAdvancedPageSelectNext(void)
{
    while(_TRUE)
    {
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_SETTING,_BEACON_ADVANCED_OSD_SELECT_COLOR,_ON));
        if((GET_OSD_STATE()==_BEACON_ADVANCED_OSD_SELECT_IMAGE)&&((SysSourceGetSourceType() != _SOURCE_VGA)||(SysModeGetModeState()== _MODE_STATUS_NOSIGNAL)||(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)))
        {
            SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_SETTING,_BEACON_ADVANCED_OSD_SELECT_COLOR,_ON));
        }
        if((GET_OSD_STATE()==_BEACON_ADVANCED_OSD_SELECT_COLOR)||(GET_OSD_STATE()==_BEACON_ADVANCED_OSD_SELECT_IMAGE)||(GET_OSD_STATE()==_BEACON_ADVANCED_OSD_SELECT_SETTING))
        {
            break;
        }
    }

    switch(GET_OSD_STATE())
    {
        case _BEACON_ADVANCED_OSD_SELECT_COLOR:
            //Clear content
            BeaconFuncClearFont(ROW(2),COL(7-1),WIDTH(_ADVANCED_OSD_FONT_COL_SIZE-7),HEIGHT(8));
            BeaconADColorMenuItemSelColor(GET_OSD_STATE());
            //Draw Window
            BeaconFuncDrawWindow(XSTART(3), YSTART(2*18-7), XEND(5*18-8-10), YEND(5*18), tOSD_WINDOW_3_ADVANCED_MEMU3);
            //Draw Menu content
            BeaconFuncCompressLoadText(ROW(2), COL(7-1), GET_OSD_LANGUAGE() ,  tOSD_BEACON_ADVANCED_COLOR_TEXT_STR);

            //Draw parameter
            BeaconFuncCompressLoadText(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_1), COL(_ADVANCED_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE(), tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR[GET_OSD_ASPECT_RATIO_TYPE()]);
            BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_ASPECT_ORIGIN_RATIO(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_BRIGHTNESS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncCompressLoadText(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_4), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_LANGUAGE(), tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
            BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_5), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_R(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_6), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_G(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_7), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_B(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

            break;
        case _BEACON_ADVANCED_OSD_SELECT_IMAGE:
            //Clear content
            BeaconFuncClearFont(ROW(2),COL(7-1),WIDTH(_ADVANCED_OSD_FONT_COL_SIZE-7),HEIGHT(8));
            BeaconADImageMenuItemSelColor(GET_OSD_STATE());
            //Draw Window
            BeaconFuncDrawWindow(XSTART(3), YSTART(5*18), XEND(5*18-8-10), YEND(8*18), tOSD_WINDOW_3_ADVANCED_MEMU3);

            //Draw Menu content
            BeaconFuncCompressLoadText(ROW(2), COL(7-1), GET_OSD_LANGUAGE() , tOSD_BEACON_ADVANCED_IMAGE_TEXT_STR);
            //Draw parameter
#if(_VGA_SUPPORT == _ON)
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_4), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_5), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#endif
            break;
        case _BEACON_ADVANCED_OSD_SELECT_SETTING:
            //Clear content
            BeaconFuncClearFont(ROW(2),COL(7-1),WIDTH(_ADVANCED_OSD_FONT_COL_SIZE-7),HEIGHT(8));
            BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
            //Draw Menu content
            BeaconFuncCompressLoadText(ROW(2), COL(7-1), GET_OSD_LANGUAGE() , tOSD_BEACON_ADVANCED_SETTING_TEXT_STR);
            //Draw Window
            BeaconFuncDrawWindow(XSTART(3), YSTART(8*18), XEND(5*18-8-10), YEND(11*18+7), tOSD_WINDOW_3_ADVANCED_MEMU3);
            //Draw parameter
            BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_1), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

            break;
        default:
            break;

    }

}

void BeaconAdvancedPageExit(void)
{
    BeaconExitItem();
}

void BeaconAdvancedColorMenuItem(void)
{
    switch(GET_OSD_STATE())
    {
        case _BEACON_ADVANCED_OSD_COLOR_8://back
            SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_COLOR);
            BeaconFuncCloseWindow(_WIN4);
            BeaconADColorMenuItemSelColor(GET_OSD_STATE());
            break;
        default:
            SET_OSD_STATE(GET_OSD_STATE() + _PAGE2_AMOUNT + 1);
            BeaconADColorMenuItemSelColor(GET_OSD_STATE());
            break;
    }
}

void BeaconAdvancedColorSelectNextItem(void)
{    
    SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_COLOR_END-1,_BEACON_ADVANCED_OSD_SELECT_COLOR+1,_ON));
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _OFF)
    if((GET_OSD_STATE()==_BEACON_ADVANCED_OSD_COLOR_1)||(GET_OSD_STATE()==_BEACON_ADVANCED_OSD_COLOR_2))
    {
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_COLOR_END-1,_BEACON_ADVANCED_OSD_SELECT_COLOR+1,_ON));
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_COLOR_END-1,_BEACON_ADVANCED_OSD_SELECT_COLOR+1,_ON));
    }
#else
    if((GET_OSD_STATE()==_BEACON_ADVANCED_OSD_COLOR_2)&&(UserInterfaceGetAspectRatioType()!=_ASPECT_RATIO_USER))
    {
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_COLOR_END-1,_BEACON_ADVANCED_OSD_SELECT_COLOR+1,_ON));
    }
#endif
    else if((GET_OSD_STATE()==_BEACON_ADVANCED_OSD_COLOR_5)&&(GET_COLOR_TEMP_TYPE()!=_BEACON_USER)||
            (GET_OSD_STATE()==_BEACON_ADVANCED_OSD_COLOR_7)&&(GET_COLOR_TEMP_TYPE()!=_BEACON_USER))
    {
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_COLOR_END-1,_BEACON_ADVANCED_OSD_SELECT_COLOR+1,_ON));
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_COLOR_END-1,_BEACON_ADVANCED_OSD_SELECT_COLOR+1,_ON));
        SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_COLOR_END-1,_BEACON_ADVANCED_OSD_SELECT_COLOR+1,_ON));
    }
    BeaconADColorMenuItemSelColor(GET_OSD_STATE());
}

void BeaconAdvancedColorExitItem(void)
{
    SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_COLOR);
    BeaconFuncCloseWindow(_WIN4);
    BeaconADColorMenuItemSelColor(GET_OSD_STATE());
}

void BeaconAdvancedColorMenuExit(void) 
{
    SET_OSD_STATE(GET_OSD_STATE() - (_PAGE2_AMOUNT + 1)); 
    BeaconADColorMenuItemSelColor(GET_OSD_STATE());
#if(_ASPECT_RATIO_SUPPORT == _ON)
    if(GET_OSD_STATE() == _BEACON_ADVANCED_OSD_COLOR_2)
    {
        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
    }
#endif
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);

}

void BeaconADColorAdjustAspectSelect(void)
{
#if(_CUSTOMER == _CUS_TOSHIBA)
    SET_OSD_ASPECT_RATIO_TYPE(BeaconFuncValueChange(GET_OSD_ASPECT_RATIO_TYPE(),_OSD_ASPECT_RATIO_AMOUNT,_OSD_ASPECT_RATIO_1,_ON));
#else
    SET_OSD_ASPECT_RATIO_TYPE(BeaconFuncValueChange(GET_OSD_ASPECT_RATIO_TYPE(),_OSD_ASPECT_RATIO_AMOUNT,_OSD_ASPECT_RATIO_FULL,_ON));
#endif

    BeaconFuncCompressLoadText(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_1), COL(_ADVANCED_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE(),tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR[GET_OSD_ASPECT_RATIO_TYPE()]);
    BeaconADColorMenuItemSelColor(GET_OSD_STATE());//updata user ratio
#if(_ASPECT_RATIO_SUPPORT == _ON)
    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
#endif
}
void BeaconADColorAdjustAspectRatio(void)
{
    SET_OSD_ASPECT_ORIGIN_RATIO(BeaconFuncValueChange(GET_OSD_ASPECT_ORIGIN_RATIO(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_ASPECT_ORIGIN_RATIO(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
}

void BeaconADColorAdjustBrightness(void)
{
    SET_OSD_BRIGHTNESS(BeaconFuncValueChange(GET_OSD_BRIGHTNESS(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_BRIGHTNESS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
}

void BeaconADColorAdjustColorTempType(void)
{
    SET_COLOR_TEMP_TYPE(BeaconFuncValueChange(GET_COLOR_TEMP_TYPE(),_CT_COLORTEMP_AMOUNT,0,_ON));

    BeaconFuncCompressLoadText(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_4), COL(_ADVANCED_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
    BeaconADColorMenuItemSelColor(GET_OSD_STATE());
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_5), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_R(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_6), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_G(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_7), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_B(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustContrast(GET_OSD_CONTRAST());

#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
#if(_BACKLIGHT_SENSOR == _ON)
    UserAdjustSetSensorbacklightvalue(1);
#endif
#endif
  
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
    CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif
}
void BeaconADColorAdjustColorTempTypeUserR(void)
{
    SET_COLOR_TEMP_TYPE_USER_R(BeaconFuncValueChange(GET_COLOR_TEMP_TYPE_USER_R(),255,0,_OFF));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_5), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_R(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustContrast(GET_OSD_CONTRAST());
}
void BeaconADColorAdjustColorTempTypeUserG(void)
{
    SET_COLOR_TEMP_TYPE_USER_G(BeaconFuncValueChange(GET_COLOR_TEMP_TYPE_USER_G(),255,0,_OFF));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_6), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_G(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustContrast(GET_OSD_CONTRAST());
}
void BeaconADColorAdjustColorTempTypeUserB(void)
{
    SET_COLOR_TEMP_TYPE_USER_B(BeaconFuncValueChange(GET_COLOR_TEMP_TYPE_USER_B(),255,0,_OFF));
    BeaconFuncShowNumber(BeaconADColorItemRow(_BEACON_ADVANCED_OSD_COLOR_7), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_COLOR_TEMP_TYPE_USER_B(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserAdjustContrast(GET_OSD_CONTRAST());
}


void BeaconAdvancedImageMenuItem(void)
{
    switch(GET_OSD_STATE())
    {
        case _BEACON_ADVANCED_OSD_IMAGE_1://Auto adjust
#if(_VGA_SUPPORT == _ON)
            BeaconADImageMenuItemSelColor(GET_OSD_STATE() + _PAGE3_AMOUNT + 1);
            BeaconMenuAutoAdjust();
            //Draw parameter
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_4), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_5), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconADImageMenuItemSelColor(GET_OSD_STATE());
#endif
            break;
        case _BEACON_ADVANCED_OSD_IMAGE_6://Return
            SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_IMAGE);
            BeaconFuncCloseWindow(_WIN4);
            BeaconADImageMenuItemSelColor(GET_OSD_STATE());
            break;

        default:
            SET_OSD_STATE(GET_OSD_STATE() + _PAGE3_AMOUNT + 1);
            BeaconADImageMenuItemSelColor(GET_OSD_STATE());
            break;
    }
}

void BeaconAdvancedImageSelectNextItem(void)
{    
    SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_IMAGE_END-1,_BEACON_ADVANCED_OSD_SELECT_IMAGE+1,_ON));
    BeaconADImageMenuItemSelColor(GET_OSD_STATE());
}

void BeaconAdvancedImageExitItem(void)
{
    SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_IMAGE);
    BeaconFuncCloseWindow(_WIN4);
    BeaconADImageMenuItemSelColor(GET_OSD_STATE());
}

void BeaconAdvancedImageMenuExit(void) 
{
    SET_OSD_STATE(GET_OSD_STATE() - (_PAGE3_AMOUNT + 1)); 
    BeaconADImageMenuItemSelColor(GET_OSD_STATE());
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
}


void BeaconADImageAdjustAnologHpos(void)
{
#if(_VGA_SUPPORT == _ON)
    SET_VGA_MODE_ADJUST_H_POSITION(BeaconFuncValueChange(GET_VGA_MODE_ADJUST_H_POSITION(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
#endif
}
void BeaconADImageAdjustAnologVpos(void)
{
#if(_VGA_SUPPORT == _ON)
    SET_VGA_MODE_ADJUST_V_POSITION(BeaconFuncValueChange(GET_VGA_MODE_ADJUST_V_POSITION(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
#endif
}
void BeaconADImageAdjustAnologClock(void)
{
    //WORD usClockRangeMax = 0;
    //WORD usClockRangeMin = 0;
#if(_VGA_SUPPORT == _ON)
    SET_VGA_MODE_ADJUST_CLOCK(BeaconFuncValueChange(GET_VGA_MODE_ADJUST_CLOCK(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_4), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    //usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    //usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);

    //SET_VGA_MODE_ADJUST_CLOCK(UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin)));
    UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
#endif
}
void BeaconADImageAdjustAnologPhase(void)
{
#if(_VGA_SUPPORT == _ON)
    SET_VGA_MODE_ADJUST_PHASE(BeaconFuncValueChange(GET_VGA_MODE_ADJUST_PHASE(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADImageItemRow(_BEACON_ADVANCED_OSD_IMAGE_5), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));

    //SET_VGA_MODE_ADJUST_PHASE(UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_PHASE(), _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER));
    UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
#endif
}

void BeaconAdvancedSettingMenuItem(void)
{
    BYTE ucLanguage;
    BYTE ucRealGammaNum;

    switch(GET_OSD_STATE())
    {
        case _BEACON_ADVANCED_OSD_SETTING_4:
            BeaconADSettingMenuItemSelColor(GET_OSD_STATE() + _PAGE4_AMOUNT + 1);
            ucLanguage = GET_OSD_LANGUAGE();
            ucRealGammaNum = GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE();
            BeaconFuncResetOSD();
            if(GET_OSD_LANGUAGE()!= ucLanguage)
            {
                //Clear content
                BeaconFuncClearFont(ROW(2),COL(7-1),WIDTH(_ADVANCED_OSD_FONT_COL_SIZE-7),HEIGHT(8));
                BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
                //Draw Menu content
                BeaconFuncCompressLoadText(ROW(2), COL(7-1), GET_OSD_LANGUAGE() , tOSD_BEACON_ADVANCED_SETTING_TEXT_STR);
            }
            //Draw parameter
            BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_1), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            /*if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                BeaconMenuAutoAdjust();
            }*/

            UserInterfaceAdjustColorProc();
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
            if((GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE())!= ucRealGammaNum)
            {
                CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
            }
#endif

            BeaconADSettingMenuItemSelColor(GET_OSD_STATE());

#if(_BACKLIGHT_SENSOR == _ON)
#if(_CUSTOMER == _CUS_TOSHIBA)
            g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default[(GET_COLOR_TEMP_TYPE()%2)];
#else
            g_stOtherUserData.Sensor_brightness_value = g_stOtherUserData.Sensor_brightness_default;
#endif
            UserAdjustSetSensorbacklightvalue(0);
#endif
            break;
        case _BEACON_ADVANCED_OSD_SETTING_5:
            SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_SETTING);
            BeaconFuncCloseWindow(_WIN4);
            BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
            break;
        case _BEACON_ADVANCED_OSD_SETTING_6:
            BeaconExitItem();
            break;
        default:
            SET_OSD_STATE(GET_OSD_STATE() + _PAGE4_AMOUNT + 1);
            BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
            break;
    }

}

void BeaconAdvancedSettingSelectNextItem(void)
{    
    SET_OSD_STATE(BeaconFuncValueChange(GET_OSD_STATE(),_BEACON_ADVANCED_OSD_SELECT_SETTING_END-1,_BEACON_ADVANCED_OSD_SELECT_SETTING+1,_ON));
    BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
}

void BeaconAdvancedSettingExitItem(void)
{
    SET_OSD_STATE(_BEACON_ADVANCED_OSD_SELECT_SETTING);
    BeaconFuncCloseWindow(_WIN4);
    BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
}

void BeaconAdvancedSettingMenuExit(void) 
{
    SET_OSD_STATE(GET_OSD_STATE() - (_PAGE4_AMOUNT + 1)); 
    BeaconADSettingMenuItemSelColor(GET_OSD_STATE());
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
}

void BeaconADSettingAdjustOSDHpos(void)
{
    SET_OSD_HPOS(BeaconFuncValueChange(GET_OSD_HPOS(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_1), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
   // BeaconFuncSetPosition((_PANEL_DH_START/4 + ((DWORD)((_PANEL_DH_WIDTH-_ADVANCED_OSD_WINDOWS_COL_SIZE*12) / 4) * GET_OSD_HPOS()) / 100),(0 + ((DWORD)(_PANEL_DV_HEIGHT-_ADVANCED_OSD_WINDOWS_ROW_SIZE*18) * GET_OSD_VPOS()) / 100));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
}

void BeaconADSettingAdjustOSDVpos(void)
{
    SET_OSD_VPOS(BeaconFuncValueChange(GET_OSD_VPOS(),100,0,_OFF));
    BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_2), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    //BeaconFuncSetPosition((_PANEL_DH_START/4 + ((DWORD)((_PANEL_DH_WIDTH-_ADVANCED_OSD_WINDOWS_COL_SIZE*12) / 4) * GET_OSD_HPOS()) / 100),(0 + ((DWORD)(_PANEL_DV_HEIGHT-_ADVANCED_OSD_WINDOWS_ROW_SIZE*18) * GET_OSD_VPOS()) / 100));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

}
void BeaconADSettingAdjustOSDTime(void)
{
    SET_OSD_TIME_OUT(BeaconFuncValueChange(GET_OSD_TIME_OUT(),60,5,_OFF));
    BeaconFuncShowNumber(BeaconADSettingItemRow(_BEACON_ADVANCED_OSD_SETTING_3), COL(_ADVANCED_OSD_ITEM_DATA_COL_START),GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
}

void BeaconHotkeyOSDMenu(void)
{
    BeaconExitItem();
}

void BeaconHotkeyOSDBacklightAdjust(void)
{

    SET_OSD_BACKLIGHT(BeaconFuncValueChange(GET_OSD_BACKLIGHT(),_OSD_BriCon_RANGE,0,_OFF));
    //Value progress window
#if(_OSD_BriCon_RANGE == 255)
    BeaconFuncDrawWindow(XSTART(10*12), YSTART(1*18-2), XEND(10*12+1+(DWORD)(0.5608*GET_OSD_BACKLIGHT())), YEND(2*18), tOSD_WINDOW_1_HOTKEY);
#else
    BeaconFuncDrawWindow(XSTART(10*12), YSTART(1*18-2), XEND(10*12+1+(DWORD)(1.43*GET_OSD_BACKLIGHT())), YEND(2*18), tOSD_WINDOW_1_HOTKEY);
#endif
    if(GET_OSD_LANGUAGE()==0)
    {
        BeaconFuncShowNumber(ROW(1), COL(25),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    }
    else
    {
        BeaconFuncShowNumber(ROW(1), COL(23),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        BeaconFuncHLine(ROW(1), COL(23-2),1,0x45, _WRITE_BYTE0);
    }

    UserAdjustBacklight(GET_OSD_BACKLIGHT());

    ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_OSD_SAVE_USER_DATA);

#if(_BACKLIGHT_SENSOR == _ON)
    UserAdjustSetSensorbacklightvalue(1);
#endif


}


void BeaconHotkeyOSDContrastAdjust(void)
{
    SET_OSD_CONTRAST(BeaconFuncValueChange(GET_OSD_CONTRAST(),_OSD_BriCon_RANGE,0,_OFF));
    //Value progress window
#if(_OSD_BriCon_RANGE == 255)
    BeaconFuncDrawWindow(XSTART(10*12), YSTART(1*18-2), XEND(10*12+1+(DWORD)(0.5608*GET_OSD_CONTRAST())), YEND(2*18), tOSD_WINDOW_1_HOTKEY);
#else
    BeaconFuncDrawWindow(XSTART(10*12), YSTART(1*18-2), XEND(10*12+1+(DWORD)(1.43*GET_OSD_CONTRAST())), YEND(2*18), tOSD_WINDOW_1_HOTKEY);
#endif

    if(GET_OSD_LANGUAGE()==0)
    {
        BeaconFuncShowNumber(ROW(1), COL(24),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
    }
    else
    {
        BeaconFuncShowNumber(ROW(1), COL(22),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
        BeaconFuncHLine(ROW(1), COL(22-2),1,0x49, _WRITE_BYTE0);
    }

    UserAdjustContrast(GET_OSD_CONTRAST());
    ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_OSD_SAVE_USER_DATA);

}

#if(_CUSTOMER == _CUS_TOSHIBA)
void MainMenuItemReset(void)
{
    BYTE ucItem = _BEACON_OSD_NONE;
    BYTE ucItemRow = _BEACON_OSD_NONE;

    ucItemRow = ucItem = GET_OSD_STATE();

    if((_BEACON_OSD_SELECT_END < ucItem) && (ucItem < _BEACON_OSD_ADJUST_END))
    {
        ucItemRow = ucItem - (_PAGE1_AMOUNT + 1);
    }
    
    switch(ucItemRow)
    {
        case _BEACON_OSD_1:
            SET_OSD_BACKLIGHT(GET_FACTORY_BACKLIGHT());
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_1), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
#if(_BACKLIGHT_SENSOR == _ON)
            UserAdjustSetSensorbacklightvalue(1);
#endif
            ScalerTimerDelayXms(2000);
            break;

        case _BEACON_OSD_2:
            SET_OSD_CONTRAST(GET_FACTORY_CONTRAST());
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_2), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            UserAdjustContrast(GET_OSD_CONTRAST());
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
            ScalerTimerDelayXms(2000);
            break;

        case _BEACON_OSD_3:
            SET_OSD_GAMMA(GET_FACTORY_GAMMA());
#if(_GAMMA_SELECT_TYPE == 0)
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_GAMMA(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
#elif(_GAMMA_SELECT_TYPE == 1)
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),GET_OSD_GAMMA()+8, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            if(GET_OSD_GAMMA() == _GAMMA_1)
            {
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_1, _WRITE_BYTE1);
            }
            else
            {
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_2, _WRITE_BYTE1);
            }
            BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
#elif(_GAMMA_SELECT_TYPE == 2)
            BeaconFuncClearFont(BeaconItemRow(_BEACON_OSD_3), COL(14),WIDTH(_MAIN_OSD_FONT_COL_SIZE-15),HEIGHT(1));
            if(GET_OSD_GAMMA() == _GAMMA_1)
            {
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(14),1,_D, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(15),1,_I, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(16),1,_C, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_O, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_M, _WRITE_BYTE1);
            }
            else if(GET_OSD_GAMMA() == _GAMMA_2)
            {
                BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),8, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_1, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
            }
            else
            {
                BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(16),GET_OSD_GAMMA()+7, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(17),1,_2, _WRITE_BYTE1);
                BeaconFuncHLine(BeaconItemRow(_BEACON_OSD_3), COL(18),1,_DOT, _WRITE_BYTE1);
            }
#endif

#if(_GAMMA_FUNCTION == _ON)
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
            CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#else
           // ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        
           // ScalerColorOutputGamma(_OFF);
            
            if(GET_OSD_GAMMA() != _GAMMA_OFF)
            {
                UserAdjustGamma(GET_OSD_GAMMA());
        
              //  ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
              //  ScalerColorOutputGamma(_ON);
            }
#endif
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
            ScalerTimerDelayXms(2000);            
            break;

        case _BEACON_OSD_4:
            SET_COLOR_TEMP_TYPE(GET_FACTORY_COLORTEMP());
            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_4), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            UserAdjustContrast(GET_OSD_CONTRAST());
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
#if(_BACKLIGHT_SENSOR == _ON)
            UserAdjustSetSensorbacklightvalue(1);
#endif
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
            CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif         
            ScalerTimerDelayXms(2000);
            break;

        case _BEACON_OSD_5:
            SET_OSD_LANGUAGE(0);
            //ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, 0x4C, _SPACE, ((_CP_WHITE<< 4) | _CP_BG), (WORD)(_MAIN_OSD_FONT_COL_SIZE * _MAIN_OSD_FONT_ROW_SIZE));
            BeaconFuncClearFont(ROW(1),COL(_MAIN_OSD_ITEM_COL_START),WIDTH(_MAIN_OSD_FONT_COL_SIZE),HEIGHT(10));
            //Draw Color
            BeaconMenuItemSelColor(GET_OSD_STATE());
            //Draw Menu title
            BeaconFuncCompressLoadText(ROW(1), COL(8), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_TITEL_STR);
            //Draw Menu content
            BeaconFuncCompressLoadText(ROW(_MAIN_OSD_ITEM_ROW_START), COL(_MAIN_OSD_ITEM_COL_START), GET_OSD_LANGUAGE() ,tOSD_BEACON_MAIN_TEXT_STR);
            //Draw parameter
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_1), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_BACKLIGHT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_2), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_CONTRAST(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncShowNumber(BeaconItemRow(_BEACON_OSD_3), COL(_BEACON_OSD_ITEM_DATA_COL_START),GET_OSD_GAMMA(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3));
            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_4), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_COLORTEMP[GET_COLOR_TEMP_TYPE()]);
            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_5), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_LANGUAGE);
            BeaconFuncCompressLoadText(BeaconItemRow(_BEACON_OSD_6), COL(_BEACON_OSD_ITEM_DATA_COL_START), GET_OSD_LANGUAGE() , tOSD_BEACON_MAIN_SOURCE[BeaconFuncJudgeSourceType()]);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
            ScalerTimerDelayXms(2000);
            break;

        default:
            break;
    }
}
#endif

code void (*OperationTable[][4])(void) =
{
#if(_CUSTOMER == _CUS_TOSHIBA)
  { BeaconOsdNoneMenu,              BeaconNoAction,                         BeaconNoAction,                     BeaconOsdNoneMenu},  
#else
  { BeaconOsdNoneMenu,              BeaconOsdNoneLeft,                      BeaconOsdNoneRight,                 BeaconOsdNoneExit},
#endif
//Main OSD select part
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
#if(_CUSTOMER != _CUS_TOSHIBA)
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},
#endif
  { BeaconMenuItem,                 BeaconSelectNextItem,                   BeaconSelectNextItem,               BeaconExitItem},

  { BeaconNoAction,                 BeaconNoAction,                         BeaconNoAction,                     BeaconNoAction},//No use.

//Main OSD adjust parameter
  { BeaconMenuExit,                 BeaconBacklightAdjust,                  BeaconBacklightAdjust,              BeaconMenuExit},
  { BeaconMenuExit,                 BeaconContrastAdjust,                   BeaconContrastAdjust,               BeaconMenuExit},
  { BeaconMenuExit,                 BeaconGammaAdjust,                      BeaconGammaAdjust,                  BeaconMenuExit},
  { BeaconMenuExit,                 BeaconColorTempAdjust,                  BeaconColorTempAdjust,              BeaconMenuExit},
  { BeaconMenuExit,                 BeaconLanguageAdjust,                   BeaconLanguageAdjust,               BeaconMenuExit},
  { BeaconMenuExit,                 BeaconSourceAdjust,                     BeaconSourceAdjust,                 BeaconMenuExit},
  { BeaconMenuExit,                 BeaconNoAction,                         BeaconNoAction,                     BeaconMenuExit},
#if(_CUSTOMER != _CUS_TOSHIBA)
  { BeaconMenuExit,                 BeaconNoAction,                         BeaconNoAction,                     BeaconMenuExit},
#endif
  { BeaconMenuExit,                 BeaconNoAction,                         BeaconNoAction,                     BeaconMenuExit},

  { BeaconNoAction,                 BeaconNoAction,                         BeaconNoAction,                     BeaconNoAction},//No use.Just for _BEACON_OSD_ADJUST_END

//Advance OSD part
  { BeaconAdvancedPageMenu,         BeaconAdvancedPageSelectNext,           BeaconAdvancedPageSelectNext,       BeaconAdvancedPageExit},

//Advance OSD Color select part
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},
  { BeaconAdvancedColorMenuItem,    BeaconAdvancedColorSelectNextItem,      BeaconAdvancedColorSelectNextItem,  BeaconAdvancedColorExitItem},

  { BeaconNoAction,                 BeaconNoAction,                         BeaconNoAction,                     BeaconNoAction},//No use.Just for _BEACON_ADVANCED_OSD_SELECT_COLOR_END

//Advance OSD Color adjust parameter
  { BeaconAdvancedColorMenuExit,    BeaconADColorAdjustAspectSelect,        BeaconADColorAdjustAspectSelect,        BeaconAdvancedColorMenuExit},
  { BeaconAdvancedColorMenuExit,    BeaconADColorAdjustAspectRatio,         BeaconADColorAdjustAspectRatio,         BeaconAdvancedColorMenuExit},
  { BeaconAdvancedColorMenuExit,    BeaconADColorAdjustBrightness,          BeaconADColorAdjustBrightness,          BeaconAdvancedColorMenuExit},
  { BeaconAdvancedColorMenuExit,    BeaconADColorAdjustColorTempType,       BeaconADColorAdjustColorTempType,       BeaconAdvancedColorMenuExit},
  { BeaconAdvancedColorMenuExit,    BeaconADColorAdjustColorTempTypeUserR,  BeaconADColorAdjustColorTempTypeUserR,  BeaconAdvancedColorMenuExit},
  { BeaconAdvancedColorMenuExit,    BeaconADColorAdjustColorTempTypeUserG,  BeaconADColorAdjustColorTempTypeUserG,  BeaconAdvancedColorMenuExit},
  { BeaconAdvancedColorMenuExit,    BeaconADColorAdjustColorTempTypeUserB,  BeaconADColorAdjustColorTempTypeUserB,  BeaconAdvancedColorMenuExit},
  { BeaconAdvancedColorMenuExit,    BeaconNoAction,                         BeaconNoAction,                         BeaconAdvancedColorMenuExit},

  { BeaconAdvancedPageMenu,         BeaconAdvancedPageSelectNext,           BeaconAdvancedPageSelectNext,           BeaconAdvancedPageExit},
  
//Advance OSD Image select part
  { BeaconAdvancedImageMenuItem,    BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageExitItem},
  { BeaconAdvancedImageMenuItem,    BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageExitItem},
  { BeaconAdvancedImageMenuItem,    BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageExitItem},
  { BeaconAdvancedImageMenuItem,    BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageExitItem},
  { BeaconAdvancedImageMenuItem,    BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageExitItem},
  { BeaconAdvancedImageMenuItem,    BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageSelectNextItem,      BeaconAdvancedImageExitItem},

  { BeaconNoAction,                 BeaconNoAction,                         BeaconNoAction,                         BeaconNoAction},//No use.Just for _BEACON_ADVANCED_OSD_SELECT_IMAGE_END

//Advance OSD Image adjust parameter
  { BeaconAdvancedImageMenuExit,    BeaconNoAction,                         BeaconNoAction,                         BeaconAdvancedImageMenuExit},
  { BeaconAdvancedImageMenuExit,    BeaconADImageAdjustAnologHpos,          BeaconADImageAdjustAnologHpos,          BeaconAdvancedImageMenuExit},
  { BeaconAdvancedImageMenuExit,    BeaconADImageAdjustAnologVpos,          BeaconADImageAdjustAnologVpos,          BeaconAdvancedImageMenuExit},
  { BeaconAdvancedImageMenuExit,    BeaconADImageAdjustAnologClock,         BeaconADImageAdjustAnologClock,         BeaconAdvancedImageMenuExit},
  { BeaconAdvancedImageMenuExit,    BeaconADImageAdjustAnologPhase,         BeaconADImageAdjustAnologPhase,         BeaconAdvancedImageMenuExit},
  { BeaconAdvancedImageMenuExit,    BeaconNoAction,                         BeaconNoAction,                         BeaconAdvancedImageMenuExit},

  { BeaconAdvancedPageMenu,         BeaconAdvancedPageSelectNext,           BeaconAdvancedPageSelectNext,           BeaconAdvancedPageExit},

//Advance OSD Setting select part
  { BeaconAdvancedSettingMenuItem,  BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingExitItem},
  { BeaconAdvancedSettingMenuItem,  BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingExitItem},
  { BeaconAdvancedSettingMenuItem,  BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingExitItem},
  { BeaconAdvancedSettingMenuItem,  BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingExitItem},
  { BeaconAdvancedSettingMenuItem,  BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingExitItem},
  { BeaconAdvancedSettingMenuItem,  BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingSelectNextItem,    BeaconAdvancedSettingExitItem},

  { BeaconNoAction,                 BeaconNoAction,                         BeaconNoAction,                         BeaconNoAction},//No use.Just for _BEACON_ADVANCED_OSD_SELECT_SETTING_END

//Advance OSD Setting adjust parameter
  { BeaconAdvancedSettingMenuExit,  BeaconADSettingAdjustOSDHpos,           BeaconADSettingAdjustOSDHpos,           BeaconAdvancedSettingMenuExit},
  { BeaconAdvancedSettingMenuExit,  BeaconADSettingAdjustOSDVpos,           BeaconADSettingAdjustOSDVpos,           BeaconAdvancedSettingMenuExit},
  { BeaconAdvancedSettingMenuExit,  BeaconADSettingAdjustOSDTime,           BeaconADSettingAdjustOSDTime,           BeaconAdvancedSettingMenuExit},
  { BeaconAdvancedSettingMenuExit,  BeaconNoAction,                         BeaconNoAction,                         BeaconAdvancedSettingMenuExit},
  { BeaconAdvancedSettingMenuExit,  BeaconNoAction,                         BeaconNoAction,                         BeaconAdvancedSettingMenuExit},
  { BeaconAdvancedSettingMenuExit,  BeaconNoAction,                         BeaconNoAction,                         BeaconAdvancedSettingMenuExit},

  { BeaconNoAction,                 BeaconNoAction,                         BeaconNoAction,                         BeaconNoAction},//No use.Just for _BEACON_ADVANCED_OSD_ADJUST_SETTING_END

//Hotkey select Part
  { BeaconHotkeyOSDMenu,            BeaconHotkeyOSDBacklightAdjust,         BeaconHotkeyOSDBacklightAdjust,         BeaconExitItem},//_BEACON_HOTKEY_OSD_1 Backlight
  { BeaconHotkeyOSDMenu,            BeaconHotkeyOSDContrastAdjust,          BeaconHotkeyOSDContrastAdjust,          BeaconExitItem},//_BEACON_HOTKEY_OSD_2 Contrast
  { BeaconNoAction,                 BeaconNoAction,                         BeaconNoAction,                         BeaconNoAction},///No use.Just for _BEACON_HOTKEY_OSD_END

};

#endif//#if(_OSD_TYPE == _BEACON_OSD)
