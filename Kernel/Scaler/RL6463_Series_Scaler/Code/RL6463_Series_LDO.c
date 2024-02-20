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
// ID Code      : RL6463_Series_LDO.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6463_SERIES_LDO__

#include "ScalerFunctionInclude.h"

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
void ScalerLDOPowerControl(EnumPowerStatus enumPorStatus);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : LDO Power Control.
// Input Value  : ucPorStatus    --> _POWER_STATUS_NORMAL/_POWER_STATUS_SAVING/_POWER_STATUS_OFF Select.
// Output Value : None
//--------------------------------------------------
void ScalerLDOPowerControl(EnumPowerStatus enumPorStatus)
{
    if((bit)PCB_EMBEDDED_LDO_DETECT() == _EMBEDDED_LDO_ON)
    {
        switch(enumPorStatus)
        {
            case _POWER_STATUS_NORMAL:

                // Select LDO-D voltage output is 1.0V
                ScalerSetBit(P62_03_EBD_REGLATOR_D_CTRL1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

                break;

            case _POWER_STATUS_OFF:
            case _POWER_STATUS_SAVING:

                // Select LDO-D voltage output is 0.96V
                ScalerSetBit(P62_03_EBD_REGLATOR_D_CTRL1, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

                break;

            default:

                break;
        }
    }
    else
    {
        // Avoiding Complier Error
        enumPorStatus = enumPorStatus;

        // Disable LDO-D
        ScalerSetBit(P62_03_EBD_REGLATOR_D_CTRL1, ~_BIT7, 0x00);
    }
}


