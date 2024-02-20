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
// ID Code      : OsdCircuitActivated.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInternalInclude.h"

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
void ScalerOsdCircuitActivated(bit bEnable);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Activate OSD circuit enable disable
// Input Value  : bEnable      -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdCircuitActivated(bit bEnable)
{
    bit bBackup = _DISABLE;

    if(ScalerGetBit(P3A_02_FRAME_CTRL_02, _BIT0) == _BIT0)
    {
        if(bEnable == _ENABLE)
        {
            return;
        }
        bBackup = _ENABLE;
    }

    if(bEnable == _DISABLE)
    {
        // must be reset before disable osd circuit
        // [7:5] --> Set write byte : ALL
        // [3:2] --> Set address indicator : Window control register
        ScalerSetBit(P0_94_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), 0x00);
    }

    ScalerSetBit(P3A_02_FRAME_CTRL_02, ~(_BIT0), bEnable);

    if((bBackup == _DISABLE) && (bEnable == _ENABLE))
    {
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}
