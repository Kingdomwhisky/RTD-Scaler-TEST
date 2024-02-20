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
// ID Code      : SysInt.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SYSTEM_INT__

#include "SysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
// Backup for Burst Write Bug
BYTE g_ucBackup_EXINT0;
BYTE g_ucBackup_EXINT1;
BYTE g_ucBackup_SERIAL;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysEXINT0(void);
void SysEXINT1(void);
#if(_USB3_RETIMER_SUPPORT == _ON)
void SysEXINT3(void);
#endif
void SysUartSerialPortIntProc(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Interrupt 0 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysEXINT0(void)    interrupt 0 using 1
{
    // Backup for Burst Write Bug
    g_ucBackup_EXINT0 = MCU_FFF4_SCA_INF_ADDR;

#if(_DP_SUPPORT == _ON)
    if(ScalerDpAuxJudgeHandler_EXINT0() == _TRUE)
    {
        // Reload Backup for Burst Write Bug
        MCU_FFF4_SCA_INF_ADDR = g_ucBackup_EXINT0;

        return;
    }
#endif

#if(_DP_SUPPORT == _ON)
    ScalerDpIntHandler_EXINT0();
#endif

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
    ScalerGlobalPreventGarbageByBacklight_EXINT0();
#endif

#if(_MHL_SUPPORT == _ON)
    ScalerMHLIntHandler_EXINT0();
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
    ScalerHdcp2IntHandler_EXINT0();
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
    ScalerTypeCIntHandler_EXINT0();
#endif

#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_HDMI_CEC_SUPPORT == _ON)
    ScalerCecIntHandler_EXINT0();
#endif

    if((GET_POWER_STATUS() != _POWER_STATUS_SAVING) && (GET_POWER_STATUS() != _POWER_STATUS_OFF))
    {
        ScalerTMDSIntHandler_EXINT0();
    }
    else
    {
        ScalerTMDSPSIntHandler_EXINT0();
    }

#endif

#if((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
    ScalerMbrIntHandler_EXINT0();
#endif

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
    ScalerODIntHandler_EXINT0();
#endif

#if(_PANEL_STYLE == _PANEL_VBO)
    ScalerDisplayVboIntHandler_EXINT0();
#endif

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpTxIntHandle_EXINT0();
#endif

#if(_EMBEDDED_DP_TX_SUPPORT == _ON)
    ScalerEmbeddedDpTxIntHandle_EXINT0();
#endif

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    ScalerIRHWModeIntHandler_EXINT0();
#endif

#if(_LC_TANK_SUPPORT == _ON)
#if(_XTALESS_SUPPORT == _ON)
    ScalerLCTankDpllRegulation_EXINT0();
#endif
#endif

#if(_DP_SUPPORT == _ON)
    ScalerDpExitIntSetting_EXINT0();
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_EXINT0;
}

//--------------------------------------------------
// Description  : Interrupt 1 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysEXINT1(void)    interrupt 2 using 2
{
    // Backup for Burst Write Bug
    g_ucBackup_EXINT1 = MCU_FFF4_SCA_INF_ADDR;

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    ScalerSyncDdcDetect_EXINT1();
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    ScalerDebugIntProc_EXINT1();
#else

#if(_DDCCI_CODE_REDUCTION == _OFF)
    if((bit)UserCommonInterfaceGetDdcciStatus_EXINT1() == _TRUE)
    {
        UserCommonInterfaceDdcciIntGetData_EXINT1();
    }
    else
#endif
    {
        ScalerDebugIntProc_EXINT1();
    }
#endif

#if(_AUTO_TEST_SUPPORT == _ON)
    SysAutotestIntProc_EXINT1();
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_EXINT1;
}

#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Interrupt 3 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysEXINT3(void)    interrupt 9
{
    ScalerUSB3RetimerIntHandler_EXINT3();

    EXIF &= ~_BIT5;

    MCU_FFC2_IRQ_PRIORITY_1 = ((MCU_FFC2_IRQ_PRIORITY_1 & ~(_BIT7 | _BIT6)) | 0x00);
    MCU_FFC2_IRQ_PRIORITY_1 = ((MCU_FFC2_IRQ_PRIORITY_1 & ~(_BIT7 | _BIT6)) | _BIT7);
}
#endif

//--------------------------------------------------
// Description  : Serial Port0 Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysUartSerialPortIntProc(void)    interrupt 4
{
    // Backup for Burst Write Bug
    g_ucBackup_SERIAL = MCU_FFF4_SCA_INF_ADDR;

#if(_UART_SUPPORT == _ON)
    if(GET_UART_TRANSMIT_STATUS() == _TRUE)
    {
        CLR_UART_TRANSMIT_STATUS();
    }

    UserInterfaceUartIntHandler_SERIALPORT();
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_SERIAL;
}

