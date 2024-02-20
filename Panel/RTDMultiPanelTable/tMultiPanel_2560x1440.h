// 2560x1440
{
    2495,       // _LAST_LINE_TARGET
    _PANEL_LGD, // _PANEL_MANUFACTURER
    _PANEL_DISP_24_BIT,

    600,        // _PANEL_TYP_FRAME_RATE
    860,        // _PANEL_MAX_FRAME_RATE
    560,        // _PANEL_MIN_FRAME_RATE

#if(_FREESYNC_SUPPORT == _ON)
    1440,       // _PANEL_FREESYNC_MAX_FRAME_RATE
    400,        // _PANEL_FREESYNC_MIN_FRAME_RATE
#endif

    48,         // _PANEL_DH_START
    2560,       // _PANEL_DH_WIDTH

    2720,       // _PANEL_DH_TOTAL
    2736,       // _PANEL_DH_TOTAL_MAX
    2704,       // _PANEL_DH_TOTAL_MIN

    6,          // _PANEL_DV_START
    1440,       // _PANEL_DV_HEIGHT

    1481,       // _PANEL_DV_TOTAL
#if(_FREESYNC_SUPPORT == _ON)
    8000,       // _PANEL_DV_TOTAL_MAX
#else
    1483,       // _PANEL_DV_TOTAL_MAX
#endif
    1479,       // _PANEL_DV_TOTAL_MIN

    8,          // _PANEL_DH_SYNC_WIDTH
    2,          // _PANEL_DV_SYNC_HEIGHT

    241,        // _PANEL_PIXEL_CLOCK
    302,        // _PANEL_PIXEL_CLOCK_MAX
    110,        // _PANEL_PIXEL_CLOCK_MIN

    10,         // _PANEL_POWER_ON_T1
    50,         // _PANEL_POWER_ON_T2
    250,        // _PANEL_POWER_ON_T3

    50,         // _PANEL_POWER_OFF_T4
    10,         // _PANEL_POWER_OFF_T5
    300,        // _PANEL_POWER_OFF_T6
},

