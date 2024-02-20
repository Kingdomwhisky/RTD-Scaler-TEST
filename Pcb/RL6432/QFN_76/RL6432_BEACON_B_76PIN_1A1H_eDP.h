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
// ID Code      : RL6432_QA_B_76PIN_1A1DP_eDP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6432_BEACON_B_76PIN_1A1H_eDP)


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
#define _PCB_DEBUG_DDC                          _DDC1


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#define _A0_INPUT_PORT_TYPE                     _A0_VGA_PORT
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                     _D1_HDMI_PORT//_D1_DP_PORT
#define _D1_DDC_CHANNEL_SEL                     _DDC1
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128//_EDID_SIZE_256
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH//_EDID_TABLE_LOCATION_USER
//#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
//#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
//#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE


#define  _D1_TMDS_BR_SWAP   _ON//_OFF//
#define  _D1_TMDS_PN_SWAP   _ON//_OFF//
/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _A0_INPUT_PORT


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_LANE_SWAP               _DISABLE
#define _PANEL_DPTX_1_1_LANE_PN_SWAP            _DISABLE
#define _PANEL_DPTX_1_1_SWING_LEVEL             _DP_SWING_800_MV
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_SPREAD_RANGE            0//5 //
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_12BIT//_PWM_8BIT

#define _BACKLIGHT_PWM                          _PWM4
#define _BACKLIGHT_PWM_INVERSE                  _PWM_INVERSE

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF//_ON
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _ON

#define _PWM0_PSAV_EN                           _OFF
#define _PWM1_PSAV_EN                           _OFF
#define _PWM2_PSAV_EN                           _OFF
#define _PWM3_PSAV_EN                           _OFF
#define _PWM4_PSAV_EN                           _OFF

#define _PWM0_PDOW_EN                           _OFF
#define _PWM1_PDOW_EN                           _OFF
#define _PWM2_PDOW_EN                           _OFF
#define _PWM3_PDOW_EN                           _OFF
#define _PWM4_PDOW_EN                           _OFF

#define _PWM0_RST_EN                            _OFF
#define _PWM1_RST_EN                            _OFF
#define _PWM2_RST_EN                            _OFF
#define _PWM3_RST_EN                            _OFF
#define _PWM4_RST_EN                            _OFF
#define _PWM_RST_SIGNAL_SEL                     _DVS


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                         _OFF
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _ON
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _HW_IIC_76PIN_76_1


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


/////////////////////
// Pinshare series //
/////////////////////
#include "RL6432_BEACON_B_76PIN_1A1H_eDP_PINSHARE.h"


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                }

#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                {\
                                                }

#define PCB_GPIO_SETTING_POWER_NORMAL()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_SAVING()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_DOWN()           {\
                                                }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
//#define bVCCKOFFPOWER                           (MCU_FE25_PORT85_PIN_REG) // 76PIN_PIN_72, P8.5
#define bVCCKOFFPOWER							(MCU_FE26_PORT86_PIN_REG) // 76PIN_PIN_73, P8.6

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
//#define bPANELPOWER                             (MCU_FE24_PORT84_PIN_REG) // 76PIN_PIN_71, P8.4
#define bPANELPOWER       (MCU_FE23_PORT83_PIN_REG) // 76PIN_PIN_67, P8.3

#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
//#define bBACKLIGHTPOWER                         (MCU_FE27_PORT87_PIN_REG) // 76PIN_PIN_74, P8.7
#define bBACKLIGHTPOWER                          (MCU_FE21_PORT81_PIN_REG) // 76PIN_PIN_69, P8.1

#define _LIGHT_CONTROL_ON                       1
#define _LIGHT_CONTROL_OFF                      0

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
													bControlPanel12V = (1);\
                                                    bBACKLIGHTPOWER = (x);\
                                                }

#if(_CUSTOMER == _CUS_MINDRAY)
#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, g_stUserDataInFlash.usPanelPwmFre);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }
#else
#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }
#endif

/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_FE19_PORT71_PIN_REG) // 76PIN_PIN_65, P7.1

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
//#define bEEPROM_WRITE_PROTECT                   (MCU_FE29_PORT91_PIN_REG) // 76PIN_PIN_75, P9.1
//This pin is be used to control 12v.
#define bControlPanel12V                   		(MCU_FE29_PORT91_PIN_REG) // 76PIN_PIN_75, P9.1
#define bEEPROM_WRITE_PROTECT                   (MCU_FE27_PORT87_PIN_REG) // 76PIN_PIN_74, P8.7

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
//#define bEDID_WRITE_PROTECT                     (MCU_FE22_PORT82_PIN_REG) // 76PIN_PIN_70, P8.2 
#define bEDID_WRITE_PROTECT                    (MCU_FE27_PORT87_PIN_REG) // 76PIN_PIN_74, P8.7
#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D1_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD1_DP_PIN15_CONNECT                    0//(MCU_FE26_PORT86_PIN_REG) // 76PIN_PIN_73, P8.6
#define bD1_DP_PIN16_CONNECT                    0/// (P1_4) // 76PIN_PIN_17, P1.4
#define bD1_DP_PIN17_CONNECT                    0//(MCU_FE22_PORT82_PIN_REG) // 76PIN_PIN_70, P8.2

#define bA0_CONNECT                             0///(P1_7)  // 76PIN_PIN_31, P1.7
#define bD1_CONNECT                             (((bit)bD1_DP_PIN15_CONNECT == _TRUE) && ((bit)bD1_DP_PIN16_CONNECT == _TRUE) && ((bit)bD1_DP_PIN17_CONNECT == _FALSE))

#define PCB_A0_PIN()                            (bA0_CONNECT)
#define PCB_D1_PIN()                            (bD1_CONNECT)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_DP_PIN17_CONNECT)


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
//#define bD1_HPD                                 (MCU_FE23_PORT83_PIN_REG) // 76PIN_PIN_67, P8.3
#define bD1_HPD                    (P1_4) // 76PIN_PIN_17, P1.4

#define _D1_HOT_PLUG_HIGH                       1
#define _D1_HOT_PLUG_LOW                        0

#define PCB_D1_HOTPLUG(x)                       {\
                                                    bD1_HPD = (x);\
                                                }

#define PCB_D1_HOTPLUG_DETECT()                 (bD1_HPD)


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#if(_CUSTOMER == _CUS_MINDRAY)
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, g_stUserDataInFlash.usPanelPwmFre);\
                                                }
#else
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
                                                }
#endif

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_8BIT_PWM_DUTY(_BACKLIGHT_PWM))

#elif(_PWM_DUT_RESOLUTION == _PWM_12BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))

#endif


//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define bSWIIC_SYS_EEPROM_SCL                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_SYS_EEPROM_SDA                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_A0_EEPROM_SCL                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_A0_EEPROM_SDA                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D0_EEPROM_SCL                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D0_EEPROM_SDA                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D1_EEPROM_SCL                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D1_EEPROM_SDA                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_USER_EEPROM_SCL                  (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_USER_EEPROM_SDA                  (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_USER_SENSOR_SCL                  (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_USER_SENSOR_SDA                  (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_SW_IIC_SDA_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_A0_EEPROM)\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D0_EEPROM)\
                                                    {\
                                                        bSWIIC_D0_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D1_EEPROM)\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_EEPROM)\
                                                    {\
                                                        bSWIIC_USER_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_SENSOR)\
                                                    {\
                                                        bSWIIC_USER_SENSOR_SDA = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_A0_EEPROM)\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D0_EEPROM)\
                                                    {\
                                                        bSWIIC_D0_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D1_EEPROM)\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_EEPROM)\
                                                    {\
                                                        bSWIIC_USER_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_SENSOR)\
                                                    {\
                                                        bSWIIC_USER_SENSOR_SDA = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_A0_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_A0_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D0_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_D0_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D1_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_D1_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_USER_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_SENSOR)\
                                                    {\
                                                        (x) = bSWIIC_USER_SENSOR_SDA;\
                                                    }\
                                                }

#define PCB_SW_IIC_SCL_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_A0_EEPROM)\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D0_EEPROM)\
                                                    {\
                                                        bSWIIC_D0_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D1_EEPROM)\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_EEPROM)\
                                                    {\
                                                        bSWIIC_USER_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_SENSOR)\
                                                    {\
                                                        bSWIIC_USER_SENSOR_SCL = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_A0_EEPROM)\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D0_EEPROM)\
                                                    {\
                                                        bSWIIC_D0_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D1_EEPROM)\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_EEPROM)\
                                                    {\
                                                        bSWIIC_USER_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_SENSOR)\
                                                    {\
                                                        bSWIIC_USER_SENSOR_SCL = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_A0_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_A0_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D0_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_D0_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D1_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_D1_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_USER_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_SENSOR)\
                                                    {\
                                                        (x) = bSWIIC_USER_SENSOR_SCL;\
                                                    }\
                                                }


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
//#define bLED1                                   (P1_7)  // 76PIN_PIN_31, P1.7   ///(MCU_FE20_PORT80_PIN_REG) // 76PIN_PIN_68, P8.0
#define bLED1                                   (MCU_FE25_PORT85_PIN_REG) // 76PIN_PIN_72, P8.5
//#define bLED2                                   (P1_3) // 76PIN_PIN_16, P1.3
#define bLED2                             (MCU_FE24_PORT84_PIN_REG) // 76PIN_PIN_71, P8.4

#define _LED_ON                                 0
#define _LED_OFF                                1

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                    bLED1 = _LED_ON;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_IDLE()                          {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_ON()                            {\
                                                    bLED1 = _LED_ON;\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_OFF()                           {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                    bLED1 = _LED_ON;\
                                                }

#define PCB_LED_TYPE2()                         {\
                                                    bLED2 = _LED_ON;\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }


//--------------------------------------------------
// Hard Id GPIO define
//--------------------------------------------------
#if(_GET_HARD_ID == _ON)
#define bHARD_ID0                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bHARD_ID1                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bHARD_ID2                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bHARD_ID3                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_HARD_ID0_DETECT()                  (bHARD_ID0)
#define PCB_HARD_ID1_DETECT()                  (bHARD_ID1)
#define PCB_HARD_ID2_DETECT()                  (bHARD_ID2)
#define PCB_HARD_ID3_DETECT()                  (bHARD_ID3)
#endif


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY1                                 (MCU_FF09_ADC_A0_CONVERT_RESULT) // 76PIN_PIN_39,A-ADC0
#define AD_KEY2                                 (MCU_FF0A_ADC_A1_CONVERT_RESULT) // 76PIN_PIN_38,A-ADC1

#define PCB_ADKEY1()                            (AD_KEY1)
#define PCB_ADKEY2()                            (AD_KEY2)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0xC0 <= (ucV2)) && ((ucV2) < 0xE0))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0x68 <= (ucV1)) && ((ucV1) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV1)) && ((ucV1) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\ 
                                                    if((0x68 <= (ucV2)) && ((ucV2) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV2)) && ((ucV2) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\
                                                }


#endif // End of #if(_PCB_TYPE == _RL6432_QA_B_76PIN_1A1DP_eDP)
