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
// ID Code      : RL6449_DEMO_LOCAL_DIMMING_1USB1H1TC.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6449_DEMO_LOCAL_DIMMING_1USB1H1TC)


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#define _EXT_XTAL                               _XTAL14318K


///////////////
// Debug DDC //
///////////////

//--------------------------------------------------
// Debug DDC Channel
//--------------------------------------------------
#define _PCB_DEBUG_DDC                          _DDC2


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#define _A0_INPUT_PORT_TYPE                     _A0_NO_PORT
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                     _D0_DP_PORT
#define _D0_DDC_CHANNEL_SEL                     _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_TYPE_C
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_TWO_LANE

#define _D0_DP_TYPE_C_PORT_CTRL_TYPE            _PORT_CONTROLLER_USER

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                     _D3_HDMI_PORT
#define _D3_DDC_CHANNEL_SEL                     _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER

// For HDMI MultiEdid
#define _D3_MAX_HDMI_EDID_COUNT                 2


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D2_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_4                _NO_INPUT_PORT

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#define _D0_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE2
#define _D0_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE3
#define _D0_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE0
#define _D0_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE1
#define _D0_DP_PCB_LANE0_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE1_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE2_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE3_PN_SWAP                _OFF


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_FB_SWAP                 _DISABLE
#define _PANEL_DPTX_1_1_LANE_SWAP               _DISABLE
#define _PANEL_DPTX_1_1_LANE_PN_SWAP            _DISABLE
#define _PANEL_DPTX_1_1_SWING_LEVEL             _DP_SWING_800_MV
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_SPREAD_RANGE            12
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K

//--------------------------------------------------
// Definitions of eDP Panel Power Sequence
//
// Panel On Sequence
//       _________       ________      ________
//       |       |       |      |      |      |
// ______|       |_______|      |______|      |______
//
//   Panel_On  HPD_ON    LT    IDLE   VIDEO  BL_ON
//
// Panel Off Sequence
//
//       _________
//       |       |
// ______|       |_______
//
//    BL_OFF    IDLE
//--------------------------------------------------
#define _DPTX_POWER_SEQUENCE_PANEL_ON           _HIGH
#define _DPTX_POWER_SEQUENCE_HPD_ON             _LOW
#define _DPTX_POWER_SEQUENCE_LINK_TRAINING      _HIGH
#define _DPTX_POWER_SEQUENCE_IDLE_PATTERN       _LOW
#define _DPTX_POWER_SEQUENCE_VIDEO_PATTERN      _HIGH
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_ON       _LOW
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_OFF      _HIGH




/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT

#define _BACKLIGHT_PWM                          _PWM5
#define _BACKLIGHT_PWM_INVERSE                  _ON

#define _PWM0_EN                                _ON
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _ON

#define _PWM0_PSAV_EN                           _ON
#define _PWM1_PSAV_EN                           _OFF
#define _PWM2_PSAV_EN                           _OFF
#define _PWM3_PSAV_EN                           _OFF
#define _PWM4_PSAV_EN                           _OFF
#define _PWM5_PSAV_EN                           _OFF

#define _PWM0_PDOW_EN                           _OFF
#define _PWM1_PDOW_EN                           _OFF
#define _PWM2_PDOW_EN                           _OFF
#define _PWM3_PDOW_EN                           _OFF
#define _PWM4_PDOW_EN                           _OFF
#define _PWM5_PDOW_EN                           _OFF

#define _PWM0_RST_EN                            _OFF
#define _PWM1_RST_EN                            _OFF
#define _PWM2_RST_EN                            _ON
#define _PWM3_RST_EN                            _OFF
#define _PWM4_RST_EN                            _OFF
#define _PWM5_RST_EN                            _ON
#define _PWM_RST_SIGNAL_SEL                     _DVS


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                         _ON
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _ON
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24WC64
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _HW_IIC_PIN_210_211


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#define _AD_KEY_SUPPORT                         _ON

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#define _LOW_SPEED_ADC_SUPPORT                  _ON


//////////////////////
// Series Pin Share //
//////////////////////
#include "RL6449_DEMO_LOCAL_DIMMING_1USB1H1TC_PINSHARE.h"


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                    PCB_AMP_MUTE(_AMP_MUTE_OFF);\
                                                    bBACKLIGHTPOWER = _LIGHT_CONTROL_OFF;\
                                                    /*need enable Vsync for SPI communication*/\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 480);\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (0x30));\
                                                    PCB_LED_DRIVER_POWER(_PCB_LED_DRIVER_POWER_ON);\
                                                }

#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                {\
                                                }

#define PCB_GPIO_SETTING_POWER_NORMAL()         {\
                                                    /*need enable Vsync for SPI communication*/\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 480);\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (0x30));\
                                                    PCB_LED_DRIVER_POWER(_PCB_LED_DRIVER_POWER_ON);\
                                                }

#define PCB_GPIO_SETTING_POWER_SAVING()         {\
                                                    PCB_LED_DRIVER_POWER(_PCB_LED_DRIVER_POWER_OFF);\
                                                    bBACKLIGHTPOWER = _LIGHT_CONTROL_OFF;\
                                                }

#define PCB_GPIO_SETTING_POWER_DOWN()           {\
                                                    PCB_LED_DRIVER_POWER(_PCB_LED_DRIVER_POWER_OFF);\
                                                    bBACKLIGHTPOWER = _LIGHT_CONTROL_OFF;\
                                                }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#define bVCCKOFFPOWER                           (MCU_FE21_PORT81_PIN_REG) // _PIN_179,1D1V_OFF_EN_CPU, P8.1

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#define bDDRPOWER                               (MCU_FE2E_PORT96_PIN_REG) // _PIN_200,1D8V_EN_CPU, P9.6

#define _DDR_POWER_ON                           1
#define _DDR_POWER_OFF                          0

#define PCB_DDR_POWER(x)                        {\
                                                    bDDRPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#define bREGULATOR_5V                           (MCU_FE22_PORT82_PIN_REG) // Pin_180, P8.2

#define _REGULATOR_5V_ON                        0
#define _REGULATOR_5V_OFF                       1

#define PCB_REGULATOR_5V_OUT(x)                 {\
                                                    bREGULATOR_5V = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define bPANELPOWER                             (MCU_FE19_PORT71_PIN_REG) // _PIN_158,GPIO_158_CPU_PANELVCC_EN, P7.1

#define _PANEL_CONTROL_ON                       1
#define _PANEL_CONTROL_OFF                      0

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define bBACKLIGHTPOWER                         (MCU_FE25_PORT85_PIN_REG) // _PIN_185,GPIO_185_CPU_BLEN, P8.5

#define _LIGHT_CONTROL_ON                       1
#define _LIGHT_CONTROL_OFF                      0

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    if(_LIGHT_CONTROL_ON == (x))\
                                                    {\
                                                        bBACKLIGHTPOWER = _LIGHT_CONTROL_ON;\
                                                        ScalerTimerDelayXms(20);\
                                                        ExternalDeviceInterfaceLedDriverPwmEnable(_ENABLE);\
                                                    }\
                                                    else\
                                                    {\
                                                        ExternalDeviceInterfaceLedDriverPwmEnable(_DISABLE);\
                                                        ScalerTimerDelayXms(5);\
                                                        bBACKLIGHTPOWER = _LIGHT_CONTROL_OFF;\
                                                    }\
                                                }

#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 480);\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_FE26_PORT86_PIN_REG) // _PIN_190,SPI_WP_CPU, P8.6

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_FE36_PORTA6_PIN_REG) // _PIN_209,EEPROM_WPn_CPU, PA.6

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (MCU_FE23_PORT83_PIN_REG) // _PIN_181,DDC_WPn_CPU, P8.3

#define _EDID_EEPROM_WP_ENABLE                  0
#define _EDID_EEPROM_WP_DISABLE                 1

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of HDMI External EDID Switch : #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//-----------------------------------------------
#define _HDMI_EDID_20                           1
#define _HDMI_EDID_14                           1
#define bHDMI_EDID_SELECT                       (MCU_FE2C_PORT94_PIN_REG) // _PIN_198,HDMI1_EDID_HDR_E2, P9.4

#define PCB_MULTI_EDID_SWITCH(port, index)      {\
                                                    switch((port))\
                                                    {\
                                                        case _D0_INPUT_PORT:\
                                                            break;\
                                                        case _D1_INPUT_PORT:\
                                                            break;\
                                                        case _D2_INPUT_PORT:\
                                                            break;\
                                                        case _D3_INPUT_PORT:\
                                                            if((index) == 0)\
                                                            {\
                                                                bHDMI_EDID_SELECT = _HDMI_EDID_14;\
                                                            }\
                                                            if((index) == 1)\
                                                            {\
                                                                bHDMI_EDID_SELECT = _HDMI_EDID_20;\
                                                            }\
                                                            break;\
                                                            break;\
                                                        case _D4_INPUT_PORT:\
                                                            break;\
                                                        case _D5_INPUT_PORT:\
                                                            break;\
                                                        default:\
                                                            break;\
                                                    }\
                                                }

#define PCB_MULTI_EDID_SWITCH_POWER_AC_ON()     {\
                                                    bHDMI_EDID_SELECT = _HDMI_EDID_14;\
                                                }

#define PCB_D3_EDID_SELECT(x)                   {\
                                                    bHDMI_EDID_SELECT = 1;\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD0_DP_PIN15_CONNECT                    (P1_7)  // _PIN_70,DP_SINK_CPU_P, P1.7
#define bD0_DP_PIN77_CONNECT                    (P3_4)  // _PIN_77, USBC_2LANE_DP_EVENT, P3.4
#define bD0_DP_PIN17_CONNECT                    (P1_5)  // _PIN_68,DP_SINK_CPU_N, P1.5

#define GET_TYPE_C_VIDEO()                      ((bit)bD0_DP_PIN77_CONNECT == _HIGH)
#define bD0_CONNECT                             (GET_TYPE_C_VIDEO() == _FALSE)
#define bD3_CONNECT                             (MCU_FE32_PORTA2_PIN_REG) // _PIN_204,HDMI1_DET_CPU, PA.2

#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D3_PIN()                            (bD3_CONNECT)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define bD0_HPD                                 (MCU_FE01_PORT41_PIN_REG) // _PIN_96,DP_HPD_CPU, P4.1
#define bD3_HPD                                 (P1_0)  // _PIN_1,HDMI1_HPD_CPU,P1.0

#define _D0_HOT_PLUG_HIGH                       1
#define _D0_HOT_PLUG_LOW                        0

#define _D1_HOT_PLUG_HIGH                       1
#define _D1_HOT_PLUG_LOW                        0

#define _D2_HOT_PLUG_HIGH                       1
#define _D2_HOT_PLUG_LOW                        0

#define _D3_HOT_PLUG_HIGH                       1
#define _D3_HOT_PLUG_LOW                        0

#define PCB_D0_HOTPLUG(x)                       {\
                                                    bD0_HPD = (x);\
                                                }

#define PCB_D3_HOTPLUG(x)                       {\
                                                    bD3_HPD = (x);\
                                                }

#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
#define PCB_D3_HOTPLUG_DETECT()                 (bD3_HPD)


///////////////
// PWM Macro //
///////////////
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

#define MCU_ADJUST_PWM_DUTY(x, y)               (MCU_ADJUST_8BIT_PWM_DUTY((x), (y)))
#define MCU_GET_PWM_DUTY(x)                     (MCU_GET_8BIT_PWM_DUTY(x))

#else

#define MCU_ADJUST_PWM_DUTY(x, y)               (MCU_ADJUST_12BIT_PWM_DUTY((x), (y)))
#define MCU_GET_PWM_DUTY(x)                     (MCU_GET_12BIT_PWM_DUTY(x))

#endif // End of #if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 480);\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (0x30));\
                                                    ScalerMcuPwmAdjustFrequency(_LED_PWM, 500);\
                                                }

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    ExternalDeviceInterfaceLedDriverBacklight(x);\
                                                }


//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define bSWIIC_D3_EEPROM_SCL                    (MCU_FE3B_PORTB3_PIN_REG)        // _PIN_214,HDMI1_SCL_CPU, PB.3
#define bSWIIC_D3_EEPROM_SDA                    (MCU_FE3C_PORTB4_PIN_REG)        // _PIN_215,HDMI1_SDA_CPU, PB.4



#define PCB_SW_IIC_SDA_SET()                    {\
                                                }

#define PCB_SW_IIC_SDA_CLR()                    {\
                                                }

#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                }

#define PCB_SW_IIC_SCL_SET()                    {\
                                                }

#define PCB_SW_IIC_SCL_CLR()                    {\
                                                }

#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                }


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED PWM GPIO
//--------------------------------------------------
#define bLED_PWM                                (MCU_FE24_PORT84_PIN_REG) // _PIN_184,GPIO_184_CPU_LED_WHITE, P8.4
#define _LED_PWM_GPIO_ON                        1
#define _LED_PWM_GPIO_OFF                       0

#define PCB_LED_PWM_TYPE_GPIO(x)                {\
                                                    bLED_PWM = (x);\
                                                }

#define PCB_GET_LED_PWM_TYPE_GPIO()             (bLED_PWM)

//--------------------------------------------------
// Macro of LED PinShare PWM Switch
//--------------------------------------------------
#define PCB_LED_PWM_SWITCH(x)                   {\
                                                    if((x) == _PCB_PWM_LED_SWITCH_GPIO)\
                                                    {\
                                                        ScalerSetByte(0x1034, _BIT0);\
                                                    }\
                                                    else if((x) == _PCB_PWM_LED_SWITCH_PWM)\
                                                    {\
                                                        ScalerSetByte(0x1034, (_BIT1 | _BIT0));\
                                                    }\
                                                }


///////////////////
//   LED PWM     //
///////////////////

//--------------------------------------------------
// Macro of LED PWM
//--------------------------------------------------
#define _PWM_LED_TIMER_COUNT                    30
#define _PWM_LED_ADJUST_TIME                    82

#define _LED_PWM                                _PWM0

#define _LED_PWM_MAX                            255
#define _LED_PWM_MIN                            0

#define PCB_LED_TYPE_PWM(x)                     {\
                                                    MCU_ADJUST_PWM_DUTY(_LED_PWM, (x));\
                                                }

#define PCB_GET_LED_PWM()                       (MCU_GET_PWM_DUTY(_LED_PWM))

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define bLED1                                   (MCU_FE24_PORT84_PIN_REG) // _PIN_184,GPIO_184_CPU_LED_WHITE, P8.4

#define _LED_ON                                 1
#define _LED_OFF                                0

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    bLED1 = _LED_OFF;\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                    PCB_LED_TYPE_PWM(_LED_PWM_MAX);\
                                                    ScalerSetByte(0x1034, _BIT0);\
                                                    bLED1 = _LED_ON;\
                                                    ScalerTimer0SetTimerCount(_TIMER_OFF);\
                                                }

#define PCB_LED_IDLE()                          {\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                    PCB_LED_TYPE_PWM(_LED_PWM_MAX);\
                                                    ScalerSetByte(0x1034, (_BIT1 | _BIT0));\
                                                }

#define PCB_LED_ON()                            {\
                                                    PCB_LED_TYPE_PWM(_LED_PWM_MAX);\
                                                    ScalerSetByte(0x1034, _BIT0);\
                                                    bLED1 = _LED_ON;\
                                                    ScalerTimer0SetTimerCount(_TIMER_OFF);\
                                                }

#define PCB_LED_OFF()                           {\
                                                    PCB_LED_TYPE_PWM(_LED_PWM_MIN);\
                                                    ScalerSetByte(0x1034, _BIT0);\
                                                    bLED1 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                }

#define PCB_LED_TYPE2()                         {\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY1                                 (MCU_FF09_ADC_A0_CONVERT_RESULT) // _PIN_94,GPIO_94_CPU_KEY1
#define AD_KEY2                                 (MCU_FF0A_ADC_A1_CONVERT_RESULT) // _PIN_95,GPIO_95_CPU_KEY2
#define bPOWER_KEY                              (P1_4)  // _PIN_67,GPIO_67_CPU_KEY_POWER, P1.4

#define PCB_ADKEY1()                            (AD_KEY1)
#define PCB_ADKEY2()                            (AD_KEY2)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                        if(bPOWER_KEY == 0)\
                                                        {\
                                                            (ucKeyState) |= _POWER_KEY_MASK;\
                                                        }\
                                                        if((0x90 <= (ucV2)) && ((ucV2) < 0xE0))\
                                                        {\
                                                            (ucKeyState) |= _MENU_KEY_MASK;\
                                                        }\
                                                        if((0x40 <= (ucV2)) && ((ucV2) < 0x90))\
                                                        {\
                                                            (ucKeyState) |= _EXIT_KEY_MASK;\
                                                        }\
                                                        if((0x70 <= (ucV1)) && ((ucV1) < 0x80))\
                                                        {\
                                                            (ucKeyState) |= _LEFT_KEY_MASK;\
                                                        }\
                                                        if((0x98 <= (ucV1)) && ((ucV1) < 0xB0))\
                                                        {\
                                                            (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                        }\
                                                }


/////////////////
// Audio Macro //
/////////////////

//-----------------------------------------------
// Macro of PCB Audio AMP Control
//-----------------------------------------------
#define bAMP_MUTE                               (MCU_FE2D_PORT95_PIN_REG) // _PIN_199,GPIO_199_CPU_MUTEN, P9.5

#define _AMP_MUTE_ON                            1 // Amp Mute on state
#define _AMP_MUTE_OFF                           0 // Amp Mute off state

#define PCB_AMP_MUTE(x)                         {\
                                                    bAMP_MUTE = (x);\
                                                }


///////////////////////
// Device Led Driver //
///////////////////////
#define bBACKLIGHTVCC                           (MCU_FE27_PORT87_PIN_REG) // _PIN_193,GPIO_193_CPU_BLVCC_EN, P8.7
#define bBACKLIGHTBL3D3V                        (MCU_FE02_PORT42_PIN_REG) // _PIN_97,GPIO_97_CPU_BL3D3V_EN, P4.2

#define _PCB_LED_DRIVER_POWER_OFF               0
#define _PCB_LED_DRIVER_POWER_ON                1

#define PCB_LED_DRIVER_POWER(x)                 {\
                                                    if(((x) == _PCB_LED_DRIVER_POWER_ON) && (PCB_GET_LED_DRIVER_POWER() == _PCB_LED_DRIVER_POWER_OFF))\
                                                    {\
                                                        /*need enable Vsync for SPI communication*/\
                                                        bBACKLIGHTBL3D3V = _ON;\
                                                        _nop_();\
                                                        _nop_();\
                                                        _nop_();\
                                                        _nop_();\
                                                        bBACKLIGHTVCC = _ON;\
                                                        /*bBACKLIGHTPOWER=_LIGHT_CONTROL_ON;*/\
                                                        ScalerTimerDelayXms(7);/*at less 6ms*/\
                                                        ExternalDeviceInterfaceLedDriverInitial();/*initial*/\
                                                    }\
                                                    else if(((x) == _PCB_LED_DRIVER_POWER_OFF) && (PCB_GET_LED_DRIVER_POWER() == _PCB_LED_DRIVER_POWER_ON))\
                                                    {\
                                                        bBACKLIGHTVCC = _OFF;\
                                                        ScalerTimerDelayXms(2);\
                                                        bBACKLIGHTBL3D3V = _OFF;\
                                                    }\
                                                }

#define PCB_GET_LED_DRIVER_POWER()              (bBACKLIGHTVCC & bBACKLIGHTBL3D3V)

#endif // End of #if(_PCB_TYPE == _RL6449_DEMO_LOCAL_DIMMING_1USB1H1TC)
