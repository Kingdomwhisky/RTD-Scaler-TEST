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
// ID Code      : RL6432_PCB_EXAMPLE_156_PIN_MST.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6432_PCB_EXAMPLE_156_PIN_MST)


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
#define _PCB_DEBUG_DDC                          _VGA_DDC


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                     _D0_NO_PORT
#define _D0_DDC_CHANNEL_SEL                     _NO_DDC
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#define _D0_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE

// For DP
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

// For DP Type-C
#define _D0_DP_TYPE_C_PORT_CTRL_TYPE            _PORT_CONTROLLER_RTS5400_SERIES
#define _D0_DP_TYPE_C_USB_HUB_TYPE              _USB_HUB_RTS5411_SERIES
#define _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR      0xD4
#define _D0_DP_TYPE_C_HUB_SLAVE_ADDR            0xD2
#define _D0_DP_TYPE_C_RTK_PC_SMBUS_IIC          _HW_IIC_PIN_179_180
#define _D0_DP_TYPE_C_PIN_E_AUXPN_SWAP          _SWAP_BY_PORT_CONTROLLER
#define _D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK   _DISCRETE_PORT_CTRL_USE_GPIO
#define _D0_DP_TYPE_C_BILLBOARD_TYPE            _BILLBOARD_HUB

// For DP Repeater
#define _D0_DP_REPEATER_TYPE                    _REPEATER_RTS_TRANSLATOR
#define _D0_DP_REPEATER_SLAVE_ADDR              0x66
#define _D0_DP_REPEATER_IIC                     _HW_IIC_PIN_210_211

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                     _D1_NO_PORT
#define _D1_DDC_CHANNEL_SEL                     _NO_DDC
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#define _D1_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE

// For HDMI MultiEdid
#define _D1_MAX_HDMI_EDID_COUNT                 1

// For DP
#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

// For DP Type-C
#define _D1_DP_TYPE_C_PORT_CTRL_TYPE            _PORT_CONTROLLER_RTS5400_SERIES
#define _D1_DP_TYPE_C_USB_HUB_TYPE              _USB_HUB_RTS5411_SERIES
#define _D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR      0xD4
#define _D1_DP_TYPE_C_HUB_SLAVE_ADDR            0xD2
#define _D1_DP_TYPE_C_RTK_PC_SMBUS_IIC          _HW_IIC_PIN_179_180
#define _D1_DP_TYPE_C_PIN_E_AUXPN_SWAP          _SWAP_BY_PORT_CONTROLLER
#define _D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK   _DISCRETE_PORT_CTRL_USE_GPIO
#define _D1_DP_TYPE_C_BILLBOARD_TYPE            _BILLBOARD_HUB

// For MHL
#define _D1_MHL_VERSION                         _MHL_VERSION_NULL
#define _D1_CBUS_CHANNEL_SEL                    _NO_CBUS
#define _D1_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#define _D1_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                     _D3_NO_PORT
#define _D3_DDC_CHANNEL_SEL                     _NO_DDC
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#define _D3_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE

// For HDMI MultiEdid
#define _D3_MAX_HDMI_EDID_COUNT                 1

// For MHL
#define _D3_MHL_VERSION                         _MHL_VERSION_NULL
#define _D3_CBUS_CHANNEL_SEL                    _NO_CBUS
#define _D3_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#define _D3_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D6 Input Port
//--------------------------------------------------
#define _D6_INPUT_PORT_TYPE                     _D6_NO_PORT
#define _D6_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#define _D6_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For DP
#define _D6_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D6_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D6_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#define _D6_INPUT_PORT_SWITCH_FROM              _SWITCH_NONE

// For DP Type-C
#define _D6_DP_TYPE_C_PORT_CTRL_TYPE            _PORT_CONTROLLER_RTS5400_SERIES
#define _D6_DP_TYPE_C_USB_HUB_TYPE              _USB_HUB_RTS5411_SERIES
#define _D6_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR      0xD4
#define _D6_DP_TYPE_C_HUB_SLAVE_ADDR            0xD2
#define _D6_DP_TYPE_C_RTK_PC_SMBUS_IIC          _HW_IIC_PIN_179_180
#define _D6_DP_TYPE_C_PIN_E_AUXPN_SWAP          _SWAP_BY_PORT_CONTROLLER
#define _D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK   _DISCRETE_PORT_CTRL_USE_GPIO
#define _D6_DP_TYPE_C_BILLBOARD_TYPE            _BILLBOARD_HUB

//--------------------------------------------------
// Digital Signature DDC Channel for HUB ISP
//--------------------------------------------------
#define _CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL     _NO_DDC


/////////////////////////////
// Type-C Config Setting   //
/////////////////////////////

//-------------------------------------------------
// Type-C Support 5400 Spec Version
//-------------------------------------------------
#define _TYPE_C_RTS5400_SERIES_SPEC_VER_SEL     _RTS5400_SERIES_FW_SPEC_VERSION_V0D9

//-------------------------------------------------
// Type-C PDO Information Support
//-------------------------------------------------
#define _TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT _OFF

//--------------------------------------------------
// Arbitration Type Select Between Hub (54xx) And Scaler Chip
//--------------------------------------------------
#define _RTS_SMBUS_ARBITRATION_MODE_SEL         _RTS_SMBUS_ARBITRATION_NONE


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D6_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _NO_INPUT_PORT


///////////////
// TMDS Port //
///////////////

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
#define _D1_TMDS_BR_SWAP                        _ON
#define _D1_TMDS_PN_SWAP                        _ON
#else
#define _D1_TMDS_BR_SWAP                        _OFF
#define _D1_TMDS_PN_SWAP                        _OFF
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
#define _D3_TMDS_BR_SWAP                        _ON
#define _D3_TMDS_PN_SWAP                        _ON
#else
#define _D3_TMDS_BR_SWAP                        _OFF
#define _D3_TMDS_PN_SWAP                        _OFF
#endif


/////////////
// DP Port //
/////////////

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

#define _DPTX_PCB_LANE0_MAPPING                 _DP_SCALER_LANE0
#define _DPTX_PCB_LANE1_MAPPING                 _DP_SCALER_LANE1
#define _DPTX_PCB_LANE2_MAPPING                 _DP_SCALER_LANE2
#define _DPTX_PCB_LANE3_MAPPING                 _DP_SCALER_LANE3
#define _DPTX_PCB_LANE0_PN_SWAP                 _OFF
#define _DPTX_PCB_LANE1_PN_SWAP                 _OFF
#define _DPTX_PCB_LANE2_PN_SWAP                 _OFF
#define _DPTX_PCB_LANE3_PN_SWAP                 _OFF


//////////////
// MHL Port //
//////////////

//--------------------------------------------------
// MHL CBUS Output High Voltage Level
//--------------------------------------------------
#define _MHL_CBUS_LDO_HIGH                      _DISABLE


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#define _LVDS_PORT_SEL                          _LVDS_2_PORT_AB
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#define _LVDS_RB_SWAP                           _DISABLE
#define _LVDS_ML_SWAP                           _DISABLE
#define _LVDS_DVS_INVERT                        _DISABLE
#define _LVDS_DHS_INVERT                        _DISABLE
#define _LVDS_DEN_INVERT                        _DISABLE
#define _LVDS_PAIR_MIRROR                       _DISABLE

#define _LVDS_CLK_CHANNEL_SEL                   _NORMAL_MODE           /// Display CLK Pair Position Selection: TXK = A / B / C / D / E / F / G / H port
                                                                       /// Normal mode: TXKCK1 as CLK for 8bit / 10bit
                                                                       /// Mode1:       TXK1   as CLK for 8bit / 10bit
                                                                       /// Mode2:       TXK2   as CLK for 8bit / 10bit
                                                                       /// Mode3:       TXKCK1 as CLK for 8bit
                                                                       ///              TXK3   as CLK for        10bit

//--------------------------------------------------
// LVDS Port AB Phase Selection
//--------------------------------------------------
#define _LVDS_A0_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A1_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A2_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_AC_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A3_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A4_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B0_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B1_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B2_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_BC_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B3_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B4_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_PI_PHASE_AB0_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB1_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB2_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB3_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Port CD Phase Selection
//--------------------------------------------------
#define _LVDS_C0_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C1_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C2_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_CC_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C3_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C4_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D0_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D1_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D2_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_DC_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D3_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D4_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_PI_PHASE_CD0_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD1_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD2_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD3_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL                      _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL               _DISABLE
#define _LVDS_VCM_USER_LEVEL                    0x0C

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                      10                     // 0~15, 0 ~ disable, 15 ~ 7.50%
#define _LVDS_SPREAD_SPEED                      _SPEED_33K


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_LANE_SWAP               _DISABLE               // Lane Port Swap
#define _PANEL_DPTX_1_1_LANE_PN_SWAP            _DISABLE               // Lane PN Swap
#define _PANEL_DPTX_1_1_SWING_LEVEL             _DP_SWING_800_MV       // Swing Level = 400,600,800,1200mV
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB   // Preemphasis Level = 0,3.5,6,9.5dB

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_SPREAD_RANGE            5                      // 0~15, 0 ~ disable, 15 ~ 0.98%
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K             // _SPEED_30K or _SPEED_33K


////////////////////////////
// eDPTx Panel AUX Config //
////////////////////////////

//--------------------------------------------------
// eDPTx AUX Swing Level
//--------------------------------------------------
#define _PANEL_DPTX_AUX_SWING_LEVEL             _DP_AUX_SWING_1050_MV


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT

#define _BACKLIGHT_PWM                          _NO_PWM
#define _BACKLIGHT_PWM_INVERSE                  _OFF

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF
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
#define _PWM2_RST_EN                            _OFF
#define _PWM3_RST_EN                            _OFF
#define _PWM4_RST_EN                            _OFF
#define _PWM5_RST_EN                            _OFF
#define _PWM_RST_SIGNAL_SEL                     _DVS

#define _PWM_FREQ_DVSRST_CHECK                  _ON


//////////
// TCON //
//////////

//--------------------------------------------------
// MBR TCON Pin Setting
//--------------------------------------------------
#define _PCB_MBR_TCON_PIN                       _TCON10

//--------------------------------------------------
// MBR Driver IC Max Frequency (unit: kHz)
//--------------------------------------------------
#define _PCB_MBR_DRIVER_IC_MAX_FREQ             20


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                         _OFF
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _OFF
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K
#define _HW_IIC_PAR_BY_USER_SUPPORT             _OFF


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _NO_IIC_PIN


////////////////////////////
// Second External Eeprom //
////////////////////////////

//--------------------------------------------------
// Second External Eeprom Data Storage Option
//--------------------------------------------------
#define _SEC_EEPROM_TYPE                        _EEPROM_CAT24M01
#define _SEC_EEPROM_SLAVE_ADDRESS               0xA0
#define _PCB_SEC_EEPROM_IIC                     _NO_IIC_PIN


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#define _AD_KEY_SUPPORT                         _OFF

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#define _LOW_SPEED_ADC_SUPPORT                  _OFF

//--------------------------------------------------
// Flash Latch Edge Option
//--------------------------------------------------
#define _PCB_FLASH_LATCH_SO_DATA_IN_RISING_EDGE _OFF

//--------------------------------------------------
// FLASH SPI Control Option
//--------------------------------------------------
#define _FLASH_CLK_DRIVE_CURRENT                _SPI_DRIVE_4_0MA
#define _FLASH_SI_SO_CEB_DRIVE_CURRENT          _SPI_DRIVE_4_0MA
#define _FLASH_CLK_SLEW_RATE_CONTROL            _SPI_FAST_SLEW_RATE
#define _FLASH_SI_SO_CEB_SLEW_RATE_CONTROL      _SPI_FAST_SLEW_RATE


/////////////////////
// Pinshare series //
/////////////////////
#include "RL6432_PCB_EXAMPLE_156_PIN_MST_PINSHARE.h"


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
#define bVCCKOFFPOWER                           (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0
#define _VCCK_OFF_TIME_POLLING_POWER_ON         20 // ms

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of VcckOff Poewr Release Time Control
//-----------------------------------------------
#define _VCCKOFF_POWER_OFF_TIME                 200

//-----------------------------------------------
// Macro of Power Board Low Power Pin High/Low
//-----------------------------------------------
#define bPOWERBOARDPOWER                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _LOW_POWER_ON                           1
#define _LOW_POWER_OFF                          0

#define PCB_POWERBOARD_LOWPOWER(x)              {\
                                                    bPOWERBOARDPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of Repeater Power & External Port Controller Control
//-----------------------------------------------
#define bTWOCHIPREPEATER_POWERCTL               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bTWOCHIPPORTCTRL_POWERCTL               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _TWO_CHIP_REPEATER_POWER_ON             1
#define _TWO_CHIP_REPEATER_POWER_OFF            0

#define _TWO_CHIP_PORT_CTRL_POWER_ON            1
#define _TWO_CHIP_PORT_CTRL_POWER_OFF           0

#define GET_PCB_TWO_CHIP_REPEATER_POW_STATUS()  (bTWOCHIPREPEATER_POWERCTL)

#define PCB_TWO_CHIP_REPEATER_POW(x)            {\
                                                    bTWOCHIPREPEATER_POWERCTL = (x);\
                                                }

#define GET_PCB_TWO_CHIP_PORT_CTRL_POW_STATUS() (bTWOCHIPPORTCTRL_POWERCTL)

#define PCB_TWO_CHIP_PORT_CTRL_POW(x)           {\
                                                    bTWOCHIPPORTCTRL_POWERCTL = (x);\
                                                }

//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#define bREGULATOR_5V                           (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _REGULATOR_5V_ON                        0
#define _REGULATOR_5V_OFF                       1

#define PCB_REGULATOR_5V_OUT(x)                 {\
                                                    bREGULATOR_5V = (x);\
                                                }


////////////////////
// DP Power Macro //
////////////////////

//-----------------------------------------------
// Macro of MyDP Power Control
//-----------------------------------------------
#define bD0_MYDP_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_MYDP_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_MYDP_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _MYDP_5V_POWER_ON                       1
#define _MYDP_5V_POWER_OFF                      0

#define PCB_D0_MYDP_POWER(x)                    {\
                                                    bD0_MYDP_POWER = (x);\
                                                }

#define PCB_D1_MYDP_POWER(x)                    {\
                                                    bD1_MYDP_POWER = (x);\
                                                }

#define PCB_D6_MYDP_POWER(x)                    {\
                                                    bD6_MYDP_POWER = (x);\
                                                }

//-----------------------------------------------
// Macro of DP1.2 Power Control
//-----------------------------------------------
#define bD0_DP12_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_DP12_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_DP12_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DP12_33V_POWER_ON                      1
#define _DP12_33V_POWER_OFF                     0

#define PCB_D0_DP12_POWER(x)                    {\
                                                    bD0_DP12_POWER = (x);\
                                                }

#define PCB_D1_DP12_POWER(x)                    {\
                                                    bD1_DP12_POWER = (x);\
                                                }

#define PCB_D6_DP12_POWER(x)                    {\
                                                    bD6_DP12_POWER = (x);\
                                                }

//-----------------------------------------------
// Macro of MyDP & DP1.2 Power Select
//-----------------------------------------------
#define bD0_D12_MYDP_SEL                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_D12_MYDP_SEL                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_D12_MYDP_SEL                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DP12_33V_POWER                         0
#define _MYDP_5V_POWER                          1

#define PCB_D0_DP12_MYDP_POWER_SELECT(x)        {\
                                                    bD0_D12_MYDP_SEL = (x);\
                                                }

#define PCB_D1_DP12_MYDP_POWER_SELECT(x)        {\
                                                    bD1_D12_MYDP_SEL = (x);\
                                                }

#define PCB_D6_DP12_MYDP_POWER_SELECT(x)        {\
                                                    bD6_D12_MYDP_SEL = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define bPANELPOWER                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define bBACKLIGHTPOWER                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _LIGHT_CONTROL_ON                       0
#define _LIGHT_CONTROL_OFF                      1

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    bBACKLIGHTPOWER = (x);\
                                                }

#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, (((DWORD)_PANEL_TYP_FRAME_RATE * 60) / 100));\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }


//////////////////////////////////////
// eDPTx Panel Power Sequence Macro //
//////////////////////////////////////

//--------------------------------------------------
// eDPTx 1.1 Panel Power Sequence Macro
//--------------------------------------------------
#define PCB_DPTX1_POWER_SEQUENCE(x)             {\
                                                }


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0


#define PCB_D1_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of HDMI External EDID Switch : #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//-----------------------------------------------
#define bD1_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _EEPROM_EDID_ENABLE                     0
#define _EEPROM_EDID_DISABLE                    1

#define PCB_MULTI_EDID_ALL_SWITCH_OFF(port)     {\
                                                }

#define PCB_MULTI_EDID_SWITCH(port, index)      {\
                                                }

#define PCB_MULTI_EDID_SWITCH_POWER_AC_ON()     {\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD0_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD0_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD0_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD1_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD6_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

// For DP Type-C
#define bD0_USB_TYPE_C_AUXP_CONNECT             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD0_USB_TYPE_C_AUXN_CONNECT             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD1_USB_TYPE_C_AUXP_CONNECT             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_USB_TYPE_C_AUXN_CONNECT             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD6_USB_TYPE_C_AUXP_CONNECT             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_USB_TYPE_C_AUXN_CONNECT             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)


#define bD0_CONNECT                             (((bit)bD0_DP_PIN15_CONNECT == _TRUE) && ((bit)bD0_DP_PIN16_CONNECT == _TRUE) && ((bit)bD0_DP_PIN17_CONNECT == _FALSE))
#define bD1_CONNECT                             (((bit)bD1_DP_PIN15_CONNECT == _TRUE) && ((bit)bD1_DP_PIN16_CONNECT == _TRUE) && ((bit)bD1_DP_PIN17_CONNECT == _FALSE))
#define bD3_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_CONNECT                             (((bit)bD6_DP_PIN15_CONNECT == _TRUE) && ((bit)bD6_DP_PIN16_CONNECT == _TRUE) && ((bit)bD6_DP_PIN17_CONNECT == _FALSE))

// For DP Type-C
#define bD0_CONNECT                             (((bit)bD0_USB_TYPE_C_AUXP_CONNECT == _TRUE) && ((bit)bD0_USB_TYPE_C_AUXN_CONNECT == _FALSE))
#define bD1_CONNECT                             (((bit)bD1_USB_TYPE_C_AUXP_CONNECT == _TRUE) && ((bit)bD1_USB_TYPE_C_AUXN_CONNECT == _FALSE))
#define bD6_CONNECT                             (((bit)bD6_USB_TYPE_C_AUXP_CONNECT == _TRUE) && ((bit)bD6_USB_TYPE_C_AUXN_CONNECT == _FALSE))

#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D1_PIN()                            (bD1_CONNECT)
#define PCB_D3_PIN()                            (bD3_CONNECT)
#define PCB_D6_PIN()                            (bD6_CONNECT)

//-----------------------------------------------
// Macro of DP Type-C Ext Port Controller Detect By GPIO
//-----------------------------------------------
#define bD0_CCATTACH                            (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define PCB_D0_CC_ATTACH_PIN()                  (bD0_CCATTACH)

#define bD0_ALTMODE                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define PCB_D0_ALT_MODE_PIN()                   (bD0_ALTMODE)

#define bD1_CCATTACH                            (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define PCB_D1_CC_ATTACH_PIN()                  (bD1_CCATTACH)

#define bD1_ALTMODE                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define PCB_D1_ALT_MODE_PIN()                   (bD1_ALTMODE)

#define bD6_CCATTACH                            (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define PCB_D6_CC_ATTACH_PIN()                  (bD6_CCATTACH)

#define bD6_ALTMODE                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define PCB_D6_ALT_MODE_PIN()                   (bD6_ALTMODE)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)
#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_DP_PIN17_CONNECT)
#define GET_PCB_D6_DP_SOURCE_POWER()            (bD6_DP_PIN17_CONNECT)

// For DP Type-C
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_USB_TYPE_C_AUXN_CONNECT)
#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_USB_TYPE_C_AUXN_CONNECT)
#define GET_PCB_D6_DP_SOURCE_POWER()            (bD6_USB_TYPE_C_AUXN_CONNECT)

// For DP Source Power When under Pin E Type and Aux PN Swap
#define GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP()    (bD0_USB_TYPE_C_AUXP_CONNECT)
#define GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP()    (bD1_USB_TYPE_C_AUXP_CONNECT)
#define GET_PCB_D6_DP_SOURCE_POWER_PN_SWAP()    (bD6_USB_TYPE_C_AUXP_CONNECT)

//-----------------------------------------------
// Aux PN 1M Pull High / low Swap Control
//-----------------------------------------------
#define bD0_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN      (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN      (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN      (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _AUX_PN_1M_PULL_HI_LOW_SWAP_ON          1
#define _AUX_PN_1M_PULL_HI_LOW_SWAP_OFF         0

#define PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(x)       {\
                                                    bD0_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN = (x);\
                                                }

#define PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(x)       {\
                                                    bD1_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN = (x);\
                                                }

#define PCB_D6_AUX_PN_1M_PULL_H_L_SWAP(x)       {\
                                                    bD6_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN = (x);\
                                                }

#define PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP()    (bD0_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN)
#define PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP()    (bD1_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN)
#define PCB_GET_D6_AUX_PN_1M_PULL_H_L_SWAP()    (bD6_AUX_PN_1M_PULL_HI_LOW_SWAP_PIN)

//-----------------------------------------------
// Macro of MHL Cable Connect
//-----------------------------------------------
#define bD1_MHL_CONNECT                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_MHL_CONNECT                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_D1_MHL_DETECT()                     (bD1_MHL_CONNECT)
#define PCB_D3_MHL_DETECT()                     (bD3_MHL_CONNECT)


/////////////////////////////////////////
// RTS 5400 Series SMBUS Arbit Control //
/////////////////////////////////////////

//---------------------------------------------------
// SMBus Communication Arbitration Setting
//---------------------------------------------------
#define bRTS_SMBUS_ARBITRATION_PIN              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _RTS_SMBUS_IDLE                         0
#define _RTS_SMBUS_BUSY                         1

#define PCB_CHECK_RTS_SMBUS_BUSY_STATUS(x)      {\
                                                    ScalerPinshareAdjustConfig(_PIN_1, _GPI);\
                                                    (x) = bRTS_SMBUS_ARBITRATION_PIN;\
                                                }

#define PCB_SET_RTS_SMBUS_BUSY()                {\
                                                    ScalerPinshareAdjustConfig(_PIN_1, _GPO_PP);\
                                                    bRTS_SMBUS_ARBITRATION_PIN = _RTS_SMBUS_BUSY;\
                                                }

#define PCB_RELEASE_RTS_SMBUS_BUSY()            {\
                                                    ScalerPinshareAdjustConfig(_PIN_1, _GPO_PP);\
                                                    bRTS_SMBUS_ARBITRATION_PIN = _RTS_SMBUS_IDLE;\
                                                    ScalerPinshareAdjustConfig(_PIN_1, _GPI);\
                                                }


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define bD0_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _D0_HOT_PLUG_HIGH                       1
#define _D0_HOT_PLUG_LOW                        0

#define _D1_HOT_PLUG_HIGH                       1
#define _D1_HOT_PLUG_LOW                        0

#define _D3_HOT_PLUG_HIGH                       1
#define _D3_HOT_PLUG_LOW                        0

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


//////////////////////////////////////
// DP D0 & D6 External Switch Macro //
//////////////////////////////////////

//-----------------------------------------------
// Macro of D6 Switch Power
//-----------------------------------------------
#define bDIGITAL_D6_SWITCH_POWER                (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DIGITAL_D6_SWITCH_POWER_ON             1
#define _DIGITAL_D6_SWITCH_POWER_DOWN           0

#define PCB_DIGITAL_D6_SWITCH_POWER(x)          {\
                                                    bDIGITAL_D6_SWITCH_POWER = (x);\
                                                }

//-----------------------------------------------
// Macro of D6 Switch Lane & Aux_HPD Macro
//-----------------------------------------------
#define bDIGITAL_D6_SWITCH_LANE                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bDIGITAL_D6_SWITCH_AUX_HPD              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DP_D0_D6_SWITCH_D0                     1
#define _DP_D0_D6_SWITCH_D6                     0

#define PCB_DIGITAL_D0_D6_SWITCH_LANE(x)        {\
                                                    bDIGITAL_D6_SWITCH_LANE = (x);\
                                                }

#define PCB_DIGITAL_D0_D6_SWITCH_AUX_HPD(x)     {\
                                                    bDIGITAL_D6_SWITCH_AUX_HPD = (x);\
                                                }


///////////////
// MHL Macro //
///////////////

//-----------------------------------------------
// Macro of HDMI/MHL Switch
//-----------------------------------------------
#define bD1_TMDS_SWITCH                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_TMDS_SWITCH                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _TMDS_SWITCH_MHL_CBUS                   0
#define _TMDS_SWITCH_HDMI_HPD                   1

#define PCB_D1_HDMI_MHL_SWITCH(x)               {\
                                                    bD1_TMDS_SWITCH = (x);\
                                                }

#define PCB_D3_HDMI_MHL_SWITCH(x)               {\
                                                    bD3_TMDS_SWITCH = (x);\
                                                }

//-----------------------------------------------
// Macro of MHL VBus Switch
//-----------------------------------------------
#define bD1_MHL_VBUS_SWITCH                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_MHL_VBUS_SWITCH                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _MHL_VBUS_ON                            1
#define _MHL_VBUS_OFF                           0

#define PCB_D1_MHL_VBUS_SWITCH(x)               {\
                                                    bD1_MHL_VBUS_SWITCH = (x);\
                                                    PCB_MHL_VBUS_POWER(x);\
                                                }

#define PCB_D3_MHL_VBUS_SWITCH(x)               {\
                                                    bD3_MHL_VBUS_SWITCH = (x);\
                                                    PCB_MHL_VBUS_POWER(x);\
                                                }

#define PCB_GET_D1_MHL_VBUS_SWITCH()            (bD1_MHL_VBUS_SWITCH)
#define PCB_GET_D3_MHL_VBUS_SWITCH()            (bD3_MHL_VBUS_SWITCH)

//-----------------------------------------------
// Macro of MHL VBUS 5V Power Control
//-----------------------------------------------
#define PCB_MHL_VBUS_POWER(x)                   {\
                                                    if((x) == _MHL_VBUS_ON)\
                                                    {\
                                                        PCB_REGULATOR_5V_OUT(_REGULATOR_5V_ON);\
                                                    }\
                                                    else\
                                                    {\
                                                        if(ScalerSyncMHLVBusPowerExist() == _FALSE)\
                                                        {\
                                                            PCB_REGULATOR_5V_OUT(_REGULATOR_5V_OFF);\
                                                        }\
                                                    }\
                                                }


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
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


//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define bSWIIC_SYS_EEPROM_SCL                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_SYS_EEPROM_SDA                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

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
#define bLED1                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLED2                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _LED_ON                                 1
#define _LED_OFF                                0

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                }

#define PCB_LED_IDLE()                          {\
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
#define AD_KEY0                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define AD_KEY1                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define AD_KEY2                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define AD_KEY3                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_ADKEY0()                            (_FALSE)
#define PCB_ADKEY1()                            (_FALSE)
#define PCB_ADKEY2()                            (_FALSE)
#define PCB_ADKEY3()                            (_FALSE)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }


////////////////////
// GPIO Key Macro //
////////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define bPOWER_KEY                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bMENU_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bEXIT_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLEFT_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bRIGHT_KEY                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }


/////////////////
// Audio Macro //
/////////////////

//-----------------------------------------------
// Macro of PCB Audio Connect
//-----------------------------------------------
#define bAudioDetect                            (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _AUDIO_CONNECT                          0
#define _AUDIO_DISCONNECT                       1

#define PCB_AUDIO_DETECT()                      (bAudioDetect)

//-----------------------------------------------
// Macro of PCB Audio AMP Control
//-----------------------------------------------
#define bPCBAMPMUTECONTROL                      (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _AMP_MUTE_ON                            0
#define _AMP_MUTE_OFF                           1

#define PCB_AMP_MUTE(x)                         {\
                                                    bPCBAMPMUTECONTROL = (x);\
                                                }

#endif // End of #if(_PCB_TYPE == _RL6432_PCB_EXAMPLE_156_PIN)
