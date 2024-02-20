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
// ID Code      : SysAutotest.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_AUTOTEST__

#include "SysInclude.h"

#if(_AUTO_TEST_SUPPORT == _ON)
#include "ATSysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysAutotestHandler(void);
void SysAutotestOSDSwitchCtrl(void);
void SysAutotestIntProc_EXINT1(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Auto Test Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAutotestHandler(void)
{
    ATUserCommonDdcciHandler();

    ATOSDKeyMessageScan();
}

//--------------------------------------------------
// Description  : Auto Test OSD Switch Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAutotestOSDSwitchCtrl(void)
{
    ATOSDMenuKeyMessageClrFlg();
}

//--------------------------------------------------
// Description  : Auto Test Int Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysAutotestIntProc_EXINT1(void) using 2
{
    ATUserCommonInterfaceDdcciGetData_EXINT1();
}
#endif
