// 3440x1440 freesync panel
{
    150,         // _LAST_LINE_TARGET
    _PANEL_AUO, // _PANEL_MANUFACTURER
    _PANEL_DISP_30_BIT, // _PANEL_DISP_COLOR_BIT

    600,        // _PANEL_TYP_FRAME_RATE
    860,        // _PANEL_MAX_FRAME_RATE
    560,        // _PANEL_MIN_FRAME_RATE

#if(_FREESYNC_SUPPORT == _ON)
    600,        // _PANEL_FREESYNC_MAX_FRAME_RATE
    400,        // _PANEL_FREESYNC_MIN_FRAME_RATE
#endif

    48,         // _PANEL_DH_START
    3440,       // _PANEL_DH_WIDTH

    4880,       // _PANEL_DH_TOTAL
    4912,       // _PANEL_DH_TOTAL_MAX
    4848,       // _PANEL_DH_TOTAL_MIN

    6,          // _PANEL_DV_START
    1440,       // _PANEL_DV_HEIGHT

    1468,       // _PANEL_DV_TOTAL
#if(_FREESYNC_SUPPORT == _ON)
    8000,       // _PANEL_DV_TOTAL_MAX
#else
    3720,       // _PANEL_DV_TOTAL_MAX
#endif
    1466,       // _PANEL_DV_TOTAL_MIN

    8,          // _PANEL_DH_SYNC_WIDTH
    2,          // _PANEL_DV_SYNC_HEIGHT

    430,        // _PANEL_PIXEL_CLOCK
    539,        // _PANEL_PIXEL_CLOCK_MAX
    426,        // _PANEL_PIXEL_CLOCK_MIN

    100,        // _PANEL_POWER_ON_T1
    50,         // _PANEL_POWER_ON_T2
    230,        // _PANEL_POWER_ON_T3

    230,        // _PANEL_POWER_OFF_T4
    20,         // _PANEL_POWER_OFF_T5
    1200,       // _PANEL_POWER_OFF_T6
},

