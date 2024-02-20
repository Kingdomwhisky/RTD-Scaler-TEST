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
// ID Code      : RL6410_Series_MDomainFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_MDomainLibInternalInclude.h"

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
void ScalerMDomainSetDisplayTimingGenBackgroundVStart(BYTE ucBGVStart_H, BYTE ucBGVStart_L, EnumDBApply enumDBApply);
WORD ScalerMDomainGetDisplayTimingGenBackgroundVStart(void);
void ScalerMDomainSetDisplayTimingGenBackgroundVEnd(BYTE ucBGVEnd_H, BYTE ucBGVEnd_L, EnumDBApply enumDBApply);
WORD ScalerMDomainGetDisplayTimingGenBackgroundVEnd(void);
void ScalerMDomainSetDisplayTimingGenActiveRegionHStart(BYTE ucActHStart_H, BYTE ucActHStart_L, EnumDBApply enumDBApply);
WORD ScalerMDomainGetDisplayTimingGenActiveRegionHStart(void);
WORD ScalerMDomainGetDisplayTimingGenActiveRegionHEnd(void);
void ScalerMDomainSetDisplayTimingGenActiveRegionVStart(BYTE ucActHStart_H, BYTE ucActHStart_L, EnumDBApply enumDBApply);
WORD ScalerMDomainGetDisplayTimingGenActiveRegionVStart(void);
WORD ScalerMDomainGetDisplayTimingGenActiveRegionVEnd(void);
void ScalerMDomainSetCaptureWindowEnable(bit bCapWinEnable);
void ScalerMDomainSetCaptureWindowHStart(BYTE ucCapWinHStart_H, BYTE ucCapWinHStart_L);
WORD ScalerMDomainGetCaptureWindowHStart(void);
void ScalerMDomainSetCaptureWindowHEnd(BYTE ucCapWinHEnd_H, BYTE ucCapWinHEnd_L);
WORD ScalerMDomainGetCaptureWindowHEnd(void);
void ScalerMDomainSetCaptureWindowVStart(BYTE ucCapWinVStart_H, BYTE ucCapWinVStart_L);
WORD ScalerMDomainGetCaptureWindowVStart(void);
void ScalerMDomainSetCaptureWindowVEnd(BYTE ucCapWinVEnd_H, BYTE ucCapWinVEnd_L);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set Display Timgin Gen: Background VStart
// Input Value  : Background VStart
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenBackgroundVStart(BYTE ucBGVStart_H, BYTE ucBGVStart_L, EnumDBApply enumDBApply)
{
    // Set Main V background Start
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucBGVStart_H & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, ucBGVStart_L);
    ScalerGlobalDDomainDBApply(enumDBApply);
}
//--------------------------------------------------
// Description  : Get Display Timgin Gen: Background VStart
// Input Value  : NA
// Output Value : Background VStart
//--------------------------------------------------
WORD ScalerMDomainGetDisplayTimingGenBackgroundVStart(void)
{
    // Get Main V background Start
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H);
    return (((WORD)(ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT) << 8) | ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Set Display Timgin Gen: Background VEnd
// Input Value  : Background VEnd
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenBackgroundVEnd(BYTE ucBGVEnd_H, BYTE ucBGVEnd_L, EnumDBApply enumDBApply)
{
    // Set Main V background End
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucBGVEnd_H & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, ucBGVEnd_L);
    ScalerGlobalDDomainDBApply(enumDBApply);
}
//--------------------------------------------------
// Description  : Get Display Timgin Gen: Background VEnd
// Input Value  : NA
// Output Value : Background VEnd
//--------------------------------------------------
WORD ScalerMDomainGetDisplayTimingGenBackgroundVEnd(void)
{
    // Get Main V background End
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
    return (((WORD)(ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT) << 8) | ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Set Display Timgin Gen: Diaplay active HStart
// Input Value  : Active HStart
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenActiveRegionHStart(BYTE ucActHStart_H, BYTE ucActHStart_L, EnumDBApply enumDBApply)
{
    // Set Main1 H Active HStart
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucActHStart_H & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, ucActHStart_L);
    ScalerGlobalDDomainDBApply(enumDBApply);
}
//--------------------------------------------------
// Description  : Get Display Timgin Gen: Diaplay active HStart
// Input Value  : NA
// Output Value : Active HStart
//--------------------------------------------------
WORD ScalerMDomainGetDisplayTimingGenActiveRegionHStart(void)
{
    // Get Main1 H Active HStart
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_05_DISPLAY_HOR_ACT_STA_H);
    return (((WORD)(ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT) << 8) | ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Get Display Timgin Gen: Diaplay active HEnd
// Input Value  : NA
// Output Value : Active HEnd
//--------------------------------------------------
WORD ScalerMDomainGetDisplayTimingGenActiveRegionHEnd(void)
{
    // Get Main1 H Active HEnd
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_07_DISPLAY_HOR_ACT_END_H);
    return (((WORD)(ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT) << 8) | ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Set Display Timgin Gen: Diaplay active VStart
// Input Value  : Active VStart
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetDisplayTimingGenActiveRegionVStart(BYTE ucActHStart_H, BYTE ucActHStart_L, EnumDBApply enumDBApply)
{
    // Set Main1 V Active HStart
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucActHStart_H & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, ucActHStart_L);
    ScalerGlobalDDomainDBApply(enumDBApply);
}
//--------------------------------------------------
// Description  : Get Display Timgin Gen: Diaplay active VStart
// Input Value  : NA
// Output Value : Active VStart
//--------------------------------------------------
WORD ScalerMDomainGetDisplayTimingGenActiveRegionVStart(void)
{
    // Get Main1 V Active VStart
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_10_DISPLAY_VER_ACT_STA_H);
    return (((WORD)(ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT) << 8) | ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Get Display Timgin Gen: Diaplay active VEnd
// Input Value  : NA
// Output Value : Active VEnd
//--------------------------------------------------
WORD ScalerMDomainGetDisplayTimingGenActiveRegionVEnd(void)
{
    // Get Main1 V Active VEnd
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H);
    return (((WORD)(ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT) << 8) | ScalerGetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin Enable
// Input Value  : Enable
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetCaptureWindowEnable(bit bCapWinEnable)
{
    // Enable capture win
    ScalerSetBit(P35_1C_CW_EN, ~_BIT0, bCapWinEnable);
}
//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin: HStart
// Input Value  : CapWin HStart
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetCaptureWindowHStart(BYTE ucCapWinHStart_H, BYTE ucCapWinHStart_L)
{
    // Set CapWin HStart
    ScalerSetByte(P35_1D_CW_HOR_START_H, (ucCapWinHStart_H & 0x1F));
    ScalerSetByte(P35_1E_CW_HOR_START_L, ucCapWinHStart_L);
}
//--------------------------------------------------
// Description  : Get PIPBlending CaptureWin: HStart
// Input Value  : NA
// Output Value : CapWin HStart
//--------------------------------------------------
WORD ScalerMDomainGetCaptureWindowHStart(void)
{
    // Get CapWin HStart
    return (((WORD)(ScalerGetByte(P35_1D_CW_HOR_START_H) << 8) | ScalerGetByte(P35_1E_CW_HOR_START_L)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin: HEnd
// Input Value  : CapWin HEnd
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetCaptureWindowHEnd(BYTE ucCapWinHEnd_H, BYTE ucCapWinHEnd_L)
{
    // Set CapWin HEnd
    ScalerSetByte(P35_1F_CW_HOR_END_H, (ucCapWinHEnd_H & 0x1F));
    ScalerSetByte(P35_20_CW_HOR_END_L, ucCapWinHEnd_L);
}
//--------------------------------------------------
// Description  : Get PIPBlending CaptureWin: HEnd
// Input Value  : NA
// Output Value : CapWin HEnd
//--------------------------------------------------
WORD ScalerMDomainGetCaptureWindowHEnd(void)
{
    // Get CapWin HEnd
    return (((WORD)(ScalerGetByte(P35_1F_CW_HOR_END_H) << 8) | ScalerGetByte(P35_20_CW_HOR_END_L)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin: HStart
// Input Value  : CapWin HStart
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetCaptureWindowVStart(BYTE ucCapWinVStart_H, BYTE ucCapWinVStart_L)
{
    // Set CapWin VStart
    ScalerSetByte(P35_21_CW_VER_START_H, (ucCapWinVStart_H & 0x1F));
    ScalerSetByte(P35_22_CW_VER_START_L, ucCapWinVStart_L);
}
//--------------------------------------------------
// Description  : Get PIPBlending CaptureWin: HStart
// Input Value  : NA
// Output Value : CapWin VStart
//--------------------------------------------------
WORD ScalerMDomainGetCaptureWindowVStart(void)
{
    // Get CapWin VStart
    return (((WORD)(ScalerGetByte(P35_21_CW_VER_START_H) << 8) | ScalerGetByte(P35_22_CW_VER_START_L)) & 0x1FFF);
}
//--------------------------------------------------
// Description  : Set PIPBlending CaptureWin: HEnd
// Input Value  : CapWin VEnd
// Output Value : NA
//--------------------------------------------------
void ScalerMDomainSetCaptureWindowVEnd(BYTE ucCapWinVEnd_H, BYTE ucCapWinVEnd_L)
{
    // Set CapWin VEnd
    ScalerSetByte(P35_23_CW_VER_END_H, (ucCapWinVEnd_H & 0x1F));
    ScalerSetByte(P35_24_CW_VER_END_L, ucCapWinVEnd_L);
}
