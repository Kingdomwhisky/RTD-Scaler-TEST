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
// ID Code      : OsdDrawWindow.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInternalInclude.h"

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
StructOsdWindow g_stOsdWindow;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Draw window
// Input Value  : usXStart -> Horizontal start address
//                usYStart -> Vertical start address
//                usXEnd   -> Horizontal end address
//                usYEnd   -> Vertical end address
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    BYTE pucpTemp[12] = {0};
    WORD usWinTemp = 0;

    if(GET_OSD_WINDOW_BUTTON_ENABLE() == _DISABLE)
    {
        SET_OSD_WINDOW_ENABLE(_ENABLE);
    }

#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
    if(GET_OSD_WINDOW_NUMBER() >= _OSD_WINDOW_5_1)
    {
        usWinTemp = 0x220 + (((BYTE)GET_OSD_WINDOW_NUMBER() - _OSD_WINDOW_5_1) * 4);
    }
    else
#endif
    {
        if(GET_OSD_WINDOW_NUMBER() >= _OSD_WINDOW_4_1)
        {
            usWinTemp = 0x200 + (((BYTE)GET_OSD_WINDOW_NUMBER() - _OSD_WINDOW_4_1) * 4);
        }
        else
        {
            usWinTemp = 0x100 + (GET_OSD_WINDOW_NUMBER() * 4);
        }
    }

    ScalerOsdAddrSet(_OSD_WIN_CONTROL, _OSD_BYTEALL, usWinTemp, _DISABLE);

#if(_OSD_WINDOW_COLOR_PALETTE_INDEX_BIT == 4)
    pucpTemp[0] = ((BYTE)GET_OSD_WINDOW_SHADOW_BORDER_PIXEL_WIDTH() << 3) | GET_OSD_WINDOW_SHADOW_BORDER_PIXEL_HEIGHT();
#else
    // _OSD_WINDOW_COLOR_PALETTE_INDEX_BIT = 6
    pucpTemp[0] = ((BYTE)GET_OSD_WINDOW_COLOR_SHADOW() & _BIT4) << 3 | ((BYTE)GET_OSD_WINDOW_COLOR_BORDER() & _BIT4) << 2 | (BYTE)GET_OSD_WINDOW_SHADOW_BORDER_PIXEL_WIDTH() << 3 | GET_OSD_WINDOW_SHADOW_BORDER_PIXEL_HEIGHT();
#endif

    pucpTemp[1] = ((BYTE)GET_OSD_WINDOW_COLOR_SHADOW() & 0x0F) << 4 | ((BYTE)GET_OSD_WINDOW_COLOR_BORDER() & 0x0F);
    pucpTemp[2] = ((BYTE)GET_OSD_WINDOW_GRADIENT_POLARITY_R() << 7 | (BYTE)GET_OSD_WINDOW_GRADIENT_POLARITY_G() << 6 | (BYTE)GET_OSD_WINDOW_GRADIENT_POLARITY_B() << 5 | (BYTE)GET_OSD_WINDOW_GRADIENT_LEVEL_SETP() << 3 | (BYTE)GET_OSD_WINDOW_GRADIENT_ENABLE_R() << 2 | (BYTE)GET_OSD_WINDOW_GRADIENT_ENABLE_G() << 1 | (BYTE)GET_OSD_WINDOW_GRADIENT_ENABLE_B());
    pucpTemp[3] = ((usXStart & 0xF00) >> 4) | ((usYStart & 0xF00) >> 8);
    pucpTemp[4] = (usXStart & 0x0FF);
    pucpTemp[5] = (usYStart & 0x0FF);
    pucpTemp[6] = ((usXEnd & 0xF00) >> 4) | ((usYEnd & 0xF00) >> 8);
    pucpTemp[7] = (usXEnd & 0x0FF);
    pucpTemp[8] = (usYEnd & 0x0FF);

#if(_OSD_WINDOW_COLOR_PALETTE_INDEX_BIT == 4)
    pucpTemp[9] = ((BYTE)GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE() << 4) | ((BYTE)GET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE() << 3) | ((BYTE)GET_OSD_WINDOW_REFERENCE_DELAY() << 2) | (BYTE)GET_OSD_WINDOW_BORDER_PRIORITY() << 1 | ((BYTE)GET_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION());
    pucpTemp[10] = (BYTE)GET_OSD_WINDOW_GRADIENT_LEVEL_PER() << 5 | (BYTE)GET_OSD_WINDOW_COLOR() & 0x0F;
#else
    // _OSD_WINDOW_COLOR_PALETTE_INDEX_BIT = 6
    pucpTemp[9] = (((BYTE)GET_OSD_WINDOW_COLOR_SHADOW() & _BIT5) << 2) | (((BYTE)GET_OSD_WINDOW_COLOR_BORDER() & _BIT5) << 1) | ((BYTE)GET_OSD_WINDOW_COLOR() & _BIT5) | ((BYTE)GET_OSD_WINDOW_GRADIENT_SATURATED_COLOR_MODE() << 4) | ((BYTE)GET_OSD_WINDOW_GRADIENT_REVERSED_COLOR_MODE() << 3) | ((BYTE)GET_OSD_WINDOW_REFERENCE_DELAY() << 2) | (BYTE)GET_OSD_WINDOW_BORDER_PRIORITY() << 1 | ((BYTE)GET_OSD_WINDOW_GRADIENT_LEVEL_EXTENSION());
    pucpTemp[10] = (BYTE)GET_OSD_WINDOW_GRADIENT_LEVEL_PER() << 5 | (BYTE)GET_OSD_WINDOW_COLOR() & 0x1F;
#endif

    pucpTemp[11] = (BYTE)GET_OSD_WINDOW_BLEND_ENABLE() << 7 | (BYTE)GET_OSD_WINDOW_GRADIENT_ENABLE() << 6 | (BYTE)GET_OSD_WINDOW_GRADIENT_DIRECTION() << 5 | (BYTE)GET_OSD_WINDOW_BUTTON_ENABLE() << 4 | (BYTE)GET_OSD_WINDOW_BUTTON_TYPE() << 1 | (BYTE)GET_OSD_WINDOW_ENABLE();

    if(GET_OSD_WINDOW_WAIT_DEN_STOP() == _ENABLE)
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    }

    ScalerOsdBurstWriteDataPort(pucpTemp, 12, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
    if(GET_OSD_WINDOW_NUMBER() >= _OSD_WINDOW_5_1)
    {
        usWinTemp = 0x2A5 + (((BYTE)GET_OSD_WINDOW_NUMBER() - _OSD_WINDOW_5_1) * 10);
    }
    else
#endif
    {
        usWinTemp = 0x177 + (GET_OSD_WINDOW_NUMBER() * 7);
    }

    pucpTemp[0] = ScalerOsdFrameControlByteGet(usWinTemp, _OSD_BYTE0);
    pucpTemp[0] = ((pucpTemp[0] & ~_BIT0) | (BYTE)GET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE());
    ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, usWinTemp, pucpTemp[0]);

    memset(&g_stOsdWindow, 0x00, sizeof(g_stOsdWindow));
}


/*
//--------------------------------------------------
// example 1
//--------------------------------------------------
    code StructOsdWindow g_stOsdWindowTest = { _OSD_WINDOW_6,                               // b5WindowNumber
                                               _ENABLE,                                     // b1WindowEnable
                                               9,                                           // b6WindowColor
                                               6,                                           // b6WindowColorShadow
                                               0,                                           // b6WindowColorBorder
                                               1,                                           // b3WindowShadowBorderPixelWidth
                                               1,                                           // b3WindowShadowBorderPixelHeight
                                               _OSD_WINDOW_GRADIENT_LEVEL_STEP_3,           // b2WindowGradientLevelStep
                                               _OSD_WINDOW_GRADIENT_LEVEL_PER_5,            // b3WindowGradientLevelPer
                                               _OSD_WINDOW_GRADIENT_POLARITY_DECREASE,      // b1WindowGradientPolarityR
                                               _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,      // b1WindowGradientPolarityG
                                               _OSD_WINDOW_GRADIENT_POLARITY_INCREASE,      // b1WindowGradientPolarityB
                                               _ENABLE,                                     // b1WindowGradientEnableR
                                               _DISABLE,                                    // b1WindowGradientEnableG
                                               _ENABLE,                                     // b1WindowGradientEnableB
                                               0,                                           // b1WindowGradientSaturatedColorMode
                                               0,                                           // b1WindowGradientReversedColorMode
                                               0,                                           // b1WindowReferenceDelay
                                               _OSD_WINDOW_GRADIENT_LEVEL_EXTENSION_8,      // b1WindowGradientLevelExtension
                                               1,                                           // b1WindowBlend
                                               1,                                           // b1WindowGradient
                                               _OSD_WINDOW_GRADIENT_DIRECTION_HORIZONTAL,   // b1WindowGradientDirection
                                               1,                                           // b1WindowButtonEnable
                                               _OSD_WINDOW_BUTTON_TYPE_3D_BUTTON_1,         // b3WindowType
                                               _ENABLE                                      // b1WindowRotationFunctionEnable
                                             };

    g_stOsdWindow = g_stOsdWindowTest;
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));


//--------------------------------------------------
// example 2
//--------------------------------------------------
    SET_OSD_WINDOW_NUMBER(6);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    SET_OSD_WINDOW_COLOR(4);
    SET_OSD_WINDOW_ROTATION_FUNCTION_ENABLE(_ENABLE);
    ScalerOsdDrawWindow(XSTART(100), YSTART(200), XEND(300), YEND(400));

*/
