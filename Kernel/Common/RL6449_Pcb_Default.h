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
// ID Code      : RL6449_Pcb_Default.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#ifndef _EXT_XTAL
#define _EXT_XTAL                               _XTAL14318K
#endif


///////////////
// Debug DDC //
///////////////

//--------------------------------------------------
// Debug DDC Channel
//--------------------------------------------------
#ifndef _PCB_DEBUG_DDC
#define _PCB_DEBUG_DDC                          _VGA_DDC
#endif


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#ifndef _A0_INPUT_PORT_TYPE
#define _A0_INPUT_PORT_TYPE                     _A0_NO_PORT
#endif

#ifndef _A0_EMBEDDED_DDCRAM_MAX_SIZE
#define _A0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#endif

#ifndef _A0_EMBEDDED_DDCRAM_LOCATION
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _A0_CODE_DIGITAL_SIGNATURE_ISP_EN
#define _A0_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE
#endif

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#ifndef _D0_INPUT_PORT_TYPE
#define _D0_INPUT_PORT_TYPE                     _D0_NO_PORT
#endif

#ifndef _D0_DDC_CHANNEL_SEL
#define _D0_DDC_CHANNEL_SEL                     _NO_DDC
#endif

#ifndef _D0_EMBEDDED_DDCRAM_MAX_SIZE
#define _D0_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#endif

#ifndef _D0_EMBEDDED_DDCRAM_LOCATION
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D0_CODE_DIGITAL_SIGNATURE_ISP_EN
#define _D0_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE
#endif

#ifndef _D0_DP_CONNECTOR_TYPE
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#endif

#ifndef _D0_DP_LINK_CLK_RATE
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#endif

#ifndef _D0_DP_MAIN_LINK_LANES
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#endif

#ifndef _D0_DP_TYPE_C_PORT_CTRL_TYPE
#define _D0_DP_TYPE_C_PORT_CTRL_TYPE            _PORT_CONTROLLER_NONE
#endif

#ifndef _D0_DP_TYPE_C_USB_HUB_TYPE
#define _D0_DP_TYPE_C_USB_HUB_TYPE              _USB_HUB_NONE
#endif

#ifndef _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR
#define _D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR      0xD4
#endif

#ifndef _D0_DP_TYPE_C_HUB_SLAVE_ADDR
#define _D0_DP_TYPE_C_HUB_SLAVE_ADDR            0x00
#endif

#ifndef _D0_DP_TYPE_C_RTK_PC_SMBUS_IIC
#define _D0_DP_TYPE_C_RTK_PC_SMBUS_IIC          _NO_IIC_PIN
#endif

#ifndef _D0_DP_TYPE_C_PIN_E_AUXPN_SWAP
#define _D0_DP_TYPE_C_PIN_E_AUXPN_SWAP          _SWAP_BY_SCALER
#endif

#ifndef _D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK
#define _D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK   _DISCRETE_PORT_CTRL_NOT_EXIST
#endif

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#ifndef _D1_INPUT_PORT_TYPE
#define _D1_INPUT_PORT_TYPE                     _D1_NO_PORT
#endif

#ifndef _D1_DDC_CHANNEL_SEL
#define _D1_DDC_CHANNEL_SEL                     _NO_DDC
#endif

#ifndef _D1_EMBEDDED_DDCRAM_MAX_SIZE
#define _D1_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#endif

#ifndef _D1_EMBEDDED_DDCRAM_LOCATION
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D1_CODE_DIGITAL_SIGNATURE_ISP_EN
#define _D1_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE
#endif

#ifndef _D1_DP_CONNECTOR_TYPE
#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#endif

#ifndef _D1_DP_LINK_CLK_RATE
#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#endif

#ifndef _D1_DP_MAIN_LINK_LANES
#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#endif

#ifndef _D1_DP_TYPE_C_PORT_CTRL_TYPE
#define _D1_DP_TYPE_C_PORT_CTRL_TYPE            _PORT_CONTROLLER_NONE
#endif

#ifndef _D1_DP_TYPE_C_USB_HUB_TYPE
#define _D1_DP_TYPE_C_USB_HUB_TYPE              _USB_HUB_NONE
#endif

#ifndef _D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR
#define _D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR      0xD4
#endif

#ifndef _D1_DP_TYPE_C_HUB_SLAVE_ADDR
#define _D1_DP_TYPE_C_HUB_SLAVE_ADDR            0x00
#endif

#ifndef _D1_DP_TYPE_C_RTK_PC_SMBUS_IIC
#define _D1_DP_TYPE_C_RTK_PC_SMBUS_IIC          _NO_IIC_PIN
#endif

#ifndef _D1_DP_TYPE_C_PIN_E_AUXPN_SWAP
#define _D1_DP_TYPE_C_PIN_E_AUXPN_SWAP          _SWAP_BY_SCALER
#endif

#ifndef _D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK
#define _D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK   _DISCRETE_PORT_CTRL_NOT_EXIST
#endif

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#ifndef _D2_INPUT_PORT_TYPE
#define _D2_INPUT_PORT_TYPE                     _D2_NO_PORT
#endif

#ifndef _D2_DDC_CHANNEL_SEL
#define _D2_DDC_CHANNEL_SEL                     _NO_DDC
#endif

#ifndef _D2_EMBEDDED_DDCRAM_MAX_SIZE
#define _D2_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#endif

#ifndef _D2_EMBEDDED_DDCRAM_LOCATION
#define _D2_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D2_HDMI_CEC_PIN
#define _D2_HDMI_CEC_PIN                        _HDMI_CEC_NONE
#endif

#ifndef _D2_CODE_DIGITAL_SIGNATURE_ISP_EN
#define _D2_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE
#endif

#ifndef _D2_MAX_HDMI_EDID_COUNT
#define _D2_MAX_HDMI_EDID_COUNT                 1
#endif

#ifndef _D2_MHL_VERSION
#define _D2_MHL_VERSION                         _MHL_VERSION_NULL
#endif

#ifndef _D2_CBUS_CHANNEL_SEL
#define _D2_CBUS_CHANNEL_SEL                    _NO_CBUS
#endif

#ifndef _D2_MHL_EMBEDDED_DDCRAM_SIZE
#define _D2_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#endif

#ifndef _D2_MHL_EMBEDDED_DDCRAM_LOCATION
#define _D2_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE
#endif

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#ifndef _D3_INPUT_PORT_TYPE
#define _D3_INPUT_PORT_TYPE                     _D3_NO_PORT
#endif

#ifndef _D3_DDC_CHANNEL_SEL
#define _D3_DDC_CHANNEL_SEL                     _NO_DDC
#endif

#ifndef _D3_EMBEDDED_DDCRAM_MAX_SIZE
#define _D3_EMBEDDED_DDCRAM_MAX_SIZE            _EDID_SIZE_NONE
#endif

#ifndef _D3_EMBEDDED_DDCRAM_LOCATION
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#endif

#ifndef _D3_HDMI_CEC_PIN
#define _D3_HDMI_CEC_PIN                        _HDMI_CEC_NONE
#endif

#ifndef _D3_CODE_DIGITAL_SIGNATURE_ISP_EN
#define _D3_CODE_DIGITAL_SIGNATURE_ISP_EN       _DISABLE
#endif

#ifndef _D3_MAX_HDMI_EDID_COUNT
#define _D3_MAX_HDMI_EDID_COUNT                 1
#endif

#ifndef _D3_MHL_VERSION
#define _D3_MHL_VERSION                         _MHL_VERSION_NULL
#endif

#ifndef _D3_CBUS_CHANNEL_SEL
#define _D3_CBUS_CHANNEL_SEL                    _NO_CBUS
#endif

#ifndef _D3_MHL_EMBEDDED_DDCRAM_SIZE
#define _D3_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#endif

#ifndef _D3_MHL_EMBEDDED_DDCRAM_LOCATION
#define _D3_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE
#endif

//--------------------------------------------------
// Digital Signature DDC Channel for HUB ISP
//--------------------------------------------------
#ifndef _CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL
#define _CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL     _NO_DDC
#endif


/////////////////////////////
// Type-C Config Setting   //
/////////////////////////////

//-------------------------------------------------
// Type-C Support 5400 Spec Version
//-------------------------------------------------
#ifndef _TYPE_C_RTS5400_SERIES_SPEC_VER_SEL
#define _TYPE_C_RTS5400_SERIES_SPEC_VER_SEL     _RTS5400_SERIES_FW_SPEC_VERSION_V0D9
#endif

//-------------------------------------------------
// Type-C PDO Information Support
//-------------------------------------------------
#ifndef _TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT
#define _TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT _OFF
#endif

//--------------------------------------------------
// Arbitration Type Select Between Hub (54xx) And Scaler Chip
//--------------------------------------------------
#ifndef _RTS_SMBUS_ARBITRATION_MODE_SEL
#define _RTS_SMBUS_ARBITRATION_MODE_SEL         _RTS_SMBUS_ARBITRATION_NONE
#endif


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#ifndef _A0_INPUT_PORT_GROUP
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D0_INPUT_PORT_GROUP
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D1_INPUT_PORT_GROUP
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D2_INPUT_PORT_GROUP
#define _D2_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#endif

#ifndef _D3_INPUT_PORT_GROUP
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#endif

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#ifndef _INPUT_PORT_SEARCH_PRI_0
#define _INPUT_PORT_SEARCH_PRI_0                _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_1
#define _INPUT_PORT_SEARCH_PRI_1                _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_2
#define _INPUT_PORT_SEARCH_PRI_2                _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_3
#define _INPUT_PORT_SEARCH_PRI_3                _NO_INPUT_PORT
#endif

#ifndef _INPUT_PORT_SEARCH_PRI_4
#define _INPUT_PORT_SEARCH_PRI_4                _NO_INPUT_PORT
#endif


//////////////
// VGA Port //
//////////////

//--------------------------------------------------
// Analog Signal Swap Options
//--------------------------------------------------
#ifndef _VGA_INPUT_SWAP_RG
#define _VGA_INPUT_SWAP_RG                      _OFF
#endif

#ifndef _VGA_INPUT_SWAP_RB
#define _VGA_INPUT_SWAP_RB                      _OFF
#endif

#ifndef _VGA_INPUT_SWAP_GB
#define _VGA_INPUT_SWAP_GB                      _OFF
#endif

//--------------------------------------------------
// Analog Hsync Schmitt Trigger Control
//--------------------------------------------------
#ifndef _VGA_HS_SCHMITT_TRIGGER_POLARITY_SEL
#define _VGA_HS_SCHMITT_TRIGGER_POLARITY_SEL    _POSITIVE
#endif

#ifndef _VGA_HS_SCHMITT_TRIGGER_VTH_FINE_TUNE
#define _VGA_HS_SCHMITT_TRIGGER_VTH_FINE_TUNE   _DISABLE
#endif

#ifndef _VGA_HS_SCHMITT_TRIGGER_POSITIVE_VTH
#define _VGA_HS_SCHMITT_TRIGGER_POSITIVE_VTH    _HS_SCHMITT_TRIGGER_LEVEL_10
#endif

#ifndef _VGA_HS_SCHMITT_TRIGGER_NEGATIVE_VTH
#define _VGA_HS_SCHMITT_TRIGGER_NEGATIVE_VTH    _HS_SCHMITT_TRIGGER_LEVEL_01
#endif


///////////////
// TMDS Port //
///////////////

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))

#ifndef _D2_TMDS_BR_SWAP
#define _D2_TMDS_BR_SWAP                        _ON
#endif
#ifndef _D2_TMDS_PN_SWAP
#define _D2_TMDS_PN_SWAP                        _ON
#endif

#else

#ifndef _D2_TMDS_BR_SWAP
#define _D2_TMDS_BR_SWAP                        _OFF
#endif
#ifndef _D2_TMDS_PN_SWAP
#define _D2_TMDS_PN_SWAP                        _OFF
#endif

#endif // End of #if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))

#ifndef _D3_TMDS_BR_SWAP
#define _D3_TMDS_BR_SWAP                        _ON
#endif
#ifndef _D3_TMDS_PN_SWAP
#define _D3_TMDS_PN_SWAP                        _ON
#endif

#else

#ifndef _D3_TMDS_BR_SWAP
#define _D3_TMDS_BR_SWAP                        _OFF
#endif
#ifndef _D3_TMDS_PN_SWAP
#define _D3_TMDS_PN_SWAP                        _OFF
#endif

#endif // End of #if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))


/////////////
// DP Port //
/////////////

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#ifndef _D0_DP_PCB_LANE0_MAPPING
#define _D0_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#endif

#ifndef _D0_DP_PCB_LANE1_MAPPING
#define _D0_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#endif

#ifndef _D0_DP_PCB_LANE2_MAPPING
#define _D0_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#endif

#ifndef _D0_DP_PCB_LANE3_MAPPING
#define _D0_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#endif

#ifndef _D0_DP_PCB_LANE0_PN_SWAP
#define _D0_DP_PCB_LANE0_PN_SWAP                _OFF
#endif

#ifndef _D0_DP_PCB_LANE1_PN_SWAP
#define _D0_DP_PCB_LANE1_PN_SWAP                _OFF
#endif

#ifndef _D0_DP_PCB_LANE2_PN_SWAP
#define _D0_DP_PCB_LANE2_PN_SWAP                _OFF
#endif

#ifndef _D0_DP_PCB_LANE3_PN_SWAP
#define _D0_DP_PCB_LANE3_PN_SWAP                _OFF
#endif

#ifndef _D1_DP_PCB_LANE0_MAPPING
#define _D1_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#endif

#ifndef _D1_DP_PCB_LANE1_MAPPING
#define _D1_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#endif

#ifndef _D1_DP_PCB_LANE2_MAPPING
#define _D1_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#endif

#ifndef _D1_DP_PCB_LANE3_MAPPING
#define _D1_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#endif

#ifndef _D1_DP_PCB_LANE0_PN_SWAP
#define _D1_DP_PCB_LANE0_PN_SWAP                _OFF
#endif

#ifndef _D1_DP_PCB_LANE1_PN_SWAP
#define _D1_DP_PCB_LANE1_PN_SWAP                _OFF
#endif

#ifndef _D1_DP_PCB_LANE2_PN_SWAP
#define _D1_DP_PCB_LANE2_PN_SWAP                _OFF
#endif

#ifndef _D1_DP_PCB_LANE3_PN_SWAP
#define _D1_DP_PCB_LANE3_PN_SWAP                _OFF
#endif

#ifndef _DPTX_PCB_LANE0_MAPPING
#define _DPTX_PCB_LANE0_MAPPING                 _DP_SCALER_LANE0
#endif

#ifndef _DPTX_PCB_LANE1_MAPPING
#define _DPTX_PCB_LANE1_MAPPING                 _DP_SCALER_LANE1
#endif

#ifndef _DPTX_PCB_LANE2_MAPPING
#define _DPTX_PCB_LANE2_MAPPING                 _DP_SCALER_LANE2
#endif

#ifndef _DPTX_PCB_LANE3_MAPPING
#define _DPTX_PCB_LANE3_MAPPING                 _DP_SCALER_LANE3
#endif

#ifndef _DPTX_PCB_LANE0_PN_SWAP
#define _DPTX_PCB_LANE0_PN_SWAP                 _OFF
#endif

#ifndef _DPTX_PCB_LANE1_PN_SWAP
#define _DPTX_PCB_LANE1_PN_SWAP                 _OFF
#endif

#ifndef _DPTX_PCB_LANE2_PN_SWAP
#define _DPTX_PCB_LANE2_PN_SWAP                 _OFF
#endif

#ifndef _DPTX_PCB_LANE3_PN_SWAP
#define _DPTX_PCB_LANE3_PN_SWAP                 _OFF
#endif


//////////////
// MHL Port //
//////////////

//--------------------------------------------------
// MHL CBUS Output High Voltage Level
//--------------------------------------------------
#ifndef _MHL_CBUS_LDO_HIGH
#define _MHL_CBUS_LDO_HIGH                      _DISABLE
#endif


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_1_1_FB_SWAP
#define _PANEL_DPTX_1_1_FB_SWAP                 _DISABLE
#endif

#ifndef _PANEL_DPTX_1_1_LANE_SWAP
#define _PANEL_DPTX_1_1_LANE_SWAP               _DISABLE
#endif

#ifndef _PANEL_DPTX_1_1_LANE_PN_SWAP
#define _PANEL_DPTX_1_1_LANE_PN_SWAP            _DISABLE
#endif

#ifndef _PANEL_DPTX_1_1_SWING_LEVEL
#define _PANEL_DPTX_1_1_SWING_LEVEL             _DP_SWING_800_MV
#endif

#ifndef _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB
#endif

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_1_1_SPREAD_RANGE
#define _PANEL_DPTX_1_1_SPREAD_RANGE            5
#endif

#ifndef _PANEL_DPTX_1_1_SPREAD_SPEED
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K
#endif


//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Main Link Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_1_2_SWING_LEVEL
#define _PANEL_DPTX_1_2_SWING_LEVEL             _DP_SWING_800_MV
#endif

#ifndef _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL
#define _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_3_5_DB
#endif

//--------------------------------------------------
// eDPTx 1.2 HBR2 SSC Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_1_2_SPREAD_RANGE
#define _PANEL_DPTX_1_2_SPREAD_RANGE            12
#endif

#ifndef _PANEL_DPTX_1_2_SPREAD_SPEED
#define _PANEL_DPTX_1_2_SPREAD_SPEED            _SPEED_33K
#endif

//--------------------------------------------------
// eDPTx 1.2 HBR2 FB/Lane Config
//--------------------------------------------------
#ifndef _PANEL_DPTX_1_2_FB_SWAP
#define _PANEL_DPTX_1_2_FB_SWAP                 _DISABLE
#endif
#ifndef _PANEL_DPTX_1_2_LANE_SWAP
#define _PANEL_DPTX_1_2_LANE_SWAP               _DISABLE
#endif
#ifndef _PANEL_DPTX_1_2_LANE_PN_SWAP
#define _PANEL_DPTX_1_2_LANE_PN_SWAP            _DISABLE
#endif


////////////////////////////
// eDPTx Panel AUX Config //
////////////////////////////

//--------------------------------------------------
// eDPTx AUX Swing Level
//--------------------------------------------------
#ifndef _PANEL_DPTX_AUX_SWING_LEVEL
#define _PANEL_DPTX_AUX_SWING_LEVEL             _DP_AUX_SWING_1050_MV
#endif


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Main Link Config
//--------------------------------------------------
#ifndef _VBO_LANE_SWAP
#define _VBO_LANE_SWAP                          _DISABLE
#endif

#ifndef _VBO_ML_SWAP
#define _VBO_ML_SWAP                            _DISABLE
#endif

#ifndef _VBO_PN_SWAP
#define _VBO_PN_SWAP                            _DISABLE
#endif

#ifndef _VBO_LANE_DRIV_CONTROL
#define _VBO_LANE_DRIV_CONTROL                  _VBO_DRIV_CONTROL_3_0
#endif

#ifndef _VBO_PRE_EMPHASIS_CONTROL
#define _VBO_PRE_EMPHASIS_CONTROL               _VBO_PRE_EMPHASIS_0
#endif

//--------------------------------------------------
// V by One SSC Config
//--------------------------------------------------
#ifndef _VBO_SPREAD_RANGE
#define _VBO_SPREAD_RANGE                       15
#endif

#ifndef _VBO_SPREAD_SPEED
#define _VBO_SPREAD_SPEED                       _SPEED_30K
#endif


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#ifndef _PWM_DUT_RESOLUTION
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT
#endif

#ifndef _BACKLIGHT_PWM
#define _BACKLIGHT_PWM                          _NO_PWM
#endif

#ifndef _BACKLIGHT_PWM_INVERSE
#define _BACKLIGHT_PWM_INVERSE                  _OFF
#endif

#ifndef _PWM0_EN
#define _PWM0_EN                                _OFF
#endif

#ifndef _PWM1_EN
#define _PWM1_EN                                _OFF
#endif

#ifndef _PWM2_EN
#define _PWM2_EN                                _OFF
#endif

#ifndef _PWM3_EN
#define _PWM3_EN                                _OFF
#endif

#ifndef _PWM4_EN
#define _PWM4_EN                                _OFF
#endif

#ifndef _PWM5_EN
#define _PWM5_EN                                _OFF
#endif

#ifndef _PWM0_PSAV_EN
#define _PWM0_PSAV_EN                           _OFF
#endif

#ifndef _PWM1_PSAV_EN
#define _PWM1_PSAV_EN                           _OFF
#endif

#ifndef _PWM2_PSAV_EN
#define _PWM2_PSAV_EN                           _OFF
#endif

#ifndef _PWM3_PSAV_EN
#define _PWM3_PSAV_EN                           _OFF
#endif

#ifndef _PWM4_PSAV_EN
#define _PWM4_PSAV_EN                           _OFF
#endif

#ifndef _PWM5_PSAV_EN
#define _PWM5_PSAV_EN                           _OFF
#endif

#ifndef _PWM0_PDOW_EN
#define _PWM0_PDOW_EN                           _OFF
#endif

#ifndef _PWM1_PDOW_EN
#define _PWM1_PDOW_EN                           _OFF
#endif

#ifndef _PWM2_PDOW_EN
#define _PWM2_PDOW_EN                           _OFF
#endif

#ifndef _PWM3_PDOW_EN
#define _PWM3_PDOW_EN                           _OFF
#endif

#ifndef _PWM4_PDOW_EN
#define _PWM4_PDOW_EN                           _OFF
#endif

#ifndef _PWM5_PDOW_EN
#define _PWM5_PDOW_EN                           _OFF
#endif

#ifndef _PWM0_RST_EN
#define _PWM0_RST_EN                            _OFF
#endif

#ifndef _PWM1_RST_EN
#define _PWM1_RST_EN                            _OFF
#endif

#ifndef _PWM2_RST_EN
#define _PWM2_RST_EN                            _OFF
#endif

#ifndef _PWM3_RST_EN
#define _PWM3_RST_EN                            _OFF
#endif

#ifndef _PWM4_RST_EN
#define _PWM4_RST_EN                            _OFF
#endif

#ifndef _PWM5_RST_EN
#define _PWM5_RST_EN                            _OFF
#endif

#ifndef _PWM_RST_SIGNAL_SEL
#define _PWM_RST_SIGNAL_SEL                     _DVS
#endif

#ifndef _PWM_FREQ_DVSRST_CHECK
#define _PWM_FREQ_DVSRST_CHECK                  _ON
#endif


//////////
// TCON //
//////////

//--------------------------------------------------
// MBR TCON Pin Setting
//--------------------------------------------------
#ifndef _PCB_MBR_TCON_PIN
#define _PCB_MBR_TCON_PIN                       _GEN_NONE
#endif

//--------------------------------------------------
// MBR Driver IC Max Frequency (unit: kHz)
//--------------------------------------------------
#ifndef _PCB_MBR_DRIVER_IC_MAX_FREQ
#define _PCB_MBR_DRIVER_IC_MAX_FREQ             _GEN_NONE
#endif


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#ifndef _SW_IIC_SUPPORT
#define _SW_IIC_SUPPORT                         _OFF
#endif

#ifndef _SW_IIC_CLK_DIV
#define _SW_IIC_CLK_DIV                         _DIV_1
#endif

#ifndef _HW_IIC_SUPPORT
#define _HW_IIC_SUPPORT                         _OFF
#endif

#ifndef _HW_IIC_SPEED
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K
#endif

#ifndef _HW_IIC_PAR_BY_USER_SUPPORT
#define _HW_IIC_PAR_BY_USER_SUPPORT             _OFF
#endif


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#ifndef _EEPROM_TYPE
#define _EEPROM_TYPE                            _EEPROM_24LC16
#endif

#ifndef _EEPROM_SLAVE_ADDRESS
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#endif

#ifndef _PCB_SYS_EEPROM_IIC
#define _PCB_SYS_EEPROM_IIC                     _NO_IIC_PIN
#endif


////////////////////////////
// Second External Eeprom //
////////////////////////////

//--------------------------------------------------
// Second External Eeprom Data Storage Option
//--------------------------------------------------
#ifndef _SEC_EEPROM_TYPE
#define _SEC_EEPROM_TYPE                        _EEPROM_CAT24M01
#endif

#ifndef _SEC_EEPROM_SLAVE_ADDRESS
#define _SEC_EEPROM_SLAVE_ADDRESS               0xA0
#endif

#ifndef _PCB_SEC_EEPROM_IIC
#define _PCB_SEC_EEPROM_IIC                     _NO_IIC_PIN
#endif


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#ifndef _AD_KEY_SUPPORT
#define _AD_KEY_SUPPORT                         _OFF
#endif

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#ifndef _LOW_SPEED_ADC_SUPPORT
#define _LOW_SPEED_ADC_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// FLASH SPI Control Option
//--------------------------------------------------
#ifndef _FLASH_CLK_DRIVE_CURRENT
#define _FLASH_CLK_DRIVE_CURRENT                _SPI_DRIVE_4_0MA
#endif

#ifndef _FLASH_SI_SO_CEB_DRIVE_CURRENT
#define _FLASH_SI_SO_CEB_DRIVE_CURRENT          _SPI_DRIVE_4_0MA
#endif

#ifndef _FLASH_CLK_SLEW_RATE_CONTROL
#define _FLASH_CLK_SLEW_RATE_CONTROL            _SPI_FAST_SLEW_RATE
#endif

#ifndef _FLASH_SI_SO_CEB_SLEW_RATE_CONTROL
#define _FLASH_SI_SO_CEB_SLEW_RATE_CONTROL      _SPI_FAST_SLEW_RATE
#endif


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO ON/OFF Region Initial Setting
//-----------------------------------------------
#ifndef PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON
#define PCB_ON_REGION_GPIO_SETTING_POWER_AC_ON(){\
                                                }
#endif

#ifndef PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON
#define PCB_OFF_REGION_GPIO_SETTING_POWER_AC_PD_PS_ON()\
                                                {\
                                                }
#endif

#ifndef PCB_GPIO_SETTING_POWER_NORMAL
#define PCB_GPIO_SETTING_POWER_NORMAL()         {\
                                                }
#endif

#ifndef PCB_GPIO_SETTING_POWER_SAVING
#define PCB_GPIO_SETTING_POWER_SAVING()         {\
                                                }
#endif

#ifndef PCB_GPIO_SETTING_POWER_DOWN
#define PCB_GPIO_SETTING_POWER_DOWN()           {\
                                                }
#endif


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#ifndef _VCCK_OFF_POWER_ON
#define _VCCK_OFF_POWER_ON                      1
#endif

#ifndef _VCCK_OFF_POWER_OFF
#define _VCCK_OFF_POWER_OFF                     0
#endif

#ifndef _VCCK_OFF_TIME_POLLING_POWER_ON
#define _VCCK_OFF_TIME_POLLING_POWER_ON         20
#endif

#ifndef PCB_VCCK_OFF_POWER
#define PCB_VCCK_OFF_POWER(x)                   {\
                                                }
#endif

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#ifndef _DDR_POWER_ON
#define _DDR_POWER_ON                           1
#endif

#ifndef _DDR_POWER_OFF
#define _DDR_POWER_OFF                          0
#endif

#ifndef PCB_DDR_POWER
#define PCB_DDR_POWER(x)                        {\
                                                }
#endif

//-----------------------------------------------
// Macro of DDR Poewr Release Time Control
//-----------------------------------------------
#ifndef _DDR_POWER_OFF_TIME
#define _DDR_POWER_OFF_TIME                     200
#endif

//-----------------------------------------------
// Macro of Power Board Low Power Pin High/Low
//-----------------------------------------------
#ifndef _LOW_POWER_ON
#define _LOW_POWER_ON                           1
#endif

#ifndef _LOW_POWER_OFF
#define _LOW_POWER_OFF                          0
#endif

#ifndef PCB_POWERBOARD_LOWPOWER
#define PCB_POWERBOARD_LOWPOWER(x)              {\
                                                }
#endif

//-----------------------------------------------
// Macro of Repeater Power & External Port Controller Control
//-----------------------------------------------
#ifndef _TWO_CHIP_REPEATER_POWER_ON
#define _TWO_CHIP_REPEATER_POWER_ON             1
#endif

#ifndef _TWO_CHIP_REPEATER_POWER_OFF
#define _TWO_CHIP_REPEATER_POWER_OFF            0
#endif

#ifndef _TWO_CHIP_PORT_CTRL_POWER_ON
#define _TWO_CHIP_PORT_CTRL_POWER_ON            1
#endif

#ifndef _TWO_CHIP_PORT_CTRL_POWER_OFF
#define _TWO_CHIP_PORT_CTRL_POWER_OFF           0
#endif

#ifndef GET_PCB_TWO_CHIP_REPEATER_POW_STATUS
#define GET_PCB_TWO_CHIP_REPEATER_POW_STATUS()  (_TWO_CHIP_REPEATER_POWER_ON)
#endif

#ifndef PCB_TWO_CHIP_REPEATER_POW
#define PCB_TWO_CHIP_REPEATER_POW(x)            {\
                                                }
#endif

#ifndef GET_PCB_TWO_CHIP_PORT_CTRL_POW_STATUS
#define GET_PCB_TWO_CHIP_PORT_CTRL_POW_STATUS() (_TWO_CHIP_PORT_CTRL_POWER_ON)
#endif

#ifndef PCB_TWO_CHIP_PORT_CTRL_POW
#define PCB_TWO_CHIP_PORT_CTRL_POW(x)           {\
                                                }
#endif

//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#ifndef _REGULATOR_5V_ON
#define _REGULATOR_5V_ON                        0
#endif

#ifndef _REGULATOR_5V_OFF
#define _REGULATOR_5V_OFF                       1
#endif

#ifndef PCB_REGULATOR_5V_OUT
#define PCB_REGULATOR_5V_OUT(x)                 {\
                                                }
#endif


////////////////////
// DP Power Macro //
////////////////////

//-----------------------------------------------
// Macro of MyDP Power Control
//-----------------------------------------------
#ifndef _MYDP_5V_POWER_ON
#define _MYDP_5V_POWER_ON                       1
#endif

#ifndef _MYDP_5V_POWER_OFF
#define _MYDP_5V_POWER_OFF                      0
#endif

#ifndef PCB_D0_MYDP_POWER
#define PCB_D0_MYDP_POWER(x)                    {\
                                                }
#endif

#ifndef PCB_D1_MYDP_POWER
#define PCB_D1_MYDP_POWER(x)                    {\
                                                }
#endif

//-----------------------------------------------
// Macro of DP1.2 Power Control
//-----------------------------------------------
#ifndef _DP12_33V_POWER_ON
#define _DP12_33V_POWER_ON                      1
#endif

#ifndef _DP12_33V_POWER_OFF
#define _DP12_33V_POWER_OFF                     0
#endif

#ifndef PCB_D0_DP12_POWER
#define PCB_D0_DP12_POWER(x)                    {\
                                                }
#endif

#ifndef PCB_D1_DP12_POWER
#define PCB_D1_DP12_POWER(x)                    {\
                                                }
#endif

//-----------------------------------------------
// Macro of MyDP & DP1.2 Power Select
//-----------------------------------------------
#ifndef _DP12_33V_POWER
#define _DP12_33V_POWER                         0
#endif

#ifndef _MYDP_5V_POWER
#define _MYDP_5V_POWER                          1
#endif

#ifndef PCB_D0_DP12_MYDP_POWER_SELECT
#define PCB_D0_DP12_MYDP_POWER_SELECT(x)        {\
                                                }
#endif

#ifndef PCB_D1_DP12_MYDP_POWER_SELECT
#define PCB_D1_DP12_MYDP_POWER_SELECT(x)        {\
                                                }
#endif


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#ifndef _PANEL_CONTROL_ON
#define _PANEL_CONTROL_ON                       0
#endif

#ifndef _PANEL_CONTROL_OFF
#define _PANEL_CONTROL_OFF                      1
#endif

#ifndef PCB_PANEL_POWER
#define PCB_PANEL_POWER(x)                      {\
                                                }
#endif

#ifndef PCB_PANEL_POWER_DETECT
#define PCB_PANEL_POWER_DETECT()                (_PANEL_CONTROL_OFF)
#endif

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#ifndef _LIGHT_CONTROL_ON
#define _LIGHT_CONTROL_ON                       0
#endif

#ifndef _LIGHT_CONTROL_OFF
#define _LIGHT_CONTROL_OFF                      1
#endif

#ifndef PCB_BACKLIGHT_POWER_PIN
#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                }
#endif

#ifndef PCB_BACKLIGHT_POWER
#define PCB_BACKLIGHT_POWER(x)                  {\
                                                }
#endif


//////////////////////////////////////
// eDPTx Panel Power Sequence Macro //
//////////////////////////////////////

//--------------------------------------------------
// eDPTx 1.1 Panel Power Sequence Macro
//--------------------------------------------------
#ifndef PCB_DPTX1_POWER_SEQUENCE
#define PCB_DPTX1_POWER_SEQUENCE(x)             {\
                                                }
#endif

#ifndef PCB_DPTX2_POWER_SEQUENCE
#define PCB_DPTX2_POWER_SEQUENCE(x)             {\
                                                }
#endif

//--------------------------------------------------
// eDPTx 1.2 Panel Power Sequence Macro
//--------------------------------------------------
#ifndef PCB_DPTX_POWER_SEQUENCE
#define PCB_DPTX_POWER_SEQUENCE(x)              {\
                                                }
#endif

#ifndef _DPTX_POWER_SEQUENCE_PANEL_ON
#define _DPTX_POWER_SEQUENCE_PANEL_ON           _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_HPD_ON
#define _DPTX_POWER_SEQUENCE_HPD_ON             _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_LINK_TRAINING
#define _DPTX_POWER_SEQUENCE_LINK_TRAINING      _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_IDLE_PATTERN
#define _DPTX_POWER_SEQUENCE_IDLE_PATTERN       _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_VIDEO_PATTERN
#define _DPTX_POWER_SEQUENCE_VIDEO_PATTERN      _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_BACKLIGHT_ON
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_ON       _LOW
#endif

#ifndef _DPTX_POWER_SEQUENCE_BACKLIGHT_OFF
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_OFF      _LOW
#endif


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#ifndef _FLASH_WRITE_PROTECT_ENABLE
#define _FLASH_WRITE_PROTECT_ENABLE             0
#endif

#ifndef _FLASH_WRITE_PROTECT_DISABLE
#define _FLASH_WRITE_PROTECT_DISABLE            1
#endif

#ifndef PCB_FLASH_WRITE_PROTECT
#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                }
#endif

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#ifndef _EEPROM_WP_ENABLE
#define _EEPROM_WP_ENABLE                       1
#endif

#ifndef _EEPROM_WP_DISABLE
#define _EEPROM_WP_DISABLE                      0
#endif

#ifndef PCB_EEPROM_WRITE_PROTECT
#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                }
#endif

#ifndef PCB_EEPROM_WRITE_PROTECT_DETECT
#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (_EEPROM_WP_DISABLE)
#endif

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#ifndef _EDID_EEPROM_WP_ENABLE
#define _EDID_EEPROM_WP_ENABLE                  1
#endif

#ifndef _EDID_EEPROM_WP_DISABLE
#define _EDID_EEPROM_WP_DISABLE                 0
#endif

#ifndef PCB_A0_EDID_EEPROM_WRITE_PROTECT
#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                }
#endif

#ifndef PCB_D2_EDID_EEPROM_WRITE_PROTECT
#define PCB_D2_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                }
#endif

#ifndef PCB_D3_EDID_EEPROM_WRITE_PROTECT
#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                }
#endif

//-----------------------------------------------
// Macro of HDMI External EDID Switch : #if (_HDMI_MULTI_EDID_SUPPORT == _ON)
//-----------------------------------------------
#ifndef bD2_EXT_SWITCH_EDID_0
#define bD2_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#endif

#ifndef bD2_EXT_SWITCH_EDID_1
#define bD2_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#endif

#ifndef bD2_EXT_SWITCH_EDID_2
#define bD2_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#endif

#ifndef bD3_EXT_SWITCH_EDID_0
#define bD3_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#endif

#ifndef bD3_EXT_SWITCH_EDID_1
#define bD3_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#endif

#ifndef bD3_EXT_SWITCH_EDID_2
#define bD3_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#endif

#ifndef PCB_MULTI_EDID_ALL_SWITCH_OFF
#define PCB_MULTI_EDID_ALL_SWITCH_OFF(port)     {\
                                                }
#endif

#ifndef PCB_MULTI_EDID_SWITCH
#define PCB_MULTI_EDID_SWITCH(port, index)      {\
                                                }
#endif

#ifndef PCB_MULTI_EDID_SWITCH_POWER_AC_ON
#define PCB_MULTI_EDID_SWITCH_POWER_AC_ON()     {\
                                                }
#endif


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#ifndef PCB_A0_PIN
#define PCB_A0_PIN()                            (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D0_PIN
#define PCB_D0_PIN()                            (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D1_PIN
#define PCB_D1_PIN()                            (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D2_PIN
#define PCB_D2_PIN()                            (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

#ifndef PCB_D3_PIN
#define PCB_D3_PIN()                            (_PCB_CABLE_DISCONNECT_LEVEL)
#endif

//-----------------------------------------------
// Macro of TypeC Ext Port Controller Connect
//-----------------------------------------------
#ifndef PCB_D0_CC_ATTACH_PIN
#define PCB_D0_CC_ATTACH_PIN()                  (_PCB_DP_TYPE_C_CC_UNATTACH_LEVEL)
#endif

#ifndef PCB_D0_ALT_MODE_PIN
#define PCB_D0_ALT_MODE_PIN()                   (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#endif

#ifndef PCB_D1_CC_ATTACH_PIN
#define PCB_D1_CC_ATTACH_PIN()                  (_PCB_DP_TYPE_C_CC_UNATTACH_LEVEL)
#endif

#ifndef PCB_D1_ALT_MODE_PIN
#define PCB_D1_ALT_MODE_PIN()                   (_PCB_DP_TYPE_C_NOT_ENTER_ALTMODE_LEVEL)
#endif

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#ifndef GET_PCB_D0_DP_SOURCE_POWER
#define GET_PCB_D0_DP_SOURCE_POWER()            (_LOW)
#endif

#ifndef GET_PCB_D1_DP_SOURCE_POWER
#define GET_PCB_D1_DP_SOURCE_POWER()            (_LOW)
#endif

//-----------------------------------------------
// Macro of DP Source Power When under Pin E Type and Aux PN Swap
//-----------------------------------------------
#ifndef GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP
#define GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP()    (_LOW)
#endif

#ifndef GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP
#define GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP()    (_LOW)
#endif

//-----------------------------------------------
// Aux PN 1M Pull High / low Swap Control
//-----------------------------------------------
#ifndef _AUX_PN_1M_PULL_HI_LOW_SWAP_ON
#define _AUX_PN_1M_PULL_HI_LOW_SWAP_ON          (1)
#endif

#ifndef _AUX_PN_1M_PULL_HI_LOW_SWAP_OFF
#define _AUX_PN_1M_PULL_HI_LOW_SWAP_OFF         (0)
#endif

#ifndef PCB_D0_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_D0_AUX_PN_1M_PULL_H_L_SWAP(x)       {\
                                                }
#endif

#ifndef PCB_D1_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_D1_AUX_PN_1M_PULL_H_L_SWAP(x)       {\
                                                }
#endif

#ifndef PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP()    (_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF)
#endif

#ifndef PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP
#define PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP()    (_AUX_PN_1M_PULL_HI_LOW_SWAP_OFF)
#endif

//-----------------------------------------------
// Macro of MHL Cable Connect
//-----------------------------------------------
#ifndef PCB_D2_MHL_DETECT
#define PCB_D2_MHL_DETECT()                     (_MHL_CABLE_DISCONNECT)
#endif

#ifndef PCB_D3_MHL_DETECT
#define PCB_D3_MHL_DETECT()                     (_MHL_CABLE_DISCONNECT)
#endif


/////////////////////////////////////////
// RTS 5400 Series SMBUS Arbit Control //
/////////////////////////////////////////

//---------------------------------------------------------------------------
// GPIO Arbitration Between Hub (54xx) And Scaler For Access PD (545x)
//---------------------------------------------------------------------------
#ifndef _RTS_SMBUS_IDLE
#define _RTS_SMBUS_IDLE                         0
#endif

#ifndef _RTS_SMBUS_BUSY
#define _RTS_SMBUS_BUSY                         1
#endif

#ifndef PCB_CHECK_RTS_SMBUS_BUSY_STATUS
#define PCB_CHECK_RTS_SMBUS_BUSY_STATUS(x)      {\
                                                    (x) = _RTS_SMBUS_IDLE;\
                                                }
#endif

#ifndef PCB_SET_RTS_SMBUS_BUSY
#define PCB_SET_RTS_SMBUS_BUSY()                {\
                                                }
#endif

#ifndef PCB_RELEASE_RTS_SMBUS_BUSY
#define PCB_RELEASE_RTS_SMBUS_BUSY()            {\
                                                }
#endif


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#ifndef _D0_HOT_PLUG_HIGH
#define _D0_HOT_PLUG_HIGH                       1
#endif

#ifndef _D0_HOT_PLUG_LOW
#define _D0_HOT_PLUG_LOW                        0
#endif

#ifndef _D1_HOT_PLUG_HIGH
#define _D1_HOT_PLUG_HIGH                       1
#endif

#ifndef _D1_HOT_PLUG_LOW
#define _D1_HOT_PLUG_LOW                        0
#endif

#ifndef _D2_HOT_PLUG_HIGH
#define _D2_HOT_PLUG_HIGH                       1
#endif

#ifndef _D2_HOT_PLUG_LOW
#define _D2_HOT_PLUG_LOW                        0
#endif

#ifndef _D3_HOT_PLUG_HIGH
#define _D3_HOT_PLUG_HIGH                       1
#endif

#ifndef _D3_HOT_PLUG_LOW
#define _D3_HOT_PLUG_LOW                        0
#endif

#ifndef PCB_D0_HOTPLUG
#define PCB_D0_HOTPLUG(x)                       {\
                                                }
#endif

#ifndef PCB_D1_HOTPLUG
#define PCB_D1_HOTPLUG(x)                       {\
                                                }
#endif

#ifndef PCB_D2_HOTPLUG
#define PCB_D2_HOTPLUG(x)                       {\
                                                }
#endif

#ifndef PCB_D3_HOTPLUG
#define PCB_D3_HOTPLUG(x)                       {\
                                                }
#endif

#ifndef PCB_D0_HOTPLUG_DETECT
#define PCB_D0_HOTPLUG_DETECT()                 (_D0_HOT_PLUG_LOW)
#endif

#ifndef PCB_D1_HOTPLUG_DETECT
#define PCB_D1_HOTPLUG_DETECT()                 (_D1_HOT_PLUG_LOW)
#endif

#ifndef PCB_D2_HOTPLUG_DETECT
#define PCB_D2_HOTPLUG_DETECT()                 (_D2_HOT_PLUG_LOW)
#endif

#ifndef PCB_D3_HOTPLUG_DETECT
#define PCB_D3_HOTPLUG_DETECT()                 (_D3_HOT_PLUG_LOW)
#endif


///////////////
// MHL Macro //
///////////////

//-----------------------------------------------
// Macro of HDMI/MHL Switch
//-----------------------------------------------
#ifndef _TMDS_SWITCH_MHL_CBUS
#define _TMDS_SWITCH_MHL_CBUS                   0
#endif

#ifndef _TMDS_SWITCH_HDMI_HPD
#define _TMDS_SWITCH_HDMI_HPD                   1
#endif

#ifndef PCB_D2_HDMI_MHL_SWITCH
#define PCB_D2_HDMI_MHL_SWITCH(x)               {\
                                                }
#endif

#ifndef PCB_D3_HDMI_MHL_SWITCH
#define PCB_D3_HDMI_MHL_SWITCH(x)               {\
                                                }
#endif

//-----------------------------------------------
// Macro of MHL VBus Switch
//-----------------------------------------------
#ifndef _MHL_VBUS_ON
#define _MHL_VBUS_ON                            1
#endif

#ifndef _MHL_VBUS_OFF
#define _MHL_VBUS_OFF                           0
#endif

#ifndef PCB_D2_MHL_VBUS_SWITCH
#define PCB_D2_MHL_VBUS_SWITCH(x)               {\
                                                }
#endif

#ifndef PCB_D3_MHL_VBUS_SWITCH
#define PCB_D3_MHL_VBUS_SWITCH(x)               {\
                                                }
#endif

#ifndef PCB_GET_D2_MHL_VBUS_SWITCH
#define PCB_GET_D2_MHL_VBUS_SWITCH()            (_MHL_VBUS_OFF)
#endif

#ifndef PCB_GET_D3_MHL_VBUS_SWITCH
#define PCB_GET_D3_MHL_VBUS_SWITCH()            (_MHL_VBUS_OFF)
#endif

//-----------------------------------------------
// Macro of MHL VBUS 5V Power Control
//-----------------------------------------------
#ifndef PCB_MHL_VBUS_POWER
#define PCB_MHL_VBUS_POWER(x)                   {\
                                                }
#endif


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#ifndef PCB_PWM_SETTING
#define PCB_PWM_SETTING()                       {\
                                                }
#endif

#ifndef PCB_BACKLIGHT_PWM
#define PCB_BACKLIGHT_PWM(x)                    {\
                                                }
#endif

#ifndef PCB_GET_BACKLIGHT_PWM
#define PCB_GET_BACKLIGHT_PWM()                 (0xFF)
#endif


//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#ifndef PCB_SW_IIC_SDA_SET
#define PCB_SW_IIC_SDA_SET()                    {\
                                                }
#endif

#ifndef PCB_SW_IIC_SDA_CLR
#define PCB_SW_IIC_SDA_CLR()                    {\
                                                }
#endif

#ifndef PCB_SW_IIC_SDA_CHK
#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                }
#endif

#ifndef PCB_SW_IIC_SCL_SET
#define PCB_SW_IIC_SCL_SET()                    {\
                                                }
#endif

#ifndef PCB_SW_IIC_SCL_CLR
#define PCB_SW_IIC_SCL_CLR()                    {\
                                                }
#endif

#ifndef PCB_SW_IIC_SCL_CHK
#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                }
#endif


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#ifndef _LED_ON
#define _LED_ON                                 1
#endif

#ifndef _LED_OFF
#define _LED_OFF                                0
#endif

#ifndef PCB_LED_AC_ON_INITIAL
#define PCB_LED_AC_ON_INITIAL()                 {\
                                                }
#endif

#ifndef PCB_LED_ACTIVE
#define PCB_LED_ACTIVE()                        {\
                                                }
#endif

#ifndef PCB_LED_IDLE
#define PCB_LED_IDLE()                          {\
                                                }
#endif

#ifndef PCB_LED_POWER_SAVING
#define PCB_LED_POWER_SAVING()                  {\
                                                }
#endif

#ifndef PCB_LED_ON
#define PCB_LED_ON()                            {\
                                                }
#endif

#ifndef PCB_LED_OFF
#define PCB_LED_OFF()                           {\
                                                }
#endif

#ifndef PCB_LED_TYPE1
#define PCB_LED_TYPE1()                         {\
                                                }
#endif

#ifndef PCB_LED_TYPE2
#define PCB_LED_TYPE2()                         {\
                                                }
#endif

#ifndef PCB_LED_TYPE3
#define PCB_LED_TYPE3()                         {\
                                                }
#endif

#ifndef PCB_LED_TYPE4
#define PCB_LED_TYPE4()                         {\
                                                }
#endif

#ifndef PCB_LED_TYPE5
#define PCB_LED_TYPE5()                         {\
                                                }
#endif

#ifndef PCB_LED_TYPE_FLASH
#define PCB_LED_TYPE_FLASH()                    {\
                                                }
#endif


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#ifndef PCB_ADKEY0
#define PCB_ADKEY0()                            (_FALSE)
#endif

#ifndef PCB_ADKEY1
#define PCB_ADKEY1()                            (_FALSE)
#endif

#ifndef PCB_ADKEY2
#define PCB_ADKEY2()                            (_FALSE)
#endif

#ifndef PCB_ADKEY3
#define PCB_ADKEY3()                            (_FALSE)
#endif

#ifndef PCB_KEY_STATE
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }
#endif


////////////////////
// GPIO Key Macro //
////////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#ifndef PCB_KEY_STATE
#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }
#endif


/////////////////
// Audio Macro //
/////////////////

//-----------------------------------------------
// Macro of PCB Audio Connect
//-----------------------------------------------
#ifndef _AUDIO_CONNECT
#define _AUDIO_CONNECT                          0
#endif

#ifndef _AUDIO_DISCONNECT
#define _AUDIO_DISCONNECT                       1
#endif

#ifndef PCB_AUDIO_DETECT
#define PCB_AUDIO_DETECT()                      (_AUDIO_DISCONNECT)
#endif

//-----------------------------------------------
// Macro of PCB Audio AMP Control
//-----------------------------------------------
#ifndef _AMP_MUTE_ON
#define _AMP_MUTE_ON                            0
#endif

#ifndef _AMP_MUTE_OFF
#define _AMP_MUTE_OFF                           1
#endif

#ifndef PCB_AMP_MUTE
#define PCB_AMP_MUTE(x)                         {\
                                                }
#endif
