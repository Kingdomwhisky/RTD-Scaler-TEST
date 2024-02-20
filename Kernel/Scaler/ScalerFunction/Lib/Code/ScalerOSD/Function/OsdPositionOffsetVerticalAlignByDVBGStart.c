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
// ID Code      : OsdPositionOffsetVerticalAlignByDVBGStart.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInternalInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_V_OFFSET_MIN                               (1)

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
BYTE ScalerOsdPositionOffsetVerticalAlignByDVBGStart(BYTE ucVOffset);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Align vertical offset by DVBGStart
// Input Value  : ucVOffset           -> Vertical offset base on DVBGStart 6
// Output Value : Vertical offset compensation depend on DVBGStart
//--------------------------------------------------
BYTE ScalerOsdPositionOffsetVerticalAlignByDVBGStart(BYTE ucVOffset)
{
    WORD usDVBGStart = 0;

    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &pData[0], _AUTOINC);
    usDVBGStart = ((pData[0] & 0x1F) << 8) | (pData[1]);

    if((ScalerOsdGetDoubleFunctionH() == _TRUE) && (ScalerOsdGetDoubleFunctionV() == _TRUE))
    {
        if(usDVBGStart > 6)
        {
            ucVOffset = ucVOffset + ((usDVBGStart - 6) / 2);
        }
        else
        {
            if(ucVOffset >= ((6 - usDVBGStart + 1) / 2))
            {
                ucVOffset = ucVOffset - ((6 - usDVBGStart + 1) / 2);
            }
            else
            {
                ucVOffset = 0;
            }
        }
    }
    else
    {
        if(usDVBGStart > 6)
        {
            ucVOffset = ucVOffset + usDVBGStart - 6;
        }
        else
        {
            if(ucVOffset >= (6 - usDVBGStart))
            {
                ucVOffset = ucVOffset - (6 - usDVBGStart);
            }
            else
            {
                ucVOffset = 0;
            }
        }
    }

    // Check OSD V offset minimum
    if(ucVOffset < _OSD_V_OFFSET_MIN)
    {
        return _OSD_V_OFFSET_MIN;
    }
    else
    {
        return ucVOffset;
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdPositionOffsetVerticalAlignByDVBGStart(6);
*/
