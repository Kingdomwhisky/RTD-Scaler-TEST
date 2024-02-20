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
// ID Code      : OsdRoundedWindow.c
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
void ScalerOsdRoundedWindowSize(EnumOsdWindowsType enumOsdWindowsType, EnumOsdRoundedWindowType enumRoundedWinSize);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Window Rounded Window Size
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0 or _OSD_WINDOW_5 or _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8 or _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
//                enumRoundedWinSize -> _OSD_ROUNDED_WIN_SIZE_8x8 or _OSD_ROUNDED_WIN_SIZE_16x16 or _OSD_ROUNDED_WIN_SIZE_32x32
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowSize(EnumOsdWindowsType enumOsdWindowsType, EnumOsdRoundedWindowType enumRoundedWinSize)
{
    BYTE ucTemp = 0;

    if(enumOsdWindowsType == _OSD_WINDOW_0)
    {
        // Set Rouned Window Size
        ucTemp = ScalerOsdFrameControlByteGet((_P0_92_PT_178_WIN0_ADR10_LSB >> 4), _OSD_BYTE0);

        // Set Rouned Window Size
#if(_OSD_WINDOW_ROUNED_PATTERN_32X32_SUPPORT == _ON)
        ucTemp = ((ucTemp & (~(_BIT2 | _BIT1))) | (enumRoundedWinSize));
#else
        ucTemp = ((ucTemp & (~_BIT1)) | (enumRoundedWinSize));
#endif

        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, (_P0_92_PT_178_WIN0_ADR10_LSB >> 4), ucTemp);
    }
    else if(enumOsdWindowsType == _OSD_WINDOW_5)
    {
        // Get Rouned Window Info
        ucTemp = ScalerOsdFrameControlByteGet((_P0_92_PT_19B_WIN5_ADR10_LSB >> 4), _OSD_BYTE0);

        // Set Rouned Window Size
#if(_OSD_WINDOW_ROUNED_PATTERN_32X32_SUPPORT == _ON)
        ucTemp = ((ucTemp & (~(_BIT2 | _BIT1))) | (enumRoundedWinSize));
#else
        ucTemp = ((ucTemp & (~_BIT1)) | (enumRoundedWinSize));
#endif

        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, (_P0_92_PT_19B_WIN5_ADR10_LSB >> 4), ucTemp);
    }
    else if((enumOsdWindowsType >= _OSD_WINDOW_4_1) && (enumOsdWindowsType <= _OSD_WINDOW_4_8))
    {
        // Get Rouned Window Info
        ucTemp = ScalerOsdFrameControlByteGet(((_P0_92_PT_1BE_WIN4_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_4_1) * 7)), _OSD_BYTE0);

        // Set Rouned Window Size
#if(_OSD_WINDOW_ROUNED_PATTERN_32X32_SUPPORT == _ON)
        ucTemp = ((ucTemp & (~(_BIT2 | _BIT1))) | (enumRoundedWinSize));
#else
        ucTemp = ((ucTemp & (~_BIT1)) | (enumRoundedWinSize));
#endif

        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, ((_P0_92_PT_1BE_WIN4_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_4_1) * 7)), ucTemp);
    }
#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
    else if((enumOsdWindowsType >= _OSD_WINDOW_5_1) && (enumOsdWindowsType <= _OSD_WINDOW_5_8))
    {
        // Get Rouned Window Info
        ucTemp = ScalerOsdFrameControlByteGet(((_P0_92_PT_2A6_WIN5_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_5_1) * 10)), _OSD_BYTE0);

        // Set Rouned Window Size
#if(_OSD_WINDOW_ROUNED_PATTERN_32X32_SUPPORT == _ON)
        ucTemp = ((ucTemp & (~(_BIT2 | _BIT1))) | (enumRoundedWinSize));
#else
        ucTemp = ((ucTemp & (~_BIT1)) | (enumRoundedWinSize));
#endif

        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, ((_P0_92_PT_2A6_WIN5_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_5_1) * 10)), ucTemp);
    }
#endif
}
