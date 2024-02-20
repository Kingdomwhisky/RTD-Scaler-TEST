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

#if(_PANEL_TYPE == _PANEL_EDP_COMMON_CUS_MINDRAY)
//----------------------------------------------------------------------------------------------------
// ID Code      : Panel.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_2
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_BOE

#if(_MINDRAY_PANEL_SELECT == _MINDRAY_PANEL_EDP_BOE_EV133FHM_N40)
#undef _PANEL_STR
#define _PANEL_STR                              "BOE_EV133FHM_N40"

#define _InFlashLvdsDisplayBitMode              _PANEL_DISP_18_BIT
#define _InFlashDitherWitch                     _ENABLE
#define _InFlashPanelMaxFrameRate               860

#define _InFlashPanelDhStart                    48
#define _InFlashPanelDvStart                    6

#define _InFlashPanelSyncWidth                  8
#define _InFlashPanelSyncHeight                 2

#define _InFlashPanelDhWidth                    1920
#define _InFlashPanelDvHeight                   1080

#define _InFlashPanelMaxDhTotal                 2400
#define _InFlashPanelDhTotal                    2200
#define _InFlashPanelMinDhTotal                 2080

#define _InFlashPanelMaxDvTotal                 1238
#define _InFlashPanelDvTotal                    1125
#define _InFlashPanelMinDvTotal                 1112

#define _InFlashPanelMaxPixClock                160
#define _InFlashPanelPixClock                   148
#define _InFlashPanelMinPixClock                100

#define _InFlashPanelPowerOnT1                  150
#define _InFlashPanelPowerOnT2                  50
#define _InFlashPanelPowerOnT3                  250
#define _InFlashPanelPowerOffT4                 50
#define _InFlashPanelPowerOffT5                 10
#define _InFlashPanelPowerOffT6                 300

#define _PWM_FREQ                               1000
#define _PWM_INVERSE                            _ON

#else
#undef _PANEL_STR
#define _PANEL_STR                              "PANEL_EDP"

#define _InFlashLvdsDisplayBitMode              _PANEL_DISP_18_BIT
#define _InFlashDitherWitch                     _ENABLE
#define _InFlashPanelMaxFrameRate               860

#define _InFlashPanelDhStart                    48
#define _InFlashPanelDvStart                    6

#define _InFlashPanelSyncWidth                  8
#define _InFlashPanelSyncHeight                 2

#define _InFlashPanelDhWidth                    1920
#define _InFlashPanelDvHeight                   1080

#define _InFlashPanelMaxDhTotal                 2400
#define _InFlashPanelDhTotal                    2200
#define _InFlashPanelMinDhTotal                 2080

#define _InFlashPanelMaxDvTotal                 1238
#define _InFlashPanelDvTotal                    1125
#define _InFlashPanelMinDvTotal                 1112

#define _InFlashPanelMaxPixClock                160
#define _InFlashPanelPixClock                   148
#define _InFlashPanelMinPixClock                100

#define _InFlashPanelPowerOnT1                  150
#define _InFlashPanelPowerOnT2                  50
#define _InFlashPanelPowerOnT3                  250
#define _InFlashPanelPowerOffT4                 50
#define _InFlashPanelPowerOffT5                 10
#define _InFlashPanelPowerOffT6                 300

#define _PWM_FREQ                               1000
#define _PWM_INVERSE                            _ON

#endif

#define _InFlashPwmFre                          _PWM_FREQ

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    g_stUserDataInFlash.b1LvdsDisplayBitMode//      _PANEL_DISP_18_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   g_stUserDataInFlash.usPanelMaxFrameRate//    860
#define _PANEL_MIN_FRAME_RATE                   460


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         g_stUserDataInFlash.ucPanelDhStart// Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         g_stUserDataInFlash.usPanelDhWidth// Display Horizontal Width
#define _PANEL_DH_END                           (_PANEL_DH_START + _PANEL_DH_WIDTH)                // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         g_stUserDataInFlash.usPanelDhTotal// Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     g_stUserDataInFlash.usPanelMaxDhTotal// Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     g_stUserDataInFlash.usPanelMinDhTotal// Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         g_stUserDataInFlash.ucPanelDvStart// Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        g_stUserDataInFlash.usPanelDvHeight// Display Vertical Width
#define _PANEL_DV_END                           (_PANEL_DV_START + _PANEL_DV_HEIGHT)                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         g_stUserDataInFlash.usPanelDvTotal// Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     g_stUserDataInFlash.usPanelMaxDvTotal// Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     g_stUserDataInFlash.usPanelMinDvTotal// Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    g_stUserDataInFlash.ucPanelSyncWidth// Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   g_stUserDataInFlash.ucPanelSyncHeight// Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      g_stUserDataInFlash.ucPanelPixClock// Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  g_stUserDataInFlash.ucPanelMaxPixClock                // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  g_stUserDataInFlash.ucPanelMinPixClock// Mininum Pixel Clock in MHz


#define _PANEL_POWER_ON_T1                      g_stUserDataInFlash.usPanelPowerOnT1//100                 // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      g_stUserDataInFlash.usPanelPowerOnT2                // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      g_stUserDataInFlash.usPanelPowerOnT3// Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     g_stUserDataInFlash.usPanelPowerOffT4//20                  // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     g_stUserDataInFlash.usPanelPowerOffT5//40                  // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     g_stUserDataInFlash.usPanelPowerOffT6                 // Panel Power Off T6 (ms)


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 150)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ

//--------------------------------------------------
// Definitions for video compensation
//-------------------------------------------------
#define BYPASS_VIDEO_COMPENSATION(Vin, Vout)    ((Vin) == ((Vout) >> 1))


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0)
#define _PANEL_ADC_GAIN_BIAS                    (0)


///////////////////////////
// Color Characteristics //
///////////////////////////



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#endif // End of #if(_PANEL_TYPE == _CMO_LVDS_17)
