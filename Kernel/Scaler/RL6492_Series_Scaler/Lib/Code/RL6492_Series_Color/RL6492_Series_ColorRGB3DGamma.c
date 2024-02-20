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
// ID Code      : RL6492_Series_ColorRGB3DGamma.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _3DGAMMA_TABLE_SIZE                     3645


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
void ScalerColorRGB3DGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust 3D gamma
// Input Value  : 3D Gamma Table and 3D Gamma Table Banks
// Output Value : None
//--------------------------------------------------
void ScalerColorRGB3DGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum)
{
    if(ScalerGetBit(P9_B0_RGB_3D_GAMMA_CTRL, _BIT7) == _BIT7) // 3D Gamma On
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);

        // Enable Gamma access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, _BIT6);

        // Initial Table Address
        ScalerSetByte(P9_B1_RGB_3D_GAMMA_ADDRESS_H, 0x00);
        ScalerSetByte(P9_B2_RGB_3D_GAMMA_ADDRESS_L, 0x00);

        // Load gamma table of 3D Gamma
        ScalerBurstWrite(pucGammaTableArray, _3DGAMMA_TABLE_SIZE, ucBankNum, P9_B3_RGB_3D_GAMMA_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, 0x00);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
    }
    else
    {
        // Enable Gamma access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, _BIT6);

        // Initial Table Address
        ScalerSetByte(P9_B1_RGB_3D_GAMMA_ADDRESS_H, 0x00);
        ScalerSetByte(P9_B2_RGB_3D_GAMMA_ADDRESS_L, 0x00);

        // Load gamma table of 3D Gamma
        ScalerBurstWrite(pucGammaTableArray, _3DGAMMA_TABLE_SIZE, ucBankNum, P9_B3_RGB_3D_GAMMA_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Disable Port Access
        ScalerSetBit(P9_B0_RGB_3D_GAMMA_CTRL, ~_BIT6, 0x00);
    }
}
