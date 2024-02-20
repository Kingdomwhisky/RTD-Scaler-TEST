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
// ID Code      : RL6449_Series_OsdScaleUpOnOff.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6449_Series_OSDLibInternalInclude.h"

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
void ScalerOsdScaleUpOnOff(bit bOnOff);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Font Scale Up (only valid when even-odd mode is applied)
// Input Value  : bOnOff
// Output Value :
//--------------------------------------------------
void ScalerOsdScaleUpOnOff(bit bOnOff)
{
    BYTE ucOSDOffsetCorrect = _DISABLE;

    if(((bit)ScalerGetBit(P3A_C0_OSD_SU_CRTL, _BIT7) != bOnOff) && (ScalerOsdPositionCorrectSupport() == _ON))
    {
        ucOSDOffsetCorrect = _ENABLE;
    }

    ScalerSetBit(P3A_C0_OSD_SU_CRTL, ~(_BIT7), ((BYTE)bOnOff << 7));

    if(ucOSDOffsetCorrect == _ENABLE)
    {
        ScalerOsdPositionOffsetCorrection();
    }

    if(ScalerGlobalGetIDCode() == _RL6449_VER_A_ID_CODE)
    {
        // Read value effective not immediately
        ScalerTimerWaitForEvent(_EVENT_DVS);
    }
}

