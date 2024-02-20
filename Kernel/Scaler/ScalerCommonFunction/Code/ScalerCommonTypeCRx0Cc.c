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
// ID Code      : ScalerCommonTypeCRx0Cc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _CC_FW_DEBUG                                            _OFF
#define _TYPE_C_CC_CONNECT_MODE                                 _TYPE_C_HW_MODE

#if(_TYPE_C_EMB_CTS_FLOW == _ON)
#define _TYPE_C_CC_DRP_SWITCH_MODE                              _FALSE
#else
#define _TYPE_C_CC_DRP_SWITCH_MODE                              _TRUE
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
StructTypeCInfo g_stTpcInfo;
WORD g_usSlop;
BYTE g_ucoffset;
bit g_bsign;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTypeCRx0CcClkSel(BYTE ucClockSel);
void ScalerTypeCRx0CcInitial(void);
void ScalerTypeCRx0CcHandler(BYTE ucModeState);
void ScalerTypeCRx0CcIntHandler_EXINT0(void);
BYTE ScalerTypeCRx0CcIntClrCheck_EXINT0(void);
void ScalerTypeCRx0CcTimerEventProc(EnumScalerTimerEventID enumEventID);
void ScalerTypeCRx0CcSetDeglitch(BYTE ucChannel, BYTE ucTime, EnumDeglitchUnit enumUnit);
void ScalerTypeCRx0CcSetDebounce(bit bDbType, BYTE ucTime);
void ScalerTypeCRx0CcLoadTrimming(void);
void ScalerTypeCRx0CcUnattachReset(BYTE ucModeState);
void ScalerTypeCRx0CcConnectionSet(void);
bit ScalerTypeCRx0CcAttachedSetting(void);
bit ScalerTypeCRx0CcUnattachCheck(void);
void ScalerTypeCRx0CcVconnControl(bit bAction);
void ScalerTypeCRx0CcVconnControl_EXINT0(bit bAction);
void ScalerTypeCRx0CcVconnControl_WDINT(bit bAction);
void ScalerTypeCRx0CcSetBMC(bit bAction);
void ScalerTypeCRx0CcVbusDetCtrl(bit bAction);
void ScalerTypeCRx0CcVbusDetCtrl_EXINT0(bit bAction);
void ScalerTypeCRx0CcVbusDetCtrl_WDINT(bit bAction);
BYTE ScalerTypeCRx0CcDetResistor(void);
void ScalerTypeCRx0CcACOnDeviceDetect(void);
bit ScalerTypeCRx0CcGetACOnDeviceDetect(void);
void ScalerTypeCRx0CcSwitchPowerRole(BYTE ucTargetRole);
void ScalerTypeCRx0CcSwitchPowerRole_EXINT0(BYTE ucTargetRole);
void ScalerTypeCRx0CcPowerSwitch(EnumPowerAction enumPowerAction);

#if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)
void ScalerTypeCRx0CcFWModeSRCUnattached_EXINT0(void);
#endif  // End of #if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)

#if(_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON)
void ScalerTypeCRx0CcFastRoleSwapControl(bit bAction);
#endif

#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED)

//--------------------------------------------------
// Description  : Type C Rx0 CC Clk Setting (Always Use IOSC = 28MHz)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcClkSel(BYTE ucClockSel)
{
    if(ucClockSel == _IOSC_CLK)
    {
        // [0x6600] [5:4] Clk Sel = IOSC (b'10) / [0x6601] [3:0] sys_clk_div = b'0001
        ScalerSetBit(P66_00_GLOBAL_CTL, ~(_BIT5 | _BIT4), _BIT5);
        ScalerSetBit(P66_01_SYS_CLK_SRC_CFG, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

        // [0x6602] clk_1m_div = 28 (b'0001_1100)
        ScalerSetByte(P66_02_1M_CLK_SRC_CFG, 0x1C);

        // [0x6603-04] clk_1k_div = 1000 (b'11_11101000)
        ScalerSetBit(P66_03_1K_CLK_SRC_CFG_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetByte(P66_04_1K_CLK_SRC_CFG_1, 0xE8);
    }
}

//--------------------------------------------------
// Description  : Type C CC Logic AC_ON Initail
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcInitial(void)
{
    SET_TYPE_C_GLOBAL_IRQ_ENABLE(_ENABLE);
    // ------------------- Type C Initial Setting -------------------

    // global_cc_en = _ENABLE
    ScalerSetBit(P66_00_GLOBAL_CTL, ~_BIT7, _BIT7);

    // Setting Up CC1/2 De-glitch
    ScalerTypeCRx0CcSetDeglitch(_TYPE_C_CC1, 3, _TYPE_C_UNIT_100US);
    ScalerTypeCRx0CcSetDeglitch(_TYPE_C_CC2, 3, _TYPE_C_UNIT_100US);

    // Set tCCDebounce (150 ms) & tPDDebounce (20 ms), Not Set VS-Debounce
    ScalerTypeCRx0CcSetDebounce(_TYPE_C_CC, 110);
    ScalerTypeCRx0CcSetDebounce(_TYPE_C_PD, 10);

    // Load Trimming Value From E-fuse and Set up AIF Registers
    ScalerTypeCRx0CcLoadTrimming();

    // Initial Flags & Status Setting
    CLR_CC_RX0_ATTACHED();
    SET_RX0_SRC_FRSWAP_STATUS(_DISABLE);
    SET_RX0_SNK_FRSWAP_STATUS(_DISABLE);
    SET_RX0_VCONN_STATUS(_OFF);
#if((_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_DRP) && (_TYPE_C_CC_DRP_SWITCH_MODE == _TRUE))
    SET_TYPE_C_RX0_DRP_CONNECT_MODE();
#endif
    // ------------------- OCP Initial Setting -------------------

    // OCP Mode = HW Auto Mode
    ScalerSetBit(P66_0D_TPC_OCP_CTRL, ~_BIT6, 0x00);

    // ocp_deg_cc1/2 = _ENABLE, ocp_vref_sel_cc1/2 = b'100 (470mA)
    ScalerSetByte(P66_0E_TPC_OPC_CFG_0, 0xE4);

    // Escape Vltage = 4.5V, reg_opcadj_cc1 = 0
    ScalerSetBit(P66_0F_TPC_OPC_CFG_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));

    // OCP HW Auto Mode Timing Setting
    ScalerSetByte(P66_73_VCONN_OCP_TIMER1, 0xBC);
    ScalerSetByte(P66_74_VCONN_OCP_TIMER2, 0xFC);
    ScalerSetByte(P66_75_VCONN_OCP_TIMER3, 0x41);
    ScalerSetByte(P66_76_VCONN_OCP_TIMER4, 0xBC);
    ScalerSetByte(P66_77_VCONN_OCP_TIMER5, 0xFC);

    // ----------------- HW Mode Initial Setting -----------------

#if(_TYPE_C_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // HW Mode Type-C Version Setting [7] (0:_TYPE_C_1_1 / 1:_TYPE_C_1_2)
#if(_HW_TYPE_C_SUPPORT_VERSION == _TYPE_C_VERSION_1_1)
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT7, 0x00);
#else
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT7, _BIT7);
#endif

    // DRP Port Toggle Timing Setting (SRC/SNK/TrySRC/TrySNKWait)
    // [0x6638] drp_hw_src_time = 30 ms (1E)
    ScalerSetByte(P66_38_CC_HW_DRP_SRC_TM, 0x1E);

    // [0x6639] drp_hw_snk_time = 64 ms
    ScalerSetByte(P66_39_CC_HW_DRP_SNK_TM, 0x40);

    // [0x663A] [4:3] Try.SRC = 75ms / [2:0] Try.Wait = 400ms
    ScalerSetBit(P66_3A_CC_HW_TRY_SRC_TM, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // ---------- HW Mode Accessory Support Setting ----------

    // [2]   hw_debug_sup_en
#if((_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_POWER) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_AUDIO) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_ALL))
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT2, _BIT2);
#else
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT2, 0x00);
#endif

    // [1]   hw_audio_sup_en
#if((_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_AUDIO) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_AUDIO_POWER) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_AUDIO) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_ALL))
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT1, _BIT1);
#else
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT1, 0x00);
#endif

    // [0]   hw_pwr_sup_en
#if((_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_POWER) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_AUDIO_POWER) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_DEBUG_POWER) || (_TYPE_C_ACC_SUPPORT_TYPE == _TYPE_C_ACC_ALL))
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT0, _BIT0);
#else
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~_BIT0, 0x00);
#endif

    // ---------- HW Mode FSM & BMC De-Glitch Setting ----------

    // [0x663D] Enable Setup Hold / Debounce Time
    ScalerSetBit(P66_3D_HW_DGH_EN, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // [0x663E] Deglitch HW State Transition = 5ms
    ScalerSetByte(P66_3E_HW_DGH_TH, 0xCA);

    // [0x663F] Hold Time For HW Sync = 1 ms
    ScalerSetByte(P66_3F_STABLE_TIMER_TH, 0x8A);

#endif  // End of #if(_TYPE_C_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // ----------------- Fast Role Swap Setting -----------------

#if(_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON)
    // Fast Role Swap CC Pin Select Mode = HW Mode
    ScalerSetBit(P66_60_FRS_CTRL, ~_BIT4, 0x00);

    // CC Pin Voltage < 490mV Signal Deglitch
    ScalerSetByte(P66_61_FRS_490MV_DGH, 0x41);

    // Vbus Voltage Drop Below Threshold Voltage Deglitch
    ScalerSetByte(P66_62_FRS_VBUS_DGH, 0x01);

    // Timing For SRC to Drive Low When Sending FR_SWAP Signal (90us)
    ScalerSetBit(P66_63_SRC_FRS_DRV_TM, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x09);

    // Timing For SNK to Recognize Drive Low Signal from SRC (CC Pin Vol. < 490mV for more than 50us)
    ScalerSetByte(P66_64_SNK_FRS_DET_TM, 0x20);

    // Configre For SNK to Start Supply Vbus
    ScalerSetByte(P66_65_SNK_FRS_VTH_MODE, _BIT6);

#endif  // End of #if(_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : CC Logic Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcHandler(BYTE ucModeState)
{
    ucModeState = ucModeState;

    switch(GET_TYPE_C_RX0_ATTACH_STATUS())
    {
        case _EMB_TPC_INITAIL:

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("O Type C State : INITIAL", GET_TYPE_C_RX0_ATTACH_STATUS());
#endif
            ScalerTypeCRx0CcInitial();
            ScalerTypeCRx0PdInitial();
            ScalerTypeCPowerInitial();

            if((GET_TYPE_C_RX0_AC_ON_RECONNECT() == _TRUE) && (ScalerTypeCPowerCheckLocPowExist(_ON) == _TRUE))
            {
                ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, 0x00);
                ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, 0x00);
                ScalerSetByte(P66_30_CC_HW_MODE_CTRL, 0x00);

                ScalerTimerActiveTimerEvent(1000, _SCALER_TIMER_EVENT_CC_RX0_STATE_TO_UNATTACH);
            }
            else
            {
                ScalerTimerActiveTimerEvent(1, _SCALER_TIMER_EVENT_CC_RX0_STATE_TO_UNATTACH);
            }

            break;

        case _EMB_TPC_UNATTACH:

            // 1. Reset to Unattached State (From Attached Back to Unattach : PD => Power => CC)
            ScalerTypeCRx0PdReset();
            // FW Solution : Samsung S8 Clear Flag When CC Unattach (Not Cleared When PD Reset)
            ScalerTypeCRx0PdClrInteropS8Flag();
            ScalerTypeCPowerRx0UnattachReset();
            ScalerTypeCRx0CcUnattachReset(ucModeState);

            if(GET_CC_RX0_CONNECT_EN() == _TRUE)
            {
                // 2. Setting For Connection
                ScalerTypeCRx0CcConnectionSet();

                // 3. Enable HW Connection
                ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~_BIT5, _BIT5);

                // 4. State Transition
                SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_CONNECTING);
            }
            break;

        case _EMB_TPC_CONNECTING:

            // FW Waiting for Attached When Connecting in HW_MODE
            // Can Use Debug Message to Monitor the Connecting Status
            //========================================================================
            // When "hw_done_irq" is Triggered, SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_CONNECTTED) @ SysInt
            // hw_done_irq     = 1;            [0x6630]
            // hw_done_irq_en  = _DISABLE;     [0x6630]
            // hw_unattach_irq = 1;            [0x6630]
            // hw_unattach_irq_en = _ENABLE;   [0x6630]
            //========================================================================

            break;

        case _EMB_TPC_CONNECTTED:

            // 1. Detect CC Role, Orientation and Resistor on CC Pin
            // 2. If SRC, Check Vbus = vSafe0V before turnning on Vbus
            if(ScalerTypeCRx0CcAttachedSetting() == _TRUE)
            {
                if(ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC)
                {
                    if(ScalerTypeCPowerRx0CheckVbusSafe0V() == _FALSE)
                    {
                        return;
                    }

                    // For Type-C DRP (No Try.SRC/SNK) CTS Flow
                    // ScalerTimerDelayXms(150);

                    if(GET_CC_RX0_RA_EXIST() == _TRUE)
                    {   // If SRC and Ra Exist, Turn On Vconn
                        ScalerTypeCRx0CcVconnControl(_ON);
                    }

                    // If SRC, Turn On Vbus to vSafe5V (500 * 10mV) / Current = Default Current (10mA)
                    if(ScalerTypeCPowerCheckVbusCapability(_PD_FIX_SUPPLY_PDO, 500, GET_CC_RX0_DEF_CUR()))
                    {
                        ScalerTypeCPowerRx0VbusControl(_ON, _PD_POWER_SRC, _PD_FIX_SUPPLY_PDO, 500, GET_CC_RX0_DEF_OCP_CUR());
                    }
                }
                else
                {   // Adjust Unattch Vth to 3.67V
                    ScalerTypeCPowerRx0UnattachVthAdjust();
                }

                // Set PD to Initail State (Data Role, Vconn Role, Initial State (PE_SRC/SNK_STARTUP),...)
                ScalerTypeCRx0PdAttachedSetting();

                // BMC Related Setting
                ScalerTypeCRx0CcSetBMC(_ENABLE);

                // Turn On U3 & Hub Function
                ScalerDpRx0SetDpAltModeLaneMapping(_TYPE_C_PIN_ASSIGNMENT_NONE, GET_CC_RX0_ORIENTATION());

                SET_CC_RX0_ATTACHED();

                if(GET_TYPE_C_RX0_ATTACH_STATUS() == _EMB_TPC_CONNECTTED)
                {
                    SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_ATTACHED);
#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
                    DebugMessageTypeC("O Type C State : ATTACH SUCCESS!!!", GET_TYPE_C_RX0_ATTACH_STATUS());
                    DebugMessageTypeC("  ! ! ! CC ATTACHED ! ! !", GET_CC_RX0_ATTACHED());
#endif
                }
            }
            else
            {   // If Connect to Unexpected Attached State, Transit to UNATTACH State
                SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH);
            }

            break;

        case _EMB_TPC_ATTACHED:

            //========================================================================
            // When "hw_unattach_irq" is Triggered,
            // Clear and Disable Unattach_irq, SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH) @ SysInt
            // Otherwise, Run PD Controller and Process Corresponding PD Events
            //========================================================================

#if((_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_PD) || (_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_FULL_FUNCTION))
            // 1. Always Run PD if DC Off Option = _TYPE_C_DC_OFF_POWER_BANK_PD ||  _TYPE_C_DC_OFF_FULL_FUNCTION
            ScalerTypeCRx0PdHandler();

#else
            // 1. Run PD Only when DC On if DC Off Option = _TYPE_C_DC_OFF_POWER_BANK_CC
            if(ucModeState != _MODE_STATUS_POWER_OFF)
            {
                ScalerTypeCRx0PdHandler();
            }
#endif
            // 2. Check Whether CC FW Unattach Event is Triggered
            if(ScalerTypeCRx0CcUnattachCheck() == _TRUE)
            {
                SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH);
            }

#if(_TYPE_C_PMIC_CHECK_SUPPORT == _ON)
            ScalerTypeCPmicRx0Check();
#endif

            break;

        default:

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("[WARNING] CC Enter Unexpected State", GET_TYPE_C_RX0_ATTACH_STATUS());
#endif
            // Error : Back to _EMB_TPC_UNATTACH State
            SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH);

            break;
    }
}

//--------------------------------------------------
// Description  : Interrupt Process For Type C
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcIntHandler_EXINT0(void) using 1
{
    if(ScalerGetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, (_BIT5 | _BIT1)) == (_BIT5 | _BIT1))
    {   // (cc1_vconn_shutdown_irq == 1) && (cc1_vconn_shutdown_irq_en = _ENABLE)

        // Turn Off Vconn (Should We Turn On Vconn Again Later?)
        ScalerTypeCRx0CcVconnControl_EXINT0(_OFF);
        ScalerSetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
    }

    if(ScalerGetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, (_BIT5 | _BIT1)) == (_BIT5 | _BIT1))
    {   // (cc2_vconn_shutdown_irq == 1) && (cc2_vconn_shutdown_irq_en == _ENABLE)

        // Turn Off Vconn (Should We Turn On Vconn Again Later?)
        ScalerTypeCRx0CcVconnControl_EXINT0(_OFF);
        ScalerSetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
    }

    if(ScalerGetBit_EXINT(P66_30_CC_HW_MODE_CTRL, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        // (hw_done_irq == 1) && (hw_done_irq_en == Enable)
        // [0x6630] Disable hw_done_irq and Enable hw_unattach_irq
        // [3] hw_done_irq     = 1
        // [2] hw_done_irq_en  = _DISABLE
        // [1] hw_unattach_irq = 1
        // [0] hw_unattach_irq_en = _ENABLE
        ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

#if((_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_DRP) && (_TYPE_C_CC_DRP_SWITCH_MODE == _TRUE))
        // Claer Switch Mode Timer Event if Successfully Attached
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_CC_RX0_STATE_TO_UNATTACH);
#endif

        SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_CONNECTTED);
    }

    if(ScalerGetBit_EXINT(P66_30_CC_HW_MODE_CTRL, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {   // (hw_unattach_irq == 1) && (hw_unattach_irq_en == Enable)

        // [0x6630] Clear and Disable hw_unattach_irq, and Transit to UNATTACH State
        // [3] hw_done_irq     = 1
        // [1] hw_unattach_irq = 1
        // [0] hw_unattach_irq_en = _DISABLE
        ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~(_BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

        // Turn Off Vconn Power
        ScalerTypeCRx0CcVconnControl_EXINT0(_OFF);
        ScalerTypeCPowerRx0VbusControl_EXINT0(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        ScalerTypeCPmicRx0VbusDischarge_EXINT0(_ENABLE);
#endif

#if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)
        ScalerTypeCRx0CcFWModeSRCUnattached_EXINT0();
#endif  // End of #if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)

        // Cancel AC_ON_CABLE_DETECT Timer Event & Clear AC_ON_DEVICE_DETECT flag when HW Unattach Event Triggered to update & maintain AC_ON_DEVICE_DETECT flag _False
        ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_CC_RX0_CLEAR_AC_ON_DEVICE_DETECT);
        SET_TYPE_C_RX0_AC_ON_DEVICE_DETECT(_FALSE);

        SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH);
    }

    if((ScalerGetBit_EXINT(P66_2C_CC_R_CHG_INT, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) || (ScalerGetBit_EXINT(P66_2C_CC_R_CHG_INT, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4)))
    {
        ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT5, 0x00);
        ScalerSetBit_EXINT(P65_03_PD_TOP_RST, ~_BIT5, _BIT5);
        ScalerSetBit_EXINT(P66_2C_CC_R_CHG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));
    }
}

//--------------------------------------------------
// Description  : Check If All CC Enabled IRQ is Clear Or Not
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
BYTE ScalerTypeCRx0CcIntClrCheck_EXINT0(void) using 1
{
    // Return False, if Any of IRQs is Enabled and Has Not Been Processed
    if((ScalerGetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, (_BIT5 | _BIT1)) == (_BIT5 | _BIT1)) ||
       (ScalerGetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, (_BIT5 | _BIT1)) == (_BIT5 | _BIT1)) ||
       (ScalerGetBit_EXINT(P66_30_CC_HW_MODE_CTRL, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2)) ||
       (ScalerGetBit_EXINT(P66_30_CC_HW_MODE_CTRL, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0)) ||
       (ScalerGetBit_EXINT(P66_2C_CC_R_CHG_INT, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4)))
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Timer Event Proc of CC RX0
// Input Value  : enumEventID
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_CC_RX0_STATE_TO_UNATTACH:

            SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH);

            break;

        case _SCALER_TIMER_EVENT_CC_RX0_CLEAR_AC_ON_DEVICE_DETECT:

            SET_TYPE_C_RX0_AC_ON_DEVICE_DETECT(_FALSE);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : CC De-Glitch          [0x6605 / 0x6606]
// Input Value  : bChannel  : _TYPE_C_CC1(0) / _TYPE_C_CC2(1)
//                ucTime    : 0-63
//                enumUnit  : _TYPE_C_UNIT_1US / _TYPE_C_UNIT_10US / _TYPE_C_UNIT_100US / _TYPE_C_UNIT_1MS
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcSetDeglitch(BYTE ucChannel, BYTE ucTime, EnumDeglitchUnit enumUnit)
{
    // [0x6605] Setting CC1 De-glitch Time Value
    // [0x6606] Setting CC2 De-glitch Time Value
    if(ucTime < 64)
    {
        // [5:0] tpc_cc1_dgh_lv / tpc_cc2_dgh_lv = ucTime
        ScalerSetByte(P66_05_CC1_DGH_LV + ucChannel, ucTime);

        switch(enumUnit)
        {   // Setting De-glitch Level For Valid Input

            case _TYPE_C_UNIT_1US:
                // [7:6] tpc_cc1_dgh_lv / tpc_cc2_dgh_lv = b'00
                ScalerSetBit(P66_05_CC1_DGH_LV + ucChannel, ~(_BIT7 | _BIT6), 0x00);
                break;
            case _TYPE_C_UNIT_10US:
                // [7:6] : tpc_cc1_dgh_lv / tpc_cc2_dgh_lv = b'01
                ScalerSetBit(P66_05_CC1_DGH_LV + ucChannel, ~(_BIT7 | _BIT6), _BIT6);
                break;
            case _TYPE_C_UNIT_100US:
                // [7:6] : tpc_cc1_dgh_lv / tpc_cc2_dgh_lv = b'10
                ScalerSetBit(P66_05_CC1_DGH_LV + ucChannel, ~(_BIT7 | _BIT6), _BIT7);
                break;
            case _TYPE_C_UNIT_1MS:
            default:
                // [7:6] : tpc_cc1_dgh_lv / tpc_cc2_dgh_lv = b'11
                ScalerSetBit(P66_05_CC1_DGH_LV + ucChannel, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                break;
        }
    }
    else
    {   // Setting De-glitch Level to Default Value (1us) For Invalid Input
        ScalerSetByte(P66_05_CC1_DGH_LV + ucChannel, 0x01);
    }   // End of if(ucTime < 64)
}

//--------------------------------------------------
// Description  : Set tCCDeBounce / tPDDebounce [0x6607 / 0x6608]
// Input Value  : bDbType   : _TYPE_C_CC / _TYPE_C_PD
//                ucTime    : 0-255
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcSetDebounce(bit bDbType, BYTE ucTime)
{
    if(bDbType == _TYPE_C_CC)
    {   // [0x6607] tCCDebounce = 100-200ms
        if((ucTime >= 100) && (ucTime <= 200))
        {   // tpc_db_time_tcc = ucTime
            ScalerSetByte(P66_07_TPC_TCC_DB_TIME, ucTime);
        }
        else
        {   // tpc_db_time_tcc = 150 ms
            ScalerSetByte(P66_07_TPC_TCC_DB_TIME, 150);
        }
    }
    else
    {   // [0x6608] tPDDebounce = 10-20ms
        if((ucTime >= 10) && (ucTime <= 20))
        {   // tpc_db_time_tpd = ucTime
            ScalerSetByte(P66_08_TPC_TPD_DB_TIME, ucTime);
        }
        else
        {   // tpc_db_time_tpd = 15 ms
            ScalerSetByte(P66_08_TPC_TPD_DB_TIME, 20);
        }
    }
}

//--------------------------------------------------
// Description  : Load Trimming Value From E-Fuse
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcLoadTrimming(void)
{
    BYTE pucEfuseValueTemp[8] = {0};

    // Read Check Bit
    ScalerEfuseGetData(_EFUSE_CHECK_BIT, 1, &pucEfuseValueTemp[0]);

    if((pucEfuseValueTemp[0] & 0xE0) != 0x00)
    {
        // Read CC Resistance
        ScalerEfuseGetData(_EFUSE_CC_RESISTANCE, 8, &pucEfuseValueTemp[0]);

        // CC1/CC2 Rp 12k
        ScalerSetByte(P66_1A_TPC_CC1_RP12K_CFG, (pucEfuseValueTemp[0] & 0x1F));
        ScalerSetByte(P66_1E_TPC_CC2_RP12K_CFG, (pucEfuseValueTemp[1] & 0x1F));

        // CC1/CC2 Rp 36k
        ScalerSetByte(P66_1B_TPC_CC1_RP36K_CFG, (pucEfuseValueTemp[2] & 0x1F));
        ScalerSetByte(P66_1F_TPC_CC2_RP36K_CFG, (pucEfuseValueTemp[3] & 0x1F));

        // SARSDC LDO
        ScalerSetBit(P7F_55_10B_ADC_LDO_CTRL, ~(_BIT3 | _BIT2 | _BIT1), ((pucEfuseValueTemp[2] & 0xE0) >> 4));

        // CC1/CC2 Rp 4.7k
        ScalerSetByte(P66_19_TPC_CC1_RP4P7K_CFG, (pucEfuseValueTemp[4] & 0x1F));
        ScalerSetByte(P66_1D_TPC_CC2_RP4P7K_CFG, (pucEfuseValueTemp[5] & 0x1F));

        // CC1/CC2 Rp 5.1k
        ScalerSetByte(P66_18_TPC_CC1_RD_CFG, (pucEfuseValueTemp[6] & 0x1F));
        ScalerSetByte(P66_1C_TPC_CC2_RD_CFG, (pucEfuseValueTemp[7] & 0x1F));

        // Read CC Resistance
        ScalerEfuseGetData(_EFUSE_CC_ATTACH_VOLTAGE, 8, &pucEfuseValueTemp[0]);

        // CC1 Attach Thershold
        ScalerSetByte(P66_10_CC1_VTH_CFG_0, pucEfuseValueTemp[0]);
        ScalerSetByte(P66_11_CC1_VTH_CFG_1, pucEfuseValueTemp[1]);
        ScalerSetByte(P66_12_CC1_VTH_CFG_2, pucEfuseValueTemp[2]);
        ScalerSetByte(P66_13_CC1_VTH_CFG_3, pucEfuseValueTemp[3]);

        // CC2 Attach Thershold
        ScalerSetByte(P66_14_CC2_VTH_CFG_0, pucEfuseValueTemp[4]);
        ScalerSetByte(P66_15_CC2_VTH_CFG_1, pucEfuseValueTemp[5]);
        ScalerSetByte(P66_16_CC2_VTH_CFG_2, pucEfuseValueTemp[6]);
        ScalerSetByte(P66_17_CC2_VTH_CFG_3, pucEfuseValueTemp[7]);

        // BMC RX Voltage Thershold
        ScalerEfuseGetData(_EFUSE_CC_BMC_TX_RX_VOLTAGE, 4, &pucEfuseValueTemp[0]);
        ScalerSetByte(P66_20_BMC_RX_SNK_VTH, pucEfuseValueTemp[0]);
        ScalerSetByte(P66_21_BMC_RX_SRC_VTH, pucEfuseValueTemp[1]);

        // BMC TX Swing Voltage
        ScalerSetBit(P66_22_BMC_TX_CFG, ~(_BIT2 | _BIT1 | _BIT0), (pucEfuseValueTemp[3] & 0x07));

        // VBus Comparator
        ScalerEfuseGetData(_EFUSE_VBUS_COMPARATOR, 1, &pucEfuseValueTemp[0]);
        ScalerSetBit(P7F_56_FRS_VBUS_COMP0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (pucEfuseValueTemp[0] & 0x3F));

        // ADC slop and offset
        ScalerEfuseGetData(_EFUSE_ADC_SLOP_OFFSET, 3, &pucEfuseValueTemp[0]);

        // slop*1000
        g_usSlop = (pucEfuseValueTemp[0] * 256 + pucEfuseValueTemp[1]);

        // offset
        g_ucoffset = (pucEfuseValueTemp[2] & 0x7F);
        g_bsign = ((pucEfuseValueTemp[2] & 0x80) >> 7);
    }
    else
    {
        // Setting Voltage Triming Value : CC1/2 200/400/660/800/1230/1600/2600/490 mV
        ScalerSetByte(P66_10_CC1_VTH_CFG_0, 0x88);  // 200 / 400 mV
        ScalerSetByte(P66_11_CC1_VTH_CFG_1, 0x77);  // 660 / 800 mV
        ScalerSetByte(P66_12_CC1_VTH_CFG_2, 0x67);  // 1230 / 1600 mV
        ScalerSetByte(P66_13_CC1_VTH_CFG_3, 0x55);  // 2600 / 490 mV

        ScalerSetByte(P66_14_CC2_VTH_CFG_0, 0x88);  // 200 / 400 mV
        ScalerSetByte(P66_15_CC2_VTH_CFG_1, 0x77);  // 660 / 800 mV
        ScalerSetByte(P66_16_CC2_VTH_CFG_2, 0x67);  // 1230 / 1600 mV
        ScalerSetByte(P66_17_CC2_VTH_CFG_3, 0x55);  // 2600 / 490 mV

        // Setting Resistor Triming Value : CC1/2 Rd/Rp-4.7K/Rp-12K/Rp-36K
        ScalerSetBit(P66_18_TPC_CC1_RD_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit(P66_19_TPC_CC1_RP4P7K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit(P66_1A_TPC_CC1_RP12K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit(P66_1B_TPC_CC1_RP36K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);

        ScalerSetBit(P66_1C_TPC_CC2_RD_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit(P66_1D_TPC_CC2_RP4P7K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit(P66_1E_TPC_CC2_RP12K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
        ScalerSetBit(P66_1F_TPC_CC2_RP36K_CFG, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);

        // Setting SRC/SNK VTH
        // ScalerSetByte(P66_20_BMC_RX_SNK_VTH, 0x38);
        ScalerSetByte(P66_20_BMC_RX_SNK_VTH, 0x37);
        ScalerSetByte(P66_21_BMC_RX_SRC_VTH, 0x57);

        // Setting Tx Term [7:4] = 4'b1000 (50) / Vswing [2:0] = 3'b010 (1.0V) MQP Test A Liittle Bit Higher
        ScalerSetByte(P66_22_BMC_TX_CFG, 0x82);

        // ideal slop*1000 = (2000 / 1024) * 1000 = 1953.125
        g_usSlop = 1953;

        // offset
        g_ucoffset = 0;
    }

    // Setting Rising / Falling Time
    ScalerSetByte(P66_23_BMC_TX_DRV_TM, 0x88);

    // Setting LPF
    ScalerSetBit(P66_24_BMC_LPF, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x08);
}

//--------------------------------------------------
// Description  : Type C Unattach (Turn Off Power / Disconnect Channel / Clear IRQs)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcUnattachReset(BYTE ucModeState)
{
    BYTE ucVbusDischargeCnt = 0;
    ucModeState = ucModeState;

    // Enable Vbus Discharge For Source to Discharge 5V
    if(ScalerTypeCPowerRx0CheckVbusSafe5V() == _TRUE)
    {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
        ScalerTypeCPmicRx0VbusDischarge(_ENABLE);
#endif
    }

    // Turn Off Vbus / Vconn, if they are turned on when attached
    ScalerTypeCRx0CcVconnControl(_OFF);
    ScalerTypeCPowerRx0VbusControl(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);

// =============================== Control By Power Delivery ??? ===============================
#if(_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON)
    // Disable FR_SWAP and FR_SWAP Bypass, if it is turned on when attached
    if((GET_RX0_SRC_FRSWAP_STATUS() == _ENABLE) || (GET_RX0_SNK_FRSWAP_STATUS() == _ENABLE))
    {
        ScalerTypeCRx0CcFastRoleSwapControl(_DISABLE);
        SET_RX0_SRC_FRSWAP_STATUS(_DISABLE);
        SET_RX0_SNK_FRSWAP_STATUS(_DISABLE);
    }
#endif
// =============================================================================================

    // [0x6630] Reset CC HW FSM
    // [6] hw_mode_fsm_rst = 0, [2] hw_done_irq_en = _DISABLE, [0] hw_unattach_irq_en = _DISABLE
#if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)
    // CTS FW Solution to Transit to Unattached.SRC (hw_mode_fsm_rst = 1 (Normal FSM Running))
    ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~(_BIT2 | _BIT0), 0x00);
#else
    ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~(_BIT6 | _BIT2 | _BIT0), 0x00);
#endif  // End of #if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)
    // [0x660C] Disconnect CC1/2 Channel, Detect Circuit
    // [7] tpc_cc1_det_en     = _TYPE_C_DISCONNECT
    // [6] tpc_cc2_det_en     = _TYPE_C_DISCONNECT
    // [5] tpc_cc1_channel_en = _TYPE_C_DISCONNECT
    // [4] tpc_cc2_channel_en = _TYPE_C_DISCONNECT
    ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable CC1/2 to BMC and Disable BMC Tx/Rx
    ScalerTypeCRx0CcSetBMC(_DISABLE);

    // Clear and Disable CC1/2_R_CHG_INT     [0x662C] = b'1010_0000
    ScalerSetBit(P66_2C_CC_R_CHG_INT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

// ===================================== DRP / SRC Switch =====================================
    // [0x6631] [6:5] HW Mode Type-C Port Role Setting (00:SRC-Only / 01:SNK-Only / 11:DRP)
    // [0x6635] [7:4] Set Initail State (0000: Unattach.SRC / 0001 : Unattach.SNK)
#if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)
    // [6:5] Source-Only Port ([4:3] Not Support Try.SRC/SNK)
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    ScalerSetBit(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#elif(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SNK_ONLY)
    // [6:5] Sink-Only Port ([4:3] Not Support Try.SRC/SNK)
    ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
    ScalerSetBit(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

#else

#if(_TYPE_C_CC_DRP_SWITCH_MODE == _TRUE)
    if(GET_TYPE_C_RX0_DRP_CONNECT_MODE() == _FALSE)
    {
        // ==================== SRC-Only Mode ====================

        // Switch to FW Mode to Disconnect Both CC1 / CC2, and Wait 30ms (Should Be More Than tPDDebounce Max)
        ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, 0x00);
        ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, 0x00);
        ScalerSetByte(P66_30_CC_HW_MODE_CTRL, 0x00);
        ScalerTimerDelayXms(30);

        // [6:5] Source-Only Port ([4:3] Not Support Try.SRC/SNK)
        ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
        ScalerSetBit(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Switch Connect Mode to DRP
        SET_TYPE_C_RX0_DRP_CONNECT_MODE();

        // Active Timer Event to Swith to DRP Mode if Not Attached in 2 Sec
        ScalerTimerActiveTimerEvent(1000, _SCALER_TIMER_EVENT_CC_RX0_STATE_TO_UNATTACH);
    }
    else
#endif
    {
        // ======================= DRP Mode =======================
        // [6:5] Dual Role Port ([4:3] Support Try.SRC/SNK)
        ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
        ScalerSetBit(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

        // Try.SRC/SNK Setting [4] Try.SRC [3] Try.SNK
#if(_TYPE_C_EMB_DRP_PREFER == _TYPE_C_DRP_TRY_SNK)
        ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT4 | _BIT3), _BIT3);
#elif(_TYPE_C_EMB_DRP_PREFER == _TYPE_C_DRP_TRY_SRC)
        ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT4 | _BIT3), _BIT4);
#else
        ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT4 | _BIT3), 0x00);
#endif  // End of #if(_TYPE_C_EMB_DRP_PREFER == _TYPE_C_DRP_TRY_SNK)

        // Switch Connect Mode to SRC-Only
        CLR_TYPE_C_RX0_DRP_CONNECT_MODE();
    }
#endif  // End of #if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)

#if((_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_PD) || (_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_POWER_BANK_CC))
    // If Enable Power Bnak Function when DC Off, Force Switch to SRC-Only
    if(ucModeState == _MODE_STATUS_POWER_OFF)
    {
        // [6:5] Source-Only Port ([4:3] Not Support Try.SRC/SNK)
        ScalerSetBit(P66_31_CC_HW_MODE_CFG, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
        ScalerSetBit(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
    }
#endif
// ===========================================================================================

    // CC Flags Reset
    CLR_CC_RX0_ATTACHED();
    CLR_CC_RX0_RA_EXIST();
    CLR_TYPE_C_ERROR_RECOVERY();
    CLR_CC_RX0_UNATTACH_DEBOUNCE();

    // Polling Until Vbus Discharge to 0V For At Most 5 times
    while((ucVbusDischargeCnt < 5) && (ScalerTypeCPowerRx0CheckVbusSafe0V() == _FALSE))
    {
        ucVbusDischargeCnt += 1;
        ScalerTimerDelayXms(1);
    }

#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
    // Disable Vbus Discharge
    ScalerTypeCPmicRx0VbusDischarge(_DISABLE);
#endif

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
    DebugMessageTypeC("O Type C State : UNATTACH", GET_TYPE_C_RX0_ATTACH_STATUS());
    DebugMessageTypeC("    [CC/RST] Vbus Status : ", GET_RX0_VBUS_STATUS());
    DebugMessageTypeC("    [CC/RST] Attach Status : ", GET_CC_RX0_ATTACHED());
#endif
}

//--------------------------------------------------
// Description  : Type C Setting For Connection (Select Resistor / Initial State / Connect Channels)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcConnectionSet(void)
{
#if(_TYPE_C_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // [0x6637][7:6] Setting SRC Rp Resistor (36K / 12K / 4.7K)
#if(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
    ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_DEF << 6));
    SET_CC_RX0_DEF_CUR(90);  // 90 * 10mA = 900mA
#elif(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
    ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_1P5A << 6));
    SET_CC_RX0_DEF_CUR(150); // 150 * 10mA = 1.5A
#else
    ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT7 | _BIT6), (_SET_RP_3P0A << 6));
    SET_CC_RX0_DEF_CUR(300); // 300 * 10mA = 3.0A
#endif  // End of #if(_TYPE_C_SRC_DEF_CUR == _SRC_DEF_USB)

    // Calculate Default OCP Current
    SET_CC_RX0_DEF_OCP_CUR((WORD)((DWORD)GET_CC_RX0_DEF_CUR() * _TYPE_C_DEF_OCP_RATIO / 100));

    // [5:4] Setting SNK CC1 Resistor
    ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT5 | _BIT4), (_SET_RD << 4));
    // [3:2] Setting SNK CC2 Resistor
    ScalerSetBit(P66_37_CC_HW_Z_CFG, ~(_BIT3 | _BIT2), (_SET_RD << 2));

#endif  // End of #if(_TYPE_C_CC_CONNECT_MODE == _TYPE_C_HW_MODE)

    // [0x660C] Connect CC1/2 Channel
    // [7] tpc_cc1_det_en = _TYPE_C_CONNECT
    // [6] tpc_cc2_det_en = _TYPE_C_CONNECT
    // [5] tpc_cc1_channel_en = _TYPE_C_CONNECT
    // [4] tpc_cc2_channel_en = _TYPE_C_CONNECT
    ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#if(_TYPE_C_CC_CONNECT_MODE == _TYPE_C_HW_MODE)
    // [0x6630] Enable HW Mode, Release Reset : Enable connect_en and Clear IRQs
    // [6] hw_mode_fsm_rst = 0
    // [5] hw_connect_en = _DISABLE
    // [3] hw_done_irq  = 1
    // [2] hw_done_irq_en = _DISABLE
    // [1] hw_unattach_irq = 1
    // [0] hw_unattach_irq_en = _DISABLE
    ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1));
#else
    // FW_MODE Reset
    ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
#endif

    // Active Timer Event to clear AC_ON_CABLE_DETECT flag if Not Attached in 500 ms
    ScalerTimerActiveTimerEvent(500, _SCALER_TIMER_EVENT_CC_RX0_CLEAR_AC_ON_DEVICE_DETECT);

    // Enable CC1/CC2 and Vbus Detect
    ScalerTypeCRx0CcVbusDetCtrl(_ENABLE);
    ScalerSetBit(P66_2B_CC_DIG_DET_R, ~_BIT6, _BIT6);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
    DebugMessageTypeC("O Type C State : CONNECTING...", GET_TYPE_C_RX0_ATTACH_STATUS());
    DebugMessageTypeC("    [CC/Connect Set] Default Current : ", GET_CC_RX0_DEF_CUR());
#endif
}

//--------------------------------------------------
// Description  : Set Attached Role, Resistors on CC and Orientation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTypeCRx0CcAttachedSetting(void)
{
    bit bPass = _FALSE;

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
    DebugMessageTypeC("O Type C State : CONNECTED!!!", GET_TYPE_C_RX0_ATTACH_STATUS());
#endif

    switch(GET_RX0_REG_CC_STATE())
    {
        case _ATTACHED_SRC:

            ScalerTypeCRx0PdSetPowerRole(_PD_POWER_SRC);

            if(ScalerGetBit(P66_33_CC_HW_FSM, (_BIT7)) == _BIT7)
            {   // Un-Flip : PD BMC Signal : CC1 / Vconn : CC2
                SET_CC_RX0_ORIENTATION(_TYPE_C_ORIENTATION_UNFLIP);

                // Get [0x662A][3:0], Check if Ra is Presented on CC2
                if(ScalerGetBit(P66_2A_CC_ANA_DET_R, (_BIT3 | _BIT2)) == 0x00)
                {
                    SET_CC_RX0_RA_EXIST();
                }

                // [0x660C] Disconnect CC2 Detection and BMC Channel
                // [6] tpc_cc2_det_en  = _TYPE_C_DISCONNECT
                // [2] tpc_cc2_en      = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT6 | _BIT4 | _BIT2), 0x00);

                bPass = _TRUE;
            }
            else
            {   // Flip : PD BMC Signal : CC2 / Vconn : CC1
                SET_CC_RX0_ORIENTATION(_TYPE_C_ORIENTATION_FLIP);

                // Check if Ra is Presented on CC2
                if(ScalerGetBit(P66_2A_CC_ANA_DET_R, (_BIT7 | _BIT6)) == 0x00)
                {
                    SET_CC_RX0_RA_EXIST();
                }

                // [0x660C] Disconnect CC1 Detection and BMC Channel
                // [7] tpc_cc1_det_en  = _TYPE_C_DISCONNECT
                // [3] tpc_cc1_en      = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT5 | _BIT3), 0x00);

                bPass = _TRUE;
            }

            break;

        case _ATTACHED_SNK:

            ScalerTypeCRx0PdSetPowerRole(_PD_POWER_SNK);

            if(ScalerGetBit(P66_33_CC_HW_FSM, (_BIT7)) == _BIT7)
            {   // Un-Flip : PD BMC Signal : CC1 / Vconn : CC2
                SET_CC_RX0_ORIENTATION(_TYPE_C_ORIENTATION_UNFLIP);

                // [0x660C] Disconnect CC2 Detection and BMC Channel
                // [6] tpc_cc2_det_en  = _TYPE_C_DISCONNECT
                // [2] tpc_cc2_en      = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT6 | _BIT4 | _BIT2), 0x00);

                bPass = _TRUE;
            }
            else
            {   // Flip : PD BMC Signal : CC2 / Vconn : CC1
                SET_CC_RX0_ORIENTATION(_TYPE_C_ORIENTATION_FLIP);

                // [0x660C] Disconnect CC1 Detection and BMC Channel
                // [7] tpc_cc1_det_en  = _TYPE_C_DISCONNECT
                // [3] tpc_cc1_en      = _TYPE_C_DISCONNECT (Not Needed)
                ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT5 | _BIT3), 0x00);

                bPass = _TRUE;
            }

            break;

        case _IDLE:
        case _UNATTACHED_SNK:
        case _ATTACHWAIT_SNK:
        case _UNATTACHED_SRC:
        case _ATTACHWAIT_SRC:
        case _TRY_SRC:
        case _TRY_WAIT_SNK:
        case _TRY_SNK:
        case _TRY_WAIT_SRC:
        case _UNATTACHED_ACCESSORY:
        case _ATTACH_WAIT_ACCESSORY:
        case _POWER_ACCESSORY:
        case _UNSUPORTED_ACCESSORY:
        case _DEBUG_ACCESSORY_SNK:
        case _AUDIO_ACCESSORY:
        case _AUDIO_ACCESSORY_SRC:
        case _DEBUG_ACCESSORY_SRC:
        default:
            // Not SRC nor SNK : ERROR !!!
            bPass = _FALSE;

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("  [Error] Type C Attach Check : State FAIL!!!", GET_RX0_REG_CC_STATE());
#endif

            break;
    }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
    if(bPass == _TRUE)
    {
        DebugMessageTypeC("    [CC/Attach Chk] : Pass ! ! ! ", GET_RX0_REG_CC_STATE());
        DebugMessageTypeC("    ----> Attach Role : SNK(0)/SRC(1)", ScalerTypeCRx0PdGetPowerRole());
        // DebugMessageTypeC("    ----> CC1 : Open/Ra/Rd/Rp-Def/Rp1.5/Rp3.0", GET_RX0_CC1_R());
        // DebugMessageTypeC("    ----> CC2 : Open/Ra/Rd/Rp-Def/Rp1.5/Rp3.0", GET_RX0_CC2_R());
        DebugMessageTypeC("    ----> Orientation : Unflip(1)/Flip(2)", GET_CC_RX0_ORIENTATION());
        DebugMessageTypeC("    ----> Ra Exist : ", GET_CC_RX0_RA_EXIST());
    }
#endif

    return bPass;
}

//--------------------------------------------------
// Description  : CC Check if Unattach Event is Triggered
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTypeCRx0CcUnattachCheck(void)
{
    bit bUnattach = _FALSE;

    // 1. Check if Error Recovery is SET
    if(GET_TYPE_C_ERROR_RECOVERY() == _TRUE)
    {
        if(ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC)
        {
#if(_TYPE_C_PMIC_TYPE != _PMIC_NONE)
            // Enable Vbus Discharge For Source to Discharge 5V
            ScalerTypeCPmicRx0VbusDischarge(_ENABLE);
#endif

            // Turn Off Vbus / Vconn, if they are turned on when attached
            ScalerTypeCRx0CcVconnControl(_OFF);
            ScalerTypeCPowerRx0VbusControl(_OFF, _PD_POWER_SNK, _PD_NONE_SETTING_PDO, 0, 0);
        }

        // Switch to FW Mode to Disconnect Both CC1 / CC2, and Wait 30ms (Should Be More Than tPDDebounce Max)
        ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, 0x00);
        ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, 0x00);
        ScalerSetByte(P66_30_CC_HW_MODE_CTRL, 0x00);
        ScalerTimerDelayXms(30);

        // Any Fatal Error Happens in PD, and Need to Unattach Type C Function
        bUnattach = _TRUE;
        CLR_TYPE_C_ERROR_RECOVERY();
    }

    // 2. For SRC Alway Check if SNK-Rd is Removed
    if(ScalerGetBit(P66_33_CC_HW_FSM, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x06)
    {
        if((ScalerGetByte(P66_2A_CC_ANA_DET_R) == 0xF0) || (ScalerGetByte(P66_2A_CC_ANA_DET_R) == 0x0F))
        {
            ADD_CC_RX0_UNATTACH_DEBOUNCE();

            if(GET_CC_RX0_UNATTACH_DEBOUNCE() > 10)
            {
                CLR_CC_RX0_UNATTACH_DEBOUNCE();
                bUnattach = _TRUE;
            }
        }
        else
        {
            CLR_CC_RX0_UNATTACH_DEBOUNCE();
        }
    }

    // 3. For SNK Not in PR_Swap Flow, Check if SRC-Rp is Removed
    if((ScalerTypeCRx0PdGetPowerRoleSwapProcessing() == _FALSE) && (ScalerGetBit(P66_33_CC_HW_FSM, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x03))
    {
        if(ScalerGetByte(P66_2A_CC_ANA_DET_R) == 0x00)
        {
            ADD_CC_RX0_UNATTACH_DEBOUNCE();

            if(GET_CC_RX0_UNATTACH_DEBOUNCE() > 0x0F)
            {
                CLR_CC_RX0_UNATTACH_DEBOUNCE();
                bUnattach = _TRUE;
            }
        }
        else
        {
            CLR_CC_RX0_UNATTACH_DEBOUNCE();
        }
    }

    if(bUnattach == _TRUE)
    {
        // Cancel AC_ON_CABLE_DETECT Timer Event & Clear AC_ON_DEVICE_DETECT flag when FW Unattach Event Triggered to update & maintain AC_ON_DEVICE_DETECT flag _False
        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_CC_RX0_CLEAR_AC_ON_DEVICE_DETECT);
        SET_TYPE_C_RX0_AC_ON_DEVICE_DETECT(_FALSE);
    }

    return bUnattach;
}

//--------------------------------------------------
// Description  : Enable / Disable Vconn Power
// Input Value  : bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcVconnControl(bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [0x6672] Reset and Enable CC2 OCP IRQs
            // [2]cc2_vconn_prot_irq      = 1
            // [1]cc2_vconn_shutdown_irq  = 1
            // [0]cc2_vconn_on_irq        = 1
            ScalerSetBit(P66_72_CC2_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc2_vconn_prot_irq_en    = _DISABLE
            // [5] cc2_vconn_shutdown_irq_en= _ENABLE
            // [4] cc2_vconn_on_irq_en      = _DISABLE
            ScalerSetBit(P66_72_CC2_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [0x660D] Turn On CC2 Vconn Switch : [2]tpc_cc2_vconn_en= _ENABLE
            ScalerSetBit(P66_0D_TPC_OCP_CTRL, ~_BIT2, _BIT2);

            SET_RX0_VCONN_STATUS(_ON);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("    [CC/Vconn] Vconn on CC2 : ", _TYPE_C_CC2);
            DebugMessageTypeC("    [CC/Vconn] Turn On Vconn : ", GET_RX0_VCONN_STATUS());
#endif
        }
        else if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            // [0x6671] Reset and Enable CC1 OCP IRQs
            // [2] cc1_vconn_prot_irq      = 1
            // [1] cc1_vconn_shutdown_irq  = 1
            // [0] cc1_vconn_on_irq        = 1
            ScalerSetBit(P66_71_CC1_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc1_vconn_prot_irq_en    = _DISABLE
            // [5] cc1_vconn_shutdown_irq_en= _ENABLE
            // [4] cc1_vconn_on_irq_en      = _DISABLE
            ScalerSetBit(P66_71_CC1_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [0x660D] Turn On CC1 Vconn Switch : [3] tpc_cc1_vconn_en= _ENABLE
            ScalerSetBit(P66_0D_TPC_OCP_CTRL, ~_BIT3, _BIT3);

            SET_RX0_VCONN_STATUS(_ON);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
            DebugMessageTypeC("    [CC/Vconn] Vconn on CC1 : ", _TYPE_C_CC1);
            DebugMessageTypeC("    [CC/Vconn] Turn On Vconn : ", GET_RX0_VCONN_STATUS());
#endif
        }
    }
    else
    {
        // Disable CC1/CC2 Vconn IRQs
        ScalerSetByte(P66_71_CC1_VCONN_OCP_INT, 0x00);
        ScalerSetByte(P66_72_CC2_VCONN_OCP_INT, 0x00);

        // [0x660D] Turn Off Both CC1/2 Vconn Switch : [3:2] tpc_cc1/2_vconn_en= _DISABLE
        ScalerSetBit(P66_0D_TPC_OCP_CTRL, ~(_BIT3 | _BIT2), 0x00); // [0x660D] <3:2> : tpc_cc1/2_vconn_en = _DISABLE
        SET_RX0_VCONN_STATUS(_OFF);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/Vconn] Turn Off Vconn : ", GET_RX0_VCONN_STATUS());
#endif
    }
}

//--------------------------------------------------
// Description  : Enable / Disable Vconn Power in Interrupt
// Input Value  : bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcVconnControl_EXINT0(bit bAction) using 1
{
    if(bAction == _ENABLE)
    {
        if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [0x6672] Reset and Enable CC2 OCP IRQs
            // [2]cc2_vconn_prot_irq      = 1
            // [1]cc2_vconn_shutdown_irq  = 1
            // [0]cc2_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc2_vconn_prot_irq_en    = _DISABLE
            // [5] cc2_vconn_shutdown_irq_en= _ENABLE
            // [4] cc2_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [0x660D] Turn On CC2 Vconn Switch : [2]tpc_cc2_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~_BIT2, _BIT2);

            SET_RX0_VCONN_STATUS(_ON);
        }
        else if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            // [0x6671] Reset and Enable CC1 OCP IRQs
            // [2] cc1_vconn_prot_irq      = 1
            // [1] cc1_vconn_shutdown_irq  = 1
            // [0] cc1_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc1_vconn_prot_irq_en    = _DISABLE
            // [5] cc1_vconn_shutdown_irq_en= _ENABLE
            // [4] cc1_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [0x660D] Turn On CC1 Vconn Switch : [3] tpc_cc1_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~_BIT3, _BIT3);

            SET_RX0_VCONN_STATUS(_ON);
        }
    }
    else
    {
        // Disable CC1/CC2 Vconn IRQs
        ScalerSetByte_EXINT(P66_71_CC1_VCONN_OCP_INT, 0x00);
        ScalerSetByte_EXINT(P66_72_CC2_VCONN_OCP_INT, 0x00);

        // [0x660D] Turn Off Both CC1/2 Vconn Switch : [3:2] tpc_cc1/2_vconn_en= _DISABLE
        ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~(_BIT3 | _BIT2), 0x00); // [0x660D] <3:2> : tpc_cc1/2_vconn_en = _DISABLE
        SET_RX0_VCONN_STATUS(_OFF);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable Vconn Power in Interrupt
// Input Value  : bAction : _ON / _OFF
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcVconnControl_WDINT(bit bAction) using 3
{
    if(bAction == _ENABLE)
    {
        if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [0x6672] Reset and Enable CC2 OCP IRQs
            // [2]cc2_vconn_prot_irq      = 1
            // [1]cc2_vconn_shutdown_irq  = 1
            // [0]cc2_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc2_vconn_prot_irq_en    = _DISABLE
            // [5] cc2_vconn_shutdown_irq_en= _ENABLE
            // [4] cc2_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P66_72_CC2_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [0x660D] Turn On CC2 Vconn Switch : [2]tpc_cc2_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~_BIT2, _BIT2);

            SET_RX0_VCONN_STATUS(_ON);
        }
        else if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_FLIP)
        {
            // [0x6671] Reset and Enable CC1 OCP IRQs
            // [2] cc1_vconn_prot_irq      = 1
            // [1] cc1_vconn_shutdown_irq  = 1
            // [0] cc1_vconn_on_irq        = 1
            ScalerSetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [6] cc1_vconn_prot_irq_en    = _DISABLE
            // [5] cc1_vconn_shutdown_irq_en= _ENABLE
            // [4] cc1_vconn_on_irq_en      = _DISABLE
            ScalerSetBit_EXINT(P66_71_CC1_VCONN_OCP_INT, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

            // [0x660D] Turn On CC1 Vconn Switch : [3] tpc_cc1_vconn_en= _ENABLE
            ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~_BIT3, _BIT3);

            SET_RX0_VCONN_STATUS(_ON);
        }
    }
    else
    {
        // Disable CC1/CC2 Vconn IRQs
        ScalerSetByte_EXINT(P66_71_CC1_VCONN_OCP_INT, 0x00);
        ScalerSetByte_EXINT(P66_72_CC2_VCONN_OCP_INT, 0x00);

        // [0x660D] Turn Off Both CC1/2 Vconn Switch : [3:2] tpc_cc1/2_vconn_en= _DISABLE
        ScalerSetBit_EXINT(P66_0D_TPC_OCP_CTRL, ~(_BIT3 | _BIT2), 0x00); // [0x660D] <3:2> : tpc_cc1/2_vconn_en = _DISABLE
        SET_RX0_VCONN_STATUS(_OFF);
    }
}

//--------------------------------------------------
// Description  : Enable / Disable BMC Channel in CC Logic
// Input Value  : Event : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcSetBMC(bit bAction)
{
    if(bAction == _ENABLE)
    {
        // 1. [0x6625] Set SRC/SNK BMC Vth_H/L and Enable BMC Rx ([3] Tx Controlled By HW)
        if(ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC)
        {   // [7:6] bmc_rx/tx_en = b'10 (Enable Rx, [3] Tx Control By HW)
            // [5:4] cc_bmc_rx_th_sel = 'b00
            ScalerSetBit(P66_25_BMC_TX_RX_CFG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT3));
        }
        else
        {   // [7:6] bmc_rx/tx_en = b'10 (Enable Rx, Tx Control By HW)
            // [5:4] cc_bmc_rx_th_sel = 'b11
            ScalerSetBit(P66_25_BMC_TX_RX_CFG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5 | _BIT4 | _BIT3));
        }

        // 2. [0x660C] Connect CC1 or CC2 to BMC Channel
        if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            // [3] tpc_cc1_en = _TYPE_C_CONNECT
            // [2] tpc_cc2_en = _TYPE_C_DISCONNECT (Not Needed)
            ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), _BIT3);
        }
        else
        {
            // [3] tpc_cc1_en = _TYPE_C_DISCONNECT  (Not Needed)
            // [2] tpc_cc2_en = _TYPE_C_CONNECT
            ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), _BIT2);
        }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
        if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
        {
            DebugMessageTypeC("    [CC/BMC] BMC Connected to CC1", bAction);
        }
        else
        {
            DebugMessageTypeC("    [CC/BMC] BMC Connected to CC2", bAction);
        }
#endif
    }
    else
    {   // [0x6625] Disable BMC Channel
        // [7] bmc_rx_en = _DISABLE
        // [6] bmc_tx_en = _DISABLE
        ScalerSetBit(P66_25_BMC_TX_RX_CFG, ~(_BIT7 | _BIT6), 0x00);

        // [0x660C] CC1/CC2 Disconnect to BMC Channel
        // [3] tpc_cc1_en = _TYPE_C_DISCONNECT
        // [2] tpc_cc2_en = _TYPE_C_DISCONNECT
        ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT3 | _BIT2), 0x00);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/BMC] BMC Disconnected", bAction);
#endif
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcVbusDetCtrl(bit bAction)
{
    // [0x6634] [7] vbus_det_dis
    if(bAction == _ENABLE)
    {   // Enable Vbus Detection : vbus_det_dis = _DISABLE
        ScalerSetBit(P66_34_CC_HW_STATE_CTRL, ~_BIT7, 0x00);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/Det Vbus] Start Vbus Detect", bAction);
#endif
    }
    else
    {   // Enable Vbus Detection : vbus_det_dis = _ENABLE
        ScalerSetBit(P66_34_CC_HW_STATE_CTRL, ~_BIT7, _BIT7);

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
        DebugMessageTypeC("    [CC/Det Vbus] Stop Vbus Detect", bAction);
#endif
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcVbusDetCtrl_EXINT0(bit bAction) using 1
{
    // [0x6634] Enable Vbus Detection
    // [7] vbus_det_dis    = _ENABLE
    if(bAction == _ENABLE)
    {
        ScalerSetBit_EXINT(P66_34_CC_HW_STATE_CTRL, ~_BIT7, 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P66_34_CC_HW_STATE_CTRL, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable Detect Vbus On/Off to transit State
// Input Value  : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcVbusDetCtrl_WDINT(bit bAction) using 3
{
    // [0x6634] Enable Vbus Detection
    // [7] vbus_det_dis    = _ENABLE
    if(bAction == _ENABLE)
    {
        ScalerSetBit_EXINT(P66_34_CC_HW_STATE_CTRL, ~_BIT7, 0x00);
    }
    else
    {
        ScalerSetBit_EXINT(P66_34_CC_HW_STATE_CTRL, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Update & Return CC Pin Resistor (Only For CC Pin, Not Vconn Pin)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerTypeCRx0CcDetResistor(void)
{
    // [0x662B] Set Up and Enable CC Pin Resistor Detect
    if(ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC)
    {
        // [7] det_resister_role = _PD_POWER_SRC (0), [6] det_resister_en = _ENABLE (1)
        ScalerSetBit(P66_2B_CC_DIG_DET_R, ~(_BIT7 | _BIT6), _BIT6);
    }
    else
    {
        // [7] det_resister_role = _PD_POWER_SNK (1), [6] det_resister_en = _ENABLE (1)
        ScalerSetBit(P66_2B_CC_DIG_DET_R, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }

    // [0x662C] Write 1 to Pop-Up Detect Result to [0x662B]
    ScalerSetBit(P66_2C_CC_R_CHG_INT, ~_BIT0, _BIT0);
    DELAY_5US();
    pData[0] = (ScalerGetByte(P66_2B_CC_DIG_DET_R));

    // Only Update Resistor of CC Pin, Not Vconn Pin (Flip : [5:3] CC1, Un-Flip : [2:0] CC2)
    if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
    {
        SET_RX0_CC1_R((pData[0] & (_BIT5 | _BIT4 | _BIT3)) >> 3);
        return GET_RX0_CC1_R();
    }
    else
    {
        SET_RX0_CC2_R(pData[0] & (_BIT2 | _BIT1 | _BIT0));
        return GET_RX0_CC2_R();
    }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
    if(GET_CC_RX0_ORIENTATION() == _TYPE_C_ORIENTATION_UNFLIP)
    {
        DebugMessageTypeC("[CC]  Resistor Detect CC1", GET_CC_RX0_ORIENTATION());
        DebugMessageTypeC("[CC]  Resistor Detect Result", GET_RX0_CC1_R());
    }
    else
    {
        DebugMessageTypeC("[CC]  Resistor Detect CC2", GET_CC_RX0_ORIENTATION());
        DebugMessageTypeC("[CC]  Resistor Detect Result", GET_RX0_CC2_R());
    }
#endif
}

//--------------------------------------------------
// Description  : TypeC Device Detect For initial setting port-searching time
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
void ScalerTypeCRx0CcACOnDeviceDetect(void)
{
    // Notice: For extreme case: tDRP = 50ms & dcSRC.DRP = 70 %, usResistor_hold_time shall be smaller than 15ms.
    // Notice: To avoid consistency issue between devices, usResistor_hold_time should be smaller than tPDDebounce(10ms).
    WORD usResistor_hold_time = 1;
    bit bACOnDeviceDetect = _FALSE;

    // 1. global_cc_en = _ENABLE, to enable CC register to be active
    ScalerSetBit(P66_00_GLOBAL_CTL, ~_BIT7, _BIT7);

    // 2. Switch to FW Mode
    ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~_BIT7, 0x00);

    // 3. Start storing CC attach voltage result to P66_2A_CC_ANA_DET_R
    // [0x660C] Connect CC1/2 Channel
    // [7] tpc_cc1_det_en = _TYPE_C_CONNECT
    // [6] tpc_cc2_det_en = _TYPE_C_CONNECT
    // [5] tpc_cc1_channel_en = _TYPE_C_CONNECT
    // [4] tpc_cc2_channel_en = _TYPE_C_CONNECT
    ScalerSetBit(P66_0C_TPC_CC_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // 4. FW Mode Resistor Asserted to detect TypeC device
    // 1st :
    // (1.) Set FW Mode Rd Resistor (5.1K)
    ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, _BIT7);
    ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, _BIT7);

    // (2.) Set CC1/CC2 FW Mode Vth (660mV / 1230mV)
    ScalerSetByte(P66_28_VTH_SEL, 0x00);

    // (3.) Assert Resistor for usResistor_hold_time ms, and judge whether CC1/CC2 vRd is in attached voltage range (vRd>0.2V)
    ScalerTimerDelayXms(usResistor_hold_time);
    if(((ScalerGetByte(P66_2A_CC_ANA_DET_R) & (_BIT4)) == _BIT4) || ((ScalerGetByte(P66_2A_CC_ANA_DET_R) & (_BIT0)) == _BIT0))
    {
        bACOnDeviceDetect = _TRUE;
    }
    else
    {
        // 2nd :
        // (1.) Set FW Mode Rp-3A @5V Resistor (4.7K)
        ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, _BIT3);
        ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, _BIT3);

        // (2.) Set CC1/CC2 FW Mode Vth (800mV / 2600mV)
        ScalerSetByte(P66_28_VTH_SEL, 0xFF);

        // (3.) Assert Resistor for usResistor_hold_time ms, and judge whether CC1/CC2 Rp-3A @5V is in attached voltage range (2600mV>vRd>800mV)
        ScalerTimerDelayXms(usResistor_hold_time);
        if(((ScalerGetByte(P66_2A_CC_ANA_DET_R) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == 0x70) || ((ScalerGetByte(P66_2A_CC_ANA_DET_R) & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x07))
        {
            bACOnDeviceDetect = _TRUE;
        }
        else
        {
            // 3rd :
            // (1.) Set FW Mode Rd Resistor (5.1K)
            ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, _BIT7);
            ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, _BIT7);

            // (2.) Set CC1/CC2 FW Mode Vth (660mV / 1230mV)
            ScalerSetByte(P66_28_VTH_SEL, 0x00);

            // (3.) Assert Resistor for usResistor_hold_time ms, and judge whether CC1/CC2 vRd is in attached voltage range (vRd>0.2V)
            ScalerTimerDelayXms(usResistor_hold_time);
            if(((ScalerGetByte(P66_2A_CC_ANA_DET_R) & (_BIT4)) == _BIT4) || ((ScalerGetByte(P66_2A_CC_ANA_DET_R) & (_BIT0)) == _BIT0))
            {
                bACOnDeviceDetect = _TRUE;
            }
        }
    }
    SET_TYPE_C_RX0_AC_ON_DEVICE_DETECT(bACOnDeviceDetect);
}

//--------------------------------------------------
// Description  : Return Port Controller CC Device Detect result to SysTypeC
// Input Value  : None
// Output Value : CC Device Detect result (_TRUE / _FALSE)
//--------------------------------------------------
bit ScalerTypeCRx0CcGetACOnDeviceDetect(void)
{
    return GET_TYPE_C_RX0_AC_ON_DEVICE_DETECT();
}

//--------------------------------------------------
// Description  : Process For Change Between SRC and SNK w/o Unattach
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcSwitchPowerRole(BYTE ucTargetRole)
{
    if(ucTargetRole == _PD_POWER_SRC)
    {   // Switch Type-C HW State From SNK to SRC (FW Solution)

        // 1. [0x665A/5B] Setting FW Mode Rp Resistor (36K / 12K / 4.7K)
#if(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
        ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, _BIT4);
        ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, _BIT4);

        // Set FW Mode Vth (200mV / 1600mV)
        ScalerSetByte(P66_28_VTH_SEL, 0x55);

#elif(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
        ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, _BIT5);
        ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, _BIT5);

        // Set FW Mode Vth (400mV / 1600mV)
        ScalerSetByte(P66_28_VTH_SEL, 0x99);

#else
        ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, _BIT3);
        ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, _BIT3);

        // Set FW Mode Vth (800mV / 2600mV)
        ScalerSetByte(P66_28_VTH_SEL, 0xFF);

#endif  // End of #if(_TYPE_C_SRC_DEF_CUR == _SRC_DEF_USB)

        // 2. Switch to FW Mode with Rp Aeesrted
        ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~_BIT7, 0x00);

        // 3. Set HW Mode FSM to Attached.SRC (!!! Warning : Flow or Delay Change May Cause Orientation Error)
        ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~_BIT6, 0x00);
        ScalerSetBit(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));
        ScalerTimerDelayXms(2);
        ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~_BIT6, _BIT6);

        // 4. Adjust BMC Rx Vth to SRC_H / SRC_L
        ScalerSetBit(P66_25_BMC_TX_RX_CFG, ~(_BIT5 | _BIT4), 0x00);

        // 5. Switch Back to HW Mode with FSM Already in Attached.SRC
        ScalerSetBit(P66_30_CC_HW_MODE_CTRL, ~_BIT7, _BIT7);
    }
    else
    {   // Switch Type-C HW State From SRC to SNK
        ScalerSetBit(P66_34_CC_HW_STATE_CTRL, ~_BIT5, _BIT5);
    }

#if((_DEBUG_MESSAGE_TYPE_C == _ON) && (_CC_FW_DEBUG == _ON))
    DebugMessageTypeC("    [CC/Resistor] Switch to SNK(0) / SRC(1): ", ucTargetRole);
#endif
}

//--------------------------------------------------
// Description  : Process For Change Between SRC and SNK w/o Unattach
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcSwitchPowerRole_EXINT0(BYTE ucTargetRole) using 1
{
    if(ucTargetRole == _PD_POWER_SRC)
    {
        // Switch Type-C HW State From SNK to SRC (FW Solution)

        // 1. [0x665A/5B] Setting FW Mode Rp Resistor (36K / 12K / 4.7K)
#if(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
        ScalerSetByte_EXINT(P66_5A_CC_FW_CC1_Z_CFG, _BIT4);
        ScalerSetByte_EXINT(P66_5B_CC_FW_CC2_Z_CFG, _BIT4);

        // Set FW Mode Vth (200mV / 1600mV)
        ScalerSetByte_EXINT(P66_28_VTH_SEL, 0x55);

#elif(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
        ScalerSetByte_EXINT(P66_5A_CC_FW_CC1_Z_CFG, _BIT5);
        ScalerSetByte_EXINT(P66_5B_CC_FW_CC2_Z_CFG, _BIT5);

        // Set FW Mode Vth (400mV / 1600mV)
        ScalerSetByte_EXINT(P66_28_VTH_SEL, 0x99);

#else
        ScalerSetByte_EXINT(P66_5A_CC_FW_CC1_Z_CFG, _BIT3);
        ScalerSetByte_EXINT(P66_5B_CC_FW_CC2_Z_CFG, _BIT3);

        // Set FW Mode Vth (800mV / 2600mV)
        ScalerSetByte_EXINT(P66_28_VTH_SEL, 0xFF);
#endif  // End of #if(_TYPE_C_SRC_DEF_CUR == _SRC_DEF_USB)

        // 2. Switch to FW Mode with Rp Aeesrted
        ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT7, 0x00);

        // 3. Set HW Mode FSM to Attached.SRC (!!! Warning : Flow or Delay Change May Cause Orientation Error)
        ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

        for(pData_EXINT[0] = 0; pData_EXINT[0] < 50; pData_EXINT[0] ++)
        {
            DELAY_40US_EXINT();
        }

        ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT6, _BIT6);

        // 4. Adjust BMC Rx Vth to SRC_H / SRC_L
        ScalerSetBit_EXINT(P66_25_BMC_TX_RX_CFG, ~(_BIT5 | _BIT4), 0x00);

        // 5. Switch Back to HW Mode with FSM Already in Attached.SRC
        ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT7, _BIT7);
    }
    else
    {   // Switch Type-C HW State From SRC to SNK
        ScalerSetBit_EXINT(P66_34_CC_HW_STATE_CTRL, ~_BIT5, _BIT5);
    }
}

//--------------------------------------------------
// Description  : Rx0 Cc Power Switch Proc
// Input Value  : enumPowerAction : Power Switch Enum
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            // AC On Enable CC, and Start From INITIAL State
            SET_CC_RX0_CONNECT_EN();

#if(_TYPE_C_CC_AC_ON_RECONNECT == _TRUE)
            SET_TYPE_C_RX0_AC_ON_RECONNECT();
#else
            CLR_TYPE_C_RX0_AC_ON_RECONNECT();
#endif

            SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_INITAIL);

            break;

        case _POWER_ACTION_AC_ON_TO_OFF:

            // Disable CC if DC Off Defined to No _TYPE_C_DC_OFF_NO_FUNCTION
#if(_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_NO_FUNCTION)
            CLR_CC_RX0_CONNECT_EN();

            // DC OFF = No Function, always SET AC ON Reconnect
            SET_TYPE_C_RX0_AC_ON_RECONNECT();
#else
            SET_CC_RX0_CONNECT_EN();

            // DC OFF != No Function,
#if(_TYPE_C_CC_AC_ON_RECONNECT == _TRUE)
            SET_TYPE_C_RX0_AC_ON_RECONNECT();
#else
            CLR_TYPE_C_RX0_AC_ON_RECONNECT();
#endif
#endif // End of #if(_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_NO_FUNCTION)

            // AC On Start From INITIAL State
            SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_INITAIL);

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

            // DC On Enable CC
            SET_CC_RX0_CONNECT_EN();

#if(_TYPE_C_EMB_DC_OFF_OPTION != _TYPE_C_DC_OFF_FULL_FUNCTION)
            if(GET_CC_RX0_ATTACHED() == _TYPE_C_ATTACH)
            {
                // Set Type C Error Recovery Flag to Unattach and Re-Connect
                SET_TYPE_C_ERROR_RECOVERY();
            }
            else
            {
                // CC Not Attached Yet, Back to Unattach
                SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH);
            }
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_TYPE_C_EMB_DC_OFF_OPTION != _TYPE_C_DC_OFF_FULL_FUNCTION)

            // If DC Off Defined to _TYPE_C_DC_OFF_NO_FUNCTION, Disable CC Function
#if(_TYPE_C_EMB_DC_OFF_OPTION == _TYPE_C_DC_OFF_NO_FUNCTION)
            CLR_CC_RX0_CONNECT_EN();

            // Disconnect CC, Only When Local Power Exist
            if(ScalerTypeCPowerCheckLocPowExist(_ON) == _TRUE)
            {
                ScalerSetByte(P66_5A_CC_FW_CC1_Z_CFG, 0x00);
                ScalerSetByte(P66_5B_CC_FW_CC2_Z_CFG, 0x00);
                ScalerSetByte(P66_30_CC_HW_MODE_CTRL, 0x00);
            }
#endif

            // Back to Unattach if Not _TYPE_C_DC_OFF_FULL_FUNCTION
            if(GET_CC_RX0_ATTACHED() == _TYPE_C_ATTACH)
            {
                SET_TYPE_C_ERROR_RECOVERY();
            }
            else
            {
                SET_TYPE_C_RX0_ATTACH_STATUS(_EMB_TPC_UNATTACH);
            }
#endif
            break;

        default:
            break;
    }
}

#if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)
//--------------------------------------------------
// Description  : FW Mode to Unattached.SRC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcFWModeSRCUnattached_EXINT0(void) using 1
{
    // 1. [0x665A/5B] Setting FW Mode Rp Resistor (36K / 12K / 4.7K)
#if(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_USB)
    ScalerSetByte_EXINT(P66_5A_CC_FW_CC1_Z_CFG, _BIT4);
    ScalerSetByte_EXINT(P66_5B_CC_FW_CC2_Z_CFG, _BIT4);

#elif(_TYPE_C_SRC_DEF_CUR == _TYPE_C_SRC_DEF_1P5A)
    ScalerSetByte_EXINT(P66_5A_CC_FW_CC1_Z_CFG, _BIT5);
    ScalerSetByte_EXINT(P66_5B_CC_FW_CC2_Z_CFG, _BIT5);

#else
    ScalerSetByte_EXINT(P66_5A_CC_FW_CC1_Z_CFG, _BIT3);
    ScalerSetByte_EXINT(P66_5B_CC_FW_CC2_Z_CFG, _BIT3);

#endif  // End of #if(_TYPE_C_SRC_DEF_CUR == _SRC_DEF_USB)

    // 2. Switch to FW Mode with Rp Aeesrted
    ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT7, 0x00);

    // 3. Set HW Mode FSM to Unattached.SRC
    ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT6, 0x00);
    ScalerSetBit_EXINT(P66_35_CC_HW_STATE_TRANSIT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT6, _BIT6);

    // 5. Switch Back to HW Mode with FSM Already in Unattached.SRC
    ScalerSetBit_EXINT(P66_30_CC_HW_MODE_CTRL, ~_BIT7, _BIT7);
}
#endif  // End of #if(_TYPE_C_EMB_PORT_ROLE == _TYPE_C_PORT_SRC_ONLY)

#if(_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable / Disable Fast Role Swap
// Input Value  : bAction : _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerTypeCRx0CcFastRoleSwapControl(bit bAction)
{
    if(bAction == _ENABLE)
    {
        if(ScalerTypeCRx0PdGetPowerRole() == _PD_POWER_SRC)
        {
            // [0x6666] Clear and Enable SRC FR_SWAP INT
            // [7] src_frs_done_int    = 1
            // [6] src_frs_done_int_en = _ENABLE
            ScalerSetBit(P66_66_SRC_FRS_INT, ~_BIT7, _BIT7);
            ScalerSetBit(P66_66_SRC_FRS_INT, ~_BIT6, _BIT6);

            // [0x6660] Turn On Source-Side FR_SWAP
            // [7] src_frs_en = _ENABLE
            ScalerSetBit(P66_60_FRS_CTRL, ~_BIT7, _BIT7);

            SET_RX0_SRC_FRSWAP_STATUS(_ENABLE);
        }
        else
        {
            // [0x6667] Clear and Enable SNK FR_SWAP INT
            // [7] snk_frs_done_int    = 1
            // [6] snk_frs_done_int_en = _ENABLE
            // [3] snk_frs_tri_int     = 1
            // [2] snk_frs_tri_int_en  = _ENABLE
            ScalerSetBit(P66_67_SNK_FRS_INT, ~_BIT7, _BIT7);
            ScalerSetBit(P66_67_SNK_FRS_INT, ~_BIT6, _BIT6);
            ScalerSetBit(P66_67_SNK_FRS_INT, ~_BIT3, _BIT3);
            ScalerSetBit(P66_67_SNK_FRS_INT, ~_BIT2, _BIT2);

            // [0x6660] Turn On Sink-Side FR_SWAP
            // [6] snk_frs_en = _ENABLE
            ScalerSetBit(P66_60_FRS_CTRL, ~_BIT6, _BIT6);

            SET_RX0_SNK_FRSWAP_STATUS(_ENABLE);
        }   // End of if(GET_PD_RX0_POWER_ROLE() == _PD_POWER_SRC)
    }
    else
    {   // [0x6666] Disable SRC FR_SWAP INT
        // [6] src_frs_done_int_en = _DISABLE
        ScalerSetBit(P66_66_SRC_FRS_INT, ~_BIT6, 0x00);

        // [0x6667] Disable SNK FR_SWAP INT
        // [6] snk_frs_done_int_en = _DISABLE
        // [2] snk_frs_tri_int_en  = _DISABLE
        ScalerSetBit(P66_67_SNK_FRS_INT, ~(_BIT6 | _BIT2), 0x00);

        // [0x6660] Turn Off Source/Sink-Side FR_SWAP
        // [7] src_frs_en = _DISABLE
        // [6] snk_frs_en = _DISABLE
        ScalerSetBit(P66_60_FRS_CTRL, ~(_BIT7 | _BIT6), 0x00);

        // [0x6668] Turn Off Fast-Role Swap
        ScalerSetBit(P66_68_FRS_BYPASS_MODE, ~_BIT7, 0x00);

        SET_RX0_SRC_FRSWAP_STATUS(_DISABLE);
        SET_RX0_SNK_FRSWAP_STATUS(_DISABLE);
    }
}
#endif  // End of #if(_TYPE_C_EMB_PD3_FRSWAP_SUPPORT == _ON)

#endif  // End of #if(_D0_DP_TYPE_C_PORT_CTRL_TYPE == _PORT_CONTROLLER_EMBEDDED))

