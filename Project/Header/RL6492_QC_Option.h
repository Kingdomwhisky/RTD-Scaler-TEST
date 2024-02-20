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
// ID Code      : RL6463_QC_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//************************************  For RL6463  *********************************************
// 1. RL6369_Project.h:
//    (1). _PCB_TYPE = _RL6463_QA_1A2MHL1DP
//    (2). _PANEL_TYPE = _AU_LVDS_22_WSXGA_QC
//    (3). _OSD_TYPE = _NONE_OSD
//      #define _OSD_INCLUDE                            "NoneInclude.h"
//      #define _USER_FUNCTION_INCLUDE                  "NoneUserInclude.h"
//      #define _USER_TIMER_INCLUDE                     "NoneTimerInclude.h"
//      #define _FACTORY_INCLUDE                        "NoneFactoryInclude.h"
// 2. PCB_Option.h:
//    -> _SW_IIC_SUPPORT = _OFF
// 3. Debug.h:
//    -> _DEBUG_MESSAGE_QC = _ON
// 4. RTD2014Function, RTD2014Osd, RTDFactory:
//    -> Option for Group -> Include in Target Build -> Disable
// 5. NoneFunction, NoneOsd, NoneFactory:
//    -> Option for Group -> Include in Target Build -> Enable
// 6. RL6463_Series_QC_BIST.c ~ RL6369_Series_QC_OSD.c:
//    -> Option for File -> Include in Target Build -> Enable
// 7. RL6463_Project_Link.lin:
//    -> Option for Target -> User -> Run User Programs After Build -> Run #1 -> Disable
// 8. RL6369_Project_Link.lin :
//    -> Specify QC Code Bank in Keil C BL51 Misc By Modified Following:
/*
BankArea(0x0000,0xFFFF)
PRINT(".\Output\RL6492_Project.m51") RAMSIZE(256)
; add for IIC access common bank table: COMMON(?PR?_USERCOMMONEEPROMWRITE?USERCOMMONNVRAMSYSTEM, ?PR?_USERCOMMONEEPROMIICWRITE?USERCOMMONNVRAMSYSTEM, ?PR?_SCALERMCUHWIICWRITE?SCALERMCU)
COMMON(?PR?SYSTIMERINTPROC0?SYSTIMER, ?PR?SYSTIMERINTPROC1?SYSTIMER, ?PR?SYSTIMERINTPROC2?SYSTIMER,?PR?SYSTIMERWDINTPROC?SYSTIMER)
BANK0(?CO?SYSSOURCE, ?CO?RL6492_SERIES_SCALING)
BANK1(?CO?SCALER*TX)
BANK2(?CO?SCALERPLL, ?CO?RL6492_SERIES_COLOR*, ?CO?OSDDRAWWINDOW, ?CO?SCALERCOLOR)

; Flash mode settings
;@BANK0(RL6492_Series_FlashMode)
;@TABLE(?CO?RL6492_Series_FlashMode, 0x7000)
OVERLAY(* ! ?CO?RL6492_Series_FlashMode)

BANK5(?CO?USERCOMMONMODESEARCH, ?CO?USERCOMMONADJUST, ?CO?USERCOMMONDDCCIFUNCTION, ?CO?USERCOMMONINTERFACE, ?CO?USERCOMMONNVRAMSYSTEM, ?CO?SCALERVGATOP)

BANK6(?CO?NONEUSERADJUST, ?CO?NONEOSD)
BANK11(?CO?RL6463_SERIES_QC_COLOR)
BANK15(?CO?RL6463_SERIES_QC_OD_FRC, ?CO?RL6463_SERIES_QC_OSD)

XDATA( 0XD700-0XFCFF )
NOIC

;;; for multi-panel application
;;;@if(_PANEL_EXIST_MULTIPANEL == _ON)
;;    ;@COMMON(SCALERDDOMAIN)
;;;@endif

; for flash partition application
;;;@if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
;;    ;@if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
;;        ;@BANK0(SYSMAIN)
;;    ;@elif(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
;;        ;@if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
;;            ;@BANK0(SYSMAIN, RTD2014USERBOOT)
;;        ;@else
;;            ;@BANK0()
;;            ;@BANK1()
;;            ;@BANK2()
;;            ;@BANK3()
;;            ;@BANK4()
;;            ;@BANK5()
;;            ;@BANK6()
;;            ;@BANK7()
;;            ;@BANK8()
;;            ;@BANK9()
;;            ;@BANK10()
;;            ;@BANK11()
;;            ;@BANK12()
;;            ;@BANK13()
;;            ;@BANK14()
;;            ;@BANK15()
;;            ;@BANK16(SYSMAIN, RTD2014USERBOOT)
;;        ;@endif
;;        ;@TABLE(?CO?RTD2014USERBOOT, 0xF8FE)
;;    ;@endif
;;
;;    ;@FUNC(?PR?SYSMAINSTARTUSERCODE?SYSMAIN, 0x4000)
;;;@endif
*/
//***********************************************************************************************

//--------------------------------------------------
// QC type Options
//--------------------------------------------------
