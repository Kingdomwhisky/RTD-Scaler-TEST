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
// ID Code      : RL6492_Series_OsdPositionOffsetCorrection.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6492_Series_OSDLibInternalInclude.h"

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
BYTE g_ucOSDPositionVOffsetCorrectCompensation;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdPositionOffsetCorrection(void);
WORD ScalerOsdPositionOffsetCalculation(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Correct Osd position after DVstart change
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerOsdPositionOffsetCorrection(void)
{
    WORD usHVOffset = ScalerOsdPositionOffsetCalculation();
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(HIBYTE(usHVOffset)), Y_POS(LOBYTE(usHVOffset)));
}

//--------------------------------------------------
// Description  : Calculate OSD offset
// Input Value  : None
// Output Value : HVoffset
//--------------------------------------------------
WORD ScalerOsdPositionOffsetCalculation(void)
{
    BYTE ucOsdVOffset = 0;
    BYTE ucOsdHOffset = 0;
    WORD usBGHStart = 0;
    WORD usBGVStart = 0;

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGHStart = ((pData[0] & 0x1F) << 8) | (pData[1]);
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGVStart = ((pData[0] & 0x1F) << 8) | (pData[1]);

    g_ucOSDPositionVOffsetCorrectCompensation = 0;

    if((ScalerOsdGetDoubleFunctionH() == _TRUE) && (ScalerOsdGetDoubleFunctionV() == _TRUE))
    {
        // double size
        // v offset
        if(usBGVStart >= 4)
        {
            ucOsdVOffset = (usBGVStart - 4) / 2;
        }
        else
        {
            ucOsdVOffset = 0;
            g_ucOSDPositionVOffsetCorrectCompensation = (4 - usBGVStart) / 2;
        }

        // v delay fine tune
        ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), 0);

        // h offset
        ucOsdHOffset = (usBGHStart + 16) / 2;
        // h delay fine tune
        ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), 0);
    }
    else
    {
        // normal size
        // v offset
        if(usBGVStart >= 2)
        {
            ucOsdVOffset = usBGVStart - 2;
        }
        else
        {
            ucOsdVOffset = 0;
            g_ucOSDPositionVOffsetCorrectCompensation = 2 - usBGVStart;
        }

        // v double delay fine tune
        ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), 0);

        // h offset
        ucOsdHOffset = usBGHStart + 32;
        // h delay fine tune
        ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), 0);
    }

    // OSD rotation fine tune osd h offset
    pData[0] = ScalerGetByte(P3A_41_FRAME_CTRL_41);
    if((pData[0] & _BIT0) == _BIT0) // OSD Auto Rotation Enable
    {
        switch(pData[0] & (_BIT5 | _BIT4))   // OSD Auto Rotation Direction
        {
            case 0x00:  // ucTemp = _OSD_ROTATE_DEGREE_270;    // CCW
            case _BIT4: // ucTemp = _OSD_ROTATE_DEGREE_90;     // CW
                ucOsdHOffset -= 1;
                break;

            default:
                break;
        }
    }

    if(ucOsdHOffset < 6)
    {
        ucOsdHOffset = 6;  // limitation RL6369 & RL6492
    }

    return ((ucOsdHOffset & 0xFF) << 8 | (ucOsdVOffset & 0xFF));
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdPositionOffsetCorrection();
*/
