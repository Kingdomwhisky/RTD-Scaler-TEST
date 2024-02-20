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

#if(_PANEL_TYPE == _LG_LP133WX3_TLA6)
//----------------------------------------------------------------------------------------------------
// ID Code      : Panel.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#undef _PANEL_STR
#define _PANEL_STR                             "LG_LP133WX3_TLA6"

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_LVDS

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#define _LVDS_OUTPUT_PORT                       _LVDS_1_PORT
#define _LVDS_PANEL_SECTION                     _LVDS_PANEL_1_SECTION
#define _LVDS_TABLE_TYPE                        _LVDS_BIT_MAP_TABLE_2_4

#define _LVDS_PORT_SEL                          _LVDS_1_PORT_C
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_CMO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_18_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   860
#define _PANEL_MIN_FRAME_RATE                   560


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         32                  // Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         1280                // Display Horizontal Width
#define _PANEL_DH_END                           (32+1280)           // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         1423                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     1460                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     1400                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        800                // Display Vertical Width
#define _PANEL_DV_END                           (6+800)                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         846                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     867                // Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     811                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      72                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  76                 // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  68                  // Mininum Pixel Clock in MHz

#define _PANEL_POWER_ON_T1                      5                  // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      35                  // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      550                 // Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     250                  // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     20                   // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     1100                 // Panel Power Off T6 (ms)

#if(_PWM_FREQ_FOR_DC_CONTRAL_BL_MODE == _ON)
#define _PWM_FREQ                               1380
#else
#define _PWM_FREQ                               240
#endif
#define _PWM_INVERSE                            _ON

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