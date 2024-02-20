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
// ID Code      : RL6369_Series_ColorDCCNormalizeFactorAdjust.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6369_Series_ColorLibInternalInclude.h"

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
void ScalerColorDCCNormalizeFactorAdjust(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Normalize Factor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCCNormalizeFactorAdjust(void)
{
    WORD usHWidth = 0;
    WORD usVHeight = 0;
    WORD usHStart = 0;
    WORD usHEnd = 0;
    WORD usVStart = 0;
    WORD usVEnd = 0;
    BYTE ucBorder = 0;

    // Check if highlight window on
    if(ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, _BIT0) != 0x00)
    {
        // Get highlight window type
        switch(ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0E_HLW_CONTROL0, (_BIT3 | _BIT2)))
        {
            // Full region
            case 0x00:

                usHWidth = g_stMDomainOutputData.usHWidth;
                usVHeight = g_stMDomainOutputData.usVHeight;
                PDATA_DWORD(0) = ((DWORD)4194304 * 255 / usHWidth / usVHeight) & 0xffffff;
                break;

            // Inside window
            case _BIT2:

                ScalerSetBit(P0_60_HLW_ADDR_PORT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                usHStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                usHEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                usVStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                usVEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                ucBorder = ScalerGetByte(P0_61_HLW_DATA_PORT);
                usHWidth = usHEnd + ucBorder - usHStart;
                usVHeight = usVEnd + ucBorder - usVStart;
                PDATA_DWORD(0) = ((DWORD)4194304 * 255 / usHWidth / usVHeight) & 0xffffff;
                break;

            // Outside window
            case _BIT3:

                ScalerSetBit(P0_60_HLW_ADDR_PORT, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                usHStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                usHEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                usVStart = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                usVEnd = (WORD)(ScalerGetByte(P0_61_HLW_DATA_PORT) << 8) | (ScalerGetByte(P0_61_HLW_DATA_PORT));
                ucBorder = ScalerGetByte(P0_61_HLW_DATA_PORT);
                usHWidth = usHEnd + ucBorder - usHStart;
                usVHeight = usVEnd + ucBorder - usVStart;

                // Calculate Outside Count
                PDATA_DWORD(1) = ((DWORD)(g_stMDomainOutputData.usHWidth) * (DWORD)(g_stMDomainOutputData.usVHeight)) - (DWORD)usHWidth * (DWORD)usVHeight;
                PDATA_DWORD(0) = ((DWORD)4194304 * 255 / PDATA_DWORD(1)) & 0xffffff;
                break;

            default:

                usHWidth = g_stMDomainOutputData.usHWidth;
                usVHeight = g_stMDomainOutputData.usVHeight;
                PDATA_DWORD(0) = ((DWORD)4194304 * 255 / usHWidth / usVHeight) & 0xffffff;
                break;
        }
    }
    else
    {
        usHWidth = g_stMDomainOutputData.usHWidth;
        usVHeight = g_stMDomainOutputData.usVHeight;
        PDATA_DWORD(0) = ((DWORD)4194304 * 255 / usHWidth / usVHeight) & 0xffffff;
    }

    ScalerSetBit(P7_C7_DCC_CTRL_0, ~(_BIT1 | _BIT0), _PAGE0);
    ScalerSetByte(P7_C9_DCC_ADDRESS_PORT, _P7_CA_PT_00_PORT_PAGE0_NOR_FACTOR_H);

    ScalerTimerPollingFlagProc(20, P7_C8_DCC_CTRL_1, _BIT6, 1);

    ScalerWrite(P7_CA_DCC_DATA_PORT, 3, &pData[1], _NON_AUTOINC);
}

