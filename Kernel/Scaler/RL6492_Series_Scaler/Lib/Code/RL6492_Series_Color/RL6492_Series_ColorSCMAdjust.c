
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
// ID Code      : RL6492_Series_ColorSCMAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

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
void ScalerColorSCMAdjust(BYTE ucAdjustOption1, BYTE ucAdjustOption2);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust SCM Function
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void ScalerColorSCMAdjust(BYTE ucAdjustOption1, BYTE ucAdjustOption2)
{
    ScalerSetByte(P7_CC_SCM_BLOCK_ENABLE, (((BYTE)((bit)(ucAdjustOption2 & _SCM0_BLOCK0_ENABLE)) << 7) | ((BYTE)((bit)(ucAdjustOption2 & _SCM0_BLOCK1_ENABLE)) << 6) |
                                           ((BYTE)((bit)(ucAdjustOption2 & _SCM1_BLOCK0_ENABLE)) << 5) | ((BYTE)((bit)(ucAdjustOption2 & _SCM1_BLOCK1_ENABLE)) << 4) |
                                           ((BYTE)((bit)(ucAdjustOption2 & _SCM2_BLOCK0_ENABLE)) << 3) | ((BYTE)((bit)(ucAdjustOption2 & _SCM2_BLOCK1_ENABLE)) << 2) |
                                           ((BYTE)((bit)(ucAdjustOption2 & _SCM3_BLOCK0_ENABLE)) << 1) | ((BYTE)((bit)(ucAdjustOption2 & _SCM3_BLOCK1_ENABLE)))));

    ScalerSetBit(P7_CD_SCM_BLOCK_SELECT, ~_BIT4, (BYTE)((bit)(ucAdjustOption1 & _SCMN_SHARE_REG)) << 4);
}
