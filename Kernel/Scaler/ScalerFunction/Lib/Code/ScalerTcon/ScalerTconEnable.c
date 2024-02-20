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
// ID Code      : ScalerTconEnable.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerTconLibInternalInclude.h"

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
void ScalerTconEnable(bit bEnable);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Enable TCON
// Input Value  : bEnable --> Enable TCON
// Output Value : None
//--------------------------------------------------
void ScalerTconEnable(bit bEnable)
{
    if(bEnable == _ON)
    {
        // Enable All TCON
        ScalerTconGlobalEnable(_ON);
#if(_HW_PWM_RST_BY_TCON_SELECT == _TCON4)
        // Enable TCON4
        ScalerTcon4Enable(_ON);
#elif(_HW_PWM_RST_BY_TCON_SELECT == _TCON7)
        // Enable TCON7
        ScalerTcon7Enable(_ON);
#elif(_HW_PWM_RST_BY_TCON_SELECT == _TCON8)
        // Enable TCON8
        ScalerTcon8Enable(_ON);
#endif
    }
    else
    {
        // Disable All TCON
        ScalerTconGlobalEnable(_OFF);
#if(_HW_PWM_RST_BY_TCON_SELECT == _TCON4)
        // Disable TCON4
        ScalerTcon4Enable(_OFF);
#elif(_HW_PWM_RST_BY_TCON_SELECT == _TCON7)
        // Disable TCON7
        ScalerTcon7Enable(_OFF);
#elif(_HW_PWM_RST_BY_TCON_SELECT == _TCON8)
        // Disable TCON8
        ScalerTcon8Enable(_OFF);
#endif
    }
}
