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
// ID Code      : OsdRollUp.c
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
void ScalerOsdRollUp(bit bEnable, BYTE ucRowStart, BYTE ucRowBack);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set OSD RollUp function
// Input Value  :  bEnable    -> _ENABLE or _DISABLE
//                 ucRowStart -> Set RollUp start (end) row
//                 ucRowBack  -> Set RollUp reposition row
// Output Value :
//--------------------------------------------------
void ScalerOsdRollUp(bit bEnable, BYTE ucRowStart, BYTE ucRowBack)
{
    BYTE pucTemp[2];
    WORD usCharCommandAddress = 0;
    memset(pucTemp, 0, sizeof(pucTemp));

    // Set OSD Special Function Enable/Disable
    ScalerSetBit(P3A_18_FRAME_CTRL_18, ~(_BIT7 | _BIT6), ((BYTE)bEnable << 7));

    // Get Font Select Base Address
    pucTemp[0] = ScalerGetByte(P3A_0C_FRAME_CTRL_0C);
    pucTemp[1] = ScalerGetByte(P3A_0D_FRAME_CTRL_0D);
    usCharCommandAddress = (WORD)((pucTemp[1] & 0xF0) << 4) | pucTemp[0];
    usCharCommandAddress = usCharCommandAddress + (ucRowStart * GET_OSD_MAPA_COL_MAX());

    // Set Row Command Base 0
    ScalerSetByte(P3A_19_FRAME_CTRL_19, ucRowStart);
    // Set Row Command Base 1
    ScalerSetByte(P3A_1A_FRAME_CTRL_1A, ucRowBack);

    // Set Font Select Base 0
    ScalerSetBit(P3A_1B_FRAME_CTRL_1B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((usCharCommandAddress & 0xF00) >> 4));
    ScalerSetByte(P3A_1C_FRAME_CTRL_1C, (usCharCommandAddress & 0x0FF));
}
