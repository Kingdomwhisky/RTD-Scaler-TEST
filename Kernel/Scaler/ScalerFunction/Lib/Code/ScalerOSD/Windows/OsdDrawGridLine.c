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
// ID Code      : OsdDrawGridLine.c
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
StructOsdGridWindow g_stOsdGridWindow;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdDrawGridLine(void);
void ScalerOsdDrawGridLinePanelPitch(WORD usPitchHorizontal, WORD usPitchVertical);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Draw grid line
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawGridLine(void)
{
    BYTE pucTemp[3];
    memset(pucTemp, 0, sizeof(pucTemp));

    if((GET_OSD_GRID_WINDOW_NUMBER() == _OSD_WINDOW_2) || (GET_OSD_GRID_WINDOW_NUMBER() == _OSD_WINDOW_3) || (GET_OSD_GRID_WINDOW_NUMBER() == _OSD_WINDOW_4))
    {
        pucTemp[0] = ((BYTE)GET_OSD_GRID_LINE_WIDTH() << 6) | (BYTE) GET_OSD_GRID_LINE_COLOR();
        pucTemp[1] = ((BYTE)GET_OSD_GRID_LINE_HORIZONTAL_ENABLE() << 7) | ((BYTE)GET_OSD_GRID_LINE_VERTICAL_ENABLE() << 6) | (BYTE)GET_OSD_GRID_LINE_OFFSET();
        pucTemp[2] = (BYTE)GET_OSD_GRID_LINE_PITCH() & 0xFF;
        ScalerOsdWriteAllByte((_OSD_WIN_CONTROL), (0x183 + (((BYTE)GET_OSD_GRID_WINDOW_NUMBER() - _OSD_WINDOW_2) * 7)), pucTemp[0], pucTemp[1], pucTemp[2]);

        pucTemp[0] = ((GET_OSD_GRID_LINE_PITCH() & 0xFF00) >> 7) | (BYTE)GET_OSD_GRID_LINE_FUNCTION_ENABLE();
        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, ((_P0_92_PT_184_WIN2_ADR8_LSB >> 4) + (((BYTE)GET_OSD_GRID_WINDOW_NUMBER() - _OSD_WINDOW_2) * 7)), pucTemp[0]);
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    code StructOsdGridWindow g_stOsdWindowGridTest  = { _OSD_WINDOW_2,        bGridLineWindowNumber
                                                        1,                    bGridLineWidth
                                                        1,                    bGridLineColor
                                                        _DISABLE,             bGridLineHorizontalEnable
                                                        _ENABLE,              bGridLineVerticalEnable
                                                        0x03,                 bGridLineOffset
                                                        0x2710,               bGridLinePitch
                                                        _ENABLE               bGridFunctionEnable
                                                      };
    g_stOsdGridWindow = g_stOsdWindowGridTest;
    ScalerOsdDrawGridLine();

*/




//--------------------------------------------------
// Description  : Set grid line pitch pixel
// Input Value  : ucPitchHorizontal -> Horizontal pitch
// Input Value  : ucPitchVertical   -> Vertical pitch
// Output Value :
//--------------------------------------------------
void ScalerOsdDrawGridLinePanelPitch(WORD usPitchHorizontal, WORD usPitchVertical)
{
    ScalerSetByte(P3A_35_FRAME_CTRL_35, (((usPitchHorizontal & 0x700) >> 4) | ((usPitchVertical & 0x700) >> 8)));
    ScalerSetByte(P3A_36_FRAME_CTRL_36, LOBYTE(usPitchHorizontal));
    ScalerSetByte(P3A_37_FRAME_CTRL_37, LOBYTE(usPitchVertical));
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdDrawGridLinePanelPitch(993, 993);
*/
