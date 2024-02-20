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
// ID Code      : RTDFactoryFunction.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define __FACTORY_FUNCTION__

#include "UserCommonInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _MAIN_PAGE_MODEL_NAME               _M__,_o__,_d__,_e__,_l__,__,_COLON__,__,_R__,_T__,_D__,_2__,_0__,_1__,_1__
#define _PANNEL_NAME                        _P__,_a__,_n__,_e__,_l__,__,_COLON__,__,_A__,_U__,_O__
#define _FW_VERSION                         _F__,_W__,__,_COLON__,__,_V__,_0__,_0__,_1__
#define _RTK_VERSION                        _V__,_0__,_0__,_1__
#define _FACTORY_COLORTEMP_ITEM1            _CT_9300
#define _FACTORY_COLORTEMP_ITEM2            _CT_7500
#define _FACTORY_COLORTEMP_ITEM3            _CT_6500
#define _FACTORY_COLORTEMP_ITEM4            _CT_5800
#define _FACTORY_COLORTEMP_ITEM5            _CT_SRGB
#define _FACTORY_COLORTEMP_ITEM6            _CT_USER

#define _FACTORY_COLORTEMP_TEXT1            _9__,_3__,_0__,_0__
#define _FACTORY_COLORTEMP_TEXT2            _7__,_5__,_0__,_0__
#define _FACTORY_COLORTEMP_TEXT3            _6__,_5__,_0__,_0__
#define _FACTORY_COLORTEMP_TEXT4            _5__,_8__,_0__,_0__
#define _FACTORY_COLORTEMP_TEXT5            _s__,_R__,_G__,_B__
#define _FACTORY_COLORTEMP_TEXT6            _U__,_s__,_e__,_r__

#define _FACTORY_WIN0_BORDER_PIXEL          (_BORDER0_2_PIXEL | _BORDER1_2_PIXEL)
#define _FACTORY_WIN0_BORDER_COLOR          ((_CP_WHITE << 4) | _CP_WHITE)
#define _FACTORY_WIN0_FUNC_CONTROL          (_BLEND_ENABLE | _GRADIENT_DISABLE | _GRADIENT_DIRECTION_H | _BORDER_ENABLE | _3D_BUTTON_1)
#define _FACTORY_WIN0_GRADIENT_CONTROL0     (_R_GRADIENT_DISABLE | _G_GRADIENT_DISABLE | _B_GRADIENT_ENABLE | _GRADIENT_LEVEL_3 | _R_GRADIENT_INC | _G_GRADIENT_INC | _B_GRADIENT_INC)
#define _FACTORY_WIN0_GRADIENT_CONTROL1     _3_LEVEL_RER_GRADIENT

#define _FACTORY_RBG_MAX                    255
#define _FACTORY_RBG_MIN                    0

#define _FACTORY_SSC_MAX                    15
#define _FACTORY_SSC_MIN                    0

#define _FACTORY_LVDS_CLOCK_CURRENT_MAX     3
#define _FACTORY_LVDS_CLOCK_CURRENT_MIN     0

#define _FACTORY_LVDS_DATA_CURRENT_MAX      3
#define _FACTORY_LVDS_DATA_CURRENT_MIN      0

#define _FACTORY_PATTERN_MAX                25
#define _FACTORY_PATTERN_MIN                0

#define _FACTORY_HOT_PLUG_HDMI_TIME_MAX     7
#define _FACTORY_HOT_PLUG_HDMI_TIME_MIN     1

#define _FACTORY_OSD_PAGE_MAX               1
#define _FACTORY_OSD_PAGE_MIN               0

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    __ = 0,
    _0__,_1__,_2__,_3__,_4__,_5__,_6__,_7__,_8__,_9__,
    _A__, _B__, _C__, _D__, _E__, _F__, _G__, _H__, _I__, _J__, _K__, _L__, _M__, _N__, _O__, _P__, _Q__, _R__, _S__, _T__, _U__, _V__, _W__, _X__, _Y__, _Z__,
    _a__, _b__, _c__, _d__, _e__, _f__, _g__, _h__, _i__, _j__, _k__, _l__, _m__, _n__, _o__, _p__, _q__, _r__, _s__, _t__, _u__, _v__, _w__, _x__, _y__, _z__,
    _A0__,_a0__, _a1__, _a2__, _a3__, _a4__,_c0__, _E0__, _e0__, _e1__, _e2__, _n0__, _u0__, _u1__, _u2__, _o0__, _o1__, _o2__, _o3__,_i0__,

    _UPDOT__,                // '
    _DOT__,                  // .
    _LEFT_BRACE__,           // (
    _RIGHT_BRACE__,          // )
    _AND__,                  // /
    _COLON__,                // :
    _AT_0__,                 // @
    _COMMA__,                // ,
    _SLINE__,                // -
    _SHIFT_LEFT__,           // <<
    _SHIFT_RIGHT__,          // >>
    _SEPERATE__,             // ;
    _QUERY__,                // ?
}EnumOSDfFontDef;

//****************************************************************************
// CODE TABLES
//****************************************************************************
//--------------------------------------------------
// Factory Text Table
//--------------------------------------------------
BYTE code tFACTORY_PAGE_SELECT_ITEM_TABLE[][3]=
{
    {ROW(_FACTORY_AUTOCOLOR_ROW), COL(_FACTORY_FUNCTION_COL),LENGTH(6)},
    {ROW(_FACTORY_AUTOCOLOR_TYPE_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(10)},
    {ROW(_FACTORY_BURNIN_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(4)},
    {ROW(_FACTORY_RESET_BURNIN_TIME_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(10)},
    {ROW(_FACTORY_RESET_PANEL_TIME_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(10)},

    {ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_R_COL), LENGTH(1)},    // 5
    {ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_B_COL), LENGTH(1)},

    {ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_R_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_B_COL), LENGTH(1)},    // 10

    {ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_R_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_B_COL), LENGTH(1)},

    {ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_R_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_G_COL), LENGTH(1)},    // 15
    {ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_B_COL), LENGTH(1)},

    {ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_R_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_B_COL), LENGTH(1)},

    {ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_R_COL), LENGTH(1)},    // 20
    {ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_B_COL), LENGTH(1)},

    {ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_COL), LENGTH(1)},
    {ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_COL), LENGTH(1)},    // 25

    {ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_COL), LENGTH(1)},
    {ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_COL), LENGTH(1)},

    {ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(6)},
    {ROW(_FACTORY_EXIT_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(3)},    // 30


    {ROW(_FACTORY_AUTOCOLOR_TYPE_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(6)},
    {ROW(_FACTORY_BURNIN_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},    // 33
    {ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},

    {ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},

    {ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},

    {ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},

    {ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},

    {ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},

    {ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},

    {ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL - 2), LENGTH(3)},
    {ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_OSD_PAGE_NUMBER_COL), LENGTH(2)},

    {ROW(_FACTORY_SSC_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(3)},
    {ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(6)},
    {ROW(_FACTORY_EXIT_1_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(3)},
};

BYTE code tFACTORY_PAGE_1_SELECT_ITEM_TABLE[][3]=
{
    {ROW(_FACTORY_BG_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(6)},
    {ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_R_COL), LENGTH(1)},
    {ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_G_COL), LENGTH(1)},
    {ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_B_COL), LENGTH(1)},
    {ROW(_FACTORY_SSC_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(3)},
    {ROW(_FACTORY_LVDS_CLOCK_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(11)},
    {ROW(_FACTORY_LVDS_DATA_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(11)},
    {ROW(_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_DP_AUX_MODE_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_OSD_DOUBLE_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_COLORIMETRY_SEAMLESS_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_DP_AUX_ADJR_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(18)},
    {ROW(_FACTORY_DP_IRQ_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_OSD_PAGE_1_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(12)},
    {ROW(_FACTORY_EXIT_1_ROW), COL(_FACTORY_FUNCTION_COL), LENGTH(3)},

    {ROW(_FACTORY_BG_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(3)},
    {ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_R_NUMBER_COL), LENGTH(3)},
    {ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_G_NUMBER_COL), LENGTH(3)},
    {ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_B_NUMBER_COL), LENGTH(3)},
    {ROW(_FACTORY_SSC_ROW), COL(_FACTORY_SSC_NUMBER_COL), LENGTH(3)},
    {ROW(_FACTORY_LVDS_CLOCK_ROW), COL(_FACTORY_LVDS_NUMBER_COL), LENGTH(3)},
    {ROW(_FACTORY_LVDS_DATA_ROW), COL(_FACTORY_LVDS_NUMBER_COL), LENGTH(3)},
    {ROW(_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), LENGTH(3)},
    {ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), LENGTH(3)},
    {ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), LENGTH(3)},
    {ROW(_FACTORY_DP_AUX_MODE_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(5)},
    {ROW(_FACTORY_OSD_DOUBLE_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(3)},
    {ROW(_FACTORY_COLORIMETRY_SEAMLESS_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(3)},
    {ROW(_FACTORY_DP_AUX_ADJR_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(3)},
    {ROW(_FACTORY_DP_IRQ_ROW), COL(_FACTORY_ON_OFF_COL), LENGTH(3)},

    {ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_OSD_PAGE_NUMBER_COL), LENGTH(2)},
};


BYTE code tsOSD_FACTORY_PROJECT_NAME[] =
{
    _MAIN_PAGE_MODEL_NAME,_END_,
};

BYTE code tsOSD_FACTORY_PANNEL_NAME[] =
{
    _PANNEL_NAME,_END_,
};

BYTE code tsOSD_FACTORY_VERSION[] =
{
    _FW_VERSION,_END_,
};

BYTE code tsOSD_FACTORY_AUTO_COLOR[] =
{
    _A__, _u__, _t__, _o__, __, _C__, _o__, _l__, _o__, _r__, _END_,
};

BYTE code tsOSD_FACTORY_BURNIN[] =
{
    _B__, _u__, _r__, _n__, _i__, _n__, _END_,
};

BYTE code tsOSD_FACTORY_BURNIN_TIME[] =
{
    _B__, _u__, _r__, _n__, _i__, _n__, __, _T__, _i__, _m__, _e__, _END_,
};

BYTE code tsOSD_FACTORY_RESET_BURNIN_TIME[] =
{
    _R__, _e__, _s__, _e__, _t__, __, _B__, _u__, _r__, _n__, _i__, _n__, __, _T__, _i__, _m__, _e__, _END_,
};

BYTE code tsOSD_FACTORY_PANEL_TIME[] =
{
    _P__, _a__, _n__, _e__, _l__, __, _T__, _i__, _m__, _e__, _END_,
};

BYTE code tsOSD_FACTORY_RESET_PANEL_TIME[] =
{
    _R__, _e__, _s__, _e__, _t__, __, _P__, _a__, _n__, _e__, _l__, __, _T__, _i__, _m__, _e__, _END_,
};

BYTE code tsOSD_FACTORY_COLORTEMP[] =
{
    _C__, _o__, _l__, _o__, _r__, _t__, _e__, _m__, _p__, _END_,
};

BYTE code tsOSD_FACTORY_COLORTEMP0[] =
{
    _FACTORY_COLORTEMP_TEXT1,_END_,
};

BYTE code tsOSD_FACTORY_COLORTEMP1[] =
{
    _FACTORY_COLORTEMP_TEXT2,_END_,
};

BYTE code tsOSD_FACTORY_COLORTEMP2[] =
{
    _FACTORY_COLORTEMP_TEXT3,_END_,
};

BYTE code tsOSD_FACTORY_COLORTEMP3[] =
{
    _FACTORY_COLORTEMP_TEXT4,_END_,
};

BYTE code tsOSD_FACTORY_COLORTEMP4[] =
{
    _FACTORY_COLORTEMP_TEXT5,_END_,
};

BYTE code tsOSD_FACTORY_COLORTEMP5[] =
{
    _FACTORY_COLORTEMP_TEXT6,_END_,
};

BYTE code tsOSD_FACTORY_ADC_OFFSET[] =
{
    _A__, _D__, _C__, __, _O__, _f__, _f__, _s__, _e__, _t__, _END_,
};

BYTE code tsOSD_FACTORY_ADC_GAIN[] =
{
    _A__, _D__, _C__, __, _G__, _a__, _i__, _n__, _END_,
};

BYTE code tsOSD_FACTORY_PAGE[] =
{
    _N__,_e__,_x__,_t__,__,_P__,_a__,_g__,_e__,_END_,
};

BYTE code tsOSD_FACTORY_EXIT[] =
{
    _E__, _x__, _i__, _t__, _END_,
};

BYTE code tsOSD_FACTORY_AUTO_COLOR_TYPE[] =
{
    _A__, _u__, _t__, _o__, __, _C__, _o__, _l__, _o__, _r__, __,_T__, _y__, _p__, _e__, _END_,
};

code BYTE *tOSD_FACTORY_PAGE_TABLE[] =
{
    tsOSD_FACTORY_PROJECT_NAME,
    tsOSD_FACTORY_PANNEL_NAME,
    tsOSD_FACTORY_VERSION,
    tsOSD_FACTORY_AUTO_COLOR,
    tsOSD_FACTORY_BURNIN,
    tsOSD_FACTORY_RESET_BURNIN_TIME,
    tsOSD_FACTORY_BURNIN_TIME,
    tsOSD_FACTORY_RESET_PANEL_TIME,
    tsOSD_FACTORY_PANEL_TIME,
    tsOSD_FACTORY_COLORTEMP,
    tsOSD_FACTORY_COLORTEMP0,
    tsOSD_FACTORY_COLORTEMP1,
    tsOSD_FACTORY_COLORTEMP2,
    tsOSD_FACTORY_COLORTEMP3,
    tsOSD_FACTORY_COLORTEMP4,
    tsOSD_FACTORY_COLORTEMP5,
    tsOSD_FACTORY_ADC_GAIN,
    tsOSD_FACTORY_ADC_OFFSET,
    tsOSD_FACTORY_PAGE,
    tsOSD_FACTORY_EXIT,
    tsOSD_FACTORY_AUTO_COLOR_TYPE,
};

BYTE code tsOSD_FACTORY_SSC[] =
{
    _S__, _S__, _C__, _END_,
};

BYTE code tsOSD_FACTORY_BG_ON_OFF[] =
{
    _B__, _G__, __, _O__, _n__, __, _O__, _f__, _f__, _END_,
};

BYTE code tsOSD_FACTORY_BG_COLOR[] =
{
    _B__, _G__, __, _C__, _o__, _l__, _o__, _r__, _END_,
};

BYTE code tsOSD_FACTORY_LVDS_CLOCK[] =
{
    _L__,_V__,_D__,_S__,__,_C__,_l__,_o__,_c__,_k__,__,_D__,_r__,_i__,_v__,_i__,_n__,_g__,_END_,
};

BYTE code tsOSD_FACTORY_LVDS_DATA[] =
{
    _L__,_V__,_D__,_S__,__,_D__,_a__,_t__,_a__,__,_D__,_r__,_i__,_v__,_i__,_n__,_g__,_END_,
};



BYTE code tsOSD_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH[] =
{
    _D__,_P__,__,_H__,_o__,_t__,__,_P__,_l__,_u__,_g__,__,_O__,_f__,_f__,__,_H__,_i__,_g__,_h__,_END_,
};

BYTE code tsOSD_FACTORY_HOT_PLUG_HDMI_SUPPORT[] =
{
    _H__,_D__,_M__,_I__,__,_H__,_o__,_t__,__,_P__,_l__,_u__,_g__,_END_,
};

BYTE code tsOSD_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME[] =
{
    _H__,_o__,_t__,__,_P__,_l__,_u__,_g__,_T__,_i__,_m__,_e__,_LEFT_BRACE__,_1__,_0__,_0__,_m__,_s__,_RIGHT_BRACE__,_END_,
};
BYTE code tsOSD_FACTORY_DP_AUX_MODE[] =
{
    _D__,_P__,__,_A__,_U__,_X__,__,_D__,_i__,_f__,_f__,__,_M__,_o__,_d__,_e__,_END_,
};
BYTE code tsOSD_DOUBLE_SIZE[] =
{
    _O__,_S__,_D__,__,_S__,_i__,_z__,_e__,_X__,_2__,_END_,
};

BYTE code tsCOLORIMETRY_SEAMLESS[] =
{
    _C__,_o__,_l__,_o__,_r__,_i__,_m__,_e__,_t__,_r__,_y__,__,_S__,_e__,_a__,_m__,_l__,_e__,_s__,_s__,_END_,
};
BYTE code tsOSD_FACTORY_DP_AUX_ADJR_SETTING[] =
{
    _D__,_P__,__,_A__,_U__,_X__,__,_D__,_i__,_f__,_f__,__,_M__,_o__,_d__,_e__,__,_A__,_d__,_j__,_r__,__,_S__,_e__,_t__,_t__,_i__,_n__,_g__,_END_,
};
BYTE code tsOSD_FACTORY_DP_IRQ_TIME[] =
{
    _D__,_P__,__,_I__,_R__,_Q__,__,_T__,_i__,_m__,_e__,_LEFT_BRACE__,_1__,_u__,_s__,_RIGHT_BRACE__,_END_,
};

code BYTE *tOSD_FACTORY_PAGE_1_TABLE[] =
{

    tsOSD_FACTORY_BG_ON_OFF,//0
    tsOSD_FACTORY_BG_COLOR,// 1
    tsOSD_FACTORY_SSC,// 2
    tsOSD_FACTORY_LVDS_CLOCK,// 3
    tsOSD_FACTORY_LVDS_DATA,// 4
    tsOSD_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH,//5
    tsOSD_FACTORY_HOT_PLUG_HDMI_SUPPORT,//6
    tsOSD_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME,//7
    tsOSD_FACTORY_DP_AUX_MODE,//8
    tsOSD_DOUBLE_SIZE,//9
    tsCOLORIMETRY_SEAMLESS,//10
    tsOSD_FACTORY_DP_AUX_ADJR_SETTING,//11
    tsOSD_FACTORY_DP_IRQ_TIME,//12
    tsOSD_FACTORY_PAGE,//13
    tsOSD_FACTORY_EXIT,//14

};

BYTE code tsOSD_FACTORY_R[] =
{
    _R__, _END_,
};

BYTE code tsOSD_FACTORY_G[] =
{
    _G__, _END_,
};

BYTE code tsOSD_FACTORY_B[] =
{
    _B__, _END_,
};

code BYTE *tOSD_FACTORY_RGB_TABLE[] =
{
    tsOSD_FACTORY_R,
    tsOSD_FACTORY_G,
    tsOSD_FACTORY_B,
};

BYTE code tsOSD_FACTORY_ON[] =
{
    _O__, _n__, _END_,
};

BYTE code tsOSD_FACTORY_OFF[] =
{
    _O__, _f__, _f__, _END_,
};

code BYTE *tOSD_FACTORY_ON_OFF_TABLE[] =
{
    tsOSD_FACTORY_OFF,
    tsOSD_FACTORY_ON,
};

BYTE code tsOSD_FACTORY_PASS[] =
{
    _P__, _a__, _s__, _s__, _END_,
};

BYTE code tsOSD_FACTORY_FAIL[] =
{
    _F__, _a__, _i__, _l__, _END_,
};

code BYTE *tOSD_FACTORY_PASS_FAIL_TABLE[] =
{
    tsOSD_FACTORY_FAIL,
    tsOSD_FACTORY_PASS,
};

BYTE code tsOSD_FACTORY_HOUR[] =
{
    _H__, _o__, _u__, _r__, _END_,
};

BYTE code tsOSD_FACTORY_MIN[] =
{
    _M__, _i__, _n__, _END_,
};

code BYTE *tOSD_FACTORY_HOUR_MIN_TABLE[] =
{
    tsOSD_FACTORY_HOUR,
    tsOSD_FACTORY_MIN,
};

BYTE code tsOSD_FACTORY_AUTO_COLOR_TYPE_INTERNAL[] =
{
    _I__, _n__, _t__, _e__, _r__, _n__, _a__, _l__, _END_,
};

BYTE code tsOSD_FACTORY_AUTO_COLOR_TYPE_EXTERNAL[] =
{
    _E__, _x__, _t__, _e__, _r__, _n__, _a__, _l__, _END_,
};

code BYTE *tOSD_FACTORY_AUTO_COLOR_TYPE_TABLE[] =
{
    tsOSD_FACTORY_AUTO_COLOR_TYPE_INTERNAL,
    tsOSD_FACTORY_AUTO_COLOR_TYPE_EXTERNAL,
};
BYTE code tsOSD_FACTORY_ASCII_0[] =
{
    _0__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_1[] =
{
    _1__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_2[] =
{
    _2__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_3[] =
{
    _3__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_4[] =
{
    _4__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_5[] =
{
    _5__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_6[] =
{
    _6__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_7[] =
{
    _7__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_8[] =
{
    _8__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_9[] =
{
    _9__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_A[] =
{
    _A__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_B[] =
{
    _B__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_C[] =
{
    _C__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_D[] =
{
    _D__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_E[] =
{
    _E__, _END_,
};
BYTE code tsOSD_FACTORY_ASCII_F[] =
{
    _F__, _END_,
};

code BYTE *tsOSD_FACTORY_ASCII_TABLE[] =
{
    tsOSD_FACTORY_ASCII_0,
    tsOSD_FACTORY_ASCII_1,
    tsOSD_FACTORY_ASCII_2,
    tsOSD_FACTORY_ASCII_3,
    tsOSD_FACTORY_ASCII_4,
    tsOSD_FACTORY_ASCII_5,
    tsOSD_FACTORY_ASCII_6,
    tsOSD_FACTORY_ASCII_7,
    tsOSD_FACTORY_ASCII_8,
    tsOSD_FACTORY_ASCII_9,
    tsOSD_FACTORY_ASCII_A,
    tsOSD_FACTORY_ASCII_B,
    tsOSD_FACTORY_ASCII_C,
    tsOSD_FACTORY_ASCII_D,
    tsOSD_FACTORY_ASCII_E,
    tsOSD_FACTORY_ASCII_F,
};

BYTE code tFONT_FACTORY_EUROPE[] =
{
    //========Address -- (00),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (01),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (02),
    0x00,0x00,0x00,
    0x03,0x00,0x00,
    0x37,0x00,0x00,
    0xfb,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x30,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (03),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xc0,0x66,0x00,
    0x01,0xcc,0x00,
    0x33,0x80,0x00,
    0x6f,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (04),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xc0,0x6e,0x00,
    0x33,0xcc,0x00,
    0x0c,0xe6,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (05),
    0x00,0x00,0x00,
    0x00,0x0c,0x00,
    0x11,0xcc,0x00,
    0x33,0xcc,0x00,
    0x66,0xcc,0x00,
    0xcf,0xce,0x00,
    0xf0,0xec,0x00,
    0x00,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (06),
    0x00,0x00,0x00,
    0x07,0x0e,0x00,
    0x76,0xe0,0x00,
    0x6f,0x08,0x00,
    0xfc,0xce,0x00,
    0x0c,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (07),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xcf,0x08,0x00,
    0xfe,0xce,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (08),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xf0,0xec,0x00,
    0x11,0x88,0x00,
    0x33,0x00,0x00,
    0x36,0x00,0x00,
    0x66,0x00,0x00,
    0x60,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (09),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xce,0x6e,0x00,
    0x77,0xcc,0x00,
    0xec,0xe6,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (0a),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x30,0xe6,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (0b),
    0x00,0x00,0x00,
    0x01,0x0c,0x00,
    0x11,0xcc,0x00,
    0x33,0x66,0x00,
    0x36,0x63,0x00,
    0x77,0xff,0x00,
    0x6c,0x31,0x08,
    0xc0,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (0c),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xf3,0x00,
    0xcc,0x33,0x00,
    0xff,0xee,0x00,
    0xcc,0x33,0x00,
    0xcf,0x3f,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (0d),
    0x00,0x00,0x00,
    0x01,0x0e,0x00,
    0x76,0xf3,0x08,
    0xcc,0x10,0x00,
    0xcc,0x00,0x00,
    0xcc,0x11,0x08,
    0x67,0x3f,0x80,
    0x10,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (0e),
    0x00,0x00,0x00,
    0x0f,0x0c,0x00,
    0xfc,0xe6,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcf,0x6e,0x00,
    0xf0,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (0f),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xe0,0x00,
    0xcc,0x00,0x00,
    0xff,0xee,0x00,
    0xcc,0x00,0x00,
    0xcf,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (10),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xe0,0x00,
    0xcc,0x00,0x00,
    0xff,0xcc,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (11),
    0x00,0x00,0x00,
    0x01,0x0e,0x00,
    0x76,0xf3,0x08,
    0xcc,0x10,0x80,
    0xcc,0x07,0x08,
    0xcc,0x71,0x88,
    0x67,0x1f,0x88,
    0x10,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (12),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xff,0xff,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xc0,0x30,0x00,
    0x00,0x00,0x00,

    //========Address -- (13),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (14),
    0x00,0x00,0x00,
    0x00,0x06,0x00,
    0x00,0x66,0x00,
    0x00,0x66,0x00,
    0x00,0x66,0x00,
    0x0c,0x66,0x00,
    0xc7,0x6c,0x00,
    0x70,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (15),
    0x00,0x00,0x00,
    0x0c,0x01,0x08,
    0xcc,0x36,0x00,
    0xcd,0xc8,0x00,
    0xfe,0x8c,0x00,
    0xcc,0x66,0x00,
    0xcc,0x31,0x08,
    0xc0,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (16),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcf,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (17),
    0x00,0x00,0x00,
    0x0e,0x00,0x0e,
    0xef,0x01,0xee,
    0xff,0x11,0xee,
    0xdd,0xbb,0x66,
    0xdc,0xbe,0x66,
    0xcc,0xee,0x66,
    0xc0,0xe0,0x60,
    0x00,0x00,0x00,

    //========Address -- (18),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xee,0x33,0x00,
    0xff,0x33,0x00,
    0xdd,0xbb,0x00,
    0xcc,0xff,0x00,
    0xcc,0x77,0x00,
    0xc0,0x30,0x00,
    0x00,0x00,0x00,

    //========Address -- (19),
    0x00,0x00,0x00,
    0x03,0x0e,0x00,
    0x76,0xf3,0x00,
    0xcc,0x11,0x88,
    0xcc,0x11,0x88,
    0xcc,0x11,0x88,
    0x67,0x3f,0x00,
    0x30,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (1a),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xf3,0x00,
    0xcc,0x33,0x00,
    0xff,0xfe,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (1b),
    0x00,0x00,0x00,
    0x03,0x0e,0x00,
    0x76,0xf3,0x00,
    0xcc,0x11,0x88,
    0xcc,0x11,0x88,
    0xcc,0x1d,0x88,
    0x67,0x7f,0x00,
    0x30,0xf0,0xc8,
    0x00,0x00,0x00,

    //========Address -- (1c),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xf3,0x00,
    0xcc,0x33,0x00,
    0xff,0xfe,0x00,
    0xcc,0x33,0x00,
    0xcc,0x11,0x88,
    0xc0,0x00,0xc0,
    0x00,0x00,0x00,

    //========Address -- (1d),
    0x00,0x00,0x00,
    0x03,0x0c,0x00,
    0x7c,0xe7,0x00,
    0xce,0x30,0x00,
    0x73,0xce,0x00,
    0x0c,0x73,0x00,
    0xe7,0x3e,0x00,
    0x30,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (1e),
    0x00,0x00,0x00,
    0x0f,0x0f,0x00,
    0xf1,0xf8,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x10,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (1f),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xe7,0x7e,0x00,
    0x30,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (20),
    0x00,0x00,0x00,
    0x0c,0x01,0x08,
    0xc6,0x13,0x80,
    0x66,0x33,0x00,
    0x33,0x66,0x00,
    0x33,0x66,0x00,
    0x11,0xcc,0x00,
    0x10,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (21),
    0x00,0x00,0x00,
    0x0c,0x0c,0x0c,
    0xcc,0xcc,0xcc,
    0xcc,0xcc,0xcc,
    0xdd,0xee,0xcc,
    0xd7,0x23,0xc8,
    0x77,0x33,0x88,
    0x70,0x30,0x80,
    0x00,0x00,0x00,

    //========Address -- (22),
    0x00,0x00,0x00,
    0x0c,0x00,0x0c,
    0xe7,0x13,0xc8,
    0x31,0x3e,0x00,
    0x00,0xcc,0x00,
    0x13,0xe3,0x00,
    0x7e,0x31,0x8c,
    0xc0,0x00,0xc0,
    0x00,0x00,0x00,

    //========Address -- (23),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xc6,0x36,0x00,
    0x63,0x6c,0x00,
    0x31,0xc8,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x10,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (24),
    0x00,0x00,0x00,
    0x0f,0x0f,0x00,
    0xf0,0xf7,0x00,
    0x00,0x6c,0x00,
    0x13,0x88,0x00,
    0x36,0x00,0x00,
    0xcf,0x0f,0x00,
    0xf0,0xf0,0x00,
    0x00,0x00,0x00,

    //========Address -- (25),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x7c,0xcc,0x00,
    0xcf,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (26),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xdf,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xef,0xec,0x00,
    0xd0,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (27),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0xce,0x00,
    0xec,0x60,0x00,
    0xcc,0x00,0x00,
    0xe7,0x6e,0x00,
    0x30,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (28),
    0x00,0x00,0x00,
    0x00,0x06,0x00,
    0x00,0x66,0x00,
    0x37,0x6e,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x30,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (29),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (2a),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x76,0x80,0x00,
    0xff,0x88,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x60,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (2b),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x6e,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x3c,0x66,0x00,
    0x73,0xc8,0x00,

    //========Address -- (2c),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xdf,0xce,0x00,
    0xec,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xc0,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (2d),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xc0,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (2e),
    0x00,0x00,0x00,
    0x06,0x00,0x00,
    0x60,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0xec,0x00,0x00,

    //========Address -- (2f),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcd,0xc8,0x00,
    0xdf,0x80,0x00,
    0xfd,0x88,0x00,
    0xdc,0xcc,0x00,
    0xc0,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (30),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (31),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0x9f,0x8c,
    0xec,0xec,0xcc,
    0xcc,0xcc,0xcc,
    0xcc,0xcc,0xcc,
    0xc0,0xc0,0xc0,
    0x00,0x00,0x00,

    //========Address -- (32),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0xce,0x00,
    0xec,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xc0,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (33),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (34),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xef,0xec,0x00,
    0xdc,0x80,0x00,
    0xcc,0x00,0x00,

    //========Address -- (35),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x6e,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x30,0x66,0x00,
    0x00,0x66,0x00,

    //========Address -- (36),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0x88,0x00,
    0xec,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (37),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x7f,0x8c,0x00,
    0xce,0xc0,0x00,
    0x71,0x8c,0x00,
    0xcf,0xcc,0x00,
    0x70,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (38),
    0x00,0x00,0x00,
    0x02,0x00,0x00,
    0x66,0x00,0x00,
    0xff,0x88,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x67,0x08,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (39),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (3a),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x66,0x00,
    0xc6,0x6c,0x00,
    0x66,0xcc,0x00,
    0x33,0x88,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (3b),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0xee,0x66,
    0x66,0xee,0xcc,
    0x67,0xab,0xcc,
    0x33,0x11,0x88,
    0x30,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (3c),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xce,0x37,0x00,
    0x63,0x6c,0x00,
    0x33,0xcc,0x00,
    0x6e,0x67,0x00,
    0xc0,0x30,0x00,
    0x00,0x00,0x00,

    //========Address -- (3d),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x33,0x00,
    0x66,0x66,0x00,
    0x63,0x6c,0x00,
    0x33,0xcc,0x00,
    0x11,0x88,0x00,
    0xfe,0x00,0x00,

    //========Address -- (3e),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xff,0xee,0x00,
    0x01,0xc8,0x00,
    0x33,0x00,0x00,
    0x6f,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (3f),
    0x33,0x66,0x00,
    0x01,0x0c,0x00,
    0x11,0xcc,0x00,
    0x33,0x66,0x00,
    0x36,0x63,0x00,
    0x77,0xff,0x00,
    0x6c,0x31,0x08,
    0xc0,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (40),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (41),
    0x00,0x00,0x00,
    0x07,0x04,0x00,
    0x50,0xc0,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (42),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (43),
    0x00,0x00,0x00,
    0x06,0x0c,0x00,
    0x60,0xc0,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (44),
    0x00,0x00,0x00,
    0x06,0x00,0x00,
    0x30,0x00,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (45),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0xce,0x00,
    0xec,0x60,0x00,
    0xcc,0x00,0x00,
    0xe7,0x6e,0x00,
    0x37,0xc0,0x00,
    0x1e,0x00,0x00,

    //========Address -- (46),
    0x36,0x8c,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xe0,0x00,
    0xcc,0x00,0x00,
    0xff,0xee,0x00,
    0xcc,0x00,0x00,
    0xcf,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (47),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (48),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (49),
    0x00,0x00,0x00,
    0x03,0x00,0x00,
    0x10,0x80,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (4a),
    0x00,0x00,0x00,
    0x07,0x04,0x00,
    0x50,0xc0,0x00,
    0xdf,0xce,0x00,
    0xec,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xc0,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4b),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4c),
    0x00,0x00,0x00,
    0x06,0x0c,0x00,
    0x60,0xc0,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4d),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4e),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (4f),
    0x00,0x00,0x00,
    0x07,0x04,0x00,
    0x50,0xc0,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (50),
    0x00,0x00,0x00,
    0x06,0x0c,0x00,
    0x60,0xc0,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (51),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (52),
    0x00,0x00,0x00,
    0x06,0x00,0x00,
    0xc0,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x60,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (53),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (54),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (55),
    0x00,0x00,0x00,
    0x12,0x00,0x00,
    0x66,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0x46,0x00,0x00,
    0x62,0x00,0x00,
    0x10,0x00,0x00,

    //========Address -- (56),
    0x00,0x00,0x00,
    0x84,0x00,0x00,
    0x66,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x26,0x00,0x00,
    0x64,0x00,0x00,
    0x80,0x00,0x00,

    //========Address -- (57),
    0x00,0x00,0x00,
    0x03,0x00,0x00,
    0x33,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (58),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (59),
    0x00,0x00,0x00,
    0x01,0xff,0x8c,
    0x36,0x00,0x66,
    0x66,0x7d,0x6e,
    0x66,0x99,0x66,
    0x66,0xbf,0x6e,
    0x67,0x60,0xc0,
    0x30,0xff,0xec,
    0x00,0x00,0x00,

    //========Address -- (5a),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x66,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5b),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xff,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5c),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x24,0x48,0x00,
    0x99,0x00,0x00,
    0x42,0x84,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5d),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x94,0x08,0x00,
    0x22,0x44,0x00,
    0x49,0x80,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5e),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x66,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x66,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5f),
    0x00,0x00,0x00,
    0x07,0x08,0x00,
    0xcc,0xcc,0x00,
    0x01,0xc8,0x00,
    0x13,0x80,0x00,
    0x30,0x00,0x00,
    0x33,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

BYTE code tOSD_FACTORY_CHARWIDTH_EUROPE[][2] =
{
    {__, 4},

    {_0__, 8}, {_1__, 8}, {_2__, 8}, {_3__, 8}, {_4__, 8}, {_5__, 8}, {_6__, 8}, {_7__, 8}, {_8__, 8}, {_9__, 8},

    {_A__, 11}, {_B__,  9}, {_C__, 10}, {_D__,  9}, {_E__,  8}, {_F__,  8}, {_G__, 10}, {_H__,  9}, {_I__,  3}, {_J__,  8},
    {_K__, 10}, {_L__,  8}, {_M__, 12}, {_N__,  9}, {_O__, 10}, {_P__,  9}, {_Q__, 11}, {_R__, 10}, {_S__,  9}, {_T__,  9},
    {_U__,  9}, {_V__, 10}, {_W__, 11}, {_X__, 11}, {_Y__,  9}, {_Z__,  9},

    {_a__,  8}, {_b__,  8}, {_c__,  8}, {_d__,  8}, {_e__,  8}, {_f__,  6}, {_g__,  8}, {_h__,  8}, {_i__,  3}, {_j__,  4},
    {_k__,  7}, {_l__,  3}, {_m__, 11}, {_n__,  8}, {_o__,  8}, {_p__,  8}, {_q__,  8}, {_r__,  6}, {_s__,  7}, {_t__,  6},
    {_u__,  8}, {_v__,  8}, {_w__, 12}, {_x__,  9}, {_y__,  9}, {_z__,  8},

    {_A0__,11}, {_a0__, 8}, {_a1__, 8}, {_a2__, 8}, {_a3__, 8}, {_a4__, 8}, {_c0__, 8}, {_E0__, 8}, {_e0__, 8}, {_e1__, 8}, {_e2__, 8}, {_n0__, 8},
    {_u0__, 8}, {_u1__, 8}, {_u2__, 8}, {_o0__, 8}, {_o1__, 8}, {_o2__, 8}, {_o3__, 8}, {_i0__, 4},

    {_UPDOT__, 3}, {_DOT__,   3}, {_LEFT_BRACE__, 5}, {_RIGHT_BRACE__, 5}, {_AND__, 5}, {_COLON__, 3}, {_AT_0__, 12},
    {_COMMA__, 5}, {_SLINE__, 5}, {_SHIFT_LEFT__, 7}, {_SHIFT_RIGHT__, 7}, {_SEPERATE__, 4}, {_QUERY__, 7},

    {_END_,_END_},
};

BYTE code tFONT_FACTORY_GLOBAL[]=
{
    0x0f,0x12,0x34,0x56,0x78,0x9a,0xbc,0xde,0x00,0x08,0x00,0x00,
    0x00,0x00,0x00,0x00,0xc0,0xff,
};

BYTE code tOSD_FACTORY_WIN0[] =
{
    _WIN0,
    _FACTORY_WIN0_BORDER_PIXEL,
    _FACTORY_WIN0_BORDER_COLOR,
    _FACTORY_WIN0_FUNC_CONTROL,
    _FACTORY_WIN0_GRADIENT_CONTROL0,
    _FACTORY_WIN0_GRADIENT_CONTROL1,
};

//*************************************************************************************************
// ONE PIECE
//*************************************************************************************************
#if(_FACTORY_ONE_PIECE_MARK_SUPPORT == _ON)

#define _ONE_PIECE_4BIT_FONT_STAR           280
#define ICON(x)                             ((_ONE_PIECE_4BIT_FONT_STAR / 4) + (x))

BYTE code tOSD_ONE_PIECE[] =
{
    5, _AUTOINC,     0x90, FONTALLBYTE(577),
    45, _NON_AUTOINC, 0x92, 0x90, ICON(0x00), 0x00, 0x90, ICON(0x01), 0x00, 0x90, ICON(0x02), 0x00, 0x90, ICON(0x03), 0x00, 0x90, ICON(0x04), 0x00, 0x90, ICON(0x05), 0x00, 0x90, ICON(0x06), 0x00, 0x90, ICON(0x07), 0x00, 0x90, ICON(0x08), 0x00, 0x90, ICON(0x09), 0x00, 0x90, ICON(0x0A), 0x00, 0x90, ICON(0x0B), 0x00, 0x90, ICON(0x0C), 0x00, 0x90, ICON(0x0D), 0x00,

    5, _AUTOINC,     0x90, FONTALLBYTE(604),
    45, _NON_AUTOINC, 0x92, 0x90, ICON(0x0E), 0x00, 0x90, ICON(0x0F), 0x00, 0x90, ICON(0x10), 0x00, 0x90, ICON(0x11), 0x00, 0x90, ICON(0x12), 0x00, 0x90, ICON(0x13), 0x00, 0x90, ICON(0x14), 0x00, 0x90, ICON(0x15), 0x00, 0x90, ICON(0x16), 0x00, 0x90, ICON(0x17), 0x00, 0x90, ICON(0x18), 0x00, 0x90, ICON(0x19), 0x00, 0x90, ICON(0x1A), 0x00, 0x90, ICON(0x1B), 0x00,

    5, _AUTOINC,     0x90, FONTALLBYTE(631),
    45, _NON_AUTOINC, 0x92, 0x90, ICON(0x1C), 0x00, 0x90, ICON(0x1D), 0x00, 0x90, ICON(0x1E), 0x00, 0x90, ICON(0x1F), 0x00, 0x90, ICON(0x20), 0x00, 0x90, ICON(0x21), 0x00, 0x90, ICON(0x22), 0x00, 0x90, ICON(0x23), 0x00, 0x90, ICON(0x24), 0x00, 0x90, ICON(0x25), 0x00, 0x90, ICON(0x26), 0x00, 0x90, ICON(0x27), 0x00, 0x90, ICON(0x28), 0x00, 0x90, ICON(0x29), 0x00,
};

BYTE code tPALETTE_ONE_PIECE[] =
{
    0x0d,0x0a,0x0b,
    0xfb,0xf9,0xfa,
    0x87,0x3e,0x4b,
    0xbb,0x92,0x83,
    0x66,0xc6,0xd0,
    0xca,0xb0,0xa3,
    0x82,0x6e,0x65,
    0xaf,0x73,0x69,
    0xd8,0xd1,0xca,
    0x59,0x53,0x4e,
    0x61,0xaf,0xb1,
    0x45,0x33,0x31,
    0x8f,0x91,0x8a,
    0x8f,0xad,0x9e,
    0x2d,0x2a,0x28,
    0x90,0xc6,0x97,
};

BYTE code tOSD_ONE_PIECE_ICON[] =
{
    0x0f,0x18,0x24,0x3e,0xc7,0xb6,0xda,0x95,0x0d,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0xa4,0x9e,0x5f,0xf2,0x7c,0xff,0xee,0xe7,0x7e,0x9f,0xfd,0xc9,0xe7,0xfe,0xdd,0xc9,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5a,0x2f,0xba,0x57,0x33,0xab,0x5e,0xab,0x86,0x06,0x00,0x00,0x00,0x9c,0xf5,0xb2,0x3e,0xdf,0x5e,0xfd,0x5b,0xd7,0xac,0xe9,0xf7,0x4b,0x27,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0xee,0x3b,0x49,0x3e,0x4f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x74,0xc3,0x2c,0x49,0x92,0x24,0x49,0x72,0x25,0xc9,0xfd,0x26,0x39,0xe9,0x37,0x39,0x67,0xcd,0x4e,0xd6,0xaf,0xe6,0x3a,0xd7,0x74,0xf5,0x47,0x5d,0xae,0x6b,0x00,0x00,0x00,0x63,0x41,0x7d,0x2f,0xfc,0xdd,0x8b,0x75,0xe6,0x4c,0x8d,0xa3,0x6e,0x00,0xf0,0xc2,0x1a,0xd8,0x2e,0xcc,0x7a,0xb1,0x9e,0xe7,0x4b,0x6a,0x55,0xf9,0xfc,0xde,0xf7,0x5d,0x5f,0x00,0xd8,0xd0,0x3f,0xd4,0xdc,0x1f,0x6a,0x3f,0xcf,0xc5,0xf3,0xf9,0xbb,0x77,0xad,0x4f,0x72,0xcf,0xf7,0x54,0xfe,0xee,0x4f,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0xe4,0xfe,0x25,0xc9,0x73,0x92,0x24,0x7f,0x49,0x92,0x64,0x7f,0x2a,0xe9,0xac,0x93,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0xc1,0x0c,0xf4,0x02,0x00,0x56,0xb3,0x01,0x00,0xc0,0xf7,0x85,0x55,0xe0,0x0b,0xb8,0xe6,0x70,0x7b,0x7e,0xbc,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xc9,0x91,0x24,0x1f,0xb9,0x3f,0x01,0x00,0x00,0x00,0x00,0x00,0xc0,0x0d,0x00,0x00,0x00,0x00,0x00,0xc0,0x35,0x75,0x03,0x00,0x00,0x00,0x00,0x40,0x05,0xbe,0x91,0x91,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0xe4,0x24,0x49,0x9d,0xf3,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0xa7,0x6a,0xdd,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xc9,0x49,0x24,0x7f,0x72,0xff,0xf6,0xf7,0xfb,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x68,0x7a,0x00,0x00,0x00,0x00,0x00,0x8a,0xf0,
    0x8d,0x7e,0xaf,0xbf,0xfb,0x97,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x5c,0x57,0x25,0xf9,0x3d,0x9f,0xce,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbc,0x18,0x00,0x00,0x00,0x00,0x00,0xf6,0x3e,0x78,0xd7,0xdc,0x2a,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xc9,0xc9,0x49,0xce,0x39,0x39,0xbf,0x95,0x4f,0x72,0x9e,0xe7,0x49,0x0e,0x00,0x00,0x00,0x00,0x60,0x00,0xaa,0x01,0x00,0x00,0x00,0x00,0x4c,0xcd,0xb8,0x76,0xd5,0x36,0x3b,0xbc,0x00,0x00,0x00,0x80,0x52,0xd4,0xae,0xa9,0xf7,0x99,0xa1,0xd6,0xba,0xf8,0xcb,0xdf,0x4e,0x92,0xfb,0x4a,0x4e,0xae,0x9d,0x24,0x39,0x49,0x92,0x24,0x49,0x72,0xef,0xfc,0xbe,0xb9,0x93,0x73,0xe6,0xe4,0xbe,0x7b,0xf5,0x79,0x2c,0x00,0x00,0x00,0x00,0x00,0x0a,0x06,0x68,0xa8,0x01,0x00,0x00,0x80,0x86,0xfa,0xfe,0xb0,0x66,0xfa,0x6c,0xdf,0x0b,0x7a,0x53,0xf6,0x05,0x0a,0x00,0xfa,0xf2,0x7e,0x34,0xf5,0xbd,0x4a,0xf7,0xfb,0xbd,0xeb,0x4d,0x92,0x24,0x49,0x92,0x24,0xfb,0x4e,0xce,0xe9,0xca,0xf5,0xc9,0xf7,0x84,0x75,0x65,0x35,0xda,0xbd,0x94,0x9c,0xeb,0x32,0x2f,0x00,0x00,0x00,0x60,0x2e,0xce,0xcf,0xd8,0xe8,0x4d,0x31,0x7f,0x05,0xa0,0xc1,0x2c,0x00,0x66,0x98,0xef,0xdf,0xfe,0xde,0xb6,0x07,0x3d,0xb5,0xc2,0xfe,0x7b,0x00,0x00,0x57,0x53,0x75,0x1f,0x7b,0xdc,0x45,0x65,0xd7,0x1b,0x65,0xeb,0xcb,0x94,0xb9,0xae,0xba,0x7f,0x49,0x92,0xdc,0x49,0xf2,0xe9,0xa4,0x3e,0x79,0x92,0x4f,0x9e,0x24,0x9f,0x27,0x49,0xf6,0x93,0x9c,0x53,0xbf,0xe4,0xfb,0x99,0x4a,0xee,0x2f,0x01,0x00,0x00,0x00,0x00,0xb8,0xc0,0x80,0x02,0x6c,0x30,0xb0,0x9b,0xed,0x60,0x0d,0x74,0xc3,0x2c,0x30,0x50,0x05,0x68,0x98,0x9b,0x33,0xb3,0xd8,0x2e,0xbc,0x0b,0xae,0x45,0xd5,0x1c,0xfe,0x66,0xa3,0xff,0x8a,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0x49,0x92,0x24,0xbf,0xe4,0x64,0xff,0x3d,0x79,0xf2,0x79,0x4e,0xee,0xe4,0xbe,0x9f,0x24,0x59,0x01,0x00,0x00,0x00,0x00,0xd6,0x00,0x00,
    0x00,0x00,0x00,0x80,0xa5,0x86,0xb5,0x66,0x54,0x5f,0x96,0x17,0x36,0x00,0x00,0x00,0x5e,0xca,0xf5,0x2c,0xcb,0xfb,0x96,0xee,0xd5,0xbd,0x06,0xcf,0x4e,0x92,0xe4,0x75,0x27,0xf9,0x7b,0xaf,0xe4,0xba,0xaf,0xbf,0x73,0x2e,0x2d,0xf1,0xf9,0x26,0x79,0x7a,0xff,0x92,0xcf,0x4e,0x92,0x24,0x39,0xe7,0x06,0x00,0x1e,0xca,0x5a,0x14,0x28,0xf9,0x83,0xbc,0xe0,0xc0,0x82,0x05,0xeb,0x0f,0xd6,0xb7,0x37,0xbf,0x6f,0xff,0x78,0x56,0xe3,0x57,0xe7,0xcb,0x78,0x50,0xf2,0xc7,0xda,0x4f,0x4a,0x81,0xf5,0x13,0x3c,0x9f,0x8b,0xe7,0xd9,0xa7,0x6a,0x72,0x87,0xb3,0x35,0xeb,0xf6,0x63,0x2e,0x30,0x54,0xfd,0x72,0x72,0x4e,0x72,0x3e,0xfb,0xb9,0x73,0xd2,0x77,0xee,0x7c,0xf2,0xdc,0x27,0xe7,0xfd,0xe6,0x93,0x7c,0xee,0x9c,0x64,0xfe,0x72,0xfb,0x5d,0xc9,0xbe,0x3a,0x09,0x80,0x05,0xde,0x0b,0xd5,0x7f,0xec,0x19,0x14,0x17,0x4f,0x5f,0x17,0x7f,0xcb,0x45,0x8d,0x01,0x50,0x6f,0x43,0x7e,0xdc,0xee,0x8b,0x93,0xf5,0xa8,0x93,0xf5,0x2d,0xeb,0x9e,0x55,0xe6,0x39,0x87,0xaa,0x7c,0x28,0x55,0xd4,0x5e,0x57,0x2b,0x75,0x6b,0x63,0xba,0xd4,0xef,0xcf,0x70,0x28,0x6a,0xf4,0xe7,0xda,0xe3,0x9a,0x17,0xd9,0xfa,0x9a,0xf5,0xdc,0xfc,0xfe,0xb2,0x3f,0xc9,0xfb,0xfb,0xf4,0x55,0xfb,0x3a,0xbd,0x50,0x57,0xbb,0xaa,0x72,0x74,0x49,0xce,0xa5,0x92,0x2b,0x73,0x9e,0xe7,0x56,0xd7,0x5f,0xf9,0x95,0x5b,0xcf,0x75,0x96,0x77,0x96,0x05,0xe6,0x65,0x9b,0x9f,0xb3,0x77,0xff,0x8e,0xda,0xed,0xdd,0xd7,0xb9,0xae,0xbe,0xbe,0xcf,0x37,0xbf,0x93,0xfd,0xcd,0xbd,0x3f,0xf7,0xba,0xde,0xfa,0x7d,0x96,0x85,0xeb,0xab,0xb7,0xcf,0xed,0x3b,0xfb,0x7e,0xaf,0xae,0xb9,0x73,0x5c,0xf7,0x93,0xef,0xb3,0xdc,0x73,0xc6,0xf5,0xfb,0x5b,0x77,0x15,0x7f,0xf3,0xb7,0xaf,0xeb,0xa6,0x8c,0x35,0x85,0x99,0x61,0x96,0x61,0x72,0x7e,0x49,0x72,0xff,0xdd,0x49,0xee,0xec,0x9c,0x74,0x9e,0xbf,0x3c,0xe9,0x7c,0xee,0x27,0xc9,0x93,0x9d,0x3c,0xb9,0xef,0x24,0x27,0x9f,0x95,0xdc,0xb7,0x05,0xee,0x17,0xee,0xd3,0xf0,0x1d,0x28,0xe0,0x9e,0xc6,0x7e,0x1a,0xf5,0x33,0x7f,0x53,0xc5,0xbd,0xe1,0xfe,0x83,0x3b,0x8d,0x3b,0x7b,0xe9,0xda,0xbb,0xa0,0x6b,0x35,0xdf,0x8b,0xa9,0x73,0xf7,0x5b,0xeb,0xbc,0xdc,0x2f,0x24,0x8d,0x9c,0xa5,0xdc,0x67,0x7d,0x2d,
    0xaf,0xdd,0x17,0x96,0x8b,0xa5,0xbb,0xd0,0x9e,0xd2,0x7d,0xdd,0xbf,0xfb,0xce,0x27,0x39,0x67,0x4e,0x12,0x93,0xdc,0xce,0xf9,0x26,0xfd,0xc9,0x4e,0xae,0xfb,0x73,0x27,0x7f,0xb3,0x93,0xcc,0x7d,0xef,0x84,0xfd,0xe1,0x4e,0xde,0xa6,0xef,0xdd,0xd8,0x3f,0xac,0xcf,0xc0,0x17,0x7b,0xae,0x8b,0xef,0x9f,0x85,0x05,0x4c,0x9c,0xdc,0xe7,0xe9,0x3e,0xf9,0x7e,0xba,0xc3,0x8b,0xef,0x6e,0xfa,0xf3,0xd7,0xdc,0x7f,0x2e,0xfa,0xaf,0x51,0xbb,0x81,0xd3,0x6f,0x72,0xaa,0xbb,0x3e,0xd1,0xe4,0x43,0xa7,0xfc,0x71,0x8f,0x0b,0x3d,0x8b,0xfb,0x7b,0x5d,0xec,0xf7,0x1a,0x70,0x55,0x9e,0xfb,0x73,0xd6,0x4a,0x3e,0xde,0x49,0x7e,0xae,0x2b,0xa9,0xfd,0x3d,0x27,0x65,0x7f,0x7c,0x4b,0x8d,0x86,0xeb,0xa2,0xe4,0xa8,0x81,0xb7,0x37,0x0a,0xd4,0xc2,0x54,0xe3,0xcf,0x1d,0xd8,0x77,0x37,0x55,0xe8,0x2a,0x7c,0xe6,0xde,0x8b,0x6b,0xf3,0xfe,0xde,0xa1,0xab,0x2f,0x1e,0xdf,0x33,0x3e,0xf6,0xc7,0x62,0xee,0x46,0xd5,0xa2,0x55,0xf1,0xdd,0xeb,0xed,0x79,0xf7,0xe2,0xee,0xdf,0x87,0xea,0xbd,0xf9,0xce,0x5f,0xa9,0x0b,0xfd,0x96,0x59,0x9a,0xb2,0x16,0x55,0x46,0x8e,0x9d,0xbf,0x3c,0xeb,0x57,0x39,0x27,0xdf,0x75,0xae,0xcf,0x95,0xbf,0xcf,0xe9,0xfe,0x24,0x27,0xbf,0xd4,0x5f,0x72,0x76,0x92,0xe4,0x79,0x92,0x5f,0x9e,0x0a,0x1a,0xef,0xdf,0xbb,0x38,0xd7,0xbc,0xfc,0x7d,0x2e,0xe5,0x7c,0xf7,0x2a,0xdf,0x73,0x52,0xdc,0x0d,0x1a,0x65,0x16,0xd1,0xfd,0xe7,0x33,0xdf,0xc5,0xb5,0x9f,0x51,0xfd,0xb7,0x6f,0x73,0x9e,0xcf,0xb3,0xfd,0xee,0xab,0xa8,0xea,0x86,0x6e,0xa6,0xde,0x8b,0x64,0xf5,0x57,0x7f,0xbd,0x8a,0xbf,0x5f,0xed,0xbf,0xf2,0x9d,0xfa,0xdb,0x4a,0x2d,0x7c,0xb1,0xc0,0x5a,0xbc,0xd6,0x57,0x72,0x27,0x9f,0x73,0x27,0xeb,0x53,0x4f,0x9e,0x6f,0xae,0x24,0xa7,0xff,0x3e,0x9f,0x64,0x4e,0x3e,0xfb,0xbd,0x3f,0x49,0xee,0xdf,0x93,0xf3,0xfb,0x65,0xbf,0xe7,0xb6,0x91,0x36,0xc8,0xf5,0x72,0xf2,0x49,0x5f,0xd7,0xf7,0xe3,0xea,0x31,0x77,0x5f,0xf3,0xde,0x17,0xe9,0xe0,0xde,0x7e,0xdc,0xb9,0xc2,0xdc,0x9f,0x90,0xf5,0xfc,0x75,0xaf,0x7c,0x73,0x6c,0x7f,0x63,0xad,0x08,0xa5,0x94,0xc9,0x8b,0xdf,0x76,0xf3,0xf4,0x8c,0x66,0xaa,0x31,0x6b,0x09,0x1b,0x7f,0xd7,0x33,0xc3,0x61,0xae,0x5f,0x0f,0xb8,0x94,0x65,0xfd,
    0xea,0x22,0x49,0x92,0x24,0x49,0x7e,0xc9,0x49,0x92,0x5f,0xae,0x3b,0xb9,0x7f,0xd7,0xef,0xe4,0xbe,0x9f,0xeb,0x4e,0x4e,0x92,0xcf,0xfd,0x26,0xc9,0xf9,0x7c,0x6f,0x00,0x78,0xa1,0xbb,0x6d,0xc7,0x5a,0x7b,0xcb,0x5f,0xed,0xba,0x72,0x27,0x5d,0xbf,0xf3,0xd9,0x49,0xae,0xdb,0x2e,0x00,0x18,0xb8,0x72,0xf7,0xd4,0x7d,0x3d,0xbb,0xf6,0xef,0x79,0xde,0xb7,0xfa,0x7e,0x3e,0xef,0x7d,0xde,0xbf,0xfb,0x2f,0xfb,0xfa,0xed,0x7b,0x07,0x00,0x9a,0xd2,0xbc,0x7b,0xa3,0x97,0x97,0xee,0x77,0x03,0x68,0x4c,0xcf,0xea,0xdc,0x2b,0xf9,0x24,0x27,0x49,0xde,0x27,0xc9,0x79,0x72,0x27,0xbf,0xe7,0x49,0x3e,0x77,0xdd,0xf9,0xc9,0xfd,0xbc,0x9d,0xec,0xab,0xeb,0xb9,0x92,0xcf,0xe7,0x05,0x55,0xdd,0xa8,0xb7,0x29,0xdf,0x2f,0xc5,0xf7,0xba,0x98,0xbf,0x3e,0x7a,0xd5,0x2f,0xfa,0x59,0x49,0xaf,0xd4,0x73,0xae,0x7d,0x2f,0x66,0xf2,0xb2,0xa7,0xc3,0xec,0xfa,0x63,0x3c,0x75,0x55,0xcd,0xbb,0xfb,0x52,0xb5,0xea,0xfb,0x4c,0x7f,0xaf,0xbf,0xd7,0xbe,0x3e,0xbe,0xfa,0x61,0x28,0xf8,0x2d,0xec,0xa5,0x79,0xd7,0xda,0x7b,0xfa,0xd3,0x77,0x45,0xee,0xd7,0xac,0x1d,0x56,0x6c,0xf5,0xf7,0xeb,0xeb,0xb9,0xf7,0x47,0x7f,0xce,0x27,0xbd,0x9e,0xfb,0xb3,0xaf,0x2b,0x49,0xba,0xff,0xe6,0xc9,0xc9,0xef,0x24,0x89,0xe4,0x4e,0xea,0x9b,0x3b,0xb9,0x9f,0x60,0x8f,0xb6,0x4a,0x2f,0xda,0x6a,0xf3,0xac,0x36,0x4b,0xc1,0x6a,0x68,0x50,0x0b,0x72,0xe9,0xe5,0xf7,0xd7,0xcb,0xba,0xb2,0xbe,0xcb,0xbe,0xbb,0xd7,0xbb,0x9e,0x65,0xd6,0xbd,0x1b,0xeb,0x82,0xef,0x80,0x4b,0xf3,0xbb,0xfb,0x5d,0x6b,0xf5,0x35,0x6d,0x6a,0xac,0x6b,0xf5,0x2c,0x2f,0xbc,0xbe,0xd7,0x52,0xf5,0x2d,0xd8,0x47,0xe3,0xd6,0x68,0x77,0xdb,0x3e,0xc5,0xf9,0x5b,0xda,0x39,0xac,0xd5,0x97,0x4f,0xdb,0xf6,0xe7,0xd7,0xf7,0xdc,0x27,0x75,0xbe,0xa9,0xa4,0xbb,0x2b,0xb9,0xae,0x82,0x51,0x57,0x7f,0xe7,0xd4,0xba,0x46,0x95,0xf5,0xfd,0x96,0xeb,0x5a,0x9f,0x7b,0x76,0x7f,0x97,0xd2,0xf6,0x60,0x66,0x6d,0xcc,0xdc,0xba,0xf6,0xcf,0xd5,0x6b,0x9e,0xba,0xae,0xb5,0xaa,0xba,0xdf,0xb7,0xce,0xba,0xee,0xac,0x19,0xfd,0xae,0x8f,0xeb,0xef,0x4f,0x31,0xf3,0xb7,0x59,0xef,0xfe,0x74,0xcf,0xde,0xb5,0xfa,0xfc,0x7d,0xaa,0xd7,0xf7,0x54,0x5d,0xd7,0xf9,0xd6,0xbe,0x56,
    0x3d,0x77,0x9e,0xbe,0x77,0x8e,0xf7,0x7e,0x53,0xbc,0xef,0x67,0xb3,0x66,0xee,0x39,0xe5,0xfc,0xfd,0xfd,0x95,0xac,0xf3,0xaa,0xbc,0x57,0x58,0xf9,0x64,0xea,0x3d,0x2b,0xef,0xfe,0xfb,0xfb,0xde,0x39,0xcf,0x55,0x7d,0x4e,0xe5,0xd9,0xe7,0xbc,0x0a,0xf4,0x05,0x97,0x82,0x2e,0xdc,0xaf,0xe2,0xbe,0x35,0x42,0x57,0x81,0x53,0x70,0x8f,0x52,0x9f,0x8f,0x62,0xbe,0xa5,0x5c,0xbb,0xf0,0xf7,0x41,0xdb,0xae,0x75,0x7d,0x83,0x07,0xf6,0xbe,0x1f,0xd2,0x57,0x55,0xd5,0x77,0xa6,0xca,0x53,0x9f,0xaa,0xfa,0x3d,0xca,0x83,0x5d,0xbf,0x5f,0xfb,0x5d,0xdf,0xf3,0x47,0xad,0x39,0x77,0x55,0x38,0x55,0x9f,0x24,0xb9,0x7f,0x27,0x79,0xf3,0xfb,0x24,0xc9,0xe7,0x93,0x7c,0x2b,0x4f,0xf2,0xa4,0x92,0xbc,0xb9,0x93,0x7c,0x3e,0x49,0x32,0xdf,0x24,0x79,0xbe,0x41,0x83,0xfd,0xf8,0x51,0xd5,0xa8,0x6a,0x74,0xe0,0xba,0x00,0x68,0xa0,0xbd,0x1c,0xeb,0xcb,0xdf,0x3d,0x3f,0xd6,0xaa,0x2f,0x53,0x4f,0xf3,0xbb,0x16,0x26,0x70,0x7f,0xe1,0x7b,0xe0,0x3b,0x86,0xd5,0xef,0x8f,0xf6,0x6e,0xde,0x99,0x61,0x1d,0x8b,0xe5,0xa0,0x34,0x66,0xe0,0xef,0x86,0xf5,0xe7,0x2f,0xc9,0xf5,0xf7,0x4b,0x12,0xd7,0x4a,0x72,0x5d,0x9f,0x2b,0xf9,0x9c,0xfb,0x24,0xc9,0xdc,0xc9,0x39,0x27,0x49,0xae,0xf3,0x49,0xce,0xef,0x2f,0x49,0x34,0x58,0x0b,0x14,0x14,0x00,0x00,0x00,0x50,0xf8,0xdd,0xa9,0xda,0x73,0x3f,0xac,0xed,0xb0,0x07,0xa6,0x60,0xd3,0xf0,0xfc,0x30,0x6f,0x51,0xfb,0x0f,0xf3,0xa5,0xf6,0xf7,0x85,0xec,0x07,0x7b,0xcf,0x66,0xaa,0x8b,0xf1,0x69,0xaa,0xaa,0xb1,0xf7,0xa6,0xde,0x07,0x73,0x7f,0x4e,0x4e,0xee,0xe7,0x7c,0x92,0x3c,0xcf,0xe7,0x9b,0xe4,0x7e,0x92,0x93,0xfb,0x77,0x27,0xdf,0xec,0x4f,0x92,0x3c,0x4f,0x72,0xf2,0x97,0xdc,0xe7,0xca,0x7b,0x53,0x86,0x02,0x7b,0x6b,0xee,0x17,0x9e,0x1b,0xf6,0x0d,0x0a,0x00,0x05,0x55,0xf9,0x30,0xfb,0x13,0x96,0xda,0x74,0xcd,0xf0,0xe9,0x1e,0xea,0xd7,0x17,0xb5,0xbb,0xe1,0x6a,0x54,0xe8,0xa1,0xf4,0xaa,0xc1,0x5a,0xf3,0x87,0x5e,0x94,0x7e,0x9b,0xe5,0xfa,0xc2,0xba,0x28,0x5f,0xba,0xe6,0xfb,0x6b,0xbb,0xbe,0x77,0x5f,0xf7,0x9d,0xf4,0x9d,0x9d,0xec,0xe4,0x7c,0x4e,0x92,0xe4,0x49,0x92,0x9d,0xe4,0x9c,0xfd,0xc4,0x9d,0xa9,0x28,0x16,0x53,0xb9,0xae,0x27,0x27,0x7b,0xa9,
    0x3b,0x77,0xe3,0x7a,0x41,0x43,0x83,0x6e,0xaa,0xce,0x02,0x17,0x5b,0x72,0x3d,0xfd,0xf1,0x59,0xf6,0xaa,0x5f,0xa3,0x0f,0x74,0x43,0x37,0xe5,0x6a,0xa6,0xae,0x0b,0xe5,0x8b,0xd2,0x6b,0x69,0xae,0xd6,0x2c,0x6a,0x0a,0x2c,0x58,0x4d,0xd5,0x5a,0xf2,0xa8,0xaf,0x9c,0x24,0x39,0xa7,0x93,0xe7,0xdc,0xdf,0x3c,0xc9,0xda,0xf9,0x24,0x39,0xcf,0x9d,0xfb,0x93,0xe7,0x7b,0xa7,0xf3,0xf7,0x4b,0xf2,0xdc,0x3b,0x79,0x3e,0x4f,0x92,0xeb,0xfd,0xab,0xd4,0xe3,0xfa,0x4e,0xfd,0xf6,0xd5,0x85,0x73,0x95,0xaa,0x7d,0xd8,0xb5,0x37,0x55,0x6b,0x51,0xa3,0x99,0x01,0xcb,0x65,0xbf,0x7d,0xfe,0x6a,0x3f,0x87,0x31,0x17,0x65,0xf6,0xfb,0x61,0xef,0x75,0xb3,0xf7,0x75,0x28,0xdd,0xb8,0x57,0xe3,0xeb,0x2a,0xfb,0x70,0xcf,0x7d,0x5b,0x7c,0x63,0x18,0x8b,0x66,0xad,0xf6,0xce,0x77,0x98,0xbf,0x5e,0x7c,0xd7,0x85,0xfd,0xfb,0x8e,0xf7,0xce,0xb6,0x9f,0x3c,0x9f,0x0f,0x75,0xcb,0xfa,0x4b,0xaf,0xeb,0xf3,0xcd,0xa9,0x2b,0x57,0x72,0xf5,0x77,0x25,0x89,0xd9,0x91,0xf8,0xbb,0x9b,0x66,0x99,0xaf,0x3e,0xf7,0x31,0xcc,0xef,0x32,0xbd,0xd6,0xe1,0xbb,0xde,0xe1,0xe7,0x1d,0xf8,0x4e,0xa3,0x80,0x87,0x56,0x67,0xf9,0xfc,0xd5,0xbc,0xcd,0x3e,0xf6,0xe3,0x7d,0x39,0xbd,0x0e,0xb5,0xdf,0x07,0xf5,0xdd,0xd7,0x62,0x01,0x77,0x8b,0x49,0xaf,0x24,0xfb,0xba,0xe4,0x4c,0xfd,0xdd,0xd7,0xb7,0xd4,0xba,0xfb,0xc7,0xa4,0x3e,0xf0,0x97,0xd5,0xb1,0xf3,0xed,0x3b,0xf9,0xf2,0x1c,0xd9,0xbf,0x7c,0xef,0xdc,0xf5,0x77,0x3e,0xe7,0xd9,0xef,0xe7,0x77,0x76,0x7e,0x4f,0x4e,0xee,0xcf,0xe7,0xec,0xb9,0x73,0xde,0xf7,0x6f,0x5f,0xf9,0x5d,0xbb,0xf2,0x18,0x85,0x3d,0xdf,0xbe,0xf6,0xd3,0xcb,0xdf,0xde,0x8d,0xbb,0xba,0x17,0xb4,0xb1,0xae,0x56,0xcd,0x1f,0x0b,0x50,0xf5,0x9b,0x9e,0xde,0xb3,0xfa,0xb9,0xae,0xa9,0xfd,0xeb,0xe6,0xae,0xbe,0x2e,0x83,0xfd,0xd6,0x75,0x5a,0xf5,0xac,0x0f,0x2f,0xf0,0x2d,0xd7,0xee,0xeb,0xfb,0x9c,0xdf,0xb5,0xd6,0xf7,0xf9,0x5e,0xd6,0xf5,0xdb,0x6d,0xf9,0x5e,0x55,0x6d,0xaf,0xea,0x42,0x3d,0xdf,0x6c,0xb3,0xaf,0x63,0xe5,0xca,0x7d,0xae,0x7a,0x3a,0x39,0x95,0xeb,0x93,0x24,0xb9,0x92,0xe4,0x4a,0x92,0x5c,0x27,0x49,0xce,0x95,0x24,0xf9,0x24,0xc9,0x75,0x25,0x69,0x0b,0x6a,0x68,0x05,0xaa,0x40,0x81,
    0x82,0x2a,0x30,0x00,0xae,0x6b,0x6a,0x53,0x7f,0x2c,0x80,0x0d,0x05,0xaa,0x60,0x17,0xdc,0x2f,0x80,0xbd,0xba,0xf6,0x59,0x2f,0xf5,0x9a,0x0d,0x06,0x36,0xd8,0xc0,0x40,0x6d,0xd8,0x1b,0x7f,0xa7,0x6a,0xef,0x4a,0xf4,0xde,0xf7,0xcd,0xbe,0x72,0xeb,0xbf,0x27,0xd9,0xf7,0xb9,0x72,0xdf,0xfb,0x73,0xee,0xfb,0xce,0xe7,0xba,0x7f,0xd6,0xbb,0x13,0xdf,0x59,0xcb,0x77,0x5d,0xa3,0x9b,0x81,0x3a,0x7c,0xdc,0xe8,0x9e,0x8d,0xde,0x05,0xb8,0x28,0x30,0xae,0xdf,0x37,0x9f,0xdd,0xab,0x4d,0x81,0x97,0x8f,0xf9,0xc3,0xb7,0x37,0xdd,0x6f,0x35,0xed,0xb2,0x28,0xf8,0xce,0x5b,0xa7,0x5a,0xd1,0x6d,0xba,0x99,0x9f,0xae,0x5e,0x2f,0x6b,0xfd,0xd1,0xbd,0xe8,0x6e,0x7b,0xf7,0x37,0x4f,0x5f,0xe4,0x2f,0xc9,0x79,0x9f,0x7c,0xeb,0x24,0x5f,0xea,0xf4,0x75,0xf1,0xc9,0xf5,0xc9,0x2f,0xb9,0xce,0xdf,0x5f,0x72,0x4e,0x92,0xe4,0x38,0xc9,0x95,0x92,0x5c,0xef,0x67,0xd5,0x7b,0xde,0xbd,0xc8,0xc5,0x8c,0x85,0x33,0x73,0x02,0x77,0xa8,0x02,0x34,0x1b,0xf8,0xad,0xeb,0xc9,0xe7,0x9a,0xad,0xbe,0x17,0xbf,0xb7,0x71,0x7f,0xcf,0x9c,0x97,0xe5,0x1c,0xf6,0x5e,0x0d,0xb0,0x01,0xb3,0xbb,0xcd,0x7c,0x40,0xdd,0x7f,0x0b,0xf3,0x79,0x77,0xfd,0x58,0xd5,0x85,0xe9,0x0b,0x95,0x82,0x13,0xf6,0x21,0x9f,0x3b,0xec,0x9d,0x3c,0x7e,0x39,0xe7,0xfc,0xf6,0x2f,0x9f,0xfb,0xfe,0xab,0x5c,0x77,0x72,0xae,0x4e,0x92,0x1c,0x2a,0x6f,0x74,0xf6,0xa1,0xe7,0xee,0x02,0x7e,0x17,0x5c,0x1f,0x5d,0xd5,0xdd,0xaa,0x70,0xd5,0xc0,0x06,0x07,0xa0,0xe7,0x5c,0xe8,0x55,0xf5,0xb9,0x9a,0xba,0xd6,0x4b,0xf5,0x75,0x28,0xfd,0x54,0x0d,0x38,0xd0,0x40,0xe9,0x05,0xae,0xab,0xbc,0xeb,0xa8,0xaa,0x59,0xc7,0x30,0xaf,0x69,0xf5,0xcc,0x1f,0xf8,0x4b,0x8e,0x5b,0x6e,0x57,0x25,0xe1,0x4e,0xb2,0x2b,0x49,0x92,0x24,0xb9,0xef,0x24,0x79,0x9e,0xdc,0xc9,0xe7,0xc9,0x9d,0x7c,0x4e,0x92,0xd4,0x24,0xc9,0x7d,0x07,0x55,0xb0,0xc1,0x39,0x70,0x0e,0xbc,0x81,0x3d,0x50,0x03,0x36,0x00,0x55,0x00,0xd4,0x0d,0xcf,0x0f,0xfe,0x16,0xcc,0x0d,0x7b,0xc3,0xfd,0x07,0x00,0x8d,0x29,0xa8,0x06,0x00,0x8d,0xa5,0x99,0x82,0x73,0xa0,0x5b,0x25,0xab,0x6b,0x92,0xee,0x4a,0xf2,0xf5,0x4b,0xf2,0x95,0x3b,0x79,0x3e,0xf7,0xd9,0xbb,0x7f,0x27,0x79,0xf2,0x8d,0xe4,0xfe,
    0x3c,0x77,0xee,0xee,0x1a,0x96,0x19,0x80,0xfa,0x5b,0xb0,0xc0,0x4b,0x37,0x00,0xcc,0x00,0x36,0xd6,0x46,0x77,0x35,0x7f,0x7f,0x0b,0xd7,0xeb,0x6e,0x73,0x5f,0xba,0x67,0x8a,0xde,0x03,0xb5,0x01,0x9b,0x6b,0xcd,0xa6,0x69,0xde,0xcf,0x17,0xf7,0xe3,0xf0,0xfe,0x75,0xad,0x75,0xbf,0xc5,0x72,0x0b,0xa9,0xd5,0xfa,0xbe,0xcf,0x37,0x49,0x3e,0xbf,0x24,0xa9,0xfd,0x24,0x99,0xfd,0x24,0xc9,0xfd,0xdb,0xc9,0xa9,0xf3,0x97,0xec,0x27,0x9f,0x2b,0xfd,0xb9,0x3e,0xbf,0x5c,0xfc,0x7d,0xbe,0x0b,0x50,0x05,0x0e,0x80,0x02,0x00,0x30,0x00,0x98,0x84,0xbf,0x3a,0x87,0xa2,0xa0,0xb1,0x0a,0x56,0x0d,0x6a,0x57,0xb1,0x3e,0x4b,0xc1,0x6d,0xd6,0x1f,0xcc,0x0b,0xe7,0x5a,0xf8,0x5c,0x0b,0x7e,0xef,0x45,0x9d,0xfa,0x72,0x2d,0x7b,0xbb,0x9f,0x3d,0xaf,0x9d,0x3c,0xf3,0x97,0x24,0xcf,0x93,0x24,0xf5,0x4b,0x92,0x24,0x49,0xee,0x24,0xc9,0x93,0x24,0xf9,0x7c,0x92,0xe4,0xef,0x49,0x92,0x4a,0x92,0xcc,0x37,0xd0,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x1d,0xd0,0xb0,0x5e,0x58,0x0b,0xd6,0x82,0xb5,0x60,0x06,0xf6,0x06,0x07,0xd6,0x82,0xf3,0x02,0x70,0x81,0x05,0x66,0xe0,0xfb,0xc2,0x19,0xf8,0xfc,0xf9,0xff,
};
#endif // End of #if(_FACTORY_ONE_PIECE_MARK_SUPPORT == _ON)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void RTDFactoryOsdFuncDisableOsd(void);
void RTDFactoryOsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
//void RTDFactoryOsdLoadHardwareVLCFont(BYTE *pucArray, WORD usOffset, WORD usFontTableStart, bit bOsdRotate);
void RTDFactoryOsdFuncClearOsdFont(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucChar);
void RTDFactoryOsdFuncPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE *pucFontTable, BYTE *pucArray, BYTE ucLanguage);
BYTE RTDFactoryOsdFuncGetOsdFontPointer(BYTE ucPointerSelect);
BYTE RTDFactoryOsdFuncSetOsdFontPointer(BYTE ucPointerSelect, BYTE ucPointer);
void RTDFactoryOsdFuncDrawWindow(BYTE *pucArray, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
void RTDFactoryOsdFuncEnableOsd(void);
void RTDFactoryOsdFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint);
void RTDFactoryOsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void RTDFactoryOsdFuncSelectItem(WORD usOsdState);
WORD RTDFactoryDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
void RTDFactoryOsdDispNumber(WORD usOsdState, WORD usValue);
void RTDFactoryOsdFuncSetPosition(BYTE ucType, WORD usX, WORD usY);
void RTDFactoryOsdChangColorTemp(BYTE ucColorTemp);
void RTDFactoryPanelUsedTimer(void);

#if(_FACTORY_ONE_PIECE_MARK_SUPPORT == _ON)
void RTDFactoryOnePieceMark(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// OSD Factory Function
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncDisableOsd(void)
{
    SET_OSD_STATE(_MENU_NONE);
    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
    ScalerOsdDisableOsd();
    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    BYTE ucI = 0;
    BYTE ucTemp = 0x11;

#if 0// (_OSD_ROTATE_FUNCTION == _ON)
    if(GET_OSD_ROTATE_STATUS() == _TRUE)
    {
        ucI = ucWidth;
        ucWidth = ucHeight;
        ucHeight = ucI;
        ucTemp = 0x58;
    }
#endif
    // Row Command
    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTemp, ucWidth);
    }

    // Row Command end
    ScalerOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);

    ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // Character Command initial
#if 0// (_OSD_ROTATE_FUNCTION == _ON)
    if(GET_OSD_ROTATE_STATUS() == _TRUE)
    {
        ucTemp = 0x8e;
    }
    else
#endif
    {
        ucTemp = 0x4C;
    }

    ScalerOsdCharCommandByteSeries(g_usFontSelectStart, _OSD_BYTE0, ucTemp, (WORD)ucWidth * ucHeight);   // 1bit, width 12pixels
    ScalerOsdCharCommandByteSeries(g_usFontSelectStart, _OSD_BYTE1, 0, (WORD)ucWidth * ucHeight);      // char initial
    ScalerOsdCharCommandByteSeries(g_usFontSelectStart, _OSD_BYTE2, ucColor, (WORD)ucWidth * ucHeight);  // color initial

    g_ucOsdWidth = ucWidth;
    g_ucOsdHeight = ucHeight;
}

//--------------------------------------------------
// Description  : Osd Load Hardware VLC Font
// Input Value  :
// Output Value :
//--------------------------------------------------
/*
void RTDFactoryOsdLoadHardwareVLCFont(BYTE *pucArray, WORD usOffset, WORD usFontTableStart, bit bOsdRotate)
{
    WORD usNum = 0;

    if(bOsdRotate == _TRUE)
    {
        usNum = 0x85;
    }

    // rotation
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE2, usNum);

    // osd compression
    ScalerOsdAddrMsb(0xC0);
    ScalerOsdAddrLsb(0x05);
    ScalerOsdBurstWriteDataPort(pucArray, 8, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);

    usNum = ((WORD) * (pucArray + 8) << 8) | *(pucArray + 9);

    usOffset = usOffset * 9;
    usOffset += usFontTableStart;

    // osd compression enable
    ScalerOsdFrameControlByte(0x007, _OSD_BYTE2, 0x01);

    // Osd load font > 12K
    if(usOffset > 4095)
    {
        ScalerOsdScrambleLoadFontAddrHsbSet();
    }
    else
    {
        ScalerOsdScrambleLoadFontAddrHsbClr();
    }

    pucArray += 10;

    ScalerOsdAddrMsb((HIBYTE(usOffset) & 0x000f) | 0xd0);
    ScalerOsdAddrLsb(LOBYTE(usOffset));
    ScalerOsdBurstWriteDataPort(pucArray, usNum, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_FLASH);

    // For osd load font > 12K !!
    ScalerOsdScrambleLoadFontAddrHsbClr();
    ScalerOsdFrameControlByte(0x007, _OSD_BYTE2, 0x00);
    ScalerOsdFrameControlByte(0x003, _OSD_BYTE2, (BYTE)bOsdRotate);
}
*/
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncClearOsdFont(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucChar)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;

#if 0 // (_OSD_ROTATE_FUNCTION == _ON)
    BYTE ucWidthCount = 0;

    if(GET_OSD_ROTATE_STATUS() == _ON)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x8E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, ucChar, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4C, ucWidth);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, ucChar, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncClearOsdFontAll(void)
{
    RTDFactoryOsdFuncClearOsdFont(0, 0, _FACTORY_OSD_COL, _FACTORY_OSD_ROW, __);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncPutStringProp(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE *pucFontTable, BYTE *pucArray, BYTE ucLanguage)
{
    bit bEndFlag = 0;
    BYTE pucTemp[27] = {0};


    memset(pData, 0x00, _DATA_ITEM_LENGTH);
    while(ucLanguage != 0)
    {
        if(*pucArray == _END_)
        {
            ucLanguage--;
        }
        pucArray++;
    }

    PDATA_WORD(5) = RTDFactoryOsdFuncGetOsdFontPointer(ucFptsSelect);

    // reorder
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT6);
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~(_BIT7 | _BIT5)));

    while(*(pucArray + pData[0]) != _END_)
    {
        switch(*(pucArray + pData[0]))
        {
            case _END_:
                bEndFlag = 1;
                break;

            default:

                pData[1] = *(pucArray + pData[0]);

                if(pucFontTable == tFONT_FACTORY_EUROPE)
                {
                    pData[2] = tOSD_FACTORY_CHARWIDTH_EUROPE[pData[1]][1];
                }
                else
                {
                    pData[2] = 12;
                }
                pData[0]++;
                break;
        }

        if(pData[3] == 0)
        {
            pData[3] = pData[2];
        }

        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);    // first bits shift direction: left shift
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2)); // left bits shift direction: rigth shift
        SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pData[2] - pData[3]) << 4) | pData[3]); // first bits shift and second bits shift

        pData[4] = pData[0];
        pData[5] = pData[3];

        for(pData[7] = 0; pData[7] < 9; pData[7]++)
        {
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0); // restart from last three bytes

            PDATA_WORD(6) = pData[1] * 27 + pData[7] * 3;

            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6)));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 1));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 2));

            pData[0] = pData[4];
            pData[3] = pData[5];


            if((pData[3] == 12) || (*(pucArray + pData[0]) == _END_))
            {
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
            }
            else
            {
                pData[6] = *(pucArray + pData[0]);
                pData[2] = tOSD_FACTORY_CHARWIDTH_EUROPE[pData[6]][1];
                pData[0] ++;

                PDATA_WORD(6) = pData[6] * 27 + pData[7] * 3;

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 2));

                pData[3] += pData[2];
            }

            while((pData[3] < 12) && (*(pucArray + pData[0]) != _END_))
            {
                SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pData[3] << 4) | pData[3]); // third bits shift and left bits shift

                switch(*(pucArray + pData[0]))
                {
                    case _END_:
                        bEndFlag = 1;
                        break;

                    default:
                        pData[6] = *(pucArray + pData[0]);

                        if(pucFontTable == tFONT_FACTORY_EUROPE)
                        {
                            pData[2] = tOSD_FACTORY_CHARWIDTH_EUROPE[pData[6]][1];
                        }
                        else
                        {
                            pData[2] = 12;
                        }
                        pData[0] ++;
                        break;
                }

                pData[3] += pData[2];

                PDATA_WORD(6) = pData[6] * 27 + pData[7] * 3;

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(6) + 2));
            }

            pucTemp[pData[7] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucTemp[pData[7] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucTemp[pData[7] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
        }

        if(pData[3] <= 12)
        {
            pData[3] = 0;
        }
        else
        {
            pData[3] = pData[3] - 12;
            pData[0]--;
        }

        // Write the pro font data to sram
        // COsdFxLoadFontDataAddrCal(PDATA_WORD(5));
        if((ucFptsSelect >= _PFONT_FACTORY_PAGE_ITEM_1) && (ucFptsSelect < _PFONT_FACTORY_PAGE_ITEM_END))
        {
            // select 1bit font form 256-511
            PDATA_WORD(7) = ((WORD)PDATA_WORD(5) + 0x100) * 9;
        }
        else
        {
            PDATA_WORD(7) = (WORD)PDATA_WORD(5) * 9;
        }
        PDATA_WORD(7) += g_usFontTableStart;

#if 0// (_OSD_ROTATE_FUNCTION == _ON)
        if(GET_OSD_ROTATE_STATUS() == _TRUE)
        {
            ScalerOsdFrameControlByte(0x003, _OSD_BYTE2, 0x85);
            ScalerOsdFrameControlByte(0x007, _OSD_BYTE2, 0x03);
        }
        else
#endif
        {
            ScalerOsdFontRotateCtrl(_OSD_ROTATE_DEGREE_0, _DISABLE, _DISABLE);
            ScalerOsdCompressionCtrl(_OSD_DECODE_COMPRESSED, _OSD_COMPRESSION_DISABLE);
        }

        if(PDATA_WORD(7) > 4095)
        {
            ScalerOsdScrambleLoadFontAddrHsbSet();
        }
        else
        {
            ScalerOsdScrambleLoadFontAddrHsbClr();
        }

        ScalerOsdAddrSet(_OSD_SRAM, _OSD_BYTEALL, PDATA_WORD(7), _DISABLE);

        ScalerOsdBurstWriteDataPort(pucTemp, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

        // OSD HW needs time to process it and then write decompressed data into SRAM.
        // The value 1ms is enough at all.
        ScalerTimerDelayXms(1);

        ScalerOsdBurstWriteDataPort(pucTemp, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

        // OSD HW needs time to process it and then write decompressed data into SRAM.
        // The value 1ms is enough at all.
        ScalerTimerDelayXms(1);

        ScalerOsdCompressionCtrl(_OSD_DECODE_COMPRESSED, _OSD_COMPRESSION_DISABLE);

#if 0// (_OSD_ROTATE_FUNCTION == _ON)
        if(GET_OSD_ROTATE_STATUS() == _TRUE)
        {
            ScalerOsdFrameControlByte(0x003, _OSD_BYTE2, 0x01);
        }
#endif
        ScalerOsdScrambleLoadFontAddrHsbClr();

#if 0// (_OSD_ROTATE_FUNCTION == _ON)
        if(GET_OSD_ROTATE_STATUS() == _TRUE)
        {
            PDATA_WORD(7) = (WORD)(g_ucOsdHeight - 1 - ucCol - pData[8]) * g_ucOsdWidth + ucRow;
        }
        else
#endif
        {
            PDATA_WORD(7) = (WORD)ucRow * g_ucOsdWidth + ucCol + pData[8];
        }
        if((ucFptsSelect >= _PFONT_FACTORY_PAGE_ITEM_1) && (ucFptsSelect < _PFONT_FACTORY_PAGE_ITEM_END))
        {
            // select 1bit font form 256-511
            ScalerOsdCommandByte(PDATA_WORD(7) + g_usFontSelectStart, _OSD_BYTE0, 0x6C);
        }
        else
        {
            ScalerOsdCommandByte(PDATA_WORD(7) + g_usFontSelectStart, _OSD_BYTE0, 0x4C);
        }

        ScalerOsdCommandByte(PDATA_WORD(7) + g_usFontSelectStart, _OSD_BYTE1, PDATA_WORD(5));
        pData[8] ++; // Record the length of prop string

        // Increase the sram address pointer
        PDATA_WORD(5) = RTDFactoryOsdFuncSetOsdFontPointer(ucFptsSelect, PDATA_WORD(5));
    }// End of while(*(pucArray + stringcnt) != _END_)

    if(ucFptsSelect == _PFONT_FACTORY_PAGE_0)
    {
        g_ucFontPointer0 = PDATA_WORD(5);
    }
    else if((ucFptsSelect == _PFONT_FACTORY_PAGE_1))
    {
        g_ucFontPointer1 = PDATA_WORD(5);
    }
    else if((ucFptsSelect >= _PFONT_FACTORY_PAGE_ITEM_1) && (ucFptsSelect <= _PFONT_FACTORY_PAGE_ITEM_30))
    {
        g_ucFontPointer2 = PDATA_WORD(5);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE RTDFactoryOsdFuncGetOsdFontPointer(BYTE ucPointerSelect)
{
    BYTE ucPointer = 0;

    if(ucPointerSelect == _PFONT_FACTORY_PAGE_0)
    {
        ucPointer = g_ucFontPointer0;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_1)
    {
        ucPointer = g_ucFontPointer1;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_1)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_1_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_2)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_2_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_3)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_3_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_4)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_4_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_5)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_5_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_6)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_6_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_7)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_7_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_8)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_8_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_9)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_9_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_10)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_10_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_11)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_11_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_12)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_12_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_13)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_13_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_14)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_14_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_15)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_15_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_16)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_16_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_17)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_17_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_18)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_18_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_19)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_19_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_20)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_20_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_21)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_21_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_22)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_22_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_23)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_23_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_24)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_24_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_25)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_25_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_26)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_26_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_27)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_27_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_28)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_28_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_29)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_29_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_30)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_30_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_31)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_31_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_32)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_32_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_33)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_33_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_34)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_34_START;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_35)
    {
        g_ucFontPointer2 = _FACTORY_ITEM_35_START;
        ucPointer = g_ucFontPointer2;
    }

    return ucPointer;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE RTDFactoryOsdFuncSetOsdFontPointer(BYTE ucPointerSelect, BYTE ucPointer)
{
    ucPointer++;

    if(ucPointerSelect == _PFONT_FACTORY_PAGE_0)
    {
        if(ucPointer >= _FACTORY_PAGE_0_END)
        {
            ucPointer = _FACTORY_PAGE_0_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_1)
    {
        if(ucPointer >= _FACTORY_PAGE_1_END)
        {
            ucPointer = _FACTORY_PAGE_1_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_1)
    {
        if(ucPointer >= _FACTORY_ITEM_1_END)
        {
            ucPointer = _FACTORY_ITEM_1_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_2)
    {
        if(ucPointer >= _FACTORY_ITEM_2_END)
        {
            ucPointer = _FACTORY_ITEM_2_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_3)
    {
        if(ucPointer >= _FACTORY_ITEM_3_END)
        {
            ucPointer = _FACTORY_ITEM_3_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_4)
    {
        if(ucPointer >= _FACTORY_ITEM_4_END)
        {
            ucPointer = _FACTORY_ITEM_4_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_5)
    {
        if(ucPointer >= _FACTORY_ITEM_5_END)
        {
            ucPointer = _FACTORY_ITEM_5_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_6)
    {
        if(ucPointer >= _FACTORY_ITEM_6_END)
        {
            ucPointer = _FACTORY_ITEM_6_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_7)
    {
        if(ucPointer >= _FACTORY_ITEM_7_END)
        {
            ucPointer = _FACTORY_ITEM_7_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_8)
    {
        if(ucPointer >= _FACTORY_ITEM_8_END)
        {
            ucPointer = _FACTORY_ITEM_8_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_9)
    {
        if(ucPointer >= _FACTORY_ITEM_9_END)
        {
            ucPointer = _FACTORY_ITEM_9_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_10)
    {
        if(ucPointer >= _FACTORY_ITEM_10_END)
        {
            ucPointer = _FACTORY_ITEM_10_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_11)
    {
        if(ucPointer >= _FACTORY_ITEM_11_END)
        {
            ucPointer = _FACTORY_ITEM_11_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_12)
    {
        if(ucPointer >= _FACTORY_ITEM_12_END)
        {
            ucPointer = _FACTORY_ITEM_12_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_13)
    {
        if(ucPointer >= _FACTORY_ITEM_13_END)
        {
            ucPointer = _FACTORY_ITEM_13_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_14)
    {
        if(ucPointer >= _FACTORY_ITEM_14_END)
        {
            ucPointer = _FACTORY_ITEM_14_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_15)
    {
        if(ucPointer >= _FACTORY_ITEM_15_END)
        {
            ucPointer = _FACTORY_ITEM_15_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_16)
    {
        if(ucPointer >= _FACTORY_ITEM_16_END)
        {
            ucPointer = _FACTORY_ITEM_16_START;
        }
    }

    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_17)
    {
        if(ucPointer >= _FACTORY_ITEM_17_END)
        {
            ucPointer = _FACTORY_ITEM_17_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_18)
    {
        if(ucPointer >= _FACTORY_ITEM_18_END)
        {
            ucPointer = _FACTORY_ITEM_18_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_19)
    {
        if(ucPointer >= _FACTORY_ITEM_19_END)
        {
            ucPointer = _FACTORY_ITEM_19_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_20)
    {
        if(ucPointer >= _FACTORY_ITEM_20_END)
        {
            ucPointer = _FACTORY_ITEM_20_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_21)
    {
        if(ucPointer >= _FACTORY_ITEM_21_END)
        {
            ucPointer = _FACTORY_ITEM_21_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_22)
    {
        if(ucPointer >= _FACTORY_ITEM_22_END)
        {
            ucPointer = _FACTORY_ITEM_22_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_23)
    {
        if(ucPointer >= _FACTORY_ITEM_23_END)
        {
            ucPointer = _FACTORY_ITEM_23_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_24)
    {
        if(ucPointer >= _FACTORY_ITEM_24_END)
        {
            ucPointer = _FACTORY_ITEM_24_START;
        }
    }

    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_25)
    {
        if(ucPointer >= _FACTORY_ITEM_25_END)
        {
            ucPointer = _FACTORY_ITEM_25_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_26)
    {
        if(ucPointer >= _FACTORY_ITEM_26_END)
        {
            ucPointer = _FACTORY_ITEM_26_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_27)
    {
        if(ucPointer >= _FACTORY_ITEM_27_END)
        {
            ucPointer = _FACTORY_ITEM_27_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_28)
    {
        if(ucPointer >= _FACTORY_ITEM_28_END)
        {
            ucPointer = _FACTORY_ITEM_28_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_29)
    {
        if(ucPointer >= _FACTORY_ITEM_29_END)
        {
            ucPointer = _FACTORY_ITEM_29_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_30)
    {
        if(ucPointer >= _FACTORY_ITEM_30_END)
        {
            ucPointer = _FACTORY_ITEM_30_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_31)
    {
        if(ucPointer >= _FACTORY_ITEM_31_END)
        {
            ucPointer = _FACTORY_ITEM_31_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_32)
    {
        if(ucPointer >= _FACTORY_ITEM_32_END)
        {
            ucPointer = _FACTORY_ITEM_32_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_33)
    {
        if(ucPointer >= _FACTORY_ITEM_33_END)
        {
            ucPointer = _FACTORY_ITEM_33_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_34)
    {
        if(ucPointer >= _FACTORY_ITEM_34_END)
        {
            ucPointer = _FACTORY_ITEM_34_START;
        }
    }
    else if(ucPointerSelect == _PFONT_FACTORY_PAGE_ITEM_35)
    {
        if(ucPointer >= _FACTORY_ITEM_35_END)
        {
            ucPointer = _FACTORY_ITEM_35_START;
        }
    }

    return ucPointer;
}

//--------------------------------------------------
// Description  :
//ucBorderPixel        bit5~3 shadow/border width or 3D button thickness in pixel unit:0~7 1~8 pixel.
//                            bit2~0 shadow/border height  in line unit:0~7 1~8 line.
//
//ucBorderColor      bit7~4 shadow/border/3D button left-top/botton border color
//                           bit3~0 shadow/border/3D button right-botton/top border color
//
//ucWinFuncControl: bit7: blend  0:disable, 1:enable
//                            bit6: gradient 0:disable, 1:enable
//                            bit5: gradient direction  0:H, 1:V
//                            bit4: shadow/border/3D button 0:disable, 1:enable
//                            bit3~1:0~3: shadow type 1~4,  4~5: 3D button1~2, 6:reserved, 7:border.
//
//ucGradientCon0:    bit7: R gradient polarity 0:decrease, 1:increase
//                            bit6: G gradient polarity 0:decrease, 1:increase
//                            bit5: B gradient polarity 0:decrease, 1:increase
//                            bit3~4: gradient level 0~3
//                            bit2: R gradient 0:disable, 1:enable
//                            bit1: G gradient 0:disable, 1:enable
//                            bit0: B gradient 0:disable, 1:enable
//
//ucGradientCon0:    bit7~5 0: 8 level per gradient
//                                       1~7: 1~7 level per gradient
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncDrawWindow(BYTE *pucArray, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor)
{
    BYTE ucIndex = 0;
    BYTE ucBorderPixel = 0;
    BYTE ucBorderColor = 0;
    BYTE ucWinFuncControl = 0;
    BYTE ucGradientCon0 = 0;
    BYTE ucGradientCon1 = 0;

#if 0// (_OSD_ROTATE_FUNCTION == _ON)
    WORD xdata usTemp = 0;
    WORD xdata usTemp1 = 0;

    if(GET_OSD_ROTATE_STATUS() == _ON)
    {
        usTemp  = usXEnd - usXStart;
        usTemp1 = usYEnd - usYStart;

        usXStart = 10 + usYStart;

        if((_FACTORY_OSD_WIDTH + _ROTATE_FACTORY_OSD_WINDOW_OFFSET) > usXEnd)
        {
            usYStart = _FACTORY_OSD_WIDTH + _ROTATE_FACTORY_OSD_WINDOW_OFFSET - usXEnd;
        }
        else
        {
            usYStart = 0;
        }

        usXEnd   = usXStart + usTemp1;
        usYEnd   = usYStart + usTemp;
    }
#endif

    ucIndex = (*(pucArray + 0));
    ucBorderPixel = (*(pucArray + 1));
    ucBorderColor = (*(pucArray + 2));
    ucWinFuncControl = (*(pucArray + 3));
    ucGradientCon0 = (*(pucArray + 4));
    ucGradientCon1 = (*(pucArray + 5));

    if(((ucWinFuncControl & _GRADIENT_ENABLE) == _GRADIENT_DISABLE) ||
       (((ucWinFuncControl & _GRADIENT_ENABLE) == _GRADIENT_ENABLE) &&
        ((ucIndex == _WIN0) ||
         (ucIndex == _WIN5) ||
         (ucIndex == _WIN6) ||
         (ucIndex == _WIN7) ||
         (ucIndex == _WIN8) ||
         (ucIndex == _WIN9))))
    {
        // Windows0,5,6,7,8,9 support gradient function.
        ScalerTimerWaitForEvent(_EVENT_DVS);
        ScalerOsdFrameControlAllByte((0x100 + (((ucIndex & 0x80) >> 7) * 0x100) + ((ucIndex & 0x0f) * 4) + 0), _OSD_WITHOUT_DB, ucBorderPixel, ucBorderColor, ucGradientCon0);
        ScalerOsdFrameControlAllByte((0x100 + (((ucIndex & 0x80) >> 7) * 0x100) + ((ucIndex & 0x0f) * 4) + 1), _OSD_WITHOUT_DB, (((usXStart & 0x0f00) >> 4) | ((usYStart & 0x0f00) >> 8)), (usXStart & 0xff), (usYStart & 0xff));
        ScalerOsdFrameControlAllByte((0x100 + (((ucIndex & 0x80) >> 7) * 0x100) + ((ucIndex & 0x0f) * 4) + 2), _OSD_WITHOUT_DB, (((usXEnd & 0x0f00) >> 4) | ((usYEnd & 0x0f00) >> 8)), (usXEnd & 0xff), (usYEnd & 0xff));
        ScalerOsdFrameControlAllByte((0x100 + (((ucIndex & 0x80) >> 7) * 0x100) + ((ucIndex & 0x0f) * 4) + 3), _OSD_WITHOUT_DB, (ucColor & _BIT5), (ucGradientCon1 | (ucColor & 0x1f)), (ucWinFuncControl | _BIT0));
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryOsdFuncEnableOsd(void)
{
    ScalerOsdEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = 0;
    BYTE pucDataSN[7] = {0};

    pucDataSN[0] = (_0__ + (ulValue / 100000));
    pucDataSN[1] = (_0__ + (ulValue % 100000 / 10000));
    pucDataSN[2] = (_0__ + (ulValue % 10000) / 1000);
    pucDataSN[3] = (_0__ + (ulValue % 1000) / 100);
    pucDataSN[4] = (_0__ + (ulValue % 100) / 10);
    pucDataSN[5] = (_0__ + (ulValue % 10));

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(pucDataSN[ucIndex] != _0__)
        {
            ucIndex = 6 - ucIndex;
            break;
        }
    }

    if((ulValue == 0) && (((bit)(ucPar & _BIT1)) == _FORCE_SHOW_NUMBER_OFF))//
    {
        ucIndex = 1;//show "0"
    }
    //Get show number of numeric
    if((bit)(ucPar & _BIT1) == _FORCE_SHOW_NUMBER_ON)//Show all
    {
        ucTemp = ((ucPar & (_BIT4|_BIT5|_BIT6)) >> 4)+1;
        ucIndex = ((ucPar & (_BIT4|_BIT5|_BIT6)) >> 4)+1;
    }
    else
    {
        ucTemp = (ucPar & ((_BIT4|_BIT5|_BIT6)) >> 4)+1;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;
        }
    }

    for(ulValue = 0; ulValue < ucTemp; ulValue++)
    {
        if(ucIndex >= (ucTemp-ulValue))
        {
            pucDataSN[ulValue] = pucDataSN[(6- ucTemp) + ulValue];
        }
        else
        {
            pucDataSN[ulValue] = __; // Space
        }
    }
    if(ucIndex <= 1)
    {
        pucDataSN[ulValue] = __;
        ulValue++;
    }
    pucDataSN[ulValue] = _END_;

    // Align Right
    if((bit)(ucPar & _BIT0) == _ALIGN_RIGHT)
    {
        RTDFactoryOsdFuncPutStringProp(ucRow, (ucCol-2), ucFontPoint, tFONT_FACTORY_EUROPE, &pucDataSN[0], _ENGLISH);
    }
    else
    {
        RTDFactoryOsdFuncPutStringProp(ucRow, ucCol, ucFontPoint, tFONT_FACTORY_EUROPE, &pucDataSN[0], _ENGLISH);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;

#if 0// (_OSD_ROTATE_FUNCTION == _ON)
    BYTE ucWidthCount = 0;

    if(GET_OSD_ROTATE_STATUS() == _ON)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x8E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            // ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4C, ucWidth);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncSelectItem(WORD usOsdState)
{
    WORD usOsdItem = 0;
    if(g_ucFactoryPage == 0)
    {
        usOsdItem = GET_OSD_STATE() - _MENU_FACTORY_AUTOCOLOR;
        RTDFactoryOsdFuncChangeColor1Bit(tFACTORY_PAGE_SELECT_ITEM_TABLE[usOsdItem][0], tFACTORY_PAGE_SELECT_ITEM_TABLE[usOsdItem][1], tFACTORY_PAGE_SELECT_ITEM_TABLE[usOsdItem][2], 1, COLOR(_CP_WHITE, _CP_BG));

        usOsdItem = usOsdState - _MENU_FACTORY_AUTOCOLOR;
        RTDFactoryOsdFuncChangeColor1Bit(tFACTORY_PAGE_SELECT_ITEM_TABLE[usOsdItem][0], tFACTORY_PAGE_SELECT_ITEM_TABLE[usOsdItem][1], tFACTORY_PAGE_SELECT_ITEM_TABLE[usOsdItem][2], 1, COLOR(_CP_RED, _CP_BG));
    }
    else if(g_ucFactoryPage == 1)
    {
        usOsdItem = GET_OSD_STATE() - _MENU_FACTORY_BG;
        RTDFactoryOsdFuncChangeColor1Bit(tFACTORY_PAGE_1_SELECT_ITEM_TABLE[usOsdItem][0], tFACTORY_PAGE_1_SELECT_ITEM_TABLE[usOsdItem][1], tFACTORY_PAGE_1_SELECT_ITEM_TABLE[usOsdItem][2], 1, COLOR(_CP_WHITE, _CP_BG));

        usOsdItem = usOsdState - _MENU_FACTORY_BG;
        RTDFactoryOsdFuncChangeColor1Bit(tFACTORY_PAGE_1_SELECT_ITEM_TABLE[usOsdItem][0], tFACTORY_PAGE_1_SELECT_ITEM_TABLE[usOsdItem][1], tFACTORY_PAGE_1_SELECT_ITEM_TABLE[usOsdItem][2], 1, COLOR(_CP_RED, _CP_BG));
    }
    SET_OSD_STATE(usOsdState);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
WORD RTDFactoryDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            if (usValue >= usMax)
            {
                if(bCycle == _ON)
                {
                    return usMin;
                }
                else
                {
                    return usMax;
                }
            }
            else
            {
                usValue++;
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if (usValue <= usMin)
            {
                if(bCycle == _ON)
                {
                    return usMax;
                }
                else
                {
                    return usMin;
                }
            }
            else
            {
                usValue--;
            }
            break;

        default:
            break;
    }

    return usValue;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdDispNumber(WORD usOsdState, WORD usValue)
{
    BYTE ucTemp = 0;

    g_usAdjustValue = usValue;

    switch(usOsdState)
    {
        case _MENU_FACTORY_AUTO_COLOR_TYPE:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _AUTO_COLOR_TYPE_EXTERNAL, _AUTO_COLOR_TYPE_INTERNAL, _ON);

            usValue = g_ucFontPointer0;
            g_ucFontPointer0 = g_ucAutoColotTypeFontPointer;
            RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_TYPE_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_AUTO_COLOR_TYPE, tFONT_FACTORY_EUROPE, tOSD_FACTORY_AUTO_COLOR_TYPE_TABLE[g_usAdjustValue], _ENGLISH);
            g_ucFontPointer0 = usValue;
            break;

        case _MENU_FACTORY_BURNIN_ON_OFF:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            RTDFactoryOsdFuncPutStringProp(_FACTORY_BURNIN_ROW, _FACTORY_ON_OFF_COL, _PFONT_FACTORY_BURNIN, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[g_usAdjustValue], _ENGLISH);
            break;

        case _MENU_FACTORY_CT1_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempR = g_usAdjustValue;
            g_stColorProcData.usColorTempR = (g_stColorProcData.usColorTempR << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_R);
            break;

        case _MENU_FACTORY_CT1_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempG = g_usAdjustValue;
            g_stColorProcData.usColorTempG = (g_stColorProcData.usColorTempG << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_G);
            break;

        case _MENU_FACTORY_CT1_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempB = g_usAdjustValue;
            g_stColorProcData.usColorTempB = (g_stColorProcData.usColorTempB << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_B);
            break;

        case _MENU_FACTORY_CT2_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempR = g_usAdjustValue;
            g_stColorProcData.usColorTempR = (g_stColorProcData.usColorTempR << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP2_R);
            break;

        case _MENU_FACTORY_CT2_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempG = g_usAdjustValue;
            g_stColorProcData.usColorTempG = (g_stColorProcData.usColorTempG << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP2_G);
            break;

        case _MENU_FACTORY_CT2_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempB = g_usAdjustValue;
            g_stColorProcData.usColorTempB = (g_stColorProcData.usColorTempB << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP2_B);
            break;

        case _MENU_FACTORY_CT3_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempR = g_usAdjustValue;
            g_stColorProcData.usColorTempR = (g_stColorProcData.usColorTempR << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP3_R);
            break;

        case _MENU_FACTORY_CT3_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempG = g_usAdjustValue;
            g_stColorProcData.usColorTempG = (g_stColorProcData.usColorTempG << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP3_G);
            break;

        case _MENU_FACTORY_CT3_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempB = g_usAdjustValue;
            g_stColorProcData.usColorTempB = (g_stColorProcData.usColorTempB << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP3_B);
            break;

        case _MENU_FACTORY_CT4_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempR = g_usAdjustValue;
            g_stColorProcData.usColorTempR = (g_stColorProcData.usColorTempR << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP4_R);
            break;

        case _MENU_FACTORY_CT4_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempG = g_usAdjustValue;
            g_stColorProcData.usColorTempG = (g_stColorProcData.usColorTempG << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP4_G);
            break;

        case _MENU_FACTORY_CT4_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempB = g_usAdjustValue;
            g_stColorProcData.usColorTempB = (g_stColorProcData.usColorTempB << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP4_B);
            break;

        case _MENU_FACTORY_CT5_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempR = g_usAdjustValue;
            g_stColorProcData.usColorTempR = (g_stColorProcData.usColorTempR << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP5_R);
            break;

        case _MENU_FACTORY_CT5_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempG = g_usAdjustValue;
            g_stColorProcData.usColorTempG = (g_stColorProcData.usColorTempG << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP5_G);
            break;

        case _MENU_FACTORY_CT5_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempB = g_usAdjustValue;
            g_stColorProcData.usColorTempB = (g_stColorProcData.usColorTempB << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP5_B);
            break;

        case _MENU_FACTORY_CT6_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempR = g_usAdjustValue;
            g_stColorProcData.usColorTempR = (g_stColorProcData.usColorTempR << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP6_R);
            break;

        case _MENU_FACTORY_CT6_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempG = g_usAdjustValue;
            g_stColorProcData.usColorTempG = (g_stColorProcData.usColorTempG << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP6_G);
            break;

        case _MENU_FACTORY_CT6_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange((g_usAdjustValue >> 4), _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stColorProcData.usColorTempB = g_usAdjustValue;
            g_stColorProcData.usColorTempB = (g_stColorProcData.usColorTempB << 4);

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_CONTRAST());
#endif
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP6_B);
            break;

#if(_VGA_SUPPORT == _ON)
        case _MENU_FACTORY_GAIN_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL] = g_usAdjustValue;
            UserCommonInterfaceAdjustADCData();
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_R);
            break;

        case _MENU_FACTORY_GAIN_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL] = g_usAdjustValue;
            UserCommonInterfaceAdjustADCData();
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_G);
            break;

        case _MENU_FACTORY_GAIN_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL] = g_usAdjustValue;
            UserCommonInterfaceAdjustADCData();
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_B);
            break;

        case _MENU_FACTORY_OFFSET_RED_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL] = g_usAdjustValue;
            UserCommonInterfaceAdjustADCData();
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_R);
            break;

        case _MENU_FACTORY_OFFSET_GREEN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL] = g_usAdjustValue;
            UserCommonInterfaceAdjustADCData();
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_G);
            break;

        case _MENU_FACTORY_OFFSET_BLUE_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL] = g_usAdjustValue;
            UserCommonInterfaceAdjustADCData();
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_B);
            break;
#endif // End of #if(_VGA_SUPPORT == _ON)

        case _MENU_FACTORY_OSD_PAGE_ADJ:
        case _MENU_FACTORY_OSD_PAGE_1_ADJ:
            g_ucFactoryPage = (BYTE)RTDFactoryDetOverRange(g_ucFactoryPage, _FACTORY_OSD_PAGE_MAX, _FACTORY_OSD_PAGE_MIN, _ON);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_OSD_PAGE_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_OSD_PAGE);
            break;

        case _MENU_FACTORY_BG_ON_OFF:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            RTDFactoryOsdFuncPutStringProp(_FACTORY_BG_ROW, _FACTORY_ON_OFF_COL, _PFONT_FACTORY_BACKGROUND_ON_OFF, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[g_usAdjustValue], _ENGLISH);
            ScalerDDomainBackgroundEnable(g_usAdjustValue);
            break;

        case _MENU_FACTORY_BG_RED_ADJ:
            g_ucBgColorR = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_R_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_R);
            ScalerDDomainBackgroundSetColor(g_ucBgColorR, g_ucBgColorG, g_ucBgColorB);
            break;

        case _MENU_FACTORY_BG_GREEN_ADJ:
            g_ucBgColorG = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_G_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_G);
            ScalerDDomainBackgroundSetColor(g_ucBgColorR, g_ucBgColorG, g_ucBgColorB);
            break;

        case _MENU_FACTORY_BG_BLUE_ADJ:
            g_ucBgColorB = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_RBG_MAX, _FACTORY_RBG_MIN, _OFF);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_B_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_B);
            ScalerDDomainBackgroundSetColor(g_ucBgColorR, g_ucBgColorG, g_ucBgColorB);
            break;

        case _MENU_FACTORY_SSC_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_SSC_MAX, _FACTORY_SSC_MIN, _OFF);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_SSC_ROW), COL(_FACTORY_SSC_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_SSC);
            break;

        case _MENU_FACTORY_LVDS_CLOCK_CURRENT_ADJ:
            g_usAdjustValue= (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_LVDS_CLOCK_CURRENT_MAX, _FACTORY_LVDS_CLOCK_CURRENT_MIN, _OFF);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_LVDS_CLOCK_ROW), COL(_FACTORY_LVDS_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_LVDS_CLOCK);
            break;

        case _MENU_FACTORY_LVDS_DATA_CURRENT_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_LVDS_DATA_CURRENT_MAX, _FACTORY_LVDS_DATA_CURRENT_MIN, _OFF);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_LVDS_DATA_ROW), COL(_FACTORY_LVDS_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_LVDS_DATA);
            break;
/*
        case _MENU_FACTORY_PATTERN_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_PATTERN_MAX, _FACTORY_PATTERN_MIN, _ON);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PATTERN_ROW), COL(_FACTORY_PATTERN_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_PATTERN);
            break;
*/

#if(_DP_SUPPORT == _ON)
        case _MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            UserCommonNVRamSetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH, g_usAdjustValue);
            RTDFactoryOsdFuncPutStringProp(_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ROW, COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), _PFONT_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[g_usAdjustValue], _ENGLISH);
            break;

#if(_HW_DP_AUX_SINGLE_ENDED_MODE_SUPPORT == _ON)
        case _MENU_FACTORY_DP_AUX_MODE_ON_OFF:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            UserCommonNVRamSetSystemData(_DP_AUX_DIFF_MODE, g_usAdjustValue);
            UserCommonInterfaceDpAuxSet();
            RTDFactoryOsdFuncPutStringProp(_FACTORY_DP_AUX_MODE_ROW, COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_DP_AUX_MODE_SEL, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[g_usAdjustValue], _ENGLISH);
            break;
#endif

        case _MENU_FACTORY_DP_AUX_SETTING_ADJR:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, 0x0F, 0x00, _ON);
            UserCommonNVRamSetSystemData(_DP_AUX_ADJR_SETTING, g_usAdjustValue);
            UserCommonInterfaceDpAuxSet();
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DP_AUX_ADJR_ROW), COL(_FACTORY_ON_OFF_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_DP_AUX_ADJR);
            break;
#endif // End of #if(_DP_SUPPORT == _ON)

        case _MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT, g_usAdjustValue);
            RTDFactoryOsdFuncPutStringProp(_FACTORY_HOT_PLUG_HDMI_SUPPORT_ROW, COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), _PFONT_FACTORY_HOT_PLUG_HDMI_SUPPORT, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[g_usAdjustValue], _ENGLISH);
            break;

        case _MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _FACTORY_HOT_PLUG_HDMI_TIME_MAX, _FACTORY_HOT_PLUG_HDMI_TIME_MIN, _OFF);
            UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME, g_usAdjustValue);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), (g_usAdjustValue), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_HOT_PLUG_HDMI_TIME);
            break;

        case _MENU_FACTORY_OSD_DOUBLE_SIZE_ON_OFF:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            SET_OSD_DOUBLE_SIZE(g_usAdjustValue);
            RTDFactoryOsdFuncPutStringProp(_FACTORY_OSD_DOUBLE_ROW, COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_OSD_DOUBLE_ON_OFF, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[g_usAdjustValue], _ENGLISH);
            break;

        case _MENU_FACTORY_COLORIMETRY_SEAMLESS_ON_OFF:
            g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, _ON, _OFF, _ON);
            UserCommonNVRamSetSystemData(_COLORIMETRY_SEAMLESS_CHANGE, g_usAdjustValue);
            RTDFactoryOsdFuncPutStringProp(_FACTORY_COLORIMETRY_SEAMLESS_ROW, COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_COLORIMETRY_SEAMLESS, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[g_usAdjustValue], _ENGLISH);
            break;

        case _MENU_FACTORY_DP_IRQ_TIME_ADJ:

            for(ucTemp = 0; ucTemp < 5; ucTemp++)
            {
                g_usAdjustValue = (BYTE)RTDFactoryDetOverRange(g_usAdjustValue, 95, 55, _OFF);
            }

            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_DP_IRQ_ROW), COL(_FACTORY_ON_OFF_COL), (g_usAdjustValue*10), (_ALIGN_LEFT| _FORCE_SHOW_NUMBER_OFF | _SHOW_4), _PFONT_FACTORY_DP_IRQ_ADJ);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdFuncSetPosition(BYTE ucType, WORD usX, WORD usY)
{
#if 0// (_OSD_ROTATE_FUNCTION == _ON)
    if(GET_OSD_ROTATE_STATUS() == _TRUE)
    {
        if(ucType == _FACTORY_OSD)
        {
            usX = 8 + ((DWORD)((_PANEL_DH_WIDTH - _FACTORY_OSD_WINDOW_SIZE_Y) / 4) * usX) / _OSD_H_POS_MAX;
            usY = 0 + ((DWORD)(_PANEL_DV_HEIGHT - _FACTORY_OSD_WINDOW_SIZE_X) * usY) / _OSD_V_POS_MAX;
        }
    }
    else
#endif
    {
        if(ucType == _FACTORY_OSD)
        {
            usX = ((DWORD)((_PANEL_DH_WIDTH - _FACTORY_OSD_WINDOW_SIZE_X) / 4) * usX) / _OSD_H_POS_MAX;
            usY = 3 + ((DWORD)(_PANEL_DV_HEIGHT - _FACTORY_OSD_WINDOW_SIZE_Y) * usY) / _OSD_V_POS_MAX;
        }
    }

    ScalerOsdPosition(_OSD_POSITION_GLOBAL_A, usX, usY);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDFactoryOsdChangColorTemp(BYTE ucColorTemp)
{
    SET_COLOR_TEMP_TYPE(ucColorTemp);
    RTDNVRamLoadColorSetting(GET_COLOR_TEMP_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_CONTRAST());
#endif
}

//--------------------------------------------------
// Description  : Pannel user time
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryPanelUsedTimer(void)
{
    SET_PANEL_TIME_MIN(GET_PANEL_TIME_MIN() + 1);

    if((GET_PANEL_TIME_HOUR() >= 65535) && (GET_PANEL_TIME_MIN() >= 59))
    {
        SET_PANEL_TIME_HOUR(65535);
        SET_PANEL_TIME_MIN(59);
    }

    if(GET_PANEL_TIME_MIN() >= 60)
    {
        SET_PANEL_TIME_HOUR(GET_PANEL_TIME_HOUR() + 1);
        SET_PANEL_TIME_MIN(0);
    }

    if(GET_OSD_IN_FACTORY_MENU_STATUS() == _FALSE)
    {
        if((GET_PANEL_TIME_MIN() % 20) == 0)
        {
            RTDNVRamSavePanelUsedTimeData();
        }
    }
    else
    {
        if(g_ucFactoryPage == 0)
        {
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_HOUR_NUMBER_COL), GET_PANEL_TIME_HOUR(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_FACTORY_PANEL_TIME_HOUR);
            RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_MIN_NUMBER_COL), GET_PANEL_TIME_MIN(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_PANEL_TIME_MIN);
        }
        RTDNVRamSavePanelUsedTimeData();
    }

    ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);
}

#if(_FACTORY_ONE_PIECE_MARK_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryOnePieceMark(void)
{
    BYTE ucTempLoop = 0;

    for(ucTempLoop = 0; ucTempLoop < (sizeof(tPALETTE_ONE_PIECE) / 3); ucTempLoop++)
    {
        ScalerOsdSetColorPalette(ucTempLoop, tPALETTE_ONE_PIECE[(ucTempLoop * 3) + 0], tPALETTE_ONE_PIECE[(ucTempLoop * 3) + 1], tPALETTE_ONE_PIECE[(ucTempLoop * 3) + 2]);
    }

    ScalerOsdBurstWriteDataPort(tOSD_ONE_PIECE, sizeof(tOSD_ONE_PIECE), GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
    ScalerOsdHardwareVLC(tOSD_ONE_PIECE_ICON, VLC_TABLE_SIZE(tOSD_ONE_PIECE_ICON), GET_CURRENT_BANK_NUMBER(), _ONE_PIECE_4BIT_FONT_STAR, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);
}

#endif // End of #if(_FACTORY_ONE_PIECE_MARK_SUPPORT == _ON)
