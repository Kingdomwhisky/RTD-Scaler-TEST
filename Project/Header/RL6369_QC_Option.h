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
// ID Code      : RL6369_QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//************************************  For RL6369  *********************************************
// 1. RL6369_Project.h:
//    (1). _PCB_TYPE = _RL6369_QA_1A2MHL1DP
//    (2). _PANEL_TYPE = _AU_LVDS_22_WSXGA_QC
//    (3). _OSD_TYPE = _NONE_OSD
// 2. PCB_Option.h:
//    -> _SW_IIC_SUPPORT = _OFF
// 3. Debug.h:
//    -> _DEBUG_MESSAGE_QC = _ON
// 4. RTD2014Function, RTD2014Osd, RTDFactory:
//    -> Option for Group -> Include in Target Build -> Disable
// 5. NoneFunction, NoneOsd, NoneFactory:
//    -> Option for Group -> Include in Target Build -> Enable
// 6. RL6369_Series_QC_BIST.c ~ RL6369_Series_QC_OSD.c:
//    -> Option for File -> Include in Target Build -> Enable
// 7. RL6369_Project_Link.lin:
//    -> Option for Target -> User -> Run User Programs After Build -> Run #1 -> Disable
// 8. Bank3 Spec Overflow:
//    -> Move RL6369_Series_MHL3 to Bank7
// 9. RL6369_Project_Link.lin :
//    -> Specify QC Code Bank in Keil C BL51 Misc By Modified Following:
/*
COMMON(?PR?SYSTIMERINTPROC0?SYSTIMER, ?PR?SYSTIMERINTPROC1?SYSTIMER, ?PR?SYSTIMERINTPROC2?SYSTIMER,?PR?SYSTIMERWDINTPROC?SYSTIMER)
BANK0(?CO?SYSSOURCE, ?CO?SYSPOWER)
BANK2(?CO?RL6369_SERIES_COLOR*, ?CO?SCALERPLL)
BANK5(?CO?USERCOMMONMODESEARCH, ?CO?USERCOMMONDDCCIFUNCTION, ?CO?USERCOMMONINTERFACE, ?CO?USERCOMMONNVRAMSYSTEM)
BANK6(?CO?NONEUSERADJUST, ?CO?NONEOSD)
BANK11(?CO?RL6369_SERIES_QC_COLOR)
BANK15(?CO?RL6369_SERIES_QC_OD_FRC, ?CO?RL6369_SERIES_QC_OSD)
*/
//***********************************************************************************************

