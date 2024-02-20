
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
// ID Code      : NoneInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "BeaconNVRamOsd.h"

#if(_OSD_TYPE == _BEACON_OSD)

#define _OSD_3D_FUNCTION                            _OFF

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#define _CONTRAST_MAX                               2848
#define _CONTRAST_MIN                               1248
#else
#define _CONTRAST_MAX                               178
#define _CONTRAST_MIN                               78
#endif

#define _CONTRAST_CENTER                            (((_CONTRAST_MAX - _CONTRAST_MIN) / 2) + _CONTRAST_MIN)

//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
#define _BACKLIGHT_MAX                              255
#else
#define _BACKLIGHT_MAX                              4095
#endif
#define _BACKLIGHT_MIN                              0
#define _BACKLIGHT_CENTER                           (((_BACKLIGHT_MAX - _BACKLIGHT_MIN) / 2) + _BACKLIGHT_MIN)

//--------------------------------------------------
// Definitions of Brightness Range
//--------------------------------------------------
#if(_BRI_TYPE == _BRI_GEN_1_10BIT)
#define _BRIGHTNESS_MAX                             712
#define _BRIGHTNESS_MIN                             312
#else
#define _BRIGHTNESS_MAX                             178
#define _BRIGHTNESS_MIN                             78
#endif

#define _BRIGHTNESS_CENTER                          (((_BRIGHTNESS_MAX - _BRIGHTNESS_MIN) / 2) + _BRIGHTNESS_MIN)

//--------------------------------------------------
// Definitions of Sharpness Range
//--------------------------------------------------
#if(_CUSTOMER == _CUS_TOSHIBA)
#define _SHARPNESS_MAX                              120
#define _SHARPNESS_MIN                              0
#else
#define _SHARPNESS_MAX                              4
#define _SHARPNESS_MIN                              0
#endif
#define _SHARPNESS_CENTER                           (((_SHARPNESS_MAX - _SHARPNESS_MIN) / 2) + _SHARPNESS_MIN)
//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _OSD_PHASE_MAX                              100
#define _OSD_PHASE_MIN                              0

//--------------------------------------------------
// Definitions of Colortemp User RGB
//--------------------------------------------------
#define _USER_RGB_MAX                               255
#define _USER_RGB_MIN                               0
#define _USER_RGB_CENTER                            (((_USER_RGB_MAX - _USER_RGB_MIN) / 2) + _USER_RGB_MIN)

//--------------------------------------------------
// Definitions of OD Gain Range
//--------------------------------------------------
#define _OD_GAIN_MAX                                127
#define _OD_GAIN_MIN                                0
#define _OD_GAIN_CENTER                             (((_OD_GAIN_MAX - _OD_GAIN_MIN) / 2) + _OD_GAIN_MIN)

//--------------------------------------------------
// Definitions of 3D EFFECT
//--------------------------------------------------
#define _3D_EFFECT_MAX                              0x10
#define _3D_EFFECT_MIN                              0x00

//--------------------------------------------------
// Definitions of 2DTO3D EFFECT
//--------------------------------------------------
#define _2DTO3D_H_EFFECT_MAX                        0x30
#define _2DTO3D_H_EFFECT_MIN                        0x00

#define _2DTO3D_H_V_EFFECT_MAX                      0xFF
#define _2DTO3D_H_V_EFFECT_MIN                      0x00

//--------------------------------------------------
// Definitions of Menu Time Range
//--------------------------------------------------
#define _OSD_TIMEOUT_MAX                            60
#define _OSD_TIMEOUT_MIN                            10
#define _OSD_TIMEOUT_CENTER                         (((_OSD_TIMEOUT_MAX - _OSD_TIMEOUT_MIN) / 2) + _OSD_TIMEOUT_MIN)
//--------------------------------------------------
// Definitions of Transparency Range
//--------------------------------------------------
#define _OSD_TRANSPARENCY_MAX                       7
#define _OSD_TRANSPARENCY_MIN                       0
#define _OSD_TRANSPARENCY_CENTER                    (((_OSD_TRANSPARENCY_MAX - _OSD_TRANSPARENCY_MIN) / 2) + _OSD_TRANSPARENCY_MIN)
//--------------------------------------------------
// Definitions of OSD H Position Range
//--------------------------------------------------
#define _OSD_H_POS_MAX                              100
#define _OSD_H_POS_MIN                              0
#define _OSD_H_POS_CENTER                           (((_OSD_H_POS_MAX - _OSD_H_POS_MIN) / 2) + _OSD_H_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_V_POS_MAX                              100
#define _OSD_V_POS_MIN                              0
#define _OSD_V_POS_CENTER                           (((_OSD_V_POS_MAX - _OSD_V_POS_MIN) / 2) + _OSD_V_POS_MIN)

//--------------------------------------------------
// Definitions of OSD V Position Range
//--------------------------------------------------
#define _OSD_ASPECT_ORIGINAL_RATIO_MAX              100
#define _OSD_ASPECT_ORIGINAL_RATIO_MIN              0
#define _OSD_ASPECT_ORIGINAL_RATIO_CENTER           ((_OSD_ASPECT_ORIGINAL_RATIO_MAX - _OSD_ASPECT_ORIGINAL_RATIO_MIN) / 2)

//--------------------------------------------------
// Definitions of Hue Saturation Range
// Allowed Hue = 0 ~ 360, Sat = 0 ~ 330
//--------------------------------------------------


//--------------------------------------------------
// 
// 
//--------------------------------------------------
#if((_ALS_TYPE != _SENSER_NONE))
#if(_CUSTOMER == _CUS_MINDRAY)
#if(_RECOVER_PARAMETER == _ON)
#define GET_OSD_ALS_MANUAL_AUTO_STATUS()                        (g_ucALS_Manual_Auto)
#define SET_OSD_ALS_MANUAL_AUTO_STATUS(x)                       (g_ucALS_Manual_Auto = (x))
#else
#define GET_OSD_ALS_MANUAL_AUTO_STATUS()                        (g_stOSDUserData.ALS_Manual_Auto)
#define SET_OSD_ALS_MANUAL_AUTO_STATUS(x)                       (g_stOSDUserData.ALS_Manual_Auto = (x))
#endif
#endif
#endif
//--------------------------------------------------
// Definitions of OSD Volume Range
//--------------------------------------------------
#define _OSD_VOLUME_MAX                             100
#define _OSD_VOLUME_MIN                             0
#define _OSD_VOLUME_CENTER                          (((_OSD_VOLUME_MAX - _OSD_VOLUME_MIN) / 2) + _OSD_VOLUME_MIN)

//--------------------------------------------------
// Definitions of Hue Saturation Range
//--------------------------------------------------
#define _SIX_COLOR_SATURATION_MAX                   200
#define _SIX_COLOR_SATURATION_MIN                   0
#define _SIX_COLOR_SATURATION_CENTER                100

#define _SIX_COLOR_HUE_MAX                          100
#define _SIX_COLOR_HUE_MIN                          0
#define _SIX_COLOR_HUE_CENTER                       50

//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT1))
#define SET_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT1)

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()                          ((bit)(g_stOsdInfo.ucOsdKeyControl & _BIT0))
#define SET_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()                          (g_stOsdInfo.ucOsdKeyControl &= ~_BIT0)

//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()                        (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT2)
#define SET_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl |= _BIT2)
#define CLR_KEYREPEATSTART()                        (g_stOsdInfo.ucOsdKeyControl &= ~_BIT2)

//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()                       (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl |= _BIT3)
#define CLR_KEYREPEATENABLE()                       (g_stOsdInfo.ucOsdKeyControl &= ~_BIT3)

//--------------------------------------------------
// Macro of key for holding on key until it is up
//--------------------------------------------------
#define GET_KEY_HOLD_ON()                           (bit)(g_stOsdInfo.ucOsdKeyControl & _BIT4)
#define SET_KEY_HOLD_ON()                           (g_stOsdInfo.ucOsdKeyControl |= _BIT4)
#define CLR_KEY_HOLD_ON()                           (g_stOsdInfo.ucOsdKeyControl &= ~_BIT4)
#define GET_KEY_BACKUP_MESSAGE()                    (g_stOsdInfo.ucOsdKeyBackupMessage)
#define SET_KEY_BACKUP_MESSAGE(x)                   (g_stOsdInfo.ucOsdKeyBackupMessage = (x))
//--------------------------------------------------
// Macro of Key Message
//--------------------------------------------------
#define GET_KEYMESSAGE()                            (g_stOsdInfo.ucOsdKeyMessage)
#define SET_KEYMESSAGE(x)                           (g_stOsdInfo.ucOsdKeyMessage = (x))

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
#define GET_UARTKEYSTATE()                          (g_ucUartKeyState)
#define SET_UARTKEYSTATE(x)                         (g_ucUartKeyState = (x))
#endif
//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
#define _MENU_KEY_MESSAGE                           0
#define _RIGHT_KEY_MESSAGE                          1
#define _LEFT_KEY_MESSAGE                           2
#define _EXIT_KEY_MESSAGE                           3
#define _5_KEY_MESSAGE                              4
#define _6_KEY_MESSAGE                              5
#define _7_KEY_MESSAGE                              6
#define _HOLD_KEY_MESSAGE                           7
#define _NONE_KEY_MESSAGE                           8
#define _LEFT_RIGHT_MESSAGE                         9

#define _KEY_AMOUNT                                 4

//--------------------------------------------------
// Definitions of Key Mask
//--------------------------------------------------
#if(_CUSTOMER == _CUS_TOSHIBA)
#define _POWER_KEY_MASK                             (_RIGHT_KEY_MASK | _EXIT_KEY_MASK)
#else
#define _POWER_KEY_MASK                             0x01
#endif
#define _MENU_KEY_MASK                              0x02
#define _RIGHT_KEY_MASK                             0x04
#define _LEFT_KEY_MASK                              0x08
#define _EXIT_KEY_MASK                              0x10
#define _KEY5_MASK                                  0x20
#define _KEY6_MASK                                  0x40
#define _KEY7_MASK                                  0x80
#define _LEFT_RIGHT_KEY_MASK                        (_LEFT_KEY_MASK | _RIGHT_KEY_MASK)

#if(_CUSTOMER == _CUS_TOSHIBA)
#define _SERVISE_KEY_MASK                           (_MENU_KEY_MASK | _LEFT_KEY_MASK)
#define _FACTORY_KEY_MASK                           (_MENU_KEY_MASK | _EXIT_KEY_MASK)
#else
#define _POWER_RIGHT_KEY_MASK                       (_POWER_KEY_MASK | _RIGHT_KEY_MASK)
#define _POWER_MENU_KEY_MASK                        (_POWER_KEY_MASK | _MENU_KEY_MASK)
#define _POWER_LEFT_RIGHT_KEY_MASK                  (_POWER_KEY_MASK | _LEFT_KEY_MASK | _RIGHT_KEY_MASK)
#endif

//--------------------------------------------------
// Macro of ADC Message
//��������Ҫʱʱ����ť��Ӧ�������ϵ�ȥ��flash����
//�����ݲ���Ҫ����flash��
//�ϵ���Ҫ���һ����ť״̬��������check flash������
//--------------------------------------------------
#if(_USER_ADC_ADJUST_BY_RESISTOR == _ON)
#define GET_ADC_CONTROL_ONCE()                     (g_stOsdInfo.ucOsdAdcControlOnce)
#define SET_ADC_CONTROL_ONCE(x)                    (g_stOsdInfo.ucOsdAdcControlOnce = (x))
#endif

//--------------------------------------------------
// Definitions of LED indicction
//--------------------------------------------------
typedef enum
{
    _LED_ALL_OFF = _LED_SYSTEM_END,
} EnumUserLedIndication;


//--------------------------------------------------
// Macro of OSD
//--------------------------------------------------
#define FONTBYTE0(x)                                HIBYTE(0x1000 | (x)), LOBYTE(0x1000 | (x))
#define FONTBYTE1(x)                                HIBYTE(0x5000 | (x)), LOBYTE(0x5000 | (x))
#define FONTBYTE2(x)                                HIBYTE(0x9000 | (x)), LOBYTE(0x9000 | (x))
#define FONTALLBYTE(x)                              HIBYTE(0xD000 | (x)), LOBYTE(0xD000 | (x))
#define WINDOWBYTE0(x)                              HIBYTE(0x0000 | (x)), LOBYTE(0x0000 | (x))
#define WINDOWBYTE1(x)                              HIBYTE(0x4000 | (x)), LOBYTE(0x4000 | (x))
#define WINDOWBYTE2(x)                              HIBYTE(0x8000 | (x)), LOBYTE(0x8000 | (x))
#define WINDOWALLBYTE(x)                            HIBYTE(0xC000 | (x)), LOBYTE(0xC000 | (x))
#define FRAMEBYTE0(x)                               WINDOWBYTE0(x)
#define FRAMEBYTE1(x)                               WINDOWBYTE1(x)
#define FRAMEBYTE2(x)                               WINDOWBYTE2(x)
#define FRAMEALLBYTE(x)                             WINDOWALLBYTE(x)
#define WINNO(x)                                    (x)
#define ROW(x)                                      (x)
#define COL(x)                                      (x)
#define WIDTH(x)                                    (x)
#define HEIGHT(x)                                   (x)
#define LENGTH(x)                                   (x)
#define FGCOLOR(x)                                  (x)
#define BGCOLOR(x)                                  (x)
#define COLOR00(x)                                  (x)
#define COLOR01(x)                                  (x)
#define COLOR10(x)                                  (x)
#define COLOR11(x)                                  (x)
#define XSTART(x)                                   (x)
#define YSTART(x)                                   (x)
#define XEND(x)                                     (x)
#define YEND(x)                                     (x)
#define PIXELROW(x)                                 ((x) * 18)
#define PIXELCOL(x)                                 ((x) * 12)

#define _PALETTE_INDEX0                             0   // 0 ~ 15
#define _PALETTE_INDEX1                             1   // 16 ~ 31
#define _PALETTE_INDEX2                             2   // 32 ~ 47
#define _PALETTE_INDEX3                             3   // 48 ~ 63

typedef enum
{
    _PALETTE_0,
    _PALETTE_1,
};

//--------------------------------------------------
//Font index
//--------------------------------------------------
#define _0                           0x00
#define _1                           0x01
#define _2                           0x02
#define _3                           0x03
#define _4                           0x04
#define _5                           0x05
#define _6                           0x06
#define _7                           0x07
#define _8                           0x08
#define _9                           0x09
#define _COLON                       0x0a
#define _MINUS                       0x0b
#define _LBSM                        0x0c    //left of bracket 
#define _RBSM                        0x0d    //right of bracket
#define _LBT                         0x0e    //left of bracket 
#define _RBT                         0x0f    //right of bracket
#define _SLASH                       0x10
#define _DOT                         0x11
#define _A                           0x12
#define _B                           0x13
#define _C                           0x14
#define _D                           0x15
#define _E                           0x16
#define _F                           0x17
#define _G                           0x18
#define _H                           0x19
#define _I                           0x1a
#define _J                           0x1b
#define _K                           0x1c
#define _L                           0x1d
#define _M                           0x1e
#define _N                           0x1f
#define _O                           0x20
#define _P                           0x21
#define _Q                           0x22
#define _R                           0x23
#define _S                           0x24
#define _T                           0x25
#define _U                           0x26
#define _V                           0x27
#define _W                           0x28
#define _X                           0x29
#define _Y                           0x2a
#define _Z                           0x2b
#define _a                           0x2c
#define _b                           0x2d
#define _c                           0x2e
#define _d                           0x2f
#define _e                           0x30
#define _f                           0x31
#define _g                           0x32
#define _h                           0x33
#define _i                           0x34
#define _j                           0x35
#define _k                           0x36
#define _l                           0x37
#define _m                           0x38
#define _n                           0x39
#define _o                           0x3a
#define _p                           0x3b
#define _q                           0x3c
#define _r                           0x3d
#define _s                           0x3e
#define _t                           0x3f
#define _u                           0x40
#define _v                           0x41
#define _w                           0x42
#define _x                           0x43
#define _y                           0x44
#define _z                           0x45
#define _SPACE                       0x46
#define _POS_OFFSET                  0x47//adjust pos

//define other pixel space
#define _SPACE_5                     0xF5
#define _SPACE_6                     0xF6
#define _SPACE_7                     0xF7
#define _SPACE_8                     0xF8
#define _SPACE_9                     0xF9
#define _SPACE_10                    0xFA
#define _SPACE_11                    0xFB

//MAIN OSD
#if(_CUSTOMER == _CUS_TOSHIBA)
#define _ROW_HEIGHT                                         32

#define _MAIN_OSD_WINDOWS_COL_SIZE                          23
#define _MAIN_OSD_WINDOWS_ROW_SIZE                          12

#define _MAIN_OSD_FONT_COL_SIZE                             (25+7)
#define _MAIN_OSD_FONT_ROW_SIZE                             12

#define _MAIN_OSD_ITEM_ROW_START                            2
#define _MAIN_OSD_ITEM_COL_START                            1//0

#define _BEACON_OSD_ITEM_DATA_COL_START                     19    
#else
#define _ROW_HEIGHT                                         28

#define _MAIN_OSD_WINDOWS_COL_SIZE                          20
#define _MAIN_OSD_WINDOWS_ROW_SIZE                          12

#define _MAIN_OSD_FONT_COL_SIZE                             (25+3)
#define _MAIN_OSD_FONT_ROW_SIZE                             12

#define _MAIN_OSD_ITEM_ROW_START                            2
#define _MAIN_OSD_ITEM_COL_START                            1//0

#define _BEACON_OSD_ITEM_DATA_COL_START                     16    
#endif

#define BeaconItemRow(x)                                    (_MAIN_OSD_ITEM_ROW_START+(x-1))                   


//ADVANCED OSD
#if(_CUSTOMER == _CUS_TOSHIBA)
#define _ADVANCED_OSD_WINDOWS_COL_SIZE                  31
#define _ADVANCED_OSD_WINDOWS_ROW_SIZE                  12

#define _ADVANCED_OSD_FONT_COL_SIZE                     (30+2+11)//29
#define _ADVANCED_OSD_FONT_ROW_SIZE                     11

#define _ADVANCED_OSD_ITEM_ROW_START                    1
#define _ADVANCED_OSD_ITEM_COL_START                    7

#define _ADVANCED_OSD_ITEM_DATA_COL_START               29  
#else
#define _ADVANCED_OSD_WINDOWS_COL_SIZE                  26//25
#define _ADVANCED_OSD_WINDOWS_ROW_SIZE                  12

#define _ADVANCED_OSD_FONT_COL_SIZE                     (30+2+2)//29
#define _ADVANCED_OSD_FONT_ROW_SIZE                     11

#define _ADVANCED_OSD_ITEM_ROW_START                    1
#define _ADVANCED_OSD_ITEM_COL_START                    7

#define _ADVANCED_OSD_ITEM_DATA_COL_START               23
#endif

#define BeaconADColorItemRow(x)                         (_ADVANCED_OSD_ITEM_ROW_START+(x-_BEACON_ADVANCED_OSD_SELECT_COLOR))
#define BeaconADImageItemRow(x)                         (_ADVANCED_OSD_ITEM_ROW_START+(x-_BEACON_ADVANCED_OSD_SELECT_IMAGE))
#define BeaconADSettingItemRow(x)                       (_ADVANCED_OSD_ITEM_ROW_START+(x-_BEACON_ADVANCED_OSD_SELECT_SETTING))

//Hotkey OSD size
#define _HOT_OSD_WINDOWS_COL_SIZE                       (22+6)
#define _HOT_OSD_WINDOWS_ROW_SIZE                       3

//Message OSD size
#define _MEG_OSD_WINDOWS_COL_SIZE                       (18)
#define _MEG_OSD_WINDOWS_ROW_SIZE                       8

//Font set
#define _OSD_FONT_1BIT_ADDRESS                          0x00
#define _OSD_FONT_2BIT_ADDRESS                          0xA8
#define _OSD_FONT_4BIT_ADDRESS                          0x100
#define _Font1Bit                                       1
#define _Font2Bit                                       2
#define _Font4Bit                                       4

#define _ADJUST_POS_OFF                                 0
#define _ADJUST_POS_ON                                  1

//--------------------------------------------------
// default system data
//--------------------------------------------------
/*
{
    BYTE ucModeSlotIndex;                       // Mode Slot Index
    BYTE ucSSC;
    BYTE ucDPEDIDSelect;                        // DP EDID Select

    BYTE b3HDMIHotPlugSupportTime : 3;          // HDMIHotPlugSupportTime(Unit : 100ms)
    BYTE b1HDMIHotPlugSupport : 1;              // HDMIHotPlugSupport
    BYTE b1SourceHPAutoSearch : 1;              // HP User Auto Search
    BYTE b3SourceHPDefaultSearchIndex : 3;      // HP User Defautl SearchIndex

    BYTE b1DPHotPlugDCOffHigh : 1;              // DPHotPlugDCOffHigh
    BYTE b1DPAuxDiffMode : 1;                   // DPAuxDiffMode
    BYTE b3D0DpLanes : 3;
    BYTE b3D1DpLanes : 3;

    BYTE b3D2DpLanes : 3;
    BYTE b3D6DpLanes : 3;
    BYTE b1PowerStatus : 1;                     // Monitor Power Status
    BYTE b1ColorSeamlessChange : 1;             // Colorimetry Seamless Change

    WORD b4SearchPort : 4;                      // Search Port
    WORD b3EdidD0 : 3;
    WORD b3EdidD1 : 3;
    WORD b3EdidD2 : 3;
    WORD b3EdidD3 : 3;

    WORD b3EdidD4 : 3;
    WORD b3EdidD5 : 3;
    WORD b3EdidD6 : 3;
    WORD b4SourceScanType : 4;                  // Source Scan Type
    BYTE b4DPAuxAdjrSetting : 4;                // DPAuxAdjrSetting
    BYTE ucDpIrqTime_10us;                      // DP IRQ HPD time (unit : 10us)
    BYTE b1DPIllegalIdlePatternCheck : 1;       // Eizo DP Illegal Idle Pattern Check Support
}
*/
#define _CUSTOM_SYSTEM_DEFAULT_DATA                    {\
                                                            0x00, \
                                                            _DCLK_SPREAD_RANGE, \
                                                            _DP_EDID_1080P, \
                                                            0x05, \
                                                            _ON, \
                                                            _ON, \
                                                            0x00, \
                                                            _ON, \
                                                            _ON, \
                                                            _D0_DP_MAIN_LINK_LANES, \
                                                            _D1_DP_MAIN_LINK_LANES, \
                                                            _D2_DP_MAIN_LINK_LANES, \
                                                            _D6_DP_MAIN_LINK_LANES, \
                                                            _ON, \
                                                            _TRUE, \
                                                            _DEFAULT_SOURCE_SEARCH_PORT, \
                                                            0, \
                                                            0, \
                                                            0, \
                                                            0, \
                                                            0, \
                                                            0, \
                                                            0, \
                                                            _DEFAULT_SOURCE_SCAN_TYPE, \
                                                            0x03, \
                                                            75, \
                                                            _FALSE, \
                                                        }


//--------------------------------------------------
// Definitions of Checking Max or Min Value Used by OsdDisplayDetOverRange()
//--------------------------------------------------
#define _DET_OVERRANGE_MAX                          (0)
#define _DET_OVERRANGE_MIN                          (1)

//--------------------------------------------------
// Definations of OSD Function
//--------------------------------------------------
#define _SPACE_                                     0xfc
#define _EXT_                                       0xfc
#define _REPEAT_                                    0xfd
#define _NEXT_                                      0xfe
#define _END_                                       0xff


//--------------------------------------------------
// Definations of Write Byte
//--------------------------------------------------
#define _WRITE_BYTE0                                0
#define _WRITE_BYTE1                                1
#define _WRITE_BYTE2                                2
#define _WRITE_BYTEALL                              3


//--------------------------------------------------
// MACRO for OSD Logo Status
//--------------------------------------------------
#define GET_OSD_LOGO_ON()                           (g_stOsdInfo.b1OsdLogo)
#define SET_OSD_LOGO_ON(x)                          (g_stOsdInfo.b1OsdLogo = (x))

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_WAKE_UP_SWITCH_DDCCI_PORT()         (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort)
#define SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(x)        (g_stOsdInfo.b1OsdWakeUpSwitchDdcciPort = (x))
#if(_DP_DEBUG_MSG == _ON)
//--------------------------------------------------
// MACRO for Power Saving Show DP Info
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_INFO()         (g_stOsdInfo.b1OsdWakeUpShowDpINFO)
#define SET_OSD_POWER_SAVING_SHOW_DP_INFO(x)        (g_stOsdInfo.b1OsdWakeUpShowDpINFO = (x))
#define GET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT()    (g_stOsdInfo.b4OsdWakeUpShowDpINFOPort)
#define SET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT(x)   (g_stOsdInfo.b4OsdWakeUpShowDpINFOPort = (x))


#endif

//--------------------------------------------------
// MACRO for Power Saving Show Source
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_SOURCE()          (g_stOsdInfo.b1OsdWakeUpShowSource)
#define SET_OSD_POWER_SAVING_SHOW_SOURCE(x)         (g_stOsdInfo.b1OsdWakeUpShowSource = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_IN_FACTORY_MENU_STATUS()            (g_stOsdInfo.b1OsdFactoryModeStatus)
#define SET_OSD_IN_FACTORY_MENU_STATUS(x)           (g_stOsdInfo.b1OsdFactoryModeStatus = (x))

//--------------------------------------------------
// MACRO for Source Menu Status
//--------------------------------------------------
#define GET_OSD_DO_ASPECT_RATIO()                   (g_stOsdInfo.b1OsdDoAspectRatio)
#define SET_OSD_DO_ASPECT_RATIO(x)                  (g_stOsdInfo.b1OsdDoAspectRatio = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_COLOR_FORMAT()                      (g_stOsdInfo.b3OsdColorFormat)
#define SET_OSD_COLOR_FORMAT(x)                     (g_stOsdInfo.b3OsdColorFormat = (x))

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE_PREVIOUS()                    (g_stOsdInfo.ucOsdStatePrevious)
#define SET_OSD_STATE_PREVIOUS(x)                   (g_stOsdInfo.ucOsdStatePrevious = (x))


//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE()                             (g_stOsdInfo.ucOsdState)
#define SET_OSD_STATE(x)                            (g_stOsdInfo.ucOsdState = (x))

//--------------------------------------------------
// MACRO for Osd Evevt Message
//--------------------------------------------------
#define GET_OSD_EVENT_MESSAGE()                     (g_stOsdInfo.ucOsdEventMsg)
#define SET_OSD_EVENT_MESSAGE(x)                    (g_stOsdInfo.ucOsdEventMsg = (x))

//--------------------------------------------------
// MACRO for Six Color
//--------------------------------------------------
#define GET_OSD_SIX_COLOR()                         (g_stOsdInfo.b3OsdsixColor)
#define SET_OSD_SIX_COLOR(x)                        (g_stOsdInfo.b3OsdsixColor = (x))

//--------------------------------------------------
// MACRO for Six Color Hue
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_HUE()                     (g_stOsdInfo.b3OsdsixColorHue)
#define SET_OSD_SIX_COLOR_HUE(x)                    (g_stOsdInfo.b3OsdsixColorHue = (x))

//--------------------------------------------------
// MACRO for Six Color Saturation
//--------------------------------------------------
#define GET_OSD_SIX_COLOR_SATURATION()              (g_stOsdInfo.b3OsdsixColorSaturation)
#define SET_OSD_SIX_COLOR_SATURATION(x)             (g_stOsdInfo.b3OsdsixColorSaturation = (x))

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_DOUBLE_SIZE()                       (g_stOsdInfo.b1OsdDoubleSizeStatus)
#define SET_OSD_DOUBLE_SIZE(x)                      (g_stOsdInfo.b1OsdDoubleSizeStatus = (x))

//--------------------------------------------------
// MACRO for Freeze Status
//--------------------------------------------------
#define GET_OSD_FREEZE_STATUS()                     (g_stOsdInfo.b1FreezeStatus)
#define SET_OSD_FREEZE_STATUS(x)                    (g_stOsdInfo.b1FreezeStatus = (x))

#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
#define GET_FREEZE_DISABLE_MSG_STATE()              (g_stOsdInfo.b1FreezeDisableOsdStatus)
#define SET_FREEZE_DISABLE_MSG_STATE(x)             (g_stOsdInfo.b1FreezeDisableOsdStatus = (x))
#endif

#define GET_OSD_ITEM_INDEX()                        (g_stOsdInfo.ucOsdItemIndex)
#define SET_OSD_ITEM_INDEX(x)                       (g_stOsdInfo.ucOsdItemIndex = (x))

//==========================================================================================================
// Macro of NVRam BriCon Data
//==========================================================================================================
//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#if(_RECOVER_PARAMETER == _ON)
#define GET_OSD_CONTRAST()                          (g_ucContrast)
#define SET_OSD_CONTRAST(x)                         (g_ucContrast = (x))
#else
#define GET_OSD_CONTRAST()                          (g_stBriConData.usContrast)
#define SET_OSD_CONTRAST(x)                         (g_stBriConData.usContrast = (x))
#endif

//--------------------------------------------------
// MACRO for Contrast
//--------------------------------------------------
#define GET_OSD_BRIGHTNESS()                        (g_stBriConData.usBrightness)
#define SET_OSD_BRIGHTNESS(x)                       (g_stBriConData.usBrightness = (x))

//==========================================================================================================
// Macro of NVRam User Data
//==========================================================================================================
//--------------------------------------------------
// MACRO for Rotation Status
//--------------------------------------------------
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#define GET_OSD_DISP_ROTATION_SIZE_TYPE()           (g_stOSDUserData.b2DispRotationSizeType)
#define SET_OSD_DISP_ROTATION_SIZE_TYPE(x)          (g_stOSDUserData.b2DispRotationSizeType = (x))
#endif


//--------------------------------------------------
// MACRO for DP Port Version
//--------------------------------------------------
#define GET_OSD_DP_D0_VERSION()                     (g_stOSDUserData.b2OsdDpD0PortVersion)
#define SET_OSD_DP_D0_VERSION(x)                    (g_stOSDUserData.b2OsdDpD0PortVersion = (x))

#define GET_OSD_DP_D1_VERSION()                     (g_stOSDUserData.b2OsdDpD1PortVersion)
#define SET_OSD_DP_D1_VERSION(x)                    (g_stOSDUserData.b2OsdDpD1PortVersion = (x))

#define GET_OSD_DP_D2_VERSION()                     (g_stOSDUserData.b2OsdDpD2PortVersion)
#define SET_OSD_DP_D2_VERSION(x)                    (g_stOSDUserData.b2OsdDpD2PortVersion = (x))

#define GET_OSD_DP_D6_VERSION()                     (g_stOSDUserData.b2OsdDpD6PortVersion)
#define SET_OSD_DP_D6_VERSION(x)                    (g_stOSDUserData.b2OsdDpD6PortVersion = (x))

#define GET_OSD_DP_MST()                            (g_stOSDUserData.b3OsdDpMST)
#define SET_OSD_DP_MST(x)                           (g_stOSDUserData.b3OsdDpMST = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DISP_ROTATE()                       (g_stOSDUserData.b3OsdDispRotate)
#define SET_OSD_DISP_ROTATE(x)                      (g_stOSDUserData.b3OsdDispRotate = (x))

//--------------------------------------------------
// MACRO for Latency
//--------------------------------------------------
#define GET_OSD_LATENCY()                           (g_stOSDUserData.b2LatencyStatus)
#define SET_OSD_LATENCY(x)                          (g_stOSDUserData.b2LatencyStatus = (x))

//--------------------------------------------------
// MACRO for Display Rotate
//--------------------------------------------------
#define GET_OSD_DP_VERSION_HOTKEY_DISP()            (g_stOSDUserData.b1OsdDpVersionHotKeyDisp)
#define SET_OSD_DP_VERSION_HOTKEY_DISP(x)           (g_stOSDUserData.b1OsdDpVersionHotKeyDisp = (x))

//--------------------------------------------------
// MACRO for Display
//--------------------------------------------------
#define GET_OSD_POWER_SAVING_SHOW_DP_OPTION()       (g_stOSDUserData.b1PreShowDpHotKeyVersion)
#define SET_OSD_POWER_SAVING_SHOW_DP_OPTION(x)      (g_stOSDUserData.b1PreShowDpHotKeyVersion = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY()                  (g_stOSDUserData.b1PanelUniformity)
#define SET_OSD_PANEL_UNIFORMITY(x)                 (g_stOSDUserData.b1PanelUniformity = (x))

//--------------------------------------------------
// MACRO for Panel Uniformity
//--------------------------------------------------
#define GET_OSD_PANEL_UNIFORMITY_TYPE()             (g_stOSDUserData.b3PanelUniformityType)
#define SET_OSD_PANEL_UNIFORMITY_TYPE(x)            (g_stOSDUserData.b3PanelUniformityType = (x))

//--------------------------------------------------
// MACRO for PCM Soft Proft
//--------------------------------------------------

#define GET_OSD_PCM_SOFT_PROFT_MODE()               (g_stOSDUserData.b1PCMSoftProftMode)
#define SET_OSD_PCM_SOFT_PROFT_MODE(x)              (g_stOSDUserData.b1PCMSoftProftMode = (x))

//--------------------------------------------------
// MACRO for OSD Input Port Value
//--------------------------------------------------
#define GET_OSD_INPUT_PORT_OSD_ITEM()               (g_stOSDUserData.ucOsdInputPort)
#define SET_OSD_INPUT_PORT_OSD_ITEM(x)              (g_stOSDUserData.ucOsdInputPort = (x))


//--------------------------------------------------
// MACRO for OSD Rotate
//--------------------------------------------------
#define GET_OSD_ROTATE_STATUS()                     (g_stOSDUserData.b2OsdRotate)
#define SET_OSD_ROTATE_STATUS(x)                    (g_stOSDUserData.b2OsdRotate = (x))

//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_3DOSD_STATUS()                      (g_stOSDUserData.b1Osd3DOSD)
#define SET_OSD_3DOSD_STATUS(x)                     (g_stOSDUserData.b1Osd3DOSD = (x))

//--------------------------------------------------
// Macro of BackLight
//--------------------------------------------------
#if(_RECOVER_PARAMETER == _ON)
#define GET_OSD_BACKLIGHT()                         (g_ucBackLight)
#define SET_OSD_BACKLIGHT(x)                        (g_ucBackLight = (x))
#else
#define GET_OSD_BACKLIGHT()                         (g_stOSDUserData.usBackLight)
#define SET_OSD_BACKLIGHT(x)                        (g_stOSDUserData.usBackLight = (x))
#endif

//--------------------------------------------------
// Macro of Aspect Origin Ratio
//--------------------------------------------------
#define GET_OSD_ASPECT_ORIGIN_RATIO()               (g_stOSDUserData.ucAspectOriginRatio)
#define SET_OSD_ASPECT_ORIGIN_RATIO(x)              (g_stOSDUserData.ucAspectOriginRatio = (x))

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#if(_RECOVER_PARAMETER == _ON)
#define GET_COLOR_TEMP_TYPE()                       (g_ucColorTempType)
#define SET_COLOR_TEMP_TYPE(x)                      (g_ucColorTempType = (x))
#else
#define GET_COLOR_TEMP_TYPE()                       (g_stOSDUserData.b4ColorTempType)
#define SET_COLOR_TEMP_TYPE(x)                      (g_stOSDUserData.b4ColorTempType = (x))
#endif

#if(_NATIVE_COLORTEMP == _ON)
#if(_RECOVER_PARAMETER == _ON)
#define GET_NATIVE_COLOR_TEMP()                     (g_ucNativeColorTemp)
#define SET_NATIVE_COLOR_TEMP(x)                    (g_ucNativeColorTemp = (x))
#else
#define GET_NATIVE_COLOR_TEMP()                     (g_stOSDUserData.b1NativeColorTemp)
#define SET_NATIVE_COLOR_TEMP(x)                    (g_stOSDUserData.b1NativeColorTemp = (x))
#endif
#endif

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_R()                (g_stColorProcData.usColorTempR >> 4)
#define SET_COLOR_TEMP_TYPE_USER_R(x)               (g_stColorProcData.usColorTempR = ((x) << 4))

//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_G()                (g_stColorProcData.usColorTempG >> 4)
#define SET_COLOR_TEMP_TYPE_USER_G(x)               (g_stColorProcData.usColorTempG = ((x) << 4))
//--------------------------------------------------
// Macro of Color Temperature User R
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE_USER_B()                (g_stColorProcData.usColorTempB >> 4)
#define SET_COLOR_TEMP_TYPE_USER_B(x)               (g_stColorProcData.usColorTempB = ((x) << 4))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_ASPECT_RATIO_TYPE()                 (g_stOSDUserData.b3AspectRatio)
#define SET_OSD_ASPECT_RATIO_TYPE(x)                (g_stOSDUserData.b3AspectRatio = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_VGA_COLOR_FORMAT_STATUS()               (g_stOSDUserData.b3VGARGBYUV)
#define SET_VGA_COLOR_FORMAT_STATUS(x)              (g_stOSDUserData.b3VGARGBYUV = (x))

//--------------------------------------------------
// MACRO for VGA Color Format Status
//--------------------------------------------------
#define GET_DVI_COLOR_FORMAT_STATUS()               (g_stOSDUserData.b3DVIRGBYUV)
#define SET_DVI_COLOR_FORMAT_STATUS(x)              (g_stOSDUserData.b3DVIRGBYUV = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_DDCCI_STATUS()                      (g_stOSDUserData.b1DDCCIStatus)
#define SET_OSD_DDCCI_STATUS(x)                     (g_stOSDUserData.b1DDCCIStatus = (x))

//--------------------------------------------------
// MACRO for Ultra Vivid Status
//--------------------------------------------------
#define GET_OSD_ULTRA_VIVID_STATUS()                (g_stOSDUserData.b2UltraVividStatus)
#define SET_OSD_ULTRA_VIVID_STATUS(x)               (g_stOSDUserData.b2UltraVividStatus = (x))

//--------------------------------------------------
// MACRO for Sharpness
//--------------------------------------------------
#if(_CUSTOMER == _CUS_TOSHIBA)
#define GET_OSD_SHARPNESS()                         (g_stOSDUserData.ucSharpness)
#define SET_OSD_SHARPNESS(x)                        (g_stOSDUserData.ucSharpness = (x))
#else
#define GET_OSD_SHARPNESS()                         (g_stOSDUserData.b3Sharpness)
#define SET_OSD_SHARPNESS(x)                        (g_stOSDUserData.b3Sharpness = (x))
#endif
//--------------------------------------------------
// MACRO for Transparency
//--------------------------------------------------
#define GET_OSD_TRANSPARENCY_STATUS()               (g_stOSDUserData.ucTransparency)
#define SET_OSD_TRANSPARENCY_STATUS(x)              (g_stOSDUserData.ucTransparency = (x))

//--------------------------------------------------
// MACRO for Language
//--------------------------------------------------
#define GET_OSD_LANGUAGE()                          (g_stOSDUserData.b4Language)
#define SET_OSD_LANGUAGE(x)                         (g_stOSDUserData.b4Language = (x))

//--------------------------------------------------
// MACRO for OsdTimeout
//--------------------------------------------------
#define GET_OSD_TIME_OUT()                          (g_stOSDUserData.ucOsdTimeout)
#define SET_OSD_TIME_OUT(x)                         (g_stOSDUserData.ucOsdTimeout = (x))

//--------------------------------------------------
// MACRO for OsdHPos
//--------------------------------------------------
#define GET_OSD_HPOS()                              (g_stOSDUserData.ucOsdHPos)
#define SET_OSD_HPOS(x)                             (g_stOSDUserData.ucOsdHPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#define GET_OSD_VPOS()                              (g_stOSDUserData.ucOsdVPos)
#define SET_OSD_VPOS(x)                             (g_stOSDUserData.ucOsdVPos = (x))

//--------------------------------------------------
// MACRO for OsdVPos
//--------------------------------------------------
#if(_RECOVER_PARAMETER == _ON)
#define GET_OSD_GAMMA()                             (g_ucGamma)
#define SET_OSD_GAMMA(x)                            (g_ucGamma = (x))
#else
#define GET_OSD_GAMMA()                             (g_stOSDUserData.b3Gamma)
#define SET_OSD_GAMMA(x)                            (g_stOSDUserData.b3Gamma = (x))
#endif

//--------------------------------------------------
// MACRO for OD Status
//--------------------------------------------------
#define GET_OSD_OD_STATUS()                         (g_stOSDUserData.b1ODStatus)
#define SET_OSD_OD_STATUS(x)                        (g_stOSDUserData.b1ODStatus = (x))

//--------------------------------------------------
// MACRO for OD Gain
//--------------------------------------------------
#define GET_OSD_OD_GAIN()                           (g_stOSDUserData.ucODGain)
#define SET_OSD_OD_GAIN(x)                          (g_stOSDUserData.ucODGain = (x))

//--------------------------------------------------
// MACRO for Color Effect
//--------------------------------------------------
#define GET_OSD_COLOR_EFFECT()                      (g_stOSDUserData.b4ColorEffect)
#define SET_OSD_COLOR_EFFECT(x)                     (g_stOSDUserData.b4ColorEffect = (x))

//--------------------------------------------------
// MACRO for DCRStatus
//--------------------------------------------------
#define GET_OSD_DCR_STATUS()                        (g_stOSDUserData.b1OsdDcrStatus)
#define SET_OSD_DCR_STATUS(x)                       (g_stOSDUserData.b1OsdDcrStatus = (x))

//--------------------------------------------------
// MACRO for FreeSync Status
//--------------------------------------------------
#define GET_OSD_FREE_SYNC_STATUS()                  (g_stOSDUserData.b1FreeSyncStatus)
#define SET_OSD_FREE_SYNC_STATUS(x)                 (g_stOSDUserData.b1FreeSyncStatus = (x))

//--------------------------------------------------
// MACRO for Clone Mode
//--------------------------------------------------
#define GET_OSD_CLONE_MODE()                        (g_stOSDUserData.b1CloneMode)
#define SET_OSD_CLONE_MODE(x)                       (g_stOSDUserData.b1CloneMode = (x))

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for HDR Mode
//--------------------------------------------------
#define GET_OSD_HDR_MODE()                          (g_stOSDUserData.ucHdrMode)
#define SET_OSD_HDR_MODE(x)                         (g_stOSDUserData.ucHdrMode = (x))

//--------------------------------------------------
// MACRO for Dark Enhance Status
//--------------------------------------------------
#define GET_OSD_DARK_ENHANCE_STATUS()               (g_stOSDUserData.b1DarkEnhanceStatus)
#define SET_OSD_DARK_ENHANCE_STATUS(x)              (g_stOSDUserData.b1DarkEnhanceStatus = (x))

//--------------------------------------------------
// MACRO for HDR Sharpness
//--------------------------------------------------
#define GET_OSD_HDR_SHARPNESS()                     (g_stOSDUserData.b1HdrSharpnesse)
#define SET_OSD_HDR_SHARPNESS(x)                    (g_stOSDUserData.b1HdrSharpnesse = (x))

//--------------------------------------------------
// MACRO for HDR Contrast
//--------------------------------------------------
#define GET_OSD_HDR_CONTRAST()                      (g_stOSDUserData.ucHdrContrast)
#define SET_OSD_HDR_CONTRAST(x)                     (g_stOSDUserData.ucHdrContrast = (x))

#endif

#if(_LOCAL_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// MACRO for Local Dimming
//--------------------------------------------------
#define GET_OSD_LOCAL_DIMMING()                     (g_stOSDUserData.b1HdrLocalDimming)
#define SET_OSD_LOCAL_DIMMING(x)                    (g_stOSDUserData.b1HdrLocalDimming= (x))

//--------------------------------------------------
// MACRO for Local Dimming Smooth Backlight adjust
//--------------------------------------------------
#define GET_OSD_LD_ADJ()                            (g_stOSDUserData.ucHdrLocalDimmingAdj)
#define SET_OSD_LD_ADJ(x)                           (g_stOSDUserData.ucHdrLocalDimmingAdj = (x))
#endif
//--------------------------------------------------
// MACRO for Volume Mute
//--------------------------------------------------
#define GET_OSD_VOLUME_MUTE()                       (g_stOSDUserData.b1VolumeMute)
#define SET_OSD_VOLUME_MUTE(x)                      (g_stOSDUserData.b1VolumeMute = (x))

//--------------------------------------------------
// MACRO for Volume
//--------------------------------------------------
#define GET_OSD_VOLUME()                            (g_stOSDUserData.ucVolume)
#define SET_OSD_VOLUME(x)                           (g_stOSDUserData.ucVolume = (x))

//--------------------------------------------------
// MACRO for Audio Stand a long
//--------------------------------------------------
#define GET_OSD_AUDIO_STAND_ALONE()                 (g_stOSDUserData.b1AudioStandAloneStatus)
#define SET_OSD_AUDIO_STAND_ALONE(x)                (g_stOSDUserData.b1AudioStandAloneStatus = (x))

//--------------------------------------------------
// MACRO for Audio Source
//--------------------------------------------------
#define GET_OSD_AUDIO_SOURCE()                      (g_stOSDUserData.b1AudioSourceStatus)
#define SET_OSD_AUDIO_SOURCE(x)                     (g_stOSDUserData.b1AudioSourceStatus = (x))

//--------------------------------------------------
// MACRO for Hue
//--------------------------------------------------
#define GET_OSD_HUE()                               (g_stOSDUserData.ucHue)
#define SET_OSD_HUE(x)                              (g_stOSDUserData.ucHue = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_SATURATION()                        (g_stOSDUserData.ucSaturation)
#define SET_OSD_SATURATION(x)                       (g_stOSDUserData.ucSaturation = (x))

//--------------------------------------------------
// MACRO for Aspect Ratio Status
//--------------------------------------------------
#define GET_OSD_OVERSCAN_STATUS()                   (g_stOSDUserData.b1OverScan)
#define SET_OSD_OVERSCAN_STATUS(x)                  (g_stOSDUserData.b1OverScan = (x))

//--------------------------------------------------
// MACRO for Saturation
//--------------------------------------------------
#define GET_OSD_HLWIN_TYPE()                        (g_stOSDUserData.ucHLWinType)
#define SET_OSD_HLWIN_TYPE(x)                       (g_stOSDUserData.ucHLWinType = (x))

//--------------------------------------------------
// MACRO for 3D Status
//--------------------------------------------------
#define GET_OSD_3D_STATUS()                         (g_stOSDUserData.b23DStatus)
#define SET_OSD_3D_STATUS(x)                        (g_stOSDUserData.b23DStatus = (x))

//--------------------------------------------------
// MACRO for 3D LR Status
//--------------------------------------------------
#define GET_OSD_3D_LR_STATUS()                      (g_stOSDUserData.b13DLRStatus)
#define SET_OSD_3D_LR_STATUS(x)                     (g_stOSDUserData.b13DLRStatus = (x))

//--------------------------------------------------
// MACRO for 3D Format Status
//--------------------------------------------------
#define GET_OSD_3D_FORMAT_STATUS()                  (g_stOSDUserData.b23DFormatStatus)
#define SET_OSD_3D_FORMAT_STATUS(x)                 (g_stOSDUserData.b23DFormatStatus = (x))

//--------------------------------------------------
// MACRO for 3D EFFECT
//--------------------------------------------------
#define GET_OSD_3D_EFFECT()                         (g_stOSDUserData.uc3DEffect)
#define SET_OSD_3D_EFFECT(x)                        (g_stOSDUserData.uc3DEffect = (x))

//--------------------------------------------------
// MACRO for 3D 3DTO2D
//--------------------------------------------------
#define GET_OSD_3D_3DTO2D()                         (g_stOSDUserData.b13D3DTO2DStatus)
#define SET_OSD_3D_3DTO2D(x)                        (g_stOSDUserData.b13D3DTO2DStatus = (x))

//--------------------------------------------------
// MACRO for 3D Convergence
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE()                    (g_stOSDUserData.uc3DConvergence)
#define SET_OSD_3D_CONVERGENCE(x)                   (g_stOSDUserData.uc3DConvergence = (x))

//--------------------------------------------------
// MACRO for 3D Convergence Mode
//--------------------------------------------------
#define GET_OSD_3D_CONVERGENCE_MODE()               (g_stOSDUserData.b33DConvergenceMode)
#define SET_OSD_3D_CONVERGENCE_MODE(x)              (g_stOSDUserData.b33DConvergenceMode = (x))

//--------------------------------------------------
// MACRO for Auto-Color Type
//--------------------------------------------------
#define _AUTO_COLOR_TYPE_INTERNAL                   0
#define _AUTO_COLOR_TYPE_EXTERNAL                   1

#define GET_OSD_FACTORY_AUTO_COLOR_TYPE()           (g_stOSDUserData.b1FactoryAutoColorType)
#define SET_OSD_FACTORY_AUTO_COLOR_TYPE(x)          (g_stOSDUserData.b1FactoryAutoColorType = (x))

//--------------------------------------------------
// MACRO for PCM Status
//--------------------------------------------------
#define GET_OSD_PCM_STATUS()                        (g_stOSDUserData.b3PCMStatus)
#define SET_OSD_PCM_STATUS(x)                       (g_stOSDUserData.b3PCMStatus = (x))


//--------------------------------------------------
// MACRO for DP Lane Count switch
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define GET_OSD_DP_D0_LANE_MODE()                   (g_stOSDUserData.b3D0DpLaneMode)
#define SET_OSD_DP_D0_LANE_MODE(x)                  (g_stOSDUserData.b3D0DpLaneMode = (x))
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define GET_OSD_DP_D1_LANE_MODE()                   (g_stOSDUserData.b3D1DpLaneMode)
#define SET_OSD_DP_D1_LANE_MODE(x)                  (g_stOSDUserData.b3D1DpLaneMode = (x))
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define GET_OSD_DP_D2_LANE_MODE()                   (g_stOSDUserData.b3D2DpLaneMode)
#define SET_OSD_DP_D2_LANE_MODE(x)                  (g_stOSDUserData.b3D2DpLaneMode = (x))
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
#define GET_OSD_DP_D6_LANE_MODE()                   (g_stOSDUserData.b3D6DpLaneMode)
#define SET_OSD_DP_D6_LANE_MODE(x)                  (g_stOSDUserData.b3D6DpLaneMode = (x))
#endif

//--------------------------------------------------
// MACRO for OSD double size
//--------------------------------------------------
#define GET_OSD_NVRAM_DOUBLE_SIZE()                 (g_stOSDUserData.b1OsdDoubleSize)
#define SET_OSD_NVRAM_DOUBLE_SIZE(x)                (g_stOSDUserData.b1OsdDoubleSize = (x))

//--------------------------------------------------
// MACRO for Panel Time Min
//--------------------------------------------------
#define GET_PANEL_TIME_MIN()                        (g_stPanelTimeData.ucMin)
#define SET_PANEL_TIME_MIN(x)                       (g_stPanelTimeData.ucMin = (x))

//--------------------------------------------------
// MACRO for Panel Time Hour
//--------------------------------------------------
#define GET_PANEL_TIME_HOUR()                       (g_stPanelTimeData.usHour)
#define SET_PANEL_TIME_HOUR(x)                      (g_stPanelTimeData.usHour = (x))

//--------------------------------------------------
// MACRO for Factory Power Saving Case
//--------------------------------------------------
#define GET_FORCE_POW_SAV_STATUS()                  (g_bForcePowSavStatus)
#define SET_FORCE_POW_SAV_STATUS(x)                 (g_bForcePowSavStatus = (x))

//--------------------------------------------------
// MACRO for save EDID to Extern EEP stutas
//--------------------------------------------------
#define GET_EXTERN_EDID_STUTAS()                    (g_stOtherUserData.ucExternEdidStutas)
#define SET_EXTERN_EDID_STUTAS(x)                   (g_stOtherUserData.ucExternEdidStutas = (x))

//--------------------------------------------------
// backlight sensor config
//--------------------------------------------------
#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
#define GET_TARGET_SENSOR()                         (g_stOtherUserData.Sensor_brightness_value) 
#define SET_TARGET_SENSOR(x)                        (g_stOtherUserData.Sensor_brightness_value = (x)) 

#define GET_SENSOR_BACKLIGHT()                      (g_stOtherUserData.Sensor_backlight_value) 
#define SET_SENSOR_BACKLIGHT(x)                     (g_stOtherUserData.Sensor_backlight_value = (x))

#define SET_UPDATE_TARGET_FLAG(x)                   (bUpdateSensorTargetValue = (x))

#define GET_CURRENT_SENSOR()                       (wSensorLux)

#else
#define GET_TARGET_SENSOR()                         (g_stOtherUserData.Sensor_brightness_value) 
#endif
//--------------------------------------------------
// 
//--------------------------------------------------
#if(_DDC_DETECT_EN == _ON)
#define GET_FORCE_DDC_STUTAS()                      (g_ucForceSetDDC)
#define SET_FORCE_DDC_STUTAS(x)                     (g_ucForceSetDDC = (x))
#endif
//--------------------------------------------------
// MACRO for _HDMI_SPLITTER_1X2 IC data control stutas
//--------------------------------------------------
#if(_HDMI_SPLITTER_1X2_EN == _ON)
#define HDMI_SPLITTER_1X2_ID                        0xD0

#define GET_DATA1ST_PORTACONTROL()                  (g_stOtherUserData.Data1st_PortAControl)
#define SET_DATA1ST_PORTACONTROL(x)                 (g_stOtherUserData.Data1st_PortAControl = (x))

#define GET_DATA1ST_OUTPUTSELECT()                  (g_stOtherUserData.Data1st_OutPutSelect)
#define SET_DATA1ST_OUTPUTSELECT(x)                 (g_stOtherUserData.Data1st_OutPutSelect = (x))

#define GET_DATA1ST_EQUALIZATION()                  (g_stOtherUserData.Data1st_Equalization)
#define SET_DATA1ST_EQUALIZATION(x)                 (g_stOtherUserData.Data1st_Equalization = (x))

#define GET_DATA2ND_PORTBCONTROL()                  (g_stOtherUserData.Data2nd_PortBControl)
#define SET_DATA2ND_PORTBCONTROL(x)                 (g_stOtherUserData.Data2nd_PortBControl = (x))

#define GET_DATA2ND_OUTPUTSELECT()                  (g_stOtherUserData.Data2nd_OutPutSelect)
#define SET_DATA2ND_OUTPUTSELECT(x)                 (g_stOtherUserData.Data2nd_OutPutSelect = (x))

#define GET_1ST_DATA()                              ((GET_DATA1ST_PORTACONTROL()<<4) | (GET_DATA1ST_EQUALIZATION()<<2) | GET_DATA1ST_OUTPUTSELECT())
#define GET_2ND_DATA()                              ((GET_DATA2ND_PORTBCONTROL()<<4) | GET_DATA2ND_OUTPUTSELECT())
#endif

//--------------------------------------------------
// 
//--------------------------------------------------
#define CAL_8BIT_PWM_TO_REAL_PWM(x)                 ((((DWORD)x) * ((_PWM_DUT_RESOLUTION == _PWM_12BIT)? 4095:255)) / 255)

//--------------------------------------------------
// Definitions of OSD Number ROW COL
//--------------------------------------------------
#define _OSD_NUMBER_1_ROW                           15
#define _OSD_NUMBER_1_COL                           21

#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_BLUE, _CP_BG)
#define _OSD_NUMBER_UNSTLECT_COLOR                  COLOR(_CP_BLUE, _CP_BG)
//--------------------------------------------------
// Definitions of OSD
//--------------------------------------------------
#define _PFONT_PAGE_0                               0
#define _PFONT_PAGE_1                               1
#define _PFONT_PAGE_2                               2
#define _PFONT_PAGE_ITEM_1                          3
#define _PFONT_PAGE_ITEM_2                          4
#define _PFONT_PAGE_ITEM_3                          5
#define _PFONT_PAGE_ITEM_4                          6
#define _PFONT_PAGE_ITEM_5                          7
#define _PFONT_PAGE_ITEM_6                          8
#define _PFONT_PAGE_ITEM_7                          9
#define _PFONT_PAGE_ITEM_8                          10

#define _OSD_GLOBAL_START                           0x01
#define _OSD_GLOBAL_END                             0x0F

#define _OSD_PAGE_0_START                           0x00
#define _OSD_PAGE_0_END                             0x27

#define _OSD_PAGE_1_START                           0x28
#define _OSD_PAGE_1_END                             0x4F

#define _OSD_PAGE_2_START                           0xC1
#define _OSD_PAGE_2_END                             0xF0

#define _SUB_PAGE_ITEM_1                            (_OSD_PAGE_2_START)
#define _SUB_PAGE_ITEM_1_END                        (_OSD_PAGE_2_START + 6)
#define _SUB_PAGE_ITEM_2                            (_SUB_PAGE_ITEM_1_END)
#define _SUB_PAGE_ITEM_2_END                        (_SUB_PAGE_ITEM_1_END + 6)
#define _SUB_PAGE_ITEM_3                            (_SUB_PAGE_ITEM_2_END)
#define _SUB_PAGE_ITEM_3_END                        (_SUB_PAGE_ITEM_2_END + 10)
#define _SUB_PAGE_ITEM_4                            (_SUB_PAGE_ITEM_3_END)
#define _SUB_PAGE_ITEM_4_END                        (_SUB_PAGE_ITEM_3_END + 5)
#define _SUB_PAGE_ITEM_5                            (_SUB_PAGE_ITEM_4_END)
#define _SUB_PAGE_ITEM_5_END                        (_SUB_PAGE_ITEM_4_END + 6)
#define _SUB_PAGE_ITEM_6                            (_SUB_PAGE_ITEM_5_END)
#define _SUB_PAGE_ITEM_6_END                        (_SUB_PAGE_ITEM_5_END + 8)
#define _SUB_PAGE_ITEM_7                            (_SUB_PAGE_ITEM_6_END)
#define _SUB_PAGE_ITEM_7_END                        (_SUB_PAGE_ITEM_6_END + 6)
#define _SUB_PAGE_ITEM_8                            (_SUB_PAGE_ITEM_7_END)
#define _SUB_PAGE_ITEM_8_END                        (_SUB_PAGE_ITEM_7_END + 6)

#define _NORMAL                                     0
#define _CENTER                                     1
#define _START                                      0
#define _RUN                                        1

#define _UP                                         0
#define _DOWN                                       1

#define _OUTSUBSET                                  0
#define _INSUBSET                                   1
#define _WITHOUTSUB                                 2

//--------------------------------------------------
// Definitions of OSD Window
//--------------------------------------------------
//=========== OSD Window Setting ======================//
//Blending type1:Only windows blending.
//Blending type2:All blending.
//Blending type3:Windows & Character background blending.
#define _WIN0                                       0
#define _WIN1                                       1
#define _WIN2                                       2
#define _WIN3                                       3
#define _WIN4                                       4
#define _WIN5                                       5
#define _WIN6                                       6
#define _WIN7                                       7
#define _WIN8                                       8
#define _WIN9                                       9
#define _WIN_ALL                                    0xFF

#define _WIN0_TRANS                                 (_BIT7 | 0)
#define _WIN1_TRANS                                 (_BIT7 | 1)
#define _WIN2_TRANS                                 (_BIT7 | 2)
#define _WIN3_TRANS                                 (_BIT7 | 3)
#define _WIN4_TRANS                                 (_BIT7 | 4)
#define _WIN5_TRANS                                 (_BIT7 | 5)
#define _WIN6_TRANS                                 (_BIT7 | 6)
#define _WIN7_TRANS                                 (_BIT7 | 7)

#define COLOR(fg, bg)                               ((fg) << 4 | (bg))
#define COLOR0(x)                                   (x)
#define COLOR1(x)                                   (x)
#define COLOR2(x)                                   (x)
#define COLOR3(x)                                   (x)

#define X_START(x)                                  (x)
#define Y_START(x)                                  (x)
#define X_END(x)                                    (x)
#define Y_END(x)                                    (x)

#define _BORDER0_1_PIXEL                            0
#define _BORDER0_2_PIXEL                            1
#define _BORDER0_3_PIXEL                            2
#define _BORDER0_4_PIXEL                            3
#define _BORDER0_5_PIXEL                            4
#define _BORDER0_6_PIXEL                            5
#define _BORDER0_7_PIXEL                            6
#define _BORDER0_8_PIXEL                            7

#define _BORDER1_1_PIXEL                            0x00
#define _BORDER1_2_PIXEL                            0x08
#define _BORDER1_3_PIXEL                            0x10
#define _BORDER1_4_PIXEL                            0x18
#define _BORDER1_5_PIXEL                            0x20
#define _BORDER1_6_PIXEL                            0x28
#define _BORDER1_7_PIXEL                            0x30
#define _BORDER1_8_PIXEL                            0x38

#define _BLEND_DISABLE                              0
#define _BLEND_ENABLE                               0x80
#define _GRADIENT_DISABLE                           0
#define _GRADIENT_ENABLE                            0x40
#define _GRADIENT_DIRECTION_H                       0
#define _GRADIENT_DIRECTION_V                       0x20
#define _BORDER_DISABLE                             0
#define _BORDER_ENABLE                              0x10

#define _1_LEVEL_RER_GRADIENT                       0x20
#define _2_LEVEL_RER_GRADIENT                       0x40
#define _3_LEVEL_RER_GRADIENT                       0x60
#define _4_LEVEL_RER_GRADIENT                       0x80
#define _5_LEVEL_RER_GRADIENT                       0xA0
#define _6_LEVEL_RER_GRADIENT                       0xC0
#define _7_LEVEL_RER_GRADIENT                       0xE0
#define _8_LEVEL_RER_GRADIENT                       0x00

#define _R_GRADIENT_DEC                             0x00
#define _R_GRADIENT_INC                             0x80
#define _G_GRADIENT_DEC                             0x00
#define _G_GRADIENT_INC                             0x40
#define _B_GRADIENT_DEC                             0x00
#define _B_GRADIENT_INC                             0x20

#define _GRADIENT_LEVEL_1                           0
#define _GRADIENT_LEVEL_2                           0x08
#define _GRADIENT_LEVEL_3                           0x10
#define _GRADIENT_LEVEL_4                           0x18

#define _R_GRADIENT_ENABLE                          0x04
#define _R_GRADIENT_DISABLE                         0x00
#define _G_GRADIENT_ENABLE                          0x02
#define _G_GRADIENT_DISABLE                         0x00
#define _B_GRADIENT_ENABLE                          0x01
#define _B_GRADIENT_DISABLE                         0x00

#define _SHADOW_1                                   0x00
#define _SHADOW_2                                   0x02
#define _SHADOW_3                                   0x04
#define _SHADOW_4                                   0x06
#define _3D_BUTTON_1                                0x08
#define _3D_BUTTON_2                                0x0A

#define _WIN0_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN0_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)

#define _WIN0_FUNC_CONTROL                          (_BLEND_ENABLE | _GRADIENT_DISABLE | _GRADIENT_DIRECTION_H | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN0_GRADIENT_CONTROL0                     (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_3 | _R_GRADIENT_INC | _G_GRADIENT_INC | _B_GRADIENT_INC)
#define _WIN0_GRADIENT_CONTROL1                     (_3_LEVEL_RER_GRADIENT)

#define _WIN0_ROTATE_BORDER_PIXEL                   (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN0_ROTATE_BORDER_COLOR                   ((_CP_DARKBLUE << 4) | _CP_DARKBLUE)
#define _WIN0_ROTATE_FUNC_CONTROL                   (_BLEND_ENABLE | _GRADIENT_ENABLE | _GRADIENT_DIRECTION_V | _BORDER_ENABLE | _SHADOW_3)
#define _WIN0_ROTATE_GRADIENT_CONTROL0              (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_4 | _R_GRADIENT_DEC | _G_GRADIENT_DEC | _B_GRADIENT_DEC)
#define _WIN0_ROTATE_GRADIENT_CONTROL1              (_3_LEVEL_RER_GRADIENT)

#define _WIN1_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN1_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)

#define _WIN1_FUNC_CONTROL                          (_BLEND_ENABLE | _GRADIENT_DISABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN1_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN1_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN2_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN2_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN2_FUNC_CONTROL                          (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN2_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN2_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN3_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN3_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN3_FUNC_CONTROL                          (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN3_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN3_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN7_BORDER_PIXEL                          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN7_BORDER_COLOR                          ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN7_FUNC_CONTROL                          (_BLEND_ENABLE)
#define _WIN7_GRADIENT_CONTROL0                     (_DISABLE)
#define _WIN7_GRADIENT_CONTROL1                     (_DISABLE)

#define _WIN0_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN0_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN0_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN0_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN0_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN1_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN1_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN1_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN1_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN1_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN2_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN2_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN2_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN2_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN2_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN3_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN3_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN3_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN3_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN3_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN4_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN4_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN4_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN4_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN4_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN5_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN5_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN5_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN5_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN5_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN6_TRANS_BORDER_PIXEL                    (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _WIN6_TRANS_BORDER_COLOR                    ((_CP_WHITE << 4) | _CP_WHITE)
#define _WIN6_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE | _BORDER_ENABLE | _3D_BUTTON_1)
#define _WIN6_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN6_TRANS_GRADIENT_CONTROL1               (_DISABLE)

#define _WIN7_TRANS_BORDER_PIXEL                    (_BORDER0_3_PIXEL | _BORDER1_3_PIXEL)
#define _WIN7_TRANS_BORDER_COLOR                    (_CP_YELLOW << 4)
#define _WIN7_TRANS_FUNC_CONTROL                    (_BLEND_ENABLE)
#define _WIN7_TRANS_GRADIENT_CONTROL0               (_DISABLE)
#define _WIN7_TRANS_GRADIENT_CONTROL1               (_DISABLE)



#define _OSD_UNSELECT                               0
#define _OSD_SELECT                                 1
#define _OSD_REJECT                                 2
#define _OSD_ADJUST                                 3
#define _OSD_UNHIGHLIGHT                            4
#define _OSD_HIGHLIGHT                              5
#define _OSD_PRE_SELECT                             6
#define _OSD_SELECT_ADJUST                          7


#define _KEY_INFO_ENTER                             0
#define _KEY_INFO_RIGHT                             1
#define _KEY_INFO_LEFT                              2
#define _KEY_INFO_EXIT                              3
#define _KEY_INFO_BACK                              4
#define _KEY_INFO_ALL                               5   // exit, left, right, enter

//=========== OSD Font Icon Address ======================//
#define _1GLOBAL_START                              0x00                        // Global 49
#define _1DYNAMIC_START                             (_1GLOBAL_START + 50)       // Dynamic 0
#define _1DYNAMIC_ICON_START                        (_1DYNAMIC_START + 0)       // main menu icon (6 x 4 x 8) = 196
#define _2DYNAMIC_START                             0x00
#define _2BIT_ICON_OFFSET                           0xFF

#define _LOGO_START_ADDRESS                         0x00

//=============== 1Bit Icon ========================

enum OneBitGLOBAL
{
    ___ = 0,
    _iREALTEK_00,
    _iREALTEK_01,
    _iREALTEK_02,
    _iREALTEK_03,
    _iREALTEK_04,
    _iREALTEK_05,
    _iREALTEK_06,
    _iREALTEK_07,
    _iREALTEK_08,
    _iREALTEK_09,
    _iREALTEK_0A,
    _iREALTEK_0B,
    _iREALTEK_10,
    _iREALTEK_11,
    _iREALTEK_12,
    _iREALTEK_13,
    _iREALTEK_14,
    _iREALTEK_15,
    _iREALTEK_16,
    _iREALTEK_17,
    _iREALTEK_18,
    _iREALTEK_19,
    _iREALTEK_1A,
    _iREALTEK_1B,
    _iLEFT_00,
    _iLEFT_01,
    _iRIGHT_00,
    _iRIGHT_01,
    _iKEY_BACK_00,
    _iKEY_BACK_01,
    _iKEY_BACK_10,
    _iKEY_BACK_11,
    _iKEY_LEFT_00,
    _iKEY_LEFT_01,
    _iKEY_LEFT_10,
    _iKEY_LEFT_11,
    _iKEY_RIGHT_00,
    _iKEY_RIGHT_01,
    _iKEY_RIGHT_10,
    _iKEY_RIGHT_11,
    _iKEY_ENTER_00,
    _iKEY_ENTER_01,
    _iKEY_ENTER_10,
    _iKEY_ENTER_11,
    _iKEY_EXIT_00,
    _iKEY_EXIT_01,
    _iKEY_EXIT_10,
    _iKEY_EXIT_11,
    _iINDICATE,


};

//RTD LOGO
#define _LOGO_WINDOW_SIZE_X                         839
#define _LOGO_WINDOW_SIZE_Y                         179

#define _Logo_0x00                                  0x00
#define _Logo_0x01                                  (_Logo_0x00 + 0x01)
#define _Logo_0x02                                  (_Logo_0x00 + 0x02)
#define _Logo_0x03                                  (_Logo_0x00 + 0x03)
#define _Logo_0x04                                  (_Logo_0x00 + 0x04)
#define _Logo_0x05                                  (_Logo_0x00 + 0x05)
#define _Logo_0x06                                  (_Logo_0x00 + 0x06)
#define _Logo_0x07                                  (_Logo_0x00 + 0x07)
#define _Logo_0x08                                  (_Logo_0x00 + 0x08)
#define _Logo_0x09                                  (_Logo_0x00 + 0x09)
#define _Logo_0x0a                                  (_Logo_0x00 + 0x0a)
#define _Logo_0x0b                                  (_Logo_0x00 + 0x0b)
#define _Logo_0x0c                                  (_Logo_0x00 + 0x0c)
#define _Logo_0x0d                                  (_Logo_0x00 + 0x0d)
#define _Logo_0x0e                                  (_Logo_0x00 + 0x0e)
#define _Logo_0x0f                                  (_Logo_0x00 + 0x0f)
#define _Logo_0x10                                  (_Logo_0x00 + 0x10)
#define _Logo_0x11                                  (_Logo_0x00 + 0x11)
#define _Logo_0x12                                  (_Logo_0x00 + 0x12)
#define _Logo_0x13                                  (_Logo_0x00 + 0x13)
#define _Logo_0x14                                  (_Logo_0x00 + 0x14)
#define _Logo_0x15                                  (_Logo_0x00 + 0x15)
#define _Logo_0x16                                  (_Logo_0x00 + 0x16)
#define _Logo_0x17                                  (_Logo_0x00 + 0x17)
#define _Logo_0x18                                  (_Logo_0x00 + 0x18)
#define _Logo_0x19                                  (_Logo_0x00 + 0x19)
#define _Logo_0x1a                                  (_Logo_0x00 + 0x1a)
#define _Logo_0x1b                                  (_Logo_0x00 + 0x1b)
#define _Logo_0x1c                                  (_Logo_0x00 + 0x1c)
#define _Logo_0x1d                                  (_Logo_0x00 + 0x1d)
#define _Logo_0x1e                                  (_Logo_0x00 + 0x1e)
#define _Logo_0x1f                                  (_Logo_0x00 + 0x1f)
#define _Logo_0x20                                  (_Logo_0x00 + 0x20)
#define _Logo_0x21                                  (_Logo_0x00 + 0x21)
#define _Logo_0x22                                  (_Logo_0x00 + 0x22)
#define _Logo_0x23                                  (_Logo_0x00 + 0x23)
#define _Logo_0x24                                  (_Logo_0x00 + 0x24)
#define _Logo_0x25                                  (_Logo_0x00 + 0x25)
#define _Logo_0x26                                  (_Logo_0x00 + 0x26)
#define _Logo_0x27                                  (_Logo_0x00 + 0x27)
#define _Logo_0x28                                  (_Logo_0x00 + 0x28)
#define _Logo_0x29                                  (_Logo_0x00 + 0x29)
#define _Logo_0x2a                                  (_Logo_0x00 + 0x2a)
#define _Logo_0x2b                                  (_Logo_0x00 + 0x2b)
#define _Logo_0x2c                                  (_Logo_0x00 + 0x2c)
#define _Logo_0x2d                                  (_Logo_0x00 + 0x2d)
#define _Logo_0x2e                                  (_Logo_0x00 + 0x2e)
#define _Logo_0x2f                                  (_Logo_0x00 + 0x2f)
#define _Logo_0x30                                  (_Logo_0x00 + 0x30)
#define _Logo_0x31                                  (_Logo_0x00 + 0x31)
#define _Logo_0x32                                  (_Logo_0x00 + 0x32)
#define _Logo_0x33                                  (_Logo_0x00 + 0x33)
#define _Logo_0x34                                  (_Logo_0x00 + 0x34)
#define _Logo_0x35                                  (_Logo_0x00 + 0x35)
#define _Logo_0x36                                  (_Logo_0x00 + 0x36)
#define _Logo_0x37                                  (_Logo_0x00 + 0x37)
#define _Logo_0x38                                  (_Logo_0x00 + 0x38)
#define _Logo_0x39                                  (_Logo_0x00 + 0x39)
#define _Logo_0x3a                                  (_Logo_0x00 + 0x3a)
#define _Logo_0x3b                                  (_Logo_0x00 + 0x3b)
#define _Logo_0x3c                                  (_Logo_0x00 + 0x3c)
#define _Logo_0x3d                                  (_Logo_0x00 + 0x3d)
#define _Logo_0x3e                                  (_Logo_0x00 + 0x3e)
#define _Logo_0x3f                                  (_Logo_0x00 + 0x3f)
#define _Logo_0x40                                  (_Logo_0x00 + 0x40)
#define _Logo_0x41                                  (_Logo_0x00 + 0x41)
#define _Logo_0x42                                  (_Logo_0x00 + 0x42)
#define _Logo_0x43                                  (_Logo_0x00 + 0x43)
#define _Logo_0x44                                  (_Logo_0x00 + 0x44)
#define _Logo_0x45                                  (_Logo_0x00 + 0x45)
#define _Logo_0x46                                  (_Logo_0x00 + 0x46)
#define _Logo_0x47                                  (_Logo_0x00 + 0x47)
#define _Logo_0x48                                  (_Logo_0x00 + 0x48)
#define _Logo_0x49                                  (_Logo_0x00 + 0x49)
#define _Logo_0x4a                                  (_Logo_0x00 + 0x4a)
#define _Logo_0x4b                                  (_Logo_0x00 + 0x4b)
#define _Logo_0x4c                                  (_Logo_0x00 + 0x4c)
#define _Logo_0x4d                                  (_Logo_0x00 + 0x4d)
#define _Logo_0x4e                                  (_Logo_0x00 + 0x4e)
#define _Logo_0x4f                                  (_Logo_0x00 + 0x4f)
#define _Logo_0x50_End                              (_Logo_0x00 + 0x50)

#define _Logo1_0x00                                 (_Logo_0x50_End + 0x00)
#define _Logo1_0x01                                 (_Logo1_0x00 + 0x01)
#define _Logo1_0x02                                 (_Logo1_0x00 + 0x02)
#define _Logo1_0x03                                 (_Logo1_0x00 + 0x03)
#define _Logo1_0x04                                 (_Logo1_0x00 + 0x04)
#define _Logo1_0x05                                 (_Logo1_0x00 + 0x05)
#define _Logo1_0x06                                 (_Logo1_0x00 + 0x06)
#define _Logo1_0x07                                 (_Logo1_0x00 + 0x07)
#define _Logo1_0x08                                 (_Logo1_0x00 + 0x08)
#define _Logo1_0x09                                 (_Logo1_0x00 + 0x09)
#define _Logo1_0x0a                                 (_Logo1_0x00 + 0x0a)
#define _Logo1_0x0b                                 (_Logo1_0x00 + 0x0b)
#define _Logo1_0x0c                                 (_Logo1_0x00 + 0x0c)
#define _Logo1_0x0d                                 (_Logo1_0x00 + 0x0d)
#define _Logo1_0x0e                                 (_Logo1_0x00 + 0x0e)
#define _Logo1_0x0f                                 (_Logo1_0x00 + 0x0f)
#define _Logo1_0x10                                 (_Logo1_0x00 + 0x10)
#define _Logo1_0x11                                 (_Logo1_0x00 + 0x11)
#define _Logo1_0x12                                 (_Logo1_0x00 + 0x12)
#define _Logo1_0x13                                 (_Logo1_0x00 + 0x13)
#define _Logo1_0x14                                 (_Logo1_0x00 + 0x14)
#define _Logo1_0x15                                 (_Logo1_0x00 + 0x15)
#define _Logo1_0x16                                 (_Logo1_0x00 + 0x16)
#define _Logo1_0x17                                 (_Logo1_0x00 + 0x17)
#define _Logo1_0x18                                 (_Logo1_0x00 + 0x18)
#define _Logo1_0x19                                 (_Logo1_0x00 + 0x19)
#define _Logo1_0x1a                                 (_Logo1_0x00 + 0x1a)
#define _Logo1_0x1b                                 (_Logo1_0x00 + 0x1b)
#define _Logo1_0x1c                                 (_Logo1_0x00 + 0x1c)
#define _Logo1_0x1d                                 (_Logo1_0x00 + 0x1d)
#define _Logo1_0x1e                                 (_Logo1_0x00 + 0x1e)
#define _Logo1_0x1f                                 (_Logo1_0x00 + 0x1f)
#define _Logo1_0x20                                 (_Logo1_0x00 + 0x20)
#define _Logo1_0x21                                 (_Logo1_0x00 + 0x21)
#define _Logo1_0x22                                 (_Logo1_0x00 + 0x22)
#define _Logo1_0x23                                 (_Logo1_0x00 + 0x23)
#define _Logo1_0x24                                 (_Logo1_0x00 + 0x24)
#define _Logo1_0x25                                 (_Logo1_0x00 + 0x25)
#define _Logo1_0x26                                 (_Logo1_0x00 + 0x26)
#define _Logo1_0x27                                 (_Logo1_0x00 + 0x27)
#define _Logo1_0x28                                 (_Logo1_0x00 + 0x28)
#define _Logo1_0x29                                 (_Logo1_0x00 + 0x29)
#define _Logo1_0x2a                                 (_Logo1_0x00 + 0x2a)
#define _Logo1_0x2b                                 (_Logo1_0x00 + 0x2b)
#define _Logo1_0x2c                                 (_Logo1_0x00 + 0x2c)
#define _Logo1_0x2d                                 (_Logo1_0x00 + 0x2d)
#define _Logo1_0x2e                                 (_Logo1_0x00 + 0x2e)
#define _Logo1_0x2f                                 (_Logo1_0x00 + 0x2f)
#define _Logo1_0x30                                 (_Logo1_0x00 + 0x30)
#define _Logo1_0x31                                 (_Logo1_0x00 + 0x31)
#define _Logo1_0x32                                 (_Logo1_0x00 + 0x32)
#define _Logo1_0x33                                 (_Logo1_0x00 + 0x33)
#define _Logo1_0x34                                 (_Logo1_0x00 + 0x34)
#define _Logo1_0x35                                 (_Logo1_0x00 + 0x35)
#define _Logo1_0x36                                 (_Logo1_0x00 + 0x36)
#define _Logo1_0x37                                 (_Logo1_0x00 + 0x37)
#define _Logo1_0x38                                 (_Logo1_0x00 + 0x38)
#define _Logo1_0x39                                 (_Logo1_0x00 + 0x39)
#define _Logo1_0x3a                                 (_Logo1_0x00 + 0x3a)
#define _Logo1_0x3b                                 (_Logo1_0x00 + 0x3b)
#define _Logo1_0x3c                                 (_Logo1_0x00 + 0x3c)
#define _Logo1_0x3d                                 (_Logo1_0x00 + 0x3d)
#define _Logo1_0x3e                                 (_Logo1_0x00 + 0x3e)
#define _Logo1_0x3f                                 (_Logo1_0x00 + 0x3f)
#define _Logo1_0x40                                 (_Logo1_0x00 + 0x40)
#define _Logo1_0x41                                 (_Logo1_0x00 + 0x41)
#define _Logo1_0x42                                 (_Logo1_0x00 + 0x42)
#define _Logo1_0x43                                 (_Logo1_0x00 + 0x43)
#define _Logo1_0x44                                 (_Logo1_0x00 + 0x44)
#define _Logo1_0x45                                 (_Logo1_0x00 + 0x45)
#define _Logo1_0x46                                 (_Logo1_0x00 + 0x46)

//=============== 2Bit Icon ========================



//---------------------------------------------------------------------
// Definitions of OSD Show Number Function Used by OsdDisplayShowNumber()
//---------------------------------------------------------------------
#define _ALIGN_LEFT                                 (0)
#define _ALIGN_RIGHT                                (1)

#define _FORCE_SHOW_NUMBER_OFF                      (0 << 1)
#define _FORCE_SHOW_NUMBER_ON                       (1 << 1)

#define _SHOW_1                                     (0 << 4)
#define _SHOW_2                                     (1 << 4)
#define _SHOW_3                                     (2 << 4)
#define _SHOW_4                                     (3 << 4)
#define _SHOW_5                                     (4 << 4)
#define _SHOW_6                                     (5 << 4)

//------------------------------------------------------
// Definitions of OSD Slider Function Used by OsdDisplaySlider()
//------------------------------------------------------
#define _SLIDER_RESOLUTION                          (10)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#define _PALETTE_INDEX0                             0   // 0 ~ 15
#define _PALETTE_INDEX1                             1   // 16 ~ 31
#define _PALETTE_INDEX2                             2   // 32 ~ 47
#define _PALETTE_INDEX3                             3   // 48 ~ 63

// OSD Position
#define _POS_DIRECT                                 0
#define _POS_PERCENT                                1


//---------------------------------------------------------
// OSD Rotate Type
//---------------------------------------------------------
#define _OSD_ROTATE_OFF                             0
#define _OSD_ROTATE_SOFTWARE                        1
#define _OSD_ROTATE_HARDWARE                        2

#define _OSD_ROTATE_FUNCTION                        _OSD_ROTATE_HARDWARE

//--------------------------------------------------
// Definations of OSD MAIN MENU
//--------------------------------------------------
#define _OSD_MAIN_MENU_WIDTH                        44
#define _OSD_MAIN_MENU_HEIGHT                       22

//--------------------------------------------------
// Definations of OSD Type
//--------------------------------------------------

#define _OSD_MESSAGE_ROW_START                      2
#define _OSD_MESSAGE_CENTER_COL_START               12
#define _OSD_MESSAGE_CENTER_COL_END                 23

//--------------------------------------------------
// Definations of HL window Border Size
//--------------------------------------------------
#define _HL_WIN_BORDER_SIZE                         2

//--------------------------------------------------
// Definations of Slider
//--------------------------------------------------
#define _SLIDER_LENGHT                              250
#define _SLIDER_HIGH                                20
#define _SLIDER_BORDER_PIXEL                        2
#define _SLIDER_OFFSET                              6

#define _SLIDER_SELECT_BORDER_COLOR                 _CP_GRAY
#define _SLIDER_SELECT_BG_COLOR                     _CP_WHITE

#define _SLIDER_UNSELECT_BORDER_COLOR               _CP_WHITE
#define _SLIDER_UNSELECT_BG_COLOR                   _CP_GRAY

#define _SLIDER_SELECT_COLOR                        _CP_ORANGE
#define _SLIDER_UNSELECT_COLOR                      _CP_BLUE

#define _SLIDER_0                                   0
#define _SLIDER_1                                   1
#define _SLIDER_2                                   2

#define _SELECT                                     1
#define _UNSELECT                                   0

#define _SLIDER_0_BAR_WINDOW                        _OSD_WINDOW_4_5
#define _SLIDER_0_BG_WINDOW                         _OSD_WINDOW_4_4
#define _SLIDER_0_BORDER_WINDOW                     _OSD_WINDOW_4_3

#define _SLIDER_1_BAR_WINDOW                        _OSD_WINDOW_4_8
#define _SLIDER_1_BG_WINDOW                         _OSD_WINDOW_4_7
#define _SLIDER_1_BORDER_WINDOW                     _OSD_WINDOW_4_6

#define _SLIDER_0_ROW                               16
#define _SLIDER_0_COL                               11

#define _ITEM_0                                     0
#define _ITEM_1                                     1
#define _ITEM_2                                     2
#define _ITEM_3                                     3
#define _ITEM_4                                     4
#define _ITEM_5                                     5
#define _ITEM_6                                     6
#define _ITEM_7                                     7

#define _NONE_ITEM                                  8

#define _FONTFROM_0_255                             0x00
#define _FONTFROM_256_512                           _BIT5
//--------------------------------------------------
// Definations of Color effect user mode Hue & Saturation
//--------------------------------------------------
#define _COLOR_HUE                                  0
#define _COLOR_SATURATION                           1


//--------------------------------------------------
// Define enter panel uniformity msg adjust from pcm or gamma
//--------------------------------------------------
typedef enum
{
    _FROM_STATE_PCM,
    _FROM_STATE_GAMMA,
    _FROM_STATE_AMOUNT,
    _FROM_STATE_HDR,
}EnumFromWhichState;


//--------------------------------------------------
// Define PCM Soft Proft
//--------------------------------------------------
typedef enum
{
    _PCM_SOFT_MODE_1,
    _PCM_SOFT_MODE_2,
    _PCM_SOFT_MODE_AMOUNT = _PCM_SOFT_MODE_2,
} EnumPCMSoftProftMode;

/*
//--------------------------------------------------
// Define OSD Gamma
//--------------------------------------------------
typedef enum
{
    _OSD_GAMMA_OFF,
    _OSD_GAMMA_18,
    _OSD_GAMMA_20,
    _OSD_GAMMA_22,
    _OSD_GAMMA_24,
    _OSD_GAMMA_AMOUNT = _OSD_GAMMA_24,
} EnumOsdGammaType;

//--------------------------------------------------
// Define Gamma
//--------------------------------------------------
typedef enum
{
    _GAMMA_OFF,
    _GAMMA_18,
    _GAMMA_20,
    _GAMMA_22,
    _GAMMA_24,
    _GAMMA_AMOUNT = _GAMMA_24,
} EnumGammaType;
*/
//--------------------------------------------------
// Define HL Window Type
//--------------------------------------------------
typedef enum
{
    _HL_WIN_OFF,
    _HL_WIN_1,
    _HL_WIN_2,
    _HL_WIN_3,
    _HL_WIN_4,
    _HL_WIN_5,
    _HL_WIN_AMOUNT = _HL_WIN_5,
} EnumHLWinType;

//--------------------------------------------------
// Define Color Effect
//--------------------------------------------------
typedef enum
{
    _OSD_COLOREFFECT_STANDARD,
    _OSD_COLOREFFECT_GAME,
    _OSD_COLOREFFECT_MOVIE,
    _OSD_COLOREFFECT_PHOTO,
    _OSD_COLOREFFECT_VIVID,
    _OSD_COLOREFFECT_USER,
    _OSD_COLOREFFECT_AMOUNT = _OSD_COLOREFFECT_USER,
} EnumOsdColorEffectType;

//--------------------------------------------------
// Define Color Effect
//--------------------------------------------------
typedef enum
{
    _COLOREFFECT_STANDARD,
    _COLOREFFECT_GAME,
    _COLOREFFECT_MOVIE,
    _COLOREFFECT_PHOTO,
    _COLOREFFECT_VIVID,
    _COLOREFFECT_USER,
    _COLOREFFECT_AMOUNT = _COLOREFFECT_STANDARD,
} EnumColorEffectType;

//--------------------------------------------------
// Define Color Effect Six Color
//--------------------------------------------------
typedef enum
{
    _SIXCOLOR_R,
    _SIXCOLOR_Y,
    _SIXCOLOR_G,
    _SIXCOLOR_C,
    _SIXCOLOR_B,
    _SIXCOLOR_M,
    _SIXCOLOR_AMOUNT = _SIXCOLOR_M,
} EnumSixColorType;

//--------------------------------------------------
// Define Ultra Vivid
//--------------------------------------------------
typedef enum
{
    _OSD_ULTRA_VIVID_OFF,
    _OSD_ULTRA_VIVID_L,
    _OSD_ULTRA_VIVID_M,
    _OSD_ULTRA_VIVID_H,
    _OSD_ULTRA_VIVID_AMOUNT = _OSD_ULTRA_VIVID_H,
} EnumOsdUltraVividType;

//--------------------------------------------------
// Define Ultra Vivid
//--------------------------------------------------
typedef enum
{
    _ULTRA_VIVID_L,
    _ULTRA_VIVID_M,
    _ULTRA_VIVID_H,
    _ULTRA_VIVID_OFF,
    _ULTRA_VIVID_AMOUNT = _ULTRA_VIVID_OFF,
} EnumUltraVividType;

//--------------------------------------------------
// Define Supported Aspect Ratios
//--------------------------------------------------
typedef enum
{
#if(_CUSTOMER == _CUS_TOSHIBA)

#if(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_TOSHIBA_1)
    _OSD_ASPECT_RATIO_1,
    _OSD_ASPECT_RATIO_2,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_2,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_TOSHIBA_2)
    _OSD_ASPECT_RATIO_1,
    _OSD_ASPECT_RATIO_2,
    _OSD_ASPECT_RATIO_3,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_3,
#else
    _OSD_ASPECT_RATIO_1,
    _OSD_ASPECT_RATIO_2,
    _OSD_ASPECT_RATIO_3,
    _OSD_ASPECT_RATIO_4,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_4,
#endif

#else

#if(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_1)
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_MAXIMAGE,
    _OSD_ASPECT_RATIO_HMAXIMAGE,
    _OSD_ASPECT_RATIO_VMAXIMAGE,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_VMAXIMAGE,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_2)
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_1280x960,
    _OSD_ASPECT_RATIO_1024x768,
    _OSD_ASPECT_RATIO_800x600,
    _OSD_ASPECT_RATIO_640x480,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_USER,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_3)
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_17Inch_Full,
    _OSD_ASPECT_RATIO_17Inch_4x3,
    _OSD_ASPECT_RATIO_17Inch_5x4,
    _OSD_ASPECT_RATIO_1024x768,
    _OSD_ASPECT_RATIO_800x600,
    _OSD_ASPECT_RATIO_640x480,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_USER,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_4)
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_1280x960,
    _OSD_ASPECT_RATIO_1440x1050,
    _OSD_ASPECT_RATIO_1280x1024,
    _OSD_ASPECT_RATIO_800x600,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_USER,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_5)
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_870x625,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_USER,
#elif(_ASPECT_RATIO_LIST_SELECT == _ASPECT_RATIO_LIST_6)
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_VMAXIMAGE,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_VMAXIMAGE,
#else
    _OSD_ASPECT_RATIO_FULL,
    _OSD_ASPECT_RATIO_ORIGIN,
    _OSD_ASPECT_RATIO_1024x768,
    _OSD_ASPECT_RATIO_800x600,
    _OSD_ASPECT_RATIO_640x480,
    _OSD_ASPECT_RATIO_USER,
    _OSD_ASPECT_RATIO_AMOUNT = _OSD_ASPECT_RATIO_USER,
#endif

#endif
} EnumAspectRatioTypeIndex;
//--------------------------------------------------
// Define DP Port Version
//--------------------------------------------------
typedef enum
{
    _DP_VER_1_DOT_1 = 0,
    _DP_VER_1_DOT_2,
    _DP_VER_1_DOT_3,
    _DP_VER_AMOUNT = _DP_VER_1_DOT_3,
}EnumOSDDpPortVersionDef;

typedef enum
{
    _MST_OFF = 0,
    _MST_D0,
    _MST_D1,
    _MST_D6,
    _MST_AMOUNT = _MST_D6,
}EnumOSDDpMstTypeDef;

//--------------------------------------------------
// Define Display Image Rotate
//--------------------------------------------------
typedef enum
{
    _DISP_ROTATE_0 = 0,
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
    _DISP_ROTATE_90,
#endif
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
    _DISP_ROTATE_180,
#endif
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
    _DISP_ROTATE_270,
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_HOR_MIRROR,
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
    _DISP_ROTATE_VER_MIRROR,
#endif

    _DISP_ROTATE_AMOUNT,

}EnumOSDDispRotateDegree;


typedef enum
{
    _OSD_ROTATE_DISPLAY_FULL = 0,
    _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL,
    _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO,
}EnumOsdRotationDisplaySizeDef;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _VGA_A0 = 0x01,
} EnumOsdSourceTypeVga;

typedef enum
{
    _DVI = 0x02,
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    _DVI_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
    _DVI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
    _DVI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
    _DVI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
    _DVI_D4,
#endif
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
    _DVI_D5,
#endif

    _HDMI = 0x10,
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
    _HDMI_D0,
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
    _HDMI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    _HDMI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    _HDMI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    _HDMI_D4,
#endif
#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    _HDMI_D5,
#endif
}EnumOsdSourceTypeTMDS;

typedef enum
{
    _DP = 0x0E,
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    _DP_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    _DP_D1,
#endif
#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    _DP_D2,
#endif
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    _DP_D6,
#endif
} EnumOsdSourceTypeDP;


//--------------------------------------------------
// Definitions of 3D Effect
//--------------------------------------------------
typedef enum
{
    _3D_EFFECT_OFF = _OFF,
    _3D_EFFECT_WEAK,
    _3D_EFFECT_MEDIUM,
    _3D_EFFECT_STRONG,
    _3D_EFFECT_AMOUNT = _3D_EFFECT_STRONG,
} EnumOSDSelect3DEffectDef;

//--------------------------------------------------
// Definitions of PCMType
//--------------------------------------------------
typedef enum
{
#if(_OCC_SUPPORT == _ON)
    _PCM_OSD_SRGB,
    _PCM_OSD_ADOBE_RGB,
#endif

    _PCM_OSD_USER,
    _PCM_OSD_NATIVE,
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
    _PCM_OSD_SOFT_PROFT,
    _PCM_OSD_AMOUNT = _PCM_OSD_SOFT_PROFT,
#else
    _PCM_OSD_AMOUNT = _PCM_OSD_NATIVE,
#endif
} EnumPCMTypeIndex;

//--------------------------------------------------
// MACRO for Osd Status
//--------------------------------------------------
#define GET_OSD_STATE()                             (g_stOsdInfo.ucOsdState)
#define SET_OSD_STATE(x)                            (g_stOsdInfo.ucOsdState = (x))

#define GET_BACKUP_OSD_VALUE()                      (g_stOsdInfo.ucBackupOsdValue)
#define SET_BACKUP_OSD_VALUE(x)                     (g_stOsdInfo.ucBackupOsdValue = (x))
//--------------------------------------------------
// MACRO for Osd Evevt Message
//--------------------------------------------------
#define GET_OSD_EVENT_MESSAGE()                     (g_stOsdInfo.ucOsdEventMsg)
#define SET_OSD_EVENT_MESSAGE(x)                    (g_stOsdInfo.ucOsdEventMsg = (x))

/*
typedef struct
{
    BYTE b1OsdLogo : 1;
    BYTE b1OsdWakeUpSwitchDdcciPort : 1;
    BYTE b1OsdWakeUpShowSource : 1;
    BYTE b1OsdFactoryModeStatus : 1;
    BYTE b1OsdDoAspectRatio : 1;
    BYTE b3OsdColorFormat : 3;
    BYTE b3OsdsixColor : 3;

    BYTE ucOsdStatePrevious;
    BYTE ucOsdState;
    BYTE ucBackupOsdValue;
    BYTE ucOsdEventMsg;
    BYTE ucOsdKeyMessage;
    BYTE ucOsdKeyControl;
    BYTE b3OsdsixColorHue : 3;
    BYTE b3OsdsixColorSaturation : 3;
    BYTE ucOsd3DEffectRealValue;
    BYTE ucOsdColorEffectOsdItem;
    BYTE ucOsdGammaOsdItem;
    BYTE ucOsd3DGammaOsdItem;
    BYTE ucOsdUltraVividOsdItem;
    BYTE ucOsdColorTempOsdItem;
} StructOsdInfo;
*/
typedef struct
{
    BYTE b1OsdLogo : 1;
    BYTE b1OsdWakeUpSwitchDdcciPort : 1;
    BYTE b1OsdWakeUpShowSource : 1;
    BYTE b1OsdFactoryModeStatus : 1;
    BYTE b1OsdDoAspectRatio : 1;
    BYTE b3OsdColorFormat : 3;
    BYTE b3OsdsixColor : 3;
    BYTE b1OsdDoubleSizeStatus : 1;
    BYTE b1FreezeStatus : 1;
#if((_URGENT_EVENT_CHECK_MODE == _OFF) && (_FREEZE_SUPPORT == _ON))
    BYTE b1FreezeDisableOsdStatus : 1;
#endif
#if(_DP_DEBUG_MSG == _ON)
    BYTE b1OsdWakeUpShowDpINFO : 1;
    BYTE b4OsdWakeUpShowDpINFOPort : 4;
#endif
    BYTE ucOsdStatePrevious;
    WORD ucOsdState;//By Jerry -2016-10-04//
    WORD ucBackupOsdValue;
    BYTE ucOsdEventMsg;
    BYTE ucOsdKeyMessage;
    BYTE ucOsdKeyControl;
    BYTE b3OsdsixColorHue;
    BYTE b3OsdsixColorSaturation;
    BYTE ucOsd3DEffectRealValue;

#if(_FREESYNC_SUPPORT == _ON)
    BYTE ucOsdFREESYNCInforOsdAddress;
#endif
    BYTE ucOsdItemIndex;
    BYTE ucOsdKeyBackupMessage;//for holding on key until it is up
#if(_USER_AC_ON_DELAY_SHOW_NO_SIGNAL == _ON)
    BYTE ucOsdDelayShowNoSignalFlag : 1;
#endif
#if(_USER_ADC_ADJUST_BY_RESISTOR == _ON)
    BYTE ucOsdAdcControlOnce : 1;
#endif

} StructOsdInfo;


//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
#define _6500K_9300K                                0
#define _6700K_9300K                                1
#define _13000K_9300K                               2
#define _11000K_9300K                               3
#define _9300K_13000K                               4
#define _9300K_6500K                                5
#define _14000K_11000K_9300K                        6
#define _Cool_Warm_Normal                           7
#define _7500K_13000K_ULTRASOUND                    8
#define _7500K_13000K                               9

enum OSDColortemptureDef
{
#if(_COLOR_TEMP_SELECT_TYPE == _6500K_9300K)
    _BEACON_6500,
    _BEACON_9300,   
#elif(_COLOR_TEMP_SELECT_TYPE == _6700K_9300K)
    _BEACON_6700,
    _BEACON_9300, 
#elif(_COLOR_TEMP_SELECT_TYPE == _13000K_9300K)
    _BEACON_13000,
    _BEACON_9300, 
#elif(_COLOR_TEMP_SELECT_TYPE == _11000K_9300K)
    _BEACON_11000,
    _BEACON_9300,  
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_13000K)
    _BEACON_9300,  
    _BEACON_13000,
#elif(_COLOR_TEMP_SELECT_TYPE == _9300K_6500K)
    _BEACON_9300,
    _BEACON_6500,
#elif(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
    _BEACON_14000,
    _BEACON_11000,
    _BEACON_9300,
#elif(_COLOR_TEMP_SELECT_TYPE == _Cool_Warm_Normal)
    _BEACON_Normal,
    _BEACON_Cool,
    _BEACON_Warm,
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K_ULTRASOUND)
    _BEACON_7500,
    _BEACON_13000,
    _BEACON_ULTRASOUND,
#elif(_COLOR_TEMP_SELECT_TYPE == _7500K_13000K)
    _BEACON_7500,
    _BEACON_13000,
#endif
    _BEACON_USER,
    _CT_9300,
    _CT_7500,        
    _CT_6500,
    _CT_5800,
    _CT_SRGB,
    _CT_USER,
    _CT_OFF,
#if(_COLOR_TEMP_SELECT_TYPE == _14000K_11000K_9300K)
    _CT_COLORTEMP_AMOUNT = _BEACON_9300,
#else
    _CT_COLORTEMP_AMOUNT = _BEACON_USER,
#endif
};
// EnumColortemptureDef;
enum GammaType
{
/*
    _GAMMA_18,
    _GAMMA_20,
    _GAMMA_22,
    _GAMMA_24,*/
    _GAMMA_OFF,
    _GAMMA_0 = _GAMMA_OFF,
    _GAMMA_1,
    _GAMMA_2,
    _GAMMA_3,
    _GAMMA_4,
    _GAMMA_5,
    _GAMMA_6,
    _GAMMA_7,
    _GAMMA_AMOUNT = _GAMMA_NUMBERS,
};

enum OSDColorPaletteDef
{
//Change color refer to tPALETTE_0[]
    _CP_BG = 0,
    _CP_BLACK = 0,
    _CP_WHITE,
    _CP_RED,
    _CP_GREEN,
    _CP_BLUE,
    _CP_YELLOW,
    _CP_GRAY,
    _CP_DARKBLUE,
    _CP_LIGHTBLUE,
    _CP_GRAY_1,
    _CP_PINK,
    _CP_RED_1,
    _CP_GREEN_1,
    _CP_ORANGE_L,
    _CP_ORANGE_H,
    _CP_UNSELECTGRAY,

};


enum OSDColorPaletteLogo
{
    _LOGO_CP_BG = 0,
    _LOGO_CP_BLACK = 0,
    _LOGO_CP_WHITE,
    _LOGO_CP_RED,
    _LOGO_CP_GREEN,
    _LOGO_CP_BLUE,
    _LOGO_CP_YELLOW,
    _LOGO_CP_GRAY,
    _LOGO_CP_DARKBLUE,
    _LOGO_CP_LIGHTBLUE,
    _LOGO_CP_SELECTBOTTOM,
    _LOGO_CP_PINK,
    _LOGO_CP_RED_1,
    _LOGO_CP_GREEN_1,
    _LOGO_CP_ORANGE_L,
    _LOGO_CP_ORANGE_H,
    _LOGO_CP_GRAY_1,
};

#define _PAGE1_AMOUNT                   (_BEACON_OSD_SELECT_END - _BEACON_OSD_NONE - 1)
#define _PAGE2_AMOUNT                   (_BEACON_ADVANCED_OSD_SELECT_COLOR_END - _BEACON_ADVANCED_OSD_SELECT_COLOR - 1)
#define _PAGE3_AMOUNT                   (_BEACON_ADVANCED_OSD_SELECT_IMAGE_END - _BEACON_ADVANCED_OSD_SELECT_IMAGE - 1)
#define _PAGE4_AMOUNT                   (_BEACON_ADVANCED_OSD_SELECT_SETTING_END - _BEACON_ADVANCED_OSD_SELECT_SETTING - 1)


//--------------------------------------------------
// Definitions of Beacon OSD Flow
//--------------------------------------------------
enum OsdBeaconOsdMenuPtr
{
    _BEACON_OSD_NONE = 0,
    _BEACON_OSD_1,//Brightness
    _BEACON_OSD_2,//Contrast
    _BEACON_OSD_3,//Gamma
    _BEACON_OSD_4,//Color temp
    _BEACON_OSD_5,//Language
    _BEACON_OSD_6,//Source
    _BEACON_OSD_7,//Auto adjust
#if(_CUSTOMER != _CUS_TOSHIBA)
    _BEACON_OSD_8,//Default
#endif
    _BEACON_OSD_9,//Exit
    _BEACON_OSD_SELECT_END,
    _BEACON_OSD_ADJUST_END = _BEACON_OSD_SELECT_END + _PAGE1_AMOUNT + 1,
};

enum OsdBeaconOsdAdvancedMenuPtr
{
    _BEACON_ADVANCED_OSD_NONE = _BEACON_OSD_ADJUST_END,

    _BEACON_ADVANCED_OSD_SELECT_COLOR,//21
    _BEACON_ADVANCED_OSD_COLOR_1,//zoom select
    _BEACON_ADVANCED_OSD_COLOR_2,//zoom variety
    _BEACON_ADVANCED_OSD_COLOR_3,//Dbrightness
    _BEACON_ADVANCED_OSD_COLOR_4,//color temp
    _BEACON_ADVANCED_OSD_COLOR_5,//r
    _BEACON_ADVANCED_OSD_COLOR_6,//g
    _BEACON_ADVANCED_OSD_COLOR_7,//b
    _BEACON_ADVANCED_OSD_COLOR_8,//return
    _BEACON_ADVANCED_OSD_SELECT_COLOR_END,
    _BEACON_ADVANCED_OSD_ADJUST_COLOR_END = _BEACON_ADVANCED_OSD_SELECT_COLOR_END + _PAGE2_AMOUNT + 1,

    _BEACON_ADVANCED_OSD_SELECT_IMAGE = _BEACON_ADVANCED_OSD_ADJUST_COLOR_END,//39
    _BEACON_ADVANCED_OSD_IMAGE_1,//auto adjust
    _BEACON_ADVANCED_OSD_IMAGE_2,//hpos
    _BEACON_ADVANCED_OSD_IMAGE_3,//vpos
    _BEACON_ADVANCED_OSD_IMAGE_4,//clock
    _BEACON_ADVANCED_OSD_IMAGE_5,//phase
    _BEACON_ADVANCED_OSD_IMAGE_6,//return
    _BEACON_ADVANCED_OSD_SELECT_IMAGE_END,
    _BEACON_ADVANCED_OSD_ADJUST_IMAGE_END = _BEACON_ADVANCED_OSD_SELECT_IMAGE_END + _PAGE3_AMOUNT + 1,

    _BEACON_ADVANCED_OSD_SELECT_SETTING = _BEACON_ADVANCED_OSD_ADJUST_IMAGE_END,//53
    _BEACON_ADVANCED_OSD_SETTING_1,//osd hpos
    _BEACON_ADVANCED_OSD_SETTING_2,//osd vpos
    _BEACON_ADVANCED_OSD_SETTING_3,//time
    _BEACON_ADVANCED_OSD_SETTING_4,//reset
    _BEACON_ADVANCED_OSD_SETTING_5,//back
    _BEACON_ADVANCED_OSD_SETTING_6,//exit
    _BEACON_ADVANCED_OSD_SELECT_SETTING_END,
    _BEACON_ADVANCED_OSD_ADJUST_SETTING_END = _BEACON_ADVANCED_OSD_SELECT_SETTING_END + _PAGE4_AMOUNT + 1,
};

enum OsdBeaconOsdHotkeyMenuPtr
{
    _BEACON_HOTKEY_OSD_1 = _BEACON_ADVANCED_OSD_ADJUST_SETTING_END+1,//Backlight
    _BEACON_HOTKEY_OSD_2,//Contrast
    _BEACON_HOTKEY_OSD_END,
};

typedef enum
{
    _OSDEVENT_NONE_MSG = 0,
    _OSDEVENT_SHOW_NOSIGNAL_MSG,
    _OSDEVENT_SHOW_NOCABLE_MSG,
    _OSDEVENT_SHOW_NOSUPPORT_MSG,
    _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG,
    _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG,
    _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG,
    _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG,
    _OSDEVENT_DO_AUTO_CONFIG_MSG,
    _OSDEVENT_DO_AUTO_COLOR_MSG,
    _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG,
    _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG,
    _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG,
    _OSDEVENT_SAVE_NVRAM_BRICON_MSG,
    _OSDEVENT_SAVE_NVRAM_OSDSIXCOLORDATA_MSG,
    _OSDEVENT_SAVE_OSD_USER_DATA_MSG,
} EnumOSDEvenMassage;


typedef enum
{
    _OSD_MBR_USER_DISABLE = _OFF,
    _OSD_MBR_USER_ENABLE,
    _OSD_RTK_ADV_MBR_USER_ENABLE,
}EnumOsdMbrUserSelectStatus;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bForcePowSavStatus;

extern StructOsdInfo g_stOsdInfo;
extern WORD g_usBackupValue;

extern WORD g_usFontSelectStart;
extern WORD g_usFontTableStart;
extern BYTE g_ucOsdWidth;
extern BYTE g_ucOsdHeight;
extern BYTE g_ucFontPointer0;
extern BYTE g_ucFontPointer1;
extern BYTE g_ucFontPointer2;

extern BYTE g_ucLogoTimerCounter;

#if(_USER_IIC_OR_UART_FOR_BEACON == _ON)
extern BYTE g_ucUartKeyState;
#endif

extern BYTE g_stSourceList[_INPUT_PORT_VALID];

#if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
extern bit bUpdateSensorTargetValue;
extern WORD wSensorLux;
#endif

//----------------------------------------------------------------------------------------
// Extern Tables from OsdFont.c
//----------------------------------------------------------------------------------------
extern BYTE code tICON_REALTEK_1BIT_LOGO0[];
extern BYTE code tICON_REALTEK_1BIT_LOGO1[];

//----------------------------------------------------------------------------------------
// Extern Tables from OsdTable.c
//----------------------------------------------------------------------------------------
extern BYTE code tOSD_iREALTEK[];
extern BYTE code tOSD_iKEY_BACK[];
extern BYTE code tOSD_iKEY_LEFT[];
extern BYTE code tOSD_iKEY_RIGHT[];
extern BYTE code tOSD_iKEY_ENTER[];
extern BYTE code tOSD_iKEY_EXIT[];

extern BYTE code tiOSD_REALTEK_1BIT_LOGO0[];
extern BYTE code tiOSD_REALTEK_1BIT_LOGO1[];

//****************************************************************************
// FUNCTION EXTERN of BeaconOsd.c
//****************************************************************************
extern void BeaconFuncCloseWindow(BYTE ucIndex);
extern WORD BeaconFuncValueChange(WORD Value,WORD MaxValue,WORD MinValue,bit loop);
extern void BeaconFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD usValue, BYTE ucPar);
extern void BeaconFuncHLine(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucValue, BYTE ucIndicate);
extern void BeaconFuncClearFont(BYTE ucRow, BYTE ucCol,BYTE ucWidth, BYTE ucHeight);
extern void BeaconFuncLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE *pArray);
extern void BeaconFuncCompressLoadText(BYTE ucRow, BYTE ucCol, BYTE ucSelect, BYTE *pArray);
extern void BeaconFuncApplyMapSetting(BYTE ucRow, BYTE ucByte2,BYTE ucByte1,BYTE ucByte0);
extern void BeaconFuncDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd,BYTE *pStyle);
extern void BeaconFuncTableFuncSetColorPalette(BYTE ucPaletteIndex, BYTE ucColorPalette);
extern void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
extern BYTE BeaconFuncJudgeSourceType(void);
extern void BeaconFuncResetOSD(void);
extern void BeaconFuncPrintASCII(BYTE ucRow,BYTE ucCol,BYTE ucLen, BYTE *pArray);
extern void BeaconMainOsdDisplayProc(void);
extern void BeaconAdvancedOsdDisplayProc(void);
extern void BeaconMenuItemSelColor(BYTE item);
extern void BeaconADColorMenuItemSelColor(BYTE item);
extern void BeaconADImageMenuItemSelColor(BYTE item);
extern void BeaconADSettingMenuItemSelColor(BYTE item);

#if(_CUSTOMER != _CUS_TOSHIBA)
extern void BeaconHotkeyBacklightDisplayProc(void);
extern void BeaconHotkeyContrastDisplayProc(void);
#endif
extern void BeaconDisplayNoSignalProc(void);
#if(_VGA_SUPPORT == _ON)
extern void BeaconDisplayAutoAdjustProc(void);
extern void BeaconDisplayAutoProc(BYTE ucAutoByte);
#endif
#if(_USER_ADC_ADJUST_BY_RESISTOR == _ON)
extern void BeaconFuncAdcAdjustScan(void);
#endif
#if(_EN_LOCK_FUCTION == _ON)
extern void BeaconDisplayLockProc(void);
#endif
#if(_CUSTOMER == _CUS_TOSHIBA)
extern void MainMenuItemReset(void);
#endif
//!!There code table only extern use by file BeaconOsd.c
//"code BYTE * "means the table have parameter to adjust.
extern code BYTE *tOSD_BEACON_MAIN_GAMMA[];  //Added by KW
extern code BYTE *tOSD_BEACON_MAIN_COLORTEMP[_CT_COLORTEMP_AMOUNT+1];
extern BYTE code tOSD_BEACON_MAIN_LANGUAGE[];
extern code BYTE *tOSD_BEACON_MAIN_SOURCE[_INPUT_PORT_VALID];

extern BYTE code tOSD_BEACON_MAIN_TITEL_STR[];
extern BYTE code tOSD_BEACON_MAIN_TEXT_STR[];

extern BYTE code tOSD_BEACON_ADVANCED_COLOR_TEXT_STR[];
extern code BYTE *tOSD_BEACON_ADVANCED_ASPECT_SELECT_STR[_ASPECT_RATIO_AMOUNT+1];
extern BYTE code tOSD_BEACON_ADVANCED_IMAGE_TEXT_STR[];
extern BYTE code tOSD_BEACON_ADVANCED_SETTING_TEXT_STR[];



extern BYTE code tOSD_WINDOW_3_ADVANCED_MEMU3[];

extern BYTE code tOSD_WINDOW_1_HOTKEY[];


//============Main None==============//
extern void BeaconOsdNoneMenu(void);
#if(_CUSTOMER != _CUS_TOSHIBA)
extern void BeaconOsdNoneLeft(void);
extern void BeaconOsdNoneRight(void);
extern void BeaconOsdNoneExit(void);
#endif

extern void BeaconMenuItem(void);
extern void BeaconSelectNextItem(void);
extern void BeaconExitItem(void);
extern void BeaconMenuExit(void);
extern void BeaconNoAction(void);

extern void BeaconBacklightAdjust(void);
extern void BeaconContrastAdjust(void);
extern void BeaconGammaAdjust(void);
extern void BeaconColorTempAdjust(void);
extern void BeaconLanguageAdjust(void);
extern void BeaconSourceAdjust(void);
extern void BeaconMenuAutoAdjust(void);

extern void BeaconAdvancedPageMenu(void);
extern void BeaconAdvancedPageSelectNext(void);
extern void BeaconAdvancedPageExit(void);

extern void BeaconAdvancedColorMenuItem(void);
extern void BeaconAdvancedColorSelectNextItem(void);
extern void BeaconAdvancedColorExitItem(void);
extern void BeaconAdvancedColorMenuExit(void);
extern void BeaconADColorAdjustAspectSelect(void);
extern void BeaconADColorAdjustAspectRatio(void);
extern void BeaconADColorAdjustBrightness(void);
extern void BeaconADColorAdjustColorTempType(void);
extern void BeaconADColorAdjustColorTempTypeUserR(void);
extern void BeaconADColorAdjustColorTempTypeUserG(void);
extern void BeaconADColorAdjustColorTempTypeUserB(void);


extern void BeaconAdvancedImageMenuItem(void);
extern void BeaconAdvancedImageSelectNextItem(void);
extern void BeaconAdvancedImageExitItem(void);
extern void BeaconAdvancedImageMenuExit(void);
extern void BeaconADImageAdjustAnologHpos(void);
extern void BeaconADImageAdjustAnologVpos(void);
extern void BeaconADImageAdjustAnologClock(void);
extern void BeaconADImageAdjustAnologPhase(void);


extern void BeaconAdvancedSettingMenuItem(void);
extern void BeaconAdvancedSettingSelectNextItem(void);
extern void BeaconAdvancedSettingExitItem(void);
extern void BeaconAdvancedSettingMenuExit(void);

extern void BeaconADSettingAdjustOSDHpos(void);
extern void BeaconADSettingAdjustOSDVpos(void);
extern void BeaconADSettingAdjustOSDTime(void);

extern void BeaconHotkeyOSDMenu(void);
extern void BeaconHotkeyOSDBacklightAdjust(void);
extern void BeaconHotkeyOSDContrastAdjust(void);


#ifndef __BEACON_OSDLOGO__
extern void BeaconLogoShow(void);
extern void BeaconLogoLoadNoUseTable(void);
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserDdcci.c
//----------------------------------------------------------------------------------------
extern void UserDdcciHandler(void);

//----------------------------------------------------------------------------------------
// Extern functions from RTDKey.c
//----------------------------------------------------------------------------------------
extern void NoneKeyInitial(void);

extern void OsdDispShowLogo(void);
extern void OsdDispShowInformation(void);
extern void OsdDisplaySixColorGetOneColor(BYTE ucColor);
extern BYTE OsdDispJudgeSourceType(void);
extern void OsdDisplaySixColorSetOneColor(BYTE ucColor);
#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)

