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
// ID Code      : RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6432_UNITED_A_216PIN_1A1DP1DUALDVI_DPTX_LVDS_eDP)


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
#define _PCB_DEBUG_DDC                          _VGA_DDC//_DDC2

//-------------------------------------------------
// Embedded Memory Size Option: Panel 2560x2048@50Hz Support Timing >1920x1080 1920x1200 2560x1440&1600@50Hz pixel to pixel
//-------------------------------------------------
#undef _EMBEDDED_MEMORY_SIZE_CONFIG
#define _EMBEDDED_MEMORY_SIZE_CONFIG            _4M_16BIT_DDR1_2PCS

///////////////////////
// Input Port Config //
///////////////////////
//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#define _A0_INPUT_PORT_TYPE                     _A0_VGA_PORT
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH//_EDID_TABLE_LOCATION_USER

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                     _D0_DP_PORT
#define _D0_DDC_CHANNEL_SEL                     _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH//_EDID_TABLE_LOCATION_USER
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_MINI
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                     _D1_NO_PORT//_D1_HDMI_PORT
#define _D1_DDC_CHANNEL_SEL                     _DDC1
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER
//#define _D1_MAX_HDMI_EDID_COUNT                 12
//#define _D1_FIRST_1_INDEX_EMBEDDED_EDID         _ON


//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_INPUT_PORT_TYPE                     _D2_DUAL_DVI_PORT
#define _D2_DDC_CHANNEL_SEL                     _DDC2
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256//_EDID_SIZE_NONE
#define _D2_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH//_EDID_TABLE_LOCATION_USER  //_EDID_TABLE_LOCATION_FLASH
//#define _D2_MAX_HDMI_EDID_COUNT                 12
//#define _D2_FIRST_1_INDEX_EMBEDDED_EDID         _ON

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                     _D3_NO_PORT
#define _D3_DDC_CHANNEL_SEL                     _DDC3
#define _D3_INPUT_PORT_SWITCH_FROM              _SWITCH_NONE
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D2_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D2_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _A0_INPUT_PORT


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#if 0   //Move to Pannel.h

#if(_LVDS_OUTPUT_PORT == _LVDS_2_PORT)
#define _LVDS_PORT_SEL                          _LVDS_2_PORT_CD
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE //_ENABLE
#elif(_LVDS_OUTPUT_PORT == _LVDS_4_PORT)

#if(_LVDS_CABLE_TYPE == _LVDS_CABLE_TYPE_0)
#define _LVDS_PORT_SEL                          _LVDS_4_PORT_ABCD
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#elif(_LVDS_CABLE_TYPE == _LVDS_CABLE_TYPE_1)
#define _LVDS_PORT_SEL                          _LVDS_4_PORT_ABCD
#define _LVDS_PORT_MIRROR                       _ENABLE
#define _LVDS_PORT_AB_SWAP                      _ENABLE
#define _LVDS_PORT_CD_SWAP                      _ENABLE
#define _LVDS_PN_SWAP                           _DISABLE
#endif

#endif
#endif  //#if 0

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#if(_LVDS_DRIVING_CONFIG_DEFINE_IN_USER_PROJECT == _OFF)
#define _LVDS_DRIV_CONTROL                      _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL               _DISABLE
#endif

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#if(_LVDS_SSC_CONFIG_DEFINE_IN_USER_PROJECT == _OFF)
#define _LVDS_SPREAD_RANGE                      10
#define _LVDS_SPREAD_SPEED                      _SPEED_33K
#endif


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
#define _PANEL_DPTX_1_1_SPREAD_RANGE            5
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_12BIT//_PWM_8BIT //_PWM_12BIT

#define _BACKLIGHT_PWM                          _PWM5
//#ifndef _BACKLIGHT_PWM_INVERSE
#define _BACKLIGHT_PWM_INVERSE                  _ON
//#endif

#define _BACKGROUND_LIGHT_PWM                   _PWM2 // Background light  100Hz~20KHz
#define _BUZZER_BEEP_PWM                        _PWM4 // Buzzer Beep       2000Hz

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _ON
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _ON
#define _PWM5_EN                                _ON

#define _PWM0_PSAV_EN                           _OFF
#define _PWM1_PSAV_EN                           _OFF
#define _PWM2_PSAV_EN                           _ON
#define _PWM3_PSAV_EN                           _OFF
#define _PWM4_PSAV_EN                           _ON
#define _PWM5_PSAV_EN                           _OFF

#define _PWM0_PDOW_EN                           _OFF
#define _PWM1_PDOW_EN                           _OFF
#define _PWM2_PDOW_EN                           _OFF
#define _PWM3_PDOW_EN                           _OFF
#define _PWM4_PDOW_EN                           _ON
#define _PWM5_PDOW_EN                           _OFF

#define _PWM0_RST_EN                            _OFF
#define _PWM1_RST_EN                            _OFF
#define _PWM2_RST_EN                            _OFF
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
#define _SW_IIC_SUPPORT                         _ON//_OFF
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _OFF//_ON
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24WC64
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _NO_IIC_PIN//((_HW_IIC_SUPPORT == _ON) ? (_HW_IIC_PIN_210_211) : _SW_IIC_PIN_GPIO)

//--------------------------------------------------
// External Device Sofware or Hardware IIC Bus Option[!!! Old HW BK Sensor use PIN_198_199]
//--------------------------------------------------
#define _PCB_SYS_EXTDEV_IIC0                    ((_HW_IIC_SUPPORT == _ON) ? (_HW_IIC_PIN_179_180) : _SW_IIC_PIN_GPIO)
#define _PCB_SYS_EXTDEV_IIC1                    ((_HW_IIC_SUPPORT == _ON) ? (_HW_IIC_PIN_198_199) : _SW_IIC_PIN_GPIO)

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
#include "RL6432_UNITED_A_216PIN_1A1DP1DUALDVI_DPTX_LVDS_eDP_PINSHARE.h"


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                    PCB_SET_LVDS_DPTX_SWITCH(_DPTX_PANEL_OUTPUT);\
                                                    PCB_BACKGROUND_LIGHT_EN(_OFF);\
                                                    PCB_USBHUB_POWER(_ON);\
                                                }
#elif(_PANEL_STYLE == _PANEL_LVDS)
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                    PCB_SET_LVDS_DPTX_SWITCH(_LVDS_PANEL_OUTPUT);\
                                                    PCB_BACKGROUND_LIGHT_EN(_OFF);\
                                                    PCB_USBHUB_POWER(_ON);\
                                                }
#endif

#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                {\
                                                }

#define PCB_GPIO_SETTING_POWER_NORMAL()         {\
                                                    PCB_USBHUB_POWER(_ON);\
                                                }

#define PCB_GPIO_SETTING_POWER_SAVING()         {\
                                                    PCB_USBHUB_POWER(_OFF);\
                                                }

#define PCB_GPIO_SETTING_POWER_DOWN()           {\
                                                    PCB_USBHUB_POWER(_OFF);\
                                                }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#define bVCCKOFFPOWER                           (MCU_FE27_PORT87_PIN_REG) // Pin_205, P8.7

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of DDR_PW_EN Power Control
//-----------------------------------------------
#define bDDRPWPOWER                             (MCU_FE1F_PORT77_PIN_REG) // Pin_197, P7.7

#define _DDR_PW_POWER_ON                        1
#define _DDR_PW_POWER_OFF                       0

#define PCB_DDR_PW_EN(x)                        {\
                                                    bDDRPWPOWER = (x);\
                                                }


#if 0
//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#define bREGULATOR_5V                           (MCU_FE16_PORT66_PIN_REG) // Pin_179, P6.6

#define _REGULATOR_5V_ON                        0
#define _REGULATOR_5V_OFF                       1

#define PCB_REGULATOR_5V_OUT(x)                 {\
                                                    bREGULATOR_5V = (x);\
                                                }
#endif

#if 1
//---------------------------------------------------------------------
// when the state is power-saving,power-off,need powerboard down,else need powerboard on
//-----------------------------------------------------------------------
//-----------------------------------------------
// Macro of PCB contrl the Power board 
//-----------------------------------------------
#define bPOWERBOARDPOWER                        (MCU_FE1D_PORT75_PIN_REG) // Pin_195, P7.5
#define _PCB_POWERBOARD_ON                      1  // POWER BOARD CONTROL ON STATE
#define _PCB_POWERBOARD_OFF                     0  // POWER BOARD CONTROL OFF STATE


#define PCB_POWERBOARD_CONTROL(x)               {\
                                                    bPOWERBOARDPOWER = x;\
                                                }

#define PCB_POWERBOARD_LOWPOWER(x)              {\
                                                    if(x==_LOW_POWER_ON)\
                                                    {\
                                                        ScalerTimerDelayXms(200);\
                                                        PCB_POWERBOARD_CONTROL(_PCB_POWERBOARD_OFF);\
                                                    }\
                                                    else\
                                                    {\
                                                        PCB_POWERBOARD_CONTROL(_PCB_POWERBOARD_ON);\
                                                        ScalerTimerDelayXms(200);\
                                                    }\
                                                }
#endif

//--------------------------------------------------
// Macro of USB HUB Power EN[H: On  L: Off]
//--------------------------------------------------
#define bUSBHUBPOWER                            (P3_6) // Pin_93, P3.6
#define PCB_USBHUB_POWER(x)                     {\
                                                    bUSBHUBPOWER = x;\
                                                }
//--------------------------------------------------
// Macro of USB HUB CHOOSE[H: DP2  L: DP1]
//--------------------------------------------------
#define bUSBHUBCHOOSE                           (MCU_FE0E_PORT56_PIN_REG) // Pin_166, P5.6
#define PCB_USBHUB_CHN_SEL(x)                   {\
                                                    bUSBHUBCHOOSE = x;\
                                                }
#define PCB_USBHUB_CHN_SEL_DETECT()             (bUSBHUBCHOOSE)

//--------------------------------------------------
// Macro of Background Light Control[H: On  L: Off]
//--------------------------------------------------
#define bBACKGROUND_LIGHT_EN                    (P3_7) // Pin_94, P3.7
#define PCB_BACKGROUND_LIGHT_EN(x)              {\
                                                    bBACKGROUND_LIGHT_EN = x;\
                                                }
#define PCB_BACKGROUND_LIGHT_EN_DETECT()        (bBACKGROUND_LIGHT_EN)

///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define bPANELPOWER                             (MCU_FE12_PORT62_PIN_REG) // Pin_170, P6.2

#define _PANEL_CONTROL_ON                       0   // Old HW is 1
#define _PANEL_CONTROL_OFF                      1

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define bBACKLIGHTPOWER                         (MCU_FE14_PORT64_PIN_REG) // Pin_172, P6.4

#define _LIGHT_CONTROL_ON                       0
#define _LIGHT_CONTROL_OFF                      1

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    bBACKLIGHTPOWER = (x);\
                                                }

#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, _PWM_FREQ);\                                                        
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
#define bFLASH_WRITE_PROTECT                    (MCU_FE19_PORT71_PIN_REG) // Pin_189, P7.1

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_FE26_PORT86_PIN_REG) // Pin_204, P8.6 // (MCU_FE29_PORT91_PIN_REG) // Pin_209, P9.1

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (MCU_FE1C_PORT74_PIN_REG) // Pin_194, P7.4 // (MCU_FE21_PORT81_PIN_REG) // Pin_199, P8.1

#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D1_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D2_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }
#define PCB_EDID_EEPROM_WRITE_PROTECT_DETECT()  (bEDID_WRITE_PROTECT)

//-----------------------------------------------
// Macro of HDMI External EDID Switch : #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//-----------------------------------------------
#define bD1_EXT_SWITCH_EDID_0                   (MCU_FE30_PORTA0_PIN_REG) // PIN_216, PA.0
#define _EEPROM_EDID_ENABLE                     0
#define _EEPROM_EDID_DISABLE                    1

// 0(default) Horizontal->U17  1 Vertical->U16
#define PCB_MULTI_EDID_ALL_SWITCH_OFF(port)     {\
                                                    switch((port))\
                                                    {\
                                                        case _D0_INPUT_PORT:\
                                                            break;\
                                                        case _D1_INPUT_PORT:\
                                                        case _D2_INPUT_PORT:\
                                                            bD1_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                            break;\
                                                        case _D3_INPUT_PORT:\
                                                            break;\
                                                        default:\
                                                            break;\
                                                        DebugMessageSystem("SWITCH_OFF:", port);\
                                                    }\
                                                }

#define PCB_MULTI_EDID_SWITCH(port, index)      {\
                                                    switch((port))\
                                                    {\
                                                        case _D0_INPUT_PORT:\
                                                            break;\
                                                        case _D1_INPUT_PORT:\
                                                        case _D2_INPUT_PORT:\
                                                            if((index) == 0)\
                                                            {\
                                                                bD1_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                            }\
                                                            else if((index) == 1)\
                                                            {\
                                                                bD1_EXT_SWITCH_EDID_0 = _EEPROM_EDID_DISABLE;\
                                                            }\
                                                            else\
                                                            {\
                                                                bD1_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                            }\
                                                            break;\
                                                        case _D3_INPUT_PORT:\
                                                            break;\
                                                        default:\
                                                            break;\
                                                        DebugMessageSystem("EDID_SWITCH:", port);\
                                                    }\
                                                }

#define PCB_MULTI_EDID_SWITCH_POWER_AC_ON()     {\
                                                    bD1_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                    DebugMessageSystem("EDID_AC_ON:", 0);\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD0_DP_PIN15_CONNECT                    (MCU_FE25_PORT85_PIN_REG)  // Pin_203, P8.5
#define bD0_DP_PIN16_CONNECT                    (P1_3)                  // Pin_53, P1.3
#define bD0_DP_PIN17_CONNECT                    (MCU_FE24_PORT84_PIN_REG)  // Pin_202, P8.4
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)

#define bA0_CONNECT                             (P1_7)  // Pin_68, P1.7
#define bD0_CONNECT                             (((bit)bD0_DP_PIN15_CONNECT == _TRUE) && ((bit)bD0_DP_PIN16_CONNECT == _TRUE) && ((bit)bD0_DP_PIN17_CONNECT == _FALSE))
#define bD1_CONNECT                             (P1_4)                 // Pin_54, P1.4 // (MCU_FE30_PORTA0_PIN_REG) // PIN_216, PA.0
#define bD2_CONNECT                             (P1_0)                 // Pin_1, P1.0

#define PCB_A0_PIN()                            (bA0_CONNECT)
#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D1_PIN()                            (bD1_CONNECT)
#define PCB_D2_PIN()                            (bD2_CONNECT)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)

#if 0
//-----------------------------------------------
// Macro of MHL Cable Connect
//-----------------------------------------------
#define bD1_MHL_CONNECT                         (P3_7) // Pin_94, P3.7

#define PCB_D1_MHL_DETECT()                     (bD1_MHL_CONNECT)
#endif

////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define bD0_HPD                                 (MCU_FE29_PORT91_PIN_REG) // Pin_209, P9.1  // (MCU_FE22_PORT82_PIN_REG) // Pin_201, P8.2
#define bD1_HPD                                 (P1_2) // Pin_15, P1.2
#define bD2_HPD                                 (P1_1) // Pin_3, P1.1

#define _D0_HOT_PLUG_HIGH                       1
#define _D0_HOT_PLUG_LOW                        0

#define _D1_HOT_PLUG_HIGH                       1
#define _D1_HOT_PLUG_LOW                        0

#define _D2_HOT_PLUG_HIGH                       1
#define _D2_HOT_PLUG_LOW                        0

#define PCB_D0_HOTPLUG(x)                       {\
                                                    bD0_HPD = (x);\
                                                }

#define PCB_D1_HOTPLUG(x)                       {\
                                                    bD1_HPD = (x);\
                                                }

#define PCB_D2_HOTPLUG(x)                       {\
                                                    bD2_HPD = (x);\
                                                }

#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
#define PCB_D1_HOTPLUG_DETECT()                 (bD1_HPD)
#define PCB_D2_HOTPLUG_DETECT()                 (bD2_HPD)

#if 0
///////////////
// MHL Macro //
///////////////

//-----------------------------------------------
// Macro of HDMI/MHL Switch
//-----------------------------------------------
#define bD1_TMDS_SWITCH                         (MCU_FE1C_PORT74_PIN_REG) // Pin_194, P7.4

#define _TMDS_SWITCH_MHL_CBUS                   0
#define _TMDS_SWITCH_HDMI_HPD                   1

#define PCB_D1_HDMI_MHL_SWITCH(x)               {\
                                                    bD1_TMDS_SWITCH = (x);\
                                                }

//-----------------------------------------------
// Macro of MHL VBus Switch
//-----------------------------------------------
#define bD1_MHL_VBUS_SWITCH                     (MCU_FE1A_PORT72_PIN_REG) // Pin_192, P7.2

#define _MHL_VBUS_ON                            1
#define _MHL_VBUS_OFF                           0

#define PCB_D1_MHL_VBUS_SWITCH(x)               {\
                                                    bD1_MHL_VBUS_SWITCH = (x);\
                                                }

#define PCB_GET_D1_MHL_VBUS_SWITCH()            (bD1_MHL_VBUS_SWITCH)
#endif

///////////////////
// Display Macro //
///////////////////

//--------------------------------------------------
// Macro of LVDS eDP Panel Switch Control
//--------------------------------------------------
#define bLVDSDPTXSWICH                          (MCU_FE0F_PORT57_PIN_REG) // Pin_167, P5.7  // (MCU_FE1D_PORT75_PIN_REG) // Pin_195, P7.5

#define _LVDS_PANEL_OUTPUT                      0
#define _DPTX_PANEL_OUTPUT                      1

#define PCB_SET_LVDS_DPTX_SWITCH(x)             {\
                                                    bLVDSDPTXSWICH = (x);\
                                                }


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, _PWM_FREQ);\                                                    
                                                }

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


#define PCB_BACKGROUND_LIGHT_PWM(x)             {\
                                                    MCU_ADJUST_12BIT_PWM_DUTY(_BACKGROUND_LIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKGROUND_LIGHT_PWM()          (MCU_GET_12BIT_PWM_DUTY(_BACKGROUND_LIGHT_PWM))


#define PCB_BUZZER_BEEP_PWM(x)                  {\
                                                    MCU_ADJUST_12BIT_PWM_DUTY(_BUZZER_BEEP_PWM, (x));\
                                                }
#endif


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define bLED1                                   (MCU_FE47_PORTC7_PIN_REG) // Pin_97, PC.7
#define bLED2                                   (MCU_FE48_PORTD0_PIN_REG) // Pin_98, PD.0

#define _LED_ON                                 0// 1
#define _LED_OFF                                1//0

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    bLED1 = _LED_OFF;\
                                                    bLED2 = _LED_OFF;\
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
                                                    bLED1 = _LED_OFF;\
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

#define PCB_LED_TYPE3()                         {\
                                                }

#define PCB_LED_TYPE4()                         {\
                                                }

#define PCB_LED_TYPE5()                         {\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY1                                 (MCU_FF09_ADC_A0_CONVERT_RESULT) // Pin_91
#define AD_KEY2                                 (MCU_FF0A_ADC_A1_CONVERT_RESULT) // Pin_92

#define PCB_ADKEY1()                            (AD_KEY1)
#define PCB_ADKEY2()                            (AD_KEY2)

#if (_USER_KEYPAD_TYPE == _KEYPAD_TYPE_2M) // 2M 
// Key TP2->5(OLD): V1=0xA8 V1=0xA0 V1=0x50 V1=0x78
// Key TP2->5(NEW): V1=0xA8 V2=0xA8 V1=0x50 V2=0x80
// Key TP2->5(NEW): V1=0xA8 V2=0xA8 V1=0x50 V2=0x80; PWOFF:V2=0x28
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((ucV1) < 0x5F)\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0xA0 <= (ucV1)) && ((ucV1) < 0xC8))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if((0x20 <= (ucV2)) && ((ucV2) < 0x3F))\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\                                                             
                                                    if((0x68 <= (ucV2)) && ((ucV2) < 0x8F))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\
                                                    if((0x90 <= (ucV2)) && ((ucV2) < 0xB7))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\                                                                                                        
                                                }
#else //(_KEYPAD_TYPE == _KEYPAD_TYPE_3_5M) // 3_5M 
// Key TP2->7: V1=0x28 V2=0x28 V1=0x00 V2=0x00  V2=0x58 V1=0x48
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((ucV2) < 0x14)\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0x14 <= (ucV2)) && ((ucV2) < 0x40))\
                                                    {\
                                                        (ucKeyState) |= _OK_KEY_MASK;\
                                                    }\
                                                    if((0x40 <= (ucV2)) && ((ucV2) < 0x80))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if((ucV1) < 0x14)\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x14 <= (ucV1)) && ((ucV1) < 0x38))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\
                                                    if((0x38 <= (ucV1)) && ((ucV1) < 0x80))\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\
                                                }
#endif
//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define bSWIIC_SYS_EEPROM_SCL                   (MCU_FE2A_PORT92_PIN_REG) // _PIN_210, P9.2
#define bSWIIC_SYS_EEPROM_SDA                   (MCU_FE2B_PORT93_PIN_REG) // _PIN_211, P9.3

//_IIC_SYS_BUS_I2C0: Backlight Sensor[!!!HW BK Sensor use PIN_198_199]
#define bSWIIC_SYS_BUS_I2C0_SCL                 (MCU_FE20_PORT80_PIN_REG)  // _PIN_198 P8.0
#define bSWIIC_SYS_BUS_I2C0_SDA                 (MCU_FE21_PORT81_PIN_REG)  // _PIN_199 P8.1

//_IIC_SYS_BUS_I2C1: Other Sensor
#define bSWIIC_SYS_BUS_I2C1_SCL                 (MCU_FE16_PORT66_PIN_REG)  // _PIN_179 P6.6
#define bSWIIC_SYS_BUS_I2C1_SDA                 (MCU_FE17_PORT67_PIN_REG)  // _PIN_180 P6.7

#define PCB_SW_IIC_SDA_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SDA = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SDA = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C0_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C1_SDA;\
                                                    }\
                                                }

#define PCB_SW_IIC_SCL_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SCL = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C0_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        bSWIIC_SYS_BUS_I2C1_SCL = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C0)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C0_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_SYS_BUS_EXTDEV_I2C1)\
                                                    {\
                                                        x = bSWIIC_SYS_BUS_I2C1_SCL;\
                                                    }\
                                                }

#endif // End of #if(_PCB_TYPE == _RL6432_BEACON_A_216PIN_1DP1HDMI1DUALDVI_DPTX_LVDS_eDP)
