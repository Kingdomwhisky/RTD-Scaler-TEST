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
// ID Code      : SysTMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_TMDS__

#include "SysInclude.h"

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

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
void SysTMDSRxHandler(void);
#if(_HDMI_SUPPORT == _ON)
void SysTMDSRxSetPsWakeupHpdToggle(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTMDSRxHandler(void)
{
    ScalerSyncTMDSHPDToggleProc();
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scan & Set the relatived PS Wakeup HPD Toggle flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTMDSRxSetPsWakeupHpdToggle(void)
{
    if(GET_SOURCE_TYPE(g_ucSearchIndex) == _SOURCE_HDMI)
    {
        ScalerTMDSSetPsWakeupHpdToggle(GET_INPUT_PORT(g_ucSearchIndex));
    }
}
#endif


#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
