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
// ID Code      : RL6410_Series_ColorDCRLocalDimmingStoreResult.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
StructDCRStoreInfo g_stDCRStoreInfo;

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerColorDCRLocalDimmingStoreResult(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Read DCR Local Dimming Information Result
// Input Value  : Pointor of Local Dimming Information Result
// Output Value : none
//--------------------------------------------------
void ScalerColorDCRLocalDimmingStoreResult(void)
{
    if((ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT0) == 0x00) ||
       (GET_DCR_READY_STATUS() == _FALSE))
    {
        memset(&g_stDCRStoreInfo, 0, sizeof(StructDCRStoreInfo));

        return;
    }

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_02_DCR_ABOVE_TH1_NUM_2 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);
    g_stDCRStoreInfo.ulDCR_LD_ABOVE_TH1_NUM = PDATA_DWORD(0) >> 8;

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_09_DCR_ABOVE_TH2_NUM_2 << 2) | _BIT1 | _BIT0);
    ScalerRead(P7_D9_DCR_DATA_PORT, 3, pData, _NON_AUTOINC);
    g_stDCRStoreInfo.ulDCR_LD_ABOVE_TH2_NUM = PDATA_DWORD(0) >> 8;

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_28_DCR_Y_MAX_1 << 2) | _BIT1 | _BIT0);
    g_stDCRStoreInfo.pucWinMaxRGB[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_14_DCR_HIGH_LV_VAL_R_1 << 2) | _BIT1 | _BIT0);
    g_stDCRStoreInfo.pucWinMaxRGB[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1A_DCR_HIGH_LV_VAL_G_1 << 2) | _BIT1 | _BIT0);
    g_stDCRStoreInfo.pucWinMaxRGB[2] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_20_DCR_HIGH_LV_VAL_B_1 << 2) | _BIT1 | _BIT0);
    g_stDCRStoreInfo.pucWinMaxRGB[3] = ScalerGetByte(P7_D9_DCR_DATA_PORT);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_10_DCR_HIGH_LV_NUM_R_1 << 2) | _BIT1 | _BIT0);
    pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_11_DCR_HIGH_LV_NUM_R_0 << 2) | _BIT1 | _BIT0);
    pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    g_stDCRStoreInfo.pucWinMaxRGB[4] = (BYTE)((PDATA_WORD(0) & 0x3FF) >> 2);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_22_DCR_HIGH_LV_NUM_R_2 << 2) | _BIT1 | _BIT0);
    pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_10_DCR_HIGH_LV_NUM_R_1 << 2) | _BIT1 | _BIT0);
    pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    g_stDCRStoreInfo.pucWinMaxRGB[5] = (BYTE)(PDATA_WORD(0) >> 4);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_12_DCR_LOW_LV_NUM_R_1 << 2) | _BIT1 | _BIT0);
    pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_13_DCR_LOW_LV_NUM_R_0 << 2) | _BIT1 | _BIT0);
    pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    g_stDCRStoreInfo.pucWinMaxRGB[6] = (BYTE)((PDATA_WORD(0) & 0x3FF) >> 2);

    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_23_DCR_LOW_LV_NUM_R_2 << 2) | _BIT1 | _BIT0);
    pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_12_DCR_LOW_LV_NUM_R_1 << 2) | _BIT1 | _BIT0);
    pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
    g_stDCRStoreInfo.pucWinMaxRGB[7] = (BYTE)(PDATA_WORD(0) >> 4);

    if(ScalerGetDataPortBit(P0_64_CTS_BRI_PORT_ADD, _P0_65_PT_27_CTS_BRI_SET, _BIT1) == _BIT1)
    {
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_16_DCR_HIGH_LV_NUM_G_1 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_17_DCR_HIGH_LV_NUM_G_0 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[8] = (BYTE)((PDATA_WORD(0) & 0x3FF) >> 2);

        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_24_DCR_HIGH_LV_NUM_G_2 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_16_DCR_HIGH_LV_NUM_G_1 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[9] = (BYTE)(PDATA_WORD(0) >> 4);

        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_18_DCR_LOW_LV_NUM_G_1 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_19_DCR_LOW_LV_NUM_G_0 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[10] = (BYTE)((PDATA_WORD(0) & 0x3FF) >> 2);

        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_25_DCR_LOW_LV_NUM_G_2 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_18_DCR_LOW_LV_NUM_G_1 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[11] = (BYTE)(PDATA_WORD(0) >> 4);

        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1C_DCR_HIGH_LV_NUM_B_1 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1D_DCR_HIGH_LV_NUM_B_0 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[12] = (BYTE)((PDATA_WORD(0) & 0x3FF) >> 2);

        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_26_DCR_HIGH_LV_NUM_B_2 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1C_DCR_HIGH_LV_NUM_B_1 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[13] = (BYTE)(PDATA_WORD(0) >> 4);

        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1E_DCR_LOW_LV_NUM_B_1 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1F_DCR_LOW_LV_NUM_B_0 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[14] = (BYTE)((PDATA_WORD(0) & 0x3FF) >> 2);

        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_27_DCR_LOW_LV_NUM_B_2 << 2) | _BIT1 | _BIT0);
        pData[0] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        ScalerSetByte(P7_D8_DCR_ADDRESS_PORT, (_P7_D9_PT_1E_DCR_LOW_LV_NUM_B_1 << 2) | _BIT1 | _BIT0);
        pData[1] = ScalerGetByte(P7_D9_DCR_DATA_PORT);
        g_stDCRStoreInfo.pucWinMaxRGB[15] = (BYTE)(PDATA_WORD(0) >> 4);
    }
}
