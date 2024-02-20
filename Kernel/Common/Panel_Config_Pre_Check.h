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
// ID Code      : Panel_Config_Pre_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_CONFIG_PRE_CHECK_H__
#define __PANEL_CONFIG_PRE_CHECK_H__


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// Display HDR Option
//--------------------------------------------------
#if(_HDR10_SUPPORT == _ON)

#ifndef _PANEL_MAX_LUMINANCE
#warning "Please Define _PANEL_MAX_LUMINANCE at Panel.h for HDR10"
#endif

#ifndef _PANEL_MAX_FRAME_AVERAGE_LUMINANCE
#warning "Please Define _PANEL_MAX_FRAME_AVERAGE_LUMINANCE at Panel.h for HDR10"
#endif

//--------------------------------------------------
// HDR User Define Panel Max Lv
//--------------------------------------------------
#if(_HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT == _ON)
#ifndef _PANEL_MAX_USER_DEFINE_LUMINANCE
#warning "_PANEL_MAX_USER_DEFINE_LUMINANCE should be defined at Panel.h when _HDR10_USER_DEFINE_PANEL_MAX_LV_SUPPORT is _ON"
#endif
#endif

#endif

#endif // End of #ifndef __PANEL_CONFIG_PRE_CHECK_H__

