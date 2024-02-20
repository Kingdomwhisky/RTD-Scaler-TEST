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
// ID Code      : RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP)


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
#if((INPUT_LIST_SELECT == INPUT_LIST_ONLY_D1) || (INPUT_LIST_SELECT == INPUT_LIST_A0_D1))
#define _PCB_DEBUG_DDC                          _DDC1
#else
#define _PCB_DEBUG_DDC                          _DDC3
#endif

///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#if((INPUT_LIST_SELECT == INPUT_LIST_DEFAULT) || \
    (INPUT_LIST_SELECT == INPUT_LIST_A0_D1) || \
    (INPUT_LIST_SELECT == INPUT_LIST_A0_D3))
#define _A0_INPUT_PORT_TYPE                     _A0_VGA_PORT
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#else
#define _A0_INPUT_PORT_TYPE                     _A0_NO_PORT
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_128
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#endif
//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#if((INPUT_LIST_SELECT == INPUT_LIST_DEFAULT) || \
    (INPUT_LIST_SELECT == INPUT_LIST_D0_D3))
#define _D0_INPUT_PORT_TYPE                     _D0_DP_PORT
#define _D0_DDC_CHANNEL_SEL                     _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#else
#define _D0_INPUT_PORT_TYPE                     _D0_NO_PORT
#define _D0_DDC_CHANNEL_SEL                     _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#endif
//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#if((INPUT_LIST_SELECT == INPUT_LIST_DEFAULT) || \
    (INPUT_LIST_SELECT == INPUT_LIST_ONLY_D1) || \
    (INPUT_LIST_SELECT == INPUT_LIST_A0_D1) || \
    (INPUT_LIST_SELECT == INPUT_LIST_D1_D3))
#if(D1_IS_HDMI == _ON)
#define _D1_INPUT_PORT_TYPE                     _D1_HDMI_PORT
#else
#define _D1_INPUT_PORT_TYPE                     _D1_DP_PORT
#endif
#define _D1_DDC_CHANNEL_SEL                     _DDC1
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#else
#define _D1_INPUT_PORT_TYPE                     _D1_NO_PORT//_D1_DP_PORT
#define _D1_DDC_CHANNEL_SEL                     _DDC1
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#endif
//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#if((INPUT_LIST_SELECT == INPUT_LIST_DEFAULT) || \
    (INPUT_LIST_SELECT == INPUT_LIST_ONLY_D3) || \
    (INPUT_LIST_SELECT == INPUT_LIST_A0_D3) || \
    (INPUT_LIST_SELECT == INPUT_LIST_D1_D3) || \
    (INPUT_LIST_SELECT == INPUT_LIST_D0_D3))
#define _D3_INPUT_PORT_TYPE                     _D3_HDMI_PORT
#define _D3_DDC_CHANNEL_SEL                     _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#else
#define _D3_INPUT_PORT_TYPE                     _D3_NO_PORT
#define _D3_DDC_CHANNEL_SEL                     _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_FLASH
#endif


#if((_GAMMA_IN_FLASH_BANK == _ON) && (BEACON_GAMMA_TYPE == Gamma_7x2CT_2Bank))
//--------------------------------------------------
// 
//--------------------------------------------------
#define _D5_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D5_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_256
#endif

/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#if(INPUT_LIST_SELECT == INPUT_LIST_ONLY_D3)
#define _INPUT_PORT_SEARCH_PRI_0                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D0_INPUT_PORT
#elif(INPUT_LIST_SELECT == INPUT_LIST_ONLY_D1)
#define _INPUT_PORT_SEARCH_PRI_0                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D0_INPUT_PORT
#elif(INPUT_LIST_SELECT == INPUT_LIST_A0_D3)
#define _INPUT_PORT_SEARCH_PRI_0                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D0_INPUT_PORT
#elif(INPUT_LIST_SELECT == INPUT_LIST_A0_D1)
#define _INPUT_PORT_SEARCH_PRI_0                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D0_INPUT_PORT
#elif(INPUT_LIST_SELECT == INPUT_LIST_D1_D3)
#define _INPUT_PORT_SEARCH_PRI_0                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D0_INPUT_PORT
#elif(INPUT_LIST_SELECT == INPUT_LIST_D0_D3)
#define _INPUT_PORT_SEARCH_PRI_0                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D1_INPUT_PORT
#else
#define _INPUT_PORT_SEARCH_PRI_0                _A0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D3_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D0_INPUT_PORT
#endif

//--------------------------------------------------
// TMDS Signal Swap Select
//--------------------------------------------------
#if(_USER_PCB_BOARD_TYPE == _JN_CL15XX_PCB_BOARD)
#define _D1_TMDS_BR_SWAP                        _ON //      _ON//   
#define _D1_TMDS_PN_SWAP                        _OFF //      _ON// 
#else
#define _D1_TMDS_BR_SWAP                        _OFF //      _ON//   
#define _D1_TMDS_PN_SWAP                        _OFF //      _ON// 
#endif

#define _D3_TMDS_BR_SWAP                        _ON//   _OFF
#define _D3_TMDS_PN_SWAP                        _ON//    _OFF

////////////////////
// For LVDS Panel //
////////////////////

#if 0   // move to xxxx_panel.h
//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#if(_LVDS_OUTPUT_PORT == _LVDS_2_PORT)
#define _LVDS_PORT_SEL                          _LVDS_2_PORT_CD
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _ENABLE
#elif(_LVDS_OUTPUT_PORT == _LVDS_4_PORT)

#if(_LVDS_CABLE_TYPE == _LVDS_CABLE_TYPE_0)
#define _LVDS_PORT_SEL                          _LVDS_4_PORT_ABCD
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _ENABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#elif(_LVDS_CABLE_TYPE == _LVDS_CABLE_TYPE_1)
#define _LVDS_PORT_SEL                          _LVDS_4_PORT_ABCD
#define _LVDS_PORT_MIRROR                       _ENABLE
#define _LVDS_PORT_AB_SWAP                      _ENABLE
#define _LVDS_PORT_CD_SWAP                      _ENABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#endif

#elif(_LVDS_OUTPUT_PORT == _LVDS_1_PORT)
#define _LVDS_PORT_SEL                          _LVDS_1_PORT_C
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _ENABLE

#endif

#endif

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
#define _PANEL_DPTX_1_1_SPREAD_RANGE            0//5
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#if((_BACKLIGHT_SENSOR==_ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
#define _PWM_DUT_RESOLUTION                     _PWM_12BIT
#else
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT
#endif

#define _BACKLIGHT_PWM                          _PWM5
#define _BACKLIGHT_PWM_INVERSE                  _PWM_INVERSE

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _ON

#define _PWM0_PSAV_EN                           _OFF
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
#define _EEPROM_TYPE                            _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _NO_IIC_PIN//_HW_IIC_156PIN_77_78


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
#if(_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2)
#include "RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP_PINSHARE_FOR_BX.h"
#else
#include "RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP_PINSHARE.h"
#endif

//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                    PCB_SET_LVDS_DPTX_SWITCH(_DPTX_PANEL_OUTPUT);\
                                                }
#elif(_PANEL_STYLE == _PANEL_LVDS)
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                    PCB_SET_LVDS_DPTX_SWITCH(_LVDS_PANEL_OUTPUT);\
                                                }
#endif

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
#define bVCCKOFFPOWER                           (MCU_FE20_PORT80_PIN_REG) // 156PIN_PIN_67, P8.0

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
#define bPANELPOWER                             (MCU_FE1A_PORT72_PIN_REG) // 156PIN_PIN_63, P7.2

#if(_CUSTOMER ==_CUS_MINDRAY)
#if((_USER_PCB_BOARD_TYPE == _MR_CL13XX_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _KL_CL13XX_PCB_BOARD))
#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1
#else
#define _PANEL_CONTROL_ON                       1
#define _PANEL_CONTROL_OFF                      0
#endif
#else
#if(_PANEL_POWER_CONTROL_INVERSE == _ON)
#define _PANEL_CONTROL_ON                       1
#define _PANEL_CONTROL_OFF                      0
#else
#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1
#endif
#endif

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#if((_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2))
#define bBACKLIGHT_12V_ONOFF                    (MCU_FE0A_PORT52_PIN_REG) // 156PIN_PIN_52, P5.2
#define PCB_BACKLIGHT_12V_ONOFF_PIN(x)          {\
                                                    bBACKLIGHT_12V_ONOFF = (x);\
                                                }
#endif

#if((_USER_PCB_BOARD_TYPE == _MR_CL13XX_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _KL_CL13XX_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _JN_CL15XX_PCB_BOARD))
#define bBACKLIGHTPOWER                         (MCU_FE1D_PORT75_PIN_REG) // 156PIN_PIN_65, P7.5
#else
#define bBACKLIGHTPOWER                         (MCU_FE1C_PORT74_PIN_REG) // 156PIN_PIN_64, P7.4
#endif

#if((_USER_PCB_BOARD_TYPE == _MR_CL13XX_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _KL_CL13XX_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _JN_CL15XX_PCB_BOARD))
#define _LIGHT_CONTROL_ON                       1
#define _LIGHT_CONTROL_OFF                      0
#else
#define _LIGHT_CONTROL_ON                       0
#define _LIGHT_CONTROL_OFF                      1
#endif

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
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
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, _PWM_FREQ);\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }
#endif

#if(_KL_5V_12V_GPIO_CONTROL == _ON)
#define bPANEL_12V_PCTR                         (MCU_FE25_PORT85_PIN_REG) // 156PIN_PIN_72, P8.5
#define bPANEL_5V_PCTR                          (MCU_FE24_PORT84_PIN_REG) // 156PIN_PIN_71, P8.4

#define _PANEL_5V_PCTR_HIGH                     1
#define _PANEL_5V_PCTR_LOW                      0
#define _PANEL_12V_PCTR_HIGH                    1
#define _PANEL_12V_PCTR_LOW                     0

#define PCB_PANEL_5V_PCTR(x)                    {\
                                                    bPANEL_5V_PCTR = (x);\
                                                }
#define PCB_PANEL_12V_PCTR(x)                   {\
                                                    bPANEL_12V_PCTR = (x);\
                                                }


#define PCB_PANEL_5V_PCTR_DETECT()              (bPANEL_5V_PCTR)
#define PCB_PANEL_12V_PCTR_DETECT()             (bPANEL_12V_PCTR)
#endif

/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_FE19_PORT71_PIN_REG) // 156PIN_PIN_61, P7.1

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#if(_USER_PCB_BOARD_TYPE == _LY_CL2308_PCB_BOARD)
#define bEEPROM_WRITE_PROTECT                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS) // 156PIN_PIN_76, P9.1
#else
#define bEEPROM_WRITE_PROTECT                   (MCU_FE29_PORT91_PIN_REG) // 156PIN_PIN_76, P9.1
#endif

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)


#if(_DDC_DETECT_EN == _ON)
#if(_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2)
#define bDDC_DETECT_GPIO                        (MCU_FE25_PORT85_PIN_REG) // 156PIN_PIN_72, P8.5
#else
#define bDDC_DETECT_GPIO                        (MCU_FE29_PORT91_PIN_REG) // 156PIN_PIN_76, P9.1
#endif

#define PCB_DDC_USE_GPIO_DETECT()               (bDDC_DETECT_GPIO)
#endif

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (MCU_FE21_PORT81_PIN_REG) // 156PIN_PIN_68, P8.1

#define _EDID_EEPROM_WP_ENABLE                  0
#define _EDID_EEPROM_WP_DISABLE                 1

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
#if(_KL_5V_12V_GPIO_CONTROL == _ON)
#define bD0_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS) // 156PIN_PIN_72, P8.5
#define bD0_DP_PIN16_CONNECT                    (P1_3) // 156PIN_PIN_118, P1.3
#define bD0_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS) // 156PIN_PIN_71, P8.4
#elif(_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2)
#define bD0_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE25_PORT85_PIN_REG) // 156PIN_PIN_72, P8.5
#define bD0_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(P1_3) // 156PIN_PIN_118, P1.3
#define bD0_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE24_PORT84_PIN_REG) // 156PIN_PIN_71, P8.4
#else
#define bD0_DP_PIN15_CONNECT                    (MCU_FE25_PORT85_PIN_REG) // 156PIN_PIN_72, P8.5
#define bD0_DP_PIN16_CONNECT                    (P1_3) // 156PIN_PIN_118, P1.3
#define bD0_DP_PIN17_CONNECT                    (MCU_FE24_PORT84_PIN_REG) // 156PIN_PIN_71, P8.4
#endif

#if(_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2)
#define bD1_DP_PIN15_CONNECT                    (MCU_FE22_PORT82_PIN_REG)//156PIN_PIN_70, P8.2
#define bD1_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(P1_4) // 156PIN_PIN_119, P1.4
#define bD1_DP_PIN17_CONNECT                    (MCU_FE24_PORT84_PIN_REG) // 156PIN_PIN_71, P8.4
#else
#define bD1_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE27_PORT87_PIN_REG) // 156PIN_PIN_74, P8.7
#define bD1_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(P1_4) // 156PIN_PIN_119, P1.4
#define bD1_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE26_PORT86_PIN_REG) // 156PIN_PIN_73, P8.6
#endif

#define bA0_CONNECT                             (P1_7)  // 156PIN_PIN_133, P1.7
#if(_USER_PCB_BOARD_TYPE == _RTD2556_DEMO_PCB_BOARD)
#define bD0_CONNECT                             (P1_3)  // 156PIN_PIN_118, P1.3 
#else
#define bD0_CONNECT                             (((bit)bD0_DP_PIN15_CONNECT == _TRUE) && ((bit)bD0_DP_PIN16_CONNECT == _TRUE) && ((bit)bD0_DP_PIN17_CONNECT == _FALSE))
#endif

#if(_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2)
#define bD1_CONNECT                             (((bit)bD1_DP_PIN15_CONNECT == _TRUE) && ((bit)bD1_DP_PIN17_CONNECT == _FALSE))
#else
#define bD1_CONNECT                             (((bit)bD1_DP_PIN15_CONNECT == _TRUE) && ((bit)bD1_DP_PIN16_CONNECT == _TRUE) && ((bit)bD1_DP_PIN17_CONNECT == _FALSE))
#endif

#if(_CUSTOMER == _CUS_TOSHIBA)
#if(TOSHIBA_DC_POWER == _OFF)
#define bD3_CONNECT                             (MCU_FE30_PORTA0_PIN_REG) // 156PIN_PIN_81, PA.0
#else
#define bD3_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#endif
#else
#define bD3_CONNECT                             (P1_0) // 156PIN_PIN_82, P1.0
#endif

#define PCB_A0_PIN()                            (bA0_CONNECT)
#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D1_PIN()                            (bD1_CONNECT)
#define PCB_D3_PIN()                            (bD3_CONNECT)

#if(_SIGNAL_GPIO_DETECT == _ON)
#define bH_Select                               (MCU_FE13_PORT63_PIN_REG)  // Pin 48, P6.3
#define bP_Select                               (MCU_FE09_PORT51_PIN_REG)  // Pin 51, P5.1
#endif
//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)
#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_DP_PIN17_CONNECT)

//-----------------------------------------------
// Macro of MHL Cable Connect
//-----------------------------------------------
#define bD3_MHL_CONNECT                         (MCU_FE1D_PORT75_PIN_REG)  // 156PIN_PIN_65 , P7.5

#define PCB_D3_MHL_DETECT()                     (bD3_MHL_CONNECT)

//-----------------------------------------------
// 
//-----------------------------------------------
#if(_USER_PCB_BOARD_TYPE == _KL_CUSTOMER_PCB_BOARD)
#define bSTBYB                                  (MCU_FE14_PORT64_PIN_REG)//Pin 49 P6.4
#define bP_RESET                                (MCU_FE12_PORT62_PIN_REG) // 156PIN_PIN_47, P6.2

#define PCB_STBYB_GPIO(x)                       {\
                                                    bSTBYB = (x);\
                                                }

#define PCB_P_RESET_GPIO(x)                     {\
                                                    bP_RESET = (x);\
                                                } 


#elif(_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2)
#define  bEN_D                                  (MCU_FE09_PORT51_PIN_REG)//Pin 51 P5.1
#define  bEN_H                                  (MCU_FE0B_PORT53_PIN_REG) //Pin 50 P5.3

#define  PCB_EN_D(x)                            {\
                                                    bEN_D = (~x);\
                                                }

#define  PCB_EN_H(x)                            {\
                                                    bEN_H = (~x);\
                                                }

#else

#define  bEN_D                                  (MCU_FE14_PORT64_PIN_REG)//Pin 49 P6.4
#define  bEN_H                                  (MCU_FE0B_PORT53_PIN_REG) //Pin 50 P5.3

#define  PCB_EN_D(x)                            {\
                                                    bEN_D = (x);\
                                                }

#define  PCB_EN_H(x)                            {\
                                                    bEN_H = (x);\
                                                }
#endif

//-----------------------------------------------
// 
//-----------------------------------------------
#if(_USER_PCB_BOARD_TYPE == _LY_CL2308_PCB_BOARD)
#define bHUB_RST                                (MCU_FE12_PORT62_PIN_REG) // 156PIN_PIN_47, P6.2

#define PCB_HUB_RST_GPIO(x)                     {\
                                                    bHUB_RST = (x);\
                                                } 
#endif

////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#if(_USER_PCB_BOARD_TYPE == _RTD2556_DEMO_PCB_BOARD)
#define bD0_HPD                                 (MCU_FE22_PORT82_PIN_REG) // 156PIN_PIN_70, P8.2
#define bD1_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#elif(_USER_PCB_BOARD_TYPE == _BX_CL1901_PCB_BOARD_2)
#define bD0_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE22_PORT82_PIN_REG) // 156PIN_PIN_70, P8.2
#define bD1_HPD                                 (MCU_FE23_PORT83_PIN_REG) // 156PIN_PIN_69, P8.3
#else
#define bD0_HPD                                 (MCU_FE22_PORT82_PIN_REG) // 156PIN_PIN_70, P8.2
#define bD1_HPD                                 (MCU_FE23_PORT83_PIN_REG) // 156PIN_PIN_69, P8.3
#endif
#define bD3_HPD                                 (P1_1) // 156PIN_PIN_84, P1.1

#if(_USER_PCB_BOARD_TYPE == _RTD2556_DEMO_PCB_BOARD)
#define _D0_HOT_PLUG_HIGH                       0
#define _D0_HOT_PLUG_LOW                        1
#else
#define _D0_HOT_PLUG_HIGH                       1
#define _D0_HOT_PLUG_LOW                        0
#endif

#if(D1_HOTPLUG_INVERSE == _OFF)
#define _D1_HOT_PLUG_HIGH                       1
#define _D1_HOT_PLUG_LOW                        0
#else
#define _D1_HOT_PLUG_HIGH                       0
#define _D1_HOT_PLUG_LOW                        1
#endif

#if(HOTPLUG_INVERSE == _OFF)
#define _D3_HOT_PLUG_HIGH                       1
#define _D3_HOT_PLUG_LOW                        0
#else
#define _D3_HOT_PLUG_HIGH                       0
#define _D3_HOT_PLUG_LOW                        1
#endif

#define PCB_D0_HOTPLUG(x)                       {\
                                                    bD0_HPD = (x);\
                                                }

#define PCB_D1_HOTPLUG(x)                       {\
                                                    bD1_HPD = (x);\
                                                }

#define PCB_D3_HOTPLUG(x)                       {\
                                                    bD3_HPD = (x);\
                                                }

#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
#define PCB_D1_HOTPLUG_DETECT()                 (bD1_HPD)
#define PCB_D3_HOTPLUG_DETECT()                 (bD3_HPD)


///////////////
// MHL Macro //
///////////////

//-----------------------------------------------
// Macro of HDMI/MHL Switch
//-----------------------------------------------
#define bD3_TMDS_SWITCH                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE1C_PORT74_PIN_REG) // 156PIN_PIN_64, P7.4

#define _TMDS_SWITCH_MHL_CBUS                   0
#define _TMDS_SWITCH_HDMI_HPD                   1

#define PCB_D3_HDMI_MHL_SWITCH(x)               {\
                                                    bD3_TMDS_SWITCH = (x);\
                                                }

//-----------------------------------------------
// Macro of MHL VBus Switch
//-----------------------------------------------
#define bD3_MHL_VBUS_SWITCH                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE1A_PORT72_PIN_REG) // 156PIN_PIN_63, P7.2

#define _MHL_VBUS_ON                            1
#define _MHL_VBUS_OFF                           0

#define PCB_D3_MHL_VBUS_SWITCH(x)               {\
                                                    bD3_MHL_VBUS_SWITCH = (x);\
                                                }

#define PCB_GET_D3_MHL_VBUS_SWITCH()            (bD3_MHL_VBUS_SWITCH)


///////////////////
// Display Macro //
///////////////////

//--------------------------------------------------
// Macro of LVDS eDP Panel Switch Control
//--------------------------------------------------
#define bLVDSDPTXSWICH                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)//(MCU_FE13_PORT63_PIN_REG) // 156PIN_PIN_48, P6.3

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
#if(_CUSTOMER == _CUS_MINDRAY)
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, g_stUserDataInFlash.usPanelPwmFre);\
                                                }
#else
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, _PWM_FREQ);\
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
#define SW_IIC_REG_SECECT
#ifdef SW_IIC_REG_SECECT
#if((_CUSTOMER != _CUS_MINDRAY) && (_ALS_TYPE != _SENSER_NONE))
#define SENSER_SCL_REG                            0xFE14
#define SENSER_SDA_REG                            0xFE13
#else
#define SENSER_SCL_REG                            0xFE2A
#define SENSER_SDA_REG                            0xFE2B
#endif
#define bSWIIC_A0_EEPROM_SCL                      (P1_5)
#define bSWIIC_A0_EEPROM_SDA                      (P1_6)
#define bSWIIC_D1_EEPROM_SCL                      (P3_2)
#define bSWIIC_D1_EEPROM_SDA                      (P3_3)
#define SW_IIC_REG_CONTROL_SECECT()               {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        SET_SW_IIC_SFR_CONTROL(0x00);\
                                                        SET_SW_IIC_SCLREGADDR(0xFE2A);\
                                                        SET_SW_IIC_SDAREGADDR(0xFE2B);\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_A0_EEPROM)\
                                                    {\
                                                        SET_SW_IIC_SFR_CONTROL(0x80|_IIC_A0_EEPROM);\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D1_EEPROM)\
                                                    {\
                                                        SET_SW_IIC_SFR_CONTROL(0x80|_IIC_D1_EEPROM);\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D3_EEPROM)\
                                                    {\
                                                        SET_SW_IIC_SFR_CONTROL(0x00);\
                                                        SET_SW_IIC_SCLREGADDR(0xFE2E);\
                                                        SET_SW_IIC_SDAREGADDR(0xFE2F);\
                                                    }\
                                                    else if(GET_SW_IIC_STATUS() == _IIC_USER_SENSOR)\
                                                    {\
                                                        SET_SW_IIC_SFR_CONTROL(0x00);\
                                                        SET_SW_IIC_SCLREGADDR(SENSER_SCL_REG);\
                                                        SET_SW_IIC_SDAREGADDR(SENSER_SDA_REG);\
                                                    }\
                                                    else\
                                                    {\
                                                        SET_SW_IIC_SFR_CONTROL(0xFF);\
                                                    }\
                                                }

#define PCB_SW_IIC_SDA_SET()                    {\
                                                    if(GET_SW_IIC_SFR_CONTROL() == 0x00)\
                                                    {\
                                                        ScalerSetByte(GET_SW_IIC_SDAREGADDR(),_TRUE);\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_A0_EEPROM))\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SDA = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_D1_EEPROM))\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SDA = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CLR()                    {\
                                                    if(GET_SW_IIC_SFR_CONTROL() == 0x00)\
                                                    {\
                                                        ScalerSetByte(GET_SW_IIC_SDAREGADDR(),_FALSE);\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_A0_EEPROM))\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SDA = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_D1_EEPROM))\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SDA = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                    if(GET_SW_IIC_SFR_CONTROL() == 0x00)\
                                                    {\
                                                        (x) = ScalerGetByte(GET_SW_IIC_SDAREGADDR());\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_A0_EEPROM))\
                                                    {\
                                                        (x) = bSWIIC_A0_EEPROM_SDA;\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_D1_EEPROM))\
                                                    {\
                                                        (x) = bSWIIC_D1_EEPROM_SDA;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_SET()                    {\
                                                    if(GET_SW_IIC_SFR_CONTROL() == 0x00)\
                                                    {\
                                                        ScalerSetByte(GET_SW_IIC_SCLREGADDR(),_TRUE);\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_A0_EEPROM))\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SCL = _TRUE;\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_D1_EEPROM))\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SCL = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CLR()                    {\
                                                    if(GET_SW_IIC_SFR_CONTROL() == 0x00)\
                                                    {\
                                                        ScalerSetByte(GET_SW_IIC_SCLREGADDR(),_FALSE);\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_A0_EEPROM))\
                                                    {\
                                                        bSWIIC_A0_EEPROM_SCL = _FALSE;\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_D1_EEPROM))\
                                                    {\
                                                        bSWIIC_D1_EEPROM_SCL = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                    if(GET_SW_IIC_SFR_CONTROL() == 0x00)\
                                                    {\
                                                        (x) = ScalerGetByte(GET_SW_IIC_SCLREGADDR());\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_A0_EEPROM))\
                                                    {\
                                                        (x) = bSWIIC_A0_EEPROM_SCL;\
                                                    }\
                                                    else if(GET_SW_IIC_SFR_CONTROL() == (0x80|_IIC_D1_EEPROM))\
                                                    {\
                                                        (x) = bSWIIC_D1_EEPROM_SCL;\
                                                    }\
                                                }
#else
#define bSWIIC_SYS_EEPROM_SCL                   (MCU_FE2A_PORT92_PIN_REG)
#define bSWIIC_SYS_EEPROM_SDA                   (MCU_FE2B_PORT93_PIN_REG)
#define bSWIIC_A0_EEPROM_SCL                    (P1_5)
#define bSWIIC_A0_EEPROM_SDA                    (P1_6)
#define bSWIIC_D0_EEPROM_SCL                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D0_EEPROM_SDA                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D1_EEPROM_SCL                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D1_EEPROM_SDA                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_D3_EEPROM_SCL                    (MCU_FE2E_PORT96_PIN_REG)
#define bSWIIC_D3_EEPROM_SDA                    (MCU_FE2F_PORT97_PIN_REG)
#define bSWIIC_USER_EEPROM_SCL                  (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_USER_EEPROM_SDA                  (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_USER_SENSOR_SCL                  (MCU_FE2A_PORT92_PIN_REG)   // 156PIN_PIN_77, P9.2
#define bSWIIC_USER_SENSOR_SDA                  (MCU_FE2B_PORT93_PIN_REG)   // 156PIN_PIN_78, P9.3

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
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D3_EEPROM)\
                                                    {\
                                                        bSWIIC_D3_EEPROM_SDA = _TRUE;\
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
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D3_EEPROM)\
                                                    {\
                                                        bSWIIC_D3_EEPROM_SDA = _FALSE;\
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
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D3_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_D3_EEPROM_SDA;\
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
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D3_EEPROM)\
                                                    {\
                                                        bSWIIC_D3_EEPROM_SCL = _TRUE;\
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
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D3_EEPROM)\
                                                    {\
                                                        bSWIIC_D3_EEPROM_SCL = _FALSE;\
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
                                                    else if(GET_SW_IIC_STATUS() == _IIC_D3_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_D3_EEPROM_SCL;\
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

#endif


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#if(LED_GPIO_CONTROL_SWAP == _ON)
#define bLED2                                   (MCU_FE27_PORT87_PIN_REG) // 156PIN_PIN_74, P8.7
#define bLED1                                   (MCU_FE26_PORT86_PIN_REG) // 156PIN_PIN_73, P8.6
#else
#define bLED1                                   (MCU_FE27_PORT87_PIN_REG) // 156PIN_PIN_74, P8.7
#define bLED2                                   (MCU_FE26_PORT86_PIN_REG) // 156PIN_PIN_73, P8.6
#endif

#if(LED_ON_OFF_SWAP == _ON)
#define _LED_ON                                 0
#define _LED_OFF                                1
#else
#define _LED_ON                                 1
#define _LED_OFF                                0
#endif

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

#define PCB_LED_TYPE_FLASH()                    {\
                                                }


#define PCB_LED_TYPE_INVERT()                   {\
                                                    bLED2 = ~bLED2;               \
                                                    bLED1 = _LED_OFF;               \                                                   
                                                }

#define PCB_LED_TYPE_POWEROFF_INVERT()          {\
                                                    bLED1 = ~bLED1;\
                                                    bLED2 = _LED_OFF;\                                                   
                                                }

//--------------------------------------------------
// Hard Id GPIO define
//--------------------------------------------------
#if(_GET_HARD_ID == _ON)
#if((_USER_PCB_BOARD_TYPE == _MR_CL13XX_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _KL_CL13XX_PCB_BOARD) || (_USER_PCB_BOARD_TYPE == _JN_CL15XX_PCB_BOARD))
#define bHARD_ID0                              (MCU_FE1F_PORT77_PIN_REG)
#define bHARD_ID1                              (MCU_FE22_PORT82_PIN_REG)
#define bHARD_ID2                              (MCU_FE2E_PORT96_PIN_REG)
#define bHARD_ID3                              (MCU_FE2F_PORT97_PIN_REG)
#else
#define bHARD_ID0                              (MCU_FE43_PORTC3_PIN_REG)
#define bHARD_ID1                              (MCU_FE44_PORTC4_PIN_REG)
#define bHARD_ID2                              (MCU_FE45_PORTC5_PIN_REG)
#define bHARD_ID3                              (MCU_FE46_PORTC6_PIN_REG)
#endif

#define PCB_HARD_ID0_DETECT()                  (bHARD_ID0)
#define PCB_HARD_ID1_DETECT()                  (bHARD_ID1)
#define PCB_HARD_ID2_DETECT()                  (bHARD_ID2)
#define PCB_HARD_ID3_DETECT()                  (bHARD_ID3)
#endif

//--------------------------------------------------
// HDMI_SPLITTER_1X2 GPIO Define
//--------------------------------------------------
#if(_HDMI_SPLITTER_1X2_EN == _ON)
#define bOE                                    (MCU_FE45_PORTC5_PIN_REG)   // 156PIN_PIN_43, PC.5
#define bSet_Out                               (MCU_FE46_PORTC6_PIN_REG)   // 156PIN_PIN_44, PC.6

#define _OE_HIGH                               1
#define _OE_LOW                                0

#define PCB_OE_CONTROL(x)                      {\
                                                   bOE = (x);\
                                               }

#define PCB_SETOUT_DETECT()                    (bSet_Out)
#endif

//--------------------------------------------------
// 
//--------------------------------------------------
#if(_CUSTOMER == _CUS_TOSHIBA)
#define bPin20DVI                              (P1_0)
#endif

//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#if(_USER_ADC_ADJUST_BY_RESISTOR == _ON)
#define AD_CONTRAST_ADJUST                      (MCU_FF0A_ADC_A1_CONVERT_RESULT) // 156PIN_PIN_144,A-ADC1
#define AD_BACKLIGHT_ADJUST                     (MCU_FF09_ADC_A0_CONVERT_RESULT) // 156PIN_PIN_143,A-ADC0
#endif

#define AD_KEY1                                 (MCU_FF09_ADC_A0_CONVERT_RESULT) // 156PIN_PIN_143,A-ADC0
#define AD_KEY2                                 (MCU_FF0A_ADC_A1_CONVERT_RESULT) // 156PIN_PIN_144,A-ADC1

#define PCB_ADKEY1()                            (AD_KEY1)
#define PCB_ADKEY2()                            (AD_KEY2)

#if(_USER_KEYPAD_TYPE == _KEYPAD_TYPE_5IO)
#if(_USER_PCB_BOARD_TYPE == _MR_CL0904_PCB_BOARD)
#define bKEY_1_REG                              (MCU_FE21_PORT81_PIN_REG)   // 156PIN_PIN_68
#define bKEY_2_REG                              (MCU_FE23_PORT83_PIN_REG)   // 156PIN_PIN_69
#define bKEY_3_REG                              (MCU_FE22_PORT82_PIN_REG)   // 156PIN_PIN_70
#define bKEY_4_REG                              (MCU_FE24_PORT84_PIN_REG)   // 156PIN_PIN_71
#define bKEY_5_REG                              (MCU_FE25_PORT85_PIN_REG)   // 156PIN_PIN_72
#else
#define bKEY_1_REG                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)   // 156PIN_PIN_68
#define bKEY_2_REG                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)   // 156PIN_PIN_69
#define bKEY_3_REG                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)   // 156PIN_PIN_70
#define bKEY_4_REG                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)   // 156PIN_PIN_71
#define bKEY_5_REG                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)   // 156PIN_PIN_72
#endif

#define PCB_KEY_POWER_DETECT()                  (bKEY_1_REG)
#define PCB_KEY_AUTO_DETECT()                   (bKEY_2_REG)
#define PCB_KEY_RIGHT_DETECT()                  (bKEY_3_REG)
#define PCB_KEY_LEFT_DETECT()                   (bKEY_4_REG)
#define PCB_KEY_MENU_DETECT()                   (bKEY_5_REG)
#endif


#if(_CUSTOMER ==_CUS_MINDRAY)
#if(_USER_KEYPAD_TYPE == _KEYPAD_TYPE_5IO)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if(PCB_KEY_POWER_DETECT() == _LOW)\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\
                                                    if(PCB_KEY_AUTO_DETECT() == _LOW)\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if(PCB_KEY_RIGHT_DETECT() == _LOW)\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if(PCB_KEY_LEFT_DETECT() == _LOW)\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if(PCB_KEY_MENU_DETECT() == _LOW)\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\
                                                }
#else
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }
#endif

#else
#if(_USER_KEYPAD_TYPE == _KEYPAD_TYPE_NONE)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }
#else
#if(_USER_PROJECT_TYPE == PROJECT_DEMO_RTD2556)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0xC0 <= (ucV2)) && ((ucV2) < 0xE0))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x68 <= (ucV1)) && ((ucV1) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV1)) && ((ucV1) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\ 
                                                    if((0x68 <= (ucV2)) && ((ucV2) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                }
#elif((_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276BC30_39) || \
      (_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_INNOLUX_R150XJE_L01) || \
      (_USER_PROJECT_TYPE == KL_RTD2556_CL1516CBGKLNO0X_NL10276AC30_48D)) 
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0x6F <= (ucV1)) && ((ucV1) < 0x90))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0x40 <= (ucV2)) && ((ucV2) < 0x60))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0xA0 <= (ucV2)) && ((ucV2) < 0xB0))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\ 
                                                }

#elif((_USER_PROJECT_TYPE == KL_RTD2556_CL1801C_D_BGKLQQ0X_BOE_DV185WHM_NM1) || \
        (_USER_PROJECT_TYPE == KL_RTD2556_CL1801FBGKLQQ0X_BOE_DV185WHM_NM1))
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
#elif((_USER_PROJECT_TYPE == KL_RTD2556_CL2120_BGKLPK0X_PAS_VVX22F164H00) || \
      (_USER_PROJECT_TYPE == KL_RTD2556_CL2106CBGKLZJ0X_LG_LM215WF3_SLS2) || \
      (_USER_PROJECT_TYPE == BES_RTD2556_CL1563DBGBERU01_BOE_DV150X0M_N10) || \
      (_USER_PROJECT_TYPE == DW_RTD2556_CL1514CBGDWKP01_INNOLUX_R150XJE_L01) || \
      (_USER_PROJECT_TYPE == XS_RTD2556_CL2308ABGXSQT0X_INNOLUX_R238HCA_L3B) || \
      (_USER_PROJECT_TYPE == ZP_RTD2556_CL2308_BGZPQT01_INNOLUX_R238HCA_L3B) || \
      (_USER_PROJECT_TYPE == LB_RTD2556_CL2308ABGLBQT01_INNOLUX_R238HCA_L3B) || \
      (_USER_PROJECT_TYPE == HD_RTD2556_CL1514CBGHDRU01_BOE_DV150X0M_N10) || \
      (_USER_PROJECT_TYPE == DW_RTD2556_CL2308ABGDWQT01_INNOLUX_R238HCA_L3B) || \
      (_USER_PROJECT_TYPE == NP_RTD2556_CL2308_BGNPQT01_INNOLUX_R238HCA_L3B))
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
#elif(_USER_PROJECT_TYPE == JN_RTD2556_CL2151ABGJNJF02_AUO_G215HAN01_6)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0x48 <= (ucV2)) && ((ucV2) < 0x68))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x48 <= (ucV1)) && ((ucV1) < 0x68))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV1)) && ((ucV1) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\ 
                                                    if((0 <= (ucV2)) && ((ucV2) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                }
#elif(_USER_PROJECT_TYPE == JN_RTD2556_CL2150ABGJNJF02_AUO_G215HAN01_6)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0xB8 <= (ucV2)) && ((ucV2) < 0xD8))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0xB8 <= (ucV1)) && ((ucV1) < 0xD8))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0x68 <= (ucV1)) && ((ucV1) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\ 
                                                    if((0x68 <= (ucV2)) && ((ucV2) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                }
#elif((_USER_PROJECT_TYPE == HB_RTD2556_CL2118ABGHBZJ01_LG_LM215WF3_SLS2) || \
      (_USER_PROJECT_TYPE == KE_RTD2556_CL2105_BGKEZJ01_LG_LM215WF3_SLS2) || \
      (_USER_PROJECT_TYPE == JR_RTD2556_CL2105TBGJRZJ0X_LG_LM215WF3_SLS2))
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0xC0 <= (ucV2)) && ((ucV2) < 0xD0))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if((0x80 <= (ucV1)) && ((ucV1) < 0x90))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x50 <= (ucV1)) && ((ucV1) < 0x60))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\ 
                                                    if((0xA8 <= (ucV2)) && ((ucV2) < 0xB8))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV2)) && ((ucV2) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\
                                                }
#elif((_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_LG_LP156WF6_SPP2) || \
      (_USER_PROJECT_TYPE == WD_RTD2556_CL1506_TBWDZF01_BOE_EV156FHM_N80))
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0xC0 <= (ucV2)) && ((ucV2) < 0xE0))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x68 <= (ucV1)) && ((ucV1) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
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
#elif(_USER_PROJECT_TYPE == ZQ_RTD2556_CL1901_BGZQRB01_INNOLUX_R190ECE_L01)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0x98 <= (ucV2)) && ((ucV2) < 0xB8))\
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
                                                    if((0x38 <= (ucV2)) && ((ucV2) < 0x58))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV2)) && ((ucV2) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _POWER_KEY_MASK;\
                                                    }\
                                                }
#elif((_USER_PROJECT_TYPE == BX_RTD2556_CL1930CBGBXUP02_AUO_G190EAN01_0) || \
      (_USER_PROJECT_TYPE == BX_RTD2556_CL1901ABGBXUP01_AUO_G190EAN01_0) || \
      (_USER_PROJECT_TYPE == BX_RTD2556_CL1901ABGBXUP02_AUO_G190EAN01_0))
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
#elif(_USER_PROJECT_TYPE == JN_RTD2556_CL1506BBGJNMT02_AUO_G156HAN05_0)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0x48 <= (ucV1)) && ((ucV1) < 0x68))\
                                                    {\
                                                        (ucKeyState) |= _MENU_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV1)) && ((ucV1) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
                                                    }\ 
                                                    if((0x48 <= (ucV2)) && ((ucV2) < 0x68))\
                                                    {\
                                                        (ucKeyState) |= _EXIT_KEY_MASK;\
                                                    }\
                                                    if((0 <= (ucV2)) && ((ucV2) < 0x20))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                }

#else
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if((0xC0 <= (ucV2)) && ((ucV2) < 0xE0))\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if((0x68 <= (ucV1)) && ((ucV1) < 0x88))\
                                                    {\
                                                        (ucKeyState) |= _RIGHT_KEY_MASK;\
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

#endif
#endif
#endif

#endif // End of #if(_PCB_TYPE == _RL6432_QA_B_156PIN_1A1MHL2DP_LVDS_eDP)
