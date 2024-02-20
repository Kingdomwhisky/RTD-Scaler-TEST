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
// ID Code      : RL6410_Series_ColorUltraVividAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _ULTRAVIVID_TABLE_SIZE                  238
#define _ULTRAVIVID_TABLE_SIZE_CDS              29


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
void ScalerColorUltraVividAdjust(BYTE code *pucUltraVividSetting, BYTE ucBankNum);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : UltraVivid Adjust
// Input Value  : UltraVivid Table and ucBankNum
// Output Value : None
//--------------------------------------------------
void ScalerColorUltraVividAdjust(BYTE code *pucUltraVividSetting, BYTE ucBankNum)
{
    if(GET_V_SCALE_UP() == _TRUE)
    {
        ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_03_VER_SCALE_FACTOR_H, 2, pData, _AUTOINC);
        pData[0] = ((pData[0] << 4) | (pData[1] >> 4));

        if(pData[0] < 85)  // IVHeight/DVHeight <= 1/4
        {
            ScalerBurstWrite(pucUltraVividSetting, _ULTRAVIVID_TABLE_SIZE, ucBankNum, P11_B9_SCALER_LSR_HLW, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
        }
        else if(pData[0] < 170)  // IVHeight/DVHeight < 2/3
        {
            ScalerBurstWrite(pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE, _ULTRAVIVID_TABLE_SIZE, ucBankNum, P11_B9_SCALER_LSR_HLW, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
        }
        else  // IVHeight/DVHeight <= 1
        {
            ScalerBurstWrite(pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 2, _ULTRAVIVID_TABLE_SIZE, ucBankNum, P11_B9_SCALER_LSR_HLW, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
        }
    }
    else if(GET_V_SCALE_DOWN() == _TRUE)
    {
        ScalerBurstWrite(pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 3, _ULTRAVIVID_TABLE_SIZE, ucBankNum, P11_B9_SCALER_LSR_HLW, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
    }
    else // by pass
    {
        ScalerBurstWrite(pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 4, _ULTRAVIVID_TABLE_SIZE, ucBankNum, P11_B9_SCALER_LSR_HLW, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
    }

    ScalerBurstWrite(pucUltraVividSetting + _ULTRAVIVID_TABLE_SIZE * 5, _ULTRAVIVID_TABLE_SIZE_CDS, ucBankNum, P13_A0_SR_CDS_CTRL_0, _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

    // Disable IDLTI
    ScalerSetBit(P11_A1_I_DLTI_CTRL_M1, ~_BIT0, 0x00);

    // Bypass DSHP
    ScalerSetBit(P12_A0_SR_SHP_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT7);
    ScalerSetBit(P12_A1_SR_SHP_CTRL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Wait for Event
    ScalerGlobalIDDomainDBApply(_DB_APPLY_NONE);
}
