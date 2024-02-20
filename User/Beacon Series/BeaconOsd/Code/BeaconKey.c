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
// ID Code      : NoneKey.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_KEY__

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
BYTE g_ucKeyStatePrev;
BYTE g_ucKeyStateCurr;

#if(_AD_KEY_SUPPORT == _ON)
BYTE g_ucBackupKeyState = 0xFF;
#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
BYTE g_ucKeyFlag = 0;

#define GET_POWERKEY_STATE()                        ((bit)(g_ucKeyFlag & _BIT0))
#define SET_POWERKEY_STATE()                        (g_ucKeyFlag |= _BIT0)
#define CLR_POWERKEY_STATE()                        (g_ucKeyFlag &= ~_BIT0)

#define GET_RESETKEY_STATE()                        ((bit)(g_ucKeyFlag & _BIT1))
#define SET_RESETKEY_STATE()                        (g_ucKeyFlag |= _BIT1)
#define CLR_RESETKEY_STATE()                        (g_ucKeyFlag &= ~_BIT1)

#define GET_FACTORYKEY_STATE()                      ((bit)(g_ucKeyFlag & _BIT2))
#define SET_FACTORYKEY_STATE()                      (g_ucKeyFlag |= _BIT2)
#define CLR_FACTORYKEY_STATE()                      (g_ucKeyFlag &= ~_BIT2)

#define GET_ADVANCEKEY_STATE()                      ((bit)(g_ucKeyFlag & _BIT3))
#define SET_ADVANCEKEY_STATE()                      (g_ucKeyFlag |= _BIT3)
#define CLR_ADVANCEKEY_STATE()                      (g_ucKeyFlag &= ~_BIT3)
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceKeyHandler(void);
void NoneKeyInitial(void);
bit NoneKeyScanReady(void);
BYTE NoneKeyScan(void);
bit NoneKeyPowerKeyProc(void);
void NoneKeyPowerKeyMix(void);
void NoneKeyMessageProc(void);
void NoneKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Key Handler, executed in the main loop.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyHandler(void)
{
    // Clear the key message
    if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)
    {
        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
    }

    if(NoneKeyScanReady() == _TRUE)
    {
        // Store previous key state
        g_ucKeyStatePrev = g_ucKeyStateCurr;

        // Get current key state
        g_ucKeyStateCurr = NoneKeyScan();
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
        if(g_ucKeyStateCurr == 0)
        {
            if(GET_UARTKEYSTATE() != 0)
            {
                g_ucKeyStateCurr = GET_UARTKEYSTATE();
                SET_UARTKEYSTATE(0);
            }
        }
#endif
        
        // Power key process, return if power key is pressed
        if(NoneKeyPowerKeyProc() == _TRUE)
        {
            return;
        }

        // Convert key state to key message, store in (ucKeyNotify)
        NoneKeyMessageProc();
    }
}

//--------------------------------------------------
// Description  : Key intial.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneKeyInitial(void)
{
    CLR_KEYSCANREADY();
    CLR_KEYSCANSTART();

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
    SET_UARTKEYSTATE(0);
#endif
}

//--------------------------------------------------
// Description  : Key scan ready process. We wait 0.02 sec in order to keep the keypad debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit NoneKeyScanReady(void)
{
    BYTE ucShow = 0;

    if((GET_KEYSCANSTART() == _TRUE) &&
       (GET_KEYSCANREADY() == _TRUE))
    {
        return _TRUE;
    }
    else if(GET_KEYSCANSTART() == _FALSE)
    {
        // Set Scan start flag.
        SET_KEYSCANSTART();

        //SET_KEYSCANREADY();
        // Wait 0.02 sec in order to keep the keypad debounce
        ScalerTimerReactiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_KEY_SCAN_READY);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE NoneKeyScan(void)
{
    BYTE ucKeyState = 0;
    BYTE ucVoltage0 = 0;
    BYTE ucVoltage1 = 0;
    BYTE ucVoltage2 = 0;
    BYTE ucVoltage3 = 0;
    BYTE preKeyState = 0;

#if(_AD_KEY_SUPPORT == _ON)
    ucVoltage0 = (PCB_ADKEY0() & 0xFC);
    ucVoltage1 = (PCB_ADKEY1() & 0xFC);
    ucVoltage2 = (PCB_ADKEY2() & 0xFC);
    ucVoltage3 = (PCB_ADKEY3() & 0xFC);

    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);
    //DebugMessageAnalog("GET_KEYSCANSTART",_FALSE);
    if(ucVoltage1 < 248)
    {
        DebugMessageSystem(" ucVoltage1= ", ucVoltage1);
    }
    if(ucVoltage2 < 248)
    {
        DebugMessageSystem(" ucVoltage2= ", ucVoltage2);
    }

    preKeyState = ucKeyState;
    
    if(g_ucBackupKeyState == ucKeyState)
    {
        if(ucKeyState != 0)
        {
            NoneKeyInitial();
        }

        return g_ucBackupKeyState;
    }

    if(ucKeyState != 0)
    {
        ScalerTimerDelayXms(5);

        ucVoltage0 = (PCB_ADKEY0() & 0xFC);
        ucVoltage1 = (PCB_ADKEY1() & 0xFC);
        ucVoltage2 = (PCB_ADKEY2() & 0xFC);
        ucVoltage3 = (PCB_ADKEY3() & 0xFC);

        ucKeyState = 0;

        PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);

        if(preKeyState != ucKeyState)
        {
            ucKeyState = 0;
        }
        else
        {
            g_ucBackupKeyState = ucKeyState;
        }
    }
    else
    {   
        g_ucBackupKeyState = ucKeyState;
    }
#else
    preKeyState = ucKeyState;
    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);    
#endif // End of #if(_AD_KEY_SUPPORT == _ON)
   
    if(ucKeyState != 0)
    {
        NoneKeyInitial();
    }

    return ucKeyState;
}


//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit NoneKeyPowerKeyProc(void)
{
    if((g_ucKeyStateCurr & _POWER_KEY_MASK) == _POWER_KEY_MASK)
    {
        if(((g_ucKeyStatePrev ^ g_ucKeyStateCurr) & _POWER_KEY_MASK) != 0)
        {
            NoneKeyPowerKeyMix();

            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
#if(_CUSTOMER == _CUS_TOSHIBA)
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_KEY_POWER_ON_OFF);
#else
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
#endif
            }
            else
            {
#if(_CUSTOMER == _CUS_TOSHIBA)
                ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_KEY_POWER_ON_OFF);
#else
                SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
#endif
            }

            return _TRUE;
        }
    }

    return _FALSE;

}

//--------------------------------------------------
// Description  : We can add some settings here while combo key with power key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneKeyPowerKeyMix(void)
{
#if(_CUSTOMER != _CUS_TOSHIBA)
    switch(g_ucKeyStateCurr)
    {
        case _POWER_RIGHT_KEY_MASK:
            break;

        case _POWER_MENU_KEY_MASK:
            break;

        case _POWER_LEFT_RIGHT_KEY_MASK:
            break;

        default:
            break;
    }
#endif
}


//--------------------------------------------------
// Description  : Convert keypad status into key message, stores in ucKeyNotify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneKeyMessageProc(void)
{
#if(_CUSTOMER == _CUS_TOSHIBA)
#if(_USER_BEACON_FACTORY_OSD == _ON)
    if(!g_ucBeaconFacOsdShowFlag)
#endif
    {
        if((GET_OSD_STATE()  >_BEACON_OSD_NONE) && (GET_OSD_STATE() < _BEACON_OSD_SELECT_END))
        {
            if(g_ucKeyStateCurr == _MENU_KEY_MASK)
            {
                if(GET_KEY_HOLD_ON()==_OFF)
                    g_ucKeyStateCurr = _RIGHT_KEY_MASK;
            }
            else if(g_ucKeyStateCurr == _EXIT_KEY_MASK)
            {
                if(GET_KEY_HOLD_ON()==_OFF)
                    g_ucKeyStateCurr = _LEFT_KEY_MASK;
            }
            else if(g_ucKeyStateCurr == _RIGHT_KEY_MASK)
            {
                if(GET_OSD_STATE() == _BEACON_OSD_9) //default
                    g_ucKeyStateCurr = _MENU_KEY_MASK;
                else
                    BeaconMenuItem();
            }
            else if(g_ucKeyStateCurr ==  _LEFT_KEY_MASK)
            {
                if(GET_OSD_STATE() == _BEACON_OSD_9) //default
                    g_ucKeyStateCurr = _MENU_KEY_MASK;
                else
                    BeaconMenuItem();
            }

        }
    }
#endif

    switch(g_ucKeyStateCurr)
    {
        case _MENU_KEY_MASK:
            CLR_KEYREPEATENABLE(); 
#if(_CUSTOMER == _CUS_TOSHIBA)
            if((GET_OSD_STATE() > _BEACON_OSD_SELECT_END) && (GET_OSD_STATE() < _BEACON_OSD_ADJUST_END))
                SET_KEY_HOLD_ON();
            else
                CLR_KEY_HOLD_ON();
#else
            CLR_KEY_HOLD_ON();
#endif
            NoneKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
            break;

        case _RIGHT_KEY_MASK:    
            if(GET_OSD_STATE() != _BEACON_OSD_NONE)
            {
                SET_KEYREPEATENABLE();
            }
            if(GET_OSD_STATE() == _BEACON_OSD_NONE)
            {
                SET_KEY_HOLD_ON();
            }
#if(_USER_BEACON_FACTORY_OSD == _ON)
            if(g_ucBeaconFacOsdShowFlag)
            {
                SET_KEYREPEATENABLE();
                CLR_KEY_HOLD_ON();
            }
#endif
            if(((_BEACON_OSD_SELECT_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_OSD_ADJUST_END))||
                ((_BEACON_ADVANCED_OSD_SELECT_COLOR_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_ADVANCED_OSD_ADJUST_COLOR_END))||
                ((_BEACON_ADVANCED_OSD_SELECT_IMAGE_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_ADVANCED_OSD_ADJUST_IMAGE_END))||
                ((_BEACON_ADVANCED_OSD_SELECT_SETTING_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_HOTKEY_OSD_END)))
            {
                NoneKeyMessageConvert(_RIGHT_KEY_MASK, _LEFT_KEY_MESSAGE);
            }
            else
            {
                NoneKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            }
            break;

        case _LEFT_KEY_MASK:        
            if(GET_OSD_STATE() != _BEACON_OSD_NONE)
            {
                SET_KEYREPEATENABLE();
            }
            if(GET_OSD_STATE() == _BEACON_OSD_NONE)
            {
                SET_KEY_HOLD_ON();
            }
#if(_USER_BEACON_FACTORY_OSD == _ON)
            if(g_ucBeaconFacOsdShowFlag)
            {
                SET_KEYREPEATENABLE();
                CLR_KEY_HOLD_ON();
            }
#endif      
            if(((_BEACON_OSD_SELECT_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_OSD_ADJUST_END))||
                ((_BEACON_ADVANCED_OSD_SELECT_COLOR_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_ADVANCED_OSD_ADJUST_COLOR_END))||
                ((_BEACON_ADVANCED_OSD_SELECT_IMAGE_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_ADVANCED_OSD_ADJUST_IMAGE_END))||
                ((_BEACON_ADVANCED_OSD_SELECT_SETTING_END < GET_OSD_STATE())&&(GET_OSD_STATE() < _BEACON_HOTKEY_OSD_END)))
            {
                NoneKeyMessageConvert(_LEFT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            }
            else
            {
                NoneKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
            }
            break;

        case _EXIT_KEY_MASK:
            CLR_KEYREPEATENABLE();
#if(_CUSTOMER == _CUS_TOSHIBA)
            if((GET_OSD_STATE() > _BEACON_OSD_SELECT_END) && (GET_OSD_STATE() < _BEACON_OSD_ADJUST_END))
                SET_KEY_HOLD_ON();
            else
                CLR_KEY_HOLD_ON();
#else
            CLR_KEY_HOLD_ON();
#endif
            NoneKeyMessageConvert(_EXIT_KEY_MASK, _EXIT_KEY_MESSAGE);
            if((GET_OSD_STATE() == _BEACON_OSD_NONE))
            {
                ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_HOTKEY_ENTER_AUTO_ADJUST);
            }
            break;

        case _LEFT_RIGHT_KEY_MASK:
#if(_CUSTOMER == _CUS_TOSHIBA)
        case _SERVISE_KEY_MASK:
        case _FACTORY_KEY_MASK:        
#endif
            DebugMessageSystem(" _LEFT_RIGHT_KEY_MASK= ", _LEFT_RIGHT_KEY_MASK);   
            CLR_KEYREPEATENABLE();
            CLR_KEY_HOLD_ON();
            NoneKeyMessageConvert(_LEFT_RIGHT_KEY_MASK, _LEFT_RIGHT_MESSAGE);
#if(_CUSTOMER == _CUS_TOSHIBA)
            if(g_ucKeyStateCurr == _LEFT_RIGHT_KEY_MASK)
            {
                if(!g_ucBeaconFacOsdShowFlag)
                {
                    if(GET_RESETKEY_STATE() == 0)
                    {
                        SET_RESETKEY_STATE();
                        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_KEY_RESET);
                    }

                    if((GET_OSD_STATE() != _BEACON_OSD_NONE) && (GET_OSD_STATE() < _BEACON_OSD_ADJUST_END))
                        ScalerTimerReactiveTimerEvent(SEC(3+GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);

                }
            }
            else if(g_ucKeyStateCurr == _SERVISE_KEY_MASK)
            {
                if((GET_OSD_STATE() == _BEACON_OSD_NONE) && (!g_ucBeaconFacOsdShowFlag))
                {
                    if(GET_ADVANCEKEY_STATE() == 0)
                    {
                        SET_ADVANCEKEY_STATE();
                        ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_HOTKEY_ENTER_ADVANCED_OSD);
                        ScalerTimerReactiveTimerEvent(SEC(3+GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                }
            }
            else if(g_ucKeyStateCurr == _FACTORY_KEY_MASK)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    if(GET_OSD_STATE() != _BEACON_OSD_NONE)
                    {
                        if(GET_FACTORYKEY_STATE() == 0)
                        {
                            SET_FACTORYKEY_STATE();
                            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_HOTKEY_ENTER_FACTORY_OSD);
                        }
                    }
                }
            }
#else         
            if((GET_OSD_STATE() != _BEACON_OSD_NONE)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_1)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_2))
            {
                ScalerTimerActiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_HOTKEY_ENTER_ADVANCED_OSD);
            }
            else if(GET_OSD_STATE() == _BEACON_OSD_NONE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
#if(_KEY_FUNCTION_BUG == _ON)
                    if(GET_PANELPOWERSTATUS() == _PANEL_POWER_OFF_STATE)
                    {
                        UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
                    }
#endif

                    ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_HOTKEY_ENTER_FACTORY_OSD);             
                }
            }
#endif
            break;

        default:
            if(GET_KEY_HOLD_ON()==_ON)
            {
                SET_KEYMESSAGE(GET_KEY_BACKUP_MESSAGE());
            }
            CLR_KEY_HOLD_ON();
            CLR_KEYREPEATSTART();
            CLR_KEYREPEATENABLE();
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
            break;
    }
#if(_CUSTOMER == _CUS_TOSHIBA)
    if((g_ucKeyStateCurr != _LEFT_RIGHT_KEY_MASK) && (g_ucKeyStateCurr != _SERVISE_KEY_MASK) && (g_ucKeyStateCurr != _FACTORY_KEY_MASK) && (g_ucKeyStateCurr != _LEFT_RIGHT_KEY_MASK))//No release adjusting left and right may enter there event.There cancel event
    {
        CLR_RESETKEY_STATE();
        CLR_FACTORYKEY_STATE();
        CLR_ADVANCEKEY_STATE();
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_RESET);
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HOTKEY_ENTER_ADVANCED_OSD);
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HOTKEY_ENTER_FACTORY_OSD);
    }
#else
    if(g_ucKeyStateCurr != _LEFT_RIGHT_KEY_MASK)//No release adjusting left and right may enter there event.There cancel event
    {
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HOTKEY_ENTER_ADVANCED_OSD);
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HOTKEY_ENTER_FACTORY_OSD);
    }
#endif 

    if(g_ucKeyStateCurr != _EXIT_KEY_MASK)
    {
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HOTKEY_ENTER_AUTO_ADJUST);
    }


}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void NoneKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg)
{
    if(((g_ucKeyStatePrev ^ g_ucKeyStateCurr) & ucKeyMask) != 0)
    {
        if(GET_KEY_HOLD_ON()==_ON)
            SET_KEY_BACKUP_MESSAGE(ucKeyMsg);
        else
            SET_KEYMESSAGE(ucKeyMsg);
    }
    else
    {
        if(GET_KEYREPEATENABLE() == _TRUE)
        {
            if(GET_KEYREPEATSTART() == _TRUE)
            {
                SET_KEYMESSAGE(ucKeyMsg);
            }
            else
            {
                // Set repeat key after 20ms.//-->130ms
                ScalerTimerActiveTimerEvent(SEC(0.13), _USER_TIMER_EVENT_KEY_REPEAT_ENABLE); //C.J. Timer
            }
        }
    }
}

#endif//#if(_OSD_TYPE == _BEACON_OSD)
