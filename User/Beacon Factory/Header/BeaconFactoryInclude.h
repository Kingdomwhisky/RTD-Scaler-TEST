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

//----------------------------------------------------------------------------------------
// Extern functions from FactoryFunction.c
//----------------------------------------------------------------------------------------
#if(_USER_BEACON_FACTORY_OSD == _ON)

#define _OSD_FACTORY_COL_SIZE                           24
#define _OSD_FACTORY_ROW_SIZE                           21

#define _OSD_PARAMETER_COL                              21

#define _MONITOR_SN_LENGTH                              25

#define _DDC2B_CMD_FACTORY_GAMMA_ADJUST                 0xC0
#define _CMD_SET_KEY                                    0x96

//#define ScalerSetByte(pucAddr, ucValue)             (*((volatile BYTE xdata *)(pucAddr)) = (ucValue))
//#define ScalerSetBit(pucAddr, ucAnd, ucOr)          (*((volatile BYTE xdata *)(pucAddr)) = (*((volatile BYTE xdata *)(pucAddr)) & (ucAnd)) | (ucOr))

//****************************************************************************
//    STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef struct
{
    BYTE ucBeaconFacCTType;
    BYTE ucBeaconFacDBrightness;
    BYTE ucBeaconFacContrast;
    BYTE ucBeaconFacBacklight;
    BYTE ucBeaconFacBLMAX;
    BYTE ucBeaconFacBLMID;
    BYTE ucBeaconFacBLMIN;
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
    BYTE ucSecondBeaconFacBLMAX;
    BYTE ucSecondBeaconFacBLMID;
    BYTE ucSecondBeaconFacBLMIN;
#endif    
    BYTE ucBeaconFacGamma;
    BYTE ucBeaconFacBurn : 1;
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
    BYTE ucBeaconFacPin62Pin63Func : 1;
#endif
    BYTE ucBeaconDdcciChannel : 3; 
    BYTE ucBeaconFMDIV : 1;    //ucBeaconFMDIV
#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
    BYTE ucBeaconLoadGammaFromEeprom : 1;
    BYTE ucBeaconSaveGammaToEeprom : 1;
#endif
#if(_ALS_TYPE != _SENSER_NONE)
    BYTE ucBeaconALS : 1;
#endif
    BYTE ucBeaconEdidProtect : 1;   //reserve
    BYTE ucLockState : 1;
#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
    BYTE bBackLightSensor_ONOFF : 1;   
#endif    
//<14 bytes

}StructBeaconFacType;

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
typedef struct
{
    WORD tR;
    WORD tG;
    WORD tB;
}StructGammaRGBType;
#endif


//****************************************************************************
// LAYER DEFINITIONS / MACROS 
//****************************************************************************
//--------------------------------------------------
// MACRO for Beacon Factory parameter
//--------------------------------------------------

#define GET_FACTORY_GAMMA()                     (g_stBeaconFacData.ucBeaconFacGamma)
#define SET_FACTORY_GAMMA(x)                    {\
                                                    g_stBeaconFacData.ucBeaconFacGamma= x;\
                                                }
#define GET_FACTORY_COLORTEMP()                 (g_stBeaconFacData.ucBeaconFacCTType)
#define SET_FACTORY_COLORTEMP(x)                {\
                                                    g_stBeaconFacData.ucBeaconFacCTType= x;\
                                                }

#define GET_FACTORY_DBRIGHTNESS()               (g_stBeaconFacData.ucBeaconFacDBrightness)
#define SET_FACTORY_DBRIGHTNESS(x)              {\
                                                    g_stBeaconFacData.ucBeaconFacDBrightness= x;\
                                                }

#define GET_FACTORY_CONTRAST()                  (g_stBeaconFacData.ucBeaconFacContrast)
#define SET_FACTORY_CONTRAST(x)                 {\
                                                    g_stBeaconFacData.ucBeaconFacContrast= x;\
                                                }

#define GET_FACTORY_BACKLIGHT()                 (g_stBeaconFacData.ucBeaconFacBacklight)
#define SET_FACTORY_BACKLIGHT(x)                {\
                                                    g_stBeaconFacData.ucBeaconFacBacklight= x;\
                                                }

#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
#if(_CUSTOMER == _CUS_BAISHENG)
#define GET_FACTORY_BACKLIGHT_REG_MAX(x)        (x == 0 ? g_stBeaconFacData.ucBeaconFacBLMAX : g_stBeaconFacData.ucSecondBeaconFacBLMAX)
#define SET_FACTORY_BACKLIGHT_REG_MAX(x,y)      {\
                                                    if(x == 0)\
                                                        g_stBeaconFacData.ucBeaconFacBLMAX = y;\
                                                    else\
                                                        g_stBeaconFacData.ucSecondBeaconFacBLMAX = y;\
                                                }

#define GET_FACTORY_BACKLIGHT_REG_MID(x)        (x == 0 ? g_stBeaconFacData.ucBeaconFacBLMID : g_stBeaconFacData.ucSecondBeaconFacBLMID)
#define SET_FACTORY_BACKLIGHT_REG_MID(x,y)      {\
                                                    if(x == 0)\
                                                        g_stBeaconFacData.ucBeaconFacBLMID = y;\                                                 
                                                    else\
                                                        g_stBeaconFacData.ucSecondBeaconFacBLMID = y;\
                                                }

#define GET_FACTORY_BACKLIGHT_REG_MIN(x)        (x == 0 ? g_stBeaconFacData.ucBeaconFacBLMIN : g_stBeaconFacData.ucSecondBeaconFacBLMIN)
#define SET_FACTORY_BACKLIGHT_REG_MIN(x,y)      {\
                                                    if(x == 0)\
                                                        g_stBeaconFacData.ucBeaconFacBLMIN = y;\                                               
                                                    else\
                                                        g_stBeaconFacData.ucSecondBeaconFacBLMIN = y;\
                                                }
#else
#define GET_FACTORY_BACKLIGHT_REG_MAX(x)        (x == 1 ? g_stBeaconFacData.ucSecondBeaconFacBLMAX : g_stBeaconFacData.ucBeaconFacBLMAX)
#define SET_FACTORY_BACKLIGHT_REG_MAX(x,y)      {\
                                                    if(x == 1)\
                                                        g_stBeaconFacData.ucSecondBeaconFacBLMAX = y;\
                                                    else\
                                                        g_stBeaconFacData.ucBeaconFacBLMAX = y;\
                                                }

#define GET_FACTORY_BACKLIGHT_REG_MID(x)        (x == 1 ? g_stBeaconFacData.ucSecondBeaconFacBLMID : g_stBeaconFacData.ucBeaconFacBLMID)
#define SET_FACTORY_BACKLIGHT_REG_MID(x,y)      {\
                                                    if(x == 1)\
                                                        g_stBeaconFacData.ucSecondBeaconFacBLMID = y;\                                                 
                                                    else\
                                                        g_stBeaconFacData.ucBeaconFacBLMID = y;\
                                                }

#define GET_FACTORY_BACKLIGHT_REG_MIN(x)        (x == 1 ? g_stBeaconFacData.ucSecondBeaconFacBLMIN : g_stBeaconFacData.ucBeaconFacBLMIN)
#define SET_FACTORY_BACKLIGHT_REG_MIN(x,y)      {\
                                                    if(x == 1)\
                                                        g_stBeaconFacData.ucSecondBeaconFacBLMIN = y;\                                               
                                                    else\
                                                        g_stBeaconFacData.ucBeaconFacBLMIN = y;\
                                                }
#endif
#else
#define GET_FACTORY_BACKLIGHT_REG_MAX()         (g_stBeaconFacData.ucBeaconFacBLMAX)
#define SET_FACTORY_BACKLIGHT_REG_MAX(x)        {\
                                                    g_stBeaconFacData.ucBeaconFacBLMAX= x;\
                                                }

#define GET_FACTORY_BACKLIGHT_REG_MID()         (g_stBeaconFacData.ucBeaconFacBLMID)
#define SET_FACTORY_BACKLIGHT_REG_MID(x)        {\
                                                    g_stBeaconFacData.ucBeaconFacBLMID= x;\
                                                }

#define GET_FACTORY_BACKLIGHT_REG_MIN()         (g_stBeaconFacData.ucBeaconFacBLMIN)
#define SET_FACTORY_BACKLIGHT_REG_MIN(x)        {\
                                                    g_stBeaconFacData.ucBeaconFacBLMIN= x;\
                                                }
#endif

#define GET_FACTORY_BURN()                      (g_stBeaconFacData.ucBeaconFacBurn)
#define SET_FACTORY_BURN(x)                     {\
                                                    g_stBeaconFacData.ucBeaconFacBurn= x;\
                                                }
#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
#define GET_FACTORY_TEST_PIN_FUNC()             (g_stBeaconFacData.ucBeaconFacPin62Pin63Func)
#define SET_FACTORY_TEST_PIN_FUNC(x)            {\
                                                    g_stBeaconFacData.ucBeaconFacPin62Pin63Func= x;\
                                                }
#endif

#define GET_FACTORY_DDCCI_CHANNEL()             (g_stBeaconFacData.ucBeaconDdcciChannel)
#define SET_FACTORY_DDCCI_CHANNEL(x)            {\
                                                    g_stBeaconFacData.ucBeaconDdcciChannel= x;\
                                                }


#define GET_FACTORY_FMDIV()                     (g_stBeaconFacData.ucBeaconFMDIV)
#define SET_FACTORY_FMDIV(x)                    {\
                                                    g_stBeaconFacData.ucBeaconFMDIV= x;\
                                                }

#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)

#define GET_FACTORY_LOAD_GAMMA_FROM_EEPROM()    (g_stBeaconFacData.ucBeaconLoadGammaFromEeprom)
#define SET_FACTORY_LOAD_GAMMA_FROM_EEPROM(x)   {\
                                                    g_stBeaconFacData.ucBeaconLoadGammaFromEeprom= x;\
                                                }
#define GET_FACTORY_SAVE_GAMMA_TO_EEPROM()      (g_stBeaconFacData.ucBeaconSaveGammaToEeprom)
#define SET_FACTORY_SAVE_GAMMA_TO_EEPROM(x)     {\
                                                    g_stBeaconFacData.ucBeaconSaveGammaToEeprom= x;\
                                                }
#endif

#define GET_FACTORY_EDID_PROTECT()              (g_stBeaconFacData.ucBeaconEdidProtect)
#define SET_FACTORY_EDID_PROTECT(x)             {\
                                                    g_stBeaconFacData.ucBeaconEdidProtect= x;\
                                                }

#define GET_FAC_ADJUST_HSTART()                 (g_ucFactoryAdjustHstart)
#define SET_FAC_ADJUST_HSTART(x)                {\
                                                    g_ucFactoryAdjustHstart= x;\
                                                }
#define GET_FAC_ADJUST_VSTART()                 (g_ucFactoryAdjustVstart)
#define SET_FAC_ADJUST_VSTART(x)                {\
                                                    g_ucFactoryAdjustVstart= x;\
                                                }

#if(_ALS_TYPE != _SENSER_NONE)

#define GET_FACTORY_ALS()                       (g_stBeaconFacData.ucBeaconALS)
#define SET_FACTORY_ALS(x)                      {\
                                                    g_stBeaconFacData.ucBeaconALS= x;\
                                                }
#endif

#define GET_FACTORY_LOCK_STATE()                (g_stBeaconFacData.ucLockState)
#define SET_FACTORY_LOCK_STATE(x)               {\
                                                    g_stBeaconFacData.ucLockState= x;\
                                                }

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
#define GET_BACKLIGHTSENSOR_ONOFF()             (g_stBeaconFacData.bBackLightSensor_ONOFF)
#define SET_BACKLIGHTSENSOR_ONOFF(x)            {\
                                                    if(x == 0)\
                                                        g_stBeaconFacData.bBackLightSensor_ONOFF = _OFF;\                                                 
                                                    else\
                                                        g_stBeaconFacData.bBackLightSensor_ONOFF = _ON;\
                                                }
#endif

#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
#define GET_BACKLIGHT_COM()                     ((bit)(ucIICControl1 & _BIT0))
#define SET_BACKLIGHT_COM()                     (ucIICControl1 |= _BIT0)
#define CLR_BACKLIGHT_COM()                     (ucIICControl1 &= ~_BIT0)

#define GET_DEFAULT_COM()                       ((bit)(ucIICControl1 & _BIT1))
#define SET_DEFAULT_COM()                       (ucIICControl1 |= _BIT1)
#define CLR_DEFAULT_COM()                       (ucIICControl1 &= ~_BIT1)

#define GET_CONTRAST_COM()                      ((bit)(ucIICControl1 & _BIT2))
#define SET_CONTRAST_COM()                      (ucIICControl1 |= _BIT2)
#define CLR_CONTRAST_COM()                      (ucIICControl1 &= ~_BIT2)

#define GET_GAMMA_COM()                         ((bit)(ucIICControl1 & _BIT3))
#define SET_GAMMA_COM()                         (ucIICControl1 |= _BIT3)
#define CLR_GAMMA_COM()                         (ucIICControl1 &= ~_BIT3)

#define GET_COLORTEMP_COM()                     ((bit)(ucIICControl1 & _BIT4))
#define SET_COLORTEMP_COM()                     (ucIICControl1 |= _BIT4)
#define CLR_COLORTEMP_COM()                     (ucIICControl1 &= ~_BIT4)

#define GET_COMMAND_STATE()                     ((bit)(ucIICControl1 & _BIT5))
#define SET_COMMAND_STATE()                     (ucIICControl1 |= _BIT5)
#define CLR_COMMAND_STATE()                     (ucIICControl1 &= ~_BIT5)

#define GET_CHECK_STATE()                       ((bit)(ucIICControl1 & _BIT6))
#define SET_CHECK_STATE()                       (ucIICControl1 |= _BIT6)
#define CLR_CHECK_STATE()                       (ucIICControl1 &= ~_BIT6)

#define GET_BRIGHTPION()                        ((bit)(ucIICControl1 & _BIT7))
#define SET_BRIGHTPION()                        (ucIICControl1 |= _BIT7)
#define CLR_BRIGHTPION()                        (ucIICControl1 &= ~_BIT7)

#define GET_GAMMA_ZERO()                        ((bit)(ucIICControl2 & _BIT0))
#define SET_GAMMA_ZERO()                        (ucIICControl2 |= _BIT0)
#define CLR_GAMMA_ZERO()                        (ucIICControl2 &= ~_BIT0)

#define GET_SCREENSAVE_COM()                    ((bit)(ucIICControl2 & _BIT1))
#define SET_SCREENSAVE_COM()                    (ucIICControl2|= _BIT1)
#define CLR_SCREENSAVE_COM()                    (ucIICControl2&= ~_BIT1)

#define GET_GAMMA_COM_FORGAMMA_ADJ()            ((bit)(ucIICControl2 & _BIT2))
#define SET_GAMMA_COM_FORGAMMA_ADJ()            (ucIICControl2 |= _BIT2)
#define CLR_GAMMA_COM_FORGAMMA_ADJ()            (ucIICControl2 &= ~ _BIT2)

#define GET_CALIBRATION_STRAT()                 ((bit)(ucIICControl2 & _BIT3))
#define SET_CALIBRATION_STRAT()                 (ucIICControl2 |= _BIT3)
#define CLR_CALIBRATION_STRAT()                 (ucIICControl2 &= ~_BIT3)

#define GET_MONITOR_SN_SAVE_COM()               ((bit)(ucIICControl2 & _BIT4))
#define SET_MONITOR_SN_SAVE_COM()               (ucIICControl2 |= _BIT4)
#define CLR_MONITOR_SN_SAVE_COM()               (ucIICControl2 &= ~_BIT4)

#define GET_MONITOR_SN_STATE()                  ((bit)(ucIICControl2 & _BIT5))
#define SET_MONITOR_SN_STATE()                  (ucIICControl2 |= _BIT5)
#define CLR_MONITOR_SN_STATE()                  (ucIICControl2 &= ~_BIT5)

#define GET_AutoColor()                         ((bit)(ucIICControl2 & _BIT6))
#define SET_AutoColor()                         (ucIICControl2 |= _BIT6)
#define CLR_AutoColor()                         (ucIICControl2 &= ~_BIT6)
#define GET_AutoAdjust()                        ((bit)(ucIICControl2 & _BIT7))
#define SET_AutoAdjust()                        (ucIICControl2 |= _BIT7)
#define CLR_AutoAdjust()                        (ucIICControl2 &= ~_BIT7)

#define GET_AUTO_COMPLETE()                     ((bit)(ucIICControl3&_BIT0))
#define SET_AUTO_COMPLETE()                     (ucIICControl3|=_BIT0)
#define CLR_AUTO_COMPLETE()                     (ucIICControl3&=~_BIT0)

#define GET_IIC_POWER_SWITCH_COM()              ((bit)(ucIICControl3&_BIT1))
#define SET_IIC_POWER_SWITCH_COM()              (ucIICControl3|=_BIT1)
#define CLR_IIC_POWER_SWITCH_COM()              (ucIICControl3&=~_BIT1)

#define GET_IIC_POWER_FLAG()                    ((bit)(ucIICControl3&_BIT2))
#define SET_IIC_POWER_FLAG()                    (ucIICControl3|=_BIT2)
#define CLR_IIC_POWER_FLAG()                    (ucIICControl3&=~_BIT2)


#define GET_IIC_DONE_STATE()                    ((bit)(ucIICControl3 & _BIT4))
#define SET_IIC_DONE_STATE()                    (ucIICControl3|= _BIT4)
#define CLR_IIC_DONE_STATE()                    (ucIICControl3&= ~_BIT4)

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
#define GET_IIC_SENSOR_BACKLIGHT_MID_STATE()    ((bit)(ucIICControl3 & _BIT5))
#define SET_IIC_SENSOR_BACKLIGHT_MID_STATE()    (ucIICControl3|= _BIT5)
#define CLR_IIC_SENSOR_BACKLIGHT_MID_STATE()    (ucIICControl3&= ~_BIT5)

#define GET_IIC_SENSOR_BACKLIGHT_STOP_STATE()   ((bit)(ucIICControl3 & _BIT6))
#define SET_IIC_SENSOR_BACKLIGHT_STOP_STATE()   (ucIICControl3|= _BIT6)
#define CLR_IIC_SENSOR_BACKLIGHT_STOP_STATE()   (ucIICControl3&= ~_BIT6)
#endif

#define GET_SEND_SENSOR_DATA()                  ((bit)(ucIICControl3&_BIT7))
#define SET_SEND_SENSOR_DATA()                  (ucIICControl3|=_BIT7)
#define CLR_SEND_SENSOR_DATA()                  (ucIICControl3&=~_BIT7)

//add yh_wang 13.12.27 start{
#define GET_SCREENSAVE_OFF_COM()                ((bit)(ucIICControl4 & _BIT0))
#define SET_SCREENSAVE_OFF_COM()                (ucIICControl4|= _BIT0)
#define CLR_SCREENSAVE_OFF_COM()                (ucIICControl4&= ~_BIT0)
//add yh_wang 13.12.27 end}

#define GET_SCREENSAVERS_FLAG()                 ((bit)(ucIICControl4 & _BIT1))
#define SET_SCREENSAVERS_FLAG(x)                (ucIICControl4 = ((ucIICControl4 & (~_BIT1)) | ( x<< 1)))
#define CLR_SCREENSAVERS_FLAG()                 (ucIICControl4 &=~_BIT1)
#define GET_DDCCI_COMMAND_STATE()               ((bit)(ucIICControl4 & _BIT1))
#define SET_DDCCI_COMMAND_STATE()               (ucIICControl4|= _BIT1)
#define CLR_DDCCI_COMMAND_STATE()               (ucIICControl4&= ~_BIT1)

#define GET_DDCCI_NEXTCOMMAND_ACCEPTABLE_STATE()    ((bit)(ucIICControl4 & _BIT2))
#define SET_DDCCI_NEXTCOMMAND_ACCEPTABLE_STATE()    (ucIICControl4|= _BIT2)
#define CLR_DDCCI_NEXTCOMMAND_ACCEPTABLE_STATE()    (ucIICControl4&= ~_BIT2)


#if( _SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
#define GET_GAMMA_RGB_OF_EEPROM()               ((bit)(ucIICControl4 & _BIT3))
#define SET_GAMMA_RGB_OF_EEPROM()               (ucIICControl4 |= _BIT3)
#define CLR_GAMMA_RGB_OF_EEPROM()               (ucIICControl4&= ~_BIT3)
#endif


#define GET_BRIGHTNESS_COM()                    ((bit)(ucIICControl4 & _BIT5))
#define SET_BRIGHTNESS_COM()                    (ucIICControl4 |= _BIT5)
#define CLR_BRIGHTNESS_COM()                    (ucIICControl4 &= ~_BIT5)

#endif

#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
#define GET_SaveGamma_OK_OF_FLASH()             ((bit)(ucIICControl4 & _BIT6))
#define SET_SaveGamma_OK_OF_FLASH()             (ucIICControl4 |= _BIT6)
#define CLR_SaveGamma_OK_OF_FLASH()             (ucIICControl4 &= ~_BIT6)

#define GET_CheckSum_OK_OF_FLASH()              ((bit)(ucIICControl4 & _BIT7))
#define SET_CheckSum_OK_OF_FLASH()              (ucIICControl4 |= _BIT7)
#define CLR_CheckSum_OK_OF_FLASH()              (ucIICControl4 &= ~_BIT7)

#define GET_SaveGammaOneTime_OK_OF_FLASH()      ((bit)(ucIICControl5 & _BIT0))
#define SET_SaveGammaOneTime_OK_OF_FLASH()      (ucIICControl5 |= _BIT0)
#define CLR_SaveGammaOneTime_OK_OF_FLASH()      (ucIICControl5 &= ~_BIT0)

#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#define GET_OLED_BACKLIGHT_MIN_STATE()          ((bit)(ucIICControl5 & _BIT1))
#define SET_OLED_BACKLIGHT_MIN_STATE()          (ucIICControl5 |= _BIT1)
#define CLR_OLED_BACKLIGHT_MIN_STATE()          (ucIICControl5 &= ~_BIT1)

#define GET_OLED_BACKLIGHT_MID_STATE()          ((bit)(ucIICControl5 & _BIT2))
#define SET_OLED_BACKLIGHT_MID_STATE()          (ucIICControl5 |= _BIT2)
#define CLR_OLED_BACKLIGHT_MID_STATE()          (ucIICControl5 &= ~_BIT2)

#define GET_OLED_BACKLIGHT_MAX_STATE()          ((bit)(ucIICControl5 & _BIT3))
#define SET_OLED_BACKLIGHT_MAX_STATE()          (ucIICControl5 |= _BIT3)
#define CLR_OLED_BACKLIGHT_MAX_STATE()          (ucIICControl5 &= ~_BIT3)
#endif

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
//--------------------------------------------------
// Definitions of Uart or IIC
//--------------------------------------------------
enum UartFunctionType
{
    _FACTORY_IIC_ENABLE,
    _FACTORY_UART_ENABLE,
};
#endif

//--------------------------------------------------
// Definitions of BeaconFactory OSD Flow
//--------------------------------------------------
#define _FAC_PAGE1_AMOUNT                       (_BEACON_FAC_OSD_SELECT_END - _BEACON_FAC_OSD_NONE - 1)
#define _FAC_PAGE2_AMOUNT                       (_BEACON_FAC_PAGE2_SELECT_END - _BEACON_FAC_PAGE2_START -1)
#define _FAC_PAGE3_AMOUNT                       (_BEACON_FAC_PAGE3_SELECT_END - _BEACON_FAC_PAGE3_START -1)
enum BeaconFacOsdPage1Ptr
{
    _BEACON_FAC_OSD_NONE = 0,
    _BEACON_FAC_OSD_AUTO_COLOR,
    _BEACON_FAC_OSD_GAMMA,
    _BEACON_FAC_OSD_DBRIGHTNESS,
    _BEACON_FAC_OSD_CONTRAST,
    _BEACON_FAC_OSD_BACKLIGHT,
    _BEACON_FAC_OSD_CT_TYPE,
    _BEACON_FAC_OSD_CT_R,
    _BEACON_FAC_OSD_CT_G,
    _BEACON_FAC_OSD_CT_B,
    _BEACON_FAC_OSD_BL_MAX,
    _BEACON_FAC_OSD_BL_MID,
    _BEACON_FAC_OSD_BL_MIN,
    _BEACON_FAC_OSD_BURN,
    _BEACON_FAC_OSD_SOURCE_DET_TYPE,//FAC_ADD_SOURCE_DET_ON_OFF_20151223
    _BEACON_FAC_OSD_RESET,
    _BEACON_FAC_OSD_PAGE2,
    _BEACON_FAC_OSD_EXIT,
    _BEACON_FAC_OSD_SELECT_END,

    _BEACON_FAC_OSD_ADJUST_END = _BEACON_FAC_OSD_SELECT_END + _FAC_PAGE1_AMOUNT + 1,

};
enum BeaconFacOsdPage2Ptr
{
    _BEACON_FAC_PAGE2_START = _BEACON_FAC_OSD_ADJUST_END,

    _BEACON_FAC_OSD_SHARPNESS,//SHARPNESS
    _BEACON_FAC_OSD_SATURATION,//SATURATION

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
    _BEACON_FAC_OSD_UART_ENABLE,
#endif
    _BEACON_FAC_OSD_TEST1,//HSTART
    _BEACON_FAC_OSD_TEST2,//VSTART
    _BEACON_FAC_OSD_TEST5,//SSC
    _BEACON_FAC_OSD_FMDVI,//FMDVI
    _BEACON_FAC_OSD_TEST6,//Edid write enable
    _BEACON_FAC_OSD_TEST7,//DDCCI CHANNGEL

#if(_SAVE_GAMMA_TO_EEPROM_ON_LINE == _ON)
    _BEACON_FAC_OSD_LOAD_GAMMA_FROM_EEPROM,
    _BEACON_FAC_OSD_SAVE_GAMMA_TO_EEPROM,//GAMMA IN EEPROM

#endif
#if(_ALS_TYPE != _SENSER_NONE)
    _BEACON_FAC_OSD_ALS,//ALS_SWITCH
#endif
    _BEACON_FAC_OSD_PAGE1,//PAGE1
    _BEACON_FAC_OSD_PAGE3,//PAGE3
    _BEACON_FAC_OSD_EXIT2,//EXIT2
    _BEACON_FAC_PAGE2_SELECT_END,

    _BEACON_FAC_PAGE2_ADJUST_END = _BEACON_FAC_PAGE2_SELECT_END + _FAC_PAGE2_AMOUNT + 1,

};

enum BeaconFacOsdPage3Ptr
{
    _BEACON_FAC_PAGE3_START = _BEACON_FAC_PAGE2_ADJUST_END,

#if(_SIX_COLOR_SUPPORT == _ON)
    _BEACON_FAC_PAGE3_ITEM1,//R SAT
    _BEACON_FAC_PAGE3_ITEM2,//Y SAT
    _BEACON_FAC_PAGE3_ITEM3,//G SAT	
    _BEACON_FAC_PAGE3_ITEM4,//C SAT
    _BEACON_FAC_PAGE3_ITEM5,//B SAT
    _BEACON_FAC_PAGE3_ITEM6,//M SAT
    _BEACON_FAC_PAGE3_ITEM7,//R HUE
    _BEACON_FAC_PAGE3_ITEM8,//Y HUE
    _BEACON_FAC_PAGE3_ITEM9,//G HUE
    _BEACON_FAC_PAGE3_ITEM10,//C HUE
    _BEACON_FAC_PAGE3_ITEM11,//B HUE
    _BEACON_FAC_PAGE3_ITEM12,//M HUE
#else
    _BEACON_FAC_PAGE3_ITEM1,//GAMMA BYPASS-> for testing lvds panel 
    _BEACON_FAC_PAGE3_ITEM2,//DCLK
    _BEACON_FAC_PAGE3_ITEM3,//PWM Freq --> for testing noise from adapter or pcb.
    _BEACON_FAC_PAGE3_ITEM4,//Flash wp
    _BEACON_FAC_PAGE3_ITEM5,//Gray level 0~255
#endif
    _BEACON_FAC_PAGE3_EXIT,//EXIT3

    _BEACON_FAC_PAGE3_SELECT_END,

    _BEACON_FAC_PAGE3_ADJUST_END = _BEACON_FAC_PAGE3_SELECT_END + _FAC_PAGE3_AMOUNT + 1,

};

#ifndef __BEACON_FACTORY_FUNC_
//****************************************************************************
// EXTEND VARIABLE DECLARATIONS 
//****************************************************************************
extern bit g_ucBeaconFacOsdShowFlag;
extern BYTE xdata g_ucBeaconFacOsdState;

//****************************************************************************
// EXTEND VARIABLE DECLARATIONS 
//****************************************************************************
extern void BeaconFactoryOsdMenuOperation(void);
extern void BeaconFactoryMenuItemSel(BYTE item,BYTE color);
#if(_ALS_TYPE != _SENSER_NONE)
extern bit BeaconFactoryAlsStatus();
#endif

#endif

#ifndef __BEACON_FACTORY_FUNC_
//****************************************************************************
// EXTEND VARIABLE DECLARATIONS 
//****************************************************************************
extern StructBeaconFacType g_stBeaconFacData;
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
extern StructGammaRGBType stGammaRGBdata;
extern BYTE xdata ucIICControl1;
extern BYTE xdata ucIICControl2;
extern BYTE xdata ucIICControl3;
extern BYTE xdata ucIICControl4;

extern BYTE xdata ucIICControl5;

#if( _SAVE_GAMMA_TO_EEPROM_ON_LINE	 == _ON)
extern WORD xdata usArray;
#endif

extern bit  idata g_bGammaByPass;
#endif

extern BYTE xdata ucMonitorSn[_MONITOR_SN_LENGTH];

#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
extern BYTE xdata g_ucGammaIndex;
extern WORD xdata g_usDataIndex;
extern BYTE xdata g_ucDataCount;
#endif

extern WORD xdata g_ucFactoryAdjustHstart;
extern WORD xdata g_ucFactoryAdjustVstart;
extern WORD xdata g_ucFactoryHstartMid;
extern WORD xdata g_ucFactoryVstartMid;

#if(_BACKLIGHT_SENSOR == _ENABLE)
extern WORD Value2561;
#endif

//****************************************************************************
// FUNCTION EXTERN of BeaconFactoryOsd.c
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
extern void BeaconFactoryAutoColor(void);
#endif
extern DWORD BeaconFactoryFuncValueChange(DWORD Value,DWORD MaxValue,DWORD MinValue,bit loop);
extern void BeaconFactoryFuncCalcStartAddress(BYTE ucRow, BYTE ucCol, BYTE ucIndicate);
extern void BeaconFactoryFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD usValue, BYTE ucPar);
extern void BeaconFactoryFuncHLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate);
extern void BeaconFactoryFuncLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE *pArray);
extern void BeaconFactoryFuncPrintASCII(BYTE ucRow,BYTE ucCol,BYTE ucLen, BYTE *pArray);
extern void BeaconFactoryFuncDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd,BYTE *pStyle);
extern void BeaconFactoryOsdPage2(void);
extern void BeaconFactoryOsdPage3(void);
//Use for othe file>>
extern void BeaconFactoryOsdPage1(void);
extern void BeaconFactoryFuncBurnInPattern(void);
extern void BeaconFactorySaveData(void);
extern void BeaconFactoryLoadData(void);
extern void BeaconFactoryRestoreData(void);
extern void BeaconFactorySaveMonitorSN(BYTE* pucData);
extern void BeaconFactoryLoadMonitorSN(BYTE* pucData);

#if(_USER_SHOW_DEBUG_OSD == _ON)
extern BYTE xdata g_ucDebugValue[40];
extern void BeaconDebugOsdInitial(void);
extern BYTE *BeaconDebugShowHex(BYTE ucDataArray);//00 ~FF
#endif
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
extern void BeaconFactoryDdcciCommand(void);
#endif
//Use for othe file<<

//!!There code table only extern use by file BeaconFactoryOsd.c
//"code BYTE * "means the table have parameter to adjust.
extern code BYTE *tOSD_BEACON_FAC_COLORTEMP[4];
extern code BYTE *tOSD_BEACON_FAC_YES_OR_NO[2];
extern code BYTE *tOSD_BEACON_FAC_DDCCI_CHANNEL[];
extern BYTE code tOSD_WINDOW_0_FACTORY_MEMU_2[];

#endif

#endif

#define IIC_COM_ADDRESS                         0x6e//0x46//
#define IIC_Read_ADDRESS                        0x6f//0x47//

#define SET_BACKLIGHT_ADD                       0xD0
#define SET_BACKLIGHT_REDUCE                    0xD1
#define SET_POWER_ON                            0xD2
#define SET_POWER_OFF                           0xD3
#define SET_DEFAULT                             0xD4
#define SET_CONTRAST_ADD                        0xD5
#define SET_CONTRAST_REDUCE                     0xD6
#define READ_HARDWAREINFO                       0xD7
#define READ_SOFTWAREINFO                       0xD8
#define SET_SCREENSAVERS_STATE                  0xD9
#define SET_GAMMA                               0xDA
#define SET_BACKLIGHT                           0xDB
#define SET_CONTRAST                            0xDC
#define SET_COLORTEMP                           0xDD
#define READ_POWER_STATE                        0xDE
#define READ_BACKLIGHT                          0xDF
#define READ_CONTRAST                           0xE0
#define READ_GAMMA                              0xE1
#define READ_COLORTEMP                          0xE2
#define READ_COMMAND_EXECUTION                  0xE3
#define READ_SCREENSAVERS_STATE                 0xE4
#define READ_CHECK_STATE                        0xE5

#define	SET_BRIGHTNESS_ADD                      0xF0
#define	SET_BRIGHTNESS_REDUCE                   0xF1
#define	SET_BRIGHTNESS                          0xF2

//Beacon gamma adjust tool
#define SET_BACKLIGHT_L                         0X55
#define SET_BACKLIGHT_M                         0X56
#define SET_BACKLIGHT_H                         0X57

#define CMD_GET_COMPLETE_STATUS                 0x58

#define SET_BACKLIGHT_FOR_GAMMA                 0X90
#define SET_CONTRAST_FOR_GAMMA                  0X95
#define SET_GAMMA_FOR_GAMMA                     0X91
#define SET_COLORTEMP_FOR_GAMMA                 0X92
#define COMMAND_SET_AUTO_ADJUST_FOR_GAMMA_ADJ   0X93
#define COMMAND_SET_AUTO_COLOR_FOR_GAMMA_ADJ    0X94
#define Set_GAMMA_RGB                           0x99
#define READ_CHECK_OK                           0x98
#define Set_GAMMA_PASS                          0xA3
#define GET_SN                                  0x9E
#define SET_SN                                  0x9F
#define GET_SN_CHECK                            0x60
#define GET_TEMP_SENSOR_PWM                     0x71

#define Set_GAMMA_RGB_OF_EEPROM                 0x9a

#define COMMAND_StarEnd_OSD_ADJUST_GAMMA        0XA1
#define COMMAND_SET_CALIBRATION                 0xA2

#define Set_TRANSMIT_GAMMA_DATA_OF_FLASH        0xA4
#define GET_TOTAL_CHECKSUM_STATUS               0xA5





