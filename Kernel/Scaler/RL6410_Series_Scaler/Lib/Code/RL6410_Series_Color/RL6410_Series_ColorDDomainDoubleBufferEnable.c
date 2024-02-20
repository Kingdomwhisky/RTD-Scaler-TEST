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
// ID Code      : RL6410_Series_ColorDDomainDoubleBufferEnable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_ColorLibInternalInclude.h"

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
void ScalerColorDDomainDBEnable(bit bEn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Enable/Disable double buffer
// Input Value  : bEn --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerColorDDomainDBEnable(bit bEn)
{
    if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
    {
        if(bEn == _ENABLE)
        {
            // D Domain Double Buffer Enable
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), _BIT7);
        }
        else
        {
            // D Domain Double Buffer Disable
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT7 | _BIT6), 0x00);
        }
    }
}
