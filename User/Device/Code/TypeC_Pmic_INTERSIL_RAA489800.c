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
// ID Code      : TypeC_Pmic_INTERSIL_ISL95338.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"

#if(_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of PMIC ISL95338
//--------------------------------------------------
#define _RAA489800_SUBADDR_LENGTH               0x01
#define _RAA489800_SYS_CURRENT_LIMIT            0x14
#define _RAA489800_FRW_REGULATING_VOLTAGE       0x15
#define _RAA489800_CONTROL0                     0x39
#define _RAA489800_INFORMATION1                 0x3A
#define _RAA489800_CONTROL1                     0x3C
#define _RAA489800_CONTROL2                     0x3D
#define _RAA489800_FRW_INPUT_CURRENT            0x3F
#define _RAA489800_RVS_REGULATING_VOLTAGE       0x49
#define _RAA489800_RVS_OUTPUT_CURRENT           0x4A
#define _RAA489800_INPUT_VOLTAGE_LIMIT          0x4B
#define _RAA489800_CONTROL3                     0x4C
#define _RAA489800_INFORMATION2                 0x4D
#define _RAA489800_CONTROL4                     0x4E
#define _RAA489800_MANUFACTURER_ID              0xFE
#define _RAA489800_DEVICE_ID                    0xFF

//--------------------------------------------------
// Initial Setting
//--------------------------------------------------
#define _ADDR_14_SYS_CURRENT_LIMIT_LB           0xDC    // 1.5A
#define _ADDR_14_SYS_CURRENT_LIMIT_HB           0x05

#define _ADDR_15_FRW_REGULATING_VOLT_LB         0x08    // 5.004V
#define _ADDR_15_FRW_REGULATING_VOLT_HB         0x0D

#define _ADDR_3F_FRW_INPUT_CURRENT_LB           0x80    // 4.992A
#define _ADDR_3F_FRW_INPUT_CURRENT_HB           0x13

#define _ADDR_49_RVS_REGULATING_VOLTAGE_LB      0x08    // 5.004V
#define _ADDR_49_RVS_REGULATING_VOLTAGE_HB      0x0D

#define _ADDR_4A_RVS_OUTPUT_CURRENT_LB          0x00    // 0.512A
#define _ADDR_4A_RVS_OUTPUT_CURRENT_HB          0x02

#define _ADDR_4B_INPUT_VOLTAGE_LIMIT_LB         0x00    // 4.096A
#define _ADDR_4B_INPUT_VOLTAGE_LIMIT_HB         0x08

//Control0 Register 0x39
#define _ADDR_39_SysSideDischarge               0x00    // Disable
#define _ADDR_39_ADPSideDischarge               0x00    // Disable
#define _ADDR_39_VINRegulationLoop              0x00    // Enable input voltage regulation loop
#define _ADDR_39_FETShortTH                     0x00    // 400mV
#define _ADDR_39_RVSPhaseComparatorTH_1         0x00    // 0mV, BIT[7]
#define _ADDR_39_RVSPhaseComparatorTH_2         0x00    // 0mV, BIT[9:8]
#define _ADDR_39_FRWnRVSPhaseComparatorTH       0x00    // 0mV
#define _ADDR_39_FRWPhaseComparatorTH           0x00    // 0mV

//Control1 Register 0x3C
#define _ADDR_3C_ForceVDAV                      0x00    // Disable force 5.04V VDAC
#define _ADDR_3C_FRWnRVSOVEn                    0x00    // Enable OV
#define _ADDR_3C_SwitchingInFWDMode             0x00    // Enable switching
#define _ADDR_3C_FastREFMode                    0x00    // Disable
#define _ADDR_3C_BypassMode                     0x00    // Disable
#define _ADDR_3C_SysSideCurrentAmp              0x00    // Enable system side current amplifier
#define _ADDR_3C_OutputCurrentLimitAlert        0x00    // Alert# will be asserted if the contoller enter or exit output current limit mode.
#define _ADDR_3C_SwitchingFreq_1                0x00    // 1000khz, BIT[7]
#define _ADDR_3C_SwitchingFreq_2                0x00    // 1000khz, BIT[9:8]
#define _ADDR_3C_AudioFilter                    0x00    // Disable
#define _ADDR_3C_RVSModeFunction                0x00    // Disable Force Reverse mode function
#define _ADDR_3C_SkipAutozero                   0x00    // Autozero during restart
#define _ADDR_3C_SkipTrim                       0x00    // Read trim during restart
#define _ADDR_3C_SinkingCurrent                 0x00    // Sinking current during negative DAC transition enabled
#define _ADDR_3C_DiodeEmulationComparator       0x00    // Diode-emulation comparator enabled

//Control2 Register 0x3D
#define _ADDR_3D_FaultLatchOff                  0x00    // Controller latches off after WOC, UV, ADPOV or OTP fault
#define _ADDR_3D_WOCFault                       0x00    // Enable WOC
#define _ADDR_3D_FRWFastSwap                    0x00    // Disable forward fast swap
#define _ADDR_3D_RVSFastSwap                    0x00    // Disable reverse fast swap
#define _ADDR_3D_ALERTDuration_1                0x00    // 10ms, BIT[7:6]
#define _ADDR_3D_ALERTDuration_2                0x00    // 10ms, BIT[8]
#define _ADDR_3D_ALERTDebounce                  0x00    // 7us
#define _ADDR_3D_FRWRestartDebounce             0x00    // Debounce time is 1.3s
#define _ADDR_3D_FaultRestartDebounce           0x00    // Debounce time is 1.3s or 150ms, depends on bit<13> setting
#define _ADDR_3D_FaultRestartDebounceRVSEn      0x00    // Debounce time is 1.3s
#define _ADDR_3D_UVControl                      0x01    // Enable UV
#define _ADDR_3D_OVControl                      0x01    // Enable OV

//Control3 Register 0x4C
#define _ADDR_4C_PGOODSetting                   0x01    // PGOOD suppressed until VREF equals to VDAC
#define _ADDR_4C_BBDCMConductionTime            0x00    // Shorter conduction time to reduce ripple
#define _ADDR_4C_DigitalReset                   0x00    // Idle
#define _ADDR_4C_REFAmplifier                   0x00    // Enable REF amplifier
#define _ADDR_4C_INCurrentLimitLoop             0x00    // Enable input current limit loop
#define _ADDR_4C_CurrentLoopFBGain              0x00    // Gain x 1
#define _ADDR_4C_ForceOpMode                    0x00    // No effect
#define _ADDR_4C_FRWStartupDebounceTime         0x00    // Debounce time is 200us
#define _ADDR_4C_RVSStartupDebounceTime         0x00    // Debounce time is 200us
#define _ADDR_4C_ReReadPROGPinResistor          0x01    // Do not re-read PROG pin resistor

//Control4 Register 0x4E
#define _ADDR_4E_ALERTLatch                     0x01    // ALERT# signal auto-clear
#define _ADDR_4E_ALERTClear                     0x01    // Idle
#define _ADDR_4E_FRWSleepMode                   0x00    // if FWREN=1 then controller is enabled, if FWREN=0 controller is disabled
#define _ADDR_4E_RVSModeCurrentALERT            0x00    // Enable


//--------------------------------------------------
// Definitions of Pmic RAA489800 Control
//--------------------------------------------------
#define _PMIC_SOURCE                            1       // Forward mode
#define _PMIC_SINK                              0       // Reverse mode

//--------------------------------------------------
// Definitions of Pmic Voltage & Current Offsets
//--------------------------------------------------
#define _PMIC_OFFSET_VOLTAGE                    7       // Unit: +10mV
#define _PMIC_OFFSET_CURRENT                    16      // Unit: -10mA


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct // Sys Current Limit Register 0x14
{
    BYTE ucSysCurrentLimit_LB;
    BYTE ucSysCurrentLimit_HB;
}StructRAA489800SysCurrentLimitMap;

typedef struct // FRW Regulating Voltage Register 0x15
{
    BYTE ucFRWRegulatingVolt_LB;
    BYTE ucFRWRegulatingVolt_HB;
}StructRAA489800FRWRegulatingVoltMap;

typedef struct // FRW Input Current Register 0x3F
{
    BYTE ucFRWInputCurrent_LB;
    BYTE ucFRWInputCurrent_HB;
}StructRAA489800FRWInputCurrentMap;


typedef struct // RVS Regulating Voltage Register 0x49
{
    BYTE ucRVSRegulatingVolt_LB;
    BYTE ucRVSRegulatingVolt_HB;
}StructRAA489800RVSRegulatingVoltMap;

typedef struct // RVS Onput Current Register 0x4A
{
    BYTE ucRVSOutputCurrent_LB;
    BYTE ucRVSOutputCurrent_HB;
}StructRAA489800RVSOutputCurrentMap;

typedef struct // Input Voltage Limit Register 0x4B
{
    BYTE ucInputVoltLimit_LB;
    BYTE ucInputVoltLimit_HB;
}StructRAA489800InputVoltLimitMap;

typedef struct // Control0 Register 0x39
{
    BYTE b1CR0SysSideDischarge : 1;         // BIT[0]:Enable or disable system side charger function
    BYTE b1CR0ADPSideDischarge : 1;         // BIT[1]:Enable or disable ADP side charger function
    BYTE b1CR0VINRegulationLoop : 1;        // BIT[2]:Disable or enable the input voltage regulation loop.
    BYTE b2CR0Reserved : 2;                 // BIT[4:3]:Not used
    BYTE b2CR0FETShortTH : 2;               // BIT[6:5]:Configure the high-side FET short detection PHASE node voltage threshold
    BYTE b1CR0RVSPhaseComparatorTH_1 : 1;   // BIT[7] of BIT[9:7]:Adjust phase comparator threshold offset for reverse buck and buck-boost

    BYTE b2CR0RVSPhaseComparatorTH_2 : 2;   // BIT[9:8] of BIT[9:7]:Adjust phase comparator threshold offset for reverse buck and buck-boost
    BYTE b3CR0FRWnRVSPhaseComparatorTH : 3; // BIT[12:10]:Adjust phase comparator threshold offset for forward and reverse bo
    BYTE b3CR0FRWPhaseComparatorTH : 3;     // BIT[15:13]:Adjust phase comparator threshold offset for forward buck and buck-boost
} StructRAA489800CR0RegisterMap;

typedef struct // Control1 Register 0x3C
{
    BYTE b1CR1ForceVDAV : 1;                // BIT[0]:Enable or disable force 5.04VDAC in Forward and Reverse mode.
    BYTE b1CR1FRWnRVSOVEn : 1;              // BIT[1]:Enable or disable OV fault when VDAC slew rate down in Forward and Reverse mode
    BYTE b1CR1SwitchingInFWDMode : 1;       // BIT[2]:Enable or disable the buck-boost switching VOUT output.
    BYTE b1CR1FastREFMode : 1;              // BIT[3]:Enable or disable the fast REF mode
    BYTE b1CR1BypassMode : 1;               // BIT[4]:Enable or disable the Bypass mode.
    BYTE b1CR1SysSideCurrentAmp : 1;        // BIT[5]:Enable or disable the system side current amplifier when in FWD mode without ADP.
    BYTE b1CR1OutputCurrentLimitAlert : 1;  // BIT[6]:Configures enter or exit output Current limit mode, Alert# will be asserted or not.
    BYTE b1CR1SwitchingFreq_1 : 1;          // BIT[7] of BIT[9:7]:Configures the switching frequency.

    BYTE b2CR1SwitchingFreq_2 : 2;          // BIT[9:8] of BIT[9:7]:Configures the switching frequency.
    BYTE b1CR1AudioFilter : 1;              // BIT[10]:Enable or disable the audio filter function. No audio filter function in Buck-Boost mode.
    BYTE b1CR1RVSModeFunction : 1;          // BIT[11]:Enable or disable Force Reverse mode function.
    BYTE b1CR1SkipAutozero : 1;             // BIT[12]:Enable or disable autozero during restart. Make sure to program this bit when PGOOD is high.
    BYTE b1CR1SkipTrim : 1;                 // BIT[13]:Enable or disable trim read during restart. Make sure to program this bit when PGOOD is high.
    BYTE b1CR1SinkingCurrent : 1;           // BIT[14]:Enable or disable sinking current during negative DAC transition.
    BYTE b1CR1DiodeEmulationComparator : 1; // BIT[15]:Enable or disable diode-emulation comparator
}StructRAA489800CR1RegisterMap;

typedef struct // Control2 Register 0x3D
{
    BYTE b1CR2FaultLatchOff : 1;            // BIT[0]:Disable fault latch off fucntion for WOC, UV, ADPOV or OTP fault event
    BYTE b1CR2WOCFault : 1;                 // BIT[1]:Enable and disable WOC fault.
    BYTE b1CR2Reserved1 : 1;                // BIT[2]:Not used
    BYTE b1CR2FRWFastSwap : 1;              // BIT[3]:Configure forward fast swap.
    BYTE b1CR2RVSFastSwap : 1;              // BIT[4]:Configure reverse fast swap.
    BYTE b1CR2Reserved2 : 1;                // BIT[5]:Not used
    BYTE b2CR2ALERTDuration_1 : 2;          // BIT[7:6] of BIT[8:6]:Configure the minimum duration of ALERT# signal when it is asserted

    BYTE b1CR2ALERTDuration_2 : 1;          // BIT[8] of BIT[8:6]:Configure the minimum duration of ALERT# signal when it is asserted
    BYTE b2CR2ALERTDebounce : 2;            // BIT[10:9]:Configure the ALERT# debounce time before its assertion for ADPsideALERT# and SystemsideALERT#
    BYTE b1CR2FRWRestartDebounce : 1;       // BIT[11]:Configure fault restart debounce for forward enable.
    BYTE b1CR2FaultRestartDebounce : 1;     // BIT[12]:Configure fast fault restart debounce.
    BYTE b1CR2FaultRestartDebounceRVSEn : 1;// BIT[13]:Configure fault restart debounce for reverse enable
    BYTE b1CR2UVControl : 1;                // BIT[14]:Enable or disable UV
    BYTE b1CR2OVControl : 1;                // BIT[15]:Enable or disable OV
} StructRAA489800CR2RegisterMap;

typedef struct // Control3 Register 0x4C
{
    BYTE b1CR3PGOODSetting : 1;             // BIT[0]:Configure PGOOD assert condition
    BYTE b1CR3BBDCMConductionTime : 1;      // BIT[1]:Configure the conduction time in Buck-Boost DCM.
    BYTE b1CR3DigitalReset : 1;             // BIT[2]:Reset all SMBus register values to POR default value and restarts switching.
    BYTE b1CR3REFAmplifier : 1;             // BIT[3]:Disable REF amplifier.
    BYTE b1CR3Reserved1 : 1;                // BIT[4]:Not used
    BYTE b1CR3INCurrentLimitLoop : 1;       // BIT[5]:Disable input current limit loop.
    BYTE b1CR3CurrentLoopFBGain : 1;        // BIT[6]:Configure current loop feedback gain for high current.
    BYTE b1CR3Reserved2 : 1;                // BIT[7]:Not used

    BYTE b3CR3ForceOpMode : 3;              // BIT[10:8]:Enable or disable Force Operating mode.
    BYTE b1CR3FRWStartupDebounceTime : 1;   // BIT[11]:Configure startup debounce time for forward mode
    BYTE b1CR3RVSStartupDebounceTime : 1;   // BIT[12]:Configure startup debounce time for reverse mode
    BYTE b1CR3Reserved3 : 1;                // BIT[13]:Not used
    BYTE b1CR3Reserved4 : 1;                // BIT[14]:Not used
    BYTE b1CR3ReReadPROGPinResistor : 1;    // BIT[15]:Re-read PROG pin resistor or not before switching.
} StructRAA489800CR3RegisterMap;

typedef struct // Control4 Register 0x4E
{
    BYTE b1CR4ALERTLatch : 1;               // BIT[0]:Manually resets ALERT#.
    BYTE b1CR4ALERTClear : 1;               // BIT[1]:Clear ALERT#.
    BYTE b4CR4Reserved1 : 4;                // BIT[5:2]:Not used
    BYTE b1CR4FRWSleepMode : 1;             // BIT[6]:Enable or disable Chip Sleep mode in Forward mode regardless of ADP voltage
    BYTE b1CR4RVSModeCurrentALERT : 1;      // BIT[7]:Enable or disable trigger ALERT# with current in Reverse mode

    BYTE b8CR4Reserved2 : 8;                // BIT[15:8]:Not used
} StructRAA489800CR4RegisterMap;

typedef struct
{
    BYTE b7INFO1Reserved : 7;               // BIT[6:0]: Not used

    BYTE b1INFO1CCModeChange : 1;           // BIT[7]: Controller has entered/exited CC mode
    BYTE b1INFO1ADPsideOV : 1;              // BIT[8]: Adapter side OV fault
    BYTE b1INFO1OTP : 1;                    // BIT[9]: OTP fault
    BYTE b1INFO1SYSsideUV : 1;              // BIT[10]: Sys output UV fault
    BYTE b1INFO1SYSsideOV : 1;              // BIT[11]: Sys output OV fault
    BYTE b1INFO1WOCP : 1;                   // BIT[12]: WOC fault
    BYTE b2INFO1ActiveControlLoop : 2;      // BIT[14:13]: indicator for active control loop
    BYTE b1INFO1ActiveReferenceCircuit : 1; // BIT[15]: indicator for int reference circuit
} StructRAA489800Info1RegisterMap;

typedef struct
{
    BYTE b5INFO2PROGResistor : 5;           // BIT[4:0]:Program Resister read out
    BYTE b3INFO2OperationMode : 3;          // BIT[7:5]:Indicates the RAA489800 operation mode

    BYTE b4INFO2StateMachineStatus : 4;     // BIT[11:8]:Indicates the RAA489800 state machine status.
    BYTE b2INFO2Reserved : 2;               // BIT[13:12]:Not used
    BYTE b1INFO2FWRSwitchEn : 1;            // BIT[14]:Indicates forward switching enable
    BYTE b1INFO2Reserved : 1;               // BIT[15]:Not used
} StructRAA489800Info2RegisterMap;

//****************************************************************************
// CODE TABLES
//****************************************************************************
StructRAA489800SysCurrentLimitMap code g_stPmicSysCurrentLimitInitData =
{
    _ADDR_14_SYS_CURRENT_LIMIT_LB,
    _ADDR_14_SYS_CURRENT_LIMIT_HB,
};

StructRAA489800FRWRegulatingVoltMap code g_stPmicFRWRegulatingVoltInitData =
{
    _ADDR_15_FRW_REGULATING_VOLT_LB,
    _ADDR_15_FRW_REGULATING_VOLT_HB,
};

StructRAA489800FRWInputCurrentMap code g_stPmicFRWInputCurrentInitData =
{
    _ADDR_3F_FRW_INPUT_CURRENT_LB,
    _ADDR_3F_FRW_INPUT_CURRENT_HB,
};

StructRAA489800RVSRegulatingVoltMap code g_stPmicRVSRegulatingVoltInitData =
{
    _ADDR_49_RVS_REGULATING_VOLTAGE_LB,
    _ADDR_49_RVS_REGULATING_VOLTAGE_HB,
};

StructRAA489800RVSOutputCurrentMap code g_stPmicRVSOutputCurrentInitData =
{
    _ADDR_4A_RVS_OUTPUT_CURRENT_LB,
    _ADDR_4A_RVS_OUTPUT_CURRENT_HB,
};

StructRAA489800InputVoltLimitMap code g_stPmicInputVoltLimitInitData =
{
    _ADDR_4B_INPUT_VOLTAGE_LIMIT_LB,
    _ADDR_4B_INPUT_VOLTAGE_LIMIT_HB,
};

StructRAA489800CR0RegisterMap code g_stPmicCR0InitialData =
{
    _ADDR_39_SysSideDischarge,              // Disable
    _ADDR_39_ADPSideDischarge,              // Disable
    _ADDR_39_VINRegulationLoop,             // Enable input voltage regulation loop
    0x00,                                   // Reserved
    _ADDR_39_FETShortTH,                    // 400mV
    _ADDR_39_RVSPhaseComparatorTH_1,        // 0mV

    _ADDR_39_RVSPhaseComparatorTH_2,        // 0mV
    _ADDR_39_FRWnRVSPhaseComparatorTH,      // 0mV
    _ADDR_39_FRWPhaseComparatorTH,          // 0mV
};

StructRAA489800CR1RegisterMap code g_stPmicCR1InitialData =
{
    _ADDR_3C_ForceVDAV,                     // Disable force 5.04V VDAC
    _ADDR_3C_FRWnRVSOVEn,                   // Enable OV
    _ADDR_3C_SwitchingInFWDMode,            // Enable switching
    _ADDR_3C_FastREFMode,                   // Disable
    _ADDR_3C_BypassMode,                    // Disable
    _ADDR_3C_SysSideCurrentAmp,             // Enable system side current amplifier
    _ADDR_3C_OutputCurrentLimitAlert,       // Alert# will be asserted
    _ADDR_3C_SwitchingFreq_1,               // 1000khz

    _ADDR_3C_SwitchingFreq_2,               // 1000khz
    _ADDR_3C_AudioFilter,                   // Disable
    _ADDR_3C_RVSModeFunction,               // Disable Force Reverse mode function
    _ADDR_3C_SkipAutozero,                  // Autozero during restart
    _ADDR_3C_SkipTrim,                      // Read trim during restart
    _ADDR_3C_SinkingCurrent,                // Sinking current during negative DAC transition enabled
    _ADDR_3C_DiodeEmulationComparator,      // Diode-emulation comparator enabled
};

StructRAA489800CR2RegisterMap code g_stPmicCR2InitialData =
{
    _ADDR_3D_FaultLatchOff,                 // Controller latches off after WOC, UV, ADPOV or OTP fault
    _ADDR_3D_WOCFault,                      // Enable WOC
    0x00,                                   // Reserved
    _ADDR_3D_FRWFastSwap,                   // Disable forward fast swap
    _ADDR_3D_RVSFastSwap,                   // Disable reverse fast swap
    0x00,                                   // Reserved
    _ADDR_3D_ALERTDuration_1,               // 10ms

    _ADDR_3D_ALERTDuration_2,               // 10ms
    _ADDR_3D_ALERTDebounce,                 // 7us
    _ADDR_3D_FRWRestartDebounce,            // Debounce time is 1.3s
    _ADDR_3D_FaultRestartDebounce,          // Debounce time is 1.3s or 150ms, depends on bit<13> setting
    _ADDR_3D_FaultRestartDebounceRVSEn,     // Debounce time is 1.3s
    _ADDR_3D_UVControl,                     // Enable UV
    _ADDR_3D_OVControl,                     // Enable OV

};

StructRAA489800CR3RegisterMap code g_stPmicCR3InitialData =
{
    _ADDR_4C_PGOODSetting,                  // PGGOD assert condition
    _ADDR_4C_BBDCMConductionTime,           // Shorter conduction time to reduce ripple
    _ADDR_4C_DigitalReset,                  // Idle
    _ADDR_4C_REFAmplifier,                  // Enable REF amplifier
    0x00,                                   // Reserved
    _ADDR_4C_INCurrentLimitLoop,            // Enable input current limit loop
    _ADDR_4C_CurrentLoopFBGain,             // Gain x 1
    0x00,                                   // Reserved

    _ADDR_4C_ForceOpMode,                   // No effect
    _ADDR_4C_FRWStartupDebounceTime,        // Debounce time is 200us
    _ADDR_4C_RVSStartupDebounceTime,        // Debounce time is 200us
    0x00,                                   // Reserved
    0x00,                                   // Reserved
    _ADDR_4C_ReReadPROGPinResistor,         // Re-read PROG pin resistor
};

StructRAA489800CR4RegisterMap code g_stPmicCR4InitialData =
{
    _ADDR_4E_ALERTLatch,                    // ALERT# signal auto-clear
    _ADDR_4E_ALERTClear,                    // Idle
    0x00,                                   // Reserved
    _ADDR_4E_FRWSleepMode,                  // if FWREN=1 then controller is enabled, if FWREN=0 controller is disabled
    _ADDR_4E_RVSModeCurrentALERT,           // Enable

    0x00,                                   // Reserved
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructRAA489800SysCurrentLimitMap g_stPMICSysCurrentLimit;
StructRAA489800FRWRegulatingVoltMap g_stPMICFRWRegulatingVolt;
StructRAA489800FRWInputCurrentMap g_stFRWInputCurrentData;
StructRAA489800RVSRegulatingVoltMap g_stRVSRegulatingVolt;
StructRAA489800RVSOutputCurrentMap g_stRVSOutputCurrent;
StructRAA489800InputVoltLimitMap g_stInputVoltLimit;

StructRAA489800CR0RegisterMap g_stPMICCR0Data;
StructRAA489800CR1RegisterMap g_stPMICCR1Data;
StructRAA489800CR2RegisterMap g_stPMICCR2Data;
StructRAA489800CR3RegisterMap g_stPMICCR3Data;
StructRAA489800CR4RegisterMap g_stPMICCR4Data;
StructRAA489800Info1RegisterMap g_stPMICINFO1Data;
StructRAA489800Info2RegisterMap g_stPMICINFO2Data;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ExternalDeviceInterfaceTypeCPmicACOnInitial(void);
void ExternalDeviceInterfaceTypeCPmicUnattachReset(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(void);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge(EnumTypeCPmicDischarge enumEn);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPmicDischarge enumEn);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPmicDischarge enumEn);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection);
#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType);
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType);
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(void);
#endif
#if(_TYPE_C_PMIC_DEBUG == _ON)
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(void);
#endif
#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
WORD ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(void);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : PMIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicACOnInitial(void)
{
    // Set PMIC Data initial value
    // CR0 default value
    g_stPMICCR0Data = g_stPmicCR0InitialData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR0Data)) == _SUCCESS)
    {
        DebugMessageTypeC("Write CR0 Success", 0x00);
    }
    else
    {
        DebugMessageTypeC("Write CR0 Fail", 0x00);
        return;
    }

    // CR1 default value
    g_stPMICCR1Data = g_stPmicCR1InitialData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL1, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR1Data)) == _SUCCESS)
    {
        DebugMessageTypeC("Write CR1 Success", 0x00);
    }
    else
    {
        DebugMessageTypeC("Write CR1 Fail", 0x00);
        return;
    }

    // CR2 default value
    g_stPMICCR2Data = g_stPmicCR2InitialData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL2, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR2Data)) == _SUCCESS)
    {
        DebugMessageTypeC("Write CR2 Success", 0x00);
    }
    else
    {
        DebugMessageTypeC("Write CR2 Fail", 0x00);
        return;
    }

    // CR3 default value
    g_stPMICCR3Data = g_stPmicCR3InitialData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL3, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR3Data)) == _SUCCESS)
    {
        DebugMessageTypeC("Write CR3 Success", 0x00);
    }
    else
    {
        DebugMessageTypeC("Write CR3 Fail", 0x00);
        return;
    }

    // CR4 default value
    g_stPMICCR4Data = g_stPmicCR4InitialData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL4, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR4Data)) == _SUCCESS)
    {
        DebugMessageTypeC("Write CR4 Success", 0x00);
    }
    else
    {
        DebugMessageTypeC("Write CR4 Fail", 0x00);
        return;
    }

    PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_ON);

    // 0x14: 1.5A
    g_stPMICSysCurrentLimit = g_stPmicSysCurrentLimitInitData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICSysCurrentLimit)) == _SUCCESS)
    {
        DebugMessageTypeC("Write Current Limit LB", g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB);
        DebugMessageTypeC("Write Current Limit HB", g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB);
    }
    else
    {
        DebugMessageTypeC("Write Current Limit Fail", 0x00);
        return;
    }

    // 0x15: 5.004V
    g_stPMICFRWRegulatingVolt = g_stPmicFRWRegulatingVoltInitData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICFRWRegulatingVolt)) == _SUCCESS)
    {
        DebugMessageTypeC("Write FWR Regualting Volt LB", g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB);
        DebugMessageTypeC("Write FWR Regualting Volt HB", g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB);
    }
    else
    {
        DebugMessageTypeC("Write FWR Regualting Volt Fail", 0x00);
        return;
    }

    PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_OFF);

    // 0x49:5.004V
    g_stRVSRegulatingVolt = g_stPmicRVSRegulatingVoltInitData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_RVS_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stRVSRegulatingVolt)) == _SUCCESS)
    {
        DebugMessageTypeC("Write RVS REGULATING VOLTAGE LB", g_stRVSRegulatingVolt.ucRVSRegulatingVolt_LB);
        DebugMessageTypeC("Write RVS REGULATING VOLTAGE HB", g_stRVSRegulatingVolt.ucRVSRegulatingVolt_HB);
    }
    else
    {
        DebugMessageTypeC("Write RVS REGULATING VOLTAGE Fail", 0x00);
        return;
    }

    // 0x4A:0.512A
    g_stRVSOutputCurrent = g_stPmicRVSOutputCurrentInitData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_RVS_OUTPUT_CURRENT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stRVSOutputCurrent)) == _SUCCESS)
    {
        DebugMessageTypeC("Write RVS Output Current LB", g_stRVSOutputCurrent.ucRVSOutputCurrent_LB);
        DebugMessageTypeC("Write RVS Output Current HB", g_stRVSOutputCurrent.ucRVSOutputCurrent_HB);
    }
    else
    {
        DebugMessageTypeC("Write RVS Output Current Fail", 0x00);
        return;
    }

    // 0x4B:4.096V
    g_stInputVoltLimit = g_stPmicInputVoltLimitInitData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_INPUT_VOLTAGE_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stInputVoltLimit)) == _SUCCESS)
    {
        DebugMessageTypeC("Write Input Voltage Limit LB", g_stInputVoltLimit.ucInputVoltLimit_LB);
        DebugMessageTypeC("Write Input Voltage Limit HB", g_stInputVoltLimit.ucInputVoltLimit_HB);
    }
    else
    {
        DebugMessageTypeC("Write Input Voltage Limit Fail", 0x00);
        return;
    }

    // 0x3F: 5A
    // Must set at the final
    g_stFRWInputCurrentData = g_stPmicFRWInputCurrentInitData;
    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_FRW_INPUT_CURRENT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stFRWInputCurrentData)) == _SUCCESS)
    {
        DebugMessageTypeC("Write FWR Input Current LB", g_stFRWInputCurrentData.ucFRWInputCurrent_LB);
        DebugMessageTypeC("Write FWR Input Current HB", g_stFRWInputCurrentData.ucFRWInputCurrent_HB);
    }
    else
    {
        DebugMessageTypeC("Write FWR Regualting Volt Fail", 0x00);
        return;
    }
}

//--------------------------------------------------
// Description  : PMIC Reset Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicUnattachReset(void)
{
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    BYTE pucTempData[2];
    WORD usTemp = 0;

    if(enumPowerDirection == _PMIC_SOURCE)
    {
        // Enable FWREN GPIO
        PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_ON);

        // Maximum Voltage Judgment
        if((usVoltage > 2100) || (usVoltage < 300))   // 3V ~ 21V
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Voltage Offset Compensation
        usVoltage = ((usVoltage + _PMIC_OFFSET_VOLTAGE) > 2100 ? 2100 : (usVoltage + _PMIC_OFFSET_VOLTAGE));

        // Set VOUT Voltage
        usTemp = ((usVoltage * 10) + 6) / 12;   // Round off
        usTemp = usTemp << 3;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB != pucTempData[0]) ||
           (g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB != pucTempData[1]))
        {
            g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB = pucTempData[0];
            g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB = pucTempData[1];

            if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICFRWRegulatingVolt)) == _FAIL)
            {
                DebugMessageTypeC("Write_FRW_REGULATING_VOLTAGE Fail", 0x00);
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }

            DebugMessageTypeC("usVoltage_LB", g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB);
            DebugMessageTypeC("usVoltage_HB", g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB);
        }


        // Maximum Current Judgment
        if(usCurrent > 1200)    // 12A
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Current Offset Compensation
        usCurrent = (usCurrent >= _PMIC_OFFSET_CURRENT ? (usCurrent - _PMIC_OFFSET_CURRENT) : 0);

        // Set VBUS Current Limit
        usTemp = ((usCurrent * 10) + 2) / 4;        // Round off
        usTemp = usTemp << 2;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB != pucTempData[0]) ||
           (g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB != pucTempData[1]))
        {
            g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB = pucTempData[0];
            g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB = pucTempData[1];

            if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICSysCurrentLimit)) == _FAIL)
            {
                DebugMessageTypeC("Write_SYS_CURRENT_LIMIT Fail", 0x00);
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }

            DebugMessageTypeC("usCurrent_LB", g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB);
            DebugMessageTypeC("usCurrent_HB", g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB);
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff(void)
{
    // Clear Voltage & Current Register
    g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB = 0;
    g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB = 0;
    g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB = 0;
    g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB = 0;

    // Disable FWREN GPIO
    PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_OFF);

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 1
{
    BYTE pucTempData[2];
    WORD usTemp = 0;

    if(enumPowerDirection == _PMIC_SOURCE)
    {
        // Enable FWREN GPIO
        PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_ON);

        // Maximum Voltage Judgment
        if((usVoltage > 2100) || (usVoltage < 300))   // 3V ~ 21V
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Voltage Offset Compensation
        usVoltage = ((usVoltage + _PMIC_OFFSET_VOLTAGE) > 2100 ? 2100 : (usVoltage + _PMIC_OFFSET_VOLTAGE));

        // Set VOUT Voltage
        usTemp = ((usVoltage * 10) + 6) / 12;   // Round off
        usTemp = usTemp << 3;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB != pucTempData[0]) ||
           (g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB != pucTempData[1]))
        {
            g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB = pucTempData[0];
            g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB = pucTempData[1];

            if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICFRWRegulatingVolt)) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }


        // Maximum Current Judgment
        if(usCurrent > 1200)    // 12A
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Current Offset Compensation
        usCurrent = (usCurrent >= _PMIC_OFFSET_CURRENT ? (usCurrent - _PMIC_OFFSET_CURRENT) : 0);

        // Set VBUS Current Limit
        usTemp = ((usCurrent * 10) + 2) / 4;        // Round off
        usTemp = usTemp << 2;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB != pucTempData[0]) ||
           (g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB != pucTempData[1]))
        {
            g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB = pucTempData[0];
            g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB = pucTempData[1];

            if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICSysCurrentLimit)) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(void) using 1
{
    // Clear Voltage & Current Register
    g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB = 0;
    g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB = 0;
    g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB = 0;
    g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB = 0;

    // Disable FWREN GPIO
    PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_OFF);

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Control PMIC to Directed Voltage
// Input Value  : enumPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV) / usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent) using 3
{
    BYTE pucTempData[2];
    WORD usTemp = 0;

    if(enumPowerDirection == _PMIC_SOURCE)
    {
        // Enable FWREN GPIO
        PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_ON);

        // Maximum Voltage Judgment
        if((usVoltage > 2100) || (usVoltage < 300))   // 3V ~ 21V
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Voltage Offset Compensation
        usVoltage = ((usVoltage + _PMIC_OFFSET_VOLTAGE) > 2100 ? 2100 : (usVoltage + _PMIC_OFFSET_VOLTAGE));

        // Set VOUT Voltage
        usTemp = ((usVoltage * 10) + 6) / 12;       // Round off
        usTemp = usTemp << 3;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB != pucTempData[0]) ||
           (g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB != pucTempData[1]))
        {
            g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB = pucTempData[0];
            g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB = pucTempData[1];

            if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICFRWRegulatingVolt)) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }


        // Maximum Current Judgment
        if(usCurrent > 1200)    // 12A
        {
            return _TYPE_C_PMIC_CONTROL_FAIL;
        }

        // Current Offset Compensation
        usCurrent = (usCurrent >= _PMIC_OFFSET_CURRENT ? (usCurrent - _PMIC_OFFSET_CURRENT) : 0);

        // Set VBUS Current Limit
        usTemp = ((usCurrent * 10) + 2) / 4;        // Round off
        usTemp = usTemp << 2;
        pucTempData[0] = (usTemp & 0x00FF);
        pucTempData[1] = (usTemp & 0xFF00) >> 8;

        if((g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB != pucTempData[0]) ||
           (g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB != pucTempData[1]))
        {
            g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB = pucTempData[0];
            g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB = pucTempData[1];

            if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICSysCurrentLimit)) == _FAIL)
            {
                return _TYPE_C_PMIC_CONTROL_FAIL;
            }
        }
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : Turn off PMIC
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(void) using 3
{
    // Clear Voltage & Current Register
    g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_LB = 0;
    g_stPMICFRWRegulatingVolt.ucFRWRegulatingVolt_HB = 0;
    g_stPMICSysCurrentLimit.ucSysCurrentLimit_LB = 0;
    g_stPMICSysCurrentLimit.ucSysCurrentLimit_HB = 0;

    // Disable FWREN GPIO
    PCB_PMIC_FRWEN_CONTROL(_FRWEN_CONTROL_OFF);

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge(EnumTypeCPmicDischarge enumEn)
{
    // Set PMIC VBUS Sys Discharge status
    g_stPMICCR0Data.b1CR0SysSideDischarge = enumEn;

    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_ON);
    }
    else
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_OFF);
    }

    if(ScalerTypeCPmicIICWrite(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR0Data)) == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}


//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPmicDischarge enumEn) using 1
{
    // Set PMIC VBUS Sys Discharge status
    g_stPMICCR0Data.b1CR0SysSideDischarge = enumEn;

    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_ON);
    }
    else
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_OFF);
    }

    // Disable Pmic VBUS Discharge
    if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR0Data)) == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}

//--------------------------------------------------
// Description  : PMIC VBUS Discharge Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPmicDischarge enumEn) using 3
{
    // Set PMIC VBUS Sys Discharge status
    g_stPMICCR0Data.b1CR0SysSideDischarge = enumEn;

    if(enumEn == _TYPE_C_PMIC_DISCHARGE_ENABLE)
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_ON);
    }
    else
    {
        PCB_VBUS_DISCHARGE_CONTROL(_VBUS_DISCHARGE_OFF);
    }

    if(ScalerTypeCPmicIICWrite_WDINT(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL0, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR0Data)) == _SUCCESS)
    {
        return _TYPE_C_PMIC_CONTROL_SUCCESS;
    }
    else
    {
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
        }
    }
    else
    {
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection) using 1
{
    if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
        }
    }
    else
    {
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Switch Control
// Input Value  : enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection) using 3
{
    if(enumSwitchControl == _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE)
    {
        if(enumPowerDirection == _TYPE_C_PMIC_DIRECTION_SRC)
        {
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_ON);
        }
        else
        {
            PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
            PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_ON);
        }
    }
    else
    {
        PCB_PMIC_VBUS_SOURCE_CONTROL(_VBUS_SOURCE_SWITCH_OFF);
        PCB_PMIC_VBUS_SINK_CONTROL(_VBUS_SINK_SWITCH_OFF);
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

#if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType)
{
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType) using 1
{
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Output Mode Setting
// Input Value  : enumOutputMode : Output Mode (Fixed Voltage/PPS)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(EnumTypeCPmicDirection enumPowerDirection, EnumPDPdoType enumOutputPdoType) using 3
{
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}

//--------------------------------------------------
// Description  : PMIC Read Output Status
// Input Value  : None
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(void) using 1
{
    BYTE pucTempData[2] = {0};

    if(ScalerTypeCPmicIICRead_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_INFORMATION1, _RAA489800_SUBADDR_LENGTH, 2, pucTempData) == _SUCCESS)
    {
        // Clear ALERT#
        g_stPMICCR4Data.b1CR4ALERTClear = 1;
        if(ScalerTypeCPmicIICWrite_EXINT0(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_CONTROL4, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICCR4Data)) == _FAIL)
        {
            return _TYPE_C_PMIC_NONE_MODE_OPERATION;
        }

        // Return PMIC Operating Mode
        if((pucTempData[1] & 0x60) == 0x00)
        {
            return _TYPE_C_PMIC_CV_MODE_OPERATION;
        }
        else if((pucTempData[1] & 0x60) == 0x20)
        {
            return _TYPE_C_PMIC_CC_MODE_OPERATION;
        }
        else
        {
            return _TYPE_C_PMIC_TRANSITION_MODE;
        }
    }

    return _TYPE_C_PMIC_NONE_MODE_OPERATION;
}
#endif // End of #if(_TYPE_C_EMB_PD3_PPS_SUPPORT == _ON)

#if(_TYPE_C_PMIC_DEBUG == _ON)
//--------------------------------------------------
// Description  : PMIC Status
// Input Value  : None
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(void)
{
    BYTE pucTempData[2];

    if(ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_DEVICE_ID, _RAA489800_SUBADDR_LENGTH, 1, pucTempData) == _SUCCESS)
    {
        DebugMessageTypeC("5.Pmic:DEVICE_ID", pucTempData[0]);
    }
    else
    {
        DebugMessageTypeC("5.Pmic:Read DEVICE_ID Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_MANUFACTURER_ID, _RAA489800_SUBADDR_LENGTH, 1, pucTempData) == _SUCCESS)
    {
        DebugMessageTypeC("5.Pmic:MANUFACTURER_ID", pucTempData[0]);
    }
    else
    {
        DebugMessageTypeC("5.Pmic:MANUFACTURER_ID Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_SYS_CURRENT_LIMIT, _RAA489800_SUBADDR_LENGTH, 2, pucTempData) == _SUCCESS)
    {
        DebugMessageTypeC("5.Pmic:SYS_CURRENT_LIMIT_LB", pucTempData[0]);
        DebugMessageTypeC("5.Pmic:SYS_CURRENT_LIMIT_HB", pucTempData[1]);
    }
    else
    {
        DebugMessageTypeC("5.Pmic:SYS_CURRENT_LIMIT Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_FRW_REGULATING_VOLTAGE, _RAA489800_SUBADDR_LENGTH, 2, pucTempData) == _SUCCESS)
    {
        DebugMessageTypeC("5.Pmic:FRW_REGULATING_VOLTAGE_LB", pucTempData[0]);
        DebugMessageTypeC("5.Pmic:FRW_REGULATING_VOLTAGE_HB", pucTempData[1]);
    }
    else
    {
        DebugMessageTypeC("5.Pmic:FRW_REGULATING_VOLTAGE Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_INFORMATION1, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICINFO1Data)) == _SUCCESS)
    {
        DebugMessageTypeC("5.Pmic:CCModeChange", g_stPMICINFO1Data.b1INFO1CCModeChange);
        DebugMessageTypeC("5.Pmic:ADPsideOVP", g_stPMICINFO1Data.b1INFO1ADPsideOV);
        DebugMessageTypeC("5.Pmic:OTP", g_stPMICINFO1Data.b1INFO1OTP);
        DebugMessageTypeC("5.Pmic:SYSsideUVP", g_stPMICINFO1Data.b1INFO1SYSsideUV);
        DebugMessageTypeC("5.Pmic:SYSsideOVP", g_stPMICINFO1Data.b1INFO1SYSsideOV);
        DebugMessageTypeC("5.Pmic:WOCP", g_stPMICINFO1Data.b1INFO1WOCP);
        DebugMessageTypeC("5.Pmic:ActiveControlLoop", g_stPMICINFO1Data.b2INFO1ActiveControlLoop);
        DebugMessageTypeC("5.Pmic:ActiveReferenceCircuit", g_stPMICINFO1Data.b1INFO1ActiveReferenceCircuit);
    }
    else
    {
        DebugMessageTypeC("5.Pmic:Info1 Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    if(ScalerTypeCPmicIICRead(_TYPE_C_RX0_PMIC_SLAVE_ADDRESS, _RAA489800_INFORMATION2, _RAA489800_SUBADDR_LENGTH, 2, (BYTE *)(&g_stPMICINFO2Data)) == _SUCCESS)
    {
        DebugMessageTypeC("5.Pmic:PROGResistor", g_stPMICINFO2Data.b5INFO2PROGResistor);
        DebugMessageTypeC("5.Pmic:OperationMode", g_stPMICINFO2Data.b3INFO2OperationMode);
        DebugMessageTypeC("5.Pmic:StateMachineStatus", g_stPMICINFO2Data.b4INFO2StateMachineStatus);
        DebugMessageTypeC("5.Pmic:FWRSwitchEn", g_stPMICINFO2Data.b1INFO2FWRSwitchEn);
    }
    else
    {
        DebugMessageTypeC("5.Pmic:Info2 Fail", 0x00);
        return _TYPE_C_PMIC_CONTROL_FAIL;
    }

    return _TYPE_C_PMIC_CONTROL_SUCCESS;
}
#endif // End of #if(_TYPE_C_PMIC_DEBUG == _ON)

#if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
//--------------------------------------------------
// Description  : PMIC VBUS Current Reading
// Input Value  : None
// Output Value : usCurrent : 0 ~ 500 (Unit = 10mA)
//--------------------------------------------------
WORD ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(void)
{
    return 0;
}
#endif // End of #if(_TYPE_C_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#endif // End of #if(_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)

