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
// ID Code      : NoneDdcci.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __NONE_DDCCI__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _BEACON_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
// RC
#define _DDCCI_CMD_GETVCP_RC_NO_ERROR               0x00
#define _DDCCI_CMD_GETVCP_RC_UNSUPPORTED            0x01

// TP
#define _DDCCI_CMD_GETVCP_TP_SET_PARAMETER          0x00
#define _DDCCI_CMD_GETVCP_TP_MOMENTARY              0x01

//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _COLORTEMP_USER_MAX                         255
#define _COLORTEMP_USER_MIN                         0
#define _COLORTEMP_USER_CENTER                      (((_COLORTEMP_USER_MAX - _COLORTEMP_USER_MIN) / 2) + _COLORTEMP_USER_MIN)

//--------------------------------------------------
// For DDCCI Set Input Port
//--------------------------------------------------
#if(_PCB_TYPE == _RL6432_BEACON_B_76PIN_1A1H_eDP)
#define _VGA_1                                      _A0_INPUT_PORT
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _NO_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                     _NO_INPUT_PORT
#else
#define _VGA_1                                      _A0_INPUT_PORT
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D0_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                     _D2_INPUT_PORT
#endif
//****************************************************************************
//    STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//BYTE code tCOLORPRESET_VALUE[] = {0x08, 0x06, 0x05, 0x04, 0x01, 0x0B, 0x02};

BYTE code tCOLORPRESET_VALUE[] = 
{
#if(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
    0x0D, 0x0C, 0x0B
#elif((_COLOR_TEMP_SELECT_TYPE == _9300K_6500K) || (_COLOR_TEMP_SELECT_TYPE == _9300K_13000K) \
    || (_COLOR_TEMP_SELECT_TYPE == _6500K_9300K) || (_COLOR_TEMP_SELECT_TYPE == _6700K_9300K) \
    || (_COLOR_TEMP_SELECT_TYPE == _13000K_9300K) || (_COLOR_TEMP_SELECT_TYPE == _11000K_9300K) \
    || (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K))
    0x0B, 0x0C, 0x0D
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)
    0x0C, 0x0B, 0x0A, 0x0D
#elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
    0x0d,0x08,0x05,0x0b
#else
    0x08, 0x06, 0x05, 0x04, 0x01, 0x0B, 0x02
#endif
};

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucDdcciNewControlValue = 1;
bit g_bForcePowSavStatus = _FALSE;

#if(_GET_HARD_ID == _ON)
WORD g_ucHardID = 0;
#endif

#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default))
// DDCCI CMD Check Flag ->_DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS
bit E_OrderStatus = 0;         
#endif

#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
BYTE g_ucUpdateGammaIndex = 1;
BYTE g_ucReceiveDataBlock = 0;
BYTE g_ucBankPageIndex = 0;
BYTE g_ucCommonCheckStatus = 0;
BYTE g_ucCacheData[4] = {0};
WORD g_wGammaStartAddr = _BEACON_GAMMA1_ADDRESS;
WORD g_wOneBlockDataCheckSum = 0;
#define I2C_GAMMA_DATA_LENGTH    108
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserDdcciHandler(void);
void NoneDdcciGetVCPFeature(void);
bit NoneDdcciSetVCPFeatureCheck(void);
void NoneDdcciSetVCPFeature(void);
void RTDDdcciResetAllSettings(void);
void RTDDdcciColorReset(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default))// for beacon gamma auto processing function 
//--------------------------------------------------
// function: beacon Gamma tool RGB data exchange to chip gamma lut data format
//--------------------------------------------------
static void swap(BYTE *a, BYTE *b/*, BYTE width*/)
{
    char tmp;

    if(a != b)
    {
        //while(width--)
        {
            tmp = *a;
            *a/*++*/ = *b;
            *b/*++*/ = tmp;
        }
    }
}

//--------------------------------------------------
// Description  : Set DDC-DI Command&data for beacon factory Gamma auto Processing function
// Input Value  : null
// Output Value : cmd Status..etc
//#define _DDCCI_SOURCE                               0
//#define _DDCCI_LENGTH                               1
//#define _DDCCI_COMMAND                              2       
//    0  1  2
// 6e 51 8* c0 
//--------------------------------------------------
void RTDDdcciFactoryGammaAutoProcess(void)
{
    BYTE CMDCode;
    BYTE *CmdPara;
    WORD usTemp = 0;

    CMDCode = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE]; // Index:3
    CmdPara = &g_pucDdcciRxBuf[_DDCCI_SINK_OPCODE];  // Index:4

    if((CMDCode == _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_MID)||
        (CMDCode == _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT)||
        (CMDCode == _DDCCI_GAMMA_ADJUST_SET_GAMMA_TYPE)||
        (CMDCode == _DDCCI_GAMMA_ADJUST_SET_CTEMP_TYPE)||
        (CMDCode == _DDCCI_GAMMA_ADJUST_SET_DICOM_BACKLIGHT)||
        (CMDCode == _DDCCI_GAMMA_ADJUST_SEND_GAMMA_RGB_VALUE))
    {
#if(_PCM_FUNCTION == _ON)
        // Skip Gamma if PCM != native
        if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
        {
            SET_OSD_PCM_STATUS(_PCM_OSD_NATIVE);
            OsdFuncColorPcmAdjust();
        }
#endif
    }
    
    switch( CMDCode )
    {
        case _DDCCI_GAMMA_ADJUST_SET_DDCCI2_KEY:
            //Beacon DDC-CI Test Tool
            //Menu:   51 83 C0 96 00 CheckSum:EA
            //Left:   51 83 C0 96 01 CheckSum:EB
            //Right:  51 83 C0 96 02 CheckSum:E8
            //Exit:   51 83 C0 96 03 CheckSum:E9
            //Factory:51 83 C0 96 04 CheckSum:EE
            if(CmdPara[0] < 4)
            {
                //(*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();
                //(*OperationTable[GET_OSD_STATE()][CmdPara[0]])();
                SET_KEYMESSAGE(CmdPara[0]);

                if(g_ucBeaconFacOsdShowFlag)
                    BeaconFactoryOsdMenuOperation();
                else
                {
                    (*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();
                    if((GET_OSD_STATE() == _BEACON_HOTKEY_OSD_1)||(GET_OSD_STATE() == _BEACON_HOTKEY_OSD_2))
                    {
                        ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                }

                SET_KEYMESSAGE(_NONE_KEY_MESSAGE);

            }
            // SET_KEYMESSAGE(CmdPara[0]);
            else if(CmdPara[0] == 4)
            {
                if(GET_OSD_STATE() == _BEACON_OSD_NONE)
    #if(_USER_BEACON_FACTORY_OSD == _ON)
                    BeaconFactoryOsdPage1();
    #else
                    ;
    #endif
                if((GET_OSD_STATE() != _BEACON_OSD_NONE)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_1)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_2))
                {
                    BeaconAdvancedOsdDisplayProc();
                }
            }
            break;
            
        case _DDCCI_GAMMA_ADJUST_SET_GAMMA_BYPASS:
            //parameter 0: 0x00:set no bypass   0x01:set all bypass
            //0x02:set only R linear 0x03:set only G linear 0x04:set only B linear
            {
                //ScalerColorOutputGammaEnable(CmdPara[0]);
            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_ADC_OFFSET:
#if(_VGA_SUPPORT == _ON)
            //param  range: 0-255
            //parameter 0-1-2 : offset R-G-B
            {
                g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL] = CmdPara[0];
                g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL] = CmdPara[1];
                g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL] = CmdPara[2];                

                if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
                }
                else
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
                }
            }
#endif
            break;

    	case _DDCCI_GAMMA_ADJUST_SET_ADC_GAIN:
#if(_VGA_SUPPORT == _ON)
            //param  range	: 0-255                
            //parameter 0-1-2 : Gain R-G-B
            {
                g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL] = CmdPara[0];
                g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL] = CmdPara[1];
                g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL] = CmdPara[2];                

                if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
                }
                else
                {
                    UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
                }
            }
#endif
            break;

        case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_LOW:
            //parameter 0 : backlight value (0~250 for 8Bit)
            {
                
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                SET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE(),CmdPara[0]);
    #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
    #else
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
    #endif                               
#else
                SET_FACTORY_BACKLIGHT_REG_MIN(CmdPara[0]);
    #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MIN()));
    #else
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE()));
#else
                UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MIN());
#endif
#endif

                SET_BRIGHTPION();
                CLR_COMMAND_STATE(); 
            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_MID:
            //parameter 0 : backlight value (0~253 for 8Bit)
            {
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                 SET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE(),CmdPara[0]);
    #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                 PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #else
                 PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
    #endif                               
#else
                 SET_FACTORY_BACKLIGHT_REG_MID(CmdPara[0]);
    #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                 PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MID()));
    #else
                 PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE()));
#else
                UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MID());
#endif
#endif
                
#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
                SET_IIC_SENSOR_BACKLIGHT_STOP_STATE();
                ScalerTimerReactiveTimerEvent(3000, _USER_TIMER_EVENT_BACKLIGHTSENSOR_STOP);
                SET_IIC_SENSOR_BACKLIGHT_MID_STATE();
#endif
                SET_BRIGHTPION();
                CLR_COMMAND_STATE();
            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT_HIGH:
            //parameter 0 : backlight value (0~255 for 8Bit)
            {
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                SET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE(),CmdPara[0]);
    #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
    #else
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
    #endif                               
#else
                SET_FACTORY_BACKLIGHT_REG_MAX(CmdPara[0]);
    #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MAX()));
    #else
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX()));
    #endif
#endif

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE()));
#else
                UserCommonInterfaceOledAdjustBackLight(GET_FACTORY_BACKLIGHT_REG_MAX());
#endif
#endif

                SET_BRIGHTPION();
                CLR_COMMAND_STATE();
            }
            break;

        case _DDCCI_GAMMA_ADJUST_SAVE_DICOM_BACKLIGHT:
            {

            }
            break;
            
        case _DDCCI_GAMMA_ADJUST_SET_DICOM_BACKLIGHT:
            {                

            }
            break;
            
        case _DDCCI_GAMMA_ADJUST_SET_GAMMA_TYPE:
            //parameter 0 : the gamma index
            {
                BYTE mBackup_OSD_Gammma;
                mBackup_OSD_Gammma = GET_OSD_GAMMA();
                
                switch(CmdPara[0] )
                {
                    case 0x00:
                        SET_OSD_GAMMA(_GAMMA_1);
                        break;
                    
                    case 0x01:
                        SET_OSD_GAMMA(_GAMMA_2);
                        break;
                    case 0x02:
                        SET_OSD_GAMMA(_GAMMA_3);
                        break;
                        
                    case 0x03:
                        SET_OSD_GAMMA(_GAMMA_4);
                        break;
                        
                    case 0x04:
                        SET_OSD_GAMMA(_GAMMA_5);
                        break;
                        
                    case 0x05:
                        SET_OSD_GAMMA(_GAMMA_6);
                        break;
                        
                    case 0x06:
                        SET_OSD_GAMMA(_GAMMA_7);
                        break;
                        
                    default:
                        SET_OSD_GAMMA(_DEFAULT_GAMMA);
                        break;
                }
    
                if(GET_OSD_GAMMA() <= _GAMMA_NUMBERS)
                {
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                    CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);               
                }
                else
                {
                    SET_OSD_GAMMA(mBackup_OSD_Gammma);
                }

            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_CTEMP_TYPE:
            //parameter 0 : index of color temperature
            {
                BYTE m_ColorTemp_Target = 0xFF;
                BYTE m_Native_ColorTemp_Target = 0;
                switch(CmdPara[0])
                {
#if(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_9300;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_11000;
                        break; 
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_14000;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_6500K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_9300;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_6500;
                        break; 
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_13000K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_9300;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_13000;
                        break; 
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _6500K_9300K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_6500;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _6700K_9300K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_6700;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _13000K_9300K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_13000;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _11000K_9300K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_11000;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break; 
#elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_Normal;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_Cool;
                        break;
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_Warm;
                        break; 
                    case 0x03:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_7500;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_13000;
                        break;
                    case 0x02:
                        m_ColorTemp_Target = _BEACON_ULTRASOUND;
                        break; 
                    case 0x03:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K)
                    case 0x00:
                        m_ColorTemp_Target = _BEACON_7500;
                        break;
                    case 0x01:
                        m_ColorTemp_Target = _BEACON_13000;
                        break;
                    case 0x03:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
#endif
                }
    
                if(m_ColorTemp_Target != 0xFF)
                {
                    SET_COLOR_TEMP_TYPE(m_ColorTemp_Target);
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                    UserAdjustContrast(GET_OSD_CONTRAST());
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                    CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);                
                }
            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_AUTO_ADJUST:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
                }
            }
#endif
            break;

        case _DDCCI_GAMMA_ADJUST_SET_AUTO_COLOR:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                if(SysModeGetModeState() == _MODE_STATUS_ACTIVE)
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_COLOR_MSG);
                    //BeaconFactoryAutoColor();
                }
            }
#endif
            break;

        case _DDCCI_GAMMA_ADJUST_SET_BACKLIGHT:
            if(CmdPara[0] > 100)
            {
                CmdPara[0] = 100;
            }
            SET_OSD_BACKLIGHT(CmdPara[0] );
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
    #if(_BACKLIGHT_SENSOR == _ON)
            UserAdjustSetSensorbacklightvalue(1);
    #endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
            break;            

        case _DDCCI_GAMMA_ADJUST_SET_CONTRAST:
            //parameter 0 : the of the contrast(0~100)
            if(CmdPara[0]  > 100)
            {
               CmdPara[0] = 100;
            }
            SET_OSD_CONTRAST(CmdPara[0] );
#if(_CONTRAST_SUPPORT == _ON)            
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);            
            break;
        
        case _DDCCI_GAMMA_ADJUST_SEND_GAMMA_RGB_VALUE: // 14-bit 0~0x3FFF range: 0 ~ (2^14-1) 
            //order    : set zero gamma tabble
            //Gamma tool data format:
            //parameter 0 : low byte of R   parameter 1 : high byte of R   
            //parameter 2 : low byte of G   parameter 3 : high byte of G   
            //parameter 4 : low byte of B   parameter 5 : high byte of B 
            
            //gamma Lut data format:    
            //index 0 : high byte of R/G/B   index 1 : low byte of R/G/B   
            {
                WORD GammaData_R,GammaData_G,GammaData_B;

                GammaData_R = ((WORD)(CmdPara[0]) + (WORD)(CmdPara[1]<<8));
                GammaData_G = ((WORD)(CmdPara[2]) + (WORD)(CmdPara[3]<<8));
                GammaData_B = ((WORD)(CmdPara[4]) + (WORD)(CmdPara[5]<<8));
            
                // Range check
                if((GammaData_R <= 0x3FFF)&&(GammaData_G <= 0x3FFF)&&(GammaData_B <= 0x3FFF))
                {
                    //gamma tool data format->gamma lut data format
                    swap(&CmdPara[0],&CmdPara[1]/*,1*/); //R Word H|L swap
                    swap(&CmdPara[2],&CmdPara[3]/*,1*/); //G Word H|L swap
                    swap(&CmdPara[4],&CmdPara[5]/*,1*/); //B Word H|L swap

                    UserCommonAdjustGammaRGBValue(CmdPara);
                }
            }
            break;
                 
        case _DDCCI_GAMMA_ADJUST_SET_FAC_MONITOR_SN:
            {
                // range check...max length is 25
                if(CmdPara[0] > _MONITOR_SN_LENGTH)
                {
                    CmdPara[0] = _MONITOR_SN_LENGTH;
                }

                // Save SN data
                {    
                    memcpy(ucMonitorSn,&CmdPara[1],_MONITOR_SN_LENGTH);
                    BeaconFactorySaveMonitorSN(ucMonitorSn);
#if((_KL_SPECIAL_FUNTION == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
                    ScalerTimerReactiveTimerEvent(SEC(2), _USER_TIMER_EVENT_KL_SPECIAL_FUNTION_SETTING);
#endif
                }
            }
            break;

        case _DDCCI_GAMMA_ADJUST_GET_FAC_MONITOR_SN:
            {

                g_pucDdcciTxBuf[0] = 0x6e;// Source
                g_pucDdcciTxBuf[1] = (0x80|(5+_MONITOR_SN_LENGTH));  // Length 0x80|(0xC0,CMD,data(25))
                g_pucDdcciTxBuf[2] = 0xc0;
                g_pucDdcciTxBuf[3] = 0x00;
                g_pucDdcciTxBuf[4] = 0x00;
                g_pucDdcciTxBuf[5] = (0x80|(3+_MONITOR_SN_LENGTH));
                g_pucDdcciTxBuf[6] = _DDCCI_GAMMA_ADJUST_GET_FAC_MONITOR_SN;
                
                BeaconFactoryLoadMonitorSN(&g_pucDdcciTxBuf[7]);
                
                g_pucDdcciTxBuf[7 + _MONITOR_SN_LENGTH] = UserCommonDdcciCalCheckSum(); // checksum

                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_MONITOR_EDID_IDSN:
            //order  : [Length + data] update RAM EDID ID Serial Number
            {

            }
            break;

        case _DDCCI_GAMMA_ADJUST_GET_MONITOR_EDID_IDSN:
            //order  :  Get RAM EDID ID Serial Number
            {

            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_EDID_PROTECT_EXT_EEPROM:
            //order  : Change write protection status to download EDID data external EEPROM:24C02
            //Function:UserInterfaceGetEmbeddedEDIDData()
            {

            }
            break;

        case _DDCCI_GAMMA_ADJUST_SET_EDID_BANKSEL_EXT_EEPROM:
            //order  : 0~4 for Select external EEPROM Bank
            {

            }
            break;
            
        case _DDCCI_GAMMA_ADJUST_SET_LOCAL_ENHANCEMENT_ON_OFF:
            break;

        case _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_TYPE1:

            break;

        case _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_TYPE2:

            break;

        case _DDCCI_GAMMA_ADJUST_SET_ENHANCEMENT_HVPOS_ZOOM:
            
            break;
                        
        case _DDCCI_GAMMA_ADJUST_SET_AMBI_DICOM_BACKLIGHT:
            break;

        case _DDCCI_GAMMA_ADJUST_GET_AMBI_DICOM_BACKLIGHT:
            break;

        case _DDCCI_GAMMA_ADJUST_ENTER_BRUNIN:
            {

            }
            break;

        case _DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS:
            //读取前一个命令状态（此命令只用于，PC到MCU写数据时读取)，
            //以确保前一个命令有正常收到，当前一个命令异或校验
            //正确返回0x01,不正确返回0x00
            {
                //(_BEACON_CALIBRATION_COMMAND_STATUS_EXINT_SUPPORT == _OFF)
                g_pucDdcciTxBuf[0] = 0x6e;  // Source
                g_pucDdcciTxBuf[1] = 0x86;  // Length //Byte size from next byte to before byte of checksum

                g_pucDdcciTxBuf[2] = 0xc0;  // VCP Prefix 0xC0 0x00 0x00
                g_pucDdcciTxBuf[3] = 0x00;
                g_pucDdcciTxBuf[4] = 0x00;  
                g_pucDdcciTxBuf[5] = 0x84; // length
                g_pucDdcciTxBuf[6] = _DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS; // cmd
                g_pucDdcciTxBuf[7] = E_OrderStatus; // parameter

                g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

                // Clear flag: PC only reads once
                E_OrderStatus=0;
            }
            break;

        case _DDCCI_GAMMA_ADJUST_GET_DICOM_SUPPORT:
            {               

            }
            break; 

        case _DDCCI_GAMMA_ADJUST_GET_BACKLIGHT_SENSOR_PWM:
            // parameter 0 : temperature
            // parameter 1 : Backlight Sensor Current H data
            // parameter 2 : Backlight Sensor Current L data
            // parameter 3 : Backlight Sensor Target H data
            // parameter 4 : Backlight Sensor Target L data
            // parameter 5 : PWM H data
            // parameter 6 : PWM L data
            {
                WORD usTemp = 0;
#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))            
                WORD curSensorValue = 0;
#endif
                           
                g_pucDdcciTxBuf[0] = 0x6e;           // Source
                g_pucDdcciTxBuf[1] = (0x80|(0x0C));  // Length //Byte size from next byte to before byte of checksum
                g_pucDdcciTxBuf[2] = 0xc0;            // VCP Prefix 0xC0 0x00 0x00
                g_pucDdcciTxBuf[3] = 0x00;
                g_pucDdcciTxBuf[4] = 0x00;

                g_pucDdcciTxBuf[5] = (0x80|(0x0A)); // Length // checksum to the current byte size
                g_pucDdcciTxBuf[6] = _DDCCI_GAMMA_ADJUST_GET_BACKLIGHT_SENSOR_PWM; //CMD	

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
            #if(_BACKLIGHT_SENSOR == _ON)
                curSensorValue = read2561();
            #elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
                if(readSensorValue() == _FAIL)
                   curSensorValue = 0xFFFF;
                else
                   curSensorValue = GET_CURRENT_SENSOR();
            #endif
                g_pucDdcciTxBuf[7] = 0;
                g_pucDdcciTxBuf[8] = (BYTE)((curSensorValue >> 8) & 0x00FF);
                g_pucDdcciTxBuf[9] = (BYTE)(curSensorValue & 0x00FF);

                g_pucDdcciTxBuf[10] = (BYTE)((GET_TARGET_SENSOR() >> 8) & 0x00FF);
                g_pucDdcciTxBuf[11] = (BYTE)(GET_TARGET_SENSOR() & 0x00FF);
                
#else
                g_pucDdcciTxBuf[7] = 0;
                g_pucDdcciTxBuf[8] = 0;
                g_pucDdcciTxBuf[9] = 0;

                g_pucDdcciTxBuf[10] = 0;
                g_pucDdcciTxBuf[11] = 0;
#endif

                usTemp = MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM);
 #if(_BACKLIGHT_PWM_INVERSE == _ON)
                usTemp = 4095 - usTemp;
 #endif
                g_pucDdcciTxBuf[12] = (BYTE)((usTemp >> 8) & 0x00FF);
                g_pucDdcciTxBuf[13] = (BYTE)(usTemp & 0x00FF);

                g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);              
            }
            break;

#if(_HDMI_SPLITTER_1X2_EN == _ON)
            case _DDCCI_OPCODE_HDMISPLITTER_GET_DATA:
            {
                g_pucDdcciTxBuf[0] = 0x6e;  // Source
                g_pucDdcciTxBuf[1] = (0x80|(0x07));  // Length //Byte size from next byte to before byte of checksum

                g_pucDdcciTxBuf[2] = 0xC0;  // VCP Prefix 0xC0 0x00 0x00
                g_pucDdcciTxBuf[3] = 0x00;
                g_pucDdcciTxBuf[4] = 0x00;  
                g_pucDdcciTxBuf[5] = 0x84; // length
                g_pucDdcciTxBuf[6] = _DDCCI_OPCODE_HDMISPLITTER_GET_DATA; // cmd
                g_pucDdcciTxBuf[7] = GET_1ST_DATA(); // parameter
                g_pucDdcciTxBuf[8] = GET_2ND_DATA(); // parameter

                g_pucDdcciTxBuf[9] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);

                break;
            }
            
            case _DDCCI_OPCODE_HDMISPLITTER_SET_PORTACONTROL:
            {
                switch(CmdPara[0])
                {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x04:
                    case 0x05:
                    case 0x06:
                    case 0x07:
                    case 0x08:
                    case 0x09:
                    case 0x0A:
                    case 0x0B:
                        SET_DATA1ST_PORTACONTROL(CmdPara[0]);
                        UserAdjust_HdmiSplitter_SetData(GET_1ST_DATA(),GET_2ND_DATA());
                        ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);
                        break;
                    default:
                        break;
                }
                
                break;
            }
    
            case _DDCCI_OPCODE_HDMISPLITTER_SET_EQUALIZATION:
            {
                if(CmdPara[0] <= 3)
                {
                    SET_DATA1ST_EQUALIZATION(CmdPara[0]);
                    UserAdjust_HdmiSplitter_SetData(GET_1ST_DATA(),GET_2ND_DATA());
                    ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);
                }

                break;
            }
    
            case _DDCCI_OPCODE_HDMISPLITTER_SET_PORTBCONTROL:
            {
                switch(CmdPara[0])
                {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x04:
                    case 0x05:
                    case 0x06:
                    case 0x07:
                    case 0x08:
                    case 0x09:
                    case 0x0A:
                    case 0x0B:
                        SET_DATA2ND_PORTBCONTROL(CmdPara[0]);
                        UserAdjust_HdmiSplitter_SetData(GET_1ST_DATA(),GET_2ND_DATA());
                        ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);
                        break;
                    default:
                        break;
                }

                break;
            }           
#endif

        default:
            break;
    }

    if(CMDCode == _DDCCI_GAMMA_ADJUST_GET_COMMAND_STATUS)
    {
        //读取前一个命令状态（此命令只用于，PC到MCU写数据时读取)，
        //以确保前一个命令有正常收到，当前一个命令异或校验
        //正确返回0x01,不正确返回0x00
    }
    else if(CMDCode == _DDCCI_GAMMA_ADJUST_SAVE_DICOM_BACKLIGHT)
    {
        //Beacon_Gamma_Color(I2C)3.0_T9：此命令重新读取前一个命令状态的间隔时间延长或执行下一条命令时间延长
        //  读取前一个命令状态，读到0x00，延迟1秒，重试四次每次都最少延时1秒。命令执行完之后延迟2秒，执行下一条命令
        //或读取前一个命令状态，读到0x01，延迟3秒。执行下一条命令
        //若此是0x00，确保有执行背光Sensor更新目标值且完成后必须把状态置0x01
        E_OrderStatus=1;
    }
    else
    {
        E_OrderStatus=1;
    }
    
}

#else
void DDCCI_FactoryGammaAdjust(void)
{
    BYTE  Command;
    BYTE *CmdPara;
    Command = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE];
    CmdPara = &g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE+1];

    switch( Command )
    {

        case _DDCCI_OPCODE_FACTORY_SET_KEY:
            if(CmdPara[0] < 4)
            {
                //(*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();
                //(*OperationTable[GET_OSD_STATE()][CmdPara[0]])();
                SET_KEYMESSAGE(CmdPara[0]);

                if(g_ucBeaconFacOsdShowFlag)
                    BeaconFactoryOsdMenuOperation();
                else
                {
                    (*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();
                    if((GET_OSD_STATE() == _BEACON_HOTKEY_OSD_1)||(GET_OSD_STATE() == _BEACON_HOTKEY_OSD_2))
                    {
                        ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                    else
                    {
                        ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                    }
                }

                SET_KEYMESSAGE(_NONE_KEY_MESSAGE);

            }
            // SET_KEYMESSAGE(CmdPara[0]);
            else if(CmdPara[0] == 4)
            {
                if(GET_OSD_STATE() == _BEACON_OSD_NONE)
    #if(_USER_BEACON_FACTORY_OSD == _ON)
                    BeaconFactoryOsdPage1();
    #else
                    ;
    #endif
                if((GET_OSD_STATE() != _BEACON_OSD_NONE)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_1)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_2))
                {
                    BeaconAdvancedOsdDisplayProc();
                }
            }
            break;

        case _DDCCI_OPCODE_FACTORY_SET_BACKLIGHT:
            if(CmdPara[0] > 100)
            {
                CmdPara[0] = 100;
            }
            SET_OSD_BACKLIGHT(CmdPara[0] );
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
    #if(_BACKLIGHT_SENSOR == _ON)
            UserAdjustSetSensorbacklightvalue(1);
    #endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
            break;
            
        case _DDCCI_OPCODE_FACTORY_SET_GAMMA_TYPE:
        {
            BYTE mBackup_OSD_Gammma;
            mBackup_OSD_Gammma = GET_OSD_GAMMA();
            
            switch(CmdPara[0] )
            {
                case 0x00:
                    SET_OSD_GAMMA(_GAMMA_1);
                    break;
                
                case 0x01:
                    SET_OSD_GAMMA(_GAMMA_2);
                    break;
                case 0x02:
                    SET_OSD_GAMMA(_GAMMA_3);
                    break;
                    
                case 0x03:
                    SET_OSD_GAMMA(_GAMMA_4);
                    break;
                    
                case 0x04:
                    SET_OSD_GAMMA(_GAMMA_5);
                    break;
                    
                case 0x05:
                    SET_OSD_GAMMA(_GAMMA_6);
                    break;
                    
                case 0x06:
                    SET_OSD_GAMMA(_GAMMA_7);
                    break;
                    
                default:
                    SET_OSD_GAMMA(_DEFAULT_GAMMA);
                    break;
            }

            if(GET_OSD_GAMMA() <= _GAMMA_NUMBERS)
            {
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);               
            }
            else
            {
                SET_OSD_GAMMA(mBackup_OSD_Gammma);
            }
            break;
        }
        
        case _DDCCI_OPCODE_FACTORY_SET_CTEMP_TYPE:
        {
            BYTE m_ColorTemp_Target = 0xFF;
            BYTE m_Native_ColorTemp_Target = 0;
            switch(CmdPara[0])
            {
#if(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_9300;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_11000;
                    break; 
                case 0x02:
                    m_ColorTemp_Target = _BEACON_14000;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_6500K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_9300;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_6500;
                    break; 
                case 0x02:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_13000K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_9300;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_13000;
                    break; 
                case 0x02:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _6500K_9300K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_6500;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_9300;
                    break; 
                case 0x02:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _6700K_9300K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_6700;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_9300;
                    break; 
                case 0x02:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _13000K_9300K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_13000;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_9300;
                    break; 
                case 0x02:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _11000K_9300K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_11000;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_9300;
                    break; 
                case 0x02:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break; 
#elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_Normal;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_Cool;
                    break;
                case 0x02:
                    m_ColorTemp_Target = _BEACON_Warm;
                    break; 
                case 0x03:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_7500;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_13000;
                    break;
                case 0x02:
                    m_ColorTemp_Target = _BEACON_ULTRASOUND;
                    break; 
                case 0x03:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K)
                case 0x00:
                    m_ColorTemp_Target = _BEACON_7500;
                    break;
                case 0x01:
                    m_ColorTemp_Target = _BEACON_13000;
                    break;
                case 0x03:
                    m_ColorTemp_Target = _BEACON_USER;
                    break;
                default:
                    m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                    break;
#endif
            }

            if(m_ColorTemp_Target != 0xFF)
            {
                SET_COLOR_TEMP_TYPE(m_ColorTemp_Target);
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                UserAdjustContrast(GET_OSD_CONTRAST());
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);                
            }

            break;
        }
        
        case _DDCCI_OPCODE_FACTORY_SET_CONTRAST:
            if(CmdPara[0]  > 100)
            {
               CmdPara[0] = 100;
            }
            SET_OSD_CONTRAST(CmdPara[0] );
            UserAdjustContrast(GET_OSD_CONTRAST());
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
            break;    

#if(_HDMI_SPLITTER_1X2_EN == _ON)
        case _DDCCI_OPCODE_HDMISPLITTER_GET_DATA:
        {
            g_pucDdcciTxBuf[0] = 0x6e;  // Source
            g_pucDdcciTxBuf[1] = (0x80|(0x07));  // Length //Byte size from next byte to before byte of checksum
        
            g_pucDdcciTxBuf[2] = 0xC0;  // VCP Prefix 0xC0 0x00 0x00
            g_pucDdcciTxBuf[3] = 0x00;
            g_pucDdcciTxBuf[4] = 0x00;  
            g_pucDdcciTxBuf[5] = 0x84; // length
            g_pucDdcciTxBuf[6] = _DDCCI_OPCODE_HDMISPLITTER_GET_DATA; // cmd
            g_pucDdcciTxBuf[7] = GET_1ST_DATA(); // parameter
            g_pucDdcciTxBuf[8] = GET_2ND_DATA(); // parameter
        
            g_pucDdcciTxBuf[9] = UserCommonDdcciCalCheckSum(); // checksum
            ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
        
            break;
        }

        case _DDCCI_OPCODE_HDMISPLITTER_SET_PORTACONTROL:
        {
            switch(CmdPara[0])
            {
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x04:
                case 0x05:
                case 0x06:
                case 0x07:
                case 0x08:
                case 0x09:
                case 0x0A:
                case 0x0B:
                    SET_DATA1ST_PORTACONTROL(CmdPara[0]);
                    UserAdjust_HdmiSplitter_SetData(GET_1ST_DATA(),GET_2ND_DATA());
                    ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);
                    break;
                default:
                    break;
            }

            break;
        }

        case _DDCCI_OPCODE_HDMISPLITTER_SET_EQUALIZATION:
        {
            if(CmdPara[0] <= 3)
            {
                SET_DATA1ST_EQUALIZATION(CmdPara[0]);
                UserAdjust_HdmiSplitter_SetData(GET_1ST_DATA(),GET_2ND_DATA());
                ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);
            }

            break;
        }

        case _DDCCI_OPCODE_HDMISPLITTER_SET_PORTBCONTROL:
        {
            switch(CmdPara[0])
            {
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x04:
                case 0x05:
                case 0x06:
                case 0x07:
                case 0x08:
                case 0x09:
                case 0x0A:
                case 0x0B:
                    SET_DATA2ND_PORTBCONTROL(CmdPara[0]);
                    UserAdjust_HdmiSplitter_SetData(GET_1ST_DATA(),GET_2ND_DATA());
                    ScalerTimerReactiveTimerEvent(SEC(1.5), _USER_TIMER_EVENT_SAVE_OTHER_USER_DATA);
                    break;
                default:
                    break;
            }

            break;
        }           
#endif

        case _DDCCI_OPCODE_FACTORY_GET_BACKLIGHT_SENSOR_PWM:
            // parameter 0 : temperature
            // parameter 1 : Backlight Sensor Current H data
            // parameter 2 : Backlight Sensor Current L data
            // parameter 3 : Backlight Sensor Target H data
            // parameter 4 : Backlight Sensor Target L data
            // parameter 5 : PWM H data
            // parameter 6 : PWM L data
            {
                WORD usTemp = 0;
#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))            
                WORD curSensorValue = 0;
#endif
                           
                g_pucDdcciTxBuf[0] = 0x6e;           // Source
                g_pucDdcciTxBuf[1] = (0x80|(0x0C));  // Length //Byte size from next byte to before byte of checksum
                g_pucDdcciTxBuf[2] = 0xc0;            // VCP Prefix 0xC0 0x00 0x00
                g_pucDdcciTxBuf[3] = 0x00;
                g_pucDdcciTxBuf[4] = 0x00;

                g_pucDdcciTxBuf[5] = (0x80|(0x0A)); // Length // checksum to the current byte size
                g_pucDdcciTxBuf[6] = _DDCCI_OPCODE_FACTORY_GET_BACKLIGHT_SENSOR_PWM; //CMD    

#if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
    #if(_BACKLIGHT_SENSOR == _ON)
                curSensorValue = read2561();
    #elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
                if(readSensorValue() == _FAIL)
                   curSensorValue = 0xFFFF;
                else
                   curSensorValue = GET_CURRENT_SENSOR();
    #endif
                g_pucDdcciTxBuf[7] = 0;
                g_pucDdcciTxBuf[8] = (BYTE)((curSensorValue >> 8) & 0x00FF);
                g_pucDdcciTxBuf[9] = (BYTE)(curSensorValue & 0x00FF);

                g_pucDdcciTxBuf[10] = (BYTE)((GET_TARGET_SENSOR() >> 8) & 0x00FF);
                g_pucDdcciTxBuf[11] = (BYTE)(GET_TARGET_SENSOR() & 0x00FF);
                
#else
                g_pucDdcciTxBuf[7] = 0;
                g_pucDdcciTxBuf[8] = 0;
                g_pucDdcciTxBuf[9] = 0;

                g_pucDdcciTxBuf[10] = 0;
                g_pucDdcciTxBuf[11] = 0;
#endif

                usTemp = MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM);
#if(_BACKLIGHT_PWM_INVERSE == _ON)
                usTemp = 4095 - usTemp;
#endif
                g_pucDdcciTxBuf[12] = (BYTE)((usTemp >> 8) & 0x00FF);
                g_pucDdcciTxBuf[13] = (BYTE)(usTemp & 0x00FF);

                g_pucDdcciTxBuf[14] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);              
            }
            break;
            
        case _DDCCI_OPCODE_FACTORY_GET_COMMAND_STATUS:
            {
                //(_BEACON_CALIBRATION_COMMAND_STATUS_EXINT_SUPPORT == _OFF)
                g_pucDdcciTxBuf[0] = 0x6e;  // Source
                g_pucDdcciTxBuf[1] = 0x86;  // Length //Byte size from next byte to before byte of checksum
        
                g_pucDdcciTxBuf[2] = 0xc0;  // VCP Prefix 0xC0 0x00 0x00
                g_pucDdcciTxBuf[3] = 0x00;
                g_pucDdcciTxBuf[4] = 0x00;  
                g_pucDdcciTxBuf[5] = 0x84; // length
                g_pucDdcciTxBuf[6] = _DDCCI_OPCODE_FACTORY_GET_COMMAND_STATUS; // cmd
                g_pucDdcciTxBuf[7] = 0x01; // parameter
        
                g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum(); // checksum
                ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
        
            }
            break;

        default:
            break;
    }
}
#endif

#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))

//--------------------------------------------------
// Description  : Set DDC-DI Command&data for customer update gamma data
// Input Value  : null
// Output Value : cmd Status..etc
//#define _DDCCI_SOURCE                               0
//#define _DDCCI_LENGTH                               1
//#define _DDCCI_COMMAND                              2       
//    0  1  2
// 6e 51 8* c8 
//--------------------------------------------------
void DdcciUpdateGammaDataProcess(void)
{
    BYTE g_ucTmpdata = 0;
    BYTE g_ucIndex = 0;
    WORD g_wCacheData = 0;

    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE]) 
    { 
        case _DDCCI_UPATE_GAMMA_CHECK_COMMAN_STATUS:
            g_pucDdcciTxBuf[0] = 0x6e;  // Source
            g_pucDdcciTxBuf[1] = 0x86;  // Length //Byte size from next byte to before byte of checksum           
            g_pucDdcciTxBuf[2] = 0xc8;  // VCP Prefix 0xC0 0x00 0x00
            g_pucDdcciTxBuf[3] = 0x00;
            g_pucDdcciTxBuf[4] = _DDCCI_UPATE_GAMMA_CHECK_COMMAN_STATUS;  
            g_pucDdcciTxBuf[5] = 0x00;
            g_pucDdcciTxBuf[6] = 0x00;
            g_pucDdcciTxBuf[7] = g_ucCommonCheckStatus;            
            g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum(); // checksum

            ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
            g_ucCommonCheckStatus = 0;
            break;

        case _DDCCI_UPATE_GAMMA_GET_GAMMA_INDEX:
            g_pucDdcciTxBuf[0] = 0x6e;  // Source
            g_pucDdcciTxBuf[1] = 0x86;  // Length //Byte size from next byte to before byte of checksum            
            g_pucDdcciTxBuf[2] = 0xc8;  // VCP Prefix 0xC0 0x00 0x00
            g_pucDdcciTxBuf[3] = 0x00;
            g_pucDdcciTxBuf[4] = _DDCCI_UPATE_GAMMA_GET_GAMMA_INDEX;  
            g_pucDdcciTxBuf[5] = 0x00;
            g_pucDdcciTxBuf[6] = 0x00;
            g_pucDdcciTxBuf[7] = g_ucUpdateGammaIndex;
            g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum(); // checksum

            ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
            break;
            
        case _DDCCI_UPATE_GAMMA_GET_GAMMA_NUMS:
#if((_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K) || (_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal))
            g_ucTmpdata = 3 * _GAMMA_NUMBERS;
#else
            g_ucTmpdata = 2 * _GAMMA_NUMBERS;
#endif
            g_pucDdcciTxBuf[0] = 0x6e;  // Source
            g_pucDdcciTxBuf[1] = 0x86;  // Length //Byte size from next byte to before byte of checksum            
            g_pucDdcciTxBuf[2] = 0xc8;  // VCP Prefix 0xC0 0x00 0x00
            g_pucDdcciTxBuf[3] = 0x00;
            g_pucDdcciTxBuf[4] = _DDCCI_UPATE_GAMMA_GET_GAMMA_NUMS;  
            g_pucDdcciTxBuf[5] = 0x00;
            g_pucDdcciTxBuf[6] = 0x00;
            g_pucDdcciTxBuf[7] = g_ucTmpdata;
            g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum(); // checksum

            ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
            break;

        case _DDCCI_UPATE_GAMMA_SET_GAMMA_INDEX:
            g_ucCommonCheckStatus = 0;
#if((_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K) || (_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal))
            g_ucTmpdata = 3 * _GAMMA_NUMBERS;
#else
            g_ucTmpdata = 2 * _GAMMA_NUMBERS;
#endif
            if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= g_ucTmpdata)
            {
                g_ucUpdateGammaIndex = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                
                // Gamma_7x2CT_2Bank : One bank save max Gamma = 7
                if((g_ucUpdateGammaIndex == 1) || (g_ucUpdateGammaIndex == _BEACON_GAMMA_ONE_BANK_NUM + 1))
                {
                    g_wGammaStartAddr = _BEACON_GAMMA1_ADDRESS;
                    g_ucBankPageIndex = 0;
                }
                else
                {
                    //GammaIndex 2-7 : g_ucTmpdata = 0; 9-14 g_ucTmpdata = 7;
                    g_ucTmpdata = ((g_ucUpdateGammaIndex - 1) / _BEACON_GAMMA_ONE_BANK_NUM) * _BEACON_GAMMA_ONE_BANK_NUM;
                    // gamma index in bank (GammaIndex 2-7 : g_ucTmpdata is 2-7; 9-14 : g_ucTmpdata is 2-7)
                    g_ucTmpdata = g_ucUpdateGammaIndex - g_ucTmpdata;
                    g_wGammaStartAddr = _BEACON_GAMMA2_ADDRESS + (g_ucTmpdata - 2) * 0x2000;
                    g_ucBankPageIndex = (g_ucTmpdata - 1) * 2;
                }

                g_ucReceiveDataBlock = 0;
                g_wOneBlockDataCheckSum = 0;
                g_ucCommonCheckStatus = 1;
            }
            else
            {
                g_ucCommonCheckStatus = 2;
            }
            break;

        case _DDCCI_UPATE_GAMMA_SET_GAMMA_DATA:
            //cmd : 6E  51  F1  C8  92  Index  Data_Check_H  Data_Check_L  Data0  Data1.......Data106  Data107  CHECKSUM
            // index = 0, 1, 2, 3......(first block is 0)
            // data checksum (Data_Check_H  Data_Check_L) = Data0 + Data1 + ...... + Data106 + Data107;
            g_ucCommonCheckStatus = 0;

            // cal max blocks, index must less then max blocks
            g_wCacheData = _BEACON_GAMMA_TABLE_SIZE / I2C_GAMMA_DATA_LENGTH;
            if((_BEACON_GAMMA_TABLE_SIZE % I2C_GAMMA_DATA_LENGTH) != 0)
            {
                g_wCacheData += 1;
            }

            if(((g_pucDdcciRxBuf[4] >= g_ucReceiveDataBlock) && (g_pucDdcciRxBuf[4] < g_wCacheData)) || (g_pucDdcciRxBuf[4] == 0x00))
            {
                g_ucReceiveDataBlock = g_pucDdcciRxBuf[4]; // get index gamma data block
                g_wOneBlockDataCheckSum = (WORD)(g_pucDdcciRxBuf[5] << 8) + g_pucDdcciRxBuf[6];  // get data checksum from host 
                
                memset(MCU_DDCRAM_D5, 0x00, 256);
                memcpy(MCU_DDCRAM_D5,&g_pucDdcciRxBuf[7],I2C_GAMMA_DATA_LENGTH);  

                // calculate data checksum
                g_wCacheData = 0; 
                for(g_ucIndex = 0;g_ucIndex < I2C_GAMMA_DATA_LENGTH; g_ucIndex++)
                {
                    g_wCacheData += MCU_DDCRAM_D5[g_ucIndex];
                }
               
                if(g_wCacheData == g_wOneBlockDataCheckSum)
                {
                    BYTE i;
                    bit g_bFlag = _TRUE;
                
                    if(g_ucReceiveDataBlock == 0)
                    {
                        memset(g_ucCacheData, 0x00, 4);
                        UserCommonFlashRead(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_wGammaStartAddr, 4,  g_ucCacheData);
                        if((g_ucCacheData[0] != 0xFF) || (g_ucCacheData[1] != 0xFF) || (g_ucCacheData[2] != 0xFF) || (g_ucCacheData[3] != 0xFF))
                        {
                            UserCommonFlashErasePage(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_ucBankPageIndex);
                            UserCommonFlashErasePage(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_ucBankPageIndex + 1);
                        }

                        UserCommonFlashRead(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, (g_ucBankPageIndex * 0x1000 + 0x1FFF), 1,  &g_ucTmpdata);
                        if(g_ucTmpdata == 0xFF)
                        {
                            UserCommonFlashWrite(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, (g_ucBankPageIndex * 0x1000 + 0x1FFF) , 1 , &g_ucUpdateGammaIndex);
                        }
                    }

                    // calulate receive block gamma data address
                    g_wCacheData = g_wGammaStartAddr + g_ucReceiveDataBlock * I2C_GAMMA_DATA_LENGTH; 
                        
                    memset(g_ucCacheData, 0x00, 4);
                    UserCommonFlashRead(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_wCacheData, 4,  g_ucCacheData);
                    if((g_ucCacheData[0] == 0xFF) && (g_ucCacheData[1] == 0xFF) && (g_ucCacheData[2] == 0xFF) && (g_ucCacheData[3] == 0xFF))
                    {
                        UserCommonFlashWrite(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_wCacheData , I2C_GAMMA_DATA_LENGTH , MCU_DDCRAM_D5);

                        //check write data
                        memset(MCU_DDCRAM_MHL_D5, 0x00, 256);
                        UserCommonFlashRead(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_wCacheData, I2C_GAMMA_DATA_LENGTH,  MCU_DDCRAM_MHL_D5);
                        for(i = 0; i < I2C_GAMMA_DATA_LENGTH; i++)
                        {
                            if(MCU_DDCRAM_MHL_D5[i] != MCU_DDCRAM_D5[i])
                            {
                                g_bFlag = _FALSE;
                                break;
                            }
                        }

                        if(g_bFlag == _FALSE)
                        {
                            //write data fail!!
                            g_ucCommonCheckStatus = 4;
                        }
                        else
                        {
                            g_ucCommonCheckStatus = 1;
                        }
                        
                        
                    }
                    else
                    {
                        memset(MCU_DDCRAM_MHL_D5, 0x00, 256);
                        UserCommonFlashRead(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_wCacheData, I2C_GAMMA_DATA_LENGTH,  MCU_DDCRAM_MHL_D5);
                        for(i = 0; i < I2C_GAMMA_DATA_LENGTH; i++)
                        {
                            if(MCU_DDCRAM_MHL_D5[i] != MCU_DDCRAM_D5[i])
                            {
                                g_bFlag = _FALSE;
                                break;
                            }
                        }
                        
                        if(g_bFlag == _FALSE)
                        {
                            // bank has data, but data is not the same as target data!
                            g_ucCommonCheckStatus = 3;
                        }
                        else
                        {
                            g_ucCommonCheckStatus = 1;
                        }
                        
                    }

                }
                else
                {
                    // checksum error!!!
                    g_ucCommonCheckStatus = 2;
                }
            }
            else
            {
                //warn: target block less than current block, need to check!!!!
                g_ucCommonCheckStatus = ((g_ucReceiveDataBlock & 0x7F) | _BIT7);
            }                
            break;

        case _DDCCI_UPATE_GAMMA_SEND_DATA_FINISH:
            g_ucCommonCheckStatus = 0;
            if((g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] == 0x00) && (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01))
            {
                BYTE g_ucCount = 0;
                BYTE g_ucTargetBank = 0;
                WORD g_wLength = 0, i = 0; 
                bit g_bUpdateFlag = _TRUE; 

                // cal max blocks, index must less then max blocks
                g_wCacheData = _BEACON_GAMMA_TABLE_SIZE / I2C_GAMMA_DATA_LENGTH;
                if((_BEACON_GAMMA_TABLE_SIZE % I2C_GAMMA_DATA_LENGTH) != 0)
                {
                    g_wCacheData += 1;
                }


                if((g_ucUpdateGammaIndex > 0) && (g_ucUpdateGammaIndex <= _BEACON_GAMMA_MAX_NUM))
                {   

                    if(g_ucUpdateGammaIndex > _BEACON_GAMMA_ONE_BANK_NUM)
                    {
                        g_ucTargetBank = _BEACON_GAMMA_PARTITION1_FLASH_BANK;
                    }
                    else
                    {
                        g_ucTargetBank = _BEACON_GAMMA_PARTITION0_FLASH_BANK;
                    }

                    g_ucCount = _BEACON_GAMMA_TABLE_SIZE / 256;
                    if((_BEACON_GAMMA_TABLE_SIZE % 256) != 0)
                    {
                        g_ucCount += 1;
                    }

                    if((g_ucUpdateGammaIndex == 1) || (g_ucUpdateGammaIndex == (_BEACON_GAMMA_ONE_BANK_NUM + 1)))
                    {
                        // get first 3 byte data ,this is not gamma data, 
                        memset(g_ucCacheData, 0x00, 3);
                        UserCommonFlashRead(g_ucTargetBank, 0x0000, 3,  g_ucCacheData);
                    }

                    UserCommonFlashErasePage(g_ucTargetBank, g_ucBankPageIndex);
                    UserCommonFlashErasePage(g_ucTargetBank, g_ucBankPageIndex + 1);

                    if((g_ucUpdateGammaIndex == 1) || (g_ucUpdateGammaIndex == (_BEACON_GAMMA_ONE_BANK_NUM + 1)))
                    {
                        // restore first 3 byte data
                        UserCommonFlashWrite(g_ucTargetBank, 0x0000 , 3 , g_ucCacheData);
                    }
                
                    for(g_ucIndex = 0; g_ucIndex < g_ucCount; g_ucIndex++)
                    {     
                        g_wLength = 256;  // max is 256, dont set large 256 number
                        if(g_wLength > (_BEACON_GAMMA_TABLE_SIZE - g_ucIndex * 256))
                        {
                            g_wLength = (_BEACON_GAMMA_TABLE_SIZE - g_ucIndex * 256);
                        }
                        
                        g_wCacheData = g_wGammaStartAddr + g_ucIndex * 256; // write addr
                        memset(MCU_DDCRAM_D5, 0x00, 256);
                        UserCommonFlashRead(_BEACON_GAMMA_UPDATE_CACHE_FLASH_BANK, g_wCacheData, g_wLength,  MCU_DDCRAM_D5);

                        memset(g_ucCacheData, 0x00, 4);
                        UserCommonFlashRead(g_ucTargetBank, g_wCacheData, 4,  g_ucCacheData);
                        if((g_ucCacheData[0] == 0xFF) && (g_ucCacheData[1] == 0xFF) && (g_ucCacheData[2] == 0xFF) && (g_ucCacheData[3] == 0xFF))
                        {
                            
                            UserCommonFlashWrite(g_ucTargetBank, g_wCacheData , g_wLength , MCU_DDCRAM_D5);
                            
                            //check write data is success
                            memset(MCU_DDCRAM_MHL_D5, 0x00, g_wLength);
                            UserCommonFlashRead(g_ucTargetBank, g_wCacheData, g_wLength,  MCU_DDCRAM_MHL_D5);
                            for(i = 0; i < g_wLength; i++)
                            {
                                if(MCU_DDCRAM_MHL_D5[i] != MCU_DDCRAM_D5[i])
                                {
                                    g_bUpdateFlag = _FALSE;
                                    break;
                                }
                            }
                            
                            if(g_bUpdateFlag == _FALSE)
                            {
                                break;
                            }
                        }
                        else
                        {
                            // check data in gamma bank is the save as target data
                            memset(MCU_DDCRAM_MHL_D5, 0x00, g_wLength);
                            UserCommonFlashRead(g_ucTargetBank, g_wCacheData, g_wLength,  MCU_DDCRAM_MHL_D5);
                            for(i = 0; i < g_wLength; i++)
                            {
                                if(MCU_DDCRAM_MHL_D5[i] != MCU_DDCRAM_D5[i])
                                {
                                    g_bUpdateFlag = _FALSE;
                                    break;
                                }
                            }
                        }
                    } 

                    if(g_bUpdateFlag == _TRUE)
                    {
                        g_ucTmpdata = GET_OSD_GAMMA();
#if((_CUSTOMER == _CUS_TOSHIBA) && (_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND))
                        if(GET_COLOR_TEMP_TYPE() <_BEACON_ULTRASOUND)
#elif(_CUSTOMER == _CUS_BAISHENG)
                        if(GET_COLOR_TEMP_TYPE() <= _BEACON_USER)
#else
                        if(GET_COLOR_TEMP_TYPE() <_BEACON_USER)
#endif
                        {
                            g_ucTmpdata = GET_OSD_GAMMA() + _GAMMA_AMOUNT * GET_COLOR_TEMP_TYPE();
                        }

                        if(g_ucTmpdata == g_ucUpdateGammaIndex)
                        {
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                            CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif   
                        }
                        g_ucCommonCheckStatus = 1;
                    }
                    else
                    {
                        // save Target data error!
                        g_ucCommonCheckStatus = 4;
                    }

                }
                else
                {
                    // update gamma index is out off max gamma num,
                    g_ucCommonCheckStatus = 3;
                }
                
            }
            else
            {
                // update Gamma flag error!
                g_ucCommonCheckStatus = 2;
            }
            break; 

        case _DDCCI_UPATE_GAMMA_GET_BACKLIGTH_THREE_POINT:
            g_pucDdcciTxBuf[0] = 0x6e;  // Source
            g_pucDdcciTxBuf[1] = 0x86;  // Length //Byte size from next byte to before byte of checksum            
            g_pucDdcciTxBuf[2] = 0xc8;  // VCP Prefix 0xC0 0x00 0x00
            g_pucDdcciTxBuf[3] = 0x00;
            g_pucDdcciTxBuf[4] = _DDCCI_UPATE_GAMMA_GET_BACKLIGTH_THREE_POINT;  
            g_pucDdcciTxBuf[5] = GET_FACTORY_BACKLIGHT_REG_MIN();
            g_pucDdcciTxBuf[6] = GET_FACTORY_BACKLIGHT_REG_MID();
            g_pucDdcciTxBuf[7] = GET_FACTORY_BACKLIGHT_REG_MAX();
            g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum(); // checksum
            ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
            break;

        case _DDCCI_UPATE_GAMMA_SET_BACKLIGTH_MIN:          
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            SET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE(),g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
#else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
#endif                               
#else
            SET_FACTORY_BACKLIGHT_REG_MIN(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MIN()));
#else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN()));
#endif
#endif
            BeaconFactorySaveData();           
            break;

        case _DDCCI_UPATE_GAMMA_SET_BACKLIGTH_MID:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
             SET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE(),g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
             PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
#else
             PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
#endif                               
#else
             SET_FACTORY_BACKLIGHT_REG_MID(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
             PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MID()));
#else
             PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID()));
#endif
#endif     
            BeaconFactorySaveData();
            break;

        case _DDCCI_UPATE_GAMMA_SET_BACKLIGTH_MAX:
#if(_SECOND_COLORTEMP_THREE_POINT == _ON)
            SET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE(),g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
#else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
#endif                               
#else
            SET_FACTORY_BACKLIGHT_REG_MAX(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MAX()));
#else
            PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX()));
#endif
#endif
            BeaconFactorySaveData();
            break; 

        case _DDCCI_UPATE_GAMMA_SET_MONITOR_SN:
            g_ucCommonCheckStatus = 0;
            // range check...max length is 25
            if(g_pucDdcciRxBuf[4] > _MONITOR_SN_LENGTH)
            {
                g_pucDdcciRxBuf[4] = _MONITOR_SN_LENGTH;
            }

            // Save SN data
            {    
                memcpy(ucMonitorSn,&g_pucDdcciRxBuf[5],_MONITOR_SN_LENGTH);
                BeaconFactorySaveMonitorSN(ucMonitorSn);
            }
            g_ucCommonCheckStatus = 1;
            break;

        default:
            break;
    }

}

#endif

//--------------------------------------------------
// Description  : DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserDdcciHandler(void)
{
#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default))
    BYTE IsChecksumOK = _FALSE;
    BYTE ucChecksumIdx = 0;
#endif

    if(GET_OSD_DDCCI_STATUS() == _ON)
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
        {
        #if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default))
            ucChecksumIdx = (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) + 2; // 0x51, length
            if(UserCommonDdcciCalRxCheckSum() == g_pucDdcciRxBuf[ucChecksumIdx])
            {
                IsChecksumOK = _TRUE;
            }
        #endif
        
            switch(g_pucDdcciRxBuf[_DDCCI_COMMAND])
            {
                case _DDCCI_CMD_GET_VCP_FEATURE:
                    NoneDdcciGetVCPFeature();
                    break;

                case _DDCCI_CMD_SET_VCP_FEATURE:
                    NoneDdcciSetVCPFeature();
                    break;

                case _DDCCI_CMD_GET_TIMING_REPORT:
                    UserCommonDdcciGetTimingReport();
                    break;

                case _DDCCI_CMD_SAVE_CURRENT_SETTINGS:
                    break;

                case _DDCCI_CMD_CAPABILITIES_REQUEST:
                    UserCommonDdcciGetCapabilitiesRequest();
                    break;
                case _DDCCI_CMD_FACTORY_GAMMA_ADJUST:
#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE != Gamma_default))// for beacon gamma auto processing function 
                    if(IsChecksumOK)
                    {
                        RTDDdcciFactoryGammaAutoProcess();
                    }                    
#else
                    DDCCI_FactoryGammaAdjust();
#endif
                    break;

#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
                case _DDCCI_CMD_UPDATE_GAMMA_DATA:
                    DdcciUpdateGammaDataProcess();
                    break;
#endif

                default:
                    UserCommonDdcciInitTx();
                    break;
            }

            UserCommonDdcciInitRx();

            SET_RUN_DDCCI_COMMAND(_FAIL);
        }
    }
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    else
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if((GET_RUN_DDCCI_COMMAND() == _SUCCESS) && (UserInterfaceGetDpMSTCapablePort() != _DP_MST_NO_PORT))
        {
            UserCommonDdcciInitTx();
        }
    }
#endif
}

#if(_SUPPORT_GET_LUT == _ON)
DWORD NoneDdcciGetSn(void)
{
    BYTE xdata cnt;
    BYTE xdata cnt1;
    DWORD xdata TempSn = 0;
    DWORD xdata TenCount = 1;

    for(cnt = 10; cnt < 17; cnt++)
    {
        for(cnt1 = 17 -cnt; cnt1 > 1; cnt1 -- )
            TenCount *=10;
        TempSn = TempSn + ((ucMonitorSn[cnt] - 0x30) * TenCount);
        TenCount = 1;
    }
    return TempSn;
}
#endif

//--------------------------------------------------
// Description  : DDCCI Get VCP Feature & VCP Feature Reply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneDdcciGetVCPFeature(void)
{
    BYTE pucTemp[2] = {0};
    
    memset(g_pucDdcciTxBuf,0,_DDCCI_TXBUF_LENGTH);
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x08;
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY;
    g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_NO_ERROR;
    g_pucDdcciTxBuf[_DDCCI_SINK_OPCODE] = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE];

    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
    {
        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0002, g_ucDdcciNewControlValue);
            break;

#if(_CUSTOMER == _CUS_BAISHENG)
        case _DDCCI_OPCODE_VCP_RESET_FOR_BS:    
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0001, 0x00);
            break;
#endif

        case _DDCCI_OPCODE_VCP_INPUT_SOURCE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0003, OsdDispJudgeSourceType());
            break;

        case _DDCCI_OPCODE_VCP_BACKLIGHT:
#if(_CUSTOMER == _CUS_BAISHENG)
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,GET_OSD_BRIGHTNESS());
#else
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,GET_OSD_BACKLIGHT());
#endif
            break;

#if(_CUSTOMER == _CUS_BAISHENG)
        case _DDCCI_OPCODE_VCP_BACKLIGHT_FOR_BS:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,GET_OSD_BACKLIGHT());
            break;
#endif

        case _DDCCI_OPCODE_VCP_CONTRAST:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,GET_OSD_CONTRAST());
            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:
        #if(_NATIVE_COLORTEMP == _ON)
            if(GET_NATIVE_COLOR_TEMP())
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x000D, 0x02);
            else
        #endif
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x000D, tCOLORPRESET_VALUE[GET_COLOR_TEMP_TYPE()]);
            break;

        case _DDCCI_OPCODE_VCP_GAMMA:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x000C, (0x05+GET_OSD_GAMMA()));
            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:
            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
                pData[0] = 2;
            }
            else if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                pData[0] = 1;
            }
            else
            {
                pData[0] = 1;
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0002, pData[0]);
            break;

        case _DDCCI_OPCODE_VCP_PWM_Value: 
        {
#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
            //UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 4095, Get12BitPwmDuty());
#else
            BYTE  ucPWM;
#if(_BACKLIGHT_PWM_INVERSE == _ON)
            ucPWM  = 255 - ((PCB_GET_BACKLIGHT_PWM() * 255) / ((_PWM_DUT_RESOLUTION == _PWM_12BIT)? 4095:255));
#else
            ucPWM  = (PCB_GET_BACKLIGHT_PWM() * 255) / ((_PWM_DUT_RESOLUTION == _PWM_12BIT)? 4095:255); // Duty Width fine tune !!
#endif
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 255, ucPWM);
#endif
        }
            break;

#if(_ALS_TYPE != _SENSER_NONE)
#if(_CUSTOMER == _CUS_MINDRAY)
        case _DDCCI_OPCODE_VCP_AUTO_AMBIENT_LIGHT_SENSOR:
            if(GET_OSD_ALS_MANUAL_AUTO_STATUS() == _OFF)
                pucTemp[0] = 0x01;
            else
                pucTemp[0] = 0x00;
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, pucTemp[0]);
            break;

        case _DDCCI_OPCODE_VCP_AMBIENT_LIGHT_SENSOR:
            if(GET_OSD_ALS_MANUAL_AUTO_STATUS() == _OFF)
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xffff, (WORD)lux_confirmed);  //done
            else
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xffff, 0xffff);  // doing
            break;
#else
        case _DDCCI_OPCODE_VCP_AMBIENT_LIGHT_SENSOR:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xffff, (WORD)lux_confirmed);  //done
            break;
#endif
#endif

        case _DDCCI_OPCODE_VCP_RED_GAIN:
        #if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)
            pucTemp[0] = GET_COLOR_TEMP_TYPE();
            if(GET_COLOR_TEMP_TYPE() != _BEACON_USER)
            {
                SET_COLOR_TEMP_TYPE(_BEACON_USER);
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 255, GET_COLOR_TEMP_TYPE_USER_R());
            SET_COLOR_TEMP_TYPE(pucTemp[0]);
            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
        #endif
            break;

        case _DDCCI_OPCODE_VCP_GREEN_GAIN:
        #if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)
            pucTemp[0] = GET_COLOR_TEMP_TYPE();
            if(GET_COLOR_TEMP_TYPE() != _BEACON_USER)
            {
                SET_COLOR_TEMP_TYPE(_BEACON_USER);
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 255, GET_COLOR_TEMP_TYPE_USER_G());
            SET_COLOR_TEMP_TYPE(pucTemp[0]);
            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
        #endif
            break;

        case _DDCCI_OPCODE_VCP_BLUE_GAIN:
        #if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)
            pucTemp[0] = GET_COLOR_TEMP_TYPE();
            if(GET_COLOR_TEMP_TYPE() != _BEACON_USER)
            {
                SET_COLOR_TEMP_TYPE(_BEACON_USER);
                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 255, GET_COLOR_TEMP_TYPE_USER_B());
            SET_COLOR_TEMP_TYPE(pucTemp[0]);
            RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
        #endif
            break;

        case _DDCCI_OPCODE_VCP_HPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_H_POSITION());
            }
            else
#endif
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_DIGITAL_H_POSITION());
            }

            break;

        case _DDCCI_OPCODE_VCP_VPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysSourceGetSourceType() == _SOURCE_VGA)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_V_POSITION());
            }
            else
#endif
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_DIGITAL_V_POSITION());
            }
            break;
            
#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK_PHASE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_PHASE());
            break;
#endif

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK:

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_CLOCK());
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                BYTE ucClock = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                ucClock = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, ucClock);
            }
#endif
            break;        
#endif      
        case _DDCCI_OPCODE_VCP_FW_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x00FF, _SOFTWARE_VERSION);
            break;

        case _DDCCI_OPCODE_VCP_GET_HardwareVersion:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x00FF, _HARDWARE_VERSION);
            break;

    #if(_GET_HARD_ID == _ON)
        case _DDCCI_OPCODE_VCP_GET_HardID:
            g_ucHardID = (((WORD)PCB_HARD_ID3_DETECT())<<3) |(((WORD)PCB_HARD_ID2_DETECT())<<2) |(((WORD)PCB_HARD_ID1_DETECT())<<1) |(((WORD)PCB_HARD_ID0_DETECT())<<0);
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x000F, g_ucHardID);
            break;
    #endif

        case _DDCCI_OPCODE_VCP_g_SignalUnstable:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, g_ucSignalUnstable);
            break;

        case _DDCCI_OPCODE_VCP_g_IssueState:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, g_ucIssueState);
            break;

#if(_ASPECT_RATIO_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_DISPLAY_SCALING:
            pData[0] = 0x00;
#if(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_1) 
            switch(GET_OSD_ASPECT_RATIO_TYPE())
            {
                case _OSD_ASPECT_RATIO_ORIGIN:
                    pData[0] = 0x01;
                    break;
                case _OSD_ASPECT_RATIO_MAXIMAGE:
                    pData[0] = 0x02;
                    break;          
                case _OSD_ASPECT_RATIO_VMAXIMAGE:
                    pData[0] = 0x03;
                    break;          
                case _OSD_ASPECT_RATIO_HMAXIMAGE:
                    pData[0] = 0x04;
                    break;
                case _OSD_ASPECT_RATIO_FULL:
                    pData[0] = 0x07;
                    break;
                default:
                    break;
            }
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_6)
            switch(GET_OSD_ASPECT_RATIO_TYPE())
            {       
                case _OSD_ASPECT_RATIO_VMAXIMAGE:
                    pData[0] = 0x03;
                    break;          
                case _OSD_ASPECT_RATIO_FULL:
                    pData[0] = 0x07;
                    break;
                default:
                    break;
            }
#endif
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0007, pData[0]);

            break;
#endif

        case _DDCCI_OPCODE_VCP_MONITOR_STATUS:
            pData[0] = 0x0000;
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0008, pData[0]);
            break;

        case _DDCCI_OPCODE_VCP_HV_FREQ:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, g_stMDomainInputData.usHFreq, g_stMDomainInputData.usVFreq);
            break;

        case _DDCCI_OPCODE_VCP_HV_TOTAL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, g_stMDomainInputData.usHTotal, g_stMDomainInputData.usVTotal);
            break;

        case _DDCCI_OPCODE_VCP_HV_PIXEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, g_stMDomainInputData.usHWidth, g_stMDomainInputData.usVHeight);
            break;

        case _DDCCI_OPCODE_VCP_HV_SYNC_WIDTH:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, g_stInputTimingData.usHSWidth, g_stInputTimingData.usVSWidth);
            break;

        case _DDCCI_OPCODE_VCP_HV_START:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, g_stMDomainInputData.usHStart, g_stMDomainInputData.usVStart);
            break;

        case _DDCCI_OPCODE_VCP_CURRENT_STATE:
            //_MODE_STATUS_FACTORY~
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0007, SysModeGetModeState());
            break;

        case _DDCCI_OPCODE_VCP_HFREQ:
            // PDATA_DWORD(0) = (DWORD)GET_INPUT_TIMING_HFREQ() * 100;
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, LOWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)), HIWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)));
            break;

        case _DDCCI_OPCODE_VCP_VFREQ:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, GET_INPUT_TIMING_VFREQ()*10);
            break;

    #if(_SUPPORT_GET_LUT == _ON)
        case _DDCCI_OPCODE_VCP_DISP_DESCRIPTOR_LENGTH://0xc2:
        //standrad ddcci command for read sn
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (WORD)(NoneDdcciGetSn() >> 16), (WORD)NoneDdcciGetSn());        
            break;
            
    #else      
        case _DDCCI_OPCODE_VCP_DISP_DESCRIPTOR_LENGTH://0xc2:
        //standrad ddcci command for read sn
        {
            BYTE xdata cnt;
        #if 0           
            BYTE xdata checksum = 0;
            MCU_I2C_IRQ_CTRL2_FF2A |= 0x60;
            MCU_I2C_DATA_OUT_FF26 = _DDCCI_DEST_ADDRESS;
            MCU_I2C_DATA_OUT_FF26 = 0x80|(_MONITOR_SN_LENGTH);

            for(cnt = 0; cnt < _MONITOR_SN_LENGTH; cnt++)
            {
                MCU_I2C_DATA_OUT_FF26 = ucMonitorSn[cnt];
                checksum = checksum^ucMonitorSn[cnt];
            }
            MCU_I2C_DATA_OUT_FF26 =_DDCCI_VIRTUAL_HOST_ADDRESS^ checksum^_DDCCI_DEST_ADDRESS^(0x80|(_MONITOR_SN_LENGTH));

            MCU_I2C_IRQ_CTRL2_FF2A &= (~_BIT5);
        #else
            if(_MONITOR_SN_LENGTH <= _DDCCI_TXBUF_LENGTH - 3)
            {
                g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
                g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | (_MONITOR_SN_LENGTH);
                for(cnt = 0; cnt < _DDCCI_TXBUF_LENGTH - 3; cnt++)
                {
                    if(cnt < _MONITOR_SN_LENGTH)
                    {
                        g_pucDdcciTxBuf[cnt+2] = ucMonitorSn[cnt];
                    }
                    else
                    {
                        break;
                    }
                }
                g_pucDdcciTxBuf[2+_MONITOR_SN_LENGTH] = UserCommonDdcciCalCheckSum();
            }
        #endif   
            break;
        }
    #endif

        case _DDCCI_OPCODE_VCP_SHARPNESS:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0004, GET_OSD_SHARPNESS());
            break;    

        case _DDCCI_OPCODE_VCP_VERSION:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, 0x0202);
            break;

        case _DDCCI_OPCODE_VCP_CONTROL_LOCK:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 1,GET_FACTORY_LOCK_STATE());
            break;

#if(_SUPPORT_GET_LUT == _ON)      
        case _DDCCI_OPCODE_VCP_LUT_TABLE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, g_ucLUTReadyFlag, g_ucLUTCheckSum);
            break;
#endif

        case _DDCCI_OPCODE_VCP_GET_SVNVERSION:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, _SVN_VERSION);
            break;

        case _DDCCI_OPCODE_VCP_MONITOR_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x05, 3);
            break;           

#if(_KL_5V_12V_GPIO_CONTROL == _ON)
        case _DDCCI_OPCODE_VCP_CONTROL_PANEL_5V_PCTR:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, PCB_PANEL_5V_PCTR_DETECT());
            break;

        case _DDCCI_OPCODE_VCP_CONTROL_PANEL_12V_PCTR:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, PCB_PANEL_12V_PCTR_DETECT());
            break;
#endif

#if(_BACKLIGHT_SENSOR == _ON)
        case _DDCCI_OPCODE_VCP_BACKLIGHTSENSOR_ONOFF:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0001, GET_BACKLIGHTSENSOR_ONOFF());
            break;
#endif


        default:
            g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_UNSUPPORTED;
            break;
    }
    
#if(_SUPPORT_GET_LUT == _OFF)
    if(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE] !=0xc2)
        g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE + 1] = UserCommonDdcciCalCheckSum(); 
#else
    g_pucDdcciTxBuf[_DDCCI_PRESENT_LOW_BYTE + 1] = UserCommonDdcciCalCheckSum();
#endif

    ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
}

//--------------------------------------------------
// Description  : Check DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit NoneDdcciSetVCPFeatureCheck(void)
{
    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
    {
        case _DDCCI_OPCODE_VCP_FACTORY_RESET:
        case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
        case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:
        case _DDCCI_OPCODE_VCP_COLOR_RESET:

            if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0)
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
     //   case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
     //   case _DDCCI_OPCODE_VCP_AUTO_COLOR:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 3))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x0E))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x26))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x06))
            {
                return _FALSE;
            }

            break;


        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void NoneDdcciSetVCPFeature(void)
{
    BYTE ucTemp = 0;

    //   BYTE ucGamma,ucColorTempType;
#if(_SUPPORT_GET_LUT == _ON)
    WORD usCount = 0;
    WORD usGammaAddress =0;
#endif

    if(NoneDdcciSetVCPFeatureCheck() == _FAIL)
    {
        UserCommonDdcciInitTx();
    }
    else
    {
        switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
        {
            case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    g_ucDdcciNewControlValue = 0x01;
                }

                break;

            case _DDCCI_OPCODE_VCP_SOFT_CONTROLS:
                //Beacon DDC-CI Test Tool (Version 2)
                //Menu:   51 84 03 03 00 01 CheckSum:BA
                //Left:   51 84 03 03 00 02 CheckSum:B9
                //Right:  51 84 03 03 00 03 CheckSum:B8
                //Exit:   51 84 03 03 00 04 CheckSum:BF
                //Factory:51 84 03 03 00 05 CheckSum:BE
                if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 1) && (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= 4))
                {
                    //(*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();
                    //(*OperationTable[GET_OSD_STATE()][CmdPara[0]])();
                    SET_KEYMESSAGE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] -1);
                    
                    if(g_ucBeaconFacOsdShowFlag)
                        BeaconFactoryOsdMenuOperation();
                    else
                    {
                        (*OperationTable[GET_OSD_STATE()][GET_KEYMESSAGE()])();
                        if((GET_OSD_STATE() == _BEACON_HOTKEY_OSD_1)||(GET_OSD_STATE() == _BEACON_HOTKEY_OSD_2))
                        {
                            ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                        }
                    }
                    
                    SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
        
                }
                      // SET_KEYMESSAGE(CmdPara[0]);            
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 5)
                {
                    if( GET_OSD_STATE() == _BEACON_OSD_NONE)
#if(_USER_BEACON_FACTORY_OSD == _ON)
                        BeaconFactoryOsdPage1();
#else
                    ;
#endif
                    if((GET_OSD_STATE() != _BEACON_OSD_NONE)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_1)&&(GET_OSD_STATE() != _BEACON_HOTKEY_OSD_2))
                    {
                            BeaconAdvancedOsdDisplayProc();
                    }   
                }

                break;

            case _DDCCI_OPCODE_VCP_FACTORY_RESET:
                RTDDdcciResetAllSettings();

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    UserCommonAutoConfig();
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(50);
                    SET_DIGITAL_V_POSITION(50);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

#if(_CUSTOMER == _CUS_BAISHENG)
            case _DDCCI_OPCODE_VCP_RESET_FOR_BS:
            {
                BYTE ucRealGammaNum;
                ucRealGammaNum = GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE();
                BeaconFuncResetOSD();
                UserInterfaceAdjustColorProc();
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                if((GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE())!= ucRealGammaNum)
                {
                    CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
                }
#endif
                break;
            }
#endif

            case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:

                RTDNVRamRestoreBriCon();
                RTDNVRamRestoreBacklight();

                UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
                break;

            case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    UserCommonAutoConfig();
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(50);
                    SET_DIGITAL_V_POSITION(50);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

            case _DDCCI_OPCODE_VCP_COLOR_RESET:

                RTDDdcciColorReset();

                break;

            case _DDCCI_OPCODE_VCP_FACTORY_TV_RESET:
                {
                    BYTE ucRealGammaNum;
                    ucRealGammaNum = GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE();
                    BeaconFuncResetOSD();
                    UserInterfaceAdjustColorProc();
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                    if((GET_OSD_GAMMA()+ _GAMMA_AMOUNT*GET_COLOR_TEMP_TYPE())!= ucRealGammaNum)
                    {
                        CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
                    }
#endif
                    break;
                }
                
            case _DDCCI_OPCODE_VCP_INPUT_SOURCE:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSwitchInputPort(_VGA_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x03)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSwitchInputPort(_DVI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x04)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSwitchInputPort(_DVI_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x0F)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSwitchInputPort(_DP_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x10)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSwitchInputPort(_DP_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x11)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSwitchInputPort(_HDMI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x12)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysSourceSwitchInputPort(_HDMI_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_SEARCH);
                }
                break;

            case _DDCCI_OPCODE_VCP_BACKLIGHT:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }
#if(_CUSTOMER == _CUS_BAISHENG)
                SET_OSD_BRIGHTNESS(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                UserAdjustBrightness(GET_OSD_BRIGHTNESS());           
#else
                SET_OSD_BACKLIGHT(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_BACKLIGHT_SENSOR == _ON)
                UserAdjustSetSensorbacklightvalue(1);
#endif

#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
                break;

#if(_CUSTOMER == _CUS_BAISHENG)
            case _DDCCI_OPCODE_VCP_BACKLIGHT_FOR_BS:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }
                SET_OSD_BACKLIGHT(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_BACKLIGHT_SENSOR == _ON)
                UserAdjustSetSensorbacklightvalue(1);
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
                break;                
#endif

            case _DDCCI_OPCODE_VCP_CONTRAST:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_CONTRAST(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                UserAdjustContrast(GET_OSD_CONTRAST());
#if 1//(_RECOVER_PARAMETER == _OFF)
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
#endif
                break;

            case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:
            {
                BYTE m_ColorTemp_Target = 0xFF;
                BYTE m_Native_ColorTemp_Target = 0;
                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                #if(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_9300;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_11000;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_14000;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
                #elif(_COLOR_TEMP_SELECT_TYPE == _9300K_6500K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_9300;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_6500;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
                #elif(_COLOR_TEMP_SELECT_TYPE == _9300K_13000K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_9300;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_13000;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
                #elif(_COLOR_TEMP_SELECT_TYPE == _6500K_9300K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_6500;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
                #elif(_COLOR_TEMP_SELECT_TYPE == _6700K_9300K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_6700;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
                #elif(_COLOR_TEMP_SELECT_TYPE == _13000K_9300K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_13000;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
                #elif(_COLOR_TEMP_SELECT_TYPE == _11000K_9300K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_11000;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_9300;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break; 
                #elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_Normal;
                        break;
                    case 0x08:
                        m_ColorTemp_Target = _BEACON_Cool;
                        break;
                    case 0x05:
                        m_ColorTemp_Target = _BEACON_Warm;
                        break; 
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break; 
                #elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)
                    case 0x0A:
                        m_ColorTemp_Target = _BEACON_ULTRASOUND;
                        break;
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_13000;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_7500;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;
                #elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K)
                    case 0x0B:
                        m_ColorTemp_Target = _BEACON_7500;
                        break;
                    case 0x0C:
                        m_ColorTemp_Target = _BEACON_13000;
                        break; 
                    case 0x0D:
                        m_ColorTemp_Target = _BEACON_USER;
                        break;
                    case 0x02:
                        m_Native_ColorTemp_Target = 1;
                        break;
                    default:
                        m_ColorTemp_Target = _DEFAULT_COLOR_TEMP;
                        break;                         
                #else
                    case 0x0B:
                        m_ColorTemp_Target = _CT_USER;
                        break;                    
                    case 0x05:
                        m_ColorTemp_Target = _CT_6500;
                        break;                    
                    case 0x08:
                        m_ColorTemp_Target = _CT_9300;
                        break;                    
                    case 0x01:
                        m_ColorTemp_Target = _CT_SRGB;
                        break;                    
                    case 0x04:
                        m_ColorTemp_Target = _CT_5800;
                        break;                    
                    case 0x06:
                        m_ColorTemp_Target = _CT_7500;
                        break;                    
                    case 0x02:
                        m_ColorTemp_Target = _CT_OFF;
                        break;
                    default:
                        break;
                #endif
                }
                
                if(m_ColorTemp_Target != 0xFF)
                {
                    SET_COLOR_TEMP_TYPE(m_ColorTemp_Target);
                }
            
            #if(_NATIVE_COLORTEMP == _ON)
                SET_NATIVE_COLOR_TEMP(m_Native_ColorTemp_Target);
            #endif            

                RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                UserAdjustContrast(GET_OSD_CONTRAST());
            #if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
            #endif

            #if 1//(_RECOVER_PARAMETER == _OFF)
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
            #endif
                break;
            }
            
            case _DDCCI_OPCODE_VCP_GAMMA:
            {
                BYTE mBackup_OSD_Gammma;
                mBackup_OSD_Gammma = GET_OSD_GAMMA();
                
                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x06:
                        SET_OSD_GAMMA(_GAMMA_1);
                        break;
                    case 0x07:
                        SET_OSD_GAMMA(_GAMMA_2);
                        break;
                    case 0x08:
                        SET_OSD_GAMMA(_GAMMA_3);
                        break;
                    case 0x09:
                        SET_OSD_GAMMA(_GAMMA_4);
                        break;
                    case 0x0A:
                        SET_OSD_GAMMA(_GAMMA_5);
                        break;
                    case 0x0B:
                        SET_OSD_GAMMA(_GAMMA_6);
                        break;
                    case 0x0C:
                        SET_OSD_GAMMA(_GAMMA_7);
                        break;

                    default:
                        SET_OSD_GAMMA(_DEFAULT_GAMMA);
                        break;
                }

                if(GET_OSD_GAMMA() <= _GAMMA_NUMBERS)
                {
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
                    CAdjustGammaTmp(GET_OSD_GAMMA(),GET_COLOR_TEMP_TYPE());
#endif
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
                }
                else
                {
                    SET_OSD_GAMMA(mBackup_OSD_Gammma);
                }
                break;
            }
            
            case _DDCCI_OPCODE_VCP_POWER_MODE:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 2)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 1)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
                break;

            case _DDCCI_OPCODE_VCP_PWM_Value:
            {
#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
                //WORD wTmp = 0;
                //wTmp = g_pucDdcciRxBuf[_DDCCI_SET_HIGH_BYTE] * 256 + g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                //if(wTmp <= 4095)
                //{
                //    CAdjustSensorBacklight(wTmp);
                //}
#else                
#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]));
#else
                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]));
#endif   

#if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
                UserCommonInterfaceOledAdjustBackLight(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#endif
#endif
            }
                break;
#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0)
                    {
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
                    }
                }
                break;
#endif

#if(_ALS_TYPE != _SENSER_NONE)
#if(_CUSTOMER == _CUS_MINDRAY)
            case _DDCCI_OPCODE_VCP_AUTO_AMBIENT_LIGHT_SENSOR:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x00)
                {
                    SET_OSD_ALS_MANUAL_AUTO_STATUS(_ON);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    SET_OSD_ALS_MANUAL_AUTO_STATUS(_OFF);
                    lux_confirmed = 0xffff;
                }

#if(_RECOVER_PARAMETER == _OFF)
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
#endif
                break;
#endif
#endif

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUTO_COLOR:
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0)
                    {
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_COLOR_MSG);
                        //BeaconFactoryAutoColor();
                    }
                }
                break;
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_DISPLAY_SCALING:
                ucTemp = GET_OSD_ASPECT_RATIO_TYPE();
#if(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_1)            
                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x01:
                        SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_ORIGIN);
                        break;
                        
                    case 0x02:
                        SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_MAXIMAGE);
                        break;
                        
                    case 0x03:
                        SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_VMAXIMAGE);
                        break;
                        
                    case 0x04:
                        SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_HMAXIMAGE);
                        break;
                        
                    case 0x07:
                        SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
                        break;
                      
                    default:
                        break;
                }
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_6)
                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x03:
                        SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_VMAXIMAGE);
                        break;

                    case 0x07:
                        SET_OSD_ASPECT_RATIO_TYPE(_OSD_ASPECT_RATIO_FULL);
                        break;
                      
                    default:
                        break;
                }
#endif                
                if(ucTemp != GET_OSD_ASPECT_RATIO_TYPE())
                {
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
                }

                break;
#endif

#if(_SHARPNESS_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_SHARPNESS:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > _SHARPNESS_MAX)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = _SHARPNESS_MAX;
                }
                SET_OSD_SHARPNESS(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserCommonAdjustSharpness(SysSourceGetInputPort());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;
#endif

            case _DDCCI_OPCODE_VCP_CLOCK:

#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
                    SET_VGA_MODE_ADJUST_CLOCK(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#else
                    {
                        WORD usClockRangeMax = 0;
                        WORD usClockRangeMin = 0;

                        usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                        usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);

                        SET_VGA_MODE_ADJUST_CLOCK(UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin)));
                    }
#endif
                    UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
#endif // End of #if(_VGA_SUPPORT == _ON)

                break;

            case _DDCCI_OPCODE_VCP_RED_GAIN:                
                // Only write at customer color
            #if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)
                if(GET_COLOR_TEMP_TYPE() != _BEACON_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();
                    SET_COLOR_TEMP_TYPE(_BEACON_USER);                   
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                    SET_COLOR_TEMP_TYPE_USER_R(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
                    SET_COLOR_TEMP_TYPE(ucTemp);
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_R(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserAdjustContrast(GET_OSD_CONTRAST());
                    //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);//Note_save150916
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
                }
            #endif   
                break;

            case _DDCCI_OPCODE_VCP_GREEN_GAIN:
                // Only write at customer color
            #if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)
                if(GET_COLOR_TEMP_TYPE() != _BEACON_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();
                    SET_COLOR_TEMP_TYPE(_BEACON_USER);                    
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                    SET_COLOR_TEMP_TYPE_USER_G(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
                    SET_COLOR_TEMP_TYPE(ucTemp);
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_G(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserAdjustContrast(GET_OSD_CONTRAST());
                    // SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);	//Note_save150916
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
                }
            #endif
                break;

            case _DDCCI_OPCODE_VCP_BLUE_GAIN:
                // Only write at customer color
            #if(_COLOR_TEMP_SELECT_TYPE != _14000K_11000K_9300K)
                if(GET_COLOR_TEMP_TYPE() != _BEACON_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE();
                    SET_COLOR_TEMP_TYPE(_BEACON_USER);                    
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                    SET_COLOR_TEMP_TYPE_USER_B(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE());
                    SET_COLOR_TEMP_TYPE(ucTemp);
                    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_B(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserAdjustContrast(GET_OSD_CONTRAST());
                    //SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG); //Note_save150916
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_OSD_USER_DATA_MSG);
                }
            #endif
                break;

            case _DDCCI_OPCODE_VCP_HPOSITION:
#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    SET_VGA_MODE_ADJUST_H_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_H_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustHPosition(GET_DIGITAL_H_POSITION());
                }
                break;

            case _DDCCI_OPCODE_VCP_VPOSITION:
#if(_VGA_SUPPORT == _ON)
                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(abs(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] - GET_VGA_MODE_ADJUST_V_POSITION()) > 50)
                    {
                        SET_VGA_MODE_ADJUST_V_POSITION(50);
                    }
                    SET_VGA_MODE_ADJUST_V_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
                else
#endif
                {
                    SET_DIGITAL_V_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustVPosition(GET_DIGITAL_V_POSITION());
                }

                break;

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_CLOCK_PHASE:

                if(SysSourceGetSourceType() == _SOURCE_VGA)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

                    SET_VGA_MODE_ADJUST_PHASE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                    UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }

                break;
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
            case _DDCCI_OPCODE_VCP_DISP_CALIBRATION:

                UserCommonDdcciDispCalibProcess();

                break;
#endif

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
            case _DDCCI_OPCODE_VCP_BACKLIGHTSENSOR_ONOFF:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= 1)
                {
                    SET_BACKLIGHTSENSOR_ONOFF(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    if((GET_BACKLIGHTSENSOR_ONOFF() == _OFF))
                    {
                        ClearDiffValueBySetMidPwm();
                        UserAdjustBacklight(GET_OSD_BACKLIGHT());
                    }
                    BeaconFactorySaveData();
                }
                break;
#endif


            case _DDCCI_OPCODE_VCP_CONTROL_LOCK:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= 1)
                {
                    SET_FACTORY_LOCK_STATE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    BeaconFactorySaveData();
                }
                break;

#if(_SUPPORT_GET_LUT == _ON)         
             case _DDCCI_OPCODE_VCP_LUT_TABLE:
             {
                //0x00—14000K/GAMMA0/R (256byte)
                //0x01—14000K/GAMMA0/G (256byte)
                //0x02—14000K/GAMMA0/B (256byte)
                //0x03—14000K/GAMMA1/R (256byte)
                //0x04—14000K/GAMMA1/G (256byte)
                //0x05—14000K/GAMMA1/B (256byte)
                //0x06—14000K/GAMMA2/R (256byte)
                //0x07—14000K/GAMMA2/G (256byte)
                //0x08—14000K/GAMMA2/B (256byte)
                //0x09—11000K/GAMMA0/R (256byte)
                //0x0A—11000K/GAMMA0/G (256byte)
                //0x0B—11000K/GAMMA0/B (256byte)
                //0x0C—11000K/GAMMA1/R (256byte)
                //0x0D—11000K/GAMMA1/G (256byte)
                //0x0E—11000K/GAMMA1/B (256byte)
                //0x0F—11000K/GAMMA2/R (256byte)
                //0x10—11000K/GAMMA2/G (256byte)
                //0x11—11000K/GAMMA2/B (256byte)
                //0x12—9300K/GAMMA0/R  (256byte)
                //0x13—9300K/GAMMA0/G  (256byte)
                //0x14—9300K/GAMMA0/B  (256byte)
                //0x15—9300K/GAMMA1/R  (256byte)
                //0x16—9300K/GAMMA1/G  (256byte)
                //0x17—9300K/GAMMA1/B  (256byte)
                //0x18—9300K/GAMMA2/R  (256byte)
                //0x19—9300K/GAMMA2/G  (256byte)
                //0x1A—9300K/GAMMA2/B  (256byte)
                //0xFF 及其他—将原始 EDID 放回 Buffer
#if(BEACON_GAMMA_TYPE == Gamma_9x2CT_2Bank)
                BYTE GammaIndex = 0; 
                BYTE ColorTempIndex = 0;
                BYTE GammaRGBIndex = 0; 
                WORD GammaBank = 0;
#endif
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= 0x1A)
                {
                    g_ucLUTCheckSum = 0;
                    g_ucLUTReadyFlag = 0;
#if(BEACON_GAMMA_TYPE == Gamma_10x2CT_2Bank)
             
#else

        //          bTestForBrightnessDdcci = 1;    7ms
                #if((_D1_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_256)  && (_D3_EMBEDDED_DDCRAM_MAX_SIZE >= _EDID_SIZE_256))  
#if(BEACON_GAMMA_TYPE == Gamma_9x2CT_2Bank)
                    ColorTempIndex = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] / 9;
                    GammaIndex = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] % 9;
                    GammaIndex = GammaIndex / 3 + 1;
                    GammaRGBIndex = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] % 3;
                    usGammaAddress = UserCommonAdjustGammaAddrData(GammaIndex,ColorTempIndex) + GammaRGBIndex * 256;
                    GammaBank = UserCommonAdjustGammaBank(GammaIndex,ColorTempIndex);
                    UserCommonFlashRead(GammaBank, usGammaAddress, 256,  MCU_DDCRAM_D1);    
#else
                    usGammaAddress = _GAMMA_LUT_FLASH_ADDR(1) + (WORD)g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] * 256;
                    UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, usGammaAddress, 256,  MCU_DDCRAM_D1);
#endif

                    memcpy(MCU_DDCRAM_D3, MCU_DDCRAM_D1, 256);                    
                    for(usCount = 0; usCount < 256; usCount++)
                    {
                        g_ucLUTCheckSum += MCU_DDCRAM_D1[usCount];
                    }       
                    g_ucLUTReadyFlag = 1;
                #endif
#endif
                }
                else
                    UserCommonInterfaceLoadEmbeddedEdidData();
    
                break;
            }
             
            case _DDCCI_OPCODE_VCP_RECOVER_EDID:
                UserCommonInterfaceLoadEmbeddedEdidData();
                break;
  
#endif

#if(_KL_5V_12V_GPIO_CONTROL == _ON)
            case _DDCCI_OPCODE_VCP_CONTROL_PANEL_5V_PCTR:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= 0x01)
                {
                    PCB_PANEL_5V_PCTR(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                }
                break;

            case _DDCCI_OPCODE_VCP_CONTROL_PANEL_12V_PCTR:
                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= 0x01)
                {
                    PCB_PANEL_12V_PCTR(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                }
                break;
#endif

            default:
                UserCommonDdcciInitTx();
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Reset monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciResetAllSettings(void)
{
    UserCommonNVRamRestoreSystemData();
    RTDNVRamRestoreOSDData();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();
#endif

    if((UserCommonNVRamGetSystemData(_SEARCH_PORT) != SysSourceGetInputPort()) ||
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
    {
        UserCommonNVRamSetSystemData(_SEARCH_PORT, SysSourceGetInputPort());
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        UserCommonNVRamSaveSystemData();
    }

    RTDDdcciColorReset();
}

//--------------------------------------------------
// Description  : Reset color to default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciColorReset(void)
{
    RTDNVRamRestoreUserColorSetting();
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

    RTDNVRamRestoreBriCon();
    RTDNVRamRestoreBacklight();

    UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
    UserAdjustBrightness(GET_OSD_BRIGHTNESS());
#endif
}


#endif//#if(_OSD_TYPE == _BEACON_OSD)
