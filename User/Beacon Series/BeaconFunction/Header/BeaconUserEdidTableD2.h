
//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH))

#ifdef _InFlashPanelDhWidth
#define D2_PANEL_DH_WIDTH     _InFlashPanelDhWidth
#else
#ifdef _PANEL_DH_WIDTH
#define D2_PANEL_DH_WIDTH     _PANEL_DH_WIDTH
#else
#define D2_PANEL_DH_WIDTH      1920
#endif
#endif

#ifdef _InFlashPanelDvHeight
#define D2_PANEL_DV_HEIGHT     _InFlashPanelDvHeight
#else
#ifdef _PANEL_DV_HEIGHT
#define D2_PANEL_DV_HEIGHT     _PANEL_DV_HEIGHT
#else
#define D2_PANEL_DV_HEIGHT      1080
#endif
#endif

BYTE code tEDID_TABLE_D2[] =
{
#if((D2_PANEL_DH_WIDTH == 1920)&&(D2_PANEL_DV_HEIGHT == 1200))
// 1920 x 1200 DVI
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x4A, 0x8B, 0xBF, 0x01, 0x01, 0x00, 0x50, 0x63,
    0x0C, 0x14, 0x01, 0x04, 0xB5, 0x30, 0x1B, 0x78, 0x3A, 0x35, 0x85, 0xA6, 0x56, 0x48, 0x9A, 0x24,
    0x12, 0x50, 0x54, 0xB3, 0x0C, 0x00, 0xD1, 0x00, 0x81, 0x00, 0x81, 0x80, 0x95, 0x00, 0xD1, 0xC0,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x28, 0x3C, 0x80, 0xA0, 0x70, 0xB0, 0x23, 0x40, 0x30, 0x20,
    0x36, 0x00, 0x06, 0x44, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x38, 0x4B, 0x1E,
    0x53, 0x11, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x43,
    0x4C, 0x32, 0x34, 0x30, 0x31, 0x2D, 0x44, 0x56, 0x49, 0x0A, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF,
    0x00, 0x4C, 0x35, 0x36, 0x30, 0x35, 0x31, 0x37, 0x39, 0x34, 0x33, 0x30, 0x32, 0x0A, 0x01, 0x18,
    0x02, 0x03, 0x22, 0x72, 0x4F, 0x01, 0x02, 0x03, 0x04, 0x05, 0x90, 0x11, 0x12, 0x13, 0x14, 0x9F,
    0x06, 0x07, 0x15, 0x16, 0x23, 0x09, 0x7F, 0x07, 0x83, 0x01, 0x00, 0x00, 0x65, 0x03, 0x0C, 0x00,
    0x10, 0x00, 0x28, 0x3C, 0x80, 0xA0, 0x70, 0xB0, 0x23, 0x40, 0x30, 0x20, 0x36, 0x00, 0x06, 0x44,
    0x21, 0x00, 0x00, 0x1E, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C, 0x25, 0x00,
    0xDD, 0x0C, 0x11, 0x00, 0x00, 0x9E, 0x01, 0x1D, 0x80, 0xD0, 0x72, 0x1C, 0x16, 0x20, 0x10, 0x2C,
    0x25, 0x80, 0xDD, 0x0C, 0x11, 0x00, 0x00, 0x9E, 0x02, 0x3A, 0x80, 0xD0, 0x72, 0x38, 0x2D, 0x40,
    0x10, 0x2C, 0x45, 0x80, 0xDD, 0x0C, 0x11, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67,

#else
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x08, 0xA1, 0x56, 0x25, 0x01, 0x01, 0x01, 0x01,
    0x00, 0x1B, 0x01, 0x03, 0xE0, 0x32, 0x1D, 0x78, 0xEA, 0xA6, 0xA0, 0xA6, 0x56, 0x51, 0x9C, 0x26,
    0x10, 0x50, 0x54, 0xAD, 0xCF, 0x00, 0x81, 0x80, 0xA9, 0xC0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,
    0x45, 0x00, 0xDC, 0x0C, 0x11, 0x00, 0x00, 0x1E, 0xEE, 0x34, 0x40, 0x10, 0x62, 0x00, 0x27, 0x40,
    0x60, 0xA8, 0x3A, 0x00, 0xDC, 0x0C, 0x11, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x32,
    0x4C, 0x1F, 0x50, 0x13, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC,
    0x00, 0x43, 0x4C, 0x32, 0x32, 0x2D, 0x44, 0x56, 0x49, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x00, 0x85,
#endif

};

#endif