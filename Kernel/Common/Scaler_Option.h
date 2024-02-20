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
// ID Code      : Scaler_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_OPTION_H__
#define __SCALER_OPTION_H__

//--------------------------------------------------
// MN DPLL Phase Swallow Path Type
//--------------------------------------------------
#if((_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N) || (_DPLL_STRUCT_TYPE == _DPLL_STRUCT_M_N_CASCADE_N_F))
#if((_SCALER_TYPE == _RL6410_SERIES) || (_SCALER_TYPE == _RL6449_SERIES) || (_SCALER_TYPE == _RL6432_SERIES))
#define _MN_DPLL_PATH_TYPE                          _MN_DPLL_PATH1
#define _MN_DPLL_FREQ_UP                            ((_PANEL_STYLE == _PANEL_DPTX) || (_PANEL_STYLE == _PANEL_LVDS))
#else
#define _MN_DPLL_PATH_TYPE                          _MN_DPLL_PATH1
#define _MN_DPLL_FREQ_UP                            _OFF
#endif
#endif

//-------------------------------------------------
// MN MPLL Phase Swallow Path Type
//-------------------------------------------------
#if(_MPLL_STRUCT_TYPE == _MPLL_STRUCT_M_N)
#if((_SCALER_TYPE == _RL6410_SERIES) || (_SCALER_TYPE == _RL6432_SERIES) || (_SCALER_TYPE == _RL6449_SERIES) || (_SCALER_TYPE == _RL6492_SERIES))
#define _MN_MPLL_PATH_TYPE                          _MN_MPLL_PATH1
#define _MN_MPLL_FREQ_UP                            _ON
#else
#define _MN_MPLL_PATH_TYPE                          _MN_MPLL_PATH1
#define _MN_MPLL_FREQ_UP                            _OFF
#endif
#endif

//--------------------------------------------------
// LC_Tank Clock Frequncy Define
//--------------------------------------------------
#if(_LC_TANK_SUPPORT == _ON)
#define _LC_TANK_XTAL_FREQUENCY                     _LCTANK27000K
#endif

//--------------------------------------------------
// Memory Type Option
//--------------------------------------------------
#if(_MEMORY_TYPE == _EXTERNAL_MEMORY)

#define _MEMORY_TYPE_CONFIG                         (_EXTERNAL_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK)
#define _MEMORY_SIZE_CONFIG                         _EXTERNAL_MEMORY_SIZE_CONFIG

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MODE_NONE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_FRC_MODE
#endif

#elif(_MEMORY_TYPE == _EMBEDDED_MEMORY)

#define _MEMORY_TYPE_CONFIG                         (_EMBEDDED_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK)
#define _MEMORY_SIZE_CONFIG                         _EMBEDDED_MEMORY_SIZE_CONFIG

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MODE_NONE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
#define _SDRAM_PHASE_CALIBRATION                    _ON
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#define _SDRAM_PHASE_ON_LINE_ADDRESS                (0x1FFDF7) // 2047 row, Bank1, 248 column (remain 8 cell)
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#define _DDR1_PHASE_CALIBRATION                     _ON
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#define _DDR2_PHASE_CALIBRATION                     _ON
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#endif

#elif(_MEMORY_TYPE == _GEN_NONE)

#define _MEMORY_TYPE_CONFIG                         _NO_MEMORY
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MODE_NONE

#endif // End of #if(_MEMORY_TYPE == _EXTERNAL_MEMORY)

#if(_MEMORY_TYPE_CONFIG != _MEMORY_SDRAM)
#define _SDRAM_PHASE_CALIBRATION                    _OFF
#endif

#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR1)
#define _DDR1_PHASE_CALIBRATION                     _OFF
#endif

#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR2)
#define _DDR2_PHASE_CALIBRATION                     _OFF
#endif

//--------------------------------------------------
// D Domain 4 Path for FrameSync Line Buffer Option
//--------------------------------------------------
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#undef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT             _ON
#endif


//--------------------------------------------------
// CEC Related Define
//--------------------------------------------------
#define _HDMI_CEC_SUPPORT                           ((_HW_HDMI_CEC_GEN != _HW_CEC_GEN_NONE) &&\
                                                     ((_D0_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D1_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D2_HDMI_CEC_PIN == _HDMI_CEC_0) ||\
                                                     (_D3_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D4_HDMI_CEC_PIN == _HDMI_CEC_0) || (_D5_HDMI_CEC_PIN == _HDMI_CEC_0)))


//--------------------------------------------------
// HDMI2.0 YCbCr420 Option
//--------------------------------------------------
#if(_HDMI_2_0_SUPPORT == _ON)

#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RLE0779_SERIES))
#define _HDMI_2_0_YCBCR420_SUPPORT                  _ON
#else
#define _HDMI_2_0_YCBCR420_SUPPORT                  _OFF
#endif

#else

#define _HDMI_2_0_YCBCR420_SUPPORT                  _OFF

#endif

//--------------------------------------------------
// TMDS Support Macro Option
//--------------------------------------------------
#if(_D0_TMDS_SUPPORT == _ON)
#define _D0_INPUT_PORT_TMDS_MAC_PAGE                _D0_TMDS_MAC_USE
#else
#define _D0_INPUT_PORT_TMDS_MAC_PAGE                _PAGE_NONE
#endif

#if(_D1_TMDS_SUPPORT == _ON)
#define _D1_INPUT_PORT_TMDS_MAC_PAGE                _D1_TMDS_MAC_USE
#else
#define _D1_INPUT_PORT_TMDS_MAC_PAGE                _PAGE_NONE
#endif

#if(_D2_TMDS_SUPPORT == _ON)
#define _D2_INPUT_PORT_TMDS_MAC_PAGE                _D2_TMDS_MAC_USE
#else
#define _D2_INPUT_PORT_TMDS_MAC_PAGE                _PAGE_NONE
#endif

#if(_D3_TMDS_SUPPORT == _ON)
#define _D3_INPUT_PORT_TMDS_MAC_PAGE                _D3_TMDS_MAC_USE
#else
#define _D3_INPUT_PORT_TMDS_MAC_PAGE                _PAGE_NONE
#endif

#if(_D4_TMDS_SUPPORT == _ON)
#define _D4_INPUT_PORT_TMDS_MAC_PAGE                _D4_TMDS_MAC_USE
#else
#define _D4_INPUT_PORT_TMDS_MAC_PAGE                _PAGE_NONE
#endif

#if(_D5_TMDS_SUPPORT == _ON)
#define _D5_INPUT_PORT_TMDS_MAC_PAGE                _D5_TMDS_MAC_USE
#else
#define _D5_INPUT_PORT_TMDS_MAC_PAGE                _PAGE_NONE
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE2) + (_D1_TMDS_MAC_USE == _PAGE2) + (_D2_TMDS_MAC_USE == _PAGE2) +\
    (_D3_TMDS_MAC_USE == _PAGE2) + (_D4_TMDS_MAC_USE == _PAGE2) + (_D5_TMDS_MAC_USE == _PAGE2)) >= 2)
#define _TMDS_PAGE2_COMBO_EXIST                     _ON
#else
#define _TMDS_PAGE2_COMBO_EXIST                     _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE70) + (_D1_TMDS_MAC_USE == _PAGE70) + (_D2_TMDS_MAC_USE == _PAGE70) +\
    (_D3_TMDS_MAC_USE == _PAGE70) + (_D4_TMDS_MAC_USE == _PAGE70) + (_D5_TMDS_MAC_USE == _PAGE70)) >= 2)
#define _TMDS_PAGE70_COMBO_EXIST                    _ON
#else
#define _TMDS_PAGE70_COMBO_EXIST                    _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE71) + (_D1_TMDS_MAC_USE == _PAGE71) + (_D2_TMDS_MAC_USE == _PAGE71) +\
    (_D3_TMDS_MAC_USE == _PAGE71) + (_D4_TMDS_MAC_USE == _PAGE71) + (_D5_TMDS_MAC_USE == _PAGE71)) >= 2)
#define _TMDS_PAGE71_COMBO_EXIST                    _ON
#else
#define _TMDS_PAGE71_COMBO_EXIST                    _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE72) + (_D1_TMDS_MAC_USE == _PAGE72) + (_D2_TMDS_MAC_USE == _PAGE72) +\
    (_D3_TMDS_MAC_USE == _PAGE72) + (_D4_TMDS_MAC_USE == _PAGE72) + (_D5_TMDS_MAC_USE == _PAGE72)) >= 2)
#define _TMDS_PAGE72_COMBO_EXIST                    _ON
#else
#define _TMDS_PAGE72_COMBO_EXIST                    _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE73) + (_D1_TMDS_MAC_USE == _PAGE73) + (_D2_TMDS_MAC_USE == _PAGE73) +\
    (_D3_TMDS_MAC_USE == _PAGE73) + (_D4_TMDS_MAC_USE == _PAGE73) + (_D5_TMDS_MAC_USE == _PAGE73)) >= 2)
#define _TMDS_PAGE73_COMBO_EXIST                    _ON
#else
#define _TMDS_PAGE73_COMBO_EXIST                    _OFF
#endif

#if(((_D0_TMDS_MAC_USE == _PAGE74) + (_D1_TMDS_MAC_USE == _PAGE74) + (_D2_TMDS_MAC_USE == _PAGE74) +\
    (_D3_TMDS_MAC_USE == _PAGE74) + (_D4_TMDS_MAC_USE == _PAGE74) + (_D5_TMDS_MAC_USE == _PAGE74)) >= 2)
#define _TMDS_PAGE74_COMBO_EXIST                    _ON
#else
#define _TMDS_PAGE74_COMBO_EXIST                    _OFF
#endif

#if((_TMDS_PAGE2_COMBO_EXIST == _ON) || (_TMDS_PAGE70_COMBO_EXIST == _ON) || (_TMDS_PAGE71_COMBO_EXIST == _ON) ||\
    (_TMDS_PAGE72_COMBO_EXIST == _ON) || (_TMDS_PAGE73_COMBO_EXIST == _ON) || (_TMDS_PAGE74_COMBO_EXIST == _ON))
#define _TMDS_COMBO_EXIST                           _ON
#else
#define _TMDS_COMBO_EXIST                           _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE2)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE2)))
#define _HDMI_MAC_PAGE2_USE                         _ON
#else
#define _HDMI_MAC_PAGE2_USE                         _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE71)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE_NONE) && (_D2_TMDS_MAC_USE == _PAGE71))) // RL6432 D1 is special case)
#define _HDMI_MAC_PAGE71_USE                        _ON
#else
#define _HDMI_MAC_PAGE71_USE                        _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE72)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE72)))
#define _HDMI_MAC_PAGE72_USE                        _ON
#else
#define _HDMI_MAC_PAGE72_USE                        _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE73)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE73)))
#define _HDMI_MAC_PAGE73_USE                        _ON
#else
#define _HDMI_MAC_PAGE73_USE                        _OFF
#endif

#if(((_D0_HDMI_SUPPORT == _ON) && (_D0_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D1_HDMI_SUPPORT == _ON) && (_D1_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D2_HDMI_SUPPORT == _ON) && (_D2_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D3_HDMI_SUPPORT == _ON) && (_D3_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D4_HDMI_SUPPORT == _ON) && (_D4_TMDS_MAC_USE == _PAGE74)) ||\
    ((_D5_HDMI_SUPPORT == _ON) && (_D5_TMDS_MAC_USE == _PAGE74)))
#define _HDMI_MAC_PAGE74_USE                        _ON
#else
#define _HDMI_MAC_PAGE74_USE                        _OFF
#endif

//--------------------------------------------------
// DP Support Macro Option
//--------------------------------------------------
#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE)

#define _D0_DP_EXIST                                (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _D1_DP_EXIST                                (_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _D2_DP_EXIST                                (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)

#define _D0_DP_EXIST                                (_DP_SUPPORT == _ON)
#define _D1_DP_EXIST                                _OFF
#define _D2_DP_EXIST                                _OFF

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)

#define _D0_DP_EXIST                                (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _D1_DP_EXIST                                ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
#define _D2_DP_EXIST                                _OFF

#endif

#if(((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) && (_D0_DP_ASSR_MODE_SUPPORT == _ON)) ||\
    ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2) && (_D0_DP_ASSR_MODE_SUPPORT == _ON)) ||\
    ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL) && ((_D0_DP_ASSR_MODE_SUPPORT == _ON) || (_D1_DP_ASSR_MODE_SUPPORT == _ON) || (_D2_DP_ASSR_MODE_SUPPORT == _ON))))
#define _DP_RX0_ASSR_MODE_SUPPORT                   _ON
#else
#define _DP_RX0_ASSR_MODE_SUPPORT                   _OFF
#endif

#if(((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) && (_D1_DP_ASSR_MODE_SUPPORT == _ON)) ||\
    ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2) && ((_D1_DP_ASSR_MODE_SUPPORT == _ON) || (_D2_DP_ASSR_MODE_SUPPORT == _ON))))
#define _DP_RX1_ASSR_MODE_SUPPORT                   _ON
#else
#define _DP_RX1_ASSR_MODE_SUPPORT                   _OFF
#endif

#if(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE)

#define _HW_DP_MAC0_INPUT_CLOCK_MAX                 _HW_D0_INPUT_CLOCK_MAX
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                 _HW_D1_INPUT_CLOCK_MAX

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                 _HW_D0_INPUT_CLOCK_MAX
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                 _HW_D1_INPUT_CLOCK_MAX
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                 _HW_D2_INPUT_CLOCK_MAX
#else
#define _HW_DP_MAC0_INPUT_CLOCK_MAX                 _HW_D0_INPUT_CLOCK_MAX
#endif

#define _HW_DP_MAC1_INPUT_CLOCK_MAX                 _INPUT_NONE

#elif(_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)

#define _HW_DP_MAC0_INPUT_CLOCK_MAX                 _HW_D0_INPUT_CLOCK_MAX

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                 _HW_D1_INPUT_CLOCK_MAX
#elif(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                 _HW_D2_INPUT_CLOCK_MAX
#else
#define _HW_DP_MAC1_INPUT_CLOCK_MAX                 _HW_D1_INPUT_CLOCK_MAX
#endif

#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MAC_USE == _PAGEB5)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MAC_USE == _PAGEB5)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_MAC_USE == _PAGEB5)))
#define _DP_MAC_PAGEB5_USE                          _ON
#else
#define _DP_MAC_PAGEB5_USE                          _OFF
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MAC_USE == _PAGEB8)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MAC_USE == _PAGEB8)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DP_MAC_USE == _PAGEB8)))
#define _DP_MAC_PAGEB8_USE                          _ON
#else
#define _DP_MAC_PAGEB8_USE                          _OFF
#endif

//--------------------------------------------------
// DP MST & DP Tx Option
//--------------------------------------------------
#if(_DP_SUPPORT == _OFF)
#undef _DP_MST_SUPPORT
#undef _DP_TX_SUPPORT
#define _DP_MST_SUPPORT                             _OFF
#define _DP_TX_SUPPORT                              _OFF

#undef _D0_DP_MST_PORT_SUPPORT
#undef _D1_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                     _OFF
#define _D1_DP_MST_PORT_SUPPORT                     _OFF
#else

#if(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
#undef _D0_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                     _OFF
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_DP_PORT)
#undef _D1_DP_MST_PORT_SUPPORT
#define _D1_DP_MST_PORT_SUPPORT                     _OFF
#endif

#endif

//--------------------------------------------------
// DP DownStream Count Option
//--------------------------------------------------
#if(_DP_TX_SUPPORT == _OFF)
#undef _DP_1_1_DOWN_STREAM_PORT_COUNT
#undef _DP_1_2_DOWN_STREAM_PORT_COUNT
#define _DP_1_1_DOWN_STREAM_PORT_COUNT              0x00
#define _DP_1_2_DOWN_STREAM_PORT_COUNT              0x00
#endif

//--------------------------------------------------
// DP VSC SDP Option
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_HW_DP_VSC_SDP_EXT_CAPABILITY_SUPPORT == _ON) && (_DP_ULTRA_HDR_SUPPORT == _ON))
#define _DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT     _ON
#else
#define _DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT     _OFF
#endif

//--------------------------------------------------
// MHL PS Without Power Cut Option
//--------------------------------------------------
#define _MHL_PS_WITHOUT_POWERCUT_SUPPORT            _OFF

//--------------------------------------------------
// TypeC AC ON RECONNECT Option
//--------------------------------------------------
#if((_TYPE_C_EMB_POWER_SOURCE != _TYPE_C_VBUS_POWER_ONLY) && (_D0_DP_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) && (_TYPE_C_EMB_CTS_FLOW == _OFF))
#define _TYPE_C_CC_AC_ON_RECONNECT                  _ON
#else
#define _TYPE_C_CC_AC_ON_RECONNECT                  _OFF
#endif

//--------------------------------------------------
// TypeC Alt Mode Support Option
//--------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#define _TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT   ((_TYPE_C_EMB_DP_ALT_MODE_SUPPORT == _ON) || (_TYPE_C_VENDOR_ALT_MODE != _TYPE_C_VENDOR_ALT_MODE_NONE))
#endif

//--------------------------------------------------
// Low Power FW Flow Option
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6463_SERIES)
#define _SYSTEM_LOW_POWER_GEN                       _POWER_FLOW_GEN_2
#else
#define _SYSTEM_LOW_POWER_GEN                       _POWER_FLOW_GEN_1
#endif

//--------------------------------------------------
// Watch Dog Timer Event Option
//--------------------------------------------------
#if((_HDMI_2_0_SUPPORT == _ON) ||\
    (_MHL_3_0_SUPPORT == _ON) ||\
    (_DP_SUPPORT == _ON) ||\
    ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
#define _WD_TIMER_INT_SUPPORT                       _ON
#else
#define _WD_TIMER_INT_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// Record Timer Option
//--------------------------------------------------
#if(_MHL_3_0_SUPPORT == _ON)
#define _RECORD_TIMER_SUPPORT                       _ON
#else
#define _RECORD_TIMER_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// Timer Event ID Enumeration & Structure
//--------------------------------------------------
#include _USER_TIMER_INCLUDE

typedef enum
{
    _SCALER_TIMER_EVENT_INVALID = 0x00,

#include _USER_TIMER_EVENT_ID_INCLUDE
    _USER_TIMER_EVENT_END,

#include "TimerEventIDSystem.h"
    _SYSTEM_TIMER_EVENT_END,

#include "TimerEventIDScaler.h"
    _SCALER_TIMER_EVENT_END,
} EnumScalerTimerEventID;

typedef struct
{
    EnumScalerTimerEventID enumEventID;
    WORD usTime;
} StructTimerEventTableType;

//--------------------------------------------------
// HW IIC Speed Parameters Enumeration & Structure
//--------------------------------------------------
#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
#include _USER_HWIIC_INCLUDE
#endif

typedef enum
{
    _KERNAL_PAR_100K = 0x00,
    _KERNAL_PAR_400K,

#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
// Incldue User Paramters Type
#include _USER_HW_IIC_PAR_TYPE
#endif
}EnumHWIICParType;

//****************************************************************************
// HW IIC Speed Parameters Structure
//****************************************************************************
typedef struct
{
    BYTE ucSLPC_14318K;
    BYTE ucSHPC_14318K;
    BYTE ucSLPC_28000K;
    BYTE ucSHPC_28000K;
    BYTE ucSTA_SUGPIO_C;
    BYTE ucTOR;
    BYTE ucFTPC;
    BYTE ucFD10_14318K;
    BYTE ucFD10_28000K;
} StructHwI2cSettingData;

//--------------------------------------------------
// Timer Event Count
//--------------------------------------------------
#if((_HP_SOURCE_SCAN_SUPPORT == _ON) || (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE))
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT            5
#else
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT            4
#endif

#if(_DP_SUPPORT == _ON)
#define _SCALER_DP_EVENT_COUNT                      (6 + _DP_RX_MI_DONGLE_SUPPORT)
#else
#define _SCALER_DP_EVENT_COUNT                      0
#endif

#if(_DP_MST_SUPPORT == _ON)
#define _SCALER_DP_MST_EVENT_COUNT                  (3 + _DP_PORT_VALID)
#else
#define _SCALER_DP_MST_EVENT_COUNT                  0
#endif

#if(_DP_TX_SUPPORT == _ON)
#define _SCALER_DP_TX_EVENT_COUNT                   3
#else
#define _SCALER_DP_TX_EVENT_COUNT                   0
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#define _RX0_MHL_SCALER_EVENT_COUNT                 3
#else
#define _RX0_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#define _RX1_MHL_SCALER_EVENT_COUNT                 3
#else
#define _RX1_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#define _RX2_MHL_SCALER_EVENT_COUNT                 3
#else
#define _RX2_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#define _RX3_MHL_SCALER_EVENT_COUNT                 3
#else
#define _RX3_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#define _RX4_MHL_SCALER_EVENT_COUNT                 3
#else
#define _RX4_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
#define _RX5_MHL_SCALER_EVENT_COUNT                 3
#else
#define _RX5_MHL_SCALER_EVENT_COUNT                 0
#endif

#define _SIMULTANEOUS_SCALER_EVENT_COUNT            (_SCALER_DP_EVENT_COUNT + _SCALER_DP_MST_EVENT_COUNT + _SCALER_DP_TX_EVENT_COUNT +\
                                                     _RX0_MHL_SCALER_EVENT_COUNT + _RX1_MHL_SCALER_EVENT_COUNT +\
                                                     _RX2_MHL_SCALER_EVENT_COUNT + _RX3_MHL_SCALER_EVENT_COUNT +\
                                                     _RX4_MHL_SCALER_EVENT_COUNT + _RX5_MHL_SCALER_EVENT_COUNT)

#define _TIMER_EVENT_COUNT                          (_SIMULTANEOUS_USER_EVENT_COUNT + _SIMULTANEOUS_SYSTEM_EVENT_COUNT + _SIMULTANEOUS_SCALER_EVENT_COUNT)

//--------------------------------------------------
// M2PLL is 243M
// Enumerations of Flash / MCU Speed
// Power Normal:           Flash = 40.5M,  MCU = 81M
// Power Normal Flash Low Speed:
//                         Flash = 20.25M, MCU = 40.5M
//
// M2PLL is 351M
// Enumerations of Flash / MCU Speed
// Power Normal:           Flash = 44M,    MCU = 88M
// Power Normal Flash Low Speed:
//                         Flash = 22M,    MCU = 44M
//
// Power Sav/Down 27:      Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Saving DP:        Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Saving Precision: Flash = 14.318M,  MCU = 14.318M
// Power Initial:       Flash = 14.3M,  MCU = 14.3M
//--------------------------------------------------
typedef enum
{
#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_3,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_6,
    _FLASH_CLK_FAST_DIV = _DIV_3,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else

#if(_CACHE_PS_SWITCH == _ENABLE)
    _FLASH_CLK_PS_DIV = _DIV_1,
#elif(_CACHE_PS_SWITCH == _DISABLE)
    _FLASH_CLK_PS_DIV = _DIV_4,
#endif

#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M) // Else Of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_MCU_SPEED_UP_SUPPORT == _ON)
#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_2,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
    _FLASH_CLK_FAST_DIV = _DIV_2,
#endif

#else

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_8,
    _FLASH_CLK_FAST_DIV = _DIV_4,
#endif

#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M) // Else Of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_8,
    _FLASH_CLK_FAST_DIV = _DIV_4,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif


#endif // End of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SOURCE == _FLASH_IOSC_CLK)
    _FLASH_CLK_IN_DIV = _DIV_2,
    _FLASH_CLK_PS_FAST_DIV = _DIV_1,
#else
    _FLASH_CLK_IN_DIV = _DIV_1,
    _FLASH_CLK_PS_FAST_DIV = _DIV_1, // for DP
#endif
} EnumFlashClkDiv;

typedef enum
{
    _FLASH_2_CLK_IN_DIV = _DIV_1,

#if(_MCU_SPEED_UP_SUPPORT == _ON)
    _FLASH_2_CLK_DIV = _DIV_4,
#else
    _FLASH_2_CLK_DIV = _DIV_2,
#endif

#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_CACHE_PS_SWITCH == _ENABLE)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#elif(_CACHE_PS_SWITCH == _DISABLE)
    _FLASH_2_CLK_PS_DIV = _DIV_1,
#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#endif

} EnumFlash2ClkDiv;

typedef enum
{
    _MCU_CLK_DIV = _DIV_1,
#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)
    _MCU_CLK_PS_DIV = _DIV_1,
#endif

    _MCU_CLK_IN_DIV = _DIV_1,
} EnumMcuClkDiv;

typedef enum
{
    _IOSC_DELAY6US_CNT = 3, // Using IOSC/XTAL/M2PLL CLK To Get base 6us delay on the counter
    _IOSC_DELAY4US_CNT = 6, // Using IOSC/XTAL/M2PLL CLK To Get base Xus delay on the counter
    _XTAL_DELAY6US_CNT = 2,
    _XTAL_DELAY4US_CNT = 2,

#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)
    _M2PLL_DELAY6US_CNT = 23,
    _M2PLL_DELAY4US_CNT = 19,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
#if(_MCU_SPEED_UP_SUPPORT == _ON)
    _M2PLL_DELAY6US_CNT = 53,
    _M2PLL_DELAY4US_CNT = 44,
#else
    _M2PLL_DELAY6US_CNT = 26,
    _M2PLL_DELAY4US_CNT = 21,
#endif
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_372M)
    _M2PLL_DELAY6US_CNT = 28,
    _M2PLL_DELAY4US_CNT = 22,
#endif
}EnumDelay5usTuneCnt;

//--------------------------------------------------
// Timer 0/1 Max Delay Timer(MS)
//--------------------------------------------------
#if(_MCU_SPEED_UP_SUPPORT == _ON)
#define _TIMER01_STEP_TIME_MS                       4
#else
#define _TIMER01_STEP_TIME_MS                       8
#endif

//--------------------------------------------------
// Urgent Event Check Mode
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) || (_HDCP_2_2_SUPPORT == _ON))
#undef _URGENT_EVENT_CHECK_MODE
#define _URGENT_EVENT_CHECK_MODE                    _ON
#else
#undef _URGENT_EVENT_CHECK_MODE
#define _URGENT_EVENT_CHECK_MODE                    _OFF
#endif

//--------------------------------------------------
// DP HPD Implementation Mode
//--------------------------------------------------
#if((_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) || (_DP_MST_AUTO_SEARCH_SUPPORT == _ON) || (_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE))
#define _DP_LONG_HPD_MODE                           _DP_LONG_HPD_TIMEREVENT_MODE
#else
#define _DP_LONG_HPD_MODE                           _DP_LONG_HPD_DELAY_MODE
#endif

#endif // End of #ifndef __SCALER_OPTION_H__
