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
// ID Code      : RL6369_Series_ColorICMBRILoadTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6369_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of ICM Brightness
//--------------------------------------------------
#define _ICM_BRI_TABLE_SIZE                     8
#define _ONE_CM_TABLE_SIZE                      109
#define _CMN_INDEX_OFFSET                       3
#define _CMN_BRI_TABLE_OFFSET                   104


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
void ScalerColorICMBRILoadTable(BYTE code *pucICMTable, BYTE ucBankNum);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description   : Fill ICM Brightness table
// Input Value   : pICMTable: ICM Table
//                 ucBankNum: Bank Number
//                 ucCMSel: ICM Select
// Output Value  : None
//--------------------------------------------------
void ScalerColorICMBRILoadTable(BYTE code *pucICMTable, BYTE ucBankNum)
{
    BYTE ucI = 0;
    BYTE ucCMSel = 0;
    BYTE ucTemp = 0;

    if(pucICMTable != NULL)
    {
        for(ucI = 0; ucI < 7; ucI++)
        {
            ScalerFlashRead(ucBankNum, (WORD)(&pucICMTable[_CMN_INDEX_OFFSET + ucI * _ONE_CM_TABLE_SIZE]), 1, &ucTemp);

            switch(ucTemp)
            {
                case _ICM_0:
                    ucCMSel = 0;
                    break;

                case _ICM_1:
                    ucCMSel = 1;
                    break;

                case _ICM_2:
                    ucCMSel = 2;
                    break;

                case _ICM_3:
                    ucCMSel = 3;
                    break;

                case _ICM_4:
                    ucCMSel = 4;
                    break;

                case _ICM_5:
                    ucCMSel = 5;
                    break;

                default:
                    return;
            }

            ScalerSetBit(P7_D1_ICM_SEL, ~(_BIT2 | _BIT1 | _BIT0), ucCMSel);
            ScalerSetByte(P7_D2_ICM_ADDR, _P7_D3_PT_67_PORT_CMN_BRI_RANGE);
            ScalerBurstWrite(&pucICMTable[_CMN_BRI_TABLE_OFFSET + ucI * _ONE_CM_TABLE_SIZE], _ICM_BRI_TABLE_SIZE, ucBankNum, P7_D3_ICM_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }
    }
}

