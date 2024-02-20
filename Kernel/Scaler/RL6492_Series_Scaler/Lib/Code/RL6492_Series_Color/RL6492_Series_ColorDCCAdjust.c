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
// ID Code      : RL6492_Series_ColorDCCAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _DCC_TABLE_SIZE_CTRL                    9
#define _DCC_TABLE_SIZE_CTRL_LSB                5
#define _DCC_TABLE_SIZE_CRV                     23
#define _DCC_TABLE_SIZE_CRV_LSB                 54
#define _DCC_ADJOPTION_TABLE_OFFSET             1
#define _DCC_CONTORL_TABLE_OFFSET               3
#define _DCC_CONTORL_LSB_TABLE_OFFSET           12
#define _DCC_CURVE_TABLE_OFFSET                 17
#define _DCC_CURVE_LSB_TABLE_OFFSET             40


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
void ScalerColorDCCAdjust(BYTE code *pucDccTable, BYTE ucBankAddress);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Adjust DCC Parameter
// Input Value  : pDccTable -> DCC control&user_curve register table
//                ucBankAddress -> Bank address
//                ucAdjustOption ->
//                        _BIT7: _BURSTWRITE_FROM_FLASH / _BURSTWRITE_FROM_XRAM
//                        _BIT6: Y_FORMULA -> 0: Y = (2R+5G+B)/8, 1: Y = (5R+8G+3B)/16
//                        _BIT5: SOFT_CLAMP -> 0: Disable, 1: Enable
//                        _BIT4: DCC_MODE -> 0:Auto Mode, 1: Manual Mode
//                        _BIT3: SCENE_CHANGE -> 0: Disable, 1: Enable
//                        _BIT1: Saturation Compensation -> 0: Disable, 1: Enable
//                        _BIT0: BLD_MODE -> 0: old mode, 1: new mode
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCAdjust(BYTE code *pucDccTable, BYTE ucBankAddress)
{
    BYTE ucAdjustOption = 0;

    if(pucDccTable != NULL)
    {
        ScalerFlashRead(ucBankAddress, (WORD)(&pucDccTable[_DCC_ADJOPTION_TABLE_OFFSET]), 1, &ucAdjustOption);
        // Load DCC table after DCC Flag Done
        ScalerTimerPollingFlagProc(20, P7_C8_DCC_CTRL_1, _BIT6, 1);

        ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), _PAGE0);
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_03_PORT_PAGE0_BBE_CTRL);
        ScalerBurstWrite(&pucDccTable[_DCC_CONTORL_TABLE_OFFSET], _DCC_TABLE_SIZE_CTRL, ucBankAddress, P7_CA_DCC_DATA_PORT, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_17_PORT_PAGE0_YHL_THD);
        ScalerBurstWrite(&pucDccTable[_DCC_CONTORL_LSB_TABLE_OFFSET], _DCC_TABLE_SIZE_CTRL_LSB, ucBankAddress, P7_CA_DCC_DATA_PORT, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));

        // Fill DCC user curve table
        // Select page1
        ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), _PAGE1);
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE1_DEF_CRV01_H);
        ScalerBurstWrite(&pucDccTable[_DCC_CURVE_TABLE_OFFSET], _DCC_TABLE_SIZE_CRV, ucBankAddress, P7_CA_DCC_DATA_PORT, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));
        ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_1B_PORT_PAGE1_DEF_CRV00_HALF_H);
        ScalerBurstWrite(&pucDccTable[_DCC_CURVE_LSB_TABLE_OFFSET], _DCC_TABLE_SIZE_CRV_LSB, ucBankAddress, P7_CA_DCC_DATA_PORT, _BURSTWRITE_DATA_COMMON, (bit)(ucAdjustOption & _BIT7));

        ScalerSetBit(P7_C8_DCC_CTRL_1, ~(_BIT5 | _BIT4), ((ucAdjustOption & (_BIT1 | _BIT0)) << 4));
        ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((ucAdjustOption & (_BIT6 | _BIT5 | _BIT4 | _BIT3)) | _BIT7));
    }
}
