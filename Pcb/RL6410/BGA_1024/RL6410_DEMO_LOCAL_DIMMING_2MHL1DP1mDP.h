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
// ID Code      : RL6410_DEMO_LOCAL_DIMMING_2MHL1DP1mD.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6410_DEMO_LOCAL_DIMMING_2MHL1DP1mDP)


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
#define _PCB_DEBUG_DDC                          _DDC3


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                     _D0_DP_PORT
#define _D0_DDC_CHANNEL_SEL                     _DDC0
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_MINI
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                     _D1_DP_PORT
#define _D1_DDC_CHANNEL_SEL                     _DDC1
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_256
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER
#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_INPUT_PORT_TYPE                     _D2_HDMI_PORT
#define _D2_DDC_CHANNEL_SEL                     _DDC2
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D2_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER

#define _D2_MAX_HDMI_EDID_COUNT                 3

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                     _D3_HDMI_PORT
#define _D3_DDC_CHANNEL_SEL                     _DDC3
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_USER

#define _D3_MAX_HDMI_EDID_COUNT                 3


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D2_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_0

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _D0_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _D1_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _D2_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _D3_INPUT_PORT

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#define _D0_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#define _D0_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#define _D0_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#define _D0_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#define _D0_DP_PCB_LANE0_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE1_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE2_PN_SWAP                _OFF
#define _D0_DP_PCB_LANE3_PN_SWAP                _OFF

#define _D1_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#define _D1_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#define _D1_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#define _D1_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#define _D1_DP_PCB_LANE0_PN_SWAP                _OFF
#define _D1_DP_PCB_LANE1_PN_SWAP                _OFF
#define _D1_DP_PCB_LANE2_PN_SWAP                _OFF
#define _D1_DP_PCB_LANE3_PN_SWAP                _OFF


////////////////////
// For LVDS Panel //
////////////////////

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

#elif(_LVDS_OUTPUT_PORT == _LVDS_8_PORT)
#define _LVDS_PORT_SEL                          _LVDS_8_PORT_ABCDEFGH
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _ENABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _ENABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#endif

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL                      _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL               _DISABLE

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                      10
#define _LVDS_SPREAD_SPEED                      _SPEED_33K


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
#define _PANEL_DPTX_1_1_SPREAD_RANGE            6
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K


//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_SWING_LEVEL             _DP_SWING_800_MV
#define _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_3_5_DB

//--------------------------------------------------
// eDPTx 1.2 HBR2 SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_SPREAD_RANGE            6
#define _PANEL_DPTX_1_2_SPREAD_SPEED            _SPEED_33K

//--------------------------------------------------
// eDPTx 1.2 HBR2 FB/Lane Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_FB_SWAP                 _DISABLE
#define _PANEL_DPTX_1_2_LANE_SWAP               _DISABLE
#define _PANEL_DPTX_1_2_LANE_PN_SWAP            _DISABLE


/////////////////
// Memory DDR3 //
/////////////////

//--------------------------------------------------
// Definitions of DDR3 Memory Size
//--------------------------------------------------
#define _EXTERNAL_MEMORY_SIZE_CONFIG            _1G_16BIT_DDR3_1PC

//--------------------------------------------------
// Definitions of DDR3 PLL Phase
//--------------------------------------------------
#if((_EXTERNAL_MEMORY_SIZE_CONFIG & _MEMORY_DENSITY_MASK) == _MEMORY_DENSITY_64M_16)
#define _DDR3_PLL_INITIAL_PHASE_0               0x1A082600
#define _DDR3_PLL_INITIAL_PHASE_1               0x18002719
#define _DDR3_READ_DQ_DLYN_TAP                  0x1F1F1F1F
#elif((_EXTERNAL_MEMORY_SIZE_CONFIG & _MEMORY_DENSITY_MASK) == _MEMORY_DENSITY_128M_16)
#define _DDR3_PLL_INITIAL_PHASE_0               0x1B002900
#define _DDR3_PLL_INITIAL_PHASE_1               0x1800291B
#define _DDR3_READ_DQ_DLYN_TAP                  0x1C1C1C1C
#elif((_EXTERNAL_MEMORY_SIZE_CONFIG & _MEMORY_DENSITY_MASK) == _MEMORY_DENSITY_256M_16)
#define _DDR3_PLL_INITIAL_PHASE_0               0x1A002500
#define _DDR3_PLL_INITIAL_PHASE_1               0x18002717
#define _DDR3_READ_DQ_DLYN_TAP                  0x1E1E1E1E
#endif


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT

#define _BACKLIGHT_PWM                          _PWM1
#define _BACKLIGHT_PWM_INVERSE                  _ON

#define _PWM0_EN                                _ON
#define _PWM1_EN                                _ON
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _OFF

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
#define _PWM1_RST_EN                            _ON
#define _PWM2_RST_EN                            _OFF
#define _PWM3_RST_EN                            _OFF
#define _PWM4_RST_EN                            _OFF
#define _PWM5_RST_EN                            _OFF
#define _PWM_RST_SIGNAL_SEL                     _DVS
#else
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT

#define _BACKLIGHT_PWM                          _PWM2
#define _BACKLIGHT_PWM_INVERSE                  _ON

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _ON
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _OFF

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
#define _PWM2_RST_EN                            _ON
#define _PWM3_RST_EN                            _OFF
#define _PWM4_RST_EN                            _OFF
#define _PWM5_RST_EN                            _OFF
#define _PWM_RST_SIGNAL_SEL                     _DVS
#endif


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
#define _PCB_SYS_EEPROM_IIC                     _HW_IIC_PIN_J7_H6


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
#include "RL6410_DEMO_LOCAL_DIMMING_2MHL1DP1mDP_PINSHARE.h"


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
#define bVCCKOFFPOWER                           (MCU_FE32_PORTA2_PIN_REG)

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#define bDDRPOWER                               (P3_1)

#define _DDR_POWER_ON                           1
#define _DDR_POWER_OFF                          0

#define PCB_DDR_POWER(x)                        {\
                                                    bDDRPOWER = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define bPANELPOWER                             (MCU_FE2B_PORT93_PIN_REG)

#define _PANEL_CONTROL_ON                       1
#define _PANEL_CONTROL_OFF                      0

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define bBACKLIGHTPOWER                         (MCU_FE2C_PORT94_PIN_REG)

#define _LIGHT_CONTROL_ON                       1
#define _LIGHT_CONTROL_OFF                      0

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    if(_LIGHT_CONTROL_ON == (x))\
                                                    {\
                                                        bBACKLIGHTPOWER = (x);\
                                                        ScalerTimerDelayXms(20);\
                                                        ExternalDeviceInterfaceLedDriverPwmEnable(_ENABLE);\
                                                    }\
                                                    else\
                                                    {\
                                                        ExternalDeviceInterfaceLedDriverPwmEnable(_DISABLE);\
                                                        ScalerTimerDelayXms(5);\
                                                        bBACKLIGHTPOWER = (x);\
                                                    }\
                                                }

#else
#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    bBACKLIGHTPOWER = (x);\
                                                }
#endif

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
#define bFLASH_WRITE_PROTECT                    (MCU_FE28_PORT90_PIN_REG)

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_FE0D_PORT55_PIN_REG)

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (P3_2)

#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D2_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D4_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D5_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of EDID (Foxconn Only)
//-----------------------------------------------
#define bD2_EXT_SWITCH_EDID_0                   (MCU_FE0C_PORT54_PIN_REG)
#define bD2_EXT_SWITCH_EDID_1                   (MCU_FE4E_PORTD6_PIN_REG)
#define bD2_EXT_SWITCH_EDID_2                   (MCU_FE4D_PORTD5_PIN_REG)
#define bD3_EXT_SWITCH_EDID_0                   (MCU_FE00_PORT40_PIN_REG)
#define bD3_EXT_SWITCH_EDID_1                   (MCU_FE08_PORT50_PIN_REG)
#define bD3_EXT_SWITCH_EDID_2                   (MCU_FE0B_PORT53_PIN_REG)

#define _EEPROM_EDID_ENABLE                     0
#define _EEPROM_EDID_DISABLE                    1

#define PCB_MULTI_EDID_ALL_SWITCH_OFF(port)     {\
                                                    switch((port))\
                                                    {\
                                                        case _D0_INPUT_PORT:\
                                                            break;\
                                                        case _D1_INPUT_PORT:\
                                                            break;\
                                                        case _D2_INPUT_PORT:\
                                                            bD2_EXT_SWITCH_EDID_0 = _EEPROM_EDID_DISABLE;\
                                                            bD2_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                            bD2_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            break;\
                                                        case _D3_INPUT_PORT:\
                                                            bD3_EXT_SWITCH_EDID_0 = _EEPROM_EDID_DISABLE;\
                                                            bD3_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                            bD3_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            break;\
                                                        case _D4_INPUT_PORT:\
                                                            break;\
                                                        case _D5_INPUT_PORT:\
                                                            break;\
                                                        default:\
                                                            break;\
                                                    }\
                                                }

#define PCB_MULTI_EDID_SWITCH(port, index)      {\
                                                    switch(port)\
                                                    {\
                                                        case _D0_INPUT_PORT:\
                                                            break;\
                                                        case _D1_INPUT_PORT:\
                                                            break;\
                                                        case _D2_INPUT_PORT:\
                                                            if((index) == 0)\
                                                            {\
                                                                bD2_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                                bD2_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                                bD2_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            }\
                                                            else if((index) == 1)\
                                                            {\
                                                                bD2_EXT_SWITCH_EDID_0 = _EEPROM_EDID_DISABLE;\
                                                                bD2_EXT_SWITCH_EDID_1 = _EEPROM_EDID_ENABLE;\
                                                                bD2_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            }\
                                                            else if((index) == 2)\
                                                            {\
                                                                bD2_EXT_SWITCH_EDID_0 = _EEPROM_EDID_DISABLE;\
                                                                bD2_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                                bD2_EXT_SWITCH_EDID_2 = _EEPROM_EDID_ENABLE;\
                                                            }\
                                                            else\
                                                            {\
                                                                bD2_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                                bD2_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                                bD2_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            }\
                                                            break;\
                                                        case _D3_INPUT_PORT:\
                                                            if((index) == 0)\
                                                            {\
                                                                bD3_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                                bD3_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                                bD3_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            }\
                                                            else if((index) == 1)\
                                                            {\
                                                                bD3_EXT_SWITCH_EDID_0 = _EEPROM_EDID_DISABLE;\
                                                                bD3_EXT_SWITCH_EDID_1 = _EEPROM_EDID_ENABLE;\
                                                                bD3_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            }\
                                                            else if((index) == 2)\
                                                            {\
                                                                bD3_EXT_SWITCH_EDID_0 = _EEPROM_EDID_DISABLE;\
                                                                bD3_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                                bD3_EXT_SWITCH_EDID_2 = _EEPROM_EDID_ENABLE;\
                                                            }\
                                                            else\
                                                            {\
                                                                bD3_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                                bD3_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                                bD3_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                            }\
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
                                                    bD2_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                    bD2_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                    bD2_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                    bD3_EXT_SWITCH_EDID_0 = _EEPROM_EDID_ENABLE;\
                                                    bD3_EXT_SWITCH_EDID_1 = _EEPROM_EDID_DISABLE;\
                                                    bD3_EXT_SWITCH_EDID_2 = _EEPROM_EDID_DISABLE;\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD0_DP_PIN15_CONNECT                    (MCU_FE33_PORTA3_PIN_REG)
#define bD0_DP_PIN16_CONNECT                    (MCU_FE35_PORTA5_PIN_REG)
#define bD0_DP_PIN17_CONNECT                    (MCU_FE34_PORTA4_PIN_REG)
#define bD0_CONNECT                             (((bit)bD0_DP_PIN15_CONNECT == _TRUE) && ((bit)bD0_DP_PIN16_CONNECT == _TRUE) && ((bit)bD0_DP_PIN17_CONNECT == _FALSE))

#define bD1_DP_PIN15_CONNECT                    (MCU_FE36_PORTA6_PIN_REG)
#define bD1_DP_PIN16_CONNECT                    (MCU_FE38_PORTB0_PIN_REG)
#define bD1_DP_PIN17_CONNECT                    (MCU_FE37_PORTA7_PIN_REG)
#define bD1_CONNECT                             (((bit)bD1_DP_PIN15_CONNECT == _TRUE) && ((bit)bD1_DP_PIN16_CONNECT == _TRUE) && ((bit)bD1_DP_PIN17_CONNECT == _FALSE))

#define bD2_CONNECT                             (MCU_FE3A_PORTB2_PIN_REG)
#define bD3_CONNECT                             (MCU_FE3B_PORTB3_PIN_REG)

#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D1_PIN()                            (bD1_CONNECT)
#define PCB_D2_PIN()                            (bD2_CONNECT)
#define PCB_D3_PIN()                            (bD3_CONNECT)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)
#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_DP_PIN17_CONNECT)


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define bD0_HPD                                 (MCU_FE4C_PORTD4_PIN_REG)
#define bD1_HPD                                 (MCU_FE4B_PORTD3_PIN_REG)
#define bD2_HPD                                 (MCU_FE4A_PORTD2_PIN_REG)
#define bD3_HPD                                 (MCU_FE49_PORTD1_PIN_REG)

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

#define PCB_D1_HOTPLUG(x)                       {\
                                                    bD1_HPD = (x);\
                                                }

#define PCB_D2_HOTPLUG(x)                       {\
                                                    bD2_HPD = (x);\
                                                }

#define PCB_D3_HOTPLUG(x)                       {\
                                                    bD3_HPD = (x);\
                                                }


#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
#define PCB_D1_HOTPLUG_DETECT()                 (bD1_HPD)
#define PCB_D2_HOTPLUG_DETECT()                 (bD2_HPD)
#define PCB_D3_HOTPLUG_DETECT()                 (bD3_HPD)


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)

#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 480);\
                                                    ScalerMcuPwmAdjustFrequency(_LED_PWM, 500);\
                                                }

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (0x30));\
                                                    ExternalDeviceInterfaceLedDriverBacklight(x);\
                                                }
#else
#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }
#endif

#else // Else of #if(_BACKLIGHT_DIMMING_SUPPORT == _ON)

#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, (WORD)22000);\
                                                    ScalerMcuPwmAdjustFrequency(_LED_PWM, 500);\
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

#endif

#endif // End of #if(_BACKLIGHT_DIMMING_SUPPORT == _ON)

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define bSWIIC_SYS_EEPROM_SCL                   (MCU_FE0E_PORT56_PIN_REG)
#define bSWIIC_SYS_EEPROM_SDA                   (MCU_FE0F_PORT57_PIN_REG)

#define bSWIIC_AUDIO_SCL                        (MCU_FE14_PORT64_PIN_REG)
#define bSWIIC_AUDIO_SDA                        (MCU_FE15_PORT65_PIN_REG)

#define bSWIIC_D2_EDID_EEPROM_SCL               (MCU_FE55_PORTE5_PIN_REG)
#define bSWIIC_D2_EDID_EEPROM_SDA               (MCU_FE56_PORTE6_PIN_REG)

#define bSWIIC_D3_EDID_EEPROM_SCL               (MCU_FE53_PORTE3_PIN_REG)
#define bSWIIC_D3_EDID_EEPROM_SDA               (MCU_FE54_PORTE4_PIN_REG)


#define PCB_SW_IIC_SDA_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SDA;\
                                                    }\
                                                }

#define PCB_SW_IIC_SCL_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SCL;\
                                                    }\
                                                }


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define PCB_LED_AC_ON_INITIAL()                 {\
                                                    PCB_LED_PWM_TYPE_GPIO(_LED_PWM_GPIO_OFF);\
                                                    PCB_LED_PWM_SWITCH(0);\
                                                    PCB_LED_TYPE_PWM(_LED_PWM_MIN);\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                }

#define PCB_LED_ON()                            {\
                                                }

#define PCB_LED_OFF()                           {\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                }

#define PCB_LED_TYPE2()                         {\
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
#define AD_KEY2                                 (MCU_FF0B_ADC_A2_CONVERT_RESULT)

#define PCB_ADKEY2()                            (AD_KEY2)


////////////////////
// GPIO Key Macro //
////////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define bPOWER_KEY                              (MCU_FE04_PORT44_PIN_REG)
#define bRIGHT_KEY                              (MCU_FE02_PORT42_PIN_REG)
#define bLEFT_KEY                               (MCU_FE01_PORT41_PIN_REG)
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                    if(bLEFT_KEY == 0)\
                                                    {\
                                                        (ucKeyState) |= _LEFT_KEY_MASK;\
                                                    }\
                                                    if(bRIGHT_KEY == 0)\
                                                    {\
                                                        (ucKeyState) |= (_RIGHT_KEY_MASK);\
                                                    }\
                                                    if(((ucV2) > (0x41)) && ((ucV2) < (0x61)))\
                                                    {\
                                                        (ucKeyState) |= (_MENU_KEY_MASK);\
                                                    }\
                                                    if(((ucV2) > (0x6F)) && ((ucV2) < (0x8F)))\
                                                    {\
                                                        (ucKeyState) |= (_EXIT_KEY_MASK);\
                                                    }\
                                                    if(bPOWER_KEY == 0)\
                                                    {\
                                                        (ucKeyState) |= (_POWER_KEY_MASK);\
                                                    }\
                                                }
//**********************************************************************************************
// Dell Pcb Series
//**********************************************************************************************

//--------------------------------------------------
// Define of MCU PWM
//--------------------------------------------------
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define MCU_ADJUST_PWM_DUTY(x, y)               {\
                                                    MCU_ADJUST_8BIT_PWM_DUTY((x), (y))\
                                                }\

#define MCU_GET_PWM_DUTY(x)                     {\
                                                    MCU_GET_8BIT_PWM_DUTY((x))\
                                                }\

#else
#define MCU_ADJUST_PWM_DUTY(x, y)               {\
                                                    MCU_ADJUST_12BIT_PWM_DUTY((x), (y))\
                                                }\

#define MCU_GET_PWM_DUTY(x)                     {\
                                                    MCU_GET_12BIT_PWM_DUTY(x)\
                                                }\

#endif // End of #if(_PWM_DUT_RESOLUTION == _PWM_8BIT)


///////////////////
//  Port Name    //
///////////////////
#define _D0_INPUT_PORT_NAME                     _m_, _D_, _P_
#define _D1_INPUT_PORT_NAME                     _D_, _P_
#define _D2_INPUT_PORT_NAME                     _H_, _D_, _M_, _I_, _1_
#define _D3_INPUT_PORT_NAME                     _H_, _D_, _M_, _I_, _2_


///////////////////
//   LED PWM     //
///////////////////

//--------------------------------------------------
// Macro of LED GPIO
//--------------------------------------------------
#define PCB_LED_TYPE_GPIO(x)                    {\
                                                    if((x) == _LED_GPIO_STATUS_OFF)\
                                                    {\
                                                        PCB_LED_PWM_TYPE_GPIO(_LED_PWM_GPIO_OFF);\
                                                    }\
                                                    else if((x) == _LED_GPIO_STATUS_ON)\
                                                    {\
                                                        PCB_LED_PWM_TYPE_GPIO(_LED_PWM_GPIO_ON);\
                                                    }\
                                                    else if((x) == _LED_GPIO_STATUS_SAVING)\
                                                    {\
                                                        PCB_LED_PWM_TYPE_GPIO(_LED_PWM_GPIO_OFF);\
                                                    }\
                                                }


///////////////////
//  Audio PWM    //
///////////////////

//--------------------------------------------------
// Macro of Audio PWM
//--------------------------------------------------
#define _AUDIO_PWM                              _NO_PWM

#define _AUDIO_PWM_MAX                          255
#define _AUDIO_PWM_MIN                          0

#define PCB_AUDIO_VOLUME_PWM(x)                 {\
                                                    MCU_ADJUST_PWM_DUTY(_AUDIO_PWM, (x));\
                                                }

#define PCB_GET_AUDIO_VOLUME_PWM()              (MCU_GET_PWM_DUTY(_AUDIO_PWM))


///////////////////
//   LED PWM     //
///////////////////

//--------------------------------------------------
// Macro of LED PWM GPIO
//--------------------------------------------------
#define bLED_PWM                                (MCU_FE30_PORTA0_PIN_REG)

#define _LED_PWM_GPIO_ON                        0
#define _LED_PWM_GPIO_OFF                       1

#define PCB_LED_PWM_TYPE_GPIO(x)                {\
                                                    bLED_PWM = (x);\
                                                }

#define PCB_GET_LED_PWM_TYPE_GPIO()             (bLED_PWM)

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
// Macro of LED PinShare PWM Switch
//--------------------------------------------------
#define PCB_LED_PWM_SWITCH(x)                   {\
                                                    if((x) == 0)\
                                                    {\
                                                        ScalerSetByte(P10_40_PIN_SHARE_CTRLA0, (BYTE)_PIN_AG24);\
                                                    }\
                                                    else if((x) == 1)\
                                                    {\
                                                        ScalerSetByte(P10_40_PIN_SHARE_CTRLA0, (BYTE)4);\
                                                    }\
                                                }


/////////////////
//   35 TRS    //
/////////////////
#define _PCB_EMBEDDED_SPEAKER                   _AUDIO_OUTPUT_FROM_IIS
#define _PCB_EXTERN_35_TRS                      _AUDIO_OUTPUT_FROM_NONE


////////////////////////
// Device Touch Panel //
////////////////////////

//--------------------------------------------------
//  Device AMP
//--------------------------------------------------
#define _DEVICE_AMP_TYPE                        _DEVICE_AMP_05_NUVOTON_NPCP215
#define _DEVICE_AMP_EQ_SUPPORT                  _OFF
#define _DEVICE_AMP_MAXX_SUPPORT                _ON

//--------------------------------------------------
// Macro of DAC Control
//--------------------------------------------------
#define bAMP_MUTE_NPCP215                       (MCU_FE1B_PORT73_PIN_REG)

#define _AMP_MUTE_NPCP215_ON                    0
#define _AMP_MUTE_NPCP215_OFF                   1

#define PCB_AMP_MUTE_NPCP215(x)                 {\
                                                    bAMP_MUTE_NPCP215 = (x);\
                                                }
#define PCB_GET_AMP_MUTE_NPCP215()              (bAMP_MUTE_NPCP215)

//--------------------------------------------------
// Macro of DAC Reset
//--------------------------------------------------
#define bAMP_RESET                              (MCU_FE20_PORT80_PIN_REG)

#define _AMP_RESET_ON                           0
#define _AMP_RESET_OFF                          1

#define PCB_AMP_RESET(x)                        {\
                                                    bAMP_RESET = (x);\
                                                }

//--------------------------------------------------
// Macro of AMP POWER Control
//--------------------------------------------------
#define bAMP_POWER                              (MCU_FE2E_PORT96_PIN_REG)

#define _AMP_POWER_ON                           1
#define _AMP_POWER_OFF                          0

#define PCB_AMP_POWER(x)                        {\
                                                    bAMP_POWER = (x);\
                                                }

#define PCB_GET_AMP_POWER()                     (bAMP_POWER)

//--------------------------------------------------
// Macro of AMP POWER 19V Control
//--------------------------------------------------
#define bAMP_POWER_19V                          (MCU_FE2D_PORT95_PIN_REG)
#define _AMP_POWER_19V_ON                       1
#define _AMP_POWER_19V_OFF                      0

#define PCB_AMP_POWER_19V(x)                    {\
                                                    bAMP_POWER_19V = (x);\
                                                }

//--------------------------------------------------
// Macro of AMP LINE OUT Control
//--------------------------------------------------
#define bAMP_MUTE_LINEOUT                       (0) // _PIN_199,GPIO_199_CPU_MUTEN, P9.5

#define _AMP_MUTE_LINEOUT_ON                    1
#define _AMP_MUTE_LINEOUT_OFF                   0

#define PCB_AMP_MUTE_LINEOUT(x)                 {\
                                                }

#define PCB_GET_AMP_MUTE_LINEOUT()              (bAMP_MUTE_LINEOUT)


////////////////////
// Device USB Hub //
////////////////////
#define _DEVICE_USB_HUB_TYPE                    _DEVICE_USB_HUB_02_SMSC_USB2514B// _DEVICE_NONE    //_DEVICE_USB_HUB_01_MACRO


/////////////////
//  USB Macro  //
/////////////////

//-----------------------------------------------
// Macro of PCB Usb Cable Detect
//-----------------------------------------------
#define bUSB_CABLE                              (P3_3)

#define _USB_CONNECTOR_OFF                      0
#define _USB_CONNECTOR_ON                       1

#define PCB_GET_USB_CABLE()                     (bUSB_CABLE)

//-----------------------------------------------
// Macro of PCB Usb Hub Power
//-----------------------------------------------
#define bUSB_HUB_POWER                          (P3_4)

#define _USB_HUB_POWER_ON                       1
#define _USB_HUB_POWER_OFF                      0

#define PCB_USB_HUB_POWER(x)                    {\
                                                    bUSB_HUB_POWER = (x);\
                                                }

#define PCB_GET_USB_HUB_POWER()                 (bUSB_HUB_POWER)

//-----------------------------------------------
// Macro of Dynamic High/Low
//-----------------------------------------------
#define _BACKLIGHT_HIGH_DYNAMIC_ON              1
#define _BACKLIGHT_HIGH_DYNAMIC_OFF             0

#define PCB_BACKLIGHT_HIGH_DYNAMIC(x)           {\
                                                    PCB_BACKLIGHT_POWER(((x) == _BACKLIGHT_HIGH_DYNAMIC_ON) ? _LIGHT_CONTROL_OFF : _LIGHT_CONTROL_ON);\
                                                }

#endif // End of #if(_PCB_TYPE == _RL6410_DEMO_LOCAL_DIMMING_2MHL1DP1mDP)
