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
// ID Code      : Panel_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_OPTION_H__
#define __PANEL_OPTION_H__

//--------------------------------------------------
// Panel Option for DCLK Unit
//--------------------------------------------------
#if(_PANEL_PIXEL_CLOCK_UNIT == _PANEL_CLOCK_KHZ)
#define _PANEL_PIXEL_CLOCK_KHZ                      (_PANEL_PIXEL_CLOCK)
#define _PANEL_PIXEL_CLOCK_MAX_KHZ                  (_PANEL_PIXEL_CLOCK_MAX)
#define _PANEL_PIXEL_CLOCK_MIN_KHZ                  (_PANEL_PIXEL_CLOCK_MIN)
#elif(_PANEL_PIXEL_CLOCK_UNIT == _PANEL_CLOCK_MHZ)
#define _PANEL_PIXEL_CLOCK_KHZ                      (_PANEL_PIXEL_CLOCK * 1000UL)
#define _PANEL_PIXEL_CLOCK_MAX_KHZ                  (_PANEL_PIXEL_CLOCK_MAX * 1000UL)
#define _PANEL_PIXEL_CLOCK_MIN_KHZ                  (_PANEL_PIXEL_CLOCK_MIN * 1000UL)
#endif

//--------------------------------------------------
// Panel output number
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_NONE)
#define _PANEL_OUTPUT_NUM                           (1)

#elif(_PANEL_STYLE == _PANEL_LVDS)
#define _PANEL_OUTPUT_NUM                           (1 << _LVDS_OUTPUT_PORT)

#elif(_PANEL_STYLE == _PANEL_DPTX)
#define _PANEL_OUTPUT_NUM                           (((_DISPLAY_DP_TX_PORT_1 == _ON) ? 1 : 0) + ((_DISPLAY_DP_TX_PORT_2 == _ON) ? 1 : 0))

#elif(_PANEL_STYLE == _PANEL_VBO)
#define _PANEL_OUTPUT_NUM                           _VBO_OUTPUT_PORT

#elif(_PANEL_STYLE == _PANEL_TTL)
#define _PANEL_OUTPUT_NUM                           (1 << _TTL_OUTPUT_PORT)

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

//--------------------------------------------------
// Pixel per MN DPLL offset
//--------------------------------------------------
#define _MN_DPLL_PIXEL_PER_OFFSET                   ((DWORD)_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 32768)

//----------------------------------------------------------------------------------------------------
// Panel DP Tx Option
//----------------------------------------------------------------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)
#if(_SCALER_TYPE == _RL6410_SERIES)

#if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
#define _DISPLAY_DP_TX_PORT_1                       _ON
#define _DISPLAY_DP_TX_PORT_2                       _ON
#define _DISPLAY_DP_TX_FB_MODE                      (_D_DOMAIN_PATH == _D_DOMAIN_4_PATH ? _OFF : _ON)

#else
#define _DISPLAY_DP_TX_PORT_1                       ((_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX1_PORT) ? _ON : _OFF)
#define _DISPLAY_DP_TX_PORT_2                       ((_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX2_PORT) ? _ON : _OFF)
#define _DISPLAY_DP_TX_FB_MODE                      _OFF
#endif

#define _PANEL_DPTX_SWING_LEVEL                     ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_SWING_LEVEL : _PANEL_DPTX_1_1_SWING_LEVEL)
#define _PANEL_DPTX_PREEMPHASIS_LEVEL               ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL : _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL)
#define _PANEL_DPTX_SPREAD_RANGE                    ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_SPREAD_RANGE : _PANEL_DPTX_1_1_SPREAD_RANGE)
#define _PANEL_DPTX_SPREAD_SPEED                    ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_SPREAD_SPEED : _PANEL_DPTX_1_1_SPREAD_SPEED)

#elif((_SCALER_TYPE == _RL6432_SERIES) ||\
      (_SCALER_TYPE == _RL6492_SERIES))

#define _DISPLAY_DP_TX_PORT_1                       ((_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX1_PORT) ? _ON : _OFF)
#define _DISPLAY_DP_TX_PORT_2                       ((_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX2_PORT) ? _ON : _OFF)
#define _DISPLAY_DP_TX_FB_MODE                      _OFF
#define _PANEL_DPTX_SWING_LEVEL                     _PANEL_DPTX_1_1_SWING_LEVEL
#define _PANEL_DPTX_PREEMPHASIS_LEVEL               _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL
#define _PANEL_DPTX_SPREAD_RANGE                    _PANEL_DPTX_1_1_SPREAD_RANGE
#define _PANEL_DPTX_SPREAD_SPEED                    _PANEL_DPTX_1_1_SPREAD_SPEED
#elif(_SCALER_TYPE == _RL6449_SERIES)

#if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
#define _DISPLAY_DP_TX_PORT_1                       _ON
#define _DISPLAY_DP_TX_PORT_2                       _ON
#define _DISPLAY_DP_TX_FB_MODE                      _ON
#else
#define _DISPLAY_DP_TX_PORT_1                       ((_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX1_PORT) ? _ON : _OFF)
#define _DISPLAY_DP_TX_PORT_2                       ((_PANEL_DPTX_PORT_NUMBER_SEL == _DPTX_TX2_PORT) ? _ON : _OFF)
#define _DISPLAY_DP_TX_FB_MODE                      _OFF
#endif

#define _PANEL_DPTX_SWING_LEVEL                     ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_SWING_LEVEL : _PANEL_DPTX_1_1_SWING_LEVEL)
#define _PANEL_DPTX_PREEMPHASIS_LEVEL               ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL : _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL)
#define _PANEL_DPTX_SPREAD_RANGE                    ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_SPREAD_RANGE : _PANEL_DPTX_1_1_SPREAD_RANGE)
#define _PANEL_DPTX_SPREAD_SPEED                    ((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2) ? _PANEL_DPTX_1_2_SPREAD_SPEED : _PANEL_DPTX_1_1_SPREAD_SPEED)
#endif

//--------------------------------------------------
// Panel DPTx Lane/FB Swap Option
//--------------------------------------------------
#if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
#if((_SCALER_TYPE == _RL6410_SERIES) || (_SCALER_TYPE == _RL6449_SERIES))
#define _PANEL_DPTX_FB_SWAP                         _PANEL_DPTX_1_2_FB_SWAP
#define _PANEL_DPTX_LANE_SWAP                       _PANEL_DPTX_1_2_LANE_SWAP
#define _PANEL_DPTX_LANE_PN_SWAP                    _PANEL_DPTX_1_2_LANE_PN_SWAP
#endif
#elif((_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR) || (_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_RBR))
#define _PANEL_DPTX_FB_SWAP                         _PANEL_DPTX_1_1_FB_SWAP
#define _PANEL_DPTX_LANE_SWAP                       _PANEL_DPTX_1_1_LANE_SWAP
#define _PANEL_DPTX_LANE_PN_SWAP                    _PANEL_DPTX_1_1_LANE_PN_SWAP
#endif

#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

//--------------------------------------------------
// D Domain 1/2/4 Path Option
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#define _D_DOMAIN_PATH                              _D_DOMAIN_1_PATH

#elif(_SCALER_TYPE == _RL6410_SERIES)
#if(_PANEL_EXIST_MULTIPANEL == _ON)
#define _D_DOMAIN_PATH                              _D_DOMAIN_2_PATH
#define _PANEL_DPTX_DCLK_DIV                        ((_DISPLAY_DP_TX_FB_MODE == _ON) ? 2 : 1)
#else

#if(((_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _ON) && (_PANEL_PIXEL_CLOCK_KHZ > 700000)) ||\
    ((_IMD_DOMAIN_ULTRA_HIGH_SPEED_SUPPORT == _OFF) && (_PANEL_PIXEL_CLOCK_KHZ > 630000)))
#define _D_DOMAIN_PATH                              _D_DOMAIN_4_PATH
#define _PANEL_DPTX_DCLK_DIV                        2
#else
#define _D_DOMAIN_PATH                              _D_DOMAIN_2_PATH
#define _PANEL_DPTX_DCLK_DIV                        ((_DISPLAY_DP_TX_FB_MODE == _ON) ? 2 : 1)
#endif

#endif

#elif((_SCALER_TYPE == _RL6432_SERIES) ||\
      (_SCALER_TYPE == _RL6492_SERIES))
#define _D_DOMAIN_PATH                              _D_DOMAIN_1_PATH
#define _PANEL_DPTX_DCLK_DIV                        1

#elif(_SCALER_TYPE == _RL6449_SERIES)
#define _D_DOMAIN_PATH                              _D_DOMAIN_2_PATH
#define _PANEL_DPTX_DCLK_DIV                        ((_DISPLAY_DP_TX_FB_MODE == _ON) ? 2 : 1)

#elif(_SCALER_TYPE == _RLE0779_SERIES)
#define _D_DOMAIN_PATH                              _D_DOMAIN_1_PATH
#define _PANEL_DPTX_DCLK_DIV                        1


#endif

//--------------------------------------------------
// Definitions for Uniformity Setting
//--------------------------------------------------
#if((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
    (_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
    (_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
    (_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
    (_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL) ||\
    (_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_4LEVEL))
#define _PANEL_UNIFORMITY_LEVEL_MAX                 _UNIFORMITY_4LEVEL
#elif((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL) ||\
      (_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_1LEVEL))
#define _PANEL_UNIFORMITY_LEVEL_MAX                 _UNIFORMITY_1LEVEL
#elif((_UNIFORMITY_1ST_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_2ND_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_3RD_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_4TH_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_5TH_TABLE_LEVEL == _UNIFORMITY_NONE) ||\
      (_UNIFORMITY_6TH_TABLE_LEVEL == _UNIFORMITY_NONE))
#define _PANEL_UNIFORMITY_LEVEL_MAX                 _UNIFORMITY_NONE
#endif

#define _PANEL_UNIFORMITY_HOR_INTERVAL              64
#define _PANEL_UNIFORMITY_VER_INTERVAL              _PANEL_UNIFORMITY_HOR_INTERVAL
#define _PANEL_UNIFORMITY_HOR_GRIDS                 (WORD)((_PANEL_DH_WIDTH / _PANEL_UNIFORMITY_HOR_INTERVAL) + 2)
#define _PANEL_UNIFORMITY_VER_GRIDS                 (WORD)((_PANEL_DV_HEIGHT / _PANEL_UNIFORMITY_VER_INTERVAL) + 2)
#define _PANEL_UNIFORMITY_HOR_OFFSET                (WORD)(((_PANEL_UNIFORMITY_HOR_GRIDS - 1) * _PANEL_UNIFORMITY_HOR_INTERVAL - _PANEL_DH_WIDTH) / 2)
#define _PANEL_UNIFORMITY_VER_OFFSET                (WORD)(((_PANEL_UNIFORMITY_VER_GRIDS - 1) * _PANEL_UNIFORMITY_VER_INTERVAL - _PANEL_DV_HEIGHT) / 2)
#define _PANEL_UNIFORMITY_1LEVEL_SIZE               ((WORD)_PANEL_UNIFORMITY_HOR_GRIDS * _PANEL_UNIFORMITY_VER_GRIDS * 5)
#define _PANEL_UNIFORMITY_OFFSET_LUT_SIZE           ((WORD)_PANEL_UNIFORMITY_HOR_GRIDS * _PANEL_UNIFORMITY_VER_GRIDS * 6)
#define _PANEL_UNIFORMITY_DECAY_LUT_SIZE            896

//--------------------------------------------------
// Definitions for Uniformity Local Dimming Setting
//--------------------------------------------------
#define _PANEL_UNIFORMITY_LD_HOR_INTERVAL           128
#define _PANEL_UNIFORMITY_LD_VER_INTERVAL           _PANEL_UNIFORMITY_LD_HOR_INTERVAL
#define _PANEL_UNIFORMITY_LD_HOR_GRIDS              (WORD)((_PANEL_DH_WIDTH / _PANEL_UNIFORMITY_LD_HOR_INTERVAL) + 2)
#define _PANEL_UNIFORMITY_LD_VER_GRIDS              (WORD)((_PANEL_DV_HEIGHT / _PANEL_UNIFORMITY_LD_VER_INTERVAL) + 2)
#define _PANEL_UNIFORMITY_LD_LUT_SIZE               ((WORD)_PANEL_UNIFORMITY_LD_HOR_GRIDS * _PANEL_UNIFORMITY_LD_VER_GRIDS * 5)
#define _PANEL_UNIFORMITY_LD_HOR_OFFSET             (WORD)(((_PANEL_UNIFORMITY_LD_HOR_GRIDS - 1) * _PANEL_UNIFORMITY_LD_HOR_INTERVAL - _PANEL_DH_WIDTH) / 2)
#define _PANEL_UNIFORMITY_LD_VER_OFFSET             (WORD)(((_PANEL_UNIFORMITY_LD_VER_GRIDS - 1) * _PANEL_UNIFORMITY_LD_VER_INTERVAL - _PANEL_DV_HEIGHT) / 2)

//--------------------------------------------------
// Definitions for multiple of DHtotal
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_LVDS)

#if(_LVDS_OUTPUT_PORT >= _LVDS_8_PORT)
#define _DHTOTAL_MULTIPLE                           (1 << _LVDS_OUTPUT_PORT)
#else
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#define _DHTOTAL_MULTIPLE                           (8)
#else
#define _DHTOTAL_MULTIPLE                           (4)
#endif
#endif

#elif(_PANEL_STYLE == _PANEL_TTL)
#define _DHTOTAL_MULTIPLE                           (1 << _TTL_OUTPUT_PORT)

#elif(_PANEL_STYLE == _PANEL_VBO)

#if(_VBO_OUTPUT_PORT >= _VBO_8_DATA_LANE)
#define _DHTOTAL_MULTIPLE                           (_VBO_OUTPUT_PORT)
#else
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#define _DHTOTAL_MULTIPLE                           (8)
#else
#define _DHTOTAL_MULTIPLE                           (4)
#endif
#endif

#elif(_PANEL_STYLE == _PANEL_DPTX)

#if(_PANEL_DPTX_LANE_NUMBER >= _PANEL_DPTX_LANE_NUMBER_8)
#define _DHTOTAL_MULTIPLE                           (1 << _PANEL_DPTX_LANE_NUMBER)
#else
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#define _DHTOTAL_MULTIPLE                           (8)
#else
#define _DHTOTAL_MULTIPLE                           (4)
#endif
#endif

#endif

// Real DHtotal Value = DHtotal Register Setting + _DHTOTAL_SETTING_COMPLEMENT
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#define _DHTOTAL_SETTING_COMPLEMENT                 (8)
#else
#define _DHTOTAL_SETTING_COMPLEMENT                 (4)
#endif

//--------------------------------------------------
// Definitions for Div of DPLL SSCG Mode
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_VBO)
#define _DPLL_SSCG_DIV_MODE                         (_DIV_8)
#else
#define _DPLL_SSCG_DIV_MODE                         (_DIV_1)
#endif

// 1% margin and spread
#define GET_CLOCK_SPREAD(clk, spread)               (((_DPLL_JITTER_MARGIN == _DPLL_1_PERCENT_JITTER_MARGIN) ? ((clk) / 100UL) : 0) + ((clk) * 5UL * (spread) / 2000UL / _DPLL_SSCG_DIV_MODE))

#define _PANEL_PIXEL_CLOCK_MAX_SPREAD               (_PANEL_PIXEL_CLOCK_MAX_KHZ - GET_CLOCK_SPREAD(_PANEL_PIXEL_CLOCK_MAX_KHZ, _DCLK_SPREAD_RANGE_MAX))
#define _PANEL_PIXEL_CLOCK_MIN_SPREAD               (_PANEL_PIXEL_CLOCK_MIN_KHZ + GET_CLOCK_SPREAD(_PANEL_PIXEL_CLOCK_MIN_KHZ, _DCLK_SPREAD_RANGE_MAX))

#endif // End of #ifndef __PANEL_OPTION_H__
