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
// ID Code      : User_Project_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// OSD Default Option
//--------------------------------------------------
#ifndef _OSD_INCLUDE
#define _OSD_INCLUDE                                            "NoneInclude.h"
#endif

#ifndef _USER_FUNCTION_INCLUDE
#define _USER_FUNCTION_INCLUDE                                  "NoneUserInclude.h"
#endif

#ifndef _USER_TIMER_INCLUDE
#define _USER_TIMER_INCLUDE                                     "NoneTimerInclude.h"
#endif

#ifndef _FACTORY_INCLUDE
#define _FACTORY_INCLUDE                                        "NoneFactoryInclude.h"
#endif

#ifndef _USER_HWIIC_INCLUDE
#define _USER_HWIIC_INCLUDE                                     "NoneHWIICInclude.h"
#endif

//--------------------------------------------------
// Definitions of DP extra infomation for debug , DP Support must set ON
//--------------------------------------------------
#define _DP_DEBUG_MSG                                           _OFF

//--------------------------------------------------
// Definitions to Switch EDID/Capability String to Dell Spec (DDM Tool)
//--------------------------------------------------
#define _USER_SWITCH_TO_DELL_EDID_CAP_STRING                    _OFF

#if(_USER_SWITCH_TO_DELL_EDID_CAP_STRING == _ON)
#undef _CAPABILITIES_STRING_VGA
#undef _CAPABILITIES_STRING_DVI
#undef _CAPABILITIES_STRING_HDMI
#undef _CAPABILITIES_STRING_DP

#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 0E 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 1E 1F 20 30 3E 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_DVI                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

