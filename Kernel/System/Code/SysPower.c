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
// ID Code      : SysPower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_POWER__

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
StructPowerInfoType g_stPowerInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysPowerInitial(void);
void SysPowerHandler(void);
void SysPowerSwitch(EnumPowerAction enumSwitch);

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
void SysPowerIdleProc(void);
#endif

BYTE SysPowerGetPowerStatus(void);
void SysPowerSystemClockSelect(BYTE ucClockSel);
void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus);

#if(_DIGITAL_PORT_SUPPORT == _ON)
void SysPowerLoadHDCPKey(void);

#if(_DP_TX_SUPPORT == _ON)
void SysPowerLoadDPTxHDCPKey(void);
#endif
#endif

void SysPowerIsolation(EnumPowerAction enumSwitch);
void SysPowerRecoverIsolationAreaData(void);
bit SysPowerCheckFakeSaving(void);
bit SysPowerCheckFakeOff(void);
bit SysPowerCheckNormal(void);

#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
void SysPowerMHLPowerCutProc(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Source Switch Flags
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerInitial(void)
{
    // Scaler whole chip reset
    ScalerGlobalWholeChipReset();

#if((_LC_TANK_SUPPORT != _ON) || (_XTALESS_SUPPORT != _ON))
    // Internal oscillator trimming and on
    ScalerIOSCTrimming();
#endif

    // Initial PC99 System Control
#if(_HW_PC99_SUPPORT == _ON)
    ScalerPC99EDIDInitialControl();
#endif

    // Initial LDO Voltage Output
    ScalerLDOPowerControl(_POWER_STATUS_AC_ON);

    ///////////////////
    // Load EDID     //
    ///////////////////
#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
    UserCommonInterfaceNVRamRestoreEDID();
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
    UserCommonInterfaceLoadEmbeddedEdidData();
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
    // External Edid GPO Initial
    UserCommonInterfaceHDMIMultiEdidInitial();
#endif

#if 0//(_PCB_TYPE == _RL6432_BEACON_B_156PIN_1A1H2DP_LVDS_eDP)
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT))
    PCB_D3_HOTPLUG(_D3_HOT_PLUG_LOW);
    ScalerTimerDelayXms(150);
    PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
#endif
#endif

    ///////////////////
    // Load HDCP Key //
    ///////////////////
    // HDCP Initial
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
    UserCommonInterfaceNVRamRestoreHDCP();
#endif // End of #if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)

#if(_DIGITAL_PORT_SUPPORT == _ON)
    SysPowerLoadHDCPKey();
#endif

    //////////////////////////
    // CEC Initial Setting //
    //////////////////////////
#if(_HDMI_CEC_SUPPORT == _ON)
    ScalerCecInitial();
    ScalerCecFunctionEnable(UserInterfaceCecGetCecActive());
#endif

    /////////////////////////////////////
    // DP Aux and DPCD Initial Setting //
    /////////////////////////////////////

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

    if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D0_INPUT_PORT)
    {
        ScalerDpInitial(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT));
    }
    else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D1_INPUT_PORT)
    {
        ScalerDpInitial(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpLaneCount(_D1_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D1_INPUT_PORT));
    }
    else if(GET_DP_EMBEDDED_SWITCH_SELECT() == _D2_INPUT_PORT)
    {
        ScalerDpInitial(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserInterfaceGetDpLaneCount(_D2_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D2_INPUT_PORT));
    }

#else // Else of #if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
    {
        ScalerDpInitial(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpLaneCount(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D6_INPUT_PORT));
        ScalerDpInitial(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT));
    }
    else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
    {
        ScalerDpInitial(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT));
        ScalerDpInitial(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpLaneCount(_D6_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D6_INPUT_PORT));
    }
#else
    ScalerDpInitial(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpLaneCount(_D0_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D0_INPUT_PORT));
#endif

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerDpInitial(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpLaneCount(_D1_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D1_INPUT_PORT));
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
    ScalerDpInitial(_D2_INPUT_PORT, UserInterfaceGetDPVersion(_D2_INPUT_PORT), UserInterfaceGetDpLaneCount(_D2_INPUT_PORT), UserCommonInterfaceGetDpMstCapablePort(), UserInterfaceGetFreeSyncEnable(_D2_INPUT_PORT));
#endif

#endif // End of #if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
    ScalerDpHdcpCtrlDpcdSwitch(SysSourceGetInputPort());
#endif

    /////////////////////////////////////
    // DP MST Initial Setting //
    /////////////////////////////////////

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpRxMstPowerOnInitial();

#if(_DP_MST_AUTO_SEARCH_SUPPORT == _OFF)
    ScalerDpRxMstInitial(UserCommonInterfaceGetDpMstCapablePort());
#endif
#endif

    /////////////////////////////////////
    // DP Tx Initial Setting //
    /////////////////////////////////////

#if((_DP_TX_SUPPORT == _ON) && (_DP_TX_BLOCK_CONTROL_BEFORE_STREAM_OUTPUT == _ON))
    ScalerDpTxCloneModeSwitch(UserInterfaceGetDpCloneOutputStatus());
#endif

    /////////////////////////////////////
    // TYPE-C Initial Setting //
    /////////////////////////////////////
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
    // When AC ON, detect TypeC device & initially update the result
    ScalerTypeCRx0CcACOnDeviceDetect();
#endif

    SysTypeCInitial();
#endif

    //////////////////////////////
    // MHL CBus Initial Setting //
    //////////////////////////////
    ScalerPinshareCBUSPinInitialReset();

#if(_MHL_SUPPORT == _ON)
    ScalerMHLInitialSettings();
#endif



    //////////////////////
    // Memory Power Off //
    //////////////////////

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    ScalerMemoryPowerControl(_OFF);

#if((_DDR1_PHASE_CALIBRATION == _ON) || (_SDRAM_PHASE_CALIBRATION == _ON))
    CLR_FIRST_AUTOK_STATUS();
#endif

#endif


    ///////////////////////////////////////
    // All Group Power Cut and Isolation //
    ///////////////////////////////////////

    SysPowerIsolation(_POWER_ACTION_AC_ON_INITIAL);
}

//--------------------------------------------------
// Description  : Power Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerHandler(void)
{
    // The process will deal with all kinds of power changing by power action flag.
    switch(GET_TARGET_POWER_STATUS())
    {
        case _POWER_STATUS_NORMAL:

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_OFF:

                    if(SysPowerCheckNormal() == _TRUE)
                    {
                        SysPowerSwitch(_POWER_ACTION_OFF_TO_NORMAL);
                    }
                    else
                    {
                        SysPowerSwitch(_POWER_ACTION_OFF_TO_FAKE_OFF);
                    }
                    break;

                case _POWER_STATUS_SAVING:

                    SysPowerSwitch(_POWER_ACTION_PS_TO_NORMAL);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                    if(UserInterfaceGetAIOModernStandbyMode() == _AIO_MODERN_STANDBY_MODE_ENABLE)
                    {
                        SET_AIO_MODERN_STANDBY_MODE();
                        ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_AIO_MODERN_STANDBY_MODE_TIMEOUT);
                    }
                    else
                    {
                        CLR_AIO_MODERN_STANDBY_MODE();
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AIO_MODERN_STANDBY_MODE_TIMEOUT);
                    }
#endif
                    break;

                case _POWER_STATUS_AC_ON:
                    SysPowerSwitch(_POWER_ACTION_AC_ON_TO_NORMAL);
                    break;

                case _POWER_STATUS_NORMAL:

                    if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE))
                    {
                        CLR_POWER_SWITCH_TO_FAKE_OFF();
                        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);
                        SysPowerSwitch(_POWER_ACTION_FAKE_OFF_TO_NORMAL);
                    }
                    else if(GET_POWER_SWITCH_TO_FAKE_SAVING() == _TRUE)
                    {
                        CLR_POWER_SWITCH_TO_FAKE_SAVING();
                        SysPowerSwitch(_POWER_ACTION_FAKE_PS_TO_NORMAL);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
                        if(UserInterfaceGetAIOModernStandbyMode() == _AIO_MODERN_STANDBY_MODE_ENABLE)
                        {
                            SET_AIO_MODERN_STANDBY_MODE();
                            ScalerTimerReactiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_AIO_MODERN_STANDBY_MODE_TIMEOUT);
                        }
                        else
                        {
                            CLR_AIO_MODERN_STANDBY_MODE();
                            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_AIO_MODERN_STANDBY_MODE_TIMEOUT);
                        }
#endif
                    }

                    break;

                default:
                    break;
            }

            SET_POWER_STATUS(_POWER_STATUS_NORMAL);

            break;

        case _POWER_STATUS_OFF:

            CLR_POWER_SWITCH_TO_FAKE_SAVING();

            // Clear Mode change flag
            CLR_MODE_STATE_CHANGE_MODE();

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_SAVING:
                    SysPowerSwitch(_POWER_ACTION_PS_TO_OFF);
                    SET_POWER_STATUS(_POWER_STATUS_OFF);
                    break;

                case _POWER_STATUS_AC_ON:
                    SysPowerSwitch(_POWER_ACTION_AC_ON_TO_OFF);
                    SET_POWER_STATUS(_POWER_STATUS_OFF);
                    break;

                case _POWER_STATUS_NORMAL:

                    if(SysPowerCheckFakeOff() == _FALSE)
                    {
                        CLR_POWER_SWITCH_TO_FAKE_OFF();
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_OFF);
                        SET_POWER_STATUS(_POWER_STATUS_OFF);
                    }
                    else
                    {
                        SET_POWER_SWITCH_TO_FAKE_OFF();
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_OFF);
                    }
                    break;

                default:
                    break;
            }

            break;

        case _POWER_STATUS_SAVING:

            CLR_POWER_SWITCH_TO_FAKE_SAVING();

            switch(GET_POWER_STATUS())
            {
                case _POWER_STATUS_NORMAL:

                    if(UserCommonInterfaceCheckFakeSaving() == _TRUE)
                    {
                        SET_POWER_SWITCH_TO_FAKE_SAVING();
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_FAKE_PS);
                    }
                    else
                    {
                        SysPowerSwitch(_POWER_ACTION_NORMAL_TO_PS);
                        SET_POWER_STATUS(_POWER_STATUS_SAVING);
                    }

                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }

    // Clear power action to avoid repeat calls in next circle.
    SET_TARGET_POWER_STATUS(_POWER_STATUS_NONE);

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
    // Flash go into idle mode to reduce overall system power consumption under power saving and power off status.
    if(((GET_POWER_STATUS() == _POWER_STATUS_SAVING) || (GET_POWER_STATUS() == _POWER_STATUS_OFF)) && (UserCommonInterfaceGetRunDdcciCommand() == _FALSE))
    {
        // Call operation function to make Flash into idle mode.
        SysPowerIdleProc();
    }
#endif
}

//--------------------------------------------------
// Description  : Deal With Power Manage According To Input Pamater
// Input Value  : ucSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void SysPowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_NORMAL_TO_PS:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif
            // Mode Power Saving Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_SAVING);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
            ScalerMemoryPowerControl(_OFF);
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCPowerSwitch(enumSwitch);
#endif

#if(_DP_SUPPORT == _ON)
            // DP Fake LT Protect
            ScalerSyncDpFakeLTProtect();
#endif

#if(_HDMI_SUPPORT == _ON)
            if(UserInterfaceGetForcePSStatus() == _TRUE)
            {
                SysTMDSRxSetPsWakeupHpdToggle();
            }
#endif

#if(_SYSTEM_LOW_POWER_GEN == _POWER_FLOW_GEN_1)
            // Interface Power Saving Process
            ScalerSyncPowerProc(enumSwitch);
#endif

            // Set mcu module to power saving state
            ScalerMcuPwmControl(_POWER_STATUS_SAVING);

            // Set Pin configure to power saving state
            ScalerPinshareConfig(_POWER_STATUS_SAVING);

            // Some Case Power Fake Saving Proc
#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
            SysPowerMHLPowerCutProc();
#endif
            // Select Internal Oscillator or EXT Xtal as System Clock.
            SysPowerSystemClockSelect(_SYS_PS_CLOCK_SOURCE);

#if(_SYSTEM_LOW_POWER_GEN == _POWER_FLOW_GEN_2)
            // Interface Power Saving Process
            ScalerSyncPowerProc(enumSwitch);
#endif

            // Enable all power cut area.
            SysPowerIsolation(enumSwitch);

            // LDO low power control.
            ScalerLDOPowerControl(_POWER_STATUS_SAVING);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR))
            if((GET_D0_CABLE_STATUS() == _FALSE) || (UserInterfaceGetRepeaterIntoPowerOff() == _DATA_EXCHANGE_REPEATER_POWER_OFF))
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DP_REPEATER_TYPE == _REPEATER_RTS_TRANSLATOR))
            if((GET_D1_CABLE_STATUS() == _FALSE) || (UserInterfaceGetRepeaterIntoPowerOff() == _DATA_EXCHANGE_REPEATER_POWER_OFF))
#endif
            {
                // Switch Off Repeater Power By PCB Control
                PCB_TWO_CHIP_REPEATER_POW(_TWO_CHIP_REPEATER_POWER_OFF);

                // Switch Off Repeater Power By PCB Control
                PCB_TWO_CHIP_PORT_CTRL_POW(_TWO_CHIP_PORT_CTRL_POWER_OFF);

                // Clear status that might cause PS predetect passed unexpetedly
                ScalerSyncDpRepeaterPowerOffReset();
            }
#endif

            // Set SI's powerboard to low power
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_ON);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif
            SysSourcePowerOffProc();

            // Mode Power Off Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_OFF);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
            ScalerMemoryPowerControl(_OFF);
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCPowerSwitch(enumSwitch);
#endif

#if(_DP_SUPPORT == _ON)
            // DP Fake LT Protect
            ScalerSyncDpFakeLTProtect();
#endif

#if(_SYSTEM_LOW_POWER_GEN == _POWER_FLOW_GEN_1)
            // Interface Power Off Process
            ScalerSyncPowerProc(enumSwitch);
#endif

            // Set mcu module to power off state
            ScalerMcuPwmControl(_POWER_STATUS_OFF);

            // Set mcu module to power off state
            ScalerPinshareConfig(_POWER_STATUS_OFF);

            // Select internal oscillator as system clock.
            SysPowerSystemClockSelect(_IOSC_CLK);

#if(_SYSTEM_LOW_POWER_GEN == _POWER_FLOW_GEN_2)
            // Interface Power Off Process
            ScalerSyncPowerProc(enumSwitch);
#endif

            // Enable all power cut area.
            SysPowerIsolation(enumSwitch);

            // LDO low power control.
            ScalerLDOPowerControl(_POWER_STATUS_OFF);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            // Switch Off Repeater Power By PCB Control
            PCB_TWO_CHIP_REPEATER_POW(_TWO_CHIP_REPEATER_POWER_OFF);

            // Switch Off Repeater Power By PCB Control
            PCB_TWO_CHIP_PORT_CTRL_POW(_TWO_CHIP_PORT_CTRL_POWER_OFF);
#endif

            // Set SI's powerboard to low power
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_ON);

            break;

        case _POWER_ACTION_PS_TO_OFF:

            // User Power process
            UserInterfacePowerSwitch(enumSwitch);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCPowerSwitch(enumSwitch);
#endif

            SysSourcePowerOffProc();

            // Interface Power Off Process
            ScalerSyncPowerProc(enumSwitch);

            // Set mcu module to power off state
            ScalerMcuPwmControl(_POWER_STATUS_OFF);

            // Pin configure to power off state.
            ScalerPinshareConfig(_POWER_STATUS_OFF);

            // Enable all power cut area.
            SysPowerIsolation(enumSwitch);

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            // Switch Off Repeater Power By PCB Control
            PCB_TWO_CHIP_REPEATER_POW(_TWO_CHIP_REPEATER_POWER_OFF);

            // Switch Off Repeater Power By PCB Control
            PCB_TWO_CHIP_PORT_CTRL_POW(_TWO_CHIP_PORT_CTRL_POWER_OFF);
#endif

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_FAKE_OFF:

            // Wake up SI's powerboard
            PCB_POWERBOARD_LOWPOWER(_LOW_POWER_OFF);

            // LDO to normal setting.
            ScalerLDOPowerControl(_POWER_STATUS_NORMAL);

            // Disable all power cut area.
            SysPowerIsolation(enumSwitch);

#if(_LC_TANK_SUPPORT == _ON)
#if(_XTALESS_SUPPORT == _ON)
            ScalerLCTankSystemInitial();
#endif
#endif

#if(_SYSTEM_LOW_POWER_GEN == _POWER_FLOW_GEN_2)
            // Sync Power On Process
            ScalerSyncPowerProc(enumSwitch);
#endif

            // Select M2PLL as system clock.
            SysPowerSystemClockSelect(_M2PLL_CLK);

#if(_AUDIO_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _ON)
            // Audio ADC initial
            ScalerAudioADCInitial();
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
            // Audio DAC initial, Initialize Audio DAC to Gain Depop Time
            ScalerAudioDACInitial();
#endif
#endif
            // Recovery data in all power cut area
            SysPowerRecoverIsolationAreaData();

#if(_SYSTEM_LOW_POWER_GEN == _POWER_FLOW_GEN_1)
            // Sync Power On Process
            ScalerSyncPowerProc(enumSwitch);
#endif

            // Pin configure to normal state.
            ScalerPinshareConfig(_POWER_STATUS_NORMAL);

            // Set mcu module to normal state
            ScalerMcuPwmControl(_POWER_STATUS_NORMAL);

            // User Power Process
            UserInterfacePowerSwitch(enumSwitch);

            // User initial LUT/Latch/SRAM tabled data
            UserCommonInterfaceOsdPowerOnInitial();

#if(_TWO_CHIP_DATA_EXCHANGE_MODE != _DATA_EXCHANGE_MODE_NONE)
            if((GET_PCB_TWO_CHIP_REPEATER_POW_STATUS() == _TWO_CHIP_REPEATER_POWER_OFF) ||
               (enumSwitch == _POWER_ACTION_AC_ON_TO_NORMAL))
            {
                // Switch On Repeater Power By PCB Control
                PCB_TWO_CHIP_REPEATER_POW(_TWO_CHIP_REPEATER_POWER_ON);

                // Transmit Local Data to Repeater Device for Synchronization
                UserCommonDataExchangeInit();
            }

            if(GET_PCB_TWO_CHIP_PORT_CTRL_POW_STATUS() == _TWO_CHIP_PORT_CTRL_POWER_OFF)
            {
                // Switch On Repeater Power By PCB Control
                PCB_TWO_CHIP_PORT_CTRL_POW(_TWO_CHIP_PORT_CTRL_POWER_ON);
            }
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
            ScalerMemoryPowerControl(_ON);
#endif
            // Clear Source Ready Flag
            SysSourceInfoReset();

#if(_TRANSLATOR_SUPPORT == _OFF)
            // Set Display to Free Run Mode
            SysModeSetFreeRun();

            // Initialize Osd Position
            ScalerGlobalOsdInitial();
#endif

#if(_VGA_SUPPORT == _ON)
            // Calibrate sync processor HS delay
            ScalerVgaTopModifyHsLatchEdgeDelay();
#endif

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif

#if((_DDR1_PHASE_CALIBRATION == _ON) || (_SDRAM_PHASE_CALIBRATION == _ON))
            if(enumSwitch != _POWER_ACTION_AC_ON_TO_NORMAL)
            {
                // Restore memory initial phase
#if(_DDR1_PHASE_CALIBRATION == _ON)
                ScalerDDR1RestoreInitialPhase();
#elif(_SDRAM_PHASE_CALIBRATION == _ON)
                ScalerSdramRestoreInitialPhase();
#endif
            }
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCPowerSwitch(enumSwitch);
#endif

#if(_DP_SUPPORT == _ON)
#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
            if((enumSwitch == _POWER_ACTION_OFF_TO_NORMAL) || (enumSwitch == _POWER_ACTION_OFF_TO_FAKE_OFF))
            {
                ScalerDpHdcpCtrlDpcdSwitch(SysSourceGetInputPort());
            }
#endif
            SysDpDcOffHPDToggleProc(enumSwitch);
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_PS:

            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_NORMAL_TO_PS);

            break;

        case _POWER_ACTION_NORMAL_TO_FAKE_OFF:

            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_NORMAL_TO_OFF);

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(enumSwitch);
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCPowerSwitch(enumSwitch);
#endif

            SysSourcePowerOffProc();

            // Interface Power Process
            ScalerSyncPowerProc(enumSwitch);

            // Mode Power Off Process
            SysModeResetState(_MODE_ACTION_RESET_TO_POWER_OFF);

            break;

        case _POWER_ACTION_FAKE_OFF_TO_NORMAL:

#if(_AUDIO_SUPPORT == _ON)
#if(_LINE_IN_SUPPORT == _ON)
            // Audio ADC initial
            ScalerAudioADCInitial();
#endif

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCPowerSwitch(enumSwitch);
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
            // Audio DAC initial, Initialize Audio DAC to Gain Depop Time
            ScalerAudioDACInitial();
#endif
#endif

            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_OFF_TO_NORMAL);

            // User initial LUT/Latch/SRAM tabled data
            UserCommonInterfaceOsdPowerOnInitial();

#if(_AUDIO_SUPPORT == _ON)
            SysAudioPowerProc(_POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_DP_SUPPORT == _ON)
            SysDpDcOffHPDToggleProc(enumSwitch);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
            // Set Display to Free Run Mode
            SysModeSetFreeRun();

            // Initialize Osd Position
            ScalerGlobalOsdInitial();
#endif

            break;

        case _POWER_ACTION_FAKE_PS_TO_NORMAL:

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
            SysTypeCPowerSwitch(enumSwitch);
#endif

            // User Power Process
            UserInterfacePowerSwitch(_POWER_ACTION_PS_TO_NORMAL);

            break;

        default:
            break;
    }
}

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MCU Work In Idle Mode In A Short Period Of Time.
// Input Value  : None.
// Output Value : None
//--------------------------------------------------
void SysPowerIdleProc(void)
{
    // Set Timer2 Count to 100ms but Reload value remains the same(1ms)
    ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_IDLE_MODE);

    // Enter Idle Mode
    ScalerMcuIntoIdle();

    // Add Timer Counter according to Timer2
    ScalerTimerAddTimerCounter();

    // Set Timer2 Count to 1ms
    ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_SAVING_MODE);
}
#endif // End of #if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Current System Power Status.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE SysPowerGetPowerStatus(void)
{
    switch(GET_POWER_STATUS())
    {
        case _POWER_STATUS_NORMAL:

            if(GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE)
            {
                return _POWER_STATUS_OFF;
            }

            if(GET_POWER_SWITCH_TO_FAKE_SAVING() == _TRUE)
            {
                return _POWER_STATUS_SAVING;
            }

            return GET_POWER_STATUS();

            break;

        default:

            return GET_POWER_STATUS();

            break;
    }

    return GET_POWER_STATUS();
}

//--------------------------------------------------
// Description  : Clock Select For System.
// Input Value  : ucClockSel    --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void SysPowerSystemClockSelect(BYTE ucClockSel)
{
    BYTE ucGlobalIRQTemp = 0;

    if(ucClockSel == _M2PLL_CLK)
    {
        // Power on Xtal Clock.
        ScalerPowerXtalPower(_ON);

        // Power on M2PLL.
        ScalerPLLM2PLLPower(_ON);

        // Backup Global IRQ Control Status
        ucGlobalIRQTemp = ScalerGlobalGetIRQControl();

        ScalerGlobalIRQControl(_DISABLE);

        // Cache control by IC base
        ScalerMcuCacheControl(_ENABLE);

        // Set Mcu/Flash Clock to M2PLL
        ScalerMcuFlashClockGroupSetting(_M2PLL_CLK);

        // Restore Global IRQ Control Status
        ScalerGlobalSetIRQControl(ucGlobalIRQTemp);

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_NORMAL_MODE);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to M2PLL.
        ScalerMcuPwmClockSel(_M2PLL_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to external Xtal.
        ScalerMcuSarAdcClkSel(_EXT_XTAL_CLK);
#endif

#if(_MHL_SUPPORT == _ON)
        // Switch D0 MHL System Clk to M2PLL
        ScalerMHLCBUSSwitchClk(_IOSC_CLK);
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
        ScalerTypeCPowerClkSel(_IOSC_CLK);
#endif

        // Xtal CLK Select to external crystal clock.
        ScalerGlobalCrystalClkSel(_EXT_XTAL_CLK);

        // Modify debounce settings for Xtal clock.
        ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);

#if(_HW_IIC_SUPPORT == _ON)
#if((_LC_TANK_SUPPORT == _ON) && (_XTALESS_SUPPORT == _ON))
        // Modify Hardware IIC frequency divisor for internal OSC clock.
        ScalerMcuHwIICSetFreqDiv(_IOSC_CLK);
#else
        // Modify Hardware IIC frequency divisor for Xtal clock.
        ScalerMcuHwIICSetFreqDiv(_EXT_XTAL_CLK);
#endif
#endif

        // Modify 5us delay for Flash CLK = 24.3M
        ScalerMcu5usDelayCalc(_M2PLL_CLK);

        // Internal CLK Select to M2PLL.
        ScalerGlobalSystemClkSel(_M2PLL_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select Xtal
        ScalerIRHWModeClockSel(_EXT_XTAL_CLK);
#endif
    }
    else if(ucClockSel == _IOSC_CLK)
    {
        // Xtal CLK Select to INOSC
        ScalerGlobalCrystalClkSel(_IOSC_CLK);

        // Modify debounce settings for INOSC clock.
        ScalerMcuDdcDebounceSel(_IOSC_CLK);

#if(_HW_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for IOSC clock.
        ScalerMcuHwIICSetFreqDiv(_IOSC_CLK);
#endif

#if(_MHL_SUPPORT == _ON)
        // Switch D0 MHL System Clk to IOSC
        ScalerMHLCBUSSwitchClk(_IOSC_CLK);
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
        ScalerTypeCPowerClkSel(_IOSC_CLK);
#endif

        // Internal CLK Select to Internal Crystal.
        ScalerGlobalSystemClkSel(_IOSC_CLK);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to Xtal.
        ScalerMcuPwmClockSel(_IOSC_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to Internal Crystal.
        ScalerMcuSarAdcClkSel(_IOSC_CLK);
#endif

        // Set Mcu/Flash Clock to _IOSC_CLK
        ScalerMcuFlashClockGroupSetting(_IOSC_CLK);

        // Cache control by IC base
        ScalerMcuCacheControl(_CACHE_PS_SWITCH);

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_SAVING_MODE);

        // Modify 5us delay for Flash CLK = 7M
        ScalerMcu5usDelayCalc(_IOSC_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select IOSC
        ScalerIRHWModeClockSel(_IOSC_CLK);
#endif

        // Power down M2PLL.
        ScalerPLLM2PLLPower(_OFF);

        // Power down Xtal.
        ScalerPowerXtalPower(_OFF);
    }
    else
    {
        // Xtal CLK Select to External Xtal
        ScalerGlobalCrystalClkSel(_EXT_XTAL_CLK);

        // Modify debounce settings for External Xtal clock.
        ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);

#if(_HW_IIC_SUPPORT == _ON)
        // Modify Hardware IIC frequency divisor for External Xtal clock.
        ScalerMcuHwIICSetFreqDiv(_EXT_XTAL_CLK);
#endif

#if(_MHL_SUPPORT == _ON)
        // Switch D0 MHL System Clk to IOSC
        ScalerMHLCBUSSwitchClk(_IOSC_CLK);
#endif

#if((_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON))
        ScalerTypeCPowerClkSel(_IOSC_CLK);
#endif

        // Internal CLK Select to External Crystal.
        ScalerGlobalSystemClkSel(_EXT_XTAL_CLK);

#if(_PWM_FUNCTION_SUPPORT == _ON)
        // PWM clock select to Xtal.
        ScalerMcuPwmClockSel(_EXT_XTAL_CLK);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
        // ADC clock select to Internal Crystal.
        ScalerMcuSarAdcClkSel(_EXT_XTAL_CLK);
#endif

        // Set Mcu/Flash Clock to _IOSC_CLK
        ScalerMcuFlashClockGroupSetting(_EXT_XTAL_CLK);

        // Cache control by IC base
        ScalerMcuCacheControl(_CACHE_PS_SWITCH);

        // Set Timer Count
        ScalerTimerSetTimerCount(_TIMER_OPERATION_INITIAL_MODE);

        // Modify 5us delay for Flash CLK = 7M
        ScalerMcu5usDelayCalc(_EXT_XTAL_CLK);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
        // IRDA clock Select IOSC
        ScalerIRHWModeClockSel(_EXT_XTAL_CLK);
#endif
    }
}
//--------------------------------------------------
// Description  : Set Power Action for other layer
// Input Value  : ucAction    --> Power Action
// Output Value : None
//--------------------------------------------------
void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus)
{
    // When OFF to Fake OFF & DC Key ON in One Main Loop, Clr Fake OFF Flag
    if((GET_POWER_SWITCH_TO_FAKE_OFF() == _TRUE) && (enumPorStatus == _POWER_STATUS_NORMAL))
    {
        CLR_POWER_SWITCH_TO_FAKE_OFF();
    }

    SET_TARGET_POWER_STATUS(enumPorStatus);
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover The Data of HDCP In Gdi Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerLoadHDCPKey(void)
{
    BYTE ucI = 0;
    BYTE pucTemp[64];
    memset(pucTemp, 0, sizeof(pucTemp));

    ScalerSyncHdcpEnableDownLoadKey(_ENABLE);

    for(ucI = 0; ucI < 20; ucI++)
    {
        UserCommonInterfaceGetHDCPKey((ucI * 16), 16, pucTemp);
        ScalerSyncHdcpDownLoadKey(16, pucTemp);
    }

    UserCommonInterfaceGetHDCPKeyBKsv(0, 5, pucTemp);
    ScalerSyncHdcpDownLoadBKsv(0, 5, pucTemp);

#if(_HDCP_2_2_SUPPORT == _ON)

#if(_HDCP_2_2_TX_RSA3072_MODE == _ON)

    for(ucI = 0; ucI < 24; ucI++)
    {
        // Load HDCP 2.2 Key Certrx
        UserCommonInterfaceGetHdcp2Certrx((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_CERT_RX);

        UserCommonInterfaceGetHdcp2RSADkey((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_RSA_D_KEY);

        UserCommonInterfaceGetHdcp2RSARRModN((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_RSA_RRMODN_KEY);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        UserCommonInterfaceGetHdcp2KpubKm((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_KPUB_KM);
#endif
    }

    UserCommonInterfaceGetHdcp2RSANpinv(0, 4, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 4, pucTemp, _HDCP_2_2_RSA_N_PINV);

    UserCommonInterfaceGetHdcp2LCKey(0, 16, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 16, pucTemp, _HDCP_2_2_LC);

    for(ucI = 0; ucI < 5; ucI++)
    {
        UserCommonInterfaceGetHdcp2RSAKPriv(ucI * 64, 64, pucTemp);
        ScalerHdcp2RxPairingCalculate(pucTemp, ucI);
    }
    ScalerHdcp2RxPairingCalculate(pucTemp, 5);

#else   // #if(_HDCP_2_2_TX_RSA3072_MODE == _OFF)

    for(ucI = 0; ucI < 33; ucI++)
    {
        // Load HDCP 2.2 Key Certrx
        if(ucI < 32)
        {
            UserCommonInterfaceGetHdcp2Certrx((ucI * 16), 16, pucTemp);
            ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_CERT_RX);
        }
        else
        {
            UserCommonInterfaceGetHdcp2Certrx((ucI * 16), 10, pucTemp);
            ScalerHdcp2DownLoadCalculateKey((ucI * 16), 10, pucTemp, _HDCP_2_2_CERT_RX);
        }
    }

    for(ucI = 0; ucI < 8; ucI++)
    {
        // d key, Npinv, RRmodN, public key n
        UserCommonInterfaceGetHdcp2RSADkey((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_RSA_D_KEY);

        UserCommonInterfaceGetHdcp2RSARRModN((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_RSA_RRMODN_KEY);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        UserCommonInterfaceGetHdcp2KpubKm((ucI * 16), 16, pucTemp);
        ScalerHdcp2DownLoadCalculateKey((ucI * 16), 16, pucTemp, _HDCP_2_2_KPUB_KM);
#endif
    }

    UserCommonInterfaceGetHdcp2RSANpinv(0, 4, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 4, pucTemp, _HDCP_2_2_RSA_N_PINV);

    UserCommonInterfaceGetHdcp2LCKey(0, 16, pucTemp);
    ScalerHdcp2DownLoadCalculateKey(0, 16, pucTemp, _HDCP_2_2_LC);

    for(ucI = 0; ucI < 5; ucI++)
    {
        UserCommonInterfaceGetHdcp2RSAKPriv(ucI * 64, 64, pucTemp);
        ScalerHdcp2RxPairingCalculate(pucTemp, ucI);
    }
    ScalerHdcp2RxPairingCalculate(pucTemp, 5);
#endif
#endif

    ScalerSyncHdcpEnableDownLoadKey(_DISABLE);
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Recover The Data of HDCP for DPTX
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerLoadDPTxHDCPKey(void)
{
    BYTE ucI = 0;
    BYTE pucTemp[16];

    // Enable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadDPTxKey(_ENABLE);

    for(ucI = 0; ucI < 20; ucI++)
    {
        UserCommonInterfaceGetTxHDCPKey((ucI * 16), 16, pucTemp);
        ScalerSyncHdcpDownLoadDPTxAKey(16, pucTemp);
    }

    // Get Hdcp Key
    UserCommonInterfaceGetTxHDCPKeyAKsv(0, 5, &pucTemp[5]);

    // Write Hdcp Key To SDRAM
    ScalerSyncHdcpDownLoadDPTxAKsv(0, 5, &pucTemp[5]);

    // Disable HDCP Download Key Port
    ScalerSyncHdcpEnableDownLoadDPTxKey(_DISABLE);
}
#endif
#endif

//--------------------------------------------------
// Description  : Power Isolation Setting For all power isolation Module.
// Input Value  : enumSwitch    --> Power action description.
// Output Value : None
//--------------------------------------------------
void SysPowerIsolation(EnumPowerAction enumSwitch)
{
    BYTE ucIsolationAreaFlg = 0x00;

    // Power isolation control.
    ucIsolationAreaFlg = ScalerPowerIsolation(enumSwitch);

    if((ucIsolationAreaFlg & _BIT0) == _BIT0)
    {
        SET_POWER_ISO_A_FLG();
    }

    if((ucIsolationAreaFlg & _BIT1) == _BIT1)
    {
        SET_POWER_ISO_B_FLG();
    }

    if((ucIsolationAreaFlg & _BIT2) == _BIT2)
    {
        SET_POWER_ISO_C_FLG();
    }

    if((ucIsolationAreaFlg & _BIT3) == _BIT3)
    {
        SET_POWER_ISO_D_FLG();
    }

    if((ucIsolationAreaFlg & _BIT4) == _BIT4)
    {
        SET_POWER_ISO_E_FLG();
    }
}

//--------------------------------------------------
// Description  : Recover The Data of LUT/Latch/SRAM In Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerRecoverIsolationAreaData(void)
{
    if(GET_POWER_ISO_A_FLG() == _TRUE)
    {
        CLR_POWER_ISO_A_FLG();

        // Power A Group Data Recovery
        ScalerPowerRecoverAGroupIsolationData();
    }

    if(GET_POWER_ISO_B_FLG() == _TRUE)
    {
        CLR_POWER_ISO_B_FLG();

        // Power B Group Data Recovery
        ScalerPowerRecoverBGroupIsolationData();
    }

    if(GET_POWER_ISO_C_FLG() == _TRUE)
    {
        CLR_POWER_ISO_C_FLG();

#if((_DIGITAL_PORT_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
        SysPowerLoadDPTxHDCPKey();
#endif

        // Power C Group Data Recovery
        ScalerPowerRecoverCGroupIsolationData();
    }

    if(GET_POWER_ISO_D_FLG() == _TRUE)
    {
        CLR_POWER_ISO_D_FLG();

        // Power D Group Data Recovery
        ScalerPowerRecoverDGroupIsolationData();
    }

    if(GET_POWER_ISO_E_FLG() == _TRUE)
    {
        CLR_POWER_ISO_E_FLG();

        // Power E Group Data Recovery
        ScalerPowerRecoverEGroupIsolationData();
    }
}

//--------------------------------------------------
// Description  : Check Whther go to Fake Saving Mode
// Input Value  : None
// Output Value : _TRUE => Fake Saving
//--------------------------------------------------
bit SysPowerCheckFakeSaving(void)
{
    BYTE ucTemp = 0;

    DebugMessageMst("SysPower Check Fake Saving", 0x00);

    if(UserInterfaceGetFakePSStatus() == _USER_FORCE_FAKE_POWER_SAVING)
    {
        ucTemp = 0x01;
    }

    if(GET_MODE_STATE() == _MODE_STATUS_NOSUPPORT)
    {
        ucTemp = 0x01;
    }

#if(_DP_MST_SUPPORT == _ON)
    if(ScalerSyncDpFakePowerSavingCheck() == _TRUE)
    {
        ucTemp = 0x01;
    }
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(GET_AUDIO_PLAYING_ALONE() == _TRUE)
    {
        ucTemp = 0x01;
    }
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
    if((UserCommonPortControllerGetUsbPSStatus() == _USB3_PS_ENABLE) && (ScalerTypeCSearchCcAttach() == _TYPE_C_ATTACH))
    {
        ucTemp = 0x01;
    }
#endif

    if(ucTemp != 0x00)
    {
        if((GET_MODE_STATE() != _MODE_STATUS_NOSUPPORT) && (GET_MODE_STATE() != _MODE_STATUS_ACTIVE))
        {
            if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _TRUE)
            {
                SysSourceInfoReset();
            }
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Whether go to Fake Off Mode
// Input Value  : None
// Output Value : _TRUE => Fake Off
//--------------------------------------------------
bit SysPowerCheckFakeOff(void)
{
    if(UserInterfaceGetFakePowerOffStatus() == _USER_FORCE_FAKE_POWER_OFF)
    {
        return _TRUE;
    }

    // If Power Action Switch Normal to Fake OFF, Else Power Action Switch Fake Off to OFF
    if(GET_POWER_SWITCH_TO_FAKE_OFF() != _TRUE)
    {
#if(_DP_MST_SUPPORT == _ON)
        if(ScalerSyncDpFakePowerOffCheck(SysSourceGetInputPort()) == _TRUE)
        {
            ScalerTimerActiveTimerEvent(_POWER_FAKE_OFF_TO_OFF_TIMEOUT, _SYSTEM_TIMER_EVENT_POWER_FAKE_OFF_TO_OFF);

            return _TRUE;
        }
#endif

#if(_USB3_RETIMER_SUPPORT == _ON)
        if((UserCommonPortControllerGetUsbPDStatus() == _USB3_PD_ENABLE) && (ScalerTypeCSearchCcAttach() == _TYPE_C_ATTACH))
        {
            return _TRUE;
        }
#endif
    }
    else
    {
#if(_DP_MST_SUPPORT == _ON)
        if(GET_DP_RX_MST_DC_OFF_HPD_TOGGLE_HOLD() == _TRUE)
        {
            return _TRUE;
        }
        else
#endif
        {
#if(_USB3_RETIMER_SUPPORT == _ON)
            if((UserCommonPortControllerGetUsbPDStatus() == _USB3_PD_ENABLE) && (ScalerTypeCSearchCcAttach() == _TYPE_C_ATTACH))
            {
                return _TRUE;
            }
#endif
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Whther go to Power Normal Mode
// Input Value  : None
// Output Value : _TRUE => Power Normal
//--------------------------------------------------
bit SysPowerCheckNormal(void)
{
    return (!GET_POWER_SWITCH_TO_FAKE_OFF());
}

#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Fake Saving Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysPowerMHLPowerCutProc(void)
{
    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:

#if(_MHL_SUPPORT == _ON)
            if(((SysSourceGetInputPort() == _D2_INPUT_PORT) && (GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((SysSourceGetInputPort() == _D3_INPUT_PORT) && (GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((SysSourceGetInputPort() == _D4_INPUT_PORT) && (GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)) ||
               ((SysSourceGetInputPort() == _D5_INPUT_PORT) && (GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)))
            {
                // Vcck 1.1v Power On, Group D Analog Isolation Off
                ScalerPowerSetMHLNoPowerCut();
            }
            else
            {
                ScalerPowerClrMHLNoPowerCut();
            }

#endif

            break;

        case _SOURCE_SWITCH_AUTO_IN_GROUP:
        case _SOURCE_SWITCH_AUTO_WITHOUT_GROUP:

#if(_MHL_SUPPORT == _ON)
            if((GET_D2_TMDS_MODE() == _TMDS_MHL_MODE) || (GET_D3_TMDS_MODE() == _TMDS_MHL_MODE) ||
               (GET_D4_TMDS_MODE() == _TMDS_MHL_MODE) || (GET_D5_TMDS_MODE() == _TMDS_MHL_MODE))
            {
                // Vcck 1.1v Power On, Group D Analog Isolation Off
                ScalerPowerSetMHLNoPowerCut();
            }
            else
            {
                ScalerPowerClrMHLNoPowerCut();
            }
#endif

            break;

        default:

            break;
    }
}
#endif

