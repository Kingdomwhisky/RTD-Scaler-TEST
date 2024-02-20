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
// ID Code      : RL6369_Series_ColorPCMOutputGammaAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6369_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GAMMA_WRITE_TO_SRAM                    0
#define _GAMMA_WRITE_TO_LATCH                   1

#define _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE       24
#define _PCM_OUTPUTGAMMA_SRAM_TABLE_SIZE        387

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
void ScalerColorPCMOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Adjust output gamma for PCM
// Input Value  : Gamma table type and gamma tables banks and Latch&Sram Length
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMOutputGammaAdjust(BYTE *pucGammaTableArray, BYTE ucBankNum)
{
    WORD usTotalLength = _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE + _PCM_OUTPUTGAMMA_SRAM_TABLE_SIZE;

    // Load gamma table of R Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x00, _GAMMA_WRITE_TO_LATCH);
    ScalerBurstWrite(pucGammaTableArray, _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    ScalerBurstWrite(pucGammaTableArray + _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE, _PCM_OUTPUTGAMMA_SRAM_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Load gamma table of G Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x00, _GAMMA_WRITE_TO_LATCH);
    ScalerBurstWrite(pucGammaTableArray + usTotalLength, _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    ScalerBurstWrite(pucGammaTableArray + usTotalLength + _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE, _PCM_OUTPUTGAMMA_SRAM_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Load gamma table of B Channel
    ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x00, _GAMMA_WRITE_TO_LATCH);
    ScalerBurstWrite(pucGammaTableArray + usTotalLength * 2, _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x00, _GAMMA_WRITE_TO_SRAM);
    ScalerBurstWrite(pucGammaTableArray + usTotalLength * 2 + _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE, _PCM_OUTPUTGAMMA_SRAM_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable Port Access
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);
}

