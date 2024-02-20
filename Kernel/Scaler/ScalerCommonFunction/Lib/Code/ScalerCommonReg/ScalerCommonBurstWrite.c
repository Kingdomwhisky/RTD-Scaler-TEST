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
// ID Code      : ScalerCommonBurstWrite.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerCommonRegLibInternalInclude.h"

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

void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : usAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
void ScalerBurstWrite(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, WORD usHostAddr, BYTE ucTableType, bit bTableLocation)
{
    BYTE ucTimeOut = 100;

    ScalerSetByte(P0_9F_PAGE_SEL, HIBYTE(usHostAddr));

    // Disable burst write data and burst write command function.
    MCU_FFF3_SCA_INF_CONTROL &= 0xE7;

    // Disable Burst write Auto Inc
    MCU_FFF3_SCA_INF_CONTROL |= _BIT5;

    if((ucTableType == _BURSTWRITE_DATA_COMMON) || (ucTableType == _BURSTWRITE_DATA_COMMON_AUTO_INC) || (ucTableType == _BURSTWRITE_DATA_OSD))
    {
        MCU_FFF4_SCA_INF_ADDR = usHostAddr;
    }

    MCU_FFF6_SCA_INF_BWR_ADRH = ucBankNum;

    MCU_FFF7_SCA_INF_BWR_ADRM = (BYTE)((((WORD)pucAddress) & 0xFF00) >> 8);
    MCU_FFF8_SCA_INF_BWR_ADRL = (BYTE)((((WORD)pucAddress) & 0x00FF));

    MCU_FFF9_SCA_INF_BWR_COUNT_H = (BYTE)(((usWriteLength) & 0xFF00) >> 8);
    MCU_FFFA_SCA_INF_BWR_COUNT_L = (BYTE)(((usWriteLength) & 0x00FF));

    if(ucTableType == _BURSTWRITE_DATA_OSD)
    {
        BYTE ucData = 0;

        ucData = ScalerBurstWriteTimeoutCal();

        if(ucData >= 2)
        {
            // Set the interval between two command for OSD Load Font data.
            MCU_FFFB_SCA_INF_PERIOD = ucData;
        }
        else
        {
            MCU_FFFB_SCA_INF_PERIOD = 0x02;
        }
    }
    else
    {
        MCU_FFFB_SCA_INF_PERIOD = 0x03;
    }

    MCU_FFFC_BANK_SWICH_CONTROL |= (_BIT5 & (((BYTE)bTableLocation) << 5));

    if(ucTableType == _BURSTWRITE_COMMAND)
    {
        // Enable burst write command function, enable the function of releasing mcu by interrupt.
        MCU_FFF3_SCA_INF_CONTROL = 0x10;

        while(((MCU_FFF3_SCA_INF_CONTROL & _BIT4) == _BIT4) && (--ucTimeOut > 0))
        {
            // Restart Burst Write When Interrupted
            MCU_FFF3_SCA_INF_CONTROL |= _BIT4;
        }
    }
    else  // _BURSTWRITE_DATA_COMMON/OSD
    {
        if(ucTableType == _BURSTWRITE_DATA_COMMON_AUTO_INC)
        {
            // Enable burst write data function, disable auto address increase, enable the function of releasing mcu by interrupt.
            MCU_FFF3_SCA_INF_CONTROL = 0x08;
        }
        else
        {
            // Enable burst write data function, disable auto address increase, enable the function of releasing mcu by interrupt.
            MCU_FFF3_SCA_INF_CONTROL = 0x28;
        }

        while(((MCU_FFF3_SCA_INF_CONTROL & _BIT3) == _BIT3) && (--ucTimeOut > 0))
        {
            // Restart Burst Write When Interrupted
            MCU_FFF3_SCA_INF_CONTROL |= _BIT3;
        }
    }

    // disable burst data from int xram.
    MCU_FFFC_BANK_SWICH_CONTROL &= ~_BIT5;
}
