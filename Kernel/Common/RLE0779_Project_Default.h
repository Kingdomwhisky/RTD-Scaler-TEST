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
// ID Code      : RLE0779_Project_Default.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


/////////////
// General //
/////////////

//--------------------------------------------------
// Pcb Option
//--------------------------------------------------
#ifndef _PCB_TYPE
#define _PCB_TYPE                                               _RLE0779_PCB_EXAMPLE
#endif

//--------------------------------------------------
// Scaler or Translator Option
//--------------------------------------------------
#ifndef _TRANSLATOR_SUPPORT
#define _TRANSLATOR_SUPPORT                                     _OFF
#endif


///////////
// DDCCI //
///////////

//-------------------------------------------------
// DDCCI Option
//-------------------------------------------------
#ifndef _DDCCI_RXBUF_LENGTH
#define _DDCCI_RXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TXBUF_LENGTH
#define _DDCCI_TXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TIMEOUT_LIMIT
#define _DDCCI_TIMEOUT_LIMIT                                    50 // 0~65535ms
#endif

#ifndef _CAPABILITIES_STRING_DVI
#define _CAPABILITIES_STRING_DVI                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_HDMI
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DP
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

//==================== START ======================

//-------------------------------------------------
// DDCCI Auto Switch Option
//-------------------------------------------------
#ifndef _DDCCI_AUTO_SWITCH_SUPPORT
#define _DDCCI_AUTO_SWITCH_SUPPORT                              _OFF
#endif

//===================== END =======================


////////////
// Eeprom //
////////////

//-------------------------------------------------
// Eeprom Access Function Option
//-------------------------------------------------
#ifndef _EEPROM_ACCESS_FUNCTION_SUPPORT
#define _EEPROM_ACCESS_FUNCTION_SUPPORT                         _OFF
#endif

#ifndef _EEPROM_KERNEL_START_ADDRESS
#define _EEPROM_KERNEL_START_ADDRESS                            (_EEPROM_PAGE0_BANK0)
#endif


///////////
// Flash //
///////////

//-------------------------------------------------
// Flash Clock Option
//-------------------------------------------------
#ifndef _FLASH_CLK_SPEED
#define _FLASH_CLK_SPEED                                        _FLASH_FAST_SPEED
#endif

//-------------------------------------------------
// Flash Access Function Option
//-------------------------------------------------
#ifndef _FLASH_WRITE_FUNCTION_SUPPORT
#define _FLASH_WRITE_FUNCTION_SUPPORT                           _OFF
#endif

#ifndef _FLASH_READ_FUNCTION_SUPPORT
#define _FLASH_READ_FUNCTION_SUPPORT                            _OFF
#endif

#ifndef _FLASH_TYPE_W25X20A_OR_W25X21CL
#define _FLASH_TYPE_W25X20A_OR_W25X21CL                         _FLASH_W25X20A
#endif

#ifndef _FLASH_TYPE_W25X40CL_OR_W25X41CL
#define _FLASH_TYPE_W25X40CL_OR_W25X41CL                        _FLASH_W25X40CL
#endif

#ifndef _FLASH_TYPE_GD25Q16C_OR_GD25Q16
#define _FLASH_TYPE_GD25Q16C_OR_GD25Q16                         _FLASH_GD25Q16C
#endif

#ifndef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F
#define _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F      _FLASH_MX25L3233F
#endif

#ifndef _FLASH_TYPE_GD25Q40B_OR_GD25Q41B
#define _FLASH_TYPE_GD25Q40B_OR_GD25Q41B                        _FLASH_GD25Q41B
#endif

#ifndef _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ
#define _FLASH_TYPE_W25Q16DV_OR_W25Q16JVSIQ                     _FLASH_W25Q16JVSIQ
#endif

#ifndef _FLASH_TYPE_FM25Q08_OR_FM25Q08A
#define _FLASH_TYPE_FM25Q08_OR_FM25Q08A                         _FLASH_FM25Q08A
#endif

//-------------------------------------------------
// EEPROM Emulation Option
//-------------------------------------------------
#ifndef _SYSTEM_EEPROM_EMULATION_SUPPORT
#define _SYSTEM_EEPROM_EMULATION_SUPPORT                        _OFF
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_FLASH_BANK
#define _SYSTEM_EEPROM_EMULATION_FLASH_BANK                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_START_PAGE
#define _SYSTEM_EEPROM_EMULATION_START_PAGE                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_END_PAGE
#define _SYSTEM_EEPROM_EMULATION_END_PAGE                       0
#endif

#ifndef _START_OF_PAGEID
#define _START_OF_PAGEID                                        _PAGEID_0
#endif

#ifndef _END_OF_PAGEID
#define _END_OF_PAGEID                                          _PAGEID_0
#endif

#ifndef _CHECKSUM_VERSIONCODE_ID
#define _CHECKSUM_VERSIONCODE_ID                                _PAGEID_0
#endif


//////////
// EDID //
//////////

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#ifndef _EDID_ADDRESS_EEPROM
#define _EDID_ADDRESS_EEPROM                                    (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _EDID_ADDRESS_FLASH
#define _EDID_ADDRESS_FLASH                                     (0)
#endif

#ifndef _EDID_FLASH_BANK
#define _EDID_FLASH_BANK                                        (0)
#endif

//-------------------------------------------------
// HDR10 EDID Auto Switch Option
//-------------------------------------------------
#ifndef _EDID_HDR10_AUTO_SWITCH
#define _EDID_HDR10_AUTO_SWITCH                                 _ON
#endif

//==================== START ======================
#ifndef _WRITE_EDID_TO_SYSTEM_EEPROM
#define _WRITE_EDID_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


//////////////
// HDCP Key //
//////////////

//-------------------------------------------------
// HDCP Key Location Option
//-------------------------------------------------
#ifndef _HDCP_1_4_KEY_LOCATION
#define _HDCP_1_4_KEY_LOCATION                                  _TABLE_LOCATION_SYSTEM_EEPROM
#endif

#ifndef _HDCP_2_2_KEY_LOCATION
#define _HDCP_2_2_KEY_LOCATION                                  _TABLE_LOCATION_CODE
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _RX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _RX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_1_4_KEY_FLASH_BANK
#define _RX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_EEPROM
#define _RX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_FLASH
#define _RX_HDCP_2_2_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_FLASH_BANK
#define _RX_HDCP_2_2_KEY_FLASH_BANK                             (0)
#endif

#ifndef _TX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _TX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _TX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _TX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _TX_HDCP_1_4_KEY_FLASH_BANK
#define _TX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

#ifndef _TX_HDCP_2_2_KEY_ADDRESS_EEPROM
#define _TX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _TX_HDCP_2_2_KEY_ADDRESS_FLASH
#define _TX_HDCP_2_2_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _TX_HDCP_2_2_KEY_FLASH_BANK
#define _TX_HDCP_2_2_KEY_FLASH_BANK                             (0)
#endif

//==================== START ======================
#ifndef _WRITE_HDCP_TO_SYSTEM_EEPROM
#define _WRITE_HDCP_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


///////////////////
// System Source //
///////////////////

//-------------------------------------------------
// System Auto Search Style Option
//-------------------------------------------------
#ifndef _SOURCE_AUTO_SEARCH_STYLE
#define _SOURCE_AUTO_SEARCH_STYLE                               _SOURCE_POLLING_IN_SEARCH_STATE
#endif

//-------------------------------------------------
// System Source Search Time Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI                        SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI                         SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP
#define _SOURCE_DEFAULT_SEARCH_TIME_DP                          SEC(3)
#endif

//==================== START ======================

//-------------------------------------------------
// System Default Search Time for all Port --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT
#define _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT                    SEC(2)
#endif

//-------------------------------------------------
// System Default Search Time When No Cable Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE               SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE                SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE                 SEC(3)
#endif

//--------------------------------------------------
// Double Check NVRAM Port When Searching In Polling Mode Option
//--------------------------------------------------
#ifndef _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT
#define _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT                 _OFF
#endif

#ifndef _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT
#define _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT             SEC(0.5)
#endif

//===================== END =======================


//////////////////
// System Judge //
//////////////////

//--------------------------------------------------
// System Support Timing Option
//--------------------------------------------------
#ifndef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    3300 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_HDMI
#define _INPUTCLOCK_RANG_HDMI                                   6000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DP
#define _INPUTCLOCK_RANG_DP                                     6000 // Unit in 0.1 MHz
#endif


//////////////////
// System Power //
//////////////////
//==================== START ======================

//--------------------------------------------------
// Power Fake Off to Off Timeout
//--------------------------------------------------
#ifndef _POWER_FAKE_OFF_TO_OFF_TIMEOUT
#define _POWER_FAKE_OFF_TO_OFF_TIMEOUT                          SEC(8)
#endif

//===================== END =======================


////////////////
// DVI & HDMI //
////////////////

//--------------------------------------------------
// DVI & HDMI Option
//--------------------------------------------------
#ifndef _DVI_DE_ONLY_SUPPORT
#define _DVI_DE_ONLY_SUPPORT                                    _OFF
#endif

#ifndef _HDMI_FROM_DVI_CONNECT
#define _HDMI_FROM_DVI_CONNECT                                  _OFF
#endif

#ifndef _HDMI_FREESYNC_SUPPORT
#define _HDMI_FREESYNC_SUPPORT                                  _OFF
#endif

//==================== START ======================
#ifndef _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD
#define _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD                 _MCCS_SWITCH_MODE
#endif

//-------------------------------------------------
// HDMI HDCP Re-auth Option
//-------------------------------------------------
#ifndef _HDMI_HDCP22_REAUTH_IN_RESET_PROC
#define _HDMI_HDCP22_REAUTH_IN_RESET_PROC                       _OFF
#endif

//--------------------------------------------------
// TMDS Z0's HPD DDC Check Optional
//--------------------------------------------------
#ifndef _TMDS_DDC_CHECK_BUSY_BEFORE_HPD
#define _TMDS_DDC_CHECK_BUSY_BEFORE_HPD                         _OFF
#endif
//===================== END =======================


#ifndef _TMDS_HDCP_2_2_SUPPORT
#define _TMDS_HDCP_2_2_SUPPORT                                  _OFF
#endif

#ifndef _HDMI_TX_SUPPORT
#define _HDMI_TX_SUPPORT                                        _OFF
#endif

#ifndef _HDMI_TX_HDCP_2_2_SUPPORT
#define _HDMI_TX_HDCP_2_2_SUPPORT                               _OFF
#endif

//--------------------------------------------------
// HDMI CTS Option
//--------------------------------------------------
#ifndef _TMDS_HDCP_FEATURE
#define _TMDS_HDCP_FEATURE                                      _HDCP_FEATURE_BY_INPUT
#endif

#ifndef _TMDS_Z0_POWER_SAVING_OPTION
#define _TMDS_Z0_POWER_SAVING_OPTION                            _ALL_CHANNEL_CONNECTED_FOR_CTS
#endif

#ifndef _TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT
#define _TMDS_HDMI_2_0_SCDC_RR_CTS_SUPPORT                      _OFF
#endif

#ifndef _D1_TMDS_Z0_IMPEDANCE_OPTION
#define _D1_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif

#ifndef _D2_TMDS_Z0_IMPEDANCE_OPTION
#define _D2_TMDS_Z0_IMPEDANCE_OPTION                            _BY_CONNECTOR
#endif


////////
// DP //
////////

//-------------------------------------------------
// DP Capability Option
//-------------------------------------------------
#ifndef _DP_MST_SUPPORT
#define _DP_MST_SUPPORT                                         _OFF
#endif

#ifndef _DP_TX_SUPPORT
#define _DP_TX_SUPPORT                                          _OFF
#endif

#ifndef _DP_FREESYNC_SUPPORT
#define _DP_FREESYNC_SUPPORT                                    _OFF
#endif

#ifndef _DP_HDCP_2_2_SUPPORT
#define _DP_HDCP_2_2_SUPPORT                                    _OFF
#endif

#ifndef _DP_HDCP14_CTS_SUPPORT
#define _DP_HDCP14_CTS_SUPPORT                                  _OFF
#endif

#ifndef _DP_NEGATIVE_TEST_SUPPORT
#define _DP_NEGATIVE_TEST_SUPPORT                               _OFF
#endif

//==================== START ======================

#ifndef _DP_TX_SSC_SUPPORT
#define _DP_TX_SSC_SUPPORT                                      _OFF
#endif

//--------------------------------------------------
// DP HBR & RBR Link Training Force Marginal Link(N+1)
//--------------------------------------------------
#ifndef _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK
#define _DP_HBR_RBR_LT_FORCE_MARGINAL_LINK                      _ON
#endif

//--------------------------------------------------
// DP HBR2 Marginal Link Reduce to HBR
//--------------------------------------------------
#ifndef _DP_HBR2_MARGIN_LINK_SUPPORT
#define _DP_HBR2_MARGIN_LINK_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// DP pull-up Long HPD or not (after CPIRQ) by User Option
//--------------------------------------------------
#ifndef _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT
#define _DP_LONG_HPD_AFTER_CPIRQ_SUPPORT                        _ON
#endif

//--------------------------------------------------
// DP MST Option
//--------------------------------------------------
#ifndef _D0_DP_MST_PORT_SUPPORT
#if(_DP_MST_SUPPORT == _ON)
#define _D0_DP_MST_PORT_SUPPORT                                 _ON
#else
#define _D0_DP_MST_PORT_SUPPORT                                 _OFF
#endif
#endif

#ifndef _D1_DP_MST_PORT_SUPPORT
#if(_DP_MST_SUPPORT == _ON)
#define _D1_DP_MST_PORT_SUPPORT                                 _ON
#else
#define _D1_DP_MST_PORT_SUPPORT                                 _OFF
#endif
#endif

//===================== END =======================


/////////
// MHL //
/////////

//--------------------------------------------------
// MHL2.x Option
//--------------------------------------------------
#ifndef _MHL_CBUS_CTS_MODE
#define _MHL_CBUS_CTS_MODE                                      _OFF
#endif

#ifndef _MHL2_UCP_SUPPORT
#define _MHL2_UCP_SUPPORT                                       _OFF
#endif

#ifndef _MHL2_AUD_CHANNEL
#define _MHL2_AUD_CHANNEL                                       _MHL_AUD_2CH
#endif

#ifndef _MHL2_ADOPTER_ID
#define _MHL2_ADOPTER_ID                                        0x0000
#endif

#ifndef _MHL2_DEVICE_ID
#define _MHL2_DEVICE_ID                                         0x0000
#endif

#ifndef _MHL2_PP_MODE_SUPPORT
#define _MHL2_PP_MODE_SUPPORT                                   _ON
#endif

//==================== START ======================

//--------------------------------------------------
// MHL3.x Option
//--------------------------------------------------
#ifndef _MHL3_UCP_SUPPORT
#define _MHL3_UCP_SUPPORT                                       _OFF
#endif

#ifndef _MHL3_AUD_CHANNEL
#define _MHL3_AUD_CHANNEL                                       _MHL_AUD_2CH
#endif

#ifndef _MHL3_ECBUS_HID_SUPPORT
#define _MHL3_ECBUS_HID_SUPPORT                                 _OFF
#endif

#ifndef _MHL3_ADOPTER_ID
#define _MHL3_ADOPTER_ID                                        0x0000
#endif

#ifndef _MHL3_DEVICE_ID
#define _MHL3_DEVICE_ID                                         0x0000
#endif

#ifndef _MHL3_16_BIT_MODE_SUPPORT
#define _MHL3_16_BIT_MODE_SUPPORT                               _ON
#endif

#ifndef _MHL3_ECBUS_HID_SUPPORT
#define _MHL3_ECBUS_HID_SUPPORT                                 _OFF
#endif

//===================== END =======================


///////////
// Audio //
///////////

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#ifndef _AUDIO_SUPPORT
#define _AUDIO_SUPPORT                                          _OFF
#endif

//-------------------------------------------------
// Audio DAC Option
//-------------------------------------------------
#ifndef _EMBEDDED_DAC_SUPPORT
#define _EMBEDDED_DAC_SUPPORT                                   _OFF
#endif

//==================== START ======================
#ifndef _DAC_SPEAKER_OUTPUT_SWAP
#define _DAC_SPEAKER_OUTPUT_SWAP                                _OFF
#endif

#ifndef _DAC_HP_OUTPUT_SWAP
#define _DAC_HP_OUTPUT_SWAP                                     _OFF
#endif

#ifndef _DAC_DEPOP_TO_NORMAL_WAIT_TIME
#define _DAC_DEPOP_TO_NORMAL_WAIT_TIME                          SEC(0.1)
#endif

#ifndef _DAC_DITHER_FUNCTION_LEVEL
#define _DAC_DITHER_FUNCTION_LEVEL                              _AUDIO_DAC_DITHER_LEVEL_OFF
#endif
//===================== END =======================

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#ifndef _LINE_IN_SUPPORT
#define _LINE_IN_SUPPORT                                        _OFF
#endif

#ifndef _LINE_IN_DAC_AOUT_GAIN_DB
#define _LINE_IN_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_DAC_HPOUT_GAIN_DB
#define _LINE_IN_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_BOOST_GAIN_DB
#define _LINE_IN_BOOST_GAIN_DB                                  0x17                        // 0dB, 1.5dB for each step, Max Gain: 0x3F(30dB)
#endif

#ifndef _LINE_IN_VOLUME_MAX
#define _LINE_IN_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _LINE_IN_VOLUME_MIN
#define _LINE_IN_VOLUME_MIN                                     0x0000
#endif

//==================== START ======================

//--------------------------------------------------
// Audio Line In AA DAC Bypass Option
//--------------------------------------------------
#ifndef _LINE_IN_AA_PATH_SUPPORT
#define _LINE_IN_AA_PATH_SUPPORT                                _OFF
#endif

//===================== END =======================

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#ifndef _DIGITAL_DAC_AOUT_GAIN_DB
#define _DIGITAL_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_DAC_HPOUT_GAIN_DB
#define _DIGITAL_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_VOLUME_MAX
#define _DIGITAL_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _DIGITAL_VOLUME_MIN
#define _DIGITAL_VOLUME_MIN                                     0x0000
#endif

//-------------------------------------------------
// Audio PS Option
//-------------------------------------------------
#ifndef _SLEEP_AUDIO_SUPPORT
#define _SLEEP_AUDIO_SUPPORT                                    _OFF
#endif

#ifndef _PS_AUDIO_INPUT
#define _PS_AUDIO_INPUT                                         _PS_AUDIO_LINE_IN
#endif

//==================== START ======================

//--------------------------------------------------
// Digital Volume Control Option --> For Audio Mute
//--------------------------------------------------
#ifndef _DVC_ADJUST_TYPE
#define _DVC_ADJUST_TYPE                                        _DB_GAIN
#endif

#ifndef _DB_GAIN_DOWN_VALUE
#define _DB_GAIN_DOWN_VALUE                                     _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _DB_GAIN_UP_VALUE
#define _DB_GAIN_UP_VALUE                                       _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _VOLUME_STEP_SIZE_VALUE
#define _VOLUME_STEP_SIZE_VALUE                                 (0x0040 & 0x3FFF) // For _VOLUME_STEP_SIZE
#endif

#ifndef _DVC_VOLUME_MUTE_TIMER
#define _DVC_VOLUME_MUTE_TIMER                                  400 // ms
#endif

//--------------------------------------------------
// DP Volume Control Option --> For Audio Mute / Unmute
//--------------------------------------------------
#ifndef _DP_DVC_ADJUST_TYPE
#define _DP_DVC_ADJUST_TYPE                                     _DB_GAIN
#endif

#ifndef _DP_DB_GAIN_DOWN_VALUE
#define _DP_DB_GAIN_DOWN_VALUE                                  _DB_GAIN_1_8_DB   // For _DB_GAIN Mode
#endif

#ifndef _DP_DB_GAIN_UP_VALUE
#define _DP_DB_GAIN_UP_VALUE                                    _DB_GAIN_1_8_DB   // For _DB_GAIN Mode
#endif

#ifndef _DP_VOLUME_STEP_SIZE_VALUE
#define _DP_VOLUME_STEP_SIZE_VALUE                              (0x40 & 0xFF) // For _VOLUME_STEP Mode
#endif

#ifndef _DP_DVC_VOLUME_MUTE_TIMER
#define _DP_DVC_VOLUME_MUTE_TIMER                               400 // ms
#endif

//--------------------------------------------------
// Audio Manual Sampling Frequency Option
//--------------------------------------------------
#ifndef _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT
#define _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT                     _OFF
#endif

#ifndef _FIX_SAMPLING_FREQ_TYPE
#define _FIX_SAMPLING_FREQ_TYPE                                 _FIX_FREQ_48KHZ
#endif

//--------------------------------------------------
// Switch Audio Source to Line In When Entering Power Saving Mode Option
//--------------------------------------------------
#ifndef _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE
#define _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE           _OFF
#endif

//===================== END =======================


///////////////////
// Misc Function //
///////////////////

//-------------------------------------------------
// Instant Timer Events Option
//-------------------------------------------------
#ifndef _INSTANT_TIMER_EVENT_0
#define _INSTANT_TIMER_EVENT_0                                  _OFF
#endif

#ifndef _INSTANT_TIMER_EVENT_1
#define _INSTANT_TIMER_EVENT_1                                  _OFF
#endif

//--------------------------------------------------
// IRDA Option
//--------------------------------------------------
#ifndef _IR_SUPPORT
#define _IR_SUPPORT                                             _IR_OFF
#endif

//==================== START ======================

//--------------------------------------------------
// UART Option
//--------------------------------------------------
#ifndef _UART_SUPPORT
#define _UART_SUPPORT                                           _OFF
#endif

#ifndef _UART_BAUD_RATE_POWER_NORMAL
#define _UART_BAUD_RATE_POWER_NORMAL                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

#ifndef _UART_BAUD_RATE_POWER_SAVING
#define _UART_BAUD_RATE_POWER_SAVING                            9600 // 9600/19200/14400/28800/38400/56000 Baud (Unit in Baud)
#endif

//-------------------------------------------------
// System Timer 250us Option --> SW IR Application
//-------------------------------------------------
#ifndef _SYSTEM_TIMER_QUARTER_RESOLUTION
#define _SYSTEM_TIMER_QUARTER_RESOLUTION                        _OFF
#endif

//--------------------------------------------------
//  Factory Debug Option --> Extern ScalerSetByte, ScalerGetByte, ScalerSetBit, ScalerGetBit to User
//--------------------------------------------------
#ifndef _FACTORY_DEBUG_SUPPORT
#define _FACTORY_DEBUG_SUPPORT                                  _OFF
#endif

//-------------------------------------------------
// Flash Enable Write protect Option
//-------------------------------------------------
#ifndef _FLASH_WR_PROTECT
#define _FLASH_WR_PROTECT                                       _OFF
#endif

//--------------------------------------------------
// FLASH Write SR Mode Select Eable Write SR CMD
//--------------------------------------------------
#ifndef _FLASH_EWSR_FUNCTION_SUPPORT
#define _FLASH_EWSR_FUNCTION_SUPPORT                            _OFF
#endif


//////////
// Acer //
//////////

//-------------------------------------------------
// Acer TMDS Toggle HPD & Z0 Option
//-------------------------------------------------
#ifndef _TMDS_TOGGLE_HPD_Z0_FOR_ACER
#define _TMDS_TOGGLE_HPD_Z0_FOR_ACER                            _OFF
#endif


//////////
// Asus //
//////////

//-------------------------------------------------
// Asus Auto Search Time Option --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)
//-------------------------------------------------
#ifndef _SOURCE_ASUS_START_AUTO_TIME
#define _SOURCE_ASUS_START_AUTO_TIME                            SEC(2)
#endif


//////////
// DELL //
//////////

//--------------------------------------------------
// DELL DP D3 Options --> for DELL
//--------------------------------------------------
#ifndef _DP_DELL_D3_TEST_SUPPORT
#define _DP_DELL_D3_TEST_SUPPORT                                _OFF
#endif


////////
// HP //
////////

//--------------------------------------------------
// HP Source Scan Define Option
//--------------------------------------------------
#ifndef _HP_SOURCE_SCAN_SUPPORT
#define _HP_SOURCE_SCAN_SUPPORT                                 _OFF
#endif

#ifndef _HP_SOURCE_SCAN_TYPE
#define _HP_SOURCE_SCAN_TYPE                                    _HP_SOURCE_SCAN_TYPE_F
#endif


//////////
// Eizo //
//////////

//--------------------------------------------------
// Eizo DP Sink Support OUI Under Ver1.1 Option
//--------------------------------------------------
#ifndef _DP_SINK_VER11_OUI_SUPPORT
#define _DP_SINK_VER11_OUI_SUPPORT                              _ON
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_SINK_RTK_IEEE_OUI_L
#define _DP_SINK_RTK_IEEE_OUI_L                                 0x00
#endif

#ifndef _DP_SINK_RTK_IEEE_OUI_M
#define _DP_SINK_RTK_IEEE_OUI_M                                 0xE0
#endif

#ifndef _DP_SINK_RTK_IEEE_OUI_H
#define _DP_SINK_RTK_IEEE_OUI_H                                 0x4C
#endif

#ifndef _DP_SINK_RTK_ID_STRING_0
#define _DP_SINK_RTK_ID_STRING_0                                0x44
#endif

#ifndef _DP_SINK_RTK_ID_STRING_1
#define _DP_SINK_RTK_ID_STRING_1                                0x70
#endif

#ifndef _DP_SINK_RTK_ID_STRING_2
#define _DP_SINK_RTK_ID_STRING_2                                0x31
#endif

#ifndef _DP_SINK_RTK_ID_STRING_3
#define _DP_SINK_RTK_ID_STRING_3                                0x2E
#endif

#ifndef _DP_SINK_RTK_ID_STRING_4
#define _DP_SINK_RTK_ID_STRING_4                                0x32
#endif

#ifndef _DP_SINK_RTK_ID_STRING_5
#define _DP_SINK_RTK_ID_STRING_5                                0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_SINK_RTK_HW_VERSION
#define _DP_SINK_RTK_HW_VERSION                                 0x00
#endif

#ifndef _DP_SINK_RTK_FW_VERSION_H
#define _DP_SINK_RTK_FW_VERSION_H                               0x00
#endif

#ifndef _DP_SINK_RTK_FW_VERSION_L
#define _DP_SINK_RTK_FW_VERSION_L                               0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_BRANCH_RTK_IEEE_OUI_L
#define _DP_BRANCH_RTK_IEEE_OUI_L                               0x00
#endif

#ifndef _DP_BRANCH_RTK_IEEE_OUI_M
#define _DP_BRANCH_RTK_IEEE_OUI_M                               0xE0
#endif

#ifndef _DP_BRANCH_RTK_IEEE_OUI_H
#define _DP_BRANCH_RTK_IEEE_OUI_H                               0x4C
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_0
#define _DP_BRANCH_RTK_ID_STRING_0                              0x44
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_1
#define _DP_BRANCH_RTK_ID_STRING_1                              0x70
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_2
#define _DP_BRANCH_RTK_ID_STRING_2                              0x31
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_3
#define _DP_BRANCH_RTK_ID_STRING_3                              0x2E
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_4
#define _DP_BRANCH_RTK_ID_STRING_4                              0x32
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_5
#define _DP_BRANCH_RTK_ID_STRING_5                              0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_BRANCH_RTK_HW_VERSION
#define _DP_BRANCH_RTK_HW_VERSION                               0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_H
#define _DP_BRANCH_RTK_FW_VERSION_H                             0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_L
#define _DP_BRANCH_RTK_FW_VERSION_L                             0x00
#endif


////////
// LG //
////////

//--------------------------------------------------
//  LG DP Power Management
//--------------------------------------------------
#ifndef _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER
#define _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER           _OFF
#endif

//===================== END =======================

