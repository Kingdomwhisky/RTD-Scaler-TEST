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
// ID Code      : ScalerCommonTimerFunction.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_TIMERFUNCTION__

#include "ScalerCommonFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Instant Timer0/1
//--------------------------------------------------
/////////////////
// Active Mode //
/////////////////

#if(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_M_N)
#define _TIMER_COUNT_TEMP1                      ((DWORD)_M2PLL_PLL_N * _M2PLL_PLL_O)
#define _TIMER_COUNT_TEMP2                      ((DWORD)_EXT_XTAL * _M2PLL_PLL_M)
#elif(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_N_F)
#define _TIMER_COUNT_TEMP1                      1
#define _TIMER_COUNT_TEMP2                      ((DWORD)_M2PLL_CLK_KHZ)
#endif

#define _TIMER_COUNT_TEMP                       ((DWORD)12 * _TIMER_COUNT_TEMP1 * _FLASH_CLK_DIV * _MCU_CLK_DIV)

////////////////////////////
// Power Saving/Down Mode //
////////////////////////////
#define _TIMER_COUNT_PS_TEMP                    ((DWORD)12 * _FLASH_CLK_PS_DIV * _MCU_CLK_PS_DIV)

//////////////////////////////////////////////////////
// Power Saving/Down Fast Mode for DP Aux Handshake //
//////////////////////////////////////////////////////
#define _TIMER_COUNT_PS_FAST_TEMP               ((DWORD)12 * _FLASH_CLK_PS_FAST_DIV * _MCU_CLK_PS_DIV)

//////////////////
// Initial Mode //
//////////////////
#define _TIMER_COUNT_IN_TEMP                    ((DWORD)12 * _FLASH_CLK_IN_DIV * _MCU_CLK_DIV)

////////////////////////////////////////////////////////////////////////////
// Active Mode --> for switching to a higher flash speed when OSD is used //
////////////////////////////////////////////////////////////////////////////
#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
#define _TIMER_COUNT_OSD_TEMP                   ((DWORD)12 * _TIMER_COUNT_TEMP1 * _FLASH_CLK_FAST_DIV * _MCU_CLK_DIV)
#endif

#define _TIMER_COUNT_TEMP_PS_FAST1              (_IDLE_TIME * _FLASH_CLK_PS_FAST_DIV / _FLASH_CLK_PS_DIV)
#define _TIMER_COUNT_TEMP_PS_FAST2              ((WORD)(((DWORD)_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_FAST_TEMP / 2)) / _TIMER2_COUNT_PS_FAST_TEMP))
#define _TIMER_COUNT_TEMP_PS                    ((WORD)(((DWORD)_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_TEMP / 2)) / _TIMER2_COUNT_PS_TEMP))

#define _TIMER01_TEMP_COUNT_M2PLL               (((DWORD)_TIMER_COUNT_TEMP2 + (_TIMER_COUNT_TEMP / 2)) / _TIMER_COUNT_TEMP)

#define _TIMER01_TEMP_COUNT_IOSC_FAST           (((DWORD)_INTERNAL_OSC_XTAL + (_TIMER_COUNT_PS_FAST_TEMP / 2)) / _TIMER_COUNT_PS_FAST_TEMP)
#define _TIMER01_TEMP_COUNT_IOSC                (((DWORD)_INTERNAL_OSC_XTAL + (_TIMER_COUNT_PS_TEMP / 2)) / _TIMER_COUNT_PS_TEMP)
#define _TIMER01_TEMP_COUNT_XTAL                (((DWORD)_EXT_XTAL + (_TIMER_COUNT_IN_TEMP / 2)) / _TIMER_COUNT_IN_TEMP)

#define _TIMER01_TEMP_COUNT_OSD                 (((DWORD)_TIMER_COUNT_TEMP2 + (_TIMER_COUNT_OSD_TEMP / 2)) / _TIMER_COUNT_OSD_TEMP)

//--------------------------------------------------
// Definitions of Timer1 for Serial Port
//--------------------------------------------------
/////////////////
// Active Mode //
/////////////////
#define _TIMER1_UART_COUNT_TEMP                 ((DWORD)4 * 16 * _TIMER_COUNT_TEMP1 * _FLASH_CLK_DIV * _MCU_CLK_DIV * _UART_BAUD_RATE_POWER_NORMAL / 1000)
#define _TIMER1_UART_COUNT_BYTE                 (0x100 - ((BYTE)(((DWORD)_TIMER_COUNT_TEMP2 + (_TIMER1_UART_COUNT_TEMP / 2)) / _TIMER1_UART_COUNT_TEMP)))


////////////////////////////
// Power Saving/Down Mode //
////////////////////////////
#define _TIMER1_UART_COUNT_PS_TEMP              ((DWORD)4 * 16 * _FLASH_CLK_PS_DIV * _MCU_CLK_PS_DIV * _UART_BAUD_RATE_POWER_SAVING / 1000)
#define _TIMER1_UART_COUNT_PS_BYTE              (0x100 - ((BYTE)(((DWORD)_INTERNAL_OSC_XTAL + (_TIMER1_UART_COUNT_PS_TEMP / 2)) / _TIMER1_UART_COUNT_PS_TEMP)))

//////////////////////////////////////////////////////
// Power Saving/Down Fast Mode for DP Aux Handshake //
//////////////////////////////////////////////////////
#define _TIMER1_UART_COUNT_PS_FAST_TEMP         ((DWORD)4 * 16 * _FLASH_CLK_PS_FAST_DIV * _MCU_CLK_PS_DIV * _UART_BAUD_RATE_POWER_SAVING / 1000)
#define _TIMER1_UART_COUNT_PS_FAST_BYTE         (0x100 - ((BYTE)(((DWORD)_INTERNAL_OSC_XTAL + (_TIMER1_UART_COUNT_PS_FAST_TEMP / 2)) / _TIMER1_UART_COUNT_PS_FAST_TEMP)))

//////////////////
// Initial Mode //
//////////////////
#define _TIMER1_UART_COUNT_IN_TEMP              ((DWORD)4 * 16  * _FLASH_CLK_IN_DIV * _MCU_CLK_DIV * _UART_BAUD_RATE_POWER_NORMAL / 1000)
#define _TIMER1_UART_COUNT_IN_BYTE              (0x100 - ((BYTE)(((DWORD)_EXT_XTAL + (_TIMER1_UART_COUNT_IN_TEMP / 2)) / _TIMER1_UART_COUNT_IN_TEMP)))

////////////////////////////////////////////////////////////////////////////
// Active Mode --> for switching to a higher flash speed when OSD is used //
////////////////////////////////////////////////////////////////////////////
#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
#define _TIMER1_UART_COUNT_OSD_TEMP             ((DWORD)4 * 16  * _TIMER_COUNT_TEMP1 * _FLASH_CLK_FAST_DIV * _MCU_CLK_DIV * _UART_BAUD_RATE_POWER_NORMAL / 1000)
#define _TIMER1_UART_COUNT_OSD_BYTE             (0x100 - ((BYTE)((((DWORD)_TIMER_COUNT_TEMP2 + (_TIMER1_UART_COUNT_OSD_TEMP / 2)) / _TIMER1_UART_COUNT_OSD_TEMP))))
#endif

//--------------------------------------------------
// Definitions of Timer2
//--------------------------------------------------
#define _EVENT_TIME_MAX                         61000

/////////////////
// Active Mode //
/////////////////
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_TEMP                      ((DWORD)12 * 4 * _TIMER_COUNT_TEMP1 * _FLASH_CLK_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_TEMP                      ((DWORD)12 * _TIMER_COUNT_TEMP1 * _FLASH_CLK_DIV * _MCU_CLK_DIV)
#endif

#define _TIMER2_COUNT_NUM                       (0xFFFF - ((WORD)(((DWORD)_TIMER_COUNT_TEMP2 + (_TIMER2_COUNT_TEMP / 2)) / _TIMER2_COUNT_TEMP)))

#define _TIMER2_COUNT_LBYTE                     (_TIMER2_COUNT_NUM & 0x00FF)
#define _TIMER2_COUNT_HBYTE                     (_TIMER2_COUNT_NUM >> 8)

////////////////////////////
// Power Saving/Down Mode //
////////////////////////////
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_PS_TEMP                   ((DWORD)12 * 4 * _FLASH_CLK_PS_DIV * _MCU_CLK_PS_DIV)
#else
#define _TIMER2_COUNT_PS_TEMP                   ((DWORD)12 * _FLASH_CLK_PS_DIV * _MCU_CLK_PS_DIV)
#endif
#define _TIMER2_COUNT_PS_NUM                    (0xFFFF - ((WORD)(((DWORD)_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_TEMP / 2)) / _TIMER2_COUNT_PS_TEMP)))

#define _TIMER2_COUNT_PS_LBYTE                  (_TIMER2_COUNT_PS_NUM & 0x00FF)
#define _TIMER2_COUNT_PS_HBYTE                  (_TIMER2_COUNT_PS_NUM >> 8)

//////////////////////////////////////////////////////
// Power Saving/Down Fast Mode for DP Aux Handshake //
//////////////////////////////////////////////////////
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_PS_FAST_TEMP              ((DWORD)12 * 4 * _FLASH_CLK_PS_FAST_DIV * _MCU_CLK_PS_DIV)
#else
#define _TIMER2_COUNT_PS_FAST_TEMP              ((DWORD)12 * _FLASH_CLK_PS_FAST_DIV * _MCU_CLK_PS_DIV)
#endif
#define _TIMER2_COUNT_PS_FAST_NUM               (0xFFFF - ((WORD)(((DWORD)_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_FAST_TEMP / 2)) / _TIMER2_COUNT_PS_FAST_TEMP)))

#define _TIMER2_COUNT_PS_FAST_LBYTE             (_TIMER2_COUNT_PS_FAST_NUM & 0x00FF)
#define _TIMER2_COUNT_PS_FAST_HBYTE             (_TIMER2_COUNT_PS_FAST_NUM >> 8)

//////////////////
// Initial Mode //
//////////////////
#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_IN_TEMP                   ((DWORD)12 * 4 * _FLASH_CLK_IN_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_IN_TEMP                   ((DWORD)12 * _FLASH_CLK_IN_DIV * _MCU_CLK_DIV)
#endif
#define _TIMER2_COUNT_IN_NUM                    (0xFFFF - ((WORD)(((DWORD)_EXT_XTAL + (_TIMER2_COUNT_IN_TEMP / 2)) / _TIMER2_COUNT_IN_TEMP)))

#define _TIMER2_COUNT_IN_LBYTE                  (_TIMER2_COUNT_IN_NUM & 0x00FF)
#define _TIMER2_COUNT_IN_HBYTE                  (_TIMER2_COUNT_IN_NUM >> 8)

///////////////
// Idle Mode //
///////////////
#define _IDLE_TIME_TEMP                         ((DWORD)0x0000FFFF / (((DWORD)_INTERNAL_OSC_XTAL + _TIMER2_COUNT_PS_TEMP) / _TIMER2_COUNT_PS_TEMP))
#define _IDLE_TIME                              ((_IDLE_TIME_TEMP < 100) ? _IDLE_TIME_TEMP : 100) // Avoid_TIMER2_COUNT_IDLE_NUM Overflow
#define _TIMER2_COUNT_IDLE_NUM                  (0xFFFF - ((WORD)((((DWORD)_INTERNAL_OSC_XTAL + (_TIMER2_COUNT_PS_TEMP / 2)) / _TIMER2_COUNT_PS_TEMP) * _IDLE_TIME)))

#define _TIMER2_COUNT_IDLE_LBYTE                (_TIMER2_COUNT_IDLE_NUM & 0x00FF)
#define _TIMER2_COUNT_IDLE_HBYTE                (_TIMER2_COUNT_IDLE_NUM >> 8)

////////////////////////////////////////////////////////////////////////////
// Active Mode --> for switching to a higher flash speed when OSD is used //
////////////////////////////////////////////////////////////////////////////
#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
#define _TIMER2_COUNT_OSD_TEMP                  ((DWORD)12 * 4 * _TIMER_COUNT_TEMP1 * _FLASH_CLK_FAST_DIV * _MCU_CLK_DIV)
#else
#define _TIMER2_COUNT_OSD_TEMP                  ((DWORD)12 * _TIMER_COUNT_TEMP1 * _FLASH_CLK_FAST_DIV * _MCU_CLK_DIV)
#endif

#define _TIMER2_COUNT_OSD_NUM                   (0xFFFF - ((WORD)(((DWORD)_TIMER_COUNT_TEMP2 + (_TIMER2_COUNT_OSD_TEMP / 2)) / _TIMER2_COUNT_OSD_TEMP)))

#define _TIMER2_COUNT_OSD_LBYTE                 (_TIMER2_COUNT_OSD_NUM & 0x00FF)
#define _TIMER2_COUNT_OSD_HBYTE                 (_TIMER2_COUNT_OSD_NUM >> 8)
#endif

//--------------------------------------------------
// Definitions of Watch Dog Timer Default Trigger Time
//--------------------------------------------------
#define _TIEMR_WD_DEFAULT_COUNT                 0xFFF // about 586ms with 14.318MHz Reference Clk

#define GET_TIMER_WD_THRESHOLD_COUNT()          (((WORD)(MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK & 0xF0) << 4) | MCU_FFAE_WATCHDOG_TIMER_THRESHOLD)
#define SET_TIMER_WD_THRESHOLD_COUNT(x)         {\
                                                    if((x) == 0)\
                                                    {\
                                                        MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK = (MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK & 0x0F) | (((1) >> 4) & 0xF0);\
                                                        MCU_FFAE_WATCHDOG_TIMER_THRESHOLD = (BYTE)(1);\
                                                    }\
                                                    else\
                                                    {\
                                                        MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK = (MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK & 0x0F) | (((x) >> 4) & 0xF0);\
                                                        MCU_FFAE_WATCHDOG_TIMER_THRESHOLD = (BYTE)(x);\
                                                    }\
                                                }

//--------------------------------------------------
// Macro of Timer Event Structure
//--------------------------------------------------
#define GET_EVENT_VALID(x)                      (g_pstTimerEvent[x].enumEventID != _SCALER_TIMER_EVENT_INVALID)
#define CLR_EVENT_VALID(x)                      (g_pstTimerEvent[x].enumEventID = _SCALER_TIMER_EVENT_INVALID)

#define GET_EVENT_ID(x)                         (g_pstTimerEvent[x].enumEventID)
#define SET_EVENT_ID(x, y)                      (g_pstTimerEvent[x].enumEventID = (y))

#define GET_EVENT_TIME(x)                       (g_pstTimerEvent[x].usTime)
#define SET_EVENT_TIME(x, y)                    (g_pstTimerEvent[x].usTime = (y))

#define GET_EVENT_RESUME_TIME(x)                (g_pstTimerEvent[x].usTime)
#define SET_EVENT_RESUME_TIME(x, y)             (g_pstTimerEvent[x].usTime = (y))

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Macro of WD Timer Event Structure
//--------------------------------------------------
#define GET_WD_EVENT_VALID(x)                   (g_pstWDTimerEvent[x].enumEventID != _SCALER_WD_TIMER_EVENT_INVALID)
#define CLR_WD_EVENT_VALID(x)                   (g_pstWDTimerEvent[x].enumEventID = _SCALER_WD_TIMER_EVENT_INVALID)

#define GET_WD_EVENT_ID(x)                      (g_pstWDTimerEvent[x].enumEventID)
#define SET_WD_EVENT_ID(x, y)                   (g_pstWDTimerEvent[x].enumEventID = (y))

#define GET_WD_EVENT_TIME(x)                    (g_pstWDTimerEvent[x].usTime)
#define SET_WD_EVENT_TIME(x, y)                 (g_pstWDTimerEvent[x].usTime = (y))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bNotifyTimer2Int = _FALSE;
StructTimerEventTableType g_pstTimerEvent[_TIMER_EVENT_COUNT];

#if(_RECORD_TIMER_SUPPORT == _ON)
WORD g_usTimerRecordStartTime;
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
bit g_bWDTimer2Update = _FALSE;
StructWDTimerEventType g_pstWDTimerEvent[_WD_TIMER_EVENT_COUNT];
#endif

volatile WORD data g_usTimerCounter;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
volatile WORD data g_usMeasureCounter;
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
BYTE data g_ucTimerQuarterCount;
#endif

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))
EnumScalerTimerOperationMode g_enumTimerMode = _TIMER_OPERATION_INITIAL_MODE;
#endif

#if(_INSTANT_TIMER_EVENT_0 == _ON)
BYTE g_ucTimerCountHByte0;
BYTE g_ucTimerCountLByte0;
WORD g_usTimerPreviousCount0;
WORD g_usTimerBackupCount0;
WORD g_usTimerEventPeriod0;
WORD g_usTimerAxisCnt0;
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
BYTE g_ucTimerCountHByte1;
BYTE g_ucTimerCountLByte1;
WORD g_usTimerPreviousCount1;
WORD g_usTimerBackupCount1;
WORD g_usTimerEventPeriod1;
WORD g_usTimerAxisCnt1;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_RECORD_TIMER_SUPPORT == _ON)
void ScalerTimerResetRecordTimer_WDINT(void);
BYTE ScalerTimerGetRecordTimer_EXINT0(void);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerTimerWDInitial(void);
void ScalerTimerWDEventProc_WDINT(void);
void ScalerTimerWDActivateTimerEvent_EXINT0(WORD usTime, EnumScalerWDTimerEventID enumEventID);
void ScalerTimerWDActivateTimerEvent_WDINT(WORD usTime, EnumScalerWDTimerEventID enumEventID);
void ScalerTimerWDCancelTimerEvent(EnumScalerWDTimerEventID enumEventID);

#if((_DP_SUPPORT == _ON) || ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
void ScalerTimerWDCancelTimerEvent_EXINT0(EnumScalerWDTimerEventID enumEventID);
#endif
#endif

#if(_INSTANT_TIMER_EVENT_0 == _ON)
void ScalerTimer0SetTimerCount(WORD usTimerMs);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
void ScalerTimer1SetTimerCount(WORD usTimerMs);
#endif

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))
WORD ScalerTimerGetCommonDivisor(WORD usPar1, WORD usPar2);
#endif
void ScalerTimerSetTimerCount(EnumScalerTimerOperationMode enumOperationMode);

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
void ScalerTimerAddTimerCounter(void);
#endif

void ScalerTimerEventProc(EnumScalerTimerEventID enumEventID);
WORD ScalerTimerGetEventTime(BYTE ucEventIndex);
void ScalerTimerClrEventValid(BYTE ucEventIndex);
bit ScalerTimerCheckEventValid(BYTE ucEventIndex);
void ScalerTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
void ScalerTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID);
void ScalerTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID);
WORD ScalerTimerGetEventRemainTime(EnumScalerTimerEventID enumEventID);
bit ScalerTimerSearchActiveTimerEvent(EnumScalerTimerEventID enumEventID);

#if((_DP_SUPPORT == _ON) || (_TMDS_HDCP_2_2_SUPPORT == _ON) || ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
void ScalerTimerCancelTimerEvent_EXINT0(EnumScalerTimerEventID enumEventID);
#endif

#if((_DDCCI_CODE_REDUCTION == _OFF) && (_DEBUG_MESSAGE_SUPPORT == _OFF) && (_DDCCI_AUTO_SWITCH_SUPPORT == _ON))
void ScalerTimerCancelTimerEvent_EXINT1(EnumScalerTimerEventID enumEventID);
#endif
WORD ScalerTimerCheckTimerEvent(WORD usTime);
WORD ScalerTimerGetTimerCounter(void);
BYTE ScalerTimerGetEventID(BYTE ucEventIndex);
void ScalerTimerInitialTimerEvent(void);
void ScalerTimerDelayXms(WORD usNum);
bit ScalerTimerPollingFlagProc(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
#if((_HDCP_2_2_SUPPORT == _ON) || (_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON))
BYTE ScalerTimerPollingFlagProc_EXINT0(BYTE ucTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
WORD ScalerTimerTimer2Count_EXINT0(WORD usTimer);
#endif
#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
BYTE ScalerTimerPollingFlagProc_WDINT(BYTE ucTimeout, WORD usRegister, BYTE ucBit, bit bSuccess);
WORD ScalerTimerTimer2Count_WDINT(WORD usTimer);
#endif
void ScalerTimerWaitForActiveTimerEvent(EnumScalerTimerEventID enumEventID);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_RECORD_TIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Record Timer Start Time
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerResetRecordTimer_WDINT(void) using 3
{
    LOAD_TIMER_COUNTER(&g_usTimerRecordStartTime);
}


//--------------------------------------------------
// Description  : Get Recorded Time
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTimerGetRecordTimer_EXINT0(void) using 1
{
    WORD usRecordTime = 0;
    LOAD_TIMER_COUNTER(&usRecordTime);

    if(g_usTimerRecordStartTime == usRecordTime)
    {
        usRecordTime = 0x00;
    }
    else if(g_usTimerRecordStartTime < usRecordTime)
    {
        usRecordTime = usRecordTime - g_usTimerRecordStartTime;
    }
    else
    {
        usRecordTime = (0xFFFF - g_usTimerRecordStartTime) + 1 + usRecordTime;
    }

    return (BYTE)usRecordTime;
}
#endif


#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Watch Dog Timer Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDInitial(void)
{
    // Select WD Timer INT to EXINT2
    MCU_FFC4_IRQ_PRIORITY_3 = (MCU_FFC4_IRQ_PRIORITY_3 & ~(_BIT5 | _BIT4 | _BIT3)) | _BIT4;

    EX2 = 1;

    // Set WD Timer Threshold
    SET_TIMER_WD_THRESHOLD_COUNT(0xFFF);

    // Enable WD Timer Mode
    MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT4;

    // Clear Counter
    MCU_FFEA_WATCHDOG_TIMER |= _BIT6;

    // Clear WD Timer IRQ flag
    MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT7;

    // Enable WD Timer IRQ
    MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT2;
}

//--------------------------------------------------
// Description  : Watch Dog Timer Event Processor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDEventProc_WDINT(void) using 3
{
    BYTE ucIndex = 0;
    WORD usNextTime = 0xFFF;
    BYTE ucActiveWDID = _SCALER_WD_TIMER_EVENT_NULL;
    BYTE ucActiveWDTime = 0;
    BYTE ucWDTimeMSB = 0;
    BYTE ucWDTimeLSB = 0;
    WORD usWDLatchedTime = 0;

    if(((MCU_FFEB_WDT_TEST & (_BIT7 | _BIT2)) == (_BIT7 | _BIT2)) || (GET_GLOBAL_XTAL_CLK_SWITCH() != _GLOBAL_XTAL_CLK_SEL_UNCHANGE))
    {
        // Latch Current Count
        MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

        g_bWDTimer2Update = _FALSE;

        // Backup Register Value
        ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
        ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;

        // Timer 2 Interrupt and Change Latched Value
        if(g_bWDTimer2Update == _TRUE)
        {
            // Backup Register Value
            ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
            ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;
        }

        usWDLatchedTime = ((WORD)((ucWDTimeMSB & 0x7F) << 5) | (ucWDTimeLSB >> 3));

        // Clear Counter and Latch Current Count
        MCU_FFEA_WATCHDOG_TIMER |= _BIT6;

        // Clear Overflow Flag
        MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT7;

        for(ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
        {
            if(GET_WD_EVENT_VALID(ucIndex) == _TRUE)
            {
                if(GET_WD_EVENT_TIME(ucIndex) <= usWDLatchedTime)
                {
                    switch(GET_WD_EVENT_ID(ucIndex))
                    {
#if(_D0_DP_EXIST == _ON)
                        case _SCALER_WD_TIMER_EVENT_RX0_DP_LINK_TRAINING_REBUILD_PHY:

                            ScalerDpWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex));

                            break;
#endif // #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D1_DP_EXIST == _ON)
                        case _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_TRAINING_REBUILD_PHY:

                            ScalerDpWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex));

                            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_HDMI_2_0_SUPPORT == _ON)

                        case _SCALER_WD_TIMER_EVENT_RX0_HDMI_RR_RETRY:
                        case _SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY:
                        case _SCALER_WD_TIMER_EVENT_RX2_HDMI_RR_RETRY:
                        case _SCALER_WD_TIMER_EVENT_RX3_HDMI_RR_RETRY:
                        case _SCALER_WD_TIMER_EVENT_RX4_HDMI_RR_RETRY:
                        case _SCALER_WD_TIMER_EVENT_RX5_HDMI_RR_RETRY:

                            ScalerTMDSHdmiReadRequestTimerEnable_WDINT(_ENABLE);

                            break;
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
                        case _SCALER_WD_TIMER_EVENT_PD_RX0_SENDER_RESP_TIMEOUT:
                        case _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER:
                        case _SCALER_WD_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER:
                        case _SCALER_WD_TIMER_EVENT_PD_RX0_SEND_MSG:
                        case _SCALER_WD_TIMER_EVENT_PD_RX0_STATE_TO_READY:

                            ScalerTypeCRx0PdWDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex), &ucActiveWDID, &ucActiveWDTime);

                            break;
#endif
#if((_TYPE_C_PMIC_TYPE != _PMIC_NONE) && (_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_SCALER_SARADC) && (_TYPE_C_PMIC_FW_OCP_DELAY_SHUTDOWN != 0))
                        case _SCALER_WD_TIMER_EVENT_PMIC_RX0_FW_OCP_DELAY:

                            ScalerTypeCPmicRx0WDTimerEventProc_WDINT(GET_WD_EVENT_ID(ucIndex));

                            break;
#endif
#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_D0_DP_EXIST == _ON))
                        case _SCALER_WD_TIMER_EVENT_DP_RX0_HDCP2_SKE:

                            ScalerDpRx0Hdcp2SkeProc_WDINT();

                            break;
#endif
#if((_DP_HDCP_2_2_SUPPORT == _ON) && (_D1_DP_EXIST == _ON))
                        case _SCALER_WD_TIMER_EVENT_DP_RX1_HDCP2_SKE:

                            ScalerDpRx1Hdcp2SkeProc_WDINT();

                            break;
#endif


                        default:
                            break;
                    }

                    // Clear Event Valid After Event Processed
                    CLR_WD_EVENT_VALID(ucIndex);
                }
                else
                {
                    if(GET_GLOBAL_XTAL_CLK_SWITCH() == _GLOBAL_XTAL_CLK_SEL_UNCHANGE)
                    {
                        // Calculate Remain Event Time
                        SET_WD_EVENT_TIME(ucIndex, ((GET_WD_EVENT_TIME(ucIndex) > usWDLatchedTime) ? (GET_WD_EVENT_TIME(ucIndex) - usWDLatchedTime) : 0));
                    }
                    else if(GET_GLOBAL_XTAL_CLK_SWITCH() == _GLOBAL_XTAL_CLK_SEL_TO_INTERNAL)
                    {
                        // Calculate Remain Event Time; xtal -> iosc
                        SET_WD_EVENT_TIME(ucIndex, ((GET_WD_EVENT_TIME(ucIndex) > usWDLatchedTime) ? ((DWORD)(GET_WD_EVENT_TIME(ucIndex) - usWDLatchedTime) * _INTERNAL_OSC_XTAL / _EXT_XTAL) : 0));
                    }
                    else if(GET_GLOBAL_XTAL_CLK_SWITCH() == _GLOBAL_XTAL_CLK_SEL_TO_EXTERNAL)
                    {
                        // Calculate Remain Event Time; iosc -> xtal
                        SET_WD_EVENT_TIME(ucIndex, ((GET_WD_EVENT_TIME(ucIndex) > usWDLatchedTime) ? ((DWORD)(GET_WD_EVENT_TIME(ucIndex) - usWDLatchedTime) * _EXT_XTAL / _INTERNAL_OSC_XTAL) : 0));
                    }

                    // Set Next Execute Time
                    if(GET_WD_EVENT_TIME(ucIndex) < usNextTime)
                    {
                        usNextTime = GET_WD_EVENT_TIME(ucIndex);
                    }
                }
            }
        }

        if(usNextTime == 0)
        {
            // Threshold Set 0 will Induce HW IRQ can't happen
            SET_TIMER_WD_THRESHOLD_COUNT(1);
        }
        else
        {
            SET_TIMER_WD_THRESHOLD_COUNT(usNextTime);
        }

        SET_GLOBAL_XTAL_CLK_SWITCH(_GLOBAL_XTAL_CLK_SEL_UNCHANGE);
    }

    if((ucActiveWDTime != 0x00) && (ucActiveWDID != _SCALER_WD_TIMER_EVENT_NULL))
    {
        ScalerTimerWDActivateTimerEvent_WDINT(ucActiveWDTime, ucActiveWDID);
    }
}

//--------------------------------------------------
// Description  : Activate Watch Dog Timer (Only for EXINT0)
//                Acceptable Event Time should be between 10 ~ 500ms (for 14.318M) or 5 ~ 250ms (for 27M)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDActivateTimerEvent_EXINT0(WORD usTime, EnumScalerWDTimerEventID enumEventID) using 1
{
    BYTE ucIndex = 0;
    BYTE ucEventIndex = 0;
    BYTE ucWDTimeMSB = 0;
    BYTE ucWDTimeLSB = 0;
    WORD usWDLatchedTime = 0;
    WORD usWDThresholdTemp = 0;

    // Calculate Target WD Count
    usTime = ((DWORD)usTime * (_SYS_USE_ISO_CLK ? _INTERNAL_OSC_XTAL : _EXT_XTAL)) >> 11;

    for(ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
    {
        if(GET_WD_EVENT_VALID(ucIndex) == _FALSE)
        {
            // Latch Current Count
            MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

            g_bWDTimer2Update = _FALSE;

            // Backup Register Value
            ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
            ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;

            // Timer 2 Interrupt and Change Latched Value
            if(g_bWDTimer2Update == _TRUE)
            {
                // Backup Register Value
                ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;
            }

            usWDLatchedTime = ((WORD)((ucWDTimeMSB & 0x7F) << 5) | (ucWDTimeLSB >> 3));

            SET_WD_EVENT_ID(ucIndex, enumEventID);

            // If Target WD Count overflows
            if((usWDLatchedTime + usTime) >= 0xFFF)
            {
                if(GET_TIMER_WD_THRESHOLD_COUNT() > usWDLatchedTime)
                {
                    usWDThresholdTemp = GET_TIMER_WD_THRESHOLD_COUNT() - usWDLatchedTime;

                    SET_TIMER_WD_THRESHOLD_COUNT(usWDThresholdTemp);
                }
                else
                {
                    // Threshold Set 0 will Induce HW IRQ can't happen
                    SET_TIMER_WD_THRESHOLD_COUNT(1);
                }

                // Latch Current Count
                MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

                g_bWDTimer2Update = _FALSE;

                // Backup Register Value
                ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;

                // Timer 2 Interrupt and Change Latched Value
                if(g_bWDTimer2Update == _TRUE)
                {
                    // Backup Register Value
                    ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                    ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;
                }

                usWDLatchedTime = ((WORD)((ucWDTimeMSB & 0x7F) << 5) | (ucWDTimeLSB >> 3));

                // Clear WD Timer Count
                MCU_FFEA_WATCHDOG_TIMER |= _BIT6;

                SET_WD_EVENT_TIME(ucIndex, usTime);

                // Modify the Remain Time of Every Other Valid Event (Use Event ID as Temporariy Variable)
                for(ucEventIndex = 0; ucEventIndex < _WD_TIMER_EVENT_COUNT; ucEventIndex++)
                {
                    if((GET_WD_EVENT_VALID(ucEventIndex) == _FALSE) || (ucEventIndex == ucIndex))
                    {
                        continue;
                    }
                    else
                    {
                        SET_WD_EVENT_TIME(ucEventIndex, ((GET_WD_EVENT_TIME(ucEventIndex) > usWDLatchedTime) ? (GET_WD_EVENT_TIME(ucEventIndex) - usWDLatchedTime) : 0));
                    }
                }
            }
            else
            {
                // The Target Event should happen before previous event
                if((usWDLatchedTime + usTime) < GET_TIMER_WD_THRESHOLD_COUNT())
                {
                    if(usTime == 0)
                    {
                        // Threshold Set 0 will Induce HW IRQ can't happen
                        SET_TIMER_WD_THRESHOLD_COUNT(1);
                    }
                    else
                    {
                        // Change Target WD Threshold to Current Event
                        SET_TIMER_WD_THRESHOLD_COUNT(usTime);
                    }

                    // Latch Current Count
                    MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

                    g_bWDTimer2Update = _FALSE;

                    // Backup Register Value
                    ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                    ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;

                    // Timer 2 Interrupt and Change Latched Value
                    if(g_bWDTimer2Update == _TRUE)
                    {
                        // Backup Register Value
                        ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                        ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;
                    }

                    usWDLatchedTime = ((WORD)((ucWDTimeMSB & 0x7F) << 5) | (ucWDTimeLSB >> 3));

                    // Clear WD Timer Count
                    MCU_FFEA_WATCHDOG_TIMER |= _BIT6;

                    SET_WD_EVENT_TIME(ucIndex, usTime);

                    // Modify the Remain Time of Every Other Valid Event (Use Event ID as Temporariy Variable)
                    for(ucEventIndex = 0; ucEventIndex < _WD_TIMER_EVENT_COUNT; ucEventIndex++)
                    {
                        if((GET_WD_EVENT_VALID(ucEventIndex) == _FALSE) || (ucEventIndex == ucIndex))
                        {
                            continue;
                        }
                        else
                        {
                            SET_WD_EVENT_TIME(ucEventIndex, ((GET_WD_EVENT_TIME(ucEventIndex) > usWDLatchedTime) ? (GET_WD_EVENT_TIME(ucEventIndex) - usWDLatchedTime) : 0));
                        }
                    }
                }
                else
                {
                    SET_WD_EVENT_TIME(ucIndex, (usWDLatchedTime + usTime));
                }
            }
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Activate Watch Dog Timer (Only for WDINT0)
//                Acceptable Event Time should be between 10 ~ 500ms (for 14.318M) or 5 ~ 250ms (for 27M)
// Input Value  : usTime, enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDActivateTimerEvent_WDINT(WORD usTime, EnumScalerWDTimerEventID enumEventID) using 3
{
    BYTE ucIndex = 0;
    BYTE ucEventIndex = 0;
    BYTE ucWDTimeMSB = 0;
    BYTE ucWDTimeLSB = 0;
    WORD usWDLatchedTime = 0;
    WORD usWDThresholdTemp = 0;

    // Calculate Target WD Count
    usTime = ((DWORD)usTime * (_SYS_USE_ISO_CLK ? _INTERNAL_OSC_XTAL : _EXT_XTAL)) >> 11;

    for(ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
    {
        if(GET_WD_EVENT_VALID(ucIndex) == _FALSE)
        {
            // Latch Current Count
            MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

            g_bWDTimer2Update = _FALSE;

            // Backup Register Value
            ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
            ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;

            // Timer 2 Interrupt and Change Latched Value
            if(g_bWDTimer2Update == _TRUE)
            {
                // Backup Register Value
                ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;
            }

            usWDLatchedTime = ((WORD)((ucWDTimeMSB & 0x7F) << 5) | (ucWDTimeLSB >> 3));

            SET_WD_EVENT_ID(ucIndex, enumEventID);

            // If Target WD Count overflows
            if((usWDLatchedTime + usTime) >= 0xFFF)
            {
                if(GET_TIMER_WD_THRESHOLD_COUNT() > usWDLatchedTime)
                {
                    usWDThresholdTemp = GET_TIMER_WD_THRESHOLD_COUNT() - usWDLatchedTime;

                    SET_TIMER_WD_THRESHOLD_COUNT(usWDThresholdTemp);
                }
                else
                {
                    // Threshold Set 0 will Induce HW IRQ can't happen
                    SET_TIMER_WD_THRESHOLD_COUNT(1);
                }

                // Latch Current Count
                MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

                g_bWDTimer2Update = _FALSE;

                // Backup Register Value
                ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;

                // Timer 2 Interrupt and Change Latched Value
                if(g_bWDTimer2Update == _TRUE)
                {
                    // Backup Register Value
                    ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                    ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;
                }

                usWDLatchedTime = ((WORD)((ucWDTimeMSB & 0x7F) << 5) | (ucWDTimeLSB >> 3));

                // Clear WD Timer Count
                MCU_FFEA_WATCHDOG_TIMER |= _BIT6;

                SET_WD_EVENT_TIME(ucIndex, usTime);

                // Modify the Remain Time of Every Other Valid Event (Use Event ID as Temporariy Variable)
                for(ucEventIndex = 0; ucEventIndex < _WD_TIMER_EVENT_COUNT; ucEventIndex++)
                {
                    if((GET_WD_EVENT_VALID(ucEventIndex) == _FALSE) || (ucEventIndex == ucIndex))
                    {
                        continue;
                    }
                    else
                    {
                        SET_WD_EVENT_TIME(ucEventIndex, ((GET_WD_EVENT_TIME(ucEventIndex) > usWDLatchedTime) ? (GET_WD_EVENT_TIME(ucEventIndex) - usWDLatchedTime) : 0));
                    }
                }
            }
            else
            {
                // The Target Event should happen before previous event
                if((usWDLatchedTime + usTime) < GET_TIMER_WD_THRESHOLD_COUNT())
                {
                    if(usTime == 0)
                    {
                        // Threshold Set 0 will Induce HW IRQ can't happen
                        SET_TIMER_WD_THRESHOLD_COUNT(1);
                    }
                    else
                    {
                        // Change Target WD Threshold to Current Event
                        SET_TIMER_WD_THRESHOLD_COUNT(usTime);
                    }

                    // Latch Current Count
                    MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

                    g_bWDTimer2Update = _FALSE;

                    // Backup Register Value
                    ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                    ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;

                    // Timer 2 Interrupt and Change Latched Value
                    if(g_bWDTimer2Update == _TRUE)
                    {
                        // Backup Register Value
                        ucWDTimeMSB = MCU_FFAC_WATCHDOG_CNT3_VALUE;
                        ucWDTimeLSB = MCU_FFAB_WATCHDOG_CNT23_VALUE;
                    }

                    usWDLatchedTime = ((WORD)((ucWDTimeMSB & 0x7F) << 5) | (ucWDTimeLSB >> 3));

                    // Clear WD Timer Count
                    MCU_FFEA_WATCHDOG_TIMER |= _BIT6;

                    SET_WD_EVENT_TIME(ucIndex, usTime);

                    // Modify the Remain Time of Every Other Valid Event (Use Event ID as Temporariy Variable)
                    for(ucEventIndex = 0; ucEventIndex < _WD_TIMER_EVENT_COUNT; ucEventIndex++)
                    {
                        if((GET_WD_EVENT_VALID(ucEventIndex) == _FALSE) || (ucEventIndex == ucIndex))
                        {
                            continue;
                        }
                        else
                        {
                            SET_WD_EVENT_TIME(ucEventIndex, ((GET_WD_EVENT_TIME(ucEventIndex) > usWDLatchedTime) ? (GET_WD_EVENT_TIME(ucEventIndex) - usWDLatchedTime) : 0));
                        }
                    }
                }
                else
                {
                    SET_WD_EVENT_TIME(ucIndex, (usWDLatchedTime + usTime));
                }
            }
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Cancel WD Timer Event (Only for EXINT0)
// Input Value  : ucEventID => Event ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDCancelTimerEvent(EnumScalerWDTimerEventID enumEventID)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
    {
        if(GET_WD_EVENT_ID(ucIndex) == enumEventID)
        {
            CLR_WD_EVENT_VALID(ucIndex);
            break;
        }
    }
}

#if((_DP_SUPPORT == _ON) || ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : Cancel WD Timer Event in Interrupt (Only for EXINT0)
// Input Value  : ucEventID => Event ID
// Output Value : None
//--------------------------------------------------
void ScalerTimerWDCancelTimerEvent_EXINT0(EnumScalerWDTimerEventID enumEventID) using 1
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < _WD_TIMER_EVENT_COUNT; ucIndex++)
    {
        if(GET_WD_EVENT_ID(ucIndex) == enumEventID)
        {
            CLR_WD_EVENT_VALID(ucIndex);
            break;
        }
    }
}
#endif
#endif // End of #if(_WD_TIMER_INT_SUPPORT == _ON)

#if(_INSTANT_TIMER_EVENT_0 == _ON)
//--------------------------------------------------
// Description  : Timer0 Set Timer Counter
// Input Value  : ucTimerMs --> Counter in ms (1~65535ms)
//                Stops Timer0 if ucTimerMs = 0 or _TIMER_OFF
// Output Value : None
//--------------------------------------------------
void ScalerTimer0SetTimerCount(WORD usTimerMs)
{
    BYTE ucTemp = 0;

    if(usTimerMs == _TIMER_OFF)
    {
        // Stop Timer 0
        TR0 = _OFF;
    }
    else
    {
        if(usTimerMs <= _TIMER01_STEP_TIME_MS)
        {
            // Record the timer event period is going to happen
            g_usTimerEventPeriod0 = 1;

            // An intermediate variable
            PDATA_WORD(0) = usTimerMs * 1000;

            // Back up timer event period
            g_usTimerPreviousCount0 = PDATA_WORD(0);
        }
        else
        {
            // Get common divisor of integer number (_TIMER01_STEP_TIME_MS, usTimerMs)
            ucTemp = ScalerTimerGetCommonDivisor(_TIMER01_STEP_TIME_MS, usTimerMs);

            // Record the timer event period is going to happen
            g_usTimerEventPeriod0 = usTimerMs / ucTemp;

            // An intermediate variable
            PDATA_WORD(0) = ucTemp * 1000;

            // Back up timer event period
            g_usTimerPreviousCount0 = PDATA_WORD(0);
        }

        // Check if MCU Clk Source
        if((MCU_FFED_MCU_CONTROL & _BIT1) == _BIT1)
        {
            PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_M2PLL * PDATA_WORD(0)) / 1000));
        }
        else
        {
            if(GET_REG_XTAL_CLK_SEL() == _IOSC_CLK)
            {
                if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) == _FLASH_CLK_PS_FAST_DIV)
                {
                    PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC_FAST * PDATA_WORD(0)) / 1000));
                }
                else
                {
                    PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC * PDATA_WORD(0)) / 1000));
                }
            }
            else
            {
                PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_XTAL * PDATA_WORD(0)) / 1000));
            }
        }

        // Disable Timer 0
        ET0 = _DISABLE;

        // Stop Timer 0
        TR0 = _OFF;

        // Clear overflow flag
        TF0 = 0;

        g_ucTimerCountLByte0 = PDATA_WORD(0) & 0x00FF;
        g_ucTimerCountHByte0 = PDATA_WORD(0) >> 8;

        TL0 = g_ucTimerCountLByte0;
        TH0 = g_ucTimerCountHByte0;

        // Enable interrupt of Timer0
        ET0 = _ENABLE;

        // Reset Timer0 Axis Counter
        g_usTimerAxisCnt0 = 0;

        // Run Timer 0
        TR0 = _ON;
    }
}
#endif // End of #if(_INSTANT_TIMER_EVENT_0 == _ON)

#if(_INSTANT_TIMER_EVENT_1 == _ON)
//--------------------------------------------------
// Description  : Timer1 Set Timer Counter
// Input Value  : ucTimerMs --> Counter in ms (1~65535ms)
//                Stops Timer0 if ucTimerMs = 0 or _TIMER_OFF
// Output Value : None
//--------------------------------------------------
void ScalerTimer1SetTimerCount(WORD usTimerMs)
{
    BYTE ucTemp = 0;

    if(usTimerMs == _TIMER_OFF)
    {
        // Stop Timer 1
        TR1 = _OFF;
    }
    else
    {
        if(usTimerMs <= _TIMER01_STEP_TIME_MS)
        {
            // Record the timer event period is going to happen
            g_usTimerEventPeriod1 = 1;

            // An intermediate variable
            PDATA_WORD(0) = usTimerMs * 1000;

            // Back up timer event period
            g_usTimerPreviousCount1 = PDATA_WORD(0);
        }
        else
        {
            // Get common divisor of integer number (_TIMER01_STEP_TIME_MS, usTimerMs)
            ucTemp = ScalerTimerGetCommonDivisor(_TIMER01_STEP_TIME_MS, usTimerMs);

            // Record the timer event period is going to happen
            g_usTimerEventPeriod1 = usTimerMs / ucTemp;

            // An intermediate variable
            PDATA_WORD(0) = ucTemp * 1000;

            // Back up timer event period
            g_usTimerPreviousCount1 = PDATA_WORD(0);
        }

        // Check if MCU Clk Source
        if((MCU_FFED_MCU_CONTROL & _BIT1) == _BIT1)
        {
            PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_M2PLL * PDATA_WORD(0)) / 1000));
        }
        else
        {
            if(GET_REG_XTAL_CLK_SEL() == _IOSC_CLK)
            {
                if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) == _FLASH_CLK_PS_FAST_DIV)
                {
                    PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC_FAST * PDATA_WORD(0)) / 1000));
                }
                else
                {
                    PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC * PDATA_WORD(0)) / 1000));
                }
            }
            else
            {
                PDATA_WORD(0) = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_XTAL * PDATA_WORD(0)) / 1000));
            }
        }

        // Disable Timer 1
        ET1 = _DISABLE;

        // Stop Timer 1
        TR1 = _OFF;

        // Clear overflow flag
        TF1 = 0;

        g_ucTimerCountLByte1 = PDATA_WORD(0) & 0x00FF;
        g_ucTimerCountHByte1 = PDATA_WORD(0) >> 8;

        TL1 = g_ucTimerCountLByte1;
        TH1 = g_ucTimerCountHByte1;

        // Enable interrupt of Timer1
        ET1 = _ENABLE;

        // Reset Timer1 Axis Counter
        g_usTimerAxisCnt1 = 0;

        // Run Timer 1
        TR1 = _ON;
    }
}
#endif // End of #if(_INSTANT_TIMER_EVENT_1 == _ON)

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))

//--------------------------------------------------
// Description  : Seeking common divisor of two numbers
// Input Value  : usPar1 --> Paramater 2
//                usPar2 --> Paramater 2
// Output Value : None
//--------------------------------------------------
WORD ScalerTimerGetCommonDivisor(WORD usPar1, WORD usPar2)
{
    WORD usTemp = 0;

    while(usPar2 != 0)
    {
        usTemp = usPar2;
        usPar2 = usPar1 % usPar2;
        usPar1 = usTemp;
    }

    return usPar1;
}
#endif // End of #if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))

//--------------------------------------------------
// Description  : Set Time Count for Timer2
// Input Value  : OperationMode --> Initial/Normal/Saving
// Output Value : None
//--------------------------------------------------
void ScalerTimerSetTimerCount(EnumScalerTimerOperationMode enumOperationMode)
{
#if(_INSTANT_TIMER_EVENT_0 == _ON)
    bit bTR0Info = TR0;
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
    bit bTR1Info = TR1;
#endif

    BYTE pucTimercounter[5];

    memset(pucTimercounter, 0, sizeof(pucTimercounter));

    switch(enumOperationMode)
    {
        case _TIMER_OPERATION_INITIAL_MODE:

            pucTimercounter[0] = _TIMER2_COUNT_IN_LBYTE;
            pucTimercounter[1] = _TIMER2_COUNT_IN_HBYTE;
            pucTimercounter[2] = _TIMER2_COUNT_IN_LBYTE;
            pucTimercounter[3] = _TIMER2_COUNT_IN_HBYTE;

#if(_UART_SUPPORT == _ON)
            pucTimercounter[4] = _TIMER1_UART_COUNT_IN_BYTE;
#endif
            break;

        case _TIMER_OPERATION_POWER_NORMAL_MODE:
            pucTimercounter[0] = _TIMER2_COUNT_LBYTE;
            pucTimercounter[1] = _TIMER2_COUNT_HBYTE;
            pucTimercounter[2] = _TIMER2_COUNT_LBYTE;
            pucTimercounter[3] = _TIMER2_COUNT_HBYTE;

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))
            if(g_enumTimerMode != _TIMER_OPERATION_POWER_NORMAL_MODE)
            {
                g_enumTimerMode = _TIMER_OPERATION_POWER_NORMAL_MODE;

#if(_INSTANT_TIMER_EVENT_0 == _ON)
                if(bTR0Info == _ON)
                {
                    g_usTimerBackupCount0 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_M2PLL * g_usTimerPreviousCount0) / 1000));
                }
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
                if(bTR1Info == _ON)
                {
                    g_usTimerBackupCount1 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_M2PLL * g_usTimerPreviousCount1) / 1000));
                }
#endif
            }
#endif

#if(_UART_SUPPORT == _ON)
            pucTimercounter[4] = _TIMER1_UART_COUNT_BYTE;
#endif
            break;

        case _TIMER_OPERATION_POWER_SAVING_MODE:

            if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) == _FLASH_CLK_PS_FAST_DIV)
            {
                pucTimercounter[0] = _TIMER2_COUNT_PS_FAST_LBYTE;
                pucTimercounter[1] = _TIMER2_COUNT_PS_FAST_HBYTE;
                pucTimercounter[2] = _TIMER2_COUNT_PS_FAST_LBYTE;
                pucTimercounter[3] = _TIMER2_COUNT_PS_FAST_HBYTE;

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))
                if(g_enumTimerMode != _TIMER_OPERATION_POWER_SAVING_FAST_MODE)
                {
                    g_enumTimerMode = _TIMER_OPERATION_POWER_SAVING_FAST_MODE;

#if(_INSTANT_TIMER_EVENT_0 == _ON)
                    if(bTR0Info == _ON)
                    {
                        g_usTimerBackupCount0 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC_FAST * g_usTimerPreviousCount0) / 1000));
                    }
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
                    if(bTR1Info == _ON)
                    {
                        g_usTimerBackupCount1 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC_FAST * g_usTimerPreviousCount1) / 1000));
                    }
#endif
                }
#endif

#if(_UART_SUPPORT == _ON)
                pucTimercounter[4] = _TIMER1_UART_COUNT_PS_FAST_BYTE;
#endif
            }
            else
            {
                pucTimercounter[0] = _TIMER2_COUNT_PS_LBYTE;
                pucTimercounter[1] = _TIMER2_COUNT_PS_HBYTE;
                pucTimercounter[2] = _TIMER2_COUNT_PS_LBYTE;
                pucTimercounter[3] = _TIMER2_COUNT_PS_HBYTE;

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))
                if(g_enumTimerMode != _TIMER_OPERATION_POWER_SAVING_MODE)
                {
                    g_enumTimerMode = _TIMER_OPERATION_POWER_SAVING_MODE;
#if(_INSTANT_TIMER_EVENT_0 == _ON)
                    if(bTR0Info == _ON)
                    {
                        g_usTimerBackupCount0 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC * g_usTimerPreviousCount0) / 1000));
                    }
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
                    if(bTR1Info == _ON)
                    {
                        g_usTimerBackupCount1 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_IOSC * g_usTimerPreviousCount1) / 1000));
                    }
#endif
                }
#endif

#if(_UART_SUPPORT == _ON)
                pucTimercounter[4] = _TIMER1_UART_COUNT_PS_BYTE;
#endif
            }

            break;

        case _TIMER_OPERATION_POWER_IDLE_MODE:

            pucTimercounter[0] = _TIMER2_COUNT_IDLE_LBYTE;
            pucTimercounter[1] = _TIMER2_COUNT_IDLE_HBYTE;
            pucTimercounter[2] = _TIMER2_COUNT_PS_LBYTE;
            pucTimercounter[3] = _TIMER2_COUNT_PS_HBYTE;

            break;

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
        case _TIMER_OPERATION_OSD_MODE:
            pucTimercounter[0] = _TIMER2_COUNT_OSD_LBYTE;
            pucTimercounter[1] = _TIMER2_COUNT_OSD_HBYTE;
            pucTimercounter[2] = _TIMER2_COUNT_OSD_LBYTE;
            pucTimercounter[3] = _TIMER2_COUNT_OSD_HBYTE;

#if((_INSTANT_TIMER_EVENT_0 == _ON) || (_INSTANT_TIMER_EVENT_1 == _ON))
            if(g_enumTimerMode != _TIMER_OPERATION_OSD_MODE)
            {
                g_enumTimerMode = _TIMER_OPERATION_OSD_MODE;
#if(_INSTANT_TIMER_EVENT_0 == _ON)
                if(bTR0Info == _ON)
                {
                    g_usTimerBackupCount0 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_OSD * g_usTimerPreviousCount0) / 1000));
                }
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
                if(bTR1Info == _ON)
                {
                    g_usTimerBackupCount1 = 0xFFFF - ((WORD)((_TIMER01_TEMP_COUNT_OSD * g_usTimerPreviousCount1) / 1000));
                }
#endif
            }
#endif

#if(_UART_SUPPORT == _ON)
            pucTimercounter[4] = _TIMER1_UART_COUNT_OSD_BYTE;
#endif
            break;
#endif

        default:
            // Default case set to initial mode
            pucTimercounter[0] = _TIMER2_COUNT_IN_LBYTE;
            pucTimercounter[1] = _TIMER2_COUNT_IN_HBYTE;
            pucTimercounter[2] = _TIMER2_COUNT_IN_LBYTE;
            pucTimercounter[3] = _TIMER2_COUNT_IN_HBYTE;

            break;
    }

    // Disable Timer 2
    ET2 = _DISABLE;

    // Stop Timer 2
    TR2 = _OFF;

    // Clear overflow flag
    TF2 = 0;

    TL2 = pucTimercounter[0];
    TH2 = pucTimercounter[1];
    RCAP2L = pucTimercounter[2];
    RCAP2H = pucTimercounter[3];

    g_bNotifyTimer2Int = _FALSE;

    // Enable interrupt of Timer2
    ET2 = _ENABLE;

    // Run Timer2
    TR2 = _ON;

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    if((bTR0Info == _ON) && (enumOperationMode != _TIMER_OPERATION_INITIAL_MODE) && (enumOperationMode != _TIMER_OPERATION_POWER_IDLE_MODE))
    {
        // Do not load Timer Counter if Calculated Timer Counter is the same as Previous Timer Counter
        if(g_usTimerBackupCount0 != (((WORD)g_ucTimerCountHByte0 << 8) | g_ucTimerCountLByte0))
        {
            // Disable Timer 0
            ET0 = _DISABLE;

            // Stop Timer 0
            TR0 = _OFF;

            // Clear overflow flag
            TF0 = 0;

            // Load Timer Counter
            g_ucTimerCountLByte0 = g_usTimerBackupCount0 & 0x00FF;
            g_ucTimerCountHByte0 = g_usTimerBackupCount0 >> 8;
            TL0 = g_ucTimerCountLByte0;
            TH0 = g_ucTimerCountHByte0;

            // Enable interrupt of Timer0
            ET0 = _ENABLE;

            // Run Timer 0
            TR0 = _ON;
        }
    }
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
    if((bTR1Info == _ON) && (enumOperationMode != _TIMER_OPERATION_INITIAL_MODE) && (enumOperationMode != _TIMER_OPERATION_POWER_IDLE_MODE))
    {
        // Do not load Timer Counter if Calculated Timer Counter is the same as Previous Timer Counter
        if(g_usTimerBackupCount1 != (((WORD)g_ucTimerCountHByte1 << 8) | g_ucTimerCountLByte1))
        {
            // Disable Timer 1
            ET1 = _DISABLE;

            // Stop Timer 1
            TR1 = _OFF;

            // Clear overflow flag
            TF1 = 0;

            // Load Timer Counter
            g_ucTimerCountLByte1 = g_usTimerBackupCount1 & 0x00FF;
            g_ucTimerCountHByte1 = g_usTimerBackupCount1 >> 8;
            TL1 = g_ucTimerCountLByte1;
            TH1 = g_ucTimerCountHByte1;

            // Enable interrupt of Timer1
            ET1 = _ENABLE;

            // Run Timer 1
            TR1 = _ON;
        }
    }
#endif

#if(_UART_SUPPORT == _ON)
    // Stop Timer1
    TR1 = _OFF;

    // Clear overflow flag
    TF1 = 0;

    TL1 = pucTimercounter[4];
    TH1 = pucTimercounter[4];

    // Run Timer1
    TR1 = _ON;
#endif
}

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Add Timer Counter according to timer2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerAddTimerCounter(void)
{
    WORD usOffset = 0;

    if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) == _FLASH_CLK_PS_FAST_DIV)
    {
        if(g_bNotifyTimer2Int == _TRUE)
        {
            usOffset = _TIMER_COUNT_TEMP_PS_FAST1 - 1;
        }
        else
        {
            usOffset = (((WORD)(_TIMER2_COUNT_IDLE_HBYTE << 8) & 0xFF00) | (_TIMER2_COUNT_IDLE_LBYTE));
            usOffset = (((WORD)(TH2 << 8) & 0xFF00) | (TL2)) - usOffset;
            usOffset = usOffset / _TIMER_COUNT_TEMP_PS_FAST2;
        }
    }
    else
    {
        if(g_bNotifyTimer2Int == _TRUE)
        {
            usOffset = _IDLE_TIME - 1;
        }
        else
        {
            usOffset = (((WORD)(_TIMER2_COUNT_IDLE_HBYTE << 8) & 0xFF00) | (_TIMER2_COUNT_IDLE_LBYTE));
            usOffset = (((WORD)(TH2 << 8) & 0xFF00) | (TL2)) - usOffset;
            usOffset = usOffset / _TIMER_COUNT_TEMP_PS;
        }
    }

    usOffset += ScalerTimerGetTimerCounter();
    STORE_TIMER_COUNTER(usOffset);
}
#endif // End of #if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)

//--------------------------------------------------
// Description  : Scaler Timer Event Process
// Input Value  : enumEventID --> Event to be processed
// Output Value : None
//--------------------------------------------------
void ScalerTimerEventProc(EnumScalerTimerEventID enumEventID)
{
#if(_DP_MST_SUPPORT == _ON)
    BYTE ucDebounceCnt = 0;
#endif

    switch(enumEventID)
    {
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_DVI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX0_TMDS_VIDEO_DETECT:
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX1_TMDS_VIDEO_DETECT:
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_TMDS_VIDEO_DETECT:
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_TMDS_VIDEO_DETECT:
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_TMDS_VIDEO_DETECT:
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX5_TMDS_VIDEO_DETECT:
#endif
        ScalerTMDSVideoDetectEvent(enumEventID);

        break;

#if(_HDMI_SUPPORT == _ON)

#if(_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX0_HDMI2_FORMAT_RESET_WAIT:

#if(_D1_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX1_HDMI2_FORMAT_RESET_WAIT:
#endif

#if(_D2_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_HDMI2_FORMAT_RESET_WAIT:
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI2_FORMAT_RESET_WAIT:
#endif

#if(_D4_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT:
#endif

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX5_HDMI2_FORMAT_RESET_WAIT:
#endif
            ScalerTMDSHdmi2FormatResetEvent(enumEventID);

            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX0_TMDS_HDMI_PACKET_DETECT:
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX1_TMDS_HDMI_PACKET_DETECT:
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_TMDS_HDMI_PACKET_DETECT:
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_TMDS_HDMI_PACKET_DETECT:
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX4_TMDS_HDMI_PACKET_DETECT:
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX5_TMDS_HDMI_PACKET_DETECT:
#endif
        ScalerTMDSHdmiPacketDetectEvent(enumEventID);

        break;

#if(_D0_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX0_HDMI_HPD_ASSERTED:
            PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX1_HDMI_HPD_ASSERTED:
            PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX2_HDMI_HPD_ASSERTED:
            PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_RX3_HDMI_HPD_ASSERTED:
            PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
            break;
#endif

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_LOW_DUTY:

            ScalerTMDSClkLaneZ0HighProc();
            break;

        case _SCALER_TIMER_EVENT_TMDS_Z0_POWER_SAVING_TOGGLE_HIGH_DUTY:

            ScalerTMDSClkLaneZ0LowProc();
            break;
#endif

#endif // End of #if(_HDMI_SUPPORT == _ON)

#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_PORT_EXIST == _ON))

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX0_HDCP2_REAUTH:
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX1_HDCP2_REAUTH:
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH:
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH:
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX4_HDCP2_REAUTH:
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX5_HDCP2_REAUTH:
#endif
        ScalerHdcp2ReAuthEvent(enumEventID);

        break;
#endif // End of #if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if(_AUDIO_SUPPORT == _ON)
#if((_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
        case _SCALER_TIMER_EVENT_AUDIO_D0_LOAD_STABLE_I_CODE:
#endif

#if((_D1_HDMI_SUPPORT == _ON) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
        case _SCALER_TIMER_EVENT_AUDIO_D1_LOAD_STABLE_I_CODE:
#endif

#if((_D2_HDMI_SUPPORT == _ON) || (_D2_INPUT_PORT_TYPE == _D2_DP_PORT))
        case _SCALER_TIMER_EVENT_AUDIO_D2_LOAD_STABLE_I_CODE:
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_AUDIO_D3_LOAD_STABLE_I_CODE:
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_AUDIO_D4_LOAD_STABLE_I_CODE:
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_AUDIO_D5_LOAD_STABLE_I_CODE:
#endif

        ScalerAudioLoadStableICodeEvent(enumEventID);

        break;
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_DP_SUPPORT == _ON)

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D6_INPUT_PORT_TYPE != _D6_NO_PORT))

        case _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED:
        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT:
        case _SCALER_TIMER_EVENT_DP_RX0_LONG_HOTPLUG_EVENT:
        case _SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ:

            ScalerDpTimerEventProc(enumEventID);
            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED:
        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT:
        case _SCALER_TIMER_EVENT_DP_RX1_LONG_HOTPLUG_EVENT:
        case _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ:

            ScalerDpTimerEventProc(enumEventID);
            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

        case _SCALER_TIMER_EVENT_DP_RX2_HOTPLUG_ASSERTED:
        case _SCALER_TIMER_EVENT_DP_RX2_HDCP_LONG_HOTPLUG_EVENT:
        case _SCALER_TIMER_EVENT_DP_RX2_LONG_HOTPLUG_EVENT:
        case _SCALER_TIMER_EVENT_DP_RX2_LINK_STATUS_IRQ:

            ScalerDpTimerEventProc(enumEventID);
            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)

#if(_D0_DP_EXIST == _ON)

        case _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK:

            SET_DP_RX0_VALID_VIDEO_CHECK();

            break;

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_RSV0_PACKET_DETECT:

            ScalerDpRx0RSV0PacketDetectEvent();
            break;
#endif

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))

        case _SCALER_TIMER_EVENT_DP_RX0_RSV1_PACKET_DETECT:

            ScalerDpRx0RSV1PacketDetectEvent();
            break;
#endif

#if(_DP_MST_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE:

            CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();

            if(ScalerDpRx0AuxChSourcePowerCheck() == _OFF)
            {
                // Debounce for 20ms
                for(ucDebounceCnt = 0; ucDebounceCnt < 10; ucDebounceCnt++)
                {
                    ScalerTimerDelayXms(2);

                    if(ScalerDpRx0AuxChSourcePowerCheck() == _ON)
                    {
                        break;
                    }
                }

                if(ucDebounceCnt == 10)
                {
                    SET_DP_RX0_CHECK_AUX_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_OFF);

                    // Do Mst Reset If Source Has Disconnected.
                    // (Reading 00111h = 0x00 is necessary for AMD RX480 waking up. If not so, the OS might not recognize all the audio device.)
                    ScalerDpMstReset(_DP_MST_RX0_PORT);
                }
            }

            break;

        case _SCALER_TIMER_EVENT_DP_RX0_SOURCE_WRITE_POWER_UP_TIMEOUT:

            if(GET_DP_RX0_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE)
            {
                CLR_DP_RX0_SOURCE_WRITE_POWER_UP();
            }

            break;

#if(_DP_TX_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_CPIRQ_EVENT:
            CLR_DP_RX0_HDCP_AUTH_CPIRQ_TIMRE();
            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_REPEATER_PROC_TIMEOUT:

            ScalerDpRx0HDCPSetRepeaterProcTimeout();
            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP_READ_IRQ_TIMEOUT:

            ScalerDpRx0HDCPSetReadIrqTimeout();
            break;

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))

        case _SCALER_TIMER_EVENT_DP_RX0_MST2SST_RSV1_PACKET_DETECT:

            ScalerDpRx0MstToSstRSV1PacketDetectEvent();
            break;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX0_HDCP2_CPIRQ_EVENT:
            CLR_DP_RX0_HDCP2_AUTH_CPIRQ_TIMRE();
            break;

        case _SCALER_TIMER_EVENT_DP_RX0_HDCP2_REPEATER_PROC_TIMEOUT:

            ScalerDpRx0Hdcp2SetRepeaterProcTimeout();
            break;

#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
#endif // End if #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#endif // End of #if(_D0_DP_EXIST == _ON)

#if(_D1_DP_EXIST == _ON)

        case _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK:

            SET_DP_RX1_VALID_VIDEO_CHECK();

            break;

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT:

            ScalerDpRx1RSV0PacketDetectEvent();
            break;
#endif

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))

        case _SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT:

            ScalerDpRx1RSV1PacketDetectEvent();
            break;
#endif

#if(_DP_MST_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE:

            CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();

            if(ScalerDpRx1AuxChSourcePowerCheck() == _OFF)
            {
                // Debounce for 20ms
                for(ucDebounceCnt = 0; ucDebounceCnt < 10; ucDebounceCnt++)
                {
                    ScalerTimerDelayXms(2);

                    if(ScalerDpRx1AuxChSourcePowerCheck() == _ON)
                    {
                        break;
                    }
                }

                if(ucDebounceCnt == 10)
                {
                    SET_DP_RX1_CHECK_AUX_CH_POWER_STATUS(_DP_RX_AUX_POWER_STATUS_OFF);

                    // Do Mst Reset If Source Has Disconnected.
                    // (Reading 00111h = 0x00 is necessary for AMD RX480 waking up. If not so, the OS might not recognize all the audio device.)
                    ScalerDpMstReset(_DP_MST_RX1_PORT);
                }
            }

            break;

        case _SCALER_TIMER_EVENT_DP_RX1_SOURCE_WRITE_POWER_UP_TIMEOUT:

            if(GET_DP_RX1_SOURCE_WRITE_POWER_UP() == _DP_SOURCE_WRITE_POWER_UP_TIMER_ACTIVE)
            {
                CLR_DP_RX1_SOURCE_WRITE_POWER_UP();
            }

            break;

#if(_DP_TX_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT:
            CLR_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE();
            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT:

            ScalerDpRx1HDCPSetRepeaterProcTimeout();
            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT:

            ScalerDpRx1HDCPSetReadIrqTimeout();
            break;

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))

        case _SCALER_TIMER_EVENT_DP_RX1_MST2SST_RSV1_PACKET_DETECT:

            ScalerDpRx1MstToSstRSV1PacketDetectEvent();
            break;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_RX1_HDCP2_CPIRQ_EVENT:
            CLR_DP_RX1_HDCP2_AUTH_CPIRQ_TIMRE();
            break;

        case _SCALER_TIMER_EVENT_DP_RX1_HDCP2_REPEATER_PROC_TIMEOUT:

            ScalerDpRx1Hdcp2SetRepeaterProcTimeout();
            break;

#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
#endif // End if #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#endif // End of #if(_D1_DP_EXIST == _ON)

#if(_DP_MST_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_MSG_TIMEOUT_EVENT:
            ScalerDpRxMstMsgTimeoutEvent();
            break;
#endif // End of #if(_DP_MST_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT:

            if(GET_DP_RX_REPORT_DOWNSTREAM_UNPLUG_EVENT() == _TRUE)
            {
                // Regen Unplug event
                SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(_DP_UNPLUG);
            }
            else
            {
                // Align Reported Cable Status with Tx Cable Status
                SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS());
            }

            // Initiate Connection Status Notify
            SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_CONNECTION_STATUS_NOTIFY);

            break;

        case _SCALER_TIMER_EVENT_DP_TX_FORCE_REBUILD_TOPOLOGY_EVENT:

            SET_DP_TX_WAIT_TOPOLOGY_REBUILD_MSG();

            if(GET_REG_DP_RX_MST_ENABLE() == _TRUE)
            {
                switch(g_enumDpMSTCapablePort)
                {
#if(_D0_DP_EXIST == _ON)
                    case _DP_MST_RX0_PORT:

                        ScalerDpRx0SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);

                        break;
#endif

#if(_D1_DP_EXIST == _ON)
                    case _DP_MST_RX1_PORT:

                        ScalerDpRx1SetHotPlugEvent(_DP_MST_LONG_HPD_EVENT);

                        break;
#endif

                    default:
                        break;
                }
            }

            break;

        case _SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT:

            ScalerDpRxMstMsgCountResetEvent();
            ScalerDpTxMstMsgCountResetEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT:

            ScalerDpTxMstMsgCountResetEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0:

            ScalerDpTxHDCPTimeoutToReadR0Event();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY:

            ScalerDpTxHDCPTimeoutForVReadyEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY:

            ScalerDpTxHDCPPollingVReadyEvent();
            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_CERTIFICATE:

            ScalerDpTxHdcp2TimeoutToReadCertificateEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_H_PRIME:

            ScalerDpTxHdcp2TimeoutToReadHPrimeEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_PAIRING_INFO:

            ScalerDpTxHdcp2TimeoutToReadPairingInfoEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_ENCRYPT_DATA:

            ScalerDpTxHdcp2TimeoutToEncyptDataEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_FOR_V_READY:

            ScalerDpTxHdcp2TimeoutForVReadyEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_POLLING_V_READY:

            ScalerDpTxHdcp2PollingVReadyEvent();
            break;

        case _SCALER_TIMER_EVENT_DP_TX_HDCP2_WAITING_TO_READ_M_PRIME:

            ScalerDpTxHdcp2TimeoutToReadMPrimeEvent();
            break;
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)
#endif // End if #if(_DP_TX_SUPPORT == _ON)

#if(_HDMI_TX_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP_WAITING_TO_READ_R0:

            ScalerHdmiTxHDCPTimeoutToReadR0Event();
            break;

        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP_WAITING_FOR_V_READY:

            ScalerHdmiTxHDCPTimeoutForVReadyEvent();
            break;

        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP_POLLING_V_READY:

            ScalerHdmiTxHDCPPollingVReadyEvent();
            break;

#if(_HDMI_TX_HDCP_2_2_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP2_WAITING_TO_READ_CERTIFICATE:

            ScalerHdmiTxHdcp2TimeoutToReadCertificateEvent();
            break;

        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP2_WAITING_TO_READ_H_PRIME:

            ScalerHdmiTxHdcp2TimeoutToReadHPrimeEvent();
            break;

        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP2_WAITING_TO_ENCRYPT_DATA:

            ScalerHdmiTxHdcp2TimeoutToEncyptDataEvent();
            break;

        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP2_WAITING_FOR_V_READY:

            ScalerHdmiTxHdcp2TimeoutForVReadyEvent();
            break;

        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP2_POLLING_V_READY:

            ScalerHdmiTxHdcp2PollingVReadyEvent();
            break;

        case _SCALER_TIMER_EVENT_HDMI_TX_HDCP2_WAITING_TO_READ_M_PRIME:

            ScalerHdmiTxHdcp2TimeoutToReadMPrimeEvent();
            break;
#endif
#endif // End of #if(_HDMI_TX_SUPPORT == _ON)

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_SDRAM_PHASE_CALIBRATION == _ON)

        case _SCALER_TIMER_EVENT_SDRAM_PHASE_CNT_CHECK:

            // Check phase count every 60 minute
            ScalerSdramOnLinePhaseCntCheck();
            break;
#endif

#if(_DDR1_PHASE_CALIBRATION == _ON)
        case _SCALER_TIMER_EVENT_DDR_PHASE_CNT_CHECK:

            // Check phase count every 60 minute
            ScalerDDR1OnLinePhaseCntCheck();
            break;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX0_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLTimerEventProc(enumEventID);

            break;

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLTimerEventProc(enumEventID);

            break;

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX2_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX2_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLTimerEventProc(enumEventID);

            break;

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX3_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLTimerEventProc(enumEventID);

            break;

#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX4_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX4_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLTimerEventProc(enumEventID);

            break;

#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        case _SCALER_TIMER_EVENT_MHL_RX5_READY_TO_TRANSMIT:
        case _SCALER_TIMER_EVENT_MHL_RX5_RECONNECT_1K:
        case _SCALER_TIMER_EVENT_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE:

            ScalerMHLTimerEventProc(enumEventID);

            break;

#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

        case _SCALER_TIMER_EVENT_PD_RX0_CBL_RESP_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_RX0_STATE_TO_READY:
        case _SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_ON_POWER:
        case _SCALER_TIMER_EVENT_PD_RX0_SRC_TURN_OFF_POWER:
        case _SCALER_TIMER_EVENT_PD_RX0_SEND_HARD_RST:
        case _SCALER_TIMER_EVENT_PD_RX0_TPC_ERR_RECOVER:
        case _SCALER_TIMER_EVENT_PD_RX0_CLR_SRC_CAP_WAIT:
        case _SCALER_TIMER_EVENT_PD_RX0_CLR_REQ_WAIT:
        case _SCALER_TIMER_EVENT_PD_RX0_CLR_PRS_WAIT:
        case _SCALER_TIMER_EVENT_PD_RX0_CLR_DRS_WAIT:
        case _SCALER_TIMER_EVENT_PD_RX0_CLR_VCS_WAIT:
        case _SCALER_TIMER_EVENT_PD_RX0_SET_SRC_INIT_AMS:
        case _SCALER_TIMER_EVENT_PD_RX0_PPS_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_RX0_S8_HRST:
        case _SCALER_TIMER_EVENT_PD_RX0_DFP_START_ALT_MODE:
        case _SCALER_TIMER_EVENT_PD_RX0_LENOVO_RESP_TIMEOUT:
        case _SCALER_TIMER_EVENT_PD_RX0_CLR_ATTENTION_WAIT:

            ScalerTypeCRx0PdTimerEventProc(enumEventID);

            break;

        case _SCALER_TIMER_EVENT_CC_RX0_STATE_TO_UNATTACH:
        case _SCALER_TIMER_EVENT_CC_RX0_CLEAR_AC_ON_DEVICE_DETECT:
            ScalerTypeCRx0CcTimerEventProc(enumEventID);

            break;

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
        case _SCALER_TIMER_EVENT_PMIC_TRACKING:

            ScalerTypeCPmicRx0Tracking();

            break;

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
        case _SCALER_TIMER_EVENT_PMIC_POLLING_OCP:

            ScalerTypeCPmicRx0OcpProtect();

            break;
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)


#endif // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)
#endif // End of #if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Event Time
// Input Value  : ucEventIndex --> Event which time is needed
// Output Value : Event Time
//--------------------------------------------------
WORD ScalerTimerGetEventTime(BYTE ucEventIndex)
{
    return GET_EVENT_TIME(ucEventIndex);
}

//--------------------------------------------------
// Description  : Clear Event Time
// Input Value  : ucEventIndex --> Event which time is needed to be cleared
// Output Value : None
//--------------------------------------------------
void ScalerTimerClrEventValid(BYTE ucEventIndex)
{
    CLR_EVENT_VALID(ucEventIndex);
}

//--------------------------------------------------
// Description  : Check if Event is Valid
// Input Value  : ucEventIndex --> Event to be checked
// Output Value : Validity(_TRUE/_FALSE)
//--------------------------------------------------
bit ScalerTimerCheckEventValid(BYTE ucEventIndex)
{
    return (GET_EVENT_VALID(ucEventIndex) == _TRUE);
}

//--------------------------------------------------
// Description  : Active Timer Event
// Input Value  : usTime --> Time to active Timer Event (unit is ms)
//                ucEventID --> Event to be actived
// Output Value : None
//--------------------------------------------------
void ScalerTimerActiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_EVENT_ID(ucEventIndex) == enumEventID)
            {
                return;
            }
        }
    }

    // Choose any Vacant Storage for Event
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _FALSE)
        {
            SET_EVENT_ID(ucEventIndex, enumEventID);
            SET_EVENT_TIME(ucEventIndex, (WORD)((DWORD)(ScalerTimerCheckTimerEvent(usTime)) + usTime));
            return;
        }
    }

    DebugMessageSystem("No More Available Storage for Simultaneous Event!!!!!!", 0x00);
}

//--------------------------------------------------
// Description  : Reactive a timer for an event. If the event is exist,
//                this function will reset the executing time and restart.
// Input Value  : usTime    --> Unit in 1ms, range in 0.01 ~ 61 sec
//                Event     --> Execute Event while timeup
// Output Value : None
//--------------------------------------------------
void ScalerTimerReactiveTimerEvent(WORD usTime, EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_EVENT_ID(ucEventIndex) == enumEventID)
            {
                SET_EVENT_TIME(ucEventIndex, (WORD)((DWORD)(ScalerTimerCheckTimerEvent(usTime)) + usTime));

                return;
            }
        }
    }

    // Choose any Vacant Storage for Event
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _FALSE)
        {
            SET_EVENT_ID(ucEventIndex, enumEventID);
            SET_EVENT_TIME(ucEventIndex, (WORD)((DWORD)(ScalerTimerCheckTimerEvent(usTime)) + usTime));
            return;
        }
    }
}

//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void ScalerTimerCancelTimerEvent(EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search for Existing Event with the same Event ID
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
        {
            if(GET_EVENT_ID(ucEventIndex) == enumEventID)
            {
                CLR_EVENT_VALID(ucEventIndex);

                return;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Get Event Remain Time
// Input Value  : ucEventID --> Event which has been activated
// Output Value : Event ID Time
//--------------------------------------------------
WORD ScalerTimerGetEventRemainTime(EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;
    WORD usTime = 0;

    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(ScalerTimerGetEventID(ucEventIndex) == enumEventID)
        {
            if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
            {
                if(ScalerTimerGetEventTime(ucEventIndex) > ScalerTimerGetTimerCounter())
                {
                    usTime = (ScalerTimerGetEventTime(ucEventIndex) - ScalerTimerGetTimerCounter());
                }

                break;
            }
        }
    }

    return usTime;
}

//--------------------------------------------------
// Description  : Search a timer event
// Input Value  : ucEventID --> Event which has been activated
// Output Value : None
//--------------------------------------------------
bit ScalerTimerSearchActiveTimerEvent(EnumScalerTimerEventID enumEventID)
{
    BYTE ucEventIndex = 0;

    // Search Correponding EventID and wait until it finished
    for(ucEventIndex = 0; ucEventIndex < _TIMER_EVENT_COUNT; ucEventIndex++)
    {
        if(GET_EVENT_ID(ucEventIndex) == enumEventID)
        {
            if(GET_EVENT_VALID(ucEventIndex) == _TRUE)
            {
                return _TRUE;
            }
        }
    }

    return _FALSE;
}

#if((_DP_SUPPORT == _ON) || ((_TMDS_HDCP_2_2_SUPPORT == _ON) && (_HDMI_PORT_EXIST == _ON)) || ((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)))
//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void ScalerTimerCancelTimerEvent_EXINT0(EnumScalerTimerEventID enumEventID) using 1
{
    // Search for Existing Event with the same Event ID
    for(pData_EXINT[0] = 0; pData_EXINT[0] < _TIMER_EVENT_COUNT; pData_EXINT[0]++)
    {
        if(GET_EVENT_VALID(pData_EXINT[0]) == _TRUE)
        {
            if(GET_EVENT_ID(pData_EXINT[0]) == enumEventID)
            {
                CLR_EVENT_VALID(pData_EXINT[0]);
                return;
            }
        }
    }
}
#endif

#if((_DDCCI_CODE_REDUCTION == _OFF) && (_DEBUG_MESSAGE_SUPPORT == _OFF) && (_DDCCI_AUTO_SWITCH_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Cancel a Timer Event in Int1
// Input Value  : enumEventID --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void ScalerTimerCancelTimerEvent_EXINT1(EnumScalerTimerEventID enumEventID) using 2
{
    // Search for Existing Event with the same Event ID
    for(pData_EXINT[0] = 0; pData_EXINT[0] < _TIMER_EVENT_COUNT; pData_EXINT[0]++)
    {
        if(GET_EVENT_VALID(pData_EXINT[0]) == _TRUE)
        {
            if(GET_EVENT_ID(pData_EXINT[0]) == enumEventID)
            {
                CLR_EVENT_VALID(pData_EXINT[0]);
                return;
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Check timer and events. We have to run this function when setting up a timer for an event.
// Input Value  : usTime    --> Unit in 1ms, range in 0.001 ~ 61sec
// Output Value : Return usPresentTime
//--------------------------------------------------
WORD ScalerTimerCheckTimerEvent(WORD usTime)
{
    BYTE ucTimerEventCnt = 0;
    WORD usPresentTime = 0;

    usPresentTime = ScalerTimerGetTimerCounter();

    if(usTime > _EVENT_TIME_MAX)
    {
        usTime = _EVENT_TIME_MAX;
    }

    if(((usPresentTime + usTime) > _EVENT_TIME_MAX) || // Size Limit of Timer Counter
       ((usPresentTime + usTime) < usPresentTime)) // Timer Counter Overflow
    {
        STORE_TIMER_COUNTER(0);

        // Reset Timer Event Counter
        for(ucTimerEventCnt = 0; ucTimerEventCnt < _TIMER_EVENT_COUNT; ucTimerEventCnt++)
        {
            if(GET_EVENT_VALID(ucTimerEventCnt) == _TRUE)
            {
                if(GET_EVENT_TIME(ucTimerEventCnt) > usPresentTime)
                {
                    SET_EVENT_TIME(ucTimerEventCnt, (GET_EVENT_TIME(ucTimerEventCnt) - usPresentTime));
                }
                else
                {
                    SET_EVENT_TIME(ucTimerEventCnt, 0);
                }
            }
        }

        usPresentTime = 0;
    }

    return usPresentTime;
}


//--------------------------------------------------
// Description  : Get Timer Counter.
// Input Value  : None
// Output Value : Timer Counter
//--------------------------------------------------
WORD ScalerTimerGetTimerCounter(void)
{
    WORD usPresentTime = g_usTimerCounter;

    // When get counter,timer interrupt maybe change counter.
    // Get twice to avoid it.
    if(abs(g_usTimerCounter - usPresentTime) > 0x7F)
    {
        usPresentTime = g_usTimerCounter;
    }

    return usPresentTime;
}

//--------------------------------------------------
// Description  : Get Event ID
// Input Value  : Referenced Event Index
// Output Value : Stored Event ID
//--------------------------------------------------
BYTE ScalerTimerGetEventID(BYTE ucEventIndex)
{
    return GET_EVENT_ID(ucEventIndex);
}

//--------------------------------------------------
// Description  : Initial timer and events. We have to run this function at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTimerInitialTimerEvent(void)
{
    BYTE ucTimerEventCnt = 0;

    for(ucTimerEventCnt = 0; ucTimerEventCnt < _TIMER_EVENT_COUNT; ucTimerEventCnt++)
    {
        CLR_EVENT_VALID(ucTimerEventCnt);
    }

    TR2 = 1;
}

//--------------------------------------------------
// Description  : Timer Delay
// Input Value  : usNum --> Delay in ms
// Output Value : None
//--------------------------------------------------
void ScalerTimerDelayXms(WORD usNum)
{
    if(usNum != 0)
    {
        // Avoid dead lock under timer2 interrupt function disable condition
        if(TR2 == _OFF)
        {
            return;
        }

        g_bNotifyTimer2Int = _FALSE;

        while(_TRUE)
        {
            if(g_bNotifyTimer2Int == _TRUE)
            {
                g_bNotifyTimer2Int = _FALSE;

                if(--usNum)
                {
                }
                else
                {
                    return;
                }
            }
        }
    }
}

//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process
// Input Value  : usTimeout --> Timeout number (Max: 65,535 ms)
//                usRegister--> Current Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
bit ScalerTimerPollingFlagProc(WORD usTimeout, WORD usRegister, BYTE ucBit, bit bSuccess)
{
    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;

    usPreviousTime = g_usTimerCounter;

    do
    {
        if(((bit)ScalerGetBit(usRegister, ucBit) ^ bSuccess) == _FALSE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(usTimeElapsed <= usTimeout);

    return _FALSE;
}

#if((_HDCP_2_2_SUPPORT == _ON) || (_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON))
//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process in INT
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                usRegister--> Current Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
BYTE ScalerTimerPollingFlagProc_EXINT0(BYTE ucTimeout, WORD usRegister, BYTE ucBit, bit bSuccess) using 1
{
    WORD usTimeElapsed = 0;

    // if EXINT0 Proirity > Timer2
    if(PX0 == 1)
    {
        TF2 = 0;

        do
        {
            usTimeElapsed = ScalerTimerTimer2Count_EXINT0(usTimeElapsed);

            if(((bit)ScalerGetBit_EXINT(usRegister, ucBit) ^ bSuccess) == _FALSE)
            {
                return _TRUE;
            }
        }
        while(usTimeElapsed <= ucTimeout);
    }
    else
    {
        WORD usPreviousTime = g_usTimerCounter;

        do
        {
            if(((bit)ScalerGetBit_EXINT(usRegister, ucBit) ^ bSuccess) == _FALSE)
            {
                return _TRUE;
            }

            if(usPreviousTime != g_usTimerCounter)
            {
                usTimeElapsed++;
                usPreviousTime = g_usTimerCounter;
            }
        }
        while(usTimeElapsed <= ucTimeout);
    }

    return _FALSE;
}

//----------------------------------------------------------------------
// Description  : FW Detect 1ms flag for timer2 counter
// Input Value  :
// Output Value :
//----------------------------------------------------------------------
WORD ScalerTimerTimer2Count_EXINT0(WORD usTimer) using 1
{
    if(TF2 == 1)
    {
        // Clear Timer2 flag
        TF2 = 0;

#if(_WD_TIMER_INT_SUPPORT == _OFF)
        // Clear watchdog
        CLR_MCU_WATCH_DOG();
#else
        // Latch Current Counter and not clear any WD timer counter
        MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

        g_bWDTimer2Update = _TRUE;

        // Add to Prevent INT Lock Reset
        if((MCU_FFAD_WATCHDOG_CNT1_VALUE & 0x07) > 0x04)
        {
            // Clear watchdog
            CLR_MCU_WATCH_DOG();
        }
#endif
        g_bNotifyTimer2Int = _TRUE;

        usTimer += 1;
    }

    return usTimer;
}
#endif

#if(_TYPE_C_PMIC_HW_IIC_SUPPORT == _ON)
//----------------------------------------------------------------------
// Description  : Polling Scaler Flag Process in WDINT0
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                usRegister--> Current Register
//                ucBit     --> Polling Bit
//                bSuccess  --> 1 or 0 when finished for Polling Bit
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------
BYTE ScalerTimerPollingFlagProc_WDINT(BYTE ucTimeout, WORD usRegister, BYTE ucBit, bit bSuccess) using 3
{
    WORD usTimeElapsed = 0;

    // if WDINT Proirity > Timer2
    if(PX2 == 1)
    {
        TF2 = 0;

        do
        {
            usTimeElapsed = ScalerTimerTimer2Count_WDINT(usTimeElapsed);

            if(((bit)ScalerGetBit_EXINT(usRegister, ucBit) ^ bSuccess) == _FALSE)
            {
                return _TRUE;
            }
        }
        while(usTimeElapsed <= ucTimeout);
    }
    else
    {
        WORD usPreviousTime = g_usTimerCounter;

        do
        {
            if(((bit)ScalerGetBit_EXINT(usRegister, ucBit) ^ bSuccess) == _FALSE)
            {
                return _TRUE;
            }

            if(usPreviousTime != g_usTimerCounter)
            {
                usTimeElapsed++;
                usPreviousTime = g_usTimerCounter;
            }
        }
        while(usTimeElapsed <= ucTimeout);
    }

    return _FALSE;
}

//----------------------------------------------------------------------
// Description  : FW Detect 1ms flag for timer2 counter
// Input Value  :
// Output Value :
//----------------------------------------------------------------------
WORD ScalerTimerTimer2Count_WDINT(WORD usTimer) using 3
{
    if(TF2 == 1)
    {
        // Clear Timer2 flag
        TF2 = 0;

#if(_WD_TIMER_INT_SUPPORT == _OFF)
        // Clear watchdog
        CLR_MCU_WATCH_DOG();
#else
        // Latch Current Counter and not clear any WD timer counter
        MCU_FFEB_WDT_TEST = (MCU_FFEB_WDT_TEST & (~_BIT7)) | _BIT3;

        g_bWDTimer2Update = _TRUE;

        // Add to Prevent INT Lock Reset
        if((MCU_FFAD_WATCHDOG_CNT1_VALUE & 0x07) > 0x04)
        {
            // Clear watchdog
            CLR_MCU_WATCH_DOG();
        }
#endif
        g_bNotifyTimer2Int = _TRUE;

        usTimer += 1;
    }

    return usTimer;
}
#endif

//--------------------------------------------------
// Description  : Check if Event is Valid
// Input Value  : ucEventID --> Event which has been activated
// Output Value : None
//--------------------------------------------------
void ScalerTimerWaitForActiveTimerEvent(EnumScalerTimerEventID enumEventID)
{
    ScalerTimerDelayXms(ScalerTimerGetEventRemainTime(enumEventID));
    ScalerTimerCancelTimerEvent(enumEventID);
}

