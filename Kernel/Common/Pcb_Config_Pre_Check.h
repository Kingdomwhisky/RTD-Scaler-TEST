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
// ID Code      : Pcb_Config_Pre_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_CONFIG_PRE_CHECK_H__
#define __PCB_CONFIG_PRE_CHECK_H__

///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// DP Macro Pre-Check
//--------------------------------------------------
#ifdef _D0_INPUT_PORT_TYPE
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#ifndef PCB_D0_HOTPLUG_DETECT
#ifndef _D0_DP_CONNECTOR_TYPE
#warning "PCB_D0_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#else

#if(_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C)
#warning "PCB_D0_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#else
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED)
#warning "PCB_D0_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#endif
#endif

#endif // END of #ifndef _D0_DP_CONNECTOR_TYPE
#endif // End of #ifndef PCB_D0_HOTPLUG_DETECT

#if(_DP_MST_SUPPORT == _ON)

#ifndef GET_PCB_D0_DP_SOURCE_POWER
#warning "GET_PCB_D0_DP_SOURCE_POWER() Should Be Defined!!!"
#endif

#ifdef _D0_DP_CONNECTOR_TYPE
#ifdef _D0_DP_TYPE_C_PORT_CTRL_TYPE
#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)))
#if(_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP
#warning "GET_PCB_D0_DP_SOURCE_POWER_PN_SWAP() Should Be Defined!!!"
#endif
#endif
#endif
#endif
#endif

#endif

#ifdef _D0_DP_CONNECTOR_TYPE
#ifdef _D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK
#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO))
#ifndef PCB_D0_CC_ATTACH_PIN
#warning "PCB_D0_CC_ATTACH_PIN() Should Be Defined!!!"
#endif

#ifndef PCB_D0_ALT_MODE_PIN
#warning "PCB_D0_ALT_MODE_PIN() Should Be Defined!!!"
#endif
#endif
#endif
#endif

#ifdef _D0_DP_CONNECTOR_TYPE
#ifdef _D0_DP_TYPE_C_PORT_CTRL_TYPE
#if((_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)))
#if(_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef PCB_D0_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_D0_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#ifndef PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_GET_D0_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#endif
#endif
#endif
#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#endif // End of #ifdef _D0_INPUT_PORT_TYPE

#ifdef _D1_INPUT_PORT_TYPE
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#ifndef PCB_D1_HOTPLUG_DETECT
#warning "PCB_D1_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#endif

#if(_DP_MST_SUPPORT == _ON)

#ifndef GET_PCB_D1_DP_SOURCE_POWER
#warning "GET_PCB_D1_DP_SOURCE_POWER() Should Be Defined!!!"
#endif

#ifdef _D1_DP_CONNECTOR_TYPE
#ifdef _D1_DP_TYPE_C_PORT_CTRL_TYPE
#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)))
#if(_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP
#warning "GET_PCB_D1_DP_SOURCE_POWER_PN_SWAP() Should Be Defined!!!"
#endif
#endif
#endif
#endif
#endif

#endif

#ifdef _D1_DP_CONNECTOR_TYPE
#ifdef _D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK
#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO))
#ifndef PCB_D1_CC_ATTACH_PIN
#warning "PCB_D1_CC_ATTACH_PIN() Should Be Defined!!!"
#endif

#ifndef PCB_D1_ALT_MODE_PIN
#warning "PCB_D1_ALT_MODE_PIN() Should Be Defined!!!"
#endif
#endif
#endif
#endif

#ifdef _D1_DP_CONNECTOR_TYPE
#ifdef _D1_DP_TYPE_C_PORT_CTRL_TYPE
#if((_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)))
#if(_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef PCB_D1_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_D1_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#ifndef PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_GET_D1_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#endif
#endif
#endif
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#endif // End of #ifdef _D1_INPUT_PORT_TYPE

#ifdef _D2_INPUT_PORT_TYPE
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#ifndef PCB_D2_HOTPLUG_DETECT
#warning "PCB_D2_HOTPLUG_DETECT() Should Be Defined as A HotPlug GPIO Pin!!!"
#endif

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#endif // End of #ifdef _D2_INPUT_PORT_TYPE

#ifdef _D6_INPUT_PORT_TYPE
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_DP_MST_SUPPORT == _ON))

#ifndef GET_PCB_D6_DP_SOURCE_POWER
#warning "GET_PCB_D6_DP_SOURCE_POWER() Should Be Defined!!!"
#endif

#ifdef _D6_DP_CONNECTOR_TYPE
#ifdef _D6_DP_TYPE_C_PORT_CTRL_TYPE
#if((_D6_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)))
#if(_D6_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef GET_PCB_D6_DP_SOURCE_POWER_PN_SWAP
#warning "GET_PCB_D6_DP_SOURCE_POWER_PN_SWAP() Should Be Defined!!!"
#endif
#endif
#endif
#endif
#endif

#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

#ifdef _D6_DP_CONNECTOR_TYPE
#ifdef _D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK
#if((_D6_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_GPIO))
#ifndef PCB_D6_CC_ATTACH_PIN
#warning "PCB_D6_CC_ATTACH_PIN() Should Be Defined!!!"
#endif

#ifndef PCB_D6_ALT_MODE_PIN
#warning "PCB_D6_ALT_MODE_PIN() Should Be Defined!!!"
#endif
#endif
#endif
#endif

#ifdef _D6_DP_CONNECTOR_TYPE
#ifdef _D6_DP_TYPE_C_PORT_CTRL_TYPE
#if((_D6_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C) && ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)))
#if(_D6_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER)
#ifndef PCB_D6_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_D6_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#ifndef PCB_GET_D6_AUX_PN_1M_PULL_H_L_SWAP
#warning "PCB_GET_D6_AUX_PN_1M_PULL_H_L_SWAP() Should Be Defined!!!"
#endif

#endif
#endif
#endif
#endif

#endif

#endif // End of #ifdef _D6_INPUT_PORT_TYPE


///////////////////////
// PC99 EDID Config ///
///////////////////////

//--------------------------------------------------
// PC99 EDID Pre-Check
//--------------------------------------------------
#ifdef _A0_EMBEDDED_DDCRAM_LOCATION

#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)
#ifndef _A0_EMBEDDED_DDCRAM_MAX_SIZE
#warning "_A0_EMBEDDED_DDCRAM_MAX_SIZE Should be Defined!!!"
#else
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
#warning "_A0_EMBEDDED_DDCRAM_MAX_SIZE Cannot be _EDID_SIZE_NONE!!!"
#endif
#endif
#endif

#endif

#ifdef _D0_EMBEDDED_DDCRAM_LOCATION

#if(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)
#ifndef _D0_EMBEDDED_DDCRAM_MAX_SIZE
#warning "_D0_EMBEDDED_DDCRAM_MAX_SIZE Should be Defined!!!"
#else
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
#warning "_D0_EMBEDDED_DDCRAM_MAX_SIZE Cannot be _EDID_SIZE_NONE!!!"
#endif
#endif
#endif

#endif

#ifdef _D1_EMBEDDED_DDCRAM_LOCATION

#if(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)
#ifndef _D1_EMBEDDED_DDCRAM_MAX_SIZE
#warning "_D1_EMBEDDED_DDCRAM_MAX_SIZE Should be Defined!!!"
#else
#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
#warning "_D1_EMBEDDED_DDCRAM_MAX_SIZE Cannot be _EDID_SIZE_NONE!!!"
#endif
#endif
#endif

#endif


//--------------------------------------------------
// HDMI Macro Pre-Check
//--------------------------------------------------

#ifdef _D0_MAX_HDMI_EDID_COUNT
#if(_D0_MAX_HDMI_EDID_COUNT > 1)
#define _PCB_MULTI_EDID_SWITCH_CHECK                    _ON
#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif
#endif

#ifdef _D1_MAX_HDMI_EDID_COUNT
#if(_D1_MAX_HDMI_EDID_COUNT > 1)
#define _PCB_MULTI_EDID_SWITCH_CHECK                    _ON
#endif
#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D2_MAX_HDMI_EDID_COUNT
#if(_D2_MAX_HDMI_EDID_COUNT > 1)
#define _PCB_MULTI_EDID_SWITCH_CHECK                    _ON
#endif
#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D3_MAX_HDMI_EDID_COUNT
#if(_D3_MAX_HDMI_EDID_COUNT > 1)
#define _PCB_MULTI_EDID_SWITCH_CHECK                    _ON
#endif
#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D4_MAX_HDMI_EDID_COUNT
#if(_D4_MAX_HDMI_EDID_COUNT > 1)
#define _PCB_MULTI_EDID_SWITCH_CHECK                    _ON
#endif
#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _D5_MAX_HDMI_EDID_COUNT
#if(_D5_MAX_HDMI_EDID_COUNT > 1)
#define _PCB_MULTI_EDID_SWITCH_CHECK                    _ON
#endif
#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
#define _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK            _ON
#endif
#endif

#ifdef _PCB_MULTI_EDID_SWITCH_CHECK
#ifndef PCB_MULTI_EDID_SWITCH
#warning "PCB_MULTI_EDID_SWITCH() Should Be Defined!!!"
#endif
#endif

#ifdef _PCB_MULTI_EDID_ALL_SWITCH_OFF_CHECK
#ifndef PCB_MULTI_EDID_ALL_SWITCH_OFF
#warning "PCB_MULTI_EDID_ALL_SWITCH_OFF() Should Be Defined!!!"
#endif
#endif

//--------------------------------------------------
// RTS SMBUS Arbit Control Pre-Check
//--------------------------------------------------

#ifdef _RTS_SMBUS_ARBITRATION_MODE_SEL
#if(_RTS_SMBUS_ARBITRATION_MODE_SEL == _RTS_SMBUS_ARBITRATION_DELAY_MODE)

#ifndef PCB_CHECK_RTS_SMBUS_BUSY_STATUS
#warning "PCB_CHECK_RTS_SMBUS_BUSY_STATUS() Should Be Defined!!!"
#endif

#ifndef PCB_SET_RTS_SMBUS_BUSY
#warning "PCB_SET_RTS_SMBUS_BUSY() Should Be Defined!!!"
#endif

#elif(_RTS_SMBUS_ARBITRATION_MODE_SEL == _RTS_SMBUS_ARBITRATION_HANDSHAKE_MODE)

#ifndef PCB_CHECK_RTS_SMBUS_BUSY_STATUS
#warning "PCB_CHECK_RTS_SMBUS_BUSY_STATUS() Should Be Defined!!!"
#endif

#ifndef PCB_RELEASE_RTS_SMBUS_BUSY
#warning "PCB_RELEASE_RTS_SMBUS_BUSY() Should Be Defined!!!"
#endif

#ifndef PCB_SET_RTS_SMBUS_BUSY
#warning "PCB_SET_RTS_SMBUS_BUSY() Should Be Defined!!!"
#endif

#endif
#endif

#endif // End of #ifndef __PCB_CONFIG_PRE_CHECK_H__
