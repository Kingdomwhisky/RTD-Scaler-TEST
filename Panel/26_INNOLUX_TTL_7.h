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

#if(_PANEL_TYPE == _INNOLUX_TTL_7)
//----------------------------------------------------------------------------------------------------
// ID Code      : _INNOLUX_TTL_7).h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_TTL

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#define _TTL_OUTPUT_PORT                        _TTL_2_PORT

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
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

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
#define _PANEL_DH_START                         46
#define _PANEL_DH_WIDTH                         800
#define _PANEL_DH_END                           846

#define _PANEL_DH_TOTAL                         1056
#define _PANEL_DH_TOTAL_MAX                     1200
#define _PANEL_DH_TOTAL_MIN                     862

#define _PANEL_DV_START                         23
#define _PANEL_DV_HEIGHT                        480
#define _PANEL_DV_END                           503

#define _PANEL_DV_TOTAL                         525
#define _PANEL_DV_TOTAL_MAX                     650
#define _PANEL_DV_TOTAL_MIN                     510

#define _PANEL_DH_SYNC_WIDTH                    8
#define _PANEL_DV_SYNC_HEIGHT                   2

#define _PANEL_PIXEL_CLOCK                      33
#define _PANEL_PIXEL_CLOCK_MAX                  47
#define _PANEL_PIXEL_CLOCK_MIN                  26

#define _PANEL_POWER_ON_T1                      20
#define _PANEL_POWER_ON_T2                      40
#define _PANEL_POWER_ON_T3                      250

#define _PANEL_POWER_OFF_T4                     20
#define _PANEL_POWER_OFF_T5                     40
#define _PANEL_POWER_OFF_T6                     600


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

#endif // End of #if(_PANEL_TYPE == _INNOLUX_TTL_7))
