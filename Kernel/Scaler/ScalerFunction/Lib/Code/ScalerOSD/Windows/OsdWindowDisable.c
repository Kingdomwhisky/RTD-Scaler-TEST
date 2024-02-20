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
// ID Code      : OsdWindowDisable.c
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


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdWindowDisable(EnumOsdWindowsType enumOsdWindowsType);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Disable window
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0,   _OSD_WINDOW_1,   _OSD_WINDOW_2,   _OSD_WINDOW_3,   _OSD_WINDOW_4,   _OSD_WINDOW_5,
//                                      _OSD_WINDOW_6,   _OSD_WINDOW_7,   _OSD_WINDOW_8,   _OSD_WINDOW_9,   _OSD_WINDOW_4_1, _OSD_WINDOW_4_2,
//                                      _OSD_WINDOW_4_3, _OSD_WINDOW_4_4, _OSD_WINDOW_4_5, _OSD_WINDOW_4_6, _OSD_WINDOW_4_7, _OSD_WINDOW_4_8
//                                      _OSD_WINDOW_5_1, _OSD_WINDOW_5_2, _OSD_WINDOW_5_3, _OSD_WINDOW_5_4, _OSD_WINDOW_5_5, _OSD_WINDOW_5_6,
//                                      _OSD_WINDOW_5_7, _OSD_WINDOW_5_8
//                                      _OSD_WINDOW_ALL,
// Output Value :
//--------------------------------------------------
void ScalerOsdWindowDisable(EnumOsdWindowsType enumOsdWindowsType)
{
    WORD usWinTemp = 0;

    if(enumOsdWindowsType == _OSD_WINDOW_ALL)
    {
        for(usWinTemp = 0; usWinTemp < 10; usWinTemp++)
        {
            // Window 0~9
            ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE2), _OSD_WITHOUT_DB, ((_P0_92_PT_103_WIN0_ADR3_LSB >> 4) + usWinTemp * 4), 0x00);

            if(usWinTemp < 8)
            {
                // Window 4-1~4-8
                ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE2), _OSD_WITHOUT_DB, ((_P0_92_PT_203_WIN4_1_ADR3_LSB >> 4) + usWinTemp * 4), 0x00);  // _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8

#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
                // Window 5-1~5-8
                ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE2), _OSD_WITHOUT_DB, ((_P0_92_PT_223_WIN5_1_ADR3_LSB >> 4) + usWinTemp * 4), 0x00);  // _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
#endif
            }
        }
    }
    else
    {
#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
        if((enumOsdWindowsType >= _OSD_WINDOW_5_1) && (enumOsdWindowsType <= _OSD_WINDOW_5_8))
        {
            usWinTemp = (_P0_92_PT_223_WIN5_1_ADR3_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_5_1) * 4);
        }
        else
#endif
        {
            if((enumOsdWindowsType >= _OSD_WINDOW_4_1) && (enumOsdWindowsType <= _OSD_WINDOW_4_8))
            {
                usWinTemp = (_P0_92_PT_203_WIN4_1_ADR3_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_4_1) * 4);
            }
            else if(enumOsdWindowsType <= _OSD_WINDOW_9)
            {
                usWinTemp = (_P0_92_PT_103_WIN0_ADR3_LSB >> 4) + (enumOsdWindowsType * 4);
            }
        }

        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE2), _OSD_WITHOUT_DB, usWinTemp, 0x00);
    }
}


/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdWindowDisable(_OSD_WINDOW_0);
*/
