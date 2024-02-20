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
// ID Code      : OsdRoundedWindowOnOff.c
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
void ScalerOsdRoundedWindowOnOff(EnumOsdWindowsType enumOsdWindowsType, bit bOnOff, bit bUpperLeft, bit bLowerLeft, bit bUpperRight, bit bLowerRight);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Window Rounded On/Off
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0 or _OSD_WINDOW_5 or _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8 or _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
//                bOnOff             -> _ENABLE or _DISABLE
//                bUpperLeft         -> _ENABLE or _DISABLE
//                bLowerLeft         -> _ENABLE or _DISABLE
//                bUpperRight        -> _ENABLE or _DISABLE
//                bLowerRight        -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdRoundedWindowOnOff(EnumOsdWindowsType enumOsdWindowsType, bit bOnOff, bit bUpperLeft, bit bLowerLeft, bit bUpperRight, bit bLowerRight)
{
    BYTE ucTemp = 0;

    if(enumOsdWindowsType == _OSD_WINDOW_0)
    {
        // Get Rouned Window Info
        ucTemp = ScalerOsdFrameControlByteGet((_P0_92_PT_178_WIN0_ADR10_LSB >> 4), _OSD_BYTE0);

        // Set Rounded Window on/off
        ucTemp = ((ucTemp & ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0)) | (((BYTE)bUpperLeft << 6) | ((BYTE)bLowerLeft << 5) | ((BYTE)bUpperRight << 4) | ((BYTE)bLowerRight << 3) | (BYTE)bOnOff));
        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, (_P0_92_PT_178_WIN0_ADR10_LSB >> 4), ucTemp);
    }
    else if(enumOsdWindowsType == _OSD_WINDOW_5)
    {
        // Get Rouned Window Info
        ucTemp = ScalerOsdFrameControlByteGet((_P0_92_PT_19B_WIN5_ADR10_LSB >> 4), _OSD_BYTE0);

        // Set Rounded Window on/off
        ucTemp = ((ucTemp & ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0)) | (((BYTE)bUpperLeft << 6) | ((BYTE)bLowerLeft << 5) | ((BYTE)bUpperRight << 4) | ((BYTE)bLowerRight << 3) | (BYTE)bOnOff));
        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, (_P0_92_PT_19B_WIN5_ADR10_LSB >> 4), ucTemp);
    }
    else if((enumOsdWindowsType >= _OSD_WINDOW_4_1) && (enumOsdWindowsType <= _OSD_WINDOW_4_8))
    {
        // Get Rouned Window Info
        ucTemp = ScalerOsdFrameControlByteGet(((_P0_92_PT_1BE_WIN4_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_4_1) * 7)), _OSD_BYTE0);

        // Set Rounded Window on/off
        ucTemp = ((ucTemp & ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0)) | (((BYTE)bUpperLeft << 6) | ((BYTE)bLowerLeft << 5) | ((BYTE)bUpperRight << 4) | ((BYTE)bLowerRight << 3) | (BYTE)bOnOff));
        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, ((_P0_92_PT_1BE_WIN4_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_4_1) * 7)), ucTemp);
    }
#if(_OSD_WINDOW_5_1_5_8_SUPPORT == _ON)
    else if((enumOsdWindowsType >= _OSD_WINDOW_5_1) && (enumOsdWindowsType <= _OSD_WINDOW_5_8))
    {
        // Get Rouned Window Info
        ucTemp = ScalerOsdFrameControlByteGet(((_P0_92_PT_2A6_WIN5_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_5_1) * 10)), _OSD_BYTE0);

        // Set Rounded Window on/off
        ucTemp = ((ucTemp & ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0)) | (((BYTE)bUpperLeft << 6) | ((BYTE)bLowerLeft << 5) | ((BYTE)bUpperRight << 4) | ((BYTE)bLowerRight << 3) | (BYTE)bOnOff));
        ScalerOsdWriteByte((_OSD_WIN_CONTROL | _OSD_BYTE0), _OSD_WITHOUT_DB, ((_P0_92_PT_2A6_WIN5_1_ADR10_LSB >> 4) + ((enumOsdWindowsType - _OSD_WINDOW_5_1) * 10)), ucTemp);
    }
#endif
}

