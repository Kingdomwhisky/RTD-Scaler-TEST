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
// ID Code      : Pcb_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_OPTION_H__
#define __PCB_OPTION_H__

//----------------------------------------------------------------------------------------------------
// ID Code      : PCB_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Include Pin MCU Reg
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6463_SERIES)

#include "RL6463_Series_MCU_Reg_Mapping.h"

#elif(_SCALER_TYPE == _RL6492_SERIES)

#include "RL6492_Series_MCU_Reg_Mapping.h"

#endif

//--------------------------------------------------
// Input Valid Port Option
//--------------------------------------------------
#define _INPUT_PORT_VALID                           ((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) +\
                                                     (_A1_INPUT_PORT_TYPE != _A1_NO_PORT) +\
                                                     (_A2_INPUT_PORT_TYPE != _A2_NO_PORT) +\
                                                     (_D0_INPUT_PORT_TYPE != _D0_NO_PORT) +\
                                                     (_D1_INPUT_PORT_TYPE != _D1_NO_PORT) +\
                                                     (_D2_INPUT_PORT_TYPE != _D2_NO_PORT) +\
                                                     (_D3_INPUT_PORT_TYPE != _D3_NO_PORT) +\
                                                     (_D4_INPUT_PORT_TYPE != _D4_NO_PORT) +\
                                                     (_D5_INPUT_PORT_TYPE != _D5_NO_PORT) +\
                                                     (_D6_INPUT_PORT_TYPE != _D6_NO_PORT))

//--------------------------------------------------
// Dp Valid Port Option
//--------------------------------------------------
#define _DP_PORT_VALID                              ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) +\
                                                     (_D1_INPUT_PORT_TYPE == _D1_DP_PORT) +\
                                                     (_D2_INPUT_PORT_TYPE == _D2_DP_PORT) +\
                                                     (_D6_INPUT_PORT_TYPE == _D6_DP_PORT))

//--------------------------------------------------
// Type C Valid Port Option
//--------------------------------------------------
#define _TYPE_C_PORT_VALID                          ((_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE) +\
                                                     (_D1_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE) +\
                                                     (_D6_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE))

//--------------------------------------------------
// Interface Support Option
//--------------------------------------------------
#define _VGA_PORT_EXIST                             (_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)

#define _DVI_PORT_EXIST                             ((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) ||\
                                                     (_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))

#define _HDMI_PORT_EXIST                            ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) ||\
                                                     (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) ||\
                                                     (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) ||\
                                                     (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))

#define _DP_PORT_EXIST                              ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_DP_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))

#define _VGA_SUPPORT                                (_VGA_PORT_EXIST == _ON)

#if(_VGA_SUPPORT != _ON)
#undef _YPBPR_SUPPORT
#define _YPBPR_SUPPORT                              _OFF
#endif

#define _DUAL_DVI_SUPPORT                           ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))

#define _D0_TMDS_SUPPORT                            ((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) ||\
                                                     (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) ||\
                                                     (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))

#define _D1_TMDS_SUPPORT                            ((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))

#define _D2_TMDS_SUPPORT                            ((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))

#define _D3_TMDS_SUPPORT                            ((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))

#define _D4_TMDS_SUPPORT                            ((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))

#define _D5_TMDS_SUPPORT                            ((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) ||\
                                                     (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) ||\
                                                     (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))

#define _DVI_SUPPORT                                ((_D0_TMDS_SUPPORT == _ON) ||\
                                                     (_D1_TMDS_SUPPORT == _ON) ||\
                                                     (_D2_TMDS_SUPPORT == _ON) ||\
                                                     (_D3_TMDS_SUPPORT == _ON) ||\
                                                     (_D4_TMDS_SUPPORT == _ON) ||\
                                                     (_D5_TMDS_SUPPORT == _ON))

#define _D0_HDMI_SUPPORT                            ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) ||\
                                                     (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) ||\
                                                     ((_HDMI_FROM_DVI_CONNECT == _ON) &&\
                                                      (_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)))


#define _D1_HDMI_SUPPORT                            ((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) ||\
                                                     ((_HDMI_FROM_DVI_CONNECT == _ON) &&\
                                                      (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)))

#define _D2_HDMI_SUPPORT                            ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) ||\
                                                     ((_HDMI_FROM_DVI_CONNECT == _ON) &&\
                                                      ((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) ||\
                                                       (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))))

#define _D3_HDMI_SUPPORT                            ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) ||\
                                                     ((_HDMI_FROM_DVI_CONNECT == _ON) &&\
                                                      ((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) ||\
                                                       (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) ||\
                                                       (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))))

#define _D4_HDMI_SUPPORT                            ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) ||\
                                                     ((_HDMI_FROM_DVI_CONNECT == _ON) &&\
                                                      ((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) ||\
                                                       (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) ||\
                                                       (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))))

#define _D5_HDMI_SUPPORT                            ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) ||\
                                                     (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) ||\
                                                     ((_HDMI_FROM_DVI_CONNECT == _ON) &&\
                                                      ((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) ||\
                                                       (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))))

#define _HDMI_SUPPORT                               ((_D0_HDMI_SUPPORT == _ON) ||\
                                                     (_D1_HDMI_SUPPORT == _ON) ||\
                                                     (_D2_HDMI_SUPPORT == _ON) ||\
                                                     (_D3_HDMI_SUPPORT == _ON) ||\
                                                     (_D4_HDMI_SUPPORT == _ON) ||\
                                                     (_D5_HDMI_SUPPORT == _ON))

#define _DP_SUPPORT                                 ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_DP_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))

#if((_SCALER_TYPE == _RL6369_SERIES) ||\
    (_SCALER_TYPE == _RL6463_SERIES))

#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) +\
     (_D1_INPUT_PORT_TYPE == _D1_DP_PORT) +\
     (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)) == 1)
#define _DP_EMBEDDED_SWITCH_SUPPORT_TYPE            _DP_EMBEDDED_SWITCH_1_DP
#elif(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) +\
       (_D1_INPUT_PORT_TYPE == _D1_DP_PORT) +\
       (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)) == 2)
#define _DP_EMBEDDED_SWITCH_SUPPORT_TYPE            _DP_EMBEDDED_SWITCH_2_DP
#endif

#elif(_SCALER_TYPE == _RL6492_SERIES)

#if(((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) +\
     (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)) == 1)
#define _DP_EMBEDDED_SWITCH_SUPPORT_TYPE            _DP_EMBEDDED_SWITCH_1_DP
#elif(((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) +\
       (_D2_INPUT_PORT_TYPE == _D2_DP_PORT)) == 2)
#define _DP_EMBEDDED_SWITCH_SUPPORT_TYPE            _DP_EMBEDDED_SWITCH_2_DP
#endif

#endif

#ifndef _DP_EMBEDDED_SWITCH_SUPPORT_TYPE
#define _DP_EMBEDDED_SWITCH_SUPPORT_TYPE            _DP_EMBEDDED_SWITCH_NONE
#endif

#define _MHL_SUPPORT                                ((_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) ||\
                                                     (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) ||\
                                                     (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) ||\
                                                     (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) ||\
                                                     (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) ||\
                                                     (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))

#define _MHL_3_0_SUPPORT                            (((_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) &&\
                                                      (_D0_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
                                                     ((_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) &&\
                                                      (_D1_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
                                                     ((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) &&\
                                                      (_D2_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
                                                     ((_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) &&\
                                                      (_D3_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
                                                     ((_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) &&\
                                                      (_D4_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
                                                     ((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) &&\
                                                      (_D5_MHL_VERSION >= _MHL_VERSION_3_0)))

#define _DIGITAL_PORT_SUPPORT                       ((_DVI_SUPPORT == _ON) ||\
                                                     (_HDMI_SUPPORT == _ON) ||\
                                                     (_DP_SUPPORT == _ON))

//--------------------------------------------------
// DP RL6463 Lane Swap Constraint
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6463_SERIES)
#if(((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3)))
#define _DP_RX_ACTIVE_REDUCE_LANE_COUNT_SUPPORT     _OFF
#else
#define _DP_RX_ACTIVE_REDUCE_LANE_COUNT_SUPPORT     _ON
#endif

#else

#define _DP_RX_ACTIVE_REDUCE_LANE_COUNT_SUPPORT     _OFF
#endif

//--------------------------------------------------
// Output Support Option
//--------------------------------------------------
#define _EMBEDDED_DP_TX_PORT_0                      ((_OUTPUT_TYPE_PATH == _DP_TX_2_PATH) ||\
                                                     (_OUTPUT_TYPE_PATH == _DP_TX_4_PATH))

#define _EMBEDDED_DP_TX_PORT_1                      (_OUTPUT_TYPE_PATH == _DP_TX_4_PATH)

#define _EMBEDDED_DP_TX_PORT_2                      ((_OUTPUT_TYPE_PATH == _DP_TX_2_PATH) ||\
                                                     (_OUTPUT_TYPE_PATH == _DP_TX_4_PATH))

#define _EMBEDDED_DP_TX_PORT_3                      ((_OUTPUT_TYPE_PATH == _DP_TX_1_PATH) ||\
                                                     (_OUTPUT_TYPE_PATH == _DP_TX_4_PATH))

#define _EMBEDDED_DP_TX_SUPPORT                     ((_EMBEDDED_DP_TX_PORT_0 == _ON) ||\
                                                     (_EMBEDDED_DP_TX_PORT_1 == _ON) ||\
                                                     (_EMBEDDED_DP_TX_PORT_2 == _ON) ||\
                                                     (_EMBEDDED_DP_TX_PORT_3 == _ON))

//--------------------------------------------------
// HDMI 2.0 Option
//--------------------------------------------------
#define _D0_HDMI_2_0_SUPPORT                        ((_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D0_D1) &&\
                                                     ((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) ||\
                                                      (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)))

#define _D1_HDMI_2_0_SUPPORT                        (((_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D0_D1) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D1_D2_D3) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D1_D2)) &&\
                                                     ((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) ||\
                                                      (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)))


#define _D2_HDMI_2_0_SUPPORT                        (((_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D1_D2_D3) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D1_D2)) &&\
                                                     ((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) ||\
                                                      (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)))

#define _D3_HDMI_2_0_SUPPORT                        (((_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D1_D2_D3) ||\
                                                      (_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3)) &&\
                                                     ((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) ||\
                                                      (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)))

#define _D4_HDMI_2_0_SUPPORT                        ((_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5) &&\
                                                     ((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) ||\
                                                      (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)))

#define _D5_HDMI_2_0_SUPPORT                        ((_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5) &&\
                                                     ((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) ||\
                                                      (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)))

#define _HDMI_2_0_SUPPORT                           ((_D0_HDMI_2_0_SUPPORT == _ON) ||\
                                                     (_D1_HDMI_2_0_SUPPORT == _ON) ||\
                                                     (_D2_HDMI_2_0_SUPPORT == _ON) ||\
                                                     (_D3_HDMI_2_0_SUPPORT == _ON) ||\
                                                     (_D4_HDMI_2_0_SUPPORT == _ON) ||\
                                                     (_D5_HDMI_2_0_SUPPORT == _ON))

//--------------------------------------------------
// Select DP Aux Channel DDC
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RLE0779_SERIES))

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0))
#define _D0_AUX_DDC_CHANNEL                         _D0_AUX_MAP_DDC0_PIN
#else
#define _D0_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC1_PIN
#else
#define _D1_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#elif(_SCALER_TYPE == _RL6492_SERIES)

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0))
#define _D0_AUX_DDC_CHANNEL                         _D0_AUX_MAP_DDC0_PIN
#else
#define _D0_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC0))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC0_PIN
#elif((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC1_PIN
#elif((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC2))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC2_PIN
#else
#define _D1_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC0))
#define _D2_AUX_DDC_CHANNEL                         _D2_AUX_MAP_DDC0_PIN
#elif((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC1))
#define _D2_AUX_DDC_CHANNEL                         _D2_AUX_MAP_DDC1_PIN
#elif((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC2))
#define _D2_AUX_DDC_CHANNEL                         _D2_AUX_MAP_DDC2_PIN
#else
#define _D2_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#elif((_SCALER_TYPE == _RL6369_SERIES) ||\
      (_SCALER_TYPE == _RL6463_SERIES))

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0))
#define _D0_AUX_DDC_CHANNEL                         _D0_AUX_MAP_DDC0_PIN
#elif((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC1))
#define _D0_AUX_DDC_CHANNEL                         _D0_AUX_MAP_DDC1_PIN
#elif((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC2))
#define _D0_AUX_DDC_CHANNEL                         _D0_AUX_MAP_DDC2_PIN
#else
#define _D0_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC0))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC0_PIN
#elif((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC1_PIN
#elif((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC2))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC2_PIN
#else
#define _D1_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC0))
#define _D2_AUX_DDC_CHANNEL                         _D2_AUX_MAP_DDC0_PIN
#elif((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC1))
#define _D2_AUX_DDC_CHANNEL                         _D2_AUX_MAP_DDC1_PIN
#elif((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC2))
#define _D2_AUX_DDC_CHANNEL                         _D2_AUX_MAP_DDC2_PIN
#else
#define _D2_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#endif

#ifndef _D0_AUX_DDC_CHANNEL
#define _D0_AUX_DDC_CHANNEL                         _NO_AUX
#endif
#ifndef _D1_AUX_DDC_CHANNEL
#define _D1_AUX_DDC_CHANNEL                         _NO_AUX
#endif
#ifndef _D2_AUX_DDC_CHANNEL
#define _D2_AUX_DDC_CHANNEL                         _NO_AUX
#endif

//--------------------------------------------------
// Definition of HDCP circuit shared between ports
//--------------------------------------------------
#define _DP_HDCP_ARBITER_SUPPORT                    ((_DP_EMBEDDED_SWITCH_SUPPORT_TYPE != _DP_EMBEDDED_SWITCH_2_DP) &&\
                                                     (((_D0_AUX_DDC_CHANNEL != _NO_AUX) +\
                                                       (_D1_AUX_DDC_CHANNEL != _NO_AUX) +\
                                                       (_D2_AUX_DDC_CHANNEL != _NO_AUX)) > _HW_DP_HDCP_CIRCUIT_COUNT))

//--------------------------------------------------
// Embedded EDID Option
//--------------------------------------------------
#define _EMBEDDED_EDID_SUPPORT                      ((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
                                                     (_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#define _EDID_TABLE_LOCATED_IN_FLASH                (((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
                                                     ((_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))

#define _WRITE_EDID_LOCATION_BY_USER_SUPPORT        (((_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
                                                     ((_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) &&\
                                                      (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)))

#define _D0_HDMI_MULTI_EDID_SUPPORT                 ((_D0_HDMI_SUPPORT == _ON) &&\
                                                     (_D0_MAX_HDMI_EDID_COUNT > 1))

#define _D1_HDMI_MULTI_EDID_SUPPORT                 ((_D1_HDMI_SUPPORT == _ON) &&\
                                                     (_D1_MAX_HDMI_EDID_COUNT > 1))

#define _D2_HDMI_MULTI_EDID_SUPPORT                 ((_D2_HDMI_SUPPORT == _ON) &&\
                                                     (_D2_MAX_HDMI_EDID_COUNT > 1))

#define _D3_HDMI_MULTI_EDID_SUPPORT                 ((_D3_HDMI_SUPPORT == _ON) &&\
                                                     (_D3_MAX_HDMI_EDID_COUNT > 1))

#define _D4_HDMI_MULTI_EDID_SUPPORT                 ((_D4_HDMI_SUPPORT == _ON) &&\
                                                     (_D4_MAX_HDMI_EDID_COUNT > 1))

#define _D5_HDMI_MULTI_EDID_SUPPORT                 ((_D5_HDMI_SUPPORT == _ON) &&\
                                                     (_D5_MAX_HDMI_EDID_COUNT > 1))

#define _HDMI_MULTI_EDID_SUPPORT                    ((_D0_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D1_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D2_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D3_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D4_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
                                                     (_D5_HDMI_MULTI_EDID_SUPPORT == _ON))

//--------------------------------------------------
// Display Spread Spectrum Option
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_LVDS)
#define _DCLK_SPREAD_RANGE                          _LVDS_SPREAD_RANGE
#define _DCLK_SPREAD_SPEED                          _LVDS_SPREAD_SPEED
#elif(_PANEL_STYLE == _PANEL_DPTX)
#define _DCLK_SPREAD_RANGE                          0
#define _DCLK_SPREAD_SPEED                          _SPEED_33K
#elif(_PANEL_STYLE == _PANEL_VBO)
#define _DCLK_SPREAD_RANGE                          _VBO_SPREAD_RANGE
#define _DCLK_SPREAD_SPEED                          _VBO_SPREAD_SPEED
#elif(_PANEL_STYLE == _PANEL_TTL)
#define _DCLK_SPREAD_RANGE                          _TTL_SPREAD_RANGE
#define _DCLK_SPREAD_SPEED                          _TTL_SPREAD_SPEED
#elif(_PANEL_STYLE == _PANEL_NONE)
#define _DCLK_SPREAD_RANGE                          0
#define _DCLK_SPREAD_SPEED                          _SPEED_33K
#endif

#ifndef _DCLK_SPREAD_RANGE_MAX
#define _DCLK_SPREAD_RANGE_MAX                      _DCLK_SPREAD_RANGE
#endif

//--------------------------------------------------
// PCB power Option
//--------------------------------------------------
#define PCB_POWER_5V_DETECT()                       (_TRUE)

//--------------------------------------------------
// PWM Function Support Option
//--------------------------------------------------
#define _PWM_FUNCTION_SUPPORT                       ((_PWM0_EN == _ON) ||\
                                                     (_PWM1_EN == _ON) ||\
                                                     (_PWM2_EN == _ON) ||\
                                                     (_PWM3_EN == _ON) ||\
                                                     (_PWM4_EN == _ON) ||\
                                                     (_PWM5_EN == _ON) ||\
                                                     (_PWM0_PSAV_EN == _ON) ||\
                                                     (_PWM1_PSAV_EN == _ON) ||\
                                                     (_PWM2_PSAV_EN == _ON) ||\
                                                     (_PWM3_PSAV_EN == _ON) ||\
                                                     (_PWM4_PSAV_EN == _ON) ||\
                                                     (_PWM5_PSAV_EN == _ON) ||\
                                                     (_PWM0_PDOW_EN == _ON) ||\
                                                     (_PWM1_PDOW_EN == _ON) ||\
                                                     (_PWM2_PDOW_EN == _ON) ||\
                                                     (_PWM3_PDOW_EN == _ON) ||\
                                                     (_PWM4_PDOW_EN == _ON) ||\
                                                     (_PWM5_PDOW_EN == _ON))

//--------------------------------------------------
// Flash Latch Edge Option
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES) ||\
    (_SCALER_TYPE == _RLE0779_SERIES) ||\
    (_SCALER_TYPE == _RL6463_SERIES) ||\
    (_SCALER_TYPE == _RL6492_SERIES))
#undef _PCB_FLASH_LATCH_SO_DATA_IN_RISING_EDGE
#define _PCB_FLASH_LATCH_SO_DATA_IN_RISING_EDGE     _OFF
#endif

//--------------------------------------------------
// Type-C SMBus Communication Support Definition
//--------------------------------------------------
#define _PORT_CONTROLLER_RTS_SMBUS_SUPPORT          ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) ||\
                                                     (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) ||\
                                                     (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) ||\
                                                     ((_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) && (_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)) ||\
                                                     ((_D1_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) && (_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)) ||\
                                                     ((_D6_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) && (_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)))

//--------------------------------------------------
// Type-C Rts/User Port Controller Connection Detect By User Defined Method
//--------------------------------------------------
#define _PORT_CTRL_RTS_DET_CONNECTION_BY_USER       (((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)) ||\
                                                     ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)) ||\
                                                     ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)))

#define _PORT_CTRL_USER_DET_CONNECTION_BY_USER      (((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_D0_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)) ||\
                                                     ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_D1_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)) ||\
                                                     ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) && (_D6_DP_TYPE_C_DISCRETE_PORT_CTRL_LINK == _DISCRETE_PORT_CTRL_USE_USER_FUNCIOIN)))

//--------------------------------------------------
// Type-C Port Controller Support Definition
//--------------------------------------------------
#define _PORT_CONTROLLER_RTS5400_SERIES_SUPPORT     ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) ||\
                                                     (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES) ||\
                                                     (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_RTS5400_SERIES))

#define _PORT_CONTROLLER_EMBEDDED_SUPPORT           ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) ||\
                                                     (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) ||\
                                                     (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))

#define _PORT_CONTROLLER_USERDECITION_SUPPORT       ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) ||\
                                                     (_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER) ||\
                                                     (_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_USER))


#define _PORT_CONTROLLER_EMB_DEAD_BATTERY_SUPPORT   ((_D0_DP_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON) ||\
                                                     (_D1_DP_TYPE_C_EMB_DEAD_BATTERY_SUPPORT == _ON))

//--------------------------------------------------
// Type C Connector Support Definition
//--------------------------------------------------
#define _D0_DP_TYPE_C_CONNECTOR_SUPPORT             (_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)
#define _D1_DP_TYPE_C_CONNECTOR_SUPPORT             (_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)
#define _D6_DP_TYPE_C_CONNECTOR_SUPPORT             (_D6_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPE_C)

#define _DP_TYPE_C_CONNECTOR_SUPPORT                ((_D0_DP_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_D1_DP_TYPE_C_CONNECTOR_SUPPORT == _ON) ||\
                                                     (_D6_DP_TYPE_C_CONNECTOR_SUPPORT == _ON))

//--------------------------------------------------
// Type C Support Definition
//--------------------------------------------------
#define _D0_DP_TYPE_C_PORT_CTRL_SUPPORT             (_D0_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE)
#define _D1_DP_TYPE_C_PORT_CTRL_SUPPORT             (_D1_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE)
#define _D6_DP_TYPE_C_PORT_CTRL_SUPPORT             (_D6_DP_TYPE_C_PORT_CTRL_TYPE != _PORT_CONTROLLER_NONE)

#define _DP_TYPE_C_PORT_CTRL_SUPPORT                ((_D0_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_D1_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) ||\
                                                     (_D6_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON))

//--------------------------------------------------
// Usb Hub Support Definition
//--------------------------------------------------
#define _USB_HUB_RTS5411_SERIES_SUPPORT             ((_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) ||\
                                                     (_D1_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) ||\
                                                     (_D6_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES))

#define _USB_HUB_USERDECITION_SUPPORT               ((_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER) ||\
                                                     (_D1_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER) ||\
                                                     (_D6_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER))

#define _DP_USB_HUB_SUPPORT                         ((_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE) ||\
                                                     (_D1_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE) ||\
                                                     (_D6_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE))

#define _USB3_RETIMER_SUPPORT                       ((_HW_USB3_RETIMER_SUPPORT == _ON) &&\
                                                     (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON) &&\
                                                     (_DP_USB_HUB_SUPPORT == _ON))

#define _D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT     (((_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) && (_D0_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && (_D0_DP_TYPE_C_HUB_SLAVE_ADDR != 0x00)) || (_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER))

#define _D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT     (((_D1_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) && (_D1_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && (_D1_DP_TYPE_C_HUB_SLAVE_ADDR != 0x00)) || (_D1_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER))

#define _D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT     (((_D6_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_RTS5411_SERIES) && (_D6_DP_TYPE_C_RTK_PC_SMBUS_IIC != _NO_IIC_PIN) && (_D6_DP_TYPE_C_HUB_SLAVE_ADDR != 0x00)) || (_D6_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER))

#define _DP_TYPE_C_HUB_COMMUNICATION_SUPPORT        (_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT ||\
                                                     _D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT ||\
                                                     _D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT)

//--------------------------------------------------
// Bill Board Support Definition
//--------------------------------------------------
#define _BILLBOARD_SCALER_SUPPORT                   ((_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) ||\
                                                     (_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) ||\
                                                     (_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER))

#define _BILLBOARD_HUB_SUPPORT                      (((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)) ||\
                                                     ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)) ||\
                                                     ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)))

#define _D0_BILLBOARD_SUPPORT                       ((_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) || ((_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D0_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D0_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)))
#define _D1_BILLBOARD_SUPPORT                       ((_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) || ((_D1_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D1_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D1_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)))
#define _D6_BILLBOARD_SUPPORT                       ((_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_SCALER) || ((_D6_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED) && (_D6_DP_TYPE_C_BILLBOARD_TYPE == _BILLBOARD_HUB) && (_D6_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)))

#define _BILLBOARD_SUPPORT                          (_D0_BILLBOARD_SUPPORT ||\
                                                     _D1_BILLBOARD_SUPPORT ||\
                                                     _D6_BILLBOARD_SUPPORT)

//--------------------------------------------------
// Definitions of Two Chip Data Exchange Support
//--------------------------------------------------
#if(_D0_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR)
#define _D0_TWO_CHIP_DATA_EXCHANGE_MODE             _DATA_EXCHANGE_MODE_IIC_SLAVE
#else
#define _D0_TWO_CHIP_DATA_EXCHANGE_MODE             _DATA_EXCHANGE_MODE_NONE
#endif

#if(_D1_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR)
#define _D1_TWO_CHIP_DATA_EXCHANGE_MODE             _DATA_EXCHANGE_MODE_IIC_SLAVE
#else
#define _D1_TWO_CHIP_DATA_EXCHANGE_MODE             _DATA_EXCHANGE_MODE_NONE
#endif

#if((_D0_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_IIC_SLAVE) ||\
    (_D1_TWO_CHIP_DATA_EXCHANGE_MODE == _DATA_EXCHANGE_MODE_IIC_SLAVE))
#define _TWO_CHIP_DATA_EXCHANGE_MODE                _DATA_EXCHANGE_MODE_IIC_SLAVE
#define _TWO_CHIP_EXCHANGE_RXBUF_LENGTH             15
#else
#define _TWO_CHIP_DATA_EXCHANGE_MODE                _DATA_EXCHANGE_MODE_NONE
#define _TWO_CHIP_EXCHANGE_RXBUF_LENGTH             0
#endif

//--------------------------------------------------
// Definitions of Two Chip Data Exchange Support
//--------------------------------------------------
#if((_D0_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR) && (_D1_DP_REPEATER_TYPE == _REPEATER_NONE))
#define _DP_REPEATER_SLAVE_ADDR                     _D0_DP_REPEATER_SLAVE_ADDR
#define _DP_REPEATER_IIC                            _D0_DP_REPEATER_IIC
#elif((_D1_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR) && (_D0_DP_REPEATER_TYPE == _REPEATER_NONE))
#define _DP_REPEATER_SLAVE_ADDR                     _D1_DP_REPEATER_SLAVE_ADDR
#define _DP_REPEATER_IIC                            _D1_DP_REPEATER_IIC
#elif((_D0_DP_REPEATER_TYPE == _REPEATER_NONE) && (_D1_DP_REPEATER_TYPE == _REPEATER_NONE))
#define _DP_REPEATER_SLAVE_ADDR                     _REPEATER_NONE
#define _DP_REPEATER_IIC                            _NO_IIC_PIN
#else
#define _DP_REPEATER_SLAVE_ADDR                     _D0_DP_REPEATER_SLAVE_ADDR
#define _DP_REPEATER_IIC                            _D0_DP_REPEATER_IIC
#endif

//--------------------------------------------------
// Macro of DDR Poewr Release Time Control
//--------------------------------------------------
#define PCB_DDR_POWER_RELEASE_TIME(x)               {\
                                                        ScalerTimerDelayXms(x);\
                                                    }

//--------------------------------------------------
// Macro of VcckOff Poewr Release Time Control
//--------------------------------------------------
#define PCB_VCCKOFF_POWER_RELEASE_TIME(x)           {\
                                                        ScalerTimerDelayXms(x);\
                                                    }

//--------------------------------------------------
// Macro of TypeC Pmic Support Definition
//--------------------------------------------------
#define _TYPE_C_PMIC_FW_OVP_UVP_SUPPORT             _OFF
#define _TYPE_C_PMIC_VOLTAGE_COMPENSATION           _OFF
#if(_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
#if(_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON)
#warning "_TYPE_C_PMIC_VOLTAGE_COMPENSATION Should Be _OFF!!!"
#endif
#endif

#define _TYPE_C_PMIC_CHECK_SUPPORT                  ((_TYPE_C_PMIC_FW_OVP_UVP_SUPPORT == _ON) ||\
                                                    (_TYPE_C_PMIC_VOLTAGE_COMPENSATION == _ON) ||\
                                                    (_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON) ||\
                                                    (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE) ||\
                                                    (_TYPE_C_PMIC_INT_PIN_CHECK_METHOD != _TYPE_C_PMIC_INT_PIN_NONE))

//--------------------------------------------------
// Code Signature ISP DDC Select When Initial
//--------------------------------------------------
#define _CODE_DIGITAL_SIGNATURE_ISP_SEL_INITIAL     (WORD)(1U << _CODE_DIGITAL_SIGNATURE_HUB_DDC_SEL)

//--------------------------------------------------
// Code Signature DDC ISP Select After Handshake
//--------------------------------------------------
#if(_A0_CODE_DIGITAL_SIGNATURE_ISP_EN == _ENABLE)
#if(_SCALER_TYPE == _RL6463_SERIES)
#define _A0_SIGNATURE_ISP                           ((_PIN_100 == _PIN_100_DDCSCLVGA1) ? _VGA_DDC2 : _VGA_DDC)
#else
#define _A0_SIGNATURE_ISP                           _VGA_DDC
#endif
#else
#define _A0_SIGNATURE_ISP                           _NO_DDC
#endif

#if(_D0_CODE_DIGITAL_SIGNATURE_ISP_EN == _ENABLE)
#define _D0_SIGNATURE_ISP                           _D0_DDC_CHANNEL_SEL
#else
#define _D0_SIGNATURE_ISP                           _NO_DDC
#endif

#if(_D1_CODE_DIGITAL_SIGNATURE_ISP_EN == _ENABLE)
#define _D1_SIGNATURE_ISP                           _D1_DDC_CHANNEL_SEL
#else
#define _D1_SIGNATURE_ISP                           _NO_DDC
#endif

#if(_D2_CODE_DIGITAL_SIGNATURE_ISP_EN == _ENABLE)
#define _D2_SIGNATURE_ISP                           _D2_DDC_CHANNEL_SEL
#else
#define _D2_SIGNATURE_ISP                           _NO_DDC
#endif

#if(_D3_CODE_DIGITAL_SIGNATURE_ISP_EN == _ENABLE)
#define _D3_SIGNATURE_ISP                           _D3_DDC_CHANNEL_SEL
#else
#define _D3_SIGNATURE_ISP                           _NO_DDC
#endif

#if(_D4_CODE_DIGITAL_SIGNATURE_ISP_EN == _ENABLE)
#define _D4_SIGNATURE_ISP                           _D4_DDC_CHANNEL_SEL
#else
#define _D4_SIGNATURE_ISP                           _NO_DDC
#endif

#if(_D5_CODE_DIGITAL_SIGNATURE_ISP_EN == _ENABLE)
#define _D5_SIGNATURE_ISP                           _D5_DDC_CHANNEL_SEL
#else
#define _D5_SIGNATURE_ISP                           _NO_DDC
#endif

#define _CODE_DIGITAL_SIGNATURE_ISP_SEL_EN          ((WORD)((1U << _A0_SIGNATURE_ISP) |\
                                                            (1U << _D0_SIGNATURE_ISP) |\
                                                            (1U << _D1_SIGNATURE_ISP) |\
                                                            (1U << _D2_SIGNATURE_ISP) |\
                                                            (1U << _D3_SIGNATURE_ISP) |\
                                                            (1U << _D4_SIGNATURE_ISP) |\
                                                            (1U << _D5_SIGNATURE_ISP)))

//--------------------------------------------------
// Package option setting
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6369_SERIES)
#include "RL6369_Series_Pin_Mapping.h"
#endif

#if(_SCALER_TYPE == _RL6432_SERIES)
#include "RL6432_Series_Pin_Mapping.h"
#endif

#if(_SCALER_TYPE == _RL6449_SERIES)
#include "RL6449_Series_Pin_Mapping.h"
#endif

#if(_SCALER_TYPE == _RL6463_SERIES)
#include "RL6463_Series_Pin_Mapping.h"
#endif
//--------------------------------------------------
// Enum of Pins support user to adjust configuration
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6410_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_Y6,
    _CONFIG_PIN_Y5,
    _CONFIG_PIN_AA6,
    _CONFIG_PIN_AA5,
    _CONFIG_PIN_L4,
    _CONFIG_PIN_W6,
    _CONFIG_PIN_F4,
    _CONFIG_PIN_W5,
    _CONFIG_PIN_AJ3,
    _CONFIG_PIN_AJ1,
    _CONFIG_PIN_AJ2,
    _CONFIG_PIN_AK3,
    _CONFIG_PIN_AK2,
    _CONFIG_PIN_AL3,
    _CONFIG_PIN_AL2,
    _CONFIG_PIN_AL1,
    _CONFIG_PIN_AM1,
    _CONFIG_PIN_AH9,
    _CONFIG_PIN_AH8,
    _CONFIG_PIN_AJ9,
    _CONFIG_PIN_AJ8,
    _CONFIG_PIN_AL5,
    _CONFIG_PIN_AK5,
    _CONFIG_PIN_AJ5,
    _CONFIG_PIN_AK4,
    _CONFIG_PIN_AL4,
    _CONFIG_PIN_AM4,
    _CONFIG_PIN_AM2,
    _CONFIG_PIN_AM3,
    _CONFIG_PIN_G7,
    _CONFIG_PIN_J7,
    _CONFIG_PIN_H6,
    _CONFIG_PIN_AD28,
    _CONFIG_PIN_AH27,
    _CONFIG_PIN_N29_OFF_REGION,
    _CONFIG_PIN_N28_OFF_REGION,
    _CONFIG_PIN_M29_OFF_REGION,
    _CONFIG_PIN_M28_OFF_REGION,
    _CONFIG_PIN_J29_OFF_REGION,
    _CONFIG_PIN_AJ28,
    _CONFIG_PIN_N27_OFF_REGION,
    _CONFIG_PIN_K27_OFF_REGION,
    _CONFIG_PIN_M27_OFF_REGION,
    _CONFIG_PIN_K29_OFF_REGION,
    _CONFIG_PIN_J28_OFF_REGION,
    _CONFIG_PIN_J27_OFF_REGION,
    _CONFIG_PIN_K28_OFF_REGION,
    _CONFIG_PIN_AH21,
    _CONFIG_PIN_AK21,
    _CONFIG_PIN_AJ21,
    _CONFIG_PIN_AJ20,
    _CONFIG_PIN_AH20,
    _CONFIG_PIN_AL21,
    _CONFIG_PIN_AA29,
    _CONFIG_PIN_AA28,
    _CONFIG_PIN_AG25,
    _CONFIG_PIN_AH26,
    _CONFIG_PIN_AG26,
    _CONFIG_PIN_AJ26,
    _CONFIG_PIN_AF28,
    _CONFIG_PIN_AG24,
    _CONFIG_PIN_AF24,
    _CONFIG_PIN_AE28,
    _CONFIG_PIN_AJ27,
    _CONFIG_PIN_AG29,
    _CONFIG_PIN_AH25,
    _CONFIG_PIN_AF29,
    _CONFIG_PIN_AJ25,
    _CONFIG_PIN_AG28,
    _CONFIG_PIN_AH24,
    _CONFIG_PIN_AF27,
    _CONFIG_PIN_AJ24,
    _CONFIG_PIN_AG27,
    _CONFIG_PIN_AJ18,
    _CONFIG_PIN_AK18,
    _CONFIG_PIN_AE20,
    _CONFIG_PIN_AL18,
    _CONFIG_PIN_AM18,
    _CONFIG_PIN_AL19,
    _CONFIG_PIN_AM19,
    _CONFIG_PIN_AJ11,
    _CONFIG_PIN_AJ12,
    _CONFIG_PIN_AG6,
    _CONFIG_PIN_AJ4,
    _CONFIG_PIN_AF7,
    _CONFIG_PIN_AF6,
    _CONFIG_PIN_AG7,
    _CONFIG_PIN_AH7,
    _CONFIG_PIN_AH6,
    _CONFIG_PIN_AH5,
    _CONFIG_PIN_AG8,
    _CONFIG_PIN_AG9,
    _CONFIG_PIN_J6,
    _CONFIG_PIN_J5,
    _CONFIG_PIN_K6,
    _CONFIG_PIN_K5,
    _CONFIG_PIN_L6,
    _CONFIG_PIN_L5,
    _CONFIG_PIN_M6,
    _CONFIG_PIN_M5,
    _CONFIG_PIN_H7,
    _CONFIG_PIN_K7,
    _CONFIG_PIN_C8,
    _CONFIG_PIN_N6,
    _CONFIG_PIN_C6,
    _CONFIG_PIN_N5,
} EnumConfigPin;
#elif((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_21,
    _CONFIG_PIN_36,
    _CONFIG_PIN_46,
    _CONFIG_PIN_52,
    _CONFIG_PIN_99,
} EnumConfigPin;

#elif(_SCALER_TYPE == _RL6432_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_1,
    _CONFIG_PIN_3,
    _CONFIG_PIN_15,
    _CONFIG_PIN_53,
    _CONFIG_PIN_54,
    _CONFIG_PIN_97,
    _CONFIG_PIN_169_OFF_REGION,
    _CONFIG_PIN_192,
    _CONFIG_PIN_193,
    _CONFIG_PIN_197,
    _CONFIG_PIN_198,
} EnumConfigPin;
#elif(_SCALER_TYPE == _RL6449_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_1,
    _CONFIG_PIN_14,
    _CONFIG_PIN_65,
    _CONFIG_PIN_66,
    _CONFIG_PIN_67,
    _CONFIG_PIN_68,
    _CONFIG_PIN_69,
    _CONFIG_PIN_70,
    _CONFIG_PIN_150_OFF_REGION,
    _CONFIG_PIN_151_OFF_REGION,
    _CONFIG_PIN_152_OFF_REGION,
    _CONFIG_PIN_153_OFF_REGION,
    _CONFIG_PIN_158_OFF_REGION,
    _CONFIG_PIN_159_OFF_REGION,
    _CONFIG_PIN_160_OFF_REGION,
    _CONFIG_PIN_161_OFF_REGION,
    _CONFIG_PIN_184,
    _CONFIG_PIN_195,
} EnumConfigPin;
#elif(_SCALER_TYPE == _RLE0779_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_N3,
} EnumConfigPin;
#elif(_SCALER_TYPE == _RL6463_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_21,
} EnumConfigPin;
#elif(_SCALER_TYPE == _RL6492_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_9,
} EnumConfigPin;
#endif

//--------------------------------------------------
// SPI Funtion Pinshare Config Option
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6410_SERIES)
#define _PIN_SPI_CLK_SELECTED                       (_PIN_AH21 == 4)
#define _PIN_SPI_SI_SELECTED                        (_PIN_AK21 == 4)
#define _PIN_SPI_SO_SELECTED                        (_PIN_AJ21 == 4)
#define _PIN_SPI_CEB0_SELECTED                      (_PIN_AJ20 == 4)
#define _PIN_SPI_CEB1_SELECTED                      (_PIN_AH20 == 4)
#endif

#if(_SCALER_TYPE == _RL6432_SERIES)
#define _PIN_SPI_CLK_SELECTED                       (_PIN_168_OFF_REGION == 8)
#define _PIN_SPI_SI_SELECTED                        (_PIN_169_OFF_REGION == 8)
#define _PIN_SPI_SO_SELECTED                        (_PIN_170_OFF_REGION == 8)
#define _PIN_SPI_CEB0_SELECTED                      (_PIN_171_OFF_REGION == 8)
#define _PIN_SPI_CEB1_SELECTED                      (_PIN_172_OFF_REGION == 8)
#endif

#if(_SCALER_TYPE == _RL6449_SERIES)
#define _PIN_SPI_CLK_SELECTED                       (_PIN_153_OFF_REGION == 8)
#define _PIN_SPI_SI_SELECTED                        (_PIN_154_OFF_REGION == 8)
#define _PIN_SPI_SO_SELECTED                        (_PIN_155_OFF_REGION == 8)
#define _PIN_SPI_CEB0_SELECTED                      (_PIN_156_OFF_REGION == 8)
#define _PIN_SPI_CEB1_SELECTED                      (_PIN_157_OFF_REGION == 8)
#endif

#if(_SCALER_TYPE == _RL6492_SERIES)
#define _PIN_30_GPI                                 0x00
#define _PIN_30_GPO_PP                              0x01
#define _PIN_30_GPO_OD                              0x02
#define _PIN_30_PWM4_PP                             0x03
#define _PIN_30_PWM4_OD                             0x04
#define _PIN_30_TCON11                              0x05
#define _PIN_30_T0                                  0x06
#define _PIN_30_CLKO                                0x07
#define _PIN_30_USB_SPI_CLK                         0x80
#define _PIN_30_NC                                  _PIN_30_GPO_PP
#define _PIN_SPI_CLK_SELECTED                       (_PIN_30 == _PIN_30_USB_SPI_CLK)

#define _PIN_32_GPI                                 0x00
#define _PIN_32_GPO_PP                              0x01
#define _PIN_32_GPO_OD                              0x02
#define _PIN_32_TCON0                               0x03
#define _PIN_32_T1                                  0x04
#define _PIN_32_TTL_DEN                             0x05
#define _PIN_32_TEST4B_OUT0                         0x06
#define _PIN_32_TEST4B_OUT1                         0x07
#define _PIN_32_USB_SPI_SI                          0x80
#define _PIN_32_NC                                  _PIN_32_GPO_PP
#define _PIN_SPI_SI_SELECTED                        (_PIN_32 == _PIN_32_USB_SPI_SI)

#define _PIN_33_GPI                                 0x00
#define _PIN_33_GPO_PP                              0x01
#define _PIN_33_GPO_OD                              0x02
#define _PIN_33_PWM3_PP                             0x03
#define _PIN_33_PWM3_OD                             0x04
#define _PIN_33_TCON10                              0x05
#define _PIN_33_T2                                  0x06
#define _PIN_33_DCLK                                0x07
#define _PIN_33_USB_SPI_SO                          0x80
#define _PIN_33_NC                                  _PIN_33_GPO_PP
#define _PIN_SPI_SO_SELECTED                        (_PIN_33 == _PIN_33_USB_SPI_SO)

#define _PIN_37_GPI                                 0x00
#define _PIN_37_GPO_PP                              0x01
#define _PIN_37_GPO_OD                              0x02
#define _PIN_37_PWM5_PP                             0x03
#define _PIN_37_PWM5_OD                             0x04
#define _PIN_37_TCON12                              0x05
#define _PIN_37_IRQB                                0x06
#define _PIN_37_TTL_DVS                             0x07
#define _PIN_37_USB_SPI_CEB0                        0x80
#define _PIN_37_NC                                  _PIN_37_GPO_PP
#define _PIN_SPI_CEB0_SELECTED                      (_PIN_37 == _PIN_37_USB_SPI_CEB0)

#define _PIN_38_GPI                                 0x00
#define _PIN_38_GPO_PP                              0x01
#define _PIN_38_GPO_OD                              0x02
#define _PIN_38_TCON1                               0x03
#define _PIN_38_T2EX                                0x04
#define _PIN_38_TTL_DHS                             0x05
#define _PIN_38_INT0                                0x06
#define _PIN_38_USB_SPI_CEB1                        0x80
#define _PIN_38_NC                                  _PIN_38_GPO_PP
#define _PIN_SPI_CEB1_SELECTED                      (_PIN_38 == _PIN_38_USB_SPI_CEB1)
#endif

//--------------------------------------------------
// PWM Reset by TCON or DVS SEL
//--------------------------------------------------
#define _DVS                                        0
#define _TCON                                       1

#endif // End of #ifndef __PCB_OPTION_H__
