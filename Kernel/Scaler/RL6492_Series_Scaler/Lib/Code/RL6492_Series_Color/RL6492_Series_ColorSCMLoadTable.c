
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
// ID Code      : RL6492_Series_ColorSCMLoadTable.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_ColorLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SCM_TABLE_SIZE                     78
#define _SCMN_INDEX_OFFSET                  3
#define _SCMN_TABLE_OFFSET                  4

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
void ScalerColorSCMLoadTable(BYTE code *pucSCMTable, BYTE ucBankNum);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description   : Fill SCM table
// Input Value   : None
// Output Value  : None
//--------------------------------------------------
void ScalerColorSCMLoadTable(BYTE code *pucSCMTable, BYTE ucBankNum)
{
    BYTE ucI = 0;
    BYTE ucSCMSel = 0;
    BYTE pucTemp[2] = {0};

    if(pucSCMTable != NULL)
    {
        ScalerFlashRead(ucBankNum, (WORD)(&pucSCMTable[1]), 2, pucTemp);
        ScalerColorSCMAdjust(pucTemp[0], pucTemp[1]);

        for(ucI = 0; ucI < 9; ucI++)
        {
            ScalerFlashRead(ucBankNum, (WORD)(&pucSCMTable[_SCMN_INDEX_OFFSET + ucI * (_SCM_TABLE_SIZE + 1)]), 1, &pucTemp[0]);

            switch(pucTemp[0])
            {
                case _SCM_0:
                    ucSCMSel = 0;
                    break;

                case _SCM_1:
                    ucSCMSel = 1;
                    break;

                case _SCM_2:
                    ucSCMSel = 2;
                    break;

                case _SCM_3:
                    ucSCMSel = 3;
                    break;

                case _SCM_4:
                    ucSCMSel = 4;
                    break;

                case _SCM_5:
                    ucSCMSel = 5;
                    break;

                case _SCM_6:
                    ucSCMSel = 6;
                    break;

                case _SCM_7:
                    ucSCMSel = 7;
                    break;

                default:
                    return;
            }

            ScalerSetBit(P7_CD_SCM_BLOCK_SELECT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucSCMSel);
            ScalerSetByte(P7_CE_SCM_ACCESS_PORT_CONTROL, 0x00);
            ScalerBurstWrite(&pucSCMTable[_SCMN_TABLE_OFFSET + ucI * (_SCM_TABLE_SIZE + 1)], _SCM_TABLE_SIZE, ucBankNum, P7_CF_SCM_ACCESS_PORT_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }
    }
    else
    {
        ScalerColorSCMAdjust(0x00, 0x00);
    }
}
