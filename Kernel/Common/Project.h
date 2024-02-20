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
// ID Code      : Project.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_H__
#define __PROJECT_H__

//--------------------------------------------------
// List Include
//--------------------------------------------------
#include "Scaler_List.h"
#include "Project_List.h"
#include "Panel_List.h"
#include "Pcb_List.h"
#include "User_Project_List.h"
#include "User_Panel_List.h"
#include "User_Pcb_List.h"

//--------------------------------------------------
// RLxxxx Generation Option
//--------------------------------------------------
#include "RL6369_Gen_Option.h"
#include "RL6410_Gen_Option.h"
#include "RL6432_Gen_Option.h"
#include "RL6449_Gen_Option.h"
#include "RL6463_Gen_Option.h"
#include "RL6492_Gen_Option.h"

//--------------------------------------------------
// Project and Project Option Include
//--------------------------------------------------
#include "User_Project_Include.h"
#include "Project_Config_Pre_Check.h"

#include "Project_User_Beacon_List.h"
#include "Project_User_Beacon_Default.h"
#include "Project_User_Beacon_Define.h"

#include _RLXXXX_PROJECT_DEFAULT

#include "RL6193_Project_Default.h"
#include "RL6369_Project_Default.h"
#include "RL6410_Project_Default.h"
#include "RL6432_Project_Default.h"
#include "RL6449_Project_Default.h"
#include "RL6463_Project_Default.h"
#include "RLE0779_Project_Default.h"
#include "RL6492_Project_Default.h"
#include "User_Project_Option.h"
#include "Project_Asm_Option.h"
#include "Project_Option.h"

//--------------------------------------------------
// Panel and Panel Option Include
//--------------------------------------------------
#include "User_Panel_Include.h"
#include "Panel_Config_Pre_Check.h"
#include "Panel_Default.h"
#include "User_Panel_Option.h"
#include "Panel_Option.h"

//--------------------------------------------------
// Pcb and Pcb Option Include
//--------------------------------------------------
#include "User_Pcb_Include.h"
#include "Pcb_Config_Pre_Check.h"
#include _RLXXXX_PCB_DEFAULT
#include "RL6193_Pcb_Default.h"
#include "RL6369_Pcb_Default.h"
#include "RL6410_Pcb_Default.h"
#include "RL6432_Pcb_Default.h"
#include "RL6449_Pcb_Default.h"
#include "RL6463_Pcb_Default.h"
#include "RLE0779_Pcb_Default.h"
#include "RL6492_Pcb_Default.h"
#include "User_Pcb_Option.h"
#include "Pcb_Option.h"

//--------------------------------------------------
// Option Include
//--------------------------------------------------
#include "User_Scaler_Option.h"
#include "Scaler_Option.h"

//--------------------------------------------------
// Config Check Include
//--------------------------------------------------
#include "Project_Config_Check.h"
#include "Panel_Config_Check.h"
#include "Pcb_Config_Check.h"

//--------------------------------------------------
// Debug Include
//--------------------------------------------------
#include "Debug.h"

//--------------------------------------------------
// Device Include
//--------------------------------------------------
#include "ExternalDeviceInterface.h"

//--------------------------------------------------
// Test Option Include
//--------------------------------------------------
#include "Scaler_Test_Function.h"

//--------------------------------------------------
// Edid Checker Include
//--------------------------------------------------
#include "Edid_Checker_Option.h"

#endif // End of #ifndef __PROJECT_H__
