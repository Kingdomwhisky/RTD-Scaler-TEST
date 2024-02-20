/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerCommonTimerFunctionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#define _RX0_WD_TIMER_DP_EVENT_COUNT                 2
#else
#define _RX0_WD_TIMER_DP_EVENT_COUNT                 0
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#define _RX1_WD_TIMER_DP_EVENT_COUNT                 2
#else
#define _RX1_WD_TIMER_DP_EVENT_COUNT                 0
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
#define _RX2_WD_TIMER_DP_EVENT_COUNT                 2
#else
#define _RX2_WD_TIMER_DP_EVENT_COUNT                 0
#endif


#define _WD_TIMER_EVENT_COUNT                        (10 + _RX0_WD_TIMER_DP_EVENT_COUNT + _RX1_WD_TIMER_DP_EVENT_COUNT + _RX2_WD_TIMER_DP_EVENT_COUNT) // For HDMI 2.0 / MHL 3.0 / DP 1.2

//--------------------------------------------------
// Definitions of TimeOut
//--------------------------------------------------
#define _TIMER_WAIT_EVENT_TIMEOUT                    90 // unit: ms

//--------------------------------------------------
// Definitions of Timer counter setting
//--------------------------------------------------
#define LOAD_TIMER_COUNTER(pusCounter)               {\
                                                         g_bNotifyTimer2Int = _FALSE;\
                                                         *(pusCounter) = g_usTimerCounter;\
                                                         if(g_bNotifyTimer2Int == _TRUE)\
                                                         {\
                                                             *(pusCounter) = g_usTimerCounter;\
                                                         }\
                                                     }
#define STORE_TIMER_COUNTER(x)                       {\
                                                         g_bNotifyTimer2Int = _FALSE;\
                                                         g_usTimerCounter = (x);\
                                                         if(g_bNotifyTimer2Int == _TRUE)\
                                                         {\
                                                             g_usTimerCounter = (x);\
                                                         }\
                                                     }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef enum
{
    _SCALER_WD_TIMER_EVENT_INVALID = 0,
#if(_D0_DP_EXIST == _ON)
    _SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY,
#endif
#if(_D1_DP_EXIST == _ON)
    _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY,
#endif
    _SCALER_WD_TIMER_EVENT_RX0_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX2_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX3_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX4_HDMI_RR_RETRY,
    _SCALER_WD_TIMER_EVENT_RX5_HDMI_RR_RETRY,

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
    _SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT,
    _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER,
    _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER,
    _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG,
    _SCALER_WD_TIMER_EVENT_PD_RX0_STATE_TO_READY,
#if((_TYPE_C_PMIC_TYPE != _PMIC_NONE) && (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0))
    _SCALER_WD_TIMER_EVENT_PMIC_RX0_FW_OCP_DELAY,
#endif
#endif
#endif

#if((_D0_DP_EXIST == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
    _SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE,
#endif
#if((_D1_DP_EXIST == _ON) && (_DP_HDCP_2_2_SUPPORT == _ON))
    _SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE,
#endif

    _SCALER_WD_TIMER_EVENT_END,
    _SCALER_WD_TIMER_EVENT_COUNT = _SCALER_WD_TIMER_EVENT_END,
    _SCALER_WD_TIMER_EVENT_NULL = 0xFF,
} EnumScalerWDTimerEventID;

typedef struct
{
    EnumScalerWDTimerEventID enumEventID;
    WORD usTime;
} StructWDTimerEventType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_RECORD_TIMER_SUPPORT == _ON)
extern void ScalerTimerResetRecordTimer_WDINT(void);
extern BYTE ScalerTimerGetRecordTimer_EXINT0(void);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerTimerWDInitial(void);
extern void ScalerTimerWDActivateTimerEvent_EXINT0(WORD usTime, EnumScalerWDTimerEventID enumEventID);
extern void ScalerTimerWDCancelTimerEvent(EnumScalerWDTimerEventID enumEventID);

#if((_DP_SUPPORT == _ON) || ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
extern void ScalerTimerWDCancelTimerEvent_EXINT0(EnumScalerWDTimerEventID enumEventID);
#endif

#endif

extern void ScalerTimerSetTimerCount(EnumScalerTimerOperationMode enumOperationMode);
extern void ScalerTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void ScalerTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
extern void ScalerTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID);
#if((_DP_SUPPORT == _ON) || (_TMDS_HDCP_2_2_SUPPORT == _ON) || ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
extern void ScalerTimerCancelTimerEvent_EXINT0(EnumScalerTimerEventID enumEventID);
#endif

#if((_HDCP_2_2_SUPPORT == _ON) || (_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON))
extern BYTE ScalerTimerPollingFlagProc_EXINT0(BYTE ucTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
#endif

#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
extern BYTE ScalerTimerPollingFlagProc_WDINT(BYTE ucTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
#endif

