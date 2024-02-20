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
// ID Code      : ColorDitherDefault.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#define _I_DITHER_TEMP                          _ENABLE

#if((_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT))
#define _I_DITHER_VALUE_SIGN                    _DISABLE
#define _I_DITHER_V_FRAME_MOD                   _DISABLE
#define _I_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#if((_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_3_4_SEQ_TRUNCATE_6_4_2_BIT))
#define _I_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _I_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _I_DITHER_SEQ_INV_MODE                  0
#endif

#define _I_DITHER_12_TO_10_TEMP                 _I_DITHER_TEMP
#define _I_DITHER_12_TO_10_VALUE_SIGN           _I_DITHER_VALUE_SIGN
#define _I_DITHER_12_TO_10_V_FRAME_MOD          _I_DITHER_V_FRAME_MOD
#define _I_DITHER_12_TO_10_H_FRAME_MOD          _I_DITHER_H_FRAME_MOD
#define _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE     _I_DITHER_MULTI_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE     _I_DITHER_SHARE_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE    _I_DITHER_SERIES_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_ENABLE       _I_DITHER_SEQ_INV_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_MODE         _I_DITHER_SEQ_INV_MODE // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#define _D_DITHER_TEMP                          _ENABLE

#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) || (_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_V_FRAME_MOD                   _DISABLE
#define _D_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#define _D_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _D_DITHER_SEQ_INV_MODE                  0 // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

#if((_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) || (_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))
#define _D_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE        _DISABLE
#endif

#if(_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
#define _D_DITHER_FREERUNEN_SUPPORT             _DISABLE // Enable DDither When Show Logo
#endif

