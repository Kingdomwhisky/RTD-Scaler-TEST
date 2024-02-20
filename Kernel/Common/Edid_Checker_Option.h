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
// ID Code      : Edid_Checker_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// HDMI EDID options
//--------------------------------------------------
#define _EDID_CHECK_HDMI_HDR10                      (_HDMI_HDR10_SUPPORT == _ON)

#define _EDID_CHECK_HDMI_FREESYNC                   (_HDMI_FREESYNC_SUPPORT == _ON)
#define _EDID_CHECK_HDMI_FREESYNC_II                (_HDMI_FREESYNC_II_SUPPORT == _ON)
#define _EDID_CHECK_HDMI_FREESYNC_MCCS              (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)

#if(_EDID_CHECK_HDMI_FREESYNC_MCCS == _ON)
#define _EDID_HDMI_FREESYNC_MCCS_VALUE              _HDMI_FREESYNC_MCCS_VCP
#else
#define _EDID_HDMI_FREESYNC_MCCS_VALUE              0x00
#endif

#define _EDID_CHECK_HDMI_420                        (_HDMI_2_0_YCBCR420_SUPPORT == _ON)

//--------------------------------------------------
// DP EDID options
//--------------------------------------------------
#define _EDID_CHECK_DP_HDR10                        (_DP_HDR10_SUPPORT == _ON)
#define _EDID_CHECK_DP_FREESYNC                     (_DP_FREESYNC_SUPPORT == _ON)
#define _EDID_CHECK_DP_FREESYNC_II                  (_DP_FREESYNC_II_SUPPORT == _ON)
#define _EDID_CHECK_DP_TYPE_C                       (_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

