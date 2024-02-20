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
// ID Code      : Project_Config_Pre_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_CONFIG_PRE_CHECK_H__
#define __PROJECT_CONFIG_PRE_CHECK_H__

#ifndef _TRANSLATOR_SUPPORT

#ifndef _SHARPNESS_SUPPORT
#warning "_SHARPNESS_SUPPORT Should Be Defined!!!"
#endif

#ifndef _CONTRAST_SUPPORT
#warning "_CONTRAST_SUPPORT Should Be Defined!!!"
#endif

#ifndef _BRIGHTNESS_SUPPORT
#warning "_BRIGHTNESS_SUPPORT Should Be Defined!!!"
#endif

#else

#if(_TRANSLATOR_SUPPORT == _OFF)

#ifndef _SHARPNESS_SUPPORT
#warning "_SHARPNESS_SUPPORT Should Be Defined!!!"
#endif

#ifndef _CONTRAST_SUPPORT
#warning "_CONTRAST_SUPPORT Should Be Defined!!!"
#endif

#ifndef _BRIGHTNESS_SUPPORT
#warning "_BRIGHTNESS_SUPPORT Should Be Defined!!!"
#endif

#endif

#endif // End of #ifndef _TRANSLATOR_SUPPORT

//--------------------------------------------------
// Type-C Check
//--------------------------------------------------
#ifndef _TYPE_C_EMB_PORT_ROLE
#ifdef _TYPEC_PORT_ROLE
#warning "_TYPEC_PORT_ROLE Define Should Modify Name to _TYPE_C_EMB_PORT_ROLE!!!"
#endif
#ifdef _TYPE_C_PORT_ROLE
#warning "_TYPE_C_PORT_ROLE Define Should Modify Name to _TYPE_C_EMB_PORT_ROLE!!!"
#endif
#endif // End of #ifndef _TYPE_C_EMB_PORT_ROLE

#ifndef _TYPE_C_EMB_PD_VERSION
#ifdef _TYPEC_PD_VERSION
#warning "_TYPEC_PD_VERSION Define Should Modify Name to _TYPE_C_EMB_PD_VERSION!!!"
#endif
#ifdef _TYPE_C_PD_VERSION
#warning "_TYPE_C_PD_VERSION Define Should Modify Name to _TYPE_C_EMB_PD_VERSION!!!"
#endif
#endif // End of #ifndef _TYPE_C_EMB_PD_VERSION

#ifndef _TYPE_C_EMB_PD3_PPS_SUPPORT
#ifdef _TYPE_C_PD3_PPS_SUPPORT
#warning "_TYPE_C_PD3_PPS_SUPPORT Define Should Modify Name to _TYPE_C_EMB_PD3_PPS_SUPPORT!!!"
#endif
#endif // End of #ifndef _TYPE_C_EMB_PD3_PPS_SUPPORT

#ifndef _TYPE_C_EMB_PD3_FRSWAP_SUPPORT
#ifdef _TYPEC_FRSWAP_SUPPORT
#warning "_TYPEC_FRSWAP_SUPPORT Define Should Modify Name to _TYPE_C_EMB_PD3_FRSWAP_SUPPORT!!!"
#endif
#ifdef _TYPE_C_FRSWAP_SUPPORT
#warning "_TYPE_C_FRSWAP_SUPPORT Define Should Modify Name to _TYPE_C_EMB_PD3_FRSWAP_SUPPORT!!!"
#endif
#endif // End of #ifndef _TYPE_C_EMB_PD3_FRSWAP_SUPPORT

#ifndef _TYPE_C_EMB_DC_OFF_OPTION
#ifdef _TYPE_C_DC_OFF_OPTION
#warning "_TYPE_C_DC_OFF_OPTION Define Should Modify Name to _TYPE_C_EMB_DC_OFF_OPTION!!!"
#endif
#endif // End of #ifndef _TYPE_C_EMB_DC_OFF_OPTION

#ifndef _TYPE_C_EMB_CTS_FLOW
#ifdef _USB3_RETIMER_CTS_FLOW_SUPPORT
#warning "_USB3_RETIMER_CTS_FLOW_SUPPORT Define Should Modify Name to _TYPE_C_EMB_CTS_FLOW!!!"
#endif
#ifdef _TYPE_C_CTS_FLOW
#warning "_TYPE_C_CTS_FLOW Define Should Modify Name to _TYPE_C_EMB_CTS_FLOW!!!"
#endif
#endif // End of #ifndef _TYPE_C_EMB_CTS_FLOW

#ifndef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F
#ifdef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F
#warning "_FLASH_TYPE_MX25L3206E_OR_MX25L3233F Define Should Modify Name to _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F!!!"
#endif
#endif // End of #ifndef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F_OR_KH25L3236F

#ifdef _FLASH_ACCESS_FUNCTION_SUPPORT
#warning "_FLASH_ACCESS_FUNCTION_SUPPORT Should Be Replace by _FLASH_WRITE_FUNCTION_SUPPORT & _FLASH_READ_FUNCTION_SUPPORT!!!"
#endif // End of #ifdef _FLASH_ACCESS_FUNCTION_SUPPORT

#endif // End of #ifndef __PROJECT_CONFIG_PRE_CHECK_H__
