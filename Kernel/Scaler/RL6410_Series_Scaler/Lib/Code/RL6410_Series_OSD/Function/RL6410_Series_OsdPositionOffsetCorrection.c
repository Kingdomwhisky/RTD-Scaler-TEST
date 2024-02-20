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
// ID Code      : RL6410_Series_OsdPositionOffsetCorrection.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_OSDLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SIZE_NORMAL_FB_SHIFT_ON      0
#define _SIZE_NORMAL_FB_SHIFT_OFF     1
#define _SIZE_DOUBLE_FB_SHIFT_ON      2
#define _SIZE_DOUBLE_FB_SHIFT_OFF     3

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
    BYTE ucExtention = 0;
    BYTE ucDivider = 0;
    BYTE ucState = 0;
    WORD usBGHStart = 0;
    WORD usBGVStart = 0;

    // FB enable 5K3K panel, when FB enable DHstart shift 4 pixels OSD will shift 1 pixel
    if(ScalerGetBit(P0_2F_DISPLAY_FORMAT_DOUBLE_BUFFER, _BIT0) == _BIT0)
    {
        ucDivider = 4;
    }
    else
    {
        ucDivider = 2;
    }

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGHStart = ((pData[0] & 0x1F) << 8) | (pData[1]);
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &pData[0], _AUTOINC);
    usBGVStart = ((pData[0] & 0x1F) << 8) | (pData[1]);

    g_ucOSDPositionVOffsetCorrectCompensation = 0;

    if((ScalerOsdGetDoubleFunctionH() == _TRUE) && (ScalerOsdGetDoubleFunctionV() == _TRUE))
    {
        if(ScalerGetBit(P3A_5E_FRAME_CTRL_5E, _BIT7) == _BIT7)
        {
            ucState = _SIZE_DOUBLE_FB_SHIFT_ON;
        }
        else
        {
            ucState = _SIZE_DOUBLE_FB_SHIFT_OFF;
        }
    }
    else
    {
        if(ScalerGetBit(P3A_5E_FRAME_CTRL_5E, _BIT7) == _BIT7)
        {
            ucState = _SIZE_NORMAL_FB_SHIFT_ON;
        }
        else
        {
            ucState = _SIZE_NORMAL_FB_SHIFT_OFF;
        }
    }

    switch(ucState)
    {
        case _SIZE_NORMAL_FB_SHIFT_ON:
            // v offset
            if(usBGVStart >= 4)
            {
                ucOsdVOffset = usBGVStart - 4;
            }
            else
            {
                ucOsdVOffset = 1;
                g_ucOSDPositionVOffsetCorrectCompensation = 3 - usBGVStart;
            }

            // v double delay fine tune
            ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), 0);

            // h offset
            ucExtention = ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN, 0xFF);
            ucOsdHOffset = 40 + (usBGHStart / ucDivider) + ucExtention;
            // h double delay fine tune
            ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), 0);
            break;

        case _SIZE_NORMAL_FB_SHIFT_OFF:

            // v offset
            if(usBGVStart > 2)
            {
                ucOsdVOffset = usBGVStart - 2;
            }
            else
            {
                ucOsdVOffset = 1;
                g_ucOSDPositionVOffsetCorrectCompensation = (usBGVStart == 2) ? (1) : (0);
            }

            // v double delay fine tune
            ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), 0);

            // h offset
            ucOsdHOffset = 40 + (usBGHStart / ucDivider);
            // h double delay fine tune
            ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), 0);
            break;

        case _SIZE_DOUBLE_FB_SHIFT_ON:

            // v offset
            if(usBGVStart >= 6)
            {
                ucOsdVOffset = (usBGVStart - 6) / 2;

                // v double delay fine tune
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), _BIT3);
            }
            else
            {
                ucOsdVOffset = 1;
                g_ucOSDPositionVOffsetCorrectCompensation = (5 - usBGVStart) / 2;

                // v double delay fine tune
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), 0);
            }

            // h offset
            ucExtention = ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN, 0xFF);
            ucOsdHOffset = (24 + (usBGHStart / ucDivider) + ucExtention);
            // h double delay fine tune
            if(ucOsdHOffset % 2 == 0)
            {
                ucOsdHOffset /= 2;
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), 0);
            }
            else
            {
                ucOsdHOffset = (ucOsdHOffset + 1) / 2;
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), _BIT7);
            }
            break;

        case _SIZE_DOUBLE_FB_SHIFT_OFF:
            // v offset
            if(usBGVStart >= 4)
            {
                ucOsdVOffset = (usBGVStart - 4) / 2;

                // v double delay fine tune
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), _BIT3);
            }
            else
            {
                ucOsdVOffset = 1;
                g_ucOSDPositionVOffsetCorrectCompensation = (3 - usBGVStart) / 2;

                // v double delay fine tune
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT3), 0);
            }

            // h offset
            ucOsdHOffset = (24 + (usBGHStart / ucDivider));
            // h double delay fine tune
            if(ucOsdHOffset % 2 == 0)
            {
                ucOsdHOffset /= 2;
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), 0);
            }
            else
            {
                ucOsdHOffset = (ucOsdHOffset + 1) / 2;
                ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7), _BIT7);
            }
            break;

        default:
            break;
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

    if(ucOsdHOffset < 24)
    {
        ucOsdHOffset = 24;  // limitation RL6193 & RL6410
    }

    return ((ucOsdHOffset & 0xFF) << 8 | (ucOsdVOffset & 0xFF));
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdPositionOffsetCorrection();
*/
