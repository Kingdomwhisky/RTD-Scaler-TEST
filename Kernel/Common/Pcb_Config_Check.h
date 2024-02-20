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
// ID Code      : Pcb_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_CONFIG_CHECK_H__
#define __PCB_CONFIG_CHECK_H__

/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of Embedded LDO Support
//-----------------------------------------------
#if(_SCALER_TYPE == _RL6369_SERIES)

#if(PCB_EMBEDDED_LDO_DETECT() == _EMBEDDED_LDO_ON)
#warning "PCB_EMBEDDED_LDO_DETECT() Should Be _EMBEDDED_LDO_OFF!!!"
#endif

#endif

///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// PCB DP Lane Swap Check
//--------------------------------------------------
#if(_HW_DP_LANE_SWAP_SUPPORT == _OFF)
#if((_D0_DP_PCB_LANE0_MAPPING != _DP_SCALER_LANE0) ||\
    (_D0_DP_PCB_LANE1_MAPPING != _DP_SCALER_LANE1) ||\
    (_D0_DP_PCB_LANE2_MAPPING != _DP_SCALER_LANE2) ||\
    (_D0_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3) ||\
    (_D1_DP_PCB_LANE0_MAPPING != _DP_SCALER_LANE0) ||\
    (_D1_DP_PCB_LANE1_MAPPING != _DP_SCALER_LANE1) ||\
    (_D1_DP_PCB_LANE2_MAPPING != _DP_SCALER_LANE2) ||\
    (_D1_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3))
#warning "DP Lane Swap Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// PCB DP PN Swap Check
//--------------------------------------------------
#if(_HW_DP_PN_SWAP_SUPPORT == _OFF)
#if((_D0_DP_PCB_LANE0_PN_SWAP == _ON) || (_D0_DP_PCB_LANE1_PN_SWAP == _ON) ||\
    (_D0_DP_PCB_LANE2_PN_SWAP == _ON) || (_D0_DP_PCB_LANE3_PN_SWAP == _ON) ||\
    (_D1_DP_PCB_LANE0_PN_SWAP == _ON) || (_D1_DP_PCB_LANE1_PN_SWAP == _ON) ||\
    (_D1_DP_PCB_LANE2_PN_SWAP == _ON) || (_D1_DP_PCB_LANE3_PN_SWAP == _ON))
#warning "DP PN Swap Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// DP HBR2 Margin Link Support Check
//--------------------------------------------------
#if(_DP_HBR2_MARGIN_LINK_SUPPORT == _ON)
#if((_D0_DP_LINK_CLK_RATE < _DP_HIGH_SPEED2_540MHZ) &&\
    (_D1_DP_LINK_CLK_RATE < _DP_HIGH_SPEED2_540MHZ) &&\
    (_D6_DP_LINK_CLK_RATE < _DP_HIGH_SPEED2_540MHZ))
#warning "_DP_HBR2_MARGIN_LINK_SUPPORT Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// DP RL6492 Input Port Type Constraint
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6492_SERIES)
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) &&\
    (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
#warning "D1 & D2 Type Can Not Be Assigned to DP Concurrently!!!"
#endif
#endif

//--------------------------------------------------
// DDC Mapping Check
//--------------------------------------------------
#if(((_D0_DDC_CHANNEL_SEL != _NO_DDC) && (_D0_DDC_CHANNEL_SEL != _DDC0)) ||\
    ((_D1_DDC_CHANNEL_SEL != _NO_DDC) && (_D1_DDC_CHANNEL_SEL != _DDC1)) ||\
    ((_D2_DDC_CHANNEL_SEL != _NO_DDC) && (_D2_DDC_CHANNEL_SEL != _DDC2)) ||\
    ((_D3_DDC_CHANNEL_SEL != _NO_DDC) && (_D3_DDC_CHANNEL_SEL != _DDC3)) ||\
    ((_D4_DDC_CHANNEL_SEL != _NO_DDC) && (_D4_DDC_CHANNEL_SEL != _DDC4)) ||\
    ((_D5_DDC_CHANNEL_SEL != _NO_DDC) && (_D5_DDC_CHANNEL_SEL != _DDC5)))

#if(_DDC_CHANNEL_SWITCH_SUPPORT == _OFF)
#warning "D0 or D1 or D2 or D3 or D4 or D5 Select Wrong DDC Channel!!!"
#else
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _OFF)
#warning "_DDCCI_AUTO_SWITCH_SUPPORT should be _ON!!!"
#endif
#endif

#endif

//--------------------------------------------------
// Input Port Type & DDC Channel Status Check
//--------------------------------------------------
#if(((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _NO_DDC)))
#warning "When D0 or D1 or D2 or D3 or D4 or D5 Input Port Type Select not _NO_PORT, DDC Channel Can't be _NO_DDC!!!"
#endif

//--------------------------------------------------
// Dual Link DVI Check
//--------------------------------------------------
#if(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_NONE)
#if(_DUAL_DVI_SUPPORT == _ON)
#warning "Dual Link DVI Port Can't Use in This Project!!!"
#endif
#elif(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_D2)
#if((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#warning "D3 or D4 Input Port Can't be Dual DVI Port!!!"
#endif
#elif(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_D4)
#if((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
#warning "D2 or D3 Input Port Can't be Dual DVI Port!!!"
#endif
#elif(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_D2_D3_D4)
#if(((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)) ||\
     ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)))
#warning "D2&D3 or D3&D4 Input Port Can't both be Dual DVI Port!!!"
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#warning "_D3_INPUT_PORT_TYPE Should Be _D3_NO_PORT!!!"
#endif

#if(_D3_DDC_CHANNEL_SEL == _NO_DDC)
#warning "When D2 Input Port Type is Dual Link DVI Port, D3 DDC Channel Can't be _NO_DDC!!!"
#endif

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#warning "_D4_INPUT_PORT_TYPE Should Be _D4_NO_PORT!!!"
#endif

#if(_D4_DDC_CHANNEL_SEL == _NO_DDC)
#warning "When D3 Input Port Type is Dual Link DVI Port, D4 DDC Channel Can't be _NO_DDC!!!"
#endif

#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#warning "_D5_INPUT_PORT_TYPE Should Be _D5_NO_PORT!!!"
#endif

#if(_D5_DDC_CHANNEL_SEL == _NO_DDC)
#warning "When D4 Input Port Type is Dual Link DVI Port, D5 DDC Channel Can't be _NO_DDC!!!"
#endif

#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

//--------------------------------------------------
// VGA Port Check
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6369_SERIES) ||\
    (_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RL6463_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))
#if((_A1_INPUT_PORT_TYPE != _A1_NO_PORT) || (_A2_INPUT_PORT_TYPE != _A2_NO_PORT))
#warning "_A1_VGA_PORT & _A2_VGA_PORT Can Not Be Supported!!!"
#endif
#endif

#if((_A1_INPUT_PORT_TYPE != _A1_NO_PORT) || (_A2_INPUT_PORT_TYPE != _A2_NO_PORT))
#if(_A0_INPUT_PORT_TYPE == _A0_NO_PORT)
#warning "_A0_INPUT_PORT_TYPE Should Be _A0_VGA_PORT!!!"
#endif
#endif

//--------------------------------------------------
// USB && Port Controller Relationship Setting Check
//--------------------------------------------------
#if((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _OFF) && (_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE))
#warning "'_D0_DP_TYPE_C_USB_HUB_TYPE' should be select '_USB_HUB_NONE' if '_D0_DP_CONNECTOR_TYPE' == '_PORT_CONTROLLER_NONE'!!!"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _OFF) && (_D1_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE))
#warning "'_D1_DP_TYPE_C_USB_HUB_TYPE' should be select '_USB_HUB_NONE' if '_D1_DP_CONNECTOR_TYPE' == '_PORT_CONTROLLER_NONE''!!!"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _OFF) && (_D6_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE))
#warning "'_D6_DP_TYPE_C_USB_HUB_TYPE' should be select '_USB_HUB_NONE' if '_D6_DP_CONNECTOR_TYPE' == '_PORT_CONTROLLER_NONE''!!!"
#endif

//-------------------------------------------------
// Type-C Relationship Option Check
//-------------------------------------------------
#if((_TYPE_C_RTS5400_SERIES_SPEC_VER_SEL < _RTS5400_SERIES_FW_SPEC_VERSION_V0D9) && (_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT == _ON))
#warning "_TYPE_C_RTS5400_SERIES_PDO_INFO_SUPPORT Need Change to _RTS5400_SERIES_FW_SPEC_VERSION_V0D9 or uper version~ !!"
#endif

//--------------------------------------------------
// Type-C && Port Controller Aux PN Swap Setting Check
//--------------------------------------------------
#if(_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER))
#warning "NOTE: Please Confirm D0 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_NOT_EXIST))
#warning "D0 Discrete Port Controller Link For _PORT_CONTROLLER_RTS5400_SERIES Should NOT Use _DISCRETE_PORT_CTRL_NOT_EXIST"
#endif

#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER) && (_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER' and '_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER'"
#endif

#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && ((_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_NOT_EXIST) || (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)))
#warning "D0 Discrete Port Controller Link For _PORT_CONTROLLER_USER Should Use _DISCRETE_PORT_CTRL_USE_GPIO or _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN"
#endif

#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_NOT_EXIST))
#warning "D0 Discrete Port Controller Link For _PORT_CONTROLLER_EMBEDDED Should Use _DISCRETE_PORT_CTRL_NOT_EXIST"
#endif
#endif

#if(_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER))
#warning "NOTE: Please Confirm D1 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_NOT_EXIST))
#warning "D1 Discrete Port Controller Link For _PORT_CONTROLLER_RTS5400_SERIES Should NOT Use _DISCRETE_PORT_CTRL_NOT_EXIST"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER) && (_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER' and '_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER'"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && ((_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_NOT_EXIST) || (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)))
#warning "D1 Discrete Port Controller Link For _PORT_CONTROLLER_USER Should Use _DISCRETE_PORT_CTRL_USE_GPIO or _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_NOT_EXIST))
#warning "D1 Discrete Port Controller Link For _PORT_CONTROLLER_EMBEDDED Should Use _DISCRETE_PORT_CTRL_NOT_EXIST"
#endif
#endif

#if(_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D6_DP_TYPE_C_PIN_E_AUXPN_SWAP == _SWAP_BY_SCALER))
#warning "NOTE: Please Confirm D6 Aux PN Swap By Scaler Under Pinassignment E Mode ~!!"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_NOT_EXIST))
#warning "D6 Discrete Port Controller Link For _PORT_CONTROLLER_RTS5400_SERIES Should NOT Use _DISCRETE_PORT_CTRL_NOT_EXIST"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER) && (_D6_DP_TYPE_C_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "'_D6_DP_TYPE_C_PIN_E_AUXPN_SWAP' should be selected '_SWAP_BY_SCALER' if '_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER' and '_TYPE_C_EXT_PORT_CTRL_LANE_SWAP_OPTION == _TYPE_C_LANE_SWAP_BY_SCALER'"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && ((_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_NOT_EXIST) || (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_SMBUS)))
#warning "D6 Discrete Port Controller Link For _PORT_CONTROLLER_USER Should Use _DISCRETE_PORT_CTRL_USE_GPIO or _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK != _DISCRETE_PORT_CTRL_NOT_EXIST))
#warning "D6 Discrete Port Controller Link For _PORT_CONTROLLER_EMBEDDED Should Use _DISCRETE_PORT_CTRL_NOT_EXIST"
#endif
#endif

//--------------------------------------------------
// Bill Board Support Setting Check
//--------------------------------------------------
#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED) && (_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER))
#warning "'_D0_DP_TYPE_C_BILLBOARD_TYPE' should not be selected '_BILLBOARD_SCALER' if '_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED'"
#endif

#if((_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_NONE))
#warning "'_D0_DP_TYPE_C_BILLBOARD_TYPE' should not be selected '_BILLBOARD_HUB' if '_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_NONE'"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED) && (_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER))
#warning "'_D0_DP_TYPE_C_BILLBOARD_TYPE' should not be selected '_BILLBOARD_SCALER' if '_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED'"
#endif

#if((_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D1_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_NONE))
#warning "'_D0_DP_TYPE_C_BILLBOARD_TYPE' should not be selected '_BILLBOARD_HUB' if '_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_NONE'"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED) && (_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER))
#warning "'_D0_DP_TYPE_C_BILLBOARD_TYPE' should not be selected '_BILLBOARD_SCALER' if '_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_EMBEDDED'"
#endif

#if((_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D6_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_NONE))
#warning "'_D0_DP_TYPE_C_BILLBOARD_TYPE' should not be selected '_BILLBOARD_HUB' if '_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_NONE'"
#endif

//--------------------------------------------------
// Type-C && Port Controller IIC Check
//--------------------------------------------------
#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D0_DP_TYPE_C_RTK_PC_SMBUS_IIC == _NO_IIC_PIN))
#warning "D0 SMBUS IIC Not Defined When D0 Port Controller = 5400"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D1_DP_TYPE_C_RTK_PC_SMBUS_IIC == _NO_IIC_PIN))
#warning "D1 SMBUS IIC Not Defined When D1 Port Controller = 5400"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D6_DP_TYPE_C_RTK_PC_SMBUS_IIC == _NO_IIC_PIN))
#warning "D6 SMBUS IIC Not Defined When D6 Port Controller = 5400"
#endif

//--------------------------------------------------
// Type-C Port Controller & Type-C Connector Type Setting Check
//--------------------------------------------------
#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE) && (_D0_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C))
#warning "'_D0_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C'' if '_D0_DP_TYPE_C_PORT_CTRL_TYPE' != _PORT_CONTROLLER_NONE' !!!"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE) && (_D1_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C))
#warning "'_D1_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C'' if '_D1_DP_TYPE_C_PORT_CTRL_TYPE' != _PORT_CONTROLLER_NONE' !!!"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE) && (_D6_DP_CONNECTOR_TYPE != _DP_CONNECTOR_TYPE_C))
#warning "'_D6_DP_CONNECTOR_TYPE' Shall be '_DP_CONNECTOR_TYPE_C'' if '_D6_DP_TYPE_C_PORT_CTRL_TYPE' != _PORT_CONTROLLER_NONE' !!!"
#endif

//--------------------------------------------------
// TYPE-C Port Role Check
//--------------------------------------------------
#if((_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_D0_DP_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "Type-C Port Role is Source-Only. D0 Dead Battery Should NOT Support."
#endif

#if((_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY) && (_D1_DP_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))
#warning "Type-C Port Role is Source-Only. D0 Dead Battery Should NOT Support."
#endif

//--------------------------------------------------
// DP Max Link Rate Setting Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#if(_HW_DP_D0_MAX_LINK_RATE_SUPPORT < _D0_DP_LINK_CLK_RATE)
#warning "Please Confirm D0 Port Max Link Rate Over HW Support~!!"
#endif
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#if(_HW_DP_D1_MAX_LINK_RATE_SUPPORT < _D1_DP_LINK_CLK_RATE)
#warning "Please Confirm D1 Port Max Link Rate Over HW Support~!!"
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#if(_HW_DP_D2_MAX_LINK_RATE_SUPPORT < _D2_DP_LINK_CLK_RATE)
#warning "Please Confirm D2 Port Max Link Rate Over HW Support~!!"
#endif
#endif

#ifdef __USER_COMMON_INTERFACE__

//--------------------------------------------------
// A0 EDID Location Check
//--------------------------------------------------
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
#if((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check A0 EDID table location!!!"
#endif

#if(_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)
#if((_HW_PC99_SUPPORT != _ON) ||\
    (_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE))
#warning "_A0_EMBEDDED_DDCRAM_LOCATION cannot be _EDID_TABLE_LOCATION_PC99"
#endif
#endif

#endif

//--------------------------------------------------
// D0 EDID Location Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D0 EDID table location!!!"
#endif
#if((_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D0 MHL EDID table location!!!"
#endif

#if(_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)
#if((_HW_PC99_SUPPORT != _ON) ||\
    (_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE))
#warning "_D0_EMBEDDED_DDCRAM_LOCATION cannot be _EDID_TABLE_LOCATION_PC99"
#endif
#endif

// D0 Multi Edid Check
#if(_D0_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: Please Check D0 External Edid's Index Should be 0~11 !!!"
#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
//--------------------------------------------------
// D1 EDID Location Check
//--------------------------------------------------
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D1 EDID table location!!!"
#endif
#if((_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D1 MHL EDID table location!!!"
#endif

#if(_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_PC99)
#if((_HW_PC99_SUPPORT != _ON) ||\
    (_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE))
#warning "_D1_EMBEDDED_DDCRAM_LOCATION cannot be _EDID_TABLE_LOCATION_PC99"
#endif
#endif

// D1 Multi Edid Check
#if(_D1_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: Please Check D1 External Edid's Index Should be 0~11 !!!"
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
//--------------------------------------------------
// D2 EDID Location Check
//--------------------------------------------------
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#if((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D2 EDID table location!!!"
#endif
#if((_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D2 MHL EDID table location!!!"
#endif

// D2 Multi Edid Check
#if(_D2_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: Please Check D2 External Edid's Index Should be 0~11 !!!"
#endif

#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

//--------------------------------------------------
// D3 EDID Location Check
//--------------------------------------------------
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#if((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D3 EDID table location!!!"
#endif
#if((_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D3 MHL EDID table location!!!"
#endif

// D3 Multi Edid Check
#if(_D3_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: Please Check D3 External Edid's Index Should be 0~11 !!!"
#endif

#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

//--------------------------------------------------
// D4 EDID Location Check
//--------------------------------------------------
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#if((_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D4 EDID table location!!!"
#endif
#if((_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D4 MHL EDID table location!!!"
#endif

// D4 Multi Edid Check
#if(_D4_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: Please Check D4 External Edid's Index Should be 0~11 !!!"
#endif

#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

//--------------------------------------------------
// D5 EDID Location Check
//--------------------------------------------------
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#if((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D5 EDID table location!!!"
#endif
#if((_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D5 MHL EDID table location!!!"
#endif

// D5 Multi Edid Check
#if(_D5_MAX_HDMI_EDID_COUNT > 12)
#warning "NOTE: Please Check D5 External Edid's Index Should be 0~11 !!!"
#endif

#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

//--------------------------------------------------
// D6 EDID Location Check
//--------------------------------------------------
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
#if((_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "NOTE: Please check D6 EDID table location!!!"
#endif
#endif

#endif // End of #ifdef __USER_COMMON_INTERFACE__


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Panel
//--------------------------------------------------
#if(_LVDS_VCM_USER_LEVEL > 0x1F)
#warning "LVDS VCM Selection Exceed The Maximum Value"
#endif

#if((_SCALER_TYPE == _RL6369_SERIES) ||\
    (_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))

#if((_LVDS_DRIV_CONTROL > _LVDS_DRIV_CONTROL_3_5) && (_LVDS_DRIV_CONTROL <= _LVDS_DRIV_CONTROL_4_5))
#warning "LVDS Driving Control Selection Exceed The Maximum Value"
#endif

#endif


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Panel Config Check
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)

#if((_PANEL_DPTX_1_1_SWING_LEVEL + _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL) > 2)
#warning "Panel DPTX 1.1 Swing and Pre-emphasis over Spec!!!"
#endif

#if(_PANEL_DPTX_1_1_SPREAD_SPEED == _SPEED_66K)
#warning "Panel DPTx Spread Spectrum Speed Should Be 30kHz~33kHz"
#endif


//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Panel Config Check
//--------------------------------------------------
#if((_PANEL_DPTX_1_2_SWING_LEVEL + _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL) > 3)
#warning "Panel DPTX 1.2 Swing and Pre-emphasis over Spec!!!"
#endif

#if(_PANEL_DPTX_1_2_SPREAD_SPEED == _SPEED_66K)
#warning "Panel DPTx Spread Spectrum Speed Should Be 30kHz~33kHz"
#endif

#endif


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Panel Config Check
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_VBO)
#if(_VBO_SPREAD_SPEED != _SPEED_30K)
#warning "Vbyone Spread Spectrum Speed Should Be 30kHz"
#endif
#endif


/////////////////
// Memory DDR3 //
/////////////////

//--------------------------------------------------
// DDR3 of Multi Phase For Different Vendor
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR3)
#if(_DDR3_MULTIPHASE_EXIST == _ON)
#warning "This Function Can Not Be _ON without DDR3"
#endif
#endif

//-----------------------------------------------
// Macro of DDR Poewr Release Time Control
//-----------------------------------------------
#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR2) || (_MEMORY_TYPE_CONFIG == _MEMORY_DDR3))
#if(_DDR_POWER_OFF_TIME > 1000)
#warning "DDR Power Off Time Delay Should Be Less 1S"
#endif
#endif


////////////////
// MBR + TCON //
////////////////
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_PCB_MBR_TCON_PIN == _GEN_NONE)
#warning "_PCB_MBR_TCON_PIN Should Be Specified When _MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif

#if((_PWM_RST_SIGNAL_SEL == _TCON) && (_PCB_MBR_TCON_PIN == _TCON8)) // _HW_PWM_RST_BY_TCON_SELECT == _TCON8
#warning "_PCB_MBR_TCON_PIN Cannot Be _TCON8 When _PWM_RST_SIGNAL_SEL == _TCON"
#endif

#if(_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if(_PWM_RST_SIGNAL_SEL == _TCON) // _HW_PWM_RST_BY_TCON_SELECT == _TCON8
#warning "_PWM_RST_SIGNAL_SEL Cannot Be _TCON When _DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif

#if(_PCB_MBR_TCON_PIN < _TCON8)
#warning "_PCB_MBR_TCON_PIN Must >= _TCON8 When _DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif
#endif

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
#if((_PCB_MBR_TCON_PIN <= _TCON3) || (_PCB_MBR_TCON_PIN == _TCON8) || (_PCB_MBR_TCON_PIN == _TCON9)) // Valid TCON for RTK_ADV_MBR: 4, 5, 6, 7, 10, 11, 12, 13
#warning "_PCB_MBR_TCON_PIN Should Be TCON 4/5/6/7/10/11/12/13 When _RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON"
#endif
#endif
#endif


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// SW & HW IIC
//--------------------------------------------------
#if (_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)
#if(_SW_IIC_SUPPORT == _OFF)
#warning "If using SW IIC _SW_IIC_SUPPORT Should Be ON"
#endif
#endif

#if (_PCB_SEC_EEPROM_IIC == _SW_IIC_PIN_GPIO)
#if(_SW_IIC_SUPPORT == _OFF)
#warning "If using SW IIC _SW_IIC_SUPPORT Should Be ON"
#endif
#endif

#if(_SW_IIC_SUPPORT == _ON)
#if(_SW_IIC_CLK_DIV > _DIV_7)
#warning "_SW_IIC_CLK_DIV should be less than or equal to _DIV_7"
#endif
#endif

//--------------------------------------------------
// Two Chip Communication Check
//--------------------------------------------------
#if(_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_IIC_SLAVE)

#if(_DP_LONG_HPD_MODE == _DP_LONG_HPD_DELAY_MODE)
#warning "_DP_LONG_HPD_MODE Shall Set'_DP_LONG_HPD_TIMEREVENT_MODE' When _TWO_CHIP_DATA_EXCHANGE_MODE is Supportted!!"
#endif

#if(_HW_IIC_SUPPORT == _OFF)
#warning "_HW_IIC_SUPPORT Should Be _ON!!!"
#endif

#if(!((_SCALER_TYPE == _RL6410_SERIES) || (_SCALER_TYPE == _RL6432_SERIES) || (_SCALER_TYPE == _RL6449_SERIES)))
#warning "_TWO_CHIP_DATA_EXCHANGE_MODE Should Be Set to _DATA_EXCHANGE_MODE_NONE except _RL6410_SERIES or _RL6432_SERIES or _RL6449_SERIES!!!"
#endif

#endif

//--------------------------------------------------
// SPI Funtion Pinshare Config check
//--------------------------------------------------
#if(_SPI_SUPPORT == _ON)
#if((_PIN_SPI_CLK_SELECTED == _TRUE) ||\
    (_PIN_SPI_SI_SELECTED == _TRUE) ||\
    (_PIN_SPI_SO_SELECTED == _TRUE) ||\
    (_PIN_SPI_CEB0_SELECTED == _TRUE) ||\
    (_PIN_SPI_CEB1_SELECTED == _TRUE))

#if((_PIN_SPI_CLK_SELECTED != _TRUE) ||\
    (_PIN_SPI_SI_SELECTED != _TRUE) ||\
    (_PIN_SPI_SO_SELECTED != _TRUE) ||\
    (_PIN_SPI_CEB0_SELECTED != _TRUE) ||\
    (_PIN_SPI_CEB1_SELECTED != _TRUE))
#warning "SPI-related pinshare configurations should be consistent. Either all five pins are configured to be SPI, or none should be."
#endif

#endif
#endif


////////////////
// TypeC Pmic //
////////////////
//--------------------------------------------------
// Pmic Config Check
//--------------------------------------------------
// For All PMIC
#if((_TYPE_C_PMIC_TYPE != _PMIC_NONE) && (_TYPE_C_PMIC_TYPE != _PMIC_SYS_SOLUTION))
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _OFF)
#warning "PMIC is set. _TYPE_C_PMIC_HW_IIC_SUPPORT should be ON!!!"
#endif

#if(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS == 0x00)
#warning "PMIC is set. _TYPE_C_RX0_PMIC_SLAVE_ADDRESS should NOT be 0x00!!!"
#endif
#endif // End of #if((_TYPE_C_PMIC_TYPE != _PMIC_NONE) && (_TYPE_C_PMIC_TYPE != _PMIC_SYS_SOLUTION))

#if((_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) && (_TYPE_C_PMIC_FW_OCP_CURRENT_VALUE < 100))
#warning "PMIC OCP ratio should not less than 100%!!!"
#endif

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _OFF)
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
#warning "PMIC type should be _PMIC_NONE!!!"
#endif
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _OFF)

// For PMIC_NONE
#if(_TYPE_C_PMIC_TYPE == _PMIC_NONE)
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
#warning "PMIC HW IIC is NOT support!!!"
#endif

#if(_TYPE_C_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
#warning "Polling is not support when _TYPE_C_PMIC_TYPE is _PMIC_NONE!!!"
#endif
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_NONE)

// For System_Solution
#if(_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "_PMIC_SYS_SOLUTION can't support PPS!!!"
#endif
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)

// For SY9228
#if(_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9228 can't support PPS!!!"
#endif
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SY9228)

// For SY9329
#if(_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "SY9329 can't support voltage compensation!!!"
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "SY9329 can't support PPS!!!"
#endif
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_SY9329)

// For NCP81239
#if(_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#warning "NCP81239 can't support OCP by polling PMIC ADC!!!"
#endif

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
#warning "NCP81239 can't support PPS!!!"
#endif
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)


//////////
// Misc //
//////////

//--------------------------------------------------
// Flash Latch Edge Option
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RLE0779_SERIES) ||\
    (_SCALER_TYPE == _RL6463_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))
#if(_PCB_FLASH_LATCH_SO_DATA_IN_RISING_EDGE == _ON)
#warning "Flash Latch Edge Can Not Be Change In this IC"
#endif
#endif

//--------------------------------------------------
// Code Digital Signature DDC ISP Select Check
//--------------------------------------------------
#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)

#if(_SCALER_TYPE == _RL6463_SERIES)
#if(_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL != _VGA_DDC)
#warning "_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL must select _VGA_DDC at RL6463"
#endif
#elif(((_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL == _VGA_DDC) && (_A0_INPUT_PORT_TYPE != _A0_NO_PORT)) ||\
      ((_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL == _D0_DDC_CHANNEL_SEL) && (_D0_INPUT_PORT_TYPE != _D0_NO_PORT)) ||\
      ((_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL == _D1_DDC_CHANNEL_SEL) && (_D1_INPUT_PORT_TYPE != _D1_NO_PORT)) ||\
      ((_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL == _D2_DDC_CHANNEL_SEL) && (_D2_INPUT_PORT_TYPE != _D2_NO_PORT)) ||\
      ((_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL == _D3_DDC_CHANNEL_SEL) && (_D3_INPUT_PORT_TYPE != _D3_NO_PORT)) ||\
      ((_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL == _D4_DDC_CHANNEL_SEL) && (_D4_INPUT_PORT_TYPE != _D4_NO_PORT)) ||\
      ((_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL == _D5_DDC_CHANNEL_SEL) && (_D5_INPUT_PORT_TYPE != _D5_NO_PORT)))
#warning "_CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL must select _NO_PORT!!!"
#endif

#if((_A0_CODE_DIGITAL_SIGNATURE_ISP_EN != _ENABLE) &&\
    (_D0_CODE_DIGITAL_SIGNATURE_ISP_EN != _ENABLE) &&\
    (_D1_CODE_DIGITAL_SIGNATURE_ISP_EN != _ENABLE) &&\
    (_D2_CODE_DIGITAL_SIGNATURE_ISP_EN != _ENABLE) &&\
    (_D3_CODE_DIGITAL_SIGNATURE_ISP_EN != _ENABLE) &&\
    (_D4_CODE_DIGITAL_SIGNATURE_ISP_EN != _ENABLE) &&\
    (_D5_CODE_DIGITAL_SIGNATURE_ISP_EN != _ENABLE))
#warning "_A0 or _Dx_CODE_DIGITAL_SIGNATURE_ISP_EN must select One _ENABLE at least!!!"
#endif

#endif
//--------------------------------------------------
// TYPE-C Port Controller Check
//--------------------------------------------------
// For D0 Port
#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR != 0x00))
#warning "D0 Type-C Port Controller is EMBEDDED. Port Controller SLAVE ADDR Should be 0x00!!!"
#endif

#if(((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D0_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR == 0x00))
#warning "D0 Type-C Port Controller is NOT EMBEDDED. Port Controller SLAVE ADDR Should be VALID!!!"
#endif

#if((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D0_DP_TYPE_C_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "D0 Type-C Port Controller is EMBEDDED. AUXPN_SWAP Should be SCALER!!!"
#endif

// For D1 Port
#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR != 0x00))
#warning "D1 Type-C Port Controller is EMBEDDED. Port Controller SLAVE ADDR Should be 0x00!!!"
#endif

#if(((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D1_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR == 0x00))
#warning "D1 Type-C Port Controller is NOT EMBEDDED. Port Controller SLAVE ADDR Should be VALID!!!"
#endif

#if((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D1_DP_TYPE_C_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "D1 Type-C Port Controller is EMBEDDED. AUXPN_SWAP Should be SCALER!!!"
#endif

// For D6 Port
#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D6_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR != 0x00))
#warning "D6 Type-C Port Controller is EMBEDDED. Port Controller SLAVE ADDR Should be 0x00!!!"
#endif

#if(((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) || (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER)) && (_D6_DP_TYPE_C_PORT_CTRL_SLAVE_ADDR == 0x00))
#warning "D6 Type-C Port Controller is NOT EMBEDDED. Port Controller SLAVE ADDR Should be VALID!!!"
#endif

#if((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D6_DP_TYPE_C_PIN_E_AUXPN_SWAP != _SWAP_BY_SCALER))
#warning "D6 Type-C Port Controller is EMBEDDED. AUXPN_SWAP Should be SCALER!!!"
#endif

//--------------------------------------------------
// Hub Process Check
//--------------------------------------------------
// For D0 Port
#if((_D0_DP_TYPE_C_RTK_PC_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "_SW_IIC_SUPPORT Should be On!!!"
#endif

#if((_D0_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && (_D0_DP_TYPE_C_RTK_PC_SMBUS_IIC != _SW_IIC_PIN_GPIO))
#if(_HW_IIC_SUPPORT == _OFF)
#warning "D0 HW IIC Turn On. _HW_IIC_SUPPORT Should be _ON!!!!"
#endif
#endif

#if((_D0_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && ((_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_RTS5400_SERIES) && (_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_RTS5411_SERIES)))
#warning "_D0_DP_TYPE_C_RTK_PC_SMBUS_IIC Just Use in 5400/5411 Series IC!!!"
#endif

// For D1 Port
#if((_D1_DP_TYPE_C_RTK_PC_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "_SW_IIC_SUPPORT Should be On!!!"
#endif

#if((_D1_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && (_D1_DP_TYPE_C_RTK_PC_SMBUS_IIC != _SW_IIC_PIN_GPIO))
#if(_HW_IIC_SUPPORT == _OFF)
#warning "D1 HW IIC Turn On. _HW_IIC_SUPPORT Should be _ON!!!!"
#endif
#endif

#if((_D1_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && ((_D1_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_RTS5400_SERIES) && (_D1_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_RTS5411_SERIES)))
#warning "_D1_DP_TYPE_C_RTK_PC_SMBUS_IIC Just Use in 5400/5411 Series IC!!!"
#endif

// For D6 Port
#if((_D6_DP_TYPE_C_RTK_PC_SMBUS_IIC == _SW_IIC_PIN_GPIO) && (_SW_IIC_SUPPORT == _OFF))
#warning "_SW_IIC_SUPPORT Should be On!!!"
#endif

#if((_D6_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && (_D6_DP_TYPE_C_RTK_PC_SMBUS_IIC != _SW_IIC_PIN_GPIO))
#if(_HW_IIC_SUPPORT == _OFF)
#warning "D6 HW IIC Turn On. _HW_IIC_SUPPORT Should be _ON!!!!"
#endif
#endif

#if((_D6_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && ((_D6_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_RTS5400_SERIES) && (_D6_DP_TYPE_C_USB_HUB_TYPE != _PORT_CONTROLLER_RTS5400_SERIES)))
#warning "_D6_DP_TYPE_C_RTK_PC_SMBUS_IIC Just Use in 5400/5411 Series IC!!!"
#endif
#endif // End of #ifndef __PCB_CONFIG_CHECK_H__
