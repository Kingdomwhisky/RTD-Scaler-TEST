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
// ID Code      : RL6432_QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//************************************  For RL6432  *********************************************
// 1. RL6432_Project.h:
//    (1). _PCB_TYPE = _RL6432_QA_A_1A2MHL1DP1mDP_DPTX_LVDS_eDP
//    (2). _PANEL_TYPE = _LG_LED_DP_27_QHD_QC
//    (3). _OSD_TYPE = _NONE_OSD
//      #define _OSD_TYPE                               _NONE_OSD
//
//      #define _OSD_INCLUDE                            "NoneInclude.h"
//      #define _USER_FUNCTION_INCLUDE                  "NoneUserInclude.h"
//      #define _USER_TIMER_INCLUDE                     "NoneTimerInclude.h"
//      #define _FACTORY_INCLUDE                        "NoneFactoryInclude.h"
//      #define _USER_HWIIC_INCLUDE                     "NoneHWIICInclude.h"
//
// 2. Debug.h:
//    -> _DEBUG_MESSAGE_QC = _ON
// 3. RTD2014Function, RTD2014Osd, RTDFactory:
//    -> Option for Group -> Include in Target Build -> Disable
// 4. NoneFunction, NoneOsd, NoneFactory:
//    -> Option for Group -> Include in Target Build -> Enable
//    -> Option for Files -> NoneFactoryFunction_RL6193 -> Include in Target Build -> Disable
//    -> Option for Files -> NoneFactoryFunction_RL6369 -> Include in Target Build -> Disable
//    -> Option for Files -> NoneFactoryFunction_RL6410 -> Include in Target Build -> Disable
// 5. RL6432_Series_QC_BIST.c ~ RL6432_Series_QC_OSD.c:
//    -> Option for File -> Include in Target Build -> Enable
// 6. QC_Option.h :
//    -> _FACTORY_RTD_QC_SUPPORT = _ON
// 7. RL6432_Project_Link.lin :
//    -> Specify QC Code Bank in Keil C BL51 Misc By Modified Following:
/*
COMMON(?PR?SYSTIMERINTPROC0?SYSTIMER, ?PR?SYSTIMERINTPROC1?SYSTIMER, ?PR?SYSTIMERINTPROC2?SYSTIMER,?PR?SYSTIMERWDINTPROC?SYSTIMER)
BANK0(?CO?SYSSOURCE, ?CO?RL6432_SERIES_SCALING)
BANK1(?CO?SCALER*TX)
BANK2(?CO?SCALERPLL, ?CO?RL6432_SERIES_COLOR*, ?CO?OSDDRAWWINDOW)
BANK5(?CO?USERCOMMONMODESEARCH, ?CO?USERCOMMONDDCCIFUNCTION, ?CO?USERCOMMONINTERFACE, ?CO?USERCOMMONNVRAMSYSTEM, ?CO?SCALERVGATOP)
BANK6(?CO?NONE*) 
BANK10(?CO?RL6432_SERIES_QC_COLOR_DDOMAIN)
BANK11(?CO?RL6432_SERIES_QC_MAIN, ?CO?RL6432_SERIES_QC_COLOR_IMDOMAIN, ?CO?RL6432_SERIES_QC_DSPC)
BANK13(?CO?RL6432_SERIES_QC_COLOR_DDOMAIN_II)
BANK14(?CO?RL6432_SERIES_QC_COLOR_DDOMAIN_III, ?CO?RL6432_SERIES_QC_OD_FRC)
BANK15(?CO?RL6432_SERIES_QC_OSD, ?CO?RL6432_SERIES_QC_BIST)
*/
//***********************************************************************************************

//--------------------------------------------------
// QC type Options
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#undef _MEMORY_SIZE_CONFIG
#define _MEMORY_SIZE_CONFIG                                     _4M_16BIT_DDR1_1PC
#endif

