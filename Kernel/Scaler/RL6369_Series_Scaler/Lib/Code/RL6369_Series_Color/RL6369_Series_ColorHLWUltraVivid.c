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
// ID Code      : RL6369_Series_ColorHLWUltraVivid.c
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
void ScalerColorHLWIDLTILSRAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
void ScalerColorHLWIDLTILSREnable(EnumFunctionOnOFF enumOn);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Adjust UltraVivid highlight window region
// Input Value  : usHPos, usHWidth, usVPos, usVHeight
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWIDLTILSRAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    DWORD ulScale = 0;
    WORD usBGHStart = 0;
    WORD usBGVStart = 0;
    WORD usActHStart = 0;
    WORD usActHEnd = 0;
    WORD usActVStart = 0;
    WORD usActVEnd = 0;
    bit bIdomainHLWEn = 0;
    WORD usIHLWHStart = 0;
    WORD usIHLWHEnd = 0;
    WORD usIHLWVStart = 0;
    WORD usIHLWVEnd = 0;

    if((usHWidth == 0) || (usVHeight == 0))
    {
        return;
    }


    // change HLW position reference to DH/V Sync!A(Tile mode: Active size bigger than Background size!)
    // get HLW region in four Active region HLW !Areference to active
    // by HSU Factor!Aget LSR HLW region
    // Set LSR HLW regs
    // by SU/D Factor!Aget IDLTI HLW region
    // Set IDLTI HLW regs
    // if one path is without HLW!Athan disable this path's HLW
    //
    // border width
    ScalerGetDataPortByte(P0_60_HLW_ADDR_PORT, _P0_61_PT_08_HLW_BORDER_WIDTH, 1, &pData[0], _AUTOINC);

    if((bit)ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, _BIT6) == 0x00)
    {
        usHWidth = usHWidth + (pData[0] & 0x1F);
    }

    if((bit)ScalerGetDataPortBit(P0_60_HLW_ADDR_PORT, _P0_61_PT_0C_HLW_BORDER_EN, _BIT4) == 0x00)
    {
        usVHeight = usVHeight + (pData[0] & 0x1F);
    }

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGHStart = ((pData[0] & 0x1F) << 8) | (pData[1]);
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGVStart = ((pData[0] & 0x1F) << 8) | (pData[1]);

    usHPos = usHPos + usBGHStart;
    usVPos = usVPos + usBGVStart;


    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H, 2, &pData[0], _AUTOINC);
    usActHStart = ((pData[0] & 0x1F) << 8) | (pData[1]);
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_07_DISPLAY_HOR_ACT_END_H, 2, &pData[0], _AUTOINC);
    usActHEnd = ((pData[0] & 0x1F) << 8) | (pData[1]);
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H, 2, &pData[0], _AUTOINC);
    usActVStart = ((pData[0] & 0x1F) << 8) | (pData[1]);
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H, 2, &pData[0], _AUTOINC);
    usActVEnd = ((pData[0] & 0x1F) << 8) | (pData[1]);

    if((usHPos > usActHEnd) ||
       (usHPos + usHWidth <= usActHStart) ||
       (usVPos > usActVEnd) ||
       (usVPos + usVHeight <= usActVStart))
    {
        bIdomainHLWEn = 0;
    }
    else
    {
        bIdomainHLWEn = 1;
    }

    if(bIdomainHLWEn == 1)
    {
        if(usHPos >= usActHStart)
        {
            usIHLWHStart = usHPos;
        }
        else
        {
            usIHLWHStart = usActHStart;
        }

        if(usHPos + usHWidth < usActHEnd)
        {
            usIHLWHEnd = usHPos + usHWidth;
        }
        else
        {
            usIHLWHEnd = usActHEnd;
        }

        if(usVPos >= usActVStart)
        {
            usIHLWVStart = usVPos;
        }
        else
        {
            usIHLWVStart = usActVStart;
        }

        if(usVPos + usVHeight < usActVEnd)
        {
            usIHLWVEnd = usVPos + usVHeight;
        }
        else
        {
            usIHLWVEnd = usActVEnd;
        }
        usIHLWHStart = usIHLWHStart - usActHStart;
        usIHLWHEnd = usIHLWHEnd - usActHStart;
        usIHLWVStart = usIHLWVStart - usActVStart;
        usIHLWVEnd = usIHLWVEnd - usActVStart;


        if(GET_H_SCALE_UP() == _TRUE)
        {
            ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_00_HOR_SCALE_FACTOR_H, 3, &pData[0], _AUTOINC);

            ulScale = (((DWORD)(pData[0] & 0x0F) << 16) | ((DWORD)pData[1] << 8) | (pData[2]));

            usIHLWHStart = (((ulScale * usIHLWHStart) >> 19) + 1) >> 1;
            usIHLWHEnd = (((ulScale * usIHLWHEnd) >> 19) + 1) >> 1;
        }

        // (LSR) H refers to M domain V refers to D domain
        pData[0] = (BYTE)((usIHLWHStart >> 8) & 0x1F);
        pData[1] = (BYTE)(usIHLWHStart & 0xFF);
        pData[2] = (BYTE)((usIHLWHEnd >> 8) & 0x1F);
        pData[3] = (BYTE)(usIHLWHEnd & 0xFF);
        pData[4] = (BYTE)((usIHLWVStart >> 8) & 0x1F);
        pData[5] = (BYTE)(usIHLWVStart & 0xFF);
        pData[6] = (BYTE)((usIHLWVEnd >> 8) & 0x1F);
        pData[7] = (BYTE)(usIHLWVEnd & 0xFF);

        ScalerWrite(P11_CC_LSR_HLW_H_START_HIGH, 8, pData, _AUTOINC);
    }
    else
    {
        ScalerSetBit(P11_B9_SCALER_LSR_HLW, ~_BIT7, 0x00);
    }
}


//--------------------------------------------------
// Description  : Enable/Disable IDLTI, LSR,
// Input Value  : EnumFunctionOnOFF
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWIDLTILSREnable(EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
        // LSR
        ScalerSetBit(P11_B9_SCALER_LSR_HLW, ~_BIT7, _BIT7);
    }
    else // bOn == _OFF || bOn == _CLOCK_GATED
    {
        // LSR
        ScalerSetBit(P11_B9_SCALER_LSR_HLW, ~_BIT7, 0x00);
    }
}
