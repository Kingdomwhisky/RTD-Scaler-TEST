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
// ID Code      : MultiPanel_template.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel parameter in variable
//--------------------------------------------------
#ifndef _PANEL_MULTIPANEL_VARIABLE
#define _PANEL_MULTIPANEL_VARIABLE              _OFF
#endif

//--------------------------------------------------
// Macros of MDomain Panel Index/Info struct
//--------------------------------------------------
#define GET_MDOMAIN_PANEL_INDEX()               (g_ucDDomainPanelIndex)

#if(_PANEL_MULTIPANEL_VARIABLE == _ON)

#define SET_MDOMAIN_PANEL_INDEX(x)              {\
                                                    g_ucDDomainPanelIndex = ((x) % _PANEL_AMOUNT);\
                                                    g_stPanelData = tPanelData[g_ucDDomainPanelIndex];\
                                                }

#define GET_MDOMAIN_PANAL_INFO()                (g_stPanelData)

#else

#define SET_MDOMAIN_PANEL_INDEX(x)              {\
                                                    g_ucDDomainPanelIndex = ((x) % _PANEL_AMOUNT);\
                                                }

#define GET_MDOMAIN_PANAL_INFO()                (tPanelData[g_ucDDomainPanelIndex])

#endif

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     (GET_MDOMAIN_PANAL_INFO().ucManufacturer)

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    (GET_MDOMAIN_PANAL_INFO().ucColorBit)


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
// Panel Frame Rate (Unit: 0.1 Hz)
#define _PANEL_TYP_FRAME_RATE                   (GET_MDOMAIN_PANAL_INFO().usDVfreq)
#define _PANEL_MAX_FRAME_RATE                   (GET_MDOMAIN_PANAL_INFO().usDVfreq_max)
#define _PANEL_MIN_FRAME_RATE                   (GET_MDOMAIN_PANAL_INFO().usDVfreq_min)

// Panel H/V resolution
#define _PANEL_DH_START                         (GET_MDOMAIN_PANAL_INFO().usDHstart)
#define _PANEL_DH_WIDTH                         (GET_MDOMAIN_PANAL_INFO().usDHwidth)
#define _PANEL_DH_END                           (_PANEL_DH_START + _PANEL_DH_WIDTH)
#define _PANEL_DH_SYNC_WIDTH                    (GET_MDOMAIN_PANAL_INFO().usDHSwidth)
#define _PANEL_DH_TOTAL                         (GET_MDOMAIN_PANAL_INFO().usDHtotal)
#define _PANEL_DH_TOTAL_MAX                     (GET_MDOMAIN_PANAL_INFO().usDHtotal_max)
#define _PANEL_DH_TOTAL_MIN                     (GET_MDOMAIN_PANAL_INFO().usDHtotal_min)

#define _PANEL_DV_START                         (GET_MDOMAIN_PANAL_INFO().usDVstart)
#define _PANEL_DV_HEIGHT                        (GET_MDOMAIN_PANAL_INFO().usDVheight)
#define _PANEL_DV_END                           (_PANEL_DV_START + _PANEL_DV_HEIGHT)
#define _PANEL_DV_SYNC_HEIGHT                   (GET_MDOMAIN_PANAL_INFO().usDVSwidth)
#define _PANEL_DV_TOTAL                         (GET_MDOMAIN_PANAL_INFO().usDVtotal)
#define _PANEL_DV_TOTAL_MAX                     (GET_MDOMAIN_PANAL_INFO().usDVtotal_max)
#define _PANEL_DV_TOTAL_MIN                     (GET_MDOMAIN_PANAL_INFO().usDVtotal_min)

// Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK                      (GET_MDOMAIN_PANAL_INFO().usPixelClock)
#define _PANEL_PIXEL_CLOCK_MAX                  (GET_MDOMAIN_PANAL_INFO().usPixelClock_max)
#define _PANEL_PIXEL_CLOCK_MIN                  (GET_MDOMAIN_PANAL_INFO().usPixelClock_min)

// Panel Power On T1 ~ T6 (ms)
#define _PANEL_POWER_ON_T1                      (GET_MDOMAIN_PANAL_INFO().usT1)
#define _PANEL_POWER_ON_T2                      (GET_MDOMAIN_PANAL_INFO().usT2)
#define _PANEL_POWER_ON_T3                      (GET_MDOMAIN_PANAL_INFO().usT3)
#define _PANEL_POWER_OFF_T4                     (GET_MDOMAIN_PANAL_INFO().usT4)
#define _PANEL_POWER_OFF_T5                     (GET_MDOMAIN_PANAL_INFO().usT5)
#define _PANEL_POWER_OFF_T6                     (GET_MDOMAIN_PANAL_INFO().usT6)

//--------------------------------------------------
// Definitions of freesync
//--------------------------------------------------
#if(_FREESYNC_SUPPORT == _ON)
#define _PANEL_FREESYNC_MAX_FRAME_RATE          (GET_MDOMAIN_PANAL_INFO().usDVFreesyncfreq_max)
#define _PANEL_FREESYNC_MIN_FRAME_RATE          (GET_MDOMAIN_PANAL_INFO().usDVFreesyncfreq_min)
#endif

//--------------------------------------------------
// Definitions of Panel data structure
//--------------------------------------------------
typedef struct
{
    WORD usLastLine;
    BYTE ucManufacturer;
    BYTE ucColorBit;

    WORD usDVfreq;
    WORD usDVfreq_max;
    WORD usDVfreq_min;

#if(_FREESYNC_SUPPORT == _ON)
    WORD usDVFreesyncfreq_max;
    WORD usDVFreesyncfreq_min;
#endif

    WORD usDHstart;
    WORD usDHwidth;

    WORD usDHtotal;
    WORD usDHtotal_max;
    WORD usDHtotal_min;

    WORD usDVstart;
    WORD usDVheight;

    WORD usDVtotal;
    WORD usDVtotal_max;
    WORD usDVtotal_min;

    WORD usDHSwidth;
    WORD usDVSwidth;

    WORD usPixelClock;
    WORD usPixelClock_max;
    WORD usPixelClock_min;

    WORD usT1;
    WORD usT2;
    WORD usT3;
    WORD usT4;
    WORD usT5;
    WORD usT6;
} StructVariablePanel;

//--------------------------------------------------
// Panel Data Variable
//--------------------------------------------------
#if(_PANEL_MULTIPANEL_VARIABLE == _ON)
extern StructVariablePanel g_stPanelData;

#ifdef __SCALER_DDOMAIN__
StructVariablePanel g_stPanelData               _at_ (_XRAM_ADDR_END - sizeof(StructVariablePanel) + 1);
#endif

#endif

//--------------------------------------------------
// Panel Data Table
//--------------------------------------------------
#define _PANEL_AMOUNT                           (5)

extern StructVariablePanel code tPanelData[_PANEL_AMOUNT];

#ifdef __SCALER_DDOMAIN__
StructVariablePanel code tPanelData[] =
{
#include "tMultiPanel_1920x1080.h"
#include "tMultiPanel_2560x1080.h"
#include "tMultiPanel_2560x1440.h"
#include "tMultiPanel_3440x1440.h"
#include "tMultiPanel_3840x2160.h"
};

#endif


/////////////
// Display //
/////////////

//--------------------------------------------------
// Set Last Line Finetune Target
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (\
                                                    GET_MDOMAIN_PANAL_INFO().usDHtotal -\
                                                    GET_MDOMAIN_PANAL_INFO().usLastLine\
                                                )

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ

