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
// ID Code      : Global.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "reg52_RTD.h"
#include "intrins.h"
#include "string.h"
#include "math.h"

//****************************************************************************
// Data Type Redefine
//****************************************************************************
typedef unsigned char BYTE;
typedef char          SBYTE;
typedef unsigned int  WORD;
typedef int           SWORD;
typedef unsigned long DWORD;
typedef long          SDWORD;


//****************************************************************************
// Extern pData for All Layer Temporary Use
//****************************************************************************
extern BYTE data pData[16];
extern BYTE g_ucPcbGpioDefault;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
// Struct for Debug Timer Sample
typedef struct
{
    WORD usCounter_Start;
    WORD usCounter_End;
} StructTimerSampleMS;

typedef struct
{
    BYTE ucTH_Start;
    BYTE ucTL_Start;
    BYTE ucTH_End;
    BYTE ucTL_End;
    BYTE ucRCAP2H;
    BYTE ucRCAP2L;
} StructTimerSampleUS;

typedef enum
{
    _DEBUG_TIME_CURSOR_1 = 0,
    _DEBUG_TIME_CURSOR_2 = 1,
    _DEBUG_TIME_CURSOR_3 = 2,
    _DEBUG_TIME_CURSOR_4 = 3,
    _DEBUG_TIME_CURSOR_5 = 4,
    _DEBUG_TIME_CURSOR_END,
} EnumDebugTimeCursor;

typedef struct
{  
   BYTE b1LvdsDisplayBitMode : 7;   
   BYTE b1DitherWitch : 1;

   WORD usPanelMaxFrameRate;

   BYTE ucPanelDhStart;
   BYTE ucPanelDvStart;
   BYTE ucPanelSyncWidth;
   BYTE ucPanelSyncHeight;
   WORD usPanelDhWidth;
   WORD usPanelDvHeight;
   WORD usPanelDhTotal;
   WORD usPanelDvTotal;
   WORD usPanelMaxDhTotal;
   WORD usPanelMaxDvTotal;
   WORD usPanelMinDhTotal;
   WORD usPanelMinDvTotal;
   BYTE ucPanelPixClock;
   BYTE ucPanelMaxPixClock;
   BYTE ucPanelMinPixClock;

   WORD usPanelPowerOnT1;
   WORD usPanelPowerOnT2;
   WORD usPanelPowerOnT3;
   WORD usPanelPowerOffT4;
   WORD usPanelPowerOffT5;
   WORD usPanelPowerOffT6;  

   WORD usPanelPwmFre;
} StructUserDataInflashType;

// Struct for all Timing Info
typedef struct
{
    BYTE b1HSP : 1;             // HSP
    BYTE b1VSP : 1;             // VSP
    BYTE b1Interlace : 1;       // Interlace
    BYTE b1DpInterlaceVBID : 1; // Interlace For Dp VBID
    BYTE b1VideoField : 1;      // Field for video compensation
    WORD usHFreq;               // Horizontal Freq. (unit: 0.1kHz)
    WORD usHTotal;              // Horizontal Total length (unit: Pixel)
    WORD usHWidth;              // Horizontal Active Width (unit: Pixel)
    WORD usHStart;              // Horizontal Start (unit: Pixel)
    WORD usHSWidth;             // Horizontal Sync Pulse Count (unit: SyncProc Clock)

    WORD usVFreq;               // Vertical Freq. (unit: 0.1Hz)
    WORD usVTotal;              // Vertical Total length (unit: HSync)
    WORD usVHeight;             // Vertical Active Height (unit: HSync)
    WORD usVStart;              // Vertical Start (unit: HSync)
    WORD usVSWidth;             // Vertical Sync Width    (unit: HSync)
} StructTimingInfo;

typedef struct
{
    BYTE b1HSP : 1;
    BYTE b1VSP : 1;
    WORD usHSPeriod;
    WORD usHSWidth;
    WORD usVSPeriod;
    WORD usVSWidth;
    WORD usHTotal;
    WORD usHWidth;
    WORD usVHeight;
} StructMeasureSyncData;

typedef struct
{
    WORD usVActiveStart;
    WORD usVActiveEnd;
    WORD usHActiveStart;
    WORD usHActiveEnd;
} StructAutoActiveData;

// Struct for Display Timing Info
typedef struct
{
    WORD usHTotal;                // Horizontal Total length (unit: Pixel)
    WORD usHStart;                // Horizontal Start Position
    WORD usHWidth;                // Horizontal Active Width (unit: Pixel)
    WORD usHBackStart;            // Horizontal Back Ground Start Position
    WORD usHBackWidth;            // Horizontal Back Ground Active Width (unit: Pixel)

    WORD usVTotal;                // Vertical Total length (unit: HSync)
    WORD usVStart;                // Vertical Start Position
    WORD usVHeight;               // Vertical Active Height (unit: HSync)
    WORD usVBackStart;            // Vertical Back Ground Start Position
    WORD usVBackHeight;           // Vertical Back Ground Active Height (unit: HSync)
} StructDisplayInfo;

typedef struct
{
    BYTE ucAdcPGA;
    BYTE pucAdcGainMSB[3];
    BYTE pucAdcGainLSB[3];
    BYTE pucAdcOffsetMSB[3];
    BYTE pucAdcOffsetLSB[3];
} StructAdcDataType;

typedef struct
{
    WORD usInputHWidth;
    WORD usInputVHeight;
    WORD usOutputHWidth;
    WORD usOutputVHeight;
} StructSDRAMDataInfo;

typedef struct
{
    BYTE b1FORCETOFREERUN : 1;
    BYTE b1FORCETOFRC8BIT : 1;
    WORD usMaxFreq;
    WORD usTypFreq;
    WORD usMinFreq;
} StructDVCustomizedFreq;

typedef struct
{
    WORD usFRCSpace;
    WORD usFRCBW;
    WORD usFIFOHwidth;
} StructFRCFIFOInfo;

//--------------------------------------------------
// Definitions of SDRAM Calibration Status
//--------------------------------------------------
typedef struct
{
    BYTE b1FirstAutoKStatus : 1;
    BYTE b1CasChangeStatus : 1;
    BYTE b1DCOnOnLineStatus : 1;
} StructSDRAMCalControl;

//--------------------------------------------------
// Definitions of DDR3 MultiPhase Info
//--------------------------------------------------
typedef struct
{
    DWORD ulDdrPllInitialPhase0;
    DWORD ulDdrPllInitialPhase1;
    DWORD ulDdrReadDqDelayTap;
} StructDDR3PhaseInfo;

typedef struct
{
    BYTE b3MemorySelect : 3;
    BYTE b3DVFSelect : 3;
    BYTE b2MemoryConf : 2;
    BYTE b5DataBit : 5;
    BYTE b1HSU : 1;
    BYTE b1HSD : 1;
    BYTE b1VSU : 1;
    BYTE b1VSD : 1;
    BYTE b2MemoryFrameBuf : 2;
} StructMDomainInfo;

//--------------------------------------------------
// Struct for DP HDMI Compatible Mode Info
//--------------------------------------------------
typedef struct
{
    BYTE b1D0Hdmi5VStatus : 1;
    BYTE b1D1Hdmi5VStatus : 1;
    BYTE b1D2Hdmi5VStatus : 1;
    BYTE b1D3Hdmi5VStatus : 1;
    BYTE b1D0HdmiPSWakeUp : 1;
    BYTE b1D1HdmiPSWakeUp : 1;
    BYTE b1D2HdmiPSWakeUp : 1;
    BYTE b1D3HdmiPSWakeUp : 1;
} StructDpHdmiCompatibleInfo;

//--------------------------------------------------
// Definitions for DP Margin Link
//--------------------------------------------------
typedef struct
{
    BYTE b1D0MarginLinkHBR2 : 1;
    BYTE b1D0Lane0MarginLinkHBRRBR : 1;
    BYTE b1D0Lane1MarginLinkHBRRBR : 1;
    BYTE b1D0Lane2MarginLinkHBRRBR : 1;
    BYTE b1D0Lane3MarginLinkHBRRBR : 1;
    BYTE b1D1MarginLinkHBR2 : 1;
    BYTE b1D1Lane0MarginLinkHBRRBR : 1;
    BYTE b1D1Lane1MarginLinkHBRRBR : 1;
    BYTE b1D1Lane2MarginLinkHBRRBR : 1;
    BYTE b1D1Lane3MarginLinkHBRRBR : 1;
    BYTE b1D6MarginLinkHBR2 : 1;
} StructDPMarginLinkInfo;

//--------------------------------------------------
// Definitions for DP Aux
//--------------------------------------------------
typedef struct
{
    BYTE b1DpAuxMode : 1;
    BYTE b4DpAuxAdjrSet : 4;
} StructDpAuxSetting;

typedef enum
{
    _DP_AUX_FAIL = 0x00,
    _DP_AUX_PASS,
} EnumDpAuxStatus;

//--------------------------------------------------
// Structure of DP Lanes Mapping
//--------------------------------------------------
typedef struct
{
    BYTE b2Lane0Mapping : 2;
    BYTE b2Lane1Mapping : 2;
    BYTE b2Lane2Mapping : 2;
    BYTE b2Lane3Mapping : 2;
    BYTE b1Lane0PNSwap : 1;
    BYTE b1Lane1PNSwap : 1;
    BYTE b1Lane2PNSwap : 1;
    BYTE b1Lane3PNSwap : 1;
} StructDpLanesMapping;

typedef struct
{
    BYTE b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1AuthRepeaterProcTimeout : 1;
    BYTE ucAuthUpstreamEvent;
    BYTE b1AuthCpIrqTimer : 1;
    BYTE b1AuthHdcp2ContentStreamManage : 1;
    BYTE b1AuthHdcp1ContentStreamManage : 1;
    BYTE b1AuthRepeaterAuth1Start : 1;
    BYTE b1AuthRepeaterAuth2Start : 1;
} StructDpRxHdcp2AuthInfo;

typedef enum
{
    _HDCP_NONE = 0x00,
    _HDCP_14 = 0x14,
    _HDCP_22 = 0x22,
    _HDCP_14_REPEATER = 0x94,
    _HDCP_22_REPEATER = 0xA2,
} EnumHDCPType;

//--------------------------------------------------
// Enumerations of Type-C Attach Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_UNATTACH = 0,
    _TYPE_C_ATTACH = 1,
}EnumTypeCAttachStatus;

//--------------------------------------------------
// Type-C Orientation
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ORIENTATION_NONE = 0x00,
    _TYPE_C_ORIENTATION_UNFLIP = 0x01,
    _TYPE_C_ORIENTATION_FLIP = 0x02,
}EnumTypeCOrientation;

//--------------------------------------------------
// Structure of Type-C Power Related Info
//--------------------------------------------------
typedef struct
{
    WORD b10AvaliablePower : 10;
    WORD b10Rx0MaxPower : 10;
    WORD b10Rx0ReqPower : 10;
    WORD b12Rx0OutputVol : 12;
    WORD b10Rx0OutputCur : 10;
    WORD b10Rx05VUpBound : 10;
    WORD b10Rx05VLowBound : 10;
    WORD b10Rx00VUpBound : 10;
    WORD b10Rx0LocPowOn : 10;
    WORD b10Rx0LocPowOff : 10;
    BYTE b1VbusStatus : 1;
}StructTypeCPowerInfo;

//--------------------------------------------------
// Structure of Type-C Related Structs
//--------------------------------------------------
typedef struct
{
    BYTE b5State : 5;
    BYTE b3AttachStatus : 3;
    // -----------------------------
    BYTE b3CC1Resistor : 3;
    BYTE b3CC2Resistor : 3;
    BYTE b1FRSrcEnable : 1;
    BYTE b1FRSnkEnable : 1;
    // -----------------------------
    EnumTypeCAttachStatus enumCCAttached;
    // -----------------------------
    EnumTypeCOrientation enumOrientation;
    // -----------------------------
    BYTE ucUnattachDebounce;
    // -----------------------------
    WORD b1Error : 1;
    WORD b1RaExist : 1;
    WORD b1VconnStatus : 1;
    WORD b1ConnectEnable : 1;
    WORD b1DRPConnectMode : 1;
    WORD b1AcOnReconnect : 1;
    WORD b10DefCurrent : 10;
    // -----------------------------
    WORD usDefOcpCurrent;
    // -----------------------------
    BYTE b1DeviceDetect : 1;
}StructTypeCInfo;

typedef struct
{
    WORD usDpRxLane0ErrorCount;
    WORD usDpRxLane1ErrorCount;
    WORD usDpRxLane2ErrorCount;
    WORD usDpRxLane3ErrorCount;
} StructDpRxErrorCount;

typedef struct
{
    WORD usVTotal;
    WORD usHTotal;
    WORD usDclk;
    WORD usVFreq;
} StructRtkAdvMbrTimingInfo;

typedef struct
{
    BYTE ucFrameSyncMargin;
    WORD usMaxFreq;
    WORD usMinFreq;
    DWORD ulPixelClock;
    DWORD ulPixelClockMax;
    DWORD ulPixelClockMin;
} StructRtkAdvMbrPanelInfo;

//****************************************************************************
// General Definitions
//****************************************************************************
//--------------------------------------------------
// Definitions of Physical Boolean
//--------------------------------------------------
#define _TRUE                                   1
#define _FALSE                                  0
#define _HIGH                                   1
#define _LOW                                    0
#define _ENABLE                                 1
#define _DISABLE                                0
#define _READ                                   1
#define _WRITE                                  0
#define _ON                                     1
#define _OFF                                    0
#define _SUCCESS                                1
#define _FAIL                                   0
#define _STABLE                                 1
#define _UNSTABLE                               0
#define _POSITIVE                               1
#define _NEGATIVE                               0
#define _NEWMODE                                1
#define _OLDMODE                                0
#define _ODD                                    1
#define _EVEN                                   0
#define _WAIT                                   1
#define _NOT_WAIT                               0
#define _RIGHT                                  1
#define _LEFT                                   0
#define _EDID_SWITCH_MODE                       1
#define _MCCS_SWITCH_MODE                       0
#define _LINE_BUFFER_METHOD                     1
#define _FRAME_BUFFER_METHOD                    0

//--------------------------------------------------
// Definitions of Page
//--------------------------------------------------
#define _PAGE0                                  0x00
#define _PAGE1                                  0x01
#define _PAGE2                                  0x02
#define _PAGE3                                  0x03
#define _PAGE4                                  0x04
#define _PAGE5                                  0x05
#define _PAGE6                                  0x06
#define _PAGE7                                  0x07
#define _PAGE8                                  0x08
#define _PAGE9                                  0x09
#define _PAGEA                                  0x0A
#define _PAGEB                                  0x0B
#define _PAGEC                                  0x0C
#define _PAGED                                  0x0D
#define _PAGEE                                  0x0E
#define _PAGEF                                  0x0F
#define _PAGE10                                 0x10

#define _PAGE2D                                 0x2D
#define _PAGE2E                                 0x2E
#define _PAGE6D                                 0x6D
#define _PAGE6E                                 0x6E

#define _PAGE70                                 0x70
#define _PAGE71                                 0x71
#define _PAGE72                                 0x72
#define _PAGE73                                 0x73
#define _PAGE74                                 0x74

#define _PAGEB5                                 0xB5
#define _PAGEB8                                 0xB8

#define _PAGE_COMMON                            0xFF
#define _PAGE_NONE                              0x100

//--------------------------------------------------
// Definitions of Bits
//--------------------------------------------------
#define _BIT0                                   0x0001U
#define _BIT1                                   0x0002U
#define _BIT2                                   0x0004U
#define _BIT3                                   0x0008U
#define _BIT4                                   0x0010U
#define _BIT5                                   0x0020U
#define _BIT6                                   0x0040U
#define _BIT7                                   0x0080U
#define _BIT8                                   0x0100U
#define _BIT9                                   0x0200U
#define _BIT10                                  0x0400U
#define _BIT11                                  0x0800U
#define _BIT12                                  0x1000U
#define _BIT13                                  0x2000U
#define _BIT14                                  0x4000U
#define _BIT15                                  0x8000U
#define _BIT16                                  0x10000U

#define _8_BIT                                  0x00FF
#define _9_BIT                                  0x01FF
#define _10_BIT                                 0x03FF
#define _12_BIT                                 0x0FFF
#define _13_BIT                                 0x1FFF
#define _14_BIT                                 0x3FFF
#define _20_BIT                                 0xFFFFF

//--------------------------------------------------
// Definitions of Clock Divider Number
//--------------------------------------------------
#define _DIV_1                                  1
#define _DIV_2                                  2
#define _DIV_3                                  3
#define _DIV_4                                  4
#define _DIV_5                                  5
#define _DIV_6                                  6
#define _DIV_7                                  7
#define _DIV_8                                  8
#define _DIV_9                                  9
#define _DIV_10                                 10
#define _DIV_11                                 11
#define _DIV_12                                 12
#define _DIV_13                                 13

//--------------------------------------------------
// Definations of Scaler Write/Read Type
//--------------------------------------------------
#define _NON_AUTOINC                            1
#define _AUTOINC                                0
#define _BURST                                  2
#define _END                                    0

//--------------------------------------------------
// Definitions of Null Pointer
//--------------------------------------------------
#define _NULL_POINTER                           ((BYTE code *)0xFFFF)

//--------------------------------------------------
// Definitions of Page Register
//--------------------------------------------------
#define _REG_MAIN1_PAGE                         0x0000U
#define _REG_MAIN2_PAGE                         0x4000U
#define _REG_SUB1_PAGE                          0x8000U
#define _REG_SUB2_PAGE                          0xC000U

//--------------------------------------------------
// Definitions of Checker
//--------------------------------------------------
#define _ERROR_PRONE_CODE                       (_TRUE)

//****************************************************************************
// Definitions of Type-C
//****************************************************************************

//****************************************************************************
// Definitions of DP
//****************************************************************************
//--------------------------------------------------
// Definitions of Embedded DP Switch Type
//--------------------------------------------------
#define _DP_EMBEDDED_SWITCH_NONE                0x00
#define _DP_EMBEDDED_SWITCH_1_DP                0x01
#define _DP_EMBEDDED_SWITCH_2_DP                0x02

//****************************************************************************
// Definitions of TMDS
//****************************************************************************
//--------------------------------------------------
// Definitions of TMDS HPD Type
//--------------------------------------------------
#define _TMDS_HPD_NONE                          0
#define _TMDS_HPD_NORMAL                        1
#define _TMDS_HPD_HDCP_2_2                      2
#define _TMDS_HPD_ACER                          3
#define _TMDS_HPD_EDID_SWITCH                   4
#define _TMDS_HPD_EIZO_PS_WAKEUP                5

//****************************************************************************
// Definitions of Audio
//****************************************************************************
//--------------------------------------------------
// Definitions of Audio Volume Resolution
//--------------------------------------------------
#define _AUDIO_VOLUME_8BIT                      0
#define _AUDIO_VOLUME_14BIT                     1    // DVC  Support Only

//--------------------------------------------------
// Definitions of Analog Audio Input Type
//--------------------------------------------------
#define _AUDIO_FROM_AIN                         0
#define _AUDIO_FROM_DAC                         1

//****************************************************************************
// Definitions of Auto
//****************************************************************************
//--------------------------------------------------
// Definitions of Auto Function Channel
//--------------------------------------------------
#define _AUTO_RED_CHANNEL                       0
#define _AUTO_GREEN_CHANNEL                     1
#define _AUTO_BLUE_CHANNEL                      2
#define _AUTO_RGB_CHANNEL                       3


//****************************************************************************
// Definitions of CBUS
//****************************************************************************
#define _CBUS0                                  0
#define _CBUS1                                  1
#define _CBUS2                                  2
#define _CBUS3                                  3
#define _NO_CBUS                                4

//****************************************************************************
// Definitions of Digital Functions
//****************************************************************************
//--------------------------------------------------
// Definitions of DCR Source Option
//--------------------------------------------------
#define _DCR_BEFORE_DCC                         0
#define _DCR_BEFORE_IAPSGAIN                    1

//--------------------------------------------------
// Definitions of Highlight Window Option
//--------------------------------------------------
#define _HLW_BORDER_BOTTOM                      _BIT4
#define _HLW_BORDER_TOP                         _BIT5
#define _HLW_BORDER_RIGHT                       _BIT6
#define _HLW_BORDER_LEFT                        _BIT7

//--------------------------------------------------
// Definitions of ICM Adjust Option
//--------------------------------------------------
#define _CM0_ENABLE                             _BIT0
#define _CM1_ENABLE                             _BIT1
#define _CM2_ENABLE                             _BIT2
#define _CM3_ENABLE                             _BIT3
#define _CM4_ENABLE                             _BIT4
#define _CM5_ENABLE                             _BIT5
#define _Y_CORRECTION_MODE                      _BIT6
#define _UV_DELTA_RANGE                         _BIT7
#define _UV_DELTA_RANGE_EXTEND                  _BIT0

#define _SCM0_BLOCK0_ENABLE                     _BIT0
#define _SCM0_BLOCK1_ENABLE                     _BIT1
#define _SCM1_BLOCK0_ENABLE                     _BIT2
#define _SCM1_BLOCK1_ENABLE                     _BIT3
#define _SCM2_BLOCK0_ENABLE                     _BIT4
#define _SCM2_BLOCK1_ENABLE                     _BIT5
#define _SCM3_BLOCK0_ENABLE                     _BIT6
#define _SCM3_BLOCK1_ENABLE                     _BIT7
#define _SCMN_SHARE_REG                         _BIT0

//--------------------------------------------------
// Definitions of OD Table Mode
//--------------------------------------------------
#define _OD_8BIT_LUT                            0
#define _OD_10BIT_LUT                           1

//--------------------------------------------------
// Definitions of Panel Uniformity Level Correction Selection
//--------------------------------------------------
#define _UNIFORMITY_NONE                        0
#define _UNIFORMITY_1LEVEL                      1
#define _UNIFORMITY_4LEVEL                      4

//****************************************************************************
// Definitions of EMCU
//****************************************************************************
//--------------------------------------------------
// Definations of DDC Channel
//--------------------------------------------------
#define _VGA_DDC                                0
#define _DDC0                                   1
#define _DDC1                                   2
#define _DDC2                                   3
#define _DDC3                                   4
#define _DDC4                                   5
#define _DDC5                                   6
#define _NO_DDC                                 7
#define _VGA_DDC2                               8

#define _DDC_ISP_CHANNEL_ENABLE_ALL             ((WORD)((1 << _VGA_DDC) |\
                                                        (1 << _DDC0) |\
                                                        (1 << _DDC1) |\
                                                        (1 << _DDC2) |\
                                                        (1 << _DDC3) |\
                                                        (1 << _DDC4) |\
                                                        (1 << _DDC5) |\
                                                        (1 << _VGA_DDC2)))

//--------------------------------------------------
// Definations of HDMI-CEC
//--------------------------------------------------
#define _HDMI_CEC_NONE                          0
#define _HDMI_CEC_0                             1

//--------------------------------------------------
// Definations of HDMI-CEC HW Type
// NONE: NO CEC HW IP Exist
// Type0: NO "received HB form CEC RX (0x18E3) & "Result of CEC TX sent (0x18B7[7:5])"
// Type1: NO "received HB form CEC RX (0x18E3)..ex. 6561 after ECO..
// Type2: ex. 6478, 1039...
//--------------------------------------------------
#define _HW_CEC_GEN_NONE                        0
#define _HW_CEC_GEN_TYPE_0                      1
#define _HW_CEC_GEN_TYPE_1                      2
#define _HW_CEC_GEN_TYPE_2                      3

//--------------------------------------------------
// Define for HW burst write
//--------------------------------------------------
#define _BURSTWRITE_FROM_FLASH                  0
#define _BURSTWRITE_FROM_XRAM                   1

#define _BURSTWRITE_COMMAND                     0
#define _BURSTWRITE_DATA_COMMON                 1
#define _BURSTWRITE_DATA_COMMON_AUTO_INC        2
#define _BURSTWRITE_DATA_OSD                    3

//--------------------------------------------------
// Reserved for pin define
//--------------------------------------------------
#define MCU_EMPTY_PIN_ASSIGN_ADDRESS            g_ucPcbGpioDefault


//****************************************************************************
// Definitions of IOSC
//****************************************************************************
//--------------------------------------------------
// Definitions of IOSC Clock Divider Number
//--------------------------------------------------
#define _IOSC_DIV_1                             0
#define _IOSC_DIV_2                             1
#define _IOSC_DIV_4                             2
#define _IOSC_DIV_8                             3

#define _IOSC_DIV                               _IOSC_DIV_1

//--------------------------------------------------
// Definitions of IOSC Frequency
//--------------------------------------------------
#define _IOSC27000K                             27000UL
#define _IOSC28000K                             28000UL
#define _IOSC108000K                            108000UL

//--------------------------------------------------
// Definitions of LcTank Frequency
//--------------------------------------------------
#define _LCTANK27000K                           27000UL

//****************************************************************************
// Definitions of Memory
//****************************************************************************
//--------------------------------------------------
// Definitions for Memory
//--------------------------------------------------
#define _FRAME_SYNC_LINE_BUFFER                 0
#define _FRAME_SYNC_MEMORY                      1
#define _FREE_RUN_MEMORY                        2
#define _MN_FRAME_SYNC_MEMORY                   3
#define _FREE_RUN_NO_INPUT                      4

//--------------------------------------------------
// Definitions of DVF type
//--------------------------------------------------
#define _1_IVF                                  0
#define _2_IVF                                  1
#define _3_IVF                                  2
#define _PANEL_TYP_FRAME_RATE_FREE_RUN          3
#define _2_5_IVF                                4
#define _5_4_IVF                                5
#define _6_5_IVF                                6

//--------------------------------------------------
// Definitions of Memory arrangement
//--------------------------------------------------
#define _LINE_MODE                              0
#define _FRAME_MODE                             1

//--------------------------------------------------
// Definitions of DDR Phase Calibration
//--------------------------------------------------
#define _MEMORY_PHASE_CALIBRATION_MCU_MODE      0
#define _MEMORY_PHASE_CALIBRATION_FRC_MODE      1
#define _MEMORY_PHASE_CALIBRATION_MODE_NONE     2

//****************************************************************************
// Definitions of MHL Packets
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Reply List
//--------------------------------------------------
#define _MHL_SUCCESS                            0
#define _MHL_FAIL                               1
#define _MHL_ABORT_FAIL                         2
#define _MHL_PROTOCOL_ERROR                     3

//--------------------------------------------------
// Definitions of HDCP 2.2 RSA input parameter
//--------------------------------------------------
#define _HDCP_2_2_RSA_CIPHER_TEXT               0
#define _HDCP_2_2_RSA_RRMODN_KEY                1
#define _HDCP_2_2_RSA_D_KEY                     2
#define _HDCP_2_2_RSA_N_PINV                    4
#define _HDCP_2_2_RSA_D_KEY_ENC                 5
#define _HDCP_2_2_CERT_RX                       6
#define _HDCP_2_2_LC                            7
#define _HDCP_2_2_KPUB_KM                       8
#define _HDCP_2_2_RRX                           9
#define _HDCP_2_2_RX_H_PRIME                    10
#define _HDCP_2_2_RX_PAIRING_INFO               11
#define _HDCP_2_2_RX_L_PRIME                    12
#define _HDCP_2_2_RX_M_PRIME                    13
#define _HDCP_2_2_RX_V_PRIME                    14

//--------------------------------------------------
// Definitions of HDCP 2.2 Load Key Prpcess
//--------------------------------------------------
#define _DP_TX_HDCP2_KEY_SIGNATURE              1
#define _DP_TX_HDCP2_KEY_RRMODN                 2
#define _DP_TX_HDCP2_KEY_DCP_LLC_N              3
#define _DP_TX_HDCP2_KEY_EKEY1                  4
#define _DP_TX_HDCP2_KEY_EKEY2                  5
#define _DP_TX_HDCP2_KEY_NPINV                  6

//****************************************************************************
// Definitions of Mode Search
//****************************************************************************
#define _USER_MODE_TYPE                         0
#define _PRESET_MODE_TYPE                       1

//****************************************************************************
// Definitions of NVRam
//****************************************************************************
#define _FLASH_PAGE_SIZE                        4096U

//****************************************************************************
// Definitions of FW Access Flash Method
//****************************************************************************
#define _FLASH_PORT_ACCESS                      0
#define _XDATA_MAP_ACCESS                       1

//****************************************************************************
// Definitions of M2PLL Freq
//****************************************************************************
#define _M2PLL_FREQ_243M                        0
#define _M2PLL_FREQ_351M                        1
#define _M2PLL_FREQ_372M                        2

//****************************************************************************
// Definitions of TypeC ADC Setting
//****************************************************************************
#define _TYPE_C_ADC_WITHIN_RANGE                0x00
#define _TYPE_C_ADC_WITHOUT_RANGE               0x01

//--------------------------------------------------
// Definitions of VGIP IV Capture Front Porch Min Value
//--------------------------------------------------
#define _VGIP_V_FRONT_PORCH_MIN_VALUE           (3)

//****************************************************************************
// Definitions of OSD
//****************************************************************************
typedef enum
{
    _OSD_WIN_CONTROL = 0,
    _OSD_SRAM = _BIT3,
} EnumOsdAddrIndicateType;

typedef enum
{
    _OSD_WITHOUT_DB = 0,
    _OSD_WITH_DB = _BIT7,
} EnumOsdDBufType;

typedef enum
{
    _OSD_BYTE0 = _BIT5,
    _OSD_BYTE1 = _BIT6,
    _OSD_BYTE2 = _BIT7,
    _OSD_BYTE0_BYTE1 = (_BIT6 | _BIT5),
    _OSD_BYTE0_BYTE2 = (_BIT7 | _BIT5),
    _OSD_BYTE1_BYTE2 = (_BIT7 | _BIT6),
    _OSD_BYTEALL = (_BIT7 | _BIT6 | _BIT5),
} EnumOsdWriteType;


//****************************************************************************
// Definitions of Panel
//****************************************************************************
//--------------------------------------------------
// Definitions of Panel Power Status
//--------------------------------------------------
#define _PANEL_POWER_OFF_STATE                  0
#define _WAITING_FOR_BACKLIGHT                  1
#define _READY_FOR_BACKLIGHT                    2
#define _BACKLIGHT_ON_ALREADY                   3
#define _PANEL_BACKLIGHT_OFF                    4
#define _WAITING_FOR_PANEL_OFF                  5


//--------------------------------------------------
// Definitions of Panel Power Action
//--------------------------------------------------
#define _PANEL_ON                               0
#define _PANEL_OFF                              1
#define _BACKLIGHT_ON                           2
#define _BACKLIGHT_OFF                          3


//****************************************************************************
// Definitions of Sync
//****************************************************************************
//--------------------------------------------------
// Definitions of Input Sync Type State
//--------------------------------------------------
#define _NO_SYNC_STATE                          0
#define _SS_STATE                               1
#define _CS_STATE                               2
#define _SOG_STATE                              3
#define _SOY_STATE                              4
#define _DSS_STATE                              5
#define _NOT_SUPPORT_STATE                      0


//****************************************************************************
// Definitions of Source
//****************************************************************************
//--------------------------------------------------
// Definitions of Source Switch Type
//--------------------------------------------------
#define _SOURCE_SWITCH_FIXED_PORT               0
#define _SOURCE_SWITCH_AUTO_IN_GROUP            1
#define _SOURCE_SWITCH_AUTO_WITHOUT_GROUP       2
#define _SOURCE_SWITCH_HP_SOURCE_SCAN           3
#define _SOURCE_SWITCH_HP_TIMING_CHANGE         4
#define _SOURCE_SWITCH_HP_SOURCE_SWITCH         5
#define _SOURCE_SWITCH_HP_OOR_SOURCE_SCAN       6
#define _SOURCE_SWITCH_ASUS_AUTO                7
#define _SOURCE_SWITCH_DELL_HOTKEY_AUTO         8
#define _SOURCE_SWITCH_DELL_HOTKEY_FIXED        9
#define _SOURCE_SWITCH_HP_SCAN_SWITCH_PORT      10
#define _SOURCE_SWITCH_HP_SCAN_NEXT_PORT        11

//--------------------------------------------------
// Definitions of HP Source Switch Type
//--------------------------------------------------
#define _HP_SOURCE_SCAN_TYPE_E                  0
#define _HP_SOURCE_SCAN_TYPE_F                  1


//--------------------------------------------------
// Definitions of Source Search Delay Mode
//--------------------------------------------------
#define _SOURCE_SEARCH_POLLING_MODE             0
#define _SOURCE_SEARCH_DELAY_DEFAULT_MODE       1
#define _SOURCE_SEARCH_DELAY_REACTIVE_MODE      2
#define _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE    3

//****************************************************************************
// Definitions of 3D
//****************************************************************************
//--------------------------------------------------
// Definitions of Chroma Weight for Depth Calculation
//--------------------------------------------------
#define _LUMINANCE                              0
#define _CHROMINANCE_1                          1
#define _CHROMINANCE_1_2                        2
#define _CHROMINANCE_1_4                        3

//--------------------------------------------------
// Definitions of LPF Weight Option
//--------------------------------------------------
#define _LPF_BLUR_STRONG                        0
#define _LPF_BLUR_MEDIUM                        1
#define _LPF_BLUR_WEAK                          2

//--------------------------------------------------
// Definitions of Hole Filling Mode
//--------------------------------------------------
#define _INTEGER_LEFT                           0
#define _INTEGER_INTERPOLATE                    1
#define _FRACTION_LEFT                          2
#define _FRACTION_INTERPOLATE                   3

//--------------------------------------------------
// Definitions of Dither Options
//--------------------------------------------------
#define _DDITHER_KEEP_1_FRAME                   0
#define _DDITHER_KEEP_2_FRAME                   1
#define _DDITHER_KEEP_4_FRAME                   2
#define _DDITHER_KEEP_8_FRAME                   3
#define _DDITHER_KEEP_16_FRAME                  4

#define _DDITHER_SUPER_PIXEL_2X2                0
#define _DDITHER_SUPER_PIXEL_2X4                1
#define _DDITHER_SUPER_PIXEL_4X2                2
#define _DDITHER_SUPER_PIXEL_4X4                3
#define _DDITHER_SUPER_PIXEL_4X8                4
#define _DDITHER_SUPER_PIXEL_8X4                5
#define _DDITHER_SUPER_PIXEL_8X8                6

//--------------------------------------------------
// Definitions of Color Depth
//--------------------------------------------------
#define _COLOR_DEPTH_6_BITS                     6
#define _COLOR_DEPTH_7_BITS                     7
#define _COLOR_DEPTH_8_BITS                     8
#define _COLOR_DEPTH_10_BITS                    10
#define _COLOR_DEPTH_12_BITS                    12
#define _COLOR_DEPTH_14_BITS                    14
#define _COLOR_DEPTH_16_BITS                    16

//--------------------------------------------------
// Macro of Instant Timer0/1 Counter Options
//--------------------------------------------------
#define _TIMER_OFF                              0

//****************************************************************************
// Definitions of Tcon
//****************************************************************************
//--------------------------------------------------
// Definitions of Tcon
//--------------------------------------------------
#define _TCON0                                  0
#define _TCON1                                  1
#define _TCON2                                  2
#define _TCON3                                  3
#define _TCON4                                  4
#define _TCON5                                  5
#define _TCON6                                  6
#define _TCON7                                  7
#define _TCON8                                  8
#define _TCON9                                  9
#define _TCON10                                 10
#define _TCON11                                 11
#define _TCON12                                 12
#define _TCON13                                 13

//****************************************************************************
// Global Macros
//****************************************************************************
#define LOBYTE(w)                               ((BYTE)(w))
#define HIBYTE(w)                               ((BYTE)(((WORD)(w) >> 8) & 0x00FF))
#define LOWORD(dw)                              ((WORD)(dw))
#define HIWORD(dw)                              ((WORD)((dw) >> 16))
#define SEC(x)                                  ((WORD)(1000U * (x)))

#define MAXOF(a, b)                             (((a) > (b)) ? (a) : (b))
#define MINOF(a, b)                             (((a) < (b)) ? (a) : (b))

#define SHL(x, y)                               ((x) << (y))
#define SHR(x, y)                               ((x) >> (y))
#define AND(n1, n2)                             ((n1) & (n2))

#define ABSDWORD(x, y)                          (((x) > (y)) ? ((x) - (y)) : ((y) - (x)))

#define GET_CURRENT_BANK_NUMBER()               (MCU_FFFF_PBANK_SWITCH)

//--------------------------------------------------
// Macro of Get Data bit
//--------------------------------------------------
#define GET_DATA_BIT7(x)                        ((bit)((x) & _BIT7))
#define GET_DATA_BIT6(x)                        ((bit)((x) & _BIT6))
#define GET_DATA_BIT5(x)                        ((bit)((x) & _BIT5))
#define GET_DATA_BIT4(x)                        ((bit)((x) & _BIT4))
#define GET_DATA_BIT3(x)                        ((bit)((x) & _BIT3))
#define GET_DATA_BIT2(x)                        ((bit)((x) & _BIT2))
#define GET_DATA_BIT1(x)                        ((bit)((x) & _BIT1))
#define GET_DATA_BIT0(x)                        ((bit)((x) & _BIT0))

//--------------------------------------------------
// Macro of WORD/DWORD pData
//--------------------------------------------------
#define PDATA_WORD(x)                           (((WORD *)pData)[x])
#define PDATA_WORD_EXINT(x)                     (((WORD *)pData_EXINT)[x])
#define PDATA_DWORD(x)                          (((DWORD *)pData)[x])
#define PDATA_DWORD_EXINT(x)                    (((DWORD *)pData_EXINT)[x])

//--------------------------------------------------
// Macro of BYTE Pointer
//--------------------------------------------------
#define BYTEPTR(var)                            ((BYTE *)&(var))

//--------------------------------------------------
// Macro of Get Input Port and Port Type (x is Input Port Type)
//--------------------------------------------------
#define GET_INPUT_PORT(x)                       ((x) >> 4)
#define GET_PORT_TYPE(x)                        ((x) & 0x0F)

//--------------------------------------------------
// Macro of Cable Detect Flag
//--------------------------------------------------
#define GET_A0_CABLE_STATUS()                   (g_stPortCableStatus.b1A0CableDetect)
#define SET_A0_CABLE_STATUS(x)                  (g_stPortCableStatus.b1A0CableDetect = (x))

#define GET_A1_CABLE_STATUS()                   (g_stPortCableStatus.b1A1CableDetect)
#define SET_A1_CABLE_STATUS(x)                  (g_stPortCableStatus.b1A1CableDetect = (x))

#define GET_A2_CABLE_STATUS()                   (g_stPortCableStatus.b1A2CableDetect)
#define SET_A2_CABLE_STATUS(x)                  (g_stPortCableStatus.b1A2CableDetect = (x))

#define GET_D0_CABLE_STATUS()                   (g_stPortCableStatus.b1D0CableDetect)
#define SET_D0_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D0CableDetect = (x))

#define GET_D1_CABLE_STATUS()                   (g_stPortCableStatus.b1D1CableDetect)
#define SET_D1_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D1CableDetect = (x))

#define GET_D2_CABLE_STATUS()                   (g_stPortCableStatus.b1D2CableDetect)
#define SET_D2_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D2CableDetect = (x))

#define GET_D3_CABLE_STATUS()                   (g_stPortCableStatus.b1D3CableDetect)
#define SET_D3_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D3CableDetect = (x))

#define GET_D4_CABLE_STATUS()                   (g_stPortCableStatus.b1D4CableDetect)
#define SET_D4_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D4CableDetect = (x))

#define GET_D5_CABLE_STATUS()                   (g_stPortCableStatus.b1D5CableDetect)
#define SET_D5_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D5CableDetect = (x))

#define GET_D6_CABLE_STATUS()                   (g_stPortCableStatus.b1D6CableDetect)
#define SET_D6_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D6CableDetect = (x))

#define GET_D0_TMDS_MODE()                      (g_stPortCableStatus.b1D0MHLCableDetect)
#define SET_D0_TMDS_MODE(x)                     (g_stPortCableStatus.b1D0MHLCableDetect = (x))

#define GET_D1_TMDS_MODE()                      (g_stPortCableStatus.b1D1MHLCableDetect)
#define SET_D1_TMDS_MODE(x)                     (g_stPortCableStatus.b1D1MHLCableDetect = (x))

#define GET_D2_TMDS_MODE()                      (g_stPortCableStatus.b1D2MHLCableDetect)
#define SET_D2_TMDS_MODE(x)                     (g_stPortCableStatus.b1D2MHLCableDetect = (x))

#define GET_D3_TMDS_MODE()                      (g_stPortCableStatus.b1D3MHLCableDetect)
#define SET_D3_TMDS_MODE(x)                     (g_stPortCableStatus.b1D3MHLCableDetect = (x))

#define GET_D4_TMDS_MODE()                      (g_stPortCableStatus.b1D4MHLCableDetect)
#define SET_D4_TMDS_MODE(x)                     (g_stPortCableStatus.b1D4MHLCableDetect = (x))

#define GET_D5_TMDS_MODE()                      (g_stPortCableStatus.b1D5MHLCableDetect)
#define SET_D5_TMDS_MODE(x)                     (g_stPortCableStatus.b1D5MHLCableDetect = (x))

#define GET_D6_SWITCH_SELECT()                  (g_ucD6SwitchSelect)
#define SET_D6_SWITCH_SELECT(x)                 (g_ucD6SwitchSelect = (x))

#define GET_D6_SWITCH_POWER_STATUS()            (g_bD6SwitchPowerStatus)
#define SET_D6_SWITCH_POWER_STATUS(x)           (g_bD6SwitchPowerStatus = (x))

#define GET_DP_EMBEDDED_SWITCH_SELECT()         (g_ucDpEmbeddedSwitchSelect)
#define SET_DP_EMBEDDED_SWITCH_SELECT(x)        (g_ucDpEmbeddedSwitchSelect = (x))

#define GET_DP_EMBEDDED_SWITCH_TARGET()         (g_ucDpEmbeddedSwitchTarget)
#define SET_DP_EMBEDDED_SWITCH_TARGET(x)        (g_ucDpEmbeddedSwitchTarget = (x))

#define GET_DP_EMBEDDED_SWITCH_EVENT()          (g_bDpEmbeddedSwitchEvent)
#define SET_DP_EMBEDDED_SWITCH_EVENT(x)         (g_bDpEmbeddedSwitchEvent = (x))

#define GET_DP_AUTO_SEARCH_SWITCH()             (g_bDpAutoSearchSwitch)
#define SET_DP_AUTO_SEARCH_SWITCH()             (g_bDpAutoSearchSwitch = _TRUE)
#define CLR_DP_AUTO_SEARCH_SWITCH()             (g_bDpAutoSearchSwitch = _FALSE)

#define GET_DCLK_SPREAD_SPEED_VALUE()           (g_uDclkSpreadSpeed)
#define SET_DCLK_SPREAD_SPEED_VALUE(x)          (g_uDclkSpreadSpeed  = (x))
#define GET_DCLK_SPREAD_RANGE_VALUE()           (g_uDclkSpreadRange)
#define SET_DCLK_SPREAD_RANGE_VALUE(x)          (g_uDclkSpreadRange  = (x))

//****************************************************************************
// General Enumerations
//****************************************************************************

//--------------------------------------------------
// Enumerations of DDCRAM Addr Select
//--------------------------------------------------
typedef enum
{
    _DDCRAM_TOP_ADDR,
    _DDCRAM_BOTTOM_ADDR,
} EnumDDCAddrType;

//--------------------------------------------------
// Enumerations of DDC0/1 Select
//--------------------------------------------------
typedef enum
{
    _D0_DDCRAM,
    _D1_DDCRAM,
} EnumD0D1DDCRAMSelect;

//--------------------------------------------------
// Enumerations of DDCCI or Debug Mode
//--------------------------------------------------
typedef enum
{
    _DEBUG_MODE,
    _DDCCI_MODE,
} EnumDDCCIDebugMode;

//--------------------------------------------------
// Enumerations of Repeater Power Actioh
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_REPEATER_POWER_NONE = 0x00,
    _DATA_EXCHANGE_REPEATER_POWER_OFF,
    _DATA_EXCHANGE_REPEATER_POWER_NORMAL,
} EnumDataExchangeRepeaterPowerState;

//--------------------------------------------------
// Enumerations IRQ Type
//--------------------------------------------------
typedef enum
{
    _IRQ_IVS = 0x00,
    _IRQ_DVS,
    _IRQ_DEN_START,
    _IRQ_DEN_STOP,
    _IRQ_IHS_TIMEOUT,
} EnumIRQ;

//--------------------------------------------------
// Enumerations of LED indication
//--------------------------------------------------
typedef enum
{
    _LED_POWER_ON = 0x00,
    _LED_POWER_SEARCH,
    _LED_POWER_ACTIVE,
    _LED_POWER_SAVING,
    _LED_POWER_NOSUPPORT,
    _LED_POWER_NOSUPPORT_SAVING,
    _LED_POWER_OFF,
    _LED_TYPE_1,
    _LED_TYPE_2,
    _LED_TYPE_3,
    _LED_TYPE_4,
    _LED_TYPE_5,
    _LED_TYPE_FLASH,
    _LED_SYSTEM_END,
} EnumLedIndication;

//--------------------------------------------------
// Enumerations of System Clock
//--------------------------------------------------
typedef enum
{
    _EXT_XTAL_CLK,
    _IOSC_CLK,
    _M2PLL_CLK,
    _ECBUS_CLK,
    _LC_TANK_CLK,
} EnumClkSel;

//--------------------------------------------------
// Enumerations of System Data Info
//--------------------------------------------------
typedef enum
{
    _MONITOR_POWER_STATUS,
    _SEARCH_PORT,
    _SOURCE_SCAN_TYPE,
    _MODE_SLOT_INDEX,
    _SSC,
    _DP_HOT_PLUG_DC_OFF_HIGH,
    _HDMI_HOT_PLUG_SUPPORT,
    _HDMI_HOT_PLUG_SUPPORT_TIME,
    _DP_AUX_DIFF_MODE,
    _DP_AUX_ADJR_SETTING,
    _SOURCE_HP_DEFAULT_PORT,
    _SOURCE_HP_AUTO_SEARCH,
    _DP_EDID_SELECT,
    _DP_D0_LANES,
    _DP_D1_LANES,
    _DP_D2_LANES,
    _DP_D6_LANES,
    _COLORIMETRY_SEAMLESS_CHANGE,
    _EDID_D0_SELECT,
    _EDID_D1_SELECT,
    _EDID_D2_SELECT,
    _EDID_D3_SELECT,
    _EDID_D4_SELECT,
    _EDID_D5_SELECT,
    _EDID_D6_SELECT,
    _DP_IRQ_TIME,
    _DP_ILLEGAL_IDLE_PATTERN_CHECK,
} EnumSystemDataItemDataType;

//--------------------------------------------------
// Enumerations of Waiting Events (CR_03)
//--------------------------------------------------
typedef enum
{
    _EVENT_IVS = _BIT0,
    _EVENT_IEN_START = _BIT1,
    _EVENT_IEN_STOP = _BIT2,
    _EVENT_DVS = _BIT3,
    _EVENT_DEN_START = _BIT4,
    _EVENT_DEN_STOP = _BIT5,
    _EVENT_UNDERFLOW = _BIT6,
    _EVENT_OVERFLOW = _BIT7,
    _EVENT_ALL = 0xFF,
} EnumWaitEventType;


//****************************************************************************
// Enumerations of Auto Color
//****************************************************************************
//--------------------------------------------------
// Enumerations of ADC Gain/Offset
//--------------------------------------------------
typedef enum
{
    _ADC_GAIN = 0x00,
    _ADC_OFFSET,
} EnumADCGainOffset;

//--------------------------------------------------
// Enumerations of S/H Gain Operation Mode
//--------------------------------------------------
typedef enum
{
    _SHA_GAIN_CHECK_MODE = 0x00,
    _SHA_GAIN_WRITE_MODE,
} EnumShaGainOptions;

//--------------------------------------------------
// Enumerations of auto-color types
//--------------------------------------------------
typedef enum
{
    _AUTO_TUNE_RGB,
    _AUTO_TUNE_RGB_KNOWNWHITE,
    _AUTO_TUNE_YPBPR,
    _AUTO_CALIBRATE_RGB,
    _AUTO_TUNE_RGB_GAIN_ONLY,
    _AUTO_TUNE_YPBPR_GAIN_ONLY,
} EnumAutoColorType;


//****************************************************************************
// Enumerations of Auto Phase
//****************************************************************************
//--------------------------------------------------
// Enumerations of Hardware Phase Search SOD Method
//--------------------------------------------------
typedef enum
{
    _PHASE_SEARCH_SOD = 0x00,
    _PHASE_SEARCH_WSOD = 0x01,
} EnumAutoPhaseSearchSODMethod;

//--------------------------------------------------
// Enumerations of Hardware Phase Search Step
//--------------------------------------------------
typedef enum
{
    _PHASE_SEARCH_STEP_1 = 0x00,
    _PHASE_SEARCH_STEP_2 = 0x01,
    _PHASE_SEARCH_STEP_4 = 0x02,
    _PHASE_SEARCH_STEP_8 = 0x03,
    _PHASE_SEARCH_STEP_16 = 0x04,
} EnumAutoPhaseSearchStep;

//--------------------------------------------------
// Enumerations of image auto-function measure result status
//--------------------------------------------------
typedef enum
{
    _AUTO_FAIL = _FAIL,
    _AUTO_SUCCESS = _SUCCESS,
    _AUTO_ABORT,
} EnumAutoResult;


//****************************************************************************
// Enumerations of Digital Functions
//****************************************************************************
//--------------------------------------------------
// Enumerations of Digital Functions On/Off/Clock Gated
//--------------------------------------------------
typedef enum
{
    _FUNCTION_OFF,
    _FUNCTION_ON,
    _FUNCTION_CLOCK_GATED,
} EnumFunctionOnOFF;

//--------------------------------------------------
// Enumerations of Digital Functions Double Buffer
//--------------------------------------------------
typedef enum
{
    _DB_APPLY_NONE,
    _DB_APPLY_NO_POLLING,
    _DB_APPLY_POLLING,
} EnumDBApply;

//--------------------------------------------------
// Enumerations of Digital Functions Double Buffer
//--------------------------------------------------
typedef enum
{
    _DB_VS_TRIGGER,
    _DB_ENA_STOP_TRIGGER,
} EnumDBTriggerEvent;

//--------------------------------------------------
// Enumerations of Brightness/Contrast Coefficient Sets
//--------------------------------------------------
typedef enum
{
    _BRIGHTNESS_COEF_A,
    _BRIGHTNESS_COEF_B,
    _CONTRAST_COEF_A,
    _CONTRAST_COEF_B,
    _CONTRAST_COEF_A_2,
    _CONTRAST_COEF_B_2,
} EnumBriConCoefType;

//--------------------------------------------------
// Enumerations of Color Space
//--------------------------------------------------
typedef enum
{
    _COLOR_SPACE_RGB,
    _COLOR_SPACE_YCBCR422,
    _COLOR_SPACE_YCBCR444,
    _COLOR_SPACE_YCBCR420,
    _COLOR_SPACE_YPBPR,
    _COLOR_SPACE_Y_ONLY,
    _COLOR_SPACE_RAW,
} EnumColorSpace;

//****************************************************************************
// Enumerations of Colorimetry
//****************************************************************************
typedef enum
{
    _COLORIMETRY_RGB_SRGB,
    _COLORIMETRY_RGB_ADOBERGB,
    _COLORIMETRY_RGB_XRRGB,
    _COLORIMETRY_RGB_SCRGB,
    _COLORIMETRY_RGB_DCI_P3,
    _COLORIMETRY_RGB_COLOR_PROFILE,
    _COLORIMETRY_YCC_SMPTE_170M,
    _COLORIMETRY_YCC_ITUR_BT601,
    _COLORIMETRY_YCC_ITUR_BT709,
    _COLORIMETRY_YCC_XVYCC601,
    _COLORIMETRY_YCC_XVYCC709,
    _COLORIMETRY_Y_ONLY,
    _COLORIMETRY_RAW,
    _COLORIMETRY_EXT,
    _COLORMETRY_RESERVED,
}EnumColorimetry;

typedef enum
{
    _COLORIMETRY_EXT_RGB_SRGB,
    _COLORIMETRY_EXT_RGB_XRRGB,
    _COLORIMETRY_EXT_RGB_SCRGB,
    _COLORIMETRY_EXT_RGB_ADOBERGB,
    _COLORIMETRY_EXT_RGB_DCI_P3,
    _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE,
    _COLORIMETRY_EXT_RGB_ITUR_BT2020,
    _COLORIMETRY_EXT_YCC_ITUR_BT601,
    _COLORIMETRY_EXT_YCC_ITUR_BT709,
    _COLORIMETRY_EXT_YCC_XVYCC601,
    _COLORIMETRY_EXT_YCC_XVYCC709,
    _COLORIMETRY_EXT_YCC_SYCC601,
    _COLORIMETRY_EXT_YCC_ADOBEYCC601,
    _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL,
    _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL,
    _COLORIMETRY_EXT_Y_ONLY_DICOM_PART14,
    _COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE,
    _COLORIMETRY_EXT_RESERVED,
}EnumColorimetryExt;

//--------------------------------------------------
// Enumerations of YUV2RGB Types
//--------------------------------------------------
typedef enum
{
    _COLOR_CONV_YUV2RGB_ITU601,
    _COLOR_CONV_YUV2RGB_ITU709,
    _COLOR_CONV_YUV2RGB_ITU709_RGBLIMIT,
    _COLOR_CONV_YUV2RGB_ITU601_YUVFULL,
    _COLOR_CONV_YUV2RGB_ITU709_YUVFULL,
    _COLOR_CONV_YUV2RGB_ITU601_8BIT,
    _COLOR_CONV_YUV2RGB_ITU709_8BIT,
    _COLOR_CONV_YUV2RGB_ITU709_RGBLIMIT_8BIT,
    _COLOR_CONV_YUV2RGB_ITU_BT2020_1,
    _COLOR_CONV_YUV2RGB_ITU_BT2020_2,
} EnumColorConvYuv2RgbType;

//--------------------------------------------------
// Enumerations of DCC Table Index
//--------------------------------------------------
typedef enum
{
    _DCC_CONTROL,
    _DCC_TABLE,
    _DCC_END,
} EnumDCCTableIndex;

//--------------------------------------------------
// Enumerations of DCC Read Histo Info Result Option
//--------------------------------------------------
typedef enum
{
    _DCC_S0 = 0,
    _DCC_S1,
    _DCC_S2,
    _DCC_S3,
    _DCC_S4,
    _DCC_S5,
    _DCC_S6,
    _DCC_Y_MAX,
    _DCC_Y_MIN,
} EnumDCCReadOption;

//--------------------------------------------------
// Enumerations of DCC Busy Check Type
//--------------------------------------------------
typedef enum
{
    _DELAY_30US_TIMESCALE = 0x00,
    _DELAY_XMS_TIMESCALE,
} EnumTMDSDdcDebounceType;

//--------------------------------------------------
// Enumerations of Edid Index
//--------------------------------------------------
typedef enum
{
    _EDID_INDEX_0 = 0,
    _EDID_INDEX_1,
    _EDID_INDEX_2,
    _EDID_INDEX_3,
    _EDID_INDEX_4,
    _EDID_INDEX_5,
    _EDID_INDEX_6,
    _EDID_INDEX_7,
    _EDID_INDEX_8,
    _EDID_INDEX_9,
    _EDID_INDEX_10,
    _EDID_INDEX_11,
}EnumEdidSelection;

typedef enum
{
    _HDMI_EDID_EXTERNAL = 0,
    _HDMI_EDID_EMBEDDED,
}EnumHdmiEdidLocation;

//--------------------------------------------------
// Enumerations of DCR Measure Select
//--------------------------------------------------
typedef enum
{
    _MEASURE_AVERAGE,      // R+G+B
    _MEASURE_R,            // R
    _MEASURE_G,            // G
    _MEASURE_B,            // B
    _MEASURE_Y,            // 2R+5G+B
} EnumDCRMeasureSel;

//--------------------------------------------------
// Enumerations for DCR Get Average
//--------------------------------------------------
typedef enum
{
    _DCR_ABOVE_TH1_VAL_TOTAL,
    _DCR_ABOVE_TH2_VAL_TOTAL,
} EnumDCRAverageOption;

//--------------------------------------------------
// Enumerations for DCR Get MaxRGB
//--------------------------------------------------
typedef enum
{
    _DCR_MAX_RGB_8_BIT,
    _DCR_MAX_RGB_10_BIT,
} EnumDCRMaxRGBOption;

//--------------------------------------------------
// Enumerations of DCR Local Dimming Mode Option
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_1X8_MODE,
    _LOCAL_DIMMING_2X8_MODE,
} EnumLocalDimmingHDRMode;

typedef enum
{
    _DCR_LD_ABOVE_TH1_NUM,
    _DCR_LD_ABOVE_TH2_NUM,
} EnumDCRLDAdjOption;

//--------------------------------------------------
// Enumerations of ICM Table Index
//--------------------------------------------------
typedef enum
{
    _ICM_CONTROL,
    _ICM_0,
    _ICM_1,
    _ICM_2,
    _ICM_3,
    _ICM_4,
    _ICM_5,
    _ICM_END = 0xff,
} EnumICMTableIndex;

typedef enum
{
    _SCM_CONTROL,
    _SCM_0,
    _SCM_1,
    _SCM_2,
    _SCM_3,
    _SCM_4,
    _SCM_5,
    _SCM_6,
    _SCM_7,
    _SCM_END = 0xff,
} EnumSCMTableIndex;

//--------------------------------------------------
// Enumerations of Gamma Channel
//--------------------------------------------------
typedef enum
{
    _GAMMA_RED_CHANNEL,
    _GAMMA_GREEN_CHANNEL,
    _GAMMA_BLUE_CHANNEL,
} EnumGammaChannel;

//--------------------------------------------------
// Enumerations of Highlight Window Type
//--------------------------------------------------
typedef enum
{
    _HLW_FULL_WINDOW,
    _HLW_INSIDE_WINDOW,
    _HLW_OUTSIDE_WINDOW,
} EnumHLWType;

//--------------------------------------------------
// Enumerations of Highlight Window IP Selection
//--------------------------------------------------
typedef enum
{
    _IP_SRGB,
    _IP_DCR,
    _IP_SHP_MAIN,
    _IP_SHP_SUB,
    _IP_CONTRAST,
    _IP_GAMMA,
    _IP_3DGAMMA,
    _IP_DCC,
    _IP_UNIFORMITY,
    _IP_IAPSGAIN,
    _IP_ICM,
    _IP_LIVESHOWTM,
} EnumHLWIPSel;

//--------------------------------------------------
// Enumerations of Display calibration
//--------------------------------------------------
typedef enum
{
    _OGC_CAL,
    _OCC_CAL,
    _DICOM_CAL,
    _UNIFORMITY_CAL,
}EnumCaliType;

//--------------------------------------------------
// Enumerations of Highlight Window Set Selection
//--------------------------------------------------
typedef enum
{
    _HLW_ALLSETA,
    _HLW_INSIDEA_OUTSIDEB,
    _HLW_INSIDEB_OUTSIDEA,
    _HLW_ALLSETB,
} EnumHLWSetSel;

//--------------------------------------------------
// Enumerations of Highlight Window Active Select
//--------------------------------------------------
typedef enum
{
    _BRI_CON_A_ON_FULL_WINDOW,
    _BRI_CON_B_ON_INSIDE_WINDOW,
    _BRI_CON_A_ON_HLW_OUTSIDE_WINDOW,
    _BRI_CON_B_ON_INSIDE_A_ON_HLW_OUTSIDE_WINDOW,
} EnumBriConHLWType;

//--------------------------------------------------
// Enumerations of OCC Options
//--------------------------------------------------
typedef enum
{
    _PCM_SRGB,
    _PCM_ADOBE_RGB,
    _PCM_USER_DEFINE,
    _PCM_EBU_MODE,
    _PCM_SOFT_PROFT,
    _PCM_REC_709,
    _PCM_DCI_P3,
    _PCM_SMPTE_C,
    _PCM_USER_DEFINE_2,
    _PCM_USER_DEFINE_3,
    _PCM_USER_DEFINE_4,
    _PCM_USER_DEFINE_5,
    _PCM_USER_DEFINE_6,
    _PCM_DISPLAY_P3,
    _PCM_HDR_2084,
    _TOTAL_COLORSPACE_NUM,
    _PCM_USER_MODE = _TOTAL_COLORSPACE_NUM,
    _PCM_BYPASS,
} EnumPCMType;

//--------------------------------------------------
// Enumerations of OCC/OGC Options
//--------------------------------------------------
typedef enum
{
    _OGC_GAMMA1_TYPE = 0,
    _OGC_GAMMA2_TYPE,
    _OGC_GAMMA3_TYPE,
    _OGC_GAMMA4_TYPE,
    _OGC_GAMMA5_TYPE,
    _OGC_GAMMA6_TYPE,
    _OGC_TOTAL_GAMMA_TYPE,
} EnumOGCTypeSelect;

typedef enum
{
    _OGC_NORMAL_TYPE = 0,
    _OGC_MAX_BACKLIGHT_TYPE,
} EnumOGCModeSelect;

typedef enum
{
    _SDR_SRGB,
    _SDR_ADOBE_RGB,
    _SDR_EBU_MODE,
    _SDR_REC_709,
    _SDR_DCI_P3,
    _SDR_SMPTE_C,
    _SDR_DISPLAYP3,
    _SDR_NONE_OCC,
} EnumSDRPCMStatus;

typedef enum
{
    _SDR_OGC_CASE_1,
    _SDR_OGC_CASE_2,
    _SDR_OGC_CASE_3,
    _SDR_OGC_CASE_4,
    _SDR_OGC_CASE_5,
    _SDR_NONE_OGC,
} EnumSDROGCStatus;

typedef enum
{
    _SDR_CALIBRATION_BY_OGC_TOOL,
    _SDR_NONE_CALIBRATION_BY_OGC_TOOL,
} EnumSDRCalibrationType;

//--------------------------------------------------
// Enumerations of Quantization Range (RGB)
//--------------------------------------------------
typedef enum
{
    _RGB_QUANTIZATION_FULL_RANGE = 0x00,
    _RGB_QUANTIZATION_LIMIT_RANGE = 0x01,
    _RGB_QUANTIZATION_DEFAULT_RANGE = 0x02,
    _RGB_QUANTIZATION_RESERVED = 0x03,
} EnumColorRGBQuantization;

typedef enum
{
    _AVI_RGB_QUANTIZATION_DEFAULT = 0x00,
    _AVI_RGB_QUANTIZATION_LIMITED = 0x01,
    _AVI_RGB_QUANTIZATION_FULL = 0x02,
    _AVI_RGB_QUANTIZATION_RESERVED = 0x03,
} EnumAviInfoRGBQuantization;

//--------------------------------------------------
// Definitions of AVI Info Content Types
//--------------------------------------------------
typedef enum
{
    _AVI_COLOR_SPACE_RGB = 0x00,
    _AVI_COLOR_SPACE_YCC_422 = 0x01,
    _AVI_COLOR_SPACE_YCC_444 = 0x02,
    _AVI_COLOR_SPACE_YCC_420 = 0x03,
    _AVI_COLOR_SPACE_RESERVED = 0x04,
} EnumAviInfoColorSpace;

typedef enum
{
    _AVI_COLORIMETRY_NONE = 0x00,
    _AVI_COLORIMETRY_ITU601 = 0x01,
    _AVI_COLORIMETRY_ITU709 = 0x02,
    _AVI_COLORIMETRY_EXTENDED = 0x03,
} EnumAviInfoColorimetry;

typedef enum
{
    _AVI_COLORIMETRY_EXT_XVYCC601 = 0x00,
    _AVI_COLORIMETRY_EXT_XVYCC709 = 0x01,
    _AVI_COLORIMETRY_EXT_SYCC601 = 0x02,
    _AVI_COLORIMETRY_EXT_ADOBEYCC601 = 0x03,
    _AVI_COLORIMETRY_EXT_ADOBERGB = 0x04,
    _AVI_COLORIMETRY_EXT_ITUR_BT2020_1 = 0x05,
    _AVI_COLORIMETRY_EXT_ITUR_BT2020_2 = 0x06,
    _AVI_COLORIMETRY_EXT_RESERVED = 0x07,
} EnumAviInfoColorimetryExt;

typedef enum
{
    _AVI_SCAN_INFO_NONE = 0x00,
    _AVI_SCAN_INFO_OVERSCAN = 0x01,
    _AVI_SCAN_INFO_UNDERCAN = 0x02,
    _AVI_SCAN_INFO_RESERVED = 0x03,
} EnumAviInfoScanInfo;

typedef enum
{
    _AVI_IT_CONTENT_NONE = 0x00,
    _AVI_IT_CONTENT_TRUE = 0x01,
} EnumAviInfoITContent;

//--------------------------------------------------
// Enumerations of Quantization Range (YCC)
//--------------------------------------------------
typedef enum
{
    _YCC_QUANTIZATION_LIMIT_RANGE = 0x00,
    _YCC_QUANTIZATION_FULL_RANGE = 0x01,
    _YCC_QUANTIZATION_RESERVED = 0x02,
} EnumColorYCCQuantization;

typedef enum
{
    _AVI_YCC_QUANTIZATION_LIMITED = 0x00,
    _AVI_YCC_QUANTIZATION_FULL = 0x01,
} EnumAviInfoYCCQuantization;

//--------------------------------------------------
// Enumerations of AVI Pixel Repetition
//--------------------------------------------------
typedef enum
{
    _AVI_PIXEL_REPETITION_0 = 0x00,
    _AVI_PIXEL_REPETITION_1 = 0x01,
    _AVI_PIXEL_REPETITION_2 = 0x02,
    _AVI_PIXEL_REPETITION_3 = 0x03,
    _AVI_PIXEL_REPETITION_4 = 0x04,
    _AVI_PIXEL_REPETITION_5 = 0x05,
    _AVI_PIXEL_REPETITION_6 = 0x06,
    _AVI_PIXEL_REPETITION_7 = 0x07,
    _AVI_PIXEL_REPETITION_8 = 0x08,
    _AVI_PIXEL_REPETITION_9 = 0x09,
} EnumAviInfoPixelRepetition;

//--------------------------------------------------
// Enumerations of SRGB Options
//--------------------------------------------------
typedef enum
{
    _SRGB_NORMAL_MODE,
    _SRGB_LUT_MODE,
} EnumsRGBLut;

typedef enum
{
    _SRGB_BEFORE_OG,
    _SRGB_BEFORE_CTS,
} EnumsRGBSwap;

typedef enum
{
    _SRGB_1_BIT_SHIFT_LEFT,
    _SRGB_2_BIT_SHIFT_LEFT,
    _SRGB_3_BIT_SHIFT_LEFT,
    _SRGB_0_BIT_SHIFT_LEFT,
} EnumSrgbPrecision;

//--------------------------------------------------
// Enumerations of Y Peaking
//--------------------------------------------------
typedef enum
{
    _YPEAKING_GAIN_MODE,
    _YPEAKING_TABLE_MODE,
} EnumYpeakingMode;

typedef enum
{
    _YPEAKING_N_DIV32,
    _YPEAKING_N_DIV64,
    _YPEAKING_NO_DIV,
} EnumYpeakingCoeffResolution;

//--------------------------------------------------
// Enumerations of Panel Uniformity
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_TYPE1 = 0,  // gamma 1.8
    _UNIFORMITY_TYPE2,      // gamma 2.0
    _UNIFORMITY_TYPE3,      // gamma 2.2
    _UNIFORMITY_TYPE4,      // gamma 2.4
    _UNIFORMITY_TYPE5,      // srgb
    _UNIFORMITY_TYPE6,      // adobe rgb
} EnumUniformityTypeSelect;

typedef enum
{
    _UNIFORMITY_1LEVEL_MODE = 1,
    _UNIFORMITY_4LEVEL_MODE = 4,
} EnumUniformityLevelSelect;

typedef enum
{
    _UNIFORMITY_OGC_MODE = 0,
    _UNIFORMITY_PCM_MODE,
} EnumUniformityModeSelect;

typedef enum
{
    _UNIFORMITY_SRAM1 = 0,
    _UNIFORMITY_SRAM2,
} EnumUniformitySramSelect;

//****************************************************************************
// Enumerations of Type-C
//****************************************************************************
//--------------------------------------------------
// Enumerations of Type-C Data Role
//--------------------------------------------------
typedef enum
{
    _TYPE_C_UFP_U = 0,
    _TYPE_C_DFP_U = 1,
}EnumTypeCDataRole;

//--------------------------------------------------
// Enumerations of Type-C Power Role
//--------------------------------------------------
typedef enum
{
    _TYPE_C_POWER_SNK = 0x00,
    _TYPE_C_POWER_SRC = 0x01,
    _TYPE_C_POWER_ROLE_NONE = 0xFF,
}EnumTypeCPowerRole;

//--------------------------------------------------
// Enumerations of Type-C DP Alt Mode Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ALT_MODE_NOT_READY = 0,
    _TYPE_C_ALT_MODE_READY = 1,
}EnumTypeCAltModeStatus;

//--------------------------------------------------
// Definitions of Type-C Multi-Function Preferred Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_MULTI_FUNC_NOT_PREFER = 0,
    _TYPE_C_MULTI_FUNC_PREFER = 1,
}EnumTypeCMultiFuncStatus;

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_NONE = 0x00,
    _TYPE_C_PIN_ASSIGNMENT_C = 0x04,
    _TYPE_C_PIN_ASSIGNMENT_D = 0x08,
    _TYPE_C_PIN_ASSIGNMENT_E = 0x10,
    _TYPE_C_PIN_ASSIGNMENT_F = 0x20,
}EnumTypeCPinCfgType;

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_CAP_NONE = 0x00,
    _TYPE_C_PIN_ASSIGNMENT_CAP_C = 0x04,
    _TYPE_C_PIN_ASSIGNMENT_CAP_CD = 0x0C,
    _TYPE_C_PIN_ASSIGNMENT_CAP_CE = 0x14,
    _TYPE_C_PIN_ASSIGNMENT_CAP_CDE = 0x1C,
    _TYPE_C_PIN_ASSIGNMENT_CAP_DEFAULT,
}EnumTypeCPinCfgCapType;

//--------------------------------------------------
// Enumerations of Type-C Comunication Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_USER_PORT_CTRL_COMMUNICATION_FAIL = 0,
    _TYPE_C_USER_PORT_CTRL_COMMUNICATION_SUCCESS = 1,
    _TYPE_C_USER_PORT_CTRL_OTHER_FAIL = 2,
}EnumTypeCUserPortCtrlFailureType;

//--------------------------------------------------
// Enumerations of External Port Controller Reconnect Support
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PORT_CTRL_RECONNECT_NOT_SUPPORT = _FAIL,
    _TYPE_C_PORT_CTRL_RECONNECT_SUPPORT = _SUCCESS,
}EnumTypeCPortCtrlReconnectSupport;

//--------------------------------------------------
// Enumerations of Type-C U3 Mode Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_U3_ON = 0,
    _TYPE_C_U3_OFF = 1,
}EnumTypeCU3ModeType;

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment E Support Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON = 0,
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF = 1,
}EnumTypeCPinAssignmentESupportStatus;

//--------------------------------------------------
// Enumerations of Hub DSP Device Detect
//--------------------------------------------------
typedef enum
{
    _HUB_DSP_DEVICE_NO_CHANGE = 0x00,
    _HUB_DSP_DEVICE_CHANGE = 0x01,
}EnumHubDspDetectStatus;

typedef enum
{
    _HUB_DSP0 = 0x00,
    _HUB_DSP1 = 0x01,
    _HUB_DSP2 = 0x02,
    _HUB_DSP3 = 0x03,
}EnumHubDsp;

//--------------------------------------------------
// Enumerations of Hub Input Port
//--------------------------------------------------
typedef enum
{
    _HUB_UFP_TYPE_C_INPUT_PORT = 0x00,
    _HUB_UFP_NOT_TYPE_C_INPUT_PORT = 0x01,
}EnumHubInputPort;

//--------------------------------------------------
// Enumerations of Type-C Port Controller Power On Reconnect Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PORT_CTRL_NO_RECONNECT = 0x00,
    _TYPE_C_PORT_CTRL_RECONNECT = 0x01,
}EnumTypeCPortCtrlReconnectStatus;

//--------------------------------------------------
// Enumerations of Type-C Capability Change Info
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_CAP_CHG = _BIT0,
    _TYPE_C_SRC_CAP_CHG = _BIT1,
    _TYPE_C_HUB_INPUT_SWITCH_CHG = _BIT2,
    _TYPE_C_ALL_STATUS_CHG = 0xFF,
}EnumTypeCCapChgStatus;

//--------------------------------------------------
// Enumerations of Type-C Adjust Src Cap When Hub Device Count Change
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HUB_ADJ_SRC_CAP_ENABLE = 0x00,
    _TYPE_C_HUB_ADJ_SRC_CAP_DISABLE = 0x01,
}EnumTypeCHubAdjSrcCap;

//--------------------------------------------------
// Enumerations of Type-C Get 5400 Info
//--------------------------------------------------
typedef enum
{
    _5400_CC_ATTACH = 0x00,
    _5400_ALT_MODE_READY = 0x01,
    _5400_DATA_ROLE = 0x02,
    _5400_PIN_ASSIGNMENT = 0x03,
    _5400_CONNECT_FUJITSU = 0x04,
    _5400_CABLE_VID = 0x05,
    _5400_CABLE_PID = 0x06,
    _5400_POWER_ROLE = 0x07,
    _5400_LENOVO_ALT_MODE_STATUS = 0x08,
    _5400_LENOVO_DEVICE_TYPE = 0x09,
    _5400_LENOVO_SYSTEM_EVENT = 0x0A,
}Enum5400InfoType;

//--------------------------------------------------
// Enumerations of Type-C Embedded Port Ctrl PDO from User (Src/Snk Cap)
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PDO_FROM_KERNEL = 0x00,
    _TYPE_C_PDO_FROM_USER = 0x01,
}EnumTypeCEmbPdoReference;

//--------------------------------------------------
// Enumerations of Type-C Embedded Port Ctrl RDO from User (Request)
//--------------------------------------------------
typedef enum
{
    _TYPE_C_RDO_FROM_KERNEL = 0x00,
    _TYPE_C_RDO_FROM_USER = 0x01,
}EnumTypeCEmbRdoReference;

//--------------------------------------------------
// Enumerations of Type-C PDO Count from User
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PDO_NUM_1 = 0x01,
    _TYPE_C_PDO_NUM_2 = 0x02,
    _TYPE_C_PDO_NUM_3 = 0x03,
    _TYPE_C_PDO_NUM_4 = 0x04,
    _TYPE_C_PDO_NUM_5 = 0x05,
    _TYPE_C_PDO_NUM_6 = 0x06,
    _TYPE_C_PDO_NUM_7 = 0x07,
}EnumTypeCPdoNumber;

//--------------------------------------------------
// Enumerations of Type-C PDO Types
//--------------------------------------------------
typedef enum
{
    _PD_FIX_SUPPLY_PDO = 0x00,     // Fix Supply PDO
    _PD_RESERVED_BAT_PDO = 0x01,   // Battery Supply PDO
    _PD_RESERVED_VAR_PDO = 0x02,   // Variable Supply PDO
    _PD_3_PROGRAMMABLE_PDO = 0x03, // Programmable PDO (Only for PD3.0)
    _PD_NONE_SETTING_PDO = 0xFF,   // None Setting PDO (For PMIC Initial State)
}EnumPDPdoType;

//--------------------------------------------------
// Enumerations of Embedded Type-C System Event
//--------------------------------------------------
typedef enum
{
    _PD_SYS_EVENT_NONE = 0x00,              // No Request Event to Embedded PD Ctrl
    _PD_SYS_EVENT_SEND_SRC_CAP = _BIT0,     // Request Embedded PD Ctrl to Send Src Cap
    _PD_SYS_EVENT_SEND_REQUEST = _BIT1,     // Request Embedded PD Ctrl to Send Request
    _PD_SYS_EVENT_POWER_OCP = _BIT2,        // Inform Embedded PD Ctrl of OCP Triggered
    _PD_SYS_EVENT_POWER_OVP = _BIT3,        // Inform Embedded PD Ctrl of OVP Triggered
    _PD_SYS_EVENT_ERROR_RECOVERY = _BIT4,   // Request Embedded PD Ctrl to Do Error Recovery
    _PD_SYS_EVENT_ALL = 0xFF,              // All System Event
}EnumPDSysEvent;

//--------------------------------------------------
// Enumerations of Type-C PMIC Contorl
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_CONTROL_FAIL = 0,
    _TYPE_C_PMIC_CONTROL_SUCCESS = 1,
} EnumTypeCPmicControlResult;

//--------------------------------------------------
// Enumerations of Type-C PMIC Direction
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_DIRECTION_SNK = 0,
    _TYPE_C_PMIC_DIRECTION_SRC = 1,
} EnumTypeCPmicDirection;

//--------------------------------------------------
// Enumerations of Type-C PMIC Discharge
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_DISCHARGE_DISABLE = 0,
    _TYPE_C_PMIC_DISCHARGE_ENABLE = 1,
} EnumTypeCPmicDischarge;

//--------------------------------------------------
// Enumerations of Type-C PMIC Discharge
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_SWITCH_CONTROL_DISABLE = 0,
    _TYPE_C_PMIC_SWITCH_CONTROL_ENABLE = 1,
} EnumTypeCPmicSwitchControl;

//--------------------------------------------------
// Enumerations of Type-C PMIC Operation Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PMIC_CV_MODE_OPERATION = 0x00,
    _TYPE_C_PMIC_CC_MODE_OPERATION = 0x01,
    _TYPE_C_PMIC_TRANSITION_MODE = 0x02,
    _TYPE_C_PMIC_NONE_MODE_OPERATION = 0xFF,
} EnumTypeCPmicOperationMode;

//--------------------------------------------------
// Struct for Type-C Source/Sink Capability Content for User
//--------------------------------------------------
typedef struct
{
    EnumPDPdoType enumPdoType : 8;
    // -----------------------------
    BYTE ucMaxVoltage;  // Unit = 100mV
    BYTE ucMinVoltage;  // Unit = 100mV
    BYTE ucMaxCurrent;  // Unit =  50mA
}StructTypeCUserPDO;

typedef struct
{
    BYTE ucOcpCurRatio; // Unit = %
}StructTypeCUserProtectInfo;

//--------------------------------------------------
// Struct for Type-C Request Content for User
//--------------------------------------------------
typedef struct
{
    EnumTypeCPdoNumber enumObjPos;  // Object Position
    // -----------------------------
    WORD usReqInfo1;            // Fix RDO (Op. Cur in 10mA) / PPS RDO (Vol in 20mV)
    // -----------------------------
    WORD usReqInfo2;            // Fix RDO (Max. Cur in 10mA) / PPS RDO (Op. Cur in 50mA)
    // -----------------------------
    BYTE b1CapMismatch : 1;     // Capability Mismatch Flag
    BYTE b1GiveBack : 1;        // Give Back Flag
}StructTypeCUserRDO;

//--------------------------------------------------
// Enumeration of PD Check PDO Change
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PDO_NO_CHANGE = 0x0,
    _TYPE_C_PDO_CHANGE = 0x1,
}EnumPdoCheck;

//--------------------------------------------------
// Enumerations of Type-C Lenovo Alt Mode Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_ALT_MODE_NOT_READY = 0,
    _TYPE_C_LENOVO_ALT_MODE_READY = 1,
}EnumTypeCLenovoAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C Lenovo Device Type
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_DEVICE_TYPE_RESERVED = 0x00,
    _TYPE_C_LENOVO_NOTEBOOK = 0x01,
    _TYPE_C_LENOVO_DOCKING = 0x02,
    _TYPE_C_LENOVO_POWER_ADAPTER = 0x03,
    _TYPE_C_LENOVO_DESKTOP_PC = 0x04,
    _TYPE_C_LENOVO_MONITOR = 0x05,
    _TYPE_C_LENOVO_UPS = 0x06,
    _TYPE_C_LENOVO_DEVICE_TYPE_NONE = 0xFF,
}EnumTypeCLenovoDeviceType;

//--------------------------------------------------
// Enumeration of Type-C Lenovo Alt Mode Docking Power Switch
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_DOCK_POWER_SWITCH_NONE = 0x00,
    _TYPE_C_LENOVO_DOCK_POWER_BUTTON_MAKE = 0x01,
    _TYPE_C_LENOVO_DOCK_POWER_BUTTON_BREAK = 0x02,
}EnumTypeCLenovoDockPowerSwitch;

//--------------------------------------------------
// Enumeration of Type-C Lenovo Alt Mode System Power Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_SYS_DC_MODE = 0x00,
    _TYPE_C_LENOVO_SYS_AC_MODE = 0x01,
}EnumTypeCLenovoSysPowerMode;

//--------------------------------------------------
// Enumeration of Type-C Lenovo Alt Mode System State
//--------------------------------------------------
typedef enum
{
    _TYPE_C_LENOVO_SYS_STATE_NONE = 0x00,
    _TYPE_C_LENOVO_SYS_S0 = 0x01,
    _TYPE_C_LENOVO_SYS_S0I3 = 0x02,
    _TYPE_C_LENOVO_SYS_S3 = 0x03,
    _TYPE_C_LENOVO_SYS_S4 = 0x04,
    _TYPE_C_LENOVO_SYS_S5 = 0x05,
}EnumTypeCLenovoSysState;

//--------------------------------------------------
// Struct for Type-C Lenovo Alt Mode Docking Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCLenovoDockPowerSwitch enumDockingPowerSwitch;
    BYTE b1DockingWolRequest : 1;
    BYTE b1DockingEvent : 1;
    BYTE b4DockingReserved : 4;
}StructTypeCLenovoDockEvent;

//--------------------------------------------------
// Struct for Type-C Lenovo Alt Mode System Event (Including System Acknowledge)
//--------------------------------------------------
typedef struct
{
    EnumTypeCLenovoSysPowerMode enumSystemPowerMode;
    EnumTypeCLenovoSysState enumSystemState;
    BYTE b1SystemEvent : 1;
    BYTE b3SystemReserved : 3;
    BYTE ucSystemAcknowlegde;       // [7:4] Reserved, [3] Power Button Break, [2] Power Button Make, [1] WoL, [0] Event Acknowledge
}StructTypeCLenovoSysEvent;

//--------------------------------------------------
// Enumeration of Type-C Acer Alt Mode Ready
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_ALT_MODE_NOT_READY = 0,
    _TYPE_C_ACER_ALT_MODE_READY = 1,
}EnumTypeCAcerAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C Acer Alt Mode User Event Busy Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_USER_EVENT_NOT_BUSY = 0,
    _TYPE_C_ACER_USER_EVENT_BUSY = 1,
}EnumTypeCAcerBusyStatus;

//--------------------------------------------------
// Enumeration of Type-C Acer User Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_USER_EVENT_NONE = 0x00,
    _TYPE_C_ACER_USER_EVENT_ATTENTION = _BIT0,
    _TYPE_C_ACER_USER_EVENT_ALL = 0xFF,
}EnumTypeCAcerUserEvent;

//--------------------------------------------------
// Enumeration of Type-C Acer System Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_ACER_SYS_EVENT_NONE = 0x00,
    _TYPE_C_ACER_SYS_EVENT_STATUS_REQ = _BIT0,
    _TYPE_C_ACER_SYS_EVENT_ALL = 0xFF,
}EnumTypeCAcerSysEvent;

//--------------------------------------------------
// Struct for Type-C Acer Alt Mode User Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCAcerUserEvent enumEvent;
    BYTE pucVdmData[24];
    BYTE b3VdmCnt : 3;
}StructTypeCAcerUserEvent;

//--------------------------------------------------
// Struct for Type-C Acer Alt Mode System Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCAcerSysEvent enumEvent;
    BYTE pucVdmData[24];
    BYTE b3VdmCnt : 3;
}StructTypeCAcerSysEvent;

//--------------------------------------------------
// Enumeration of Type-C Hp Alt Mode Ready
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_ALT_MODE_NOT_READY = 0,
    _TYPE_C_HP_ALT_MODE_READY = 1,
}EnumTypeCHpAltModeStatus;

//--------------------------------------------------
// Enumerations of Type-C Hp Alt Mode User Event Busy Result
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_USER_EVENT_NOT_BUSY = 0,
    _TYPE_C_HP_USER_EVENT_BUSY = 1,
}EnumTypeCHpBusyStatus;

//--------------------------------------------------
// Enumeration of Type-C Hp User Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_USER_EVENT_NONE = 0x00,
    _TYPE_C_HP_USER_EVENT_ATTEN_VWIRE = _BIT0,
    _TYPE_C_HP_USER_EVENT_ATTEN_CONFIG = _BIT1,
    _TYPE_C_HP_USER_EVENT_ATTEN_DATA = _BIT2,
    _TYPE_C_HP_USER_EVENT_ATTEN_DISCONNECT = _BIT3,
    _TYPE_C_HP_USER_EVENT_SET_VWIRE_SAMPLE_ACK = _BIT4,
    _TYPE_C_HP_USER_EVENT_ALL = 0xFF,
}EnumTypeCHpUserEvent;

//--------------------------------------------------
// Enumeration of Type-C Hp System Event
//--------------------------------------------------
typedef enum
{
    _TYPE_C_HP_SYS_EVENT_NONE = 0x00,
    _TYPE_C_HP_SYS_EVENT_SET_CONFIG_REQ = _BIT0,
    _TYPE_C_HP_SYS_EVENT_GET_CONFIG_REQ = _BIT1,
    _TYPE_C_HP_SYS_EVENT_SET_VWIRE_REQ = _BIT2,
    _TYPE_C_HP_SYS_EVENT_GET_VWIRE_REQ = _BIT3,
    _TYPE_C_HP_SYS_EVENT_SET_DATA_REQ = _BIT4,
    _TYPE_C_HP_SYS_EVENT_GET_DATA_REQ = _BIT5,
    _TYPE_C_HP_SYS_EVENT_CMD_REQ = _BIT6,
    _TYPE_C_HP_SYS_EVENT_ALL = 0xFF,
}EnumTypeCHpSysEvent;

//--------------------------------------------------
// Struct for Type-C Hp Alt Mode User Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCHpUserEvent enumEvent;
    BYTE pucVdmData[20];
    BYTE b3VdmCnt : 3;
}StructTypeCHpUserEvent;

//--------------------------------------------------
// Struct for Type-C Hp Alt Mode System Event
//--------------------------------------------------
typedef struct
{
    EnumTypeCHpSysEvent enumEvent;
    BYTE pucVdmData[20];
    BYTE b3VdmCnt : 3;
}StructTypeCHpSysEvent;

//****************************************************************************
// Enumerations of USB3 Retimer
//****************************************************************************
//--------------------------------------------------
// Enumerations of USB Support Under PD
//--------------------------------------------------
typedef enum
{
    _USB3_PD_ENABLE = 0x01,
    _USB2_PD_ENABLE = 0x02,
    _USB_PD_DISABLE = 0x03,
}EnumUSBPDSupportStatus;

//--------------------------------------------------
// Enumerations of USB Support Under PS
//--------------------------------------------------
typedef enum
{
    _USB3_PS_ENABLE = 0x01,
    _USB2_PS_ENABLE = 0x02,
    _USB_PS_DISABLE = 0x03,
}EnumUSBPSSupportStatus;

//****************************************************************************
// Enumerations of Billboard
//****************************************************************************
typedef enum
{
    _TYPE_C_BB_DISABLE = 0x00,
    _TYPE_C_BB_ENABLE = 0x01,
}EnumBillboardCtrl;

//****************************************************************************
// Enumerations of DP
//****************************************************************************
//--------------------------------------------------
// Enumerations of DP Link Training Type
//--------------------------------------------------
typedef enum
{
    _DP_NORMAL_LT = 0x00,
    _DP_FAKE_LT,
} EnumDpLinkTrainingType;

//--------------------------------------------------
// Enumerations of DP Fifo Check Condition
//--------------------------------------------------
typedef enum
{
    _DP_FIFO_DELAY_CHECK = 0x00,
    _DP_FIFO_POLLING_CHECK,
} EnumDpFifoCheckCondition;

//--------------------------------------------------
// Enumerations of DP HS Tracking Type
//--------------------------------------------------
typedef enum
{
    _DP_HS_TRACKING_HW_MODE = 0x00,
    _DP_HS_TRACKING_FW_MODE,
} EnumDpHSTrackingType;

//--------------------------------------------------
// Enumerations of DP Sink Reveive Port
//--------------------------------------------------
typedef enum
{
    _DP_SINK_REVEICE_PORT0 = 0x00,
    _DP_SINK_REVEICE_PORT1,
} EnumDpSinkReceivePort;

//--------------------------------------------------
// Enumerations of DP Sink Status
//--------------------------------------------------
typedef enum
{
    _DP_SINK_OUT_OF_SYNC = 0x00,
    _DP_SINK_IN_SYNC,
} EnumDpSinkStatus;

//--------------------------------------------------
// Enumerations of DP Hot Plug Assert Type
//--------------------------------------------------
typedef enum
{
    _DP_HPD_LOW_RESET_AUX, // 1st priority
    _DP_HPD_LOW,
    _DP_MST_LONG_HPD_EVENT,
    _DP_HDCP_LONG_HPD_EVENT,
    _DP_LONG_HPD_EVENT,
    _DP_HBR2_MARGIN_LINK_HPD_EVENT,
    _DP_HPD_ASSERTED,
    _DP_HPD_NONE = 0xFF,
} EnumDpHotPlugAssertType;

//--------------------------------------------------
// Enumerations of DP Version Type
//--------------------------------------------------
typedef enum
{
    _DP_VERSION_1_0 = 0x10,
    _DP_VERSION_1_1 = 0x11,
    _DP_VERSION_1_2 = 0x12,
    _DP_VERSION_1_3 = 0x13,
    _DP_VERSION_1_4 = 0x14,
} EnumDpVersionType;

//--------------------------------------------------
// Definitions of DP Lane
//--------------------------------------------------
typedef enum
{
    _DP_LANE_0,
    _DP_LANE_1,
    _DP_LANE_2,
    _DP_LANE_3,
} EnumDpLane;

//--------------------------------------------------
// Definitions of DP Link Rate
//--------------------------------------------------
typedef enum
{
    _DP_LINK_NONE = 0x00,
    _DP_LINK_RBR = 0x06,
    _DP_LINK_HBR = 0x0A,
    _DP_LINK_HBR2 = 0x14,
    _DP_LINK_HBR3 = 0x1E,
    _DP_LINK_HBR10G = 0x25,
} EnumDpLinkRate;

//--------------------------------------------------
// Definitions of DP TRAINING_AUX_RD_INTERVAL
//--------------------------------------------------
typedef enum
{
    _DP_LT_AUX_RD_INTVL_EQ_400US = 0x00,
    _DP_LT_AUX_RD_INTVL_EQ_4MS = 0x01,
    _DP_LT_AUX_RD_INTVL_EQ_8MS = 0x02,
    _DP_LT_AUX_RD_INTVL_EQ_12MS = 0x03,
    _DP_LT_AUX_RD_INTVL_EQ_16MS = 0x04,
} EnumDpLTAuxRdIntvlEq;

//--------------------------------------------------
// Definitions of DP Lane Count
//--------------------------------------------------
typedef enum
{
    _DP_LINK_1_LANE = 0x01,
    _DP_LINK_2_LANE = 0x02,
    _DP_LINK_4_LANE = 0x04,
} EnumDpLaneCount;

//--------------------------------------------------
// Definitions of DP Voltage Swing Level
//--------------------------------------------------
typedef enum
{
    _DP_LINK_VOLTAGE_SWING_LEVEL_0,
    _DP_LINK_VOLTAGE_SWING_LEVEL_1,
    _DP_LINK_VOLTAGE_SWING_LEVEL_2,
    _DP_LINK_VOLTAGE_SWING_LEVEL_3,
} EnumDpVoltageSwingLevel;

//--------------------------------------------------
// Definitions of DP Pre-emphasis Level
//--------------------------------------------------
typedef enum
{
    _DP_LINK_PREEMPHASIS_LEVEL_0,
    _DP_LINK_PREEMPHASIS_LEVEL_1,
    _DP_LINK_PREEMPHASIS_LEVEL_2,
    _DP_LINK_PREEMPHASIS_LEVEL_3,
} EnumDpPreEmphasisLevel;

//--------------------------------------------------
// Definitions of DP Power State
//--------------------------------------------------
typedef enum
{
    _DP_POWER_NORMAL = 0x00,
    _DP_POWER_DOWN,
    _DP_POWER_DOWN_WITH_AUX,
} EnumDpPowerState;

//--------------------------------------------------
// Enumerations of FREESYNC Support
//--------------------------------------------------
typedef enum
{
    _FREESYNC_SUPPORT_OFF = 0x00,
    _FREESYNC_SUPPORT_ON,
} EnumFreeSyncSupport;

//--------------------------------------------------
// Enumerations of MST Rx Port
//--------------------------------------------------
typedef enum
{
    _DP_MST_NO_PORT,
    _DP_MST_RX0_PORT,
    _DP_MST_RX1_PORT,
    _DP_MST_RX6_PORT,
    _DP_MST_AUTO_PORT,
} EnumDPMSTPort;

//--------------------------------------------------
// Enumerations of MST Info Backup
//--------------------------------------------------
typedef enum
{
    _DP_MST_BACKUP_INFO,
    _DP_MST_BACKUP_INFO_RESET,
    _DP_MST_BACKUP_INFO_RESTORE,
} EnumDpMstBackup;

//--------------------------------------------------
// Enumerations of DP Tx Link Config by User
//--------------------------------------------------
typedef enum
{
    _DP_TX_CONFIG_NONE = 0x00,
    _DP_TX_V11_1LANE_RBR = 0x01,
    _DP_TX_V11_2LANE_RBR = 0x02,
    _DP_TX_V11_4LANE_RBR = 0x03,
    _DP_TX_V11_1LANE_HBR = 0x04,
    _DP_TX_V11_2LANE_HBR = 0x05,
    _DP_TX_V11_4LANE_HBR = 0x06,
    _DP_TX_V12_1LANE_HBR2 = 0x07,
    _DP_TX_V12_2LANE_HBR2 = 0x08,
    _DP_TX_V12_4LANE_HBR2 = 0x09,
} EnumDpTxConfig;

//--------------------------------------------------
// Enumerations of Dp Edid Port
//--------------------------------------------------
typedef enum
{
    _D0_DP_EDID,
    _D1_DP_EDID,
    _D2_DP_EDID,
    _DP_TX_EDID,
    _NO_PORT_EDID,
} EnumDpEdidPort;

//--------------------------------------------------
// Enumerations of Display DP Tx
//--------------------------------------------------
typedef enum
{
    _DISPLAY_DP_TX_LEVEL_0 = 0x00,
    _DISPLAY_DP_TX_LEVEL_1,
    _DISPLAY_DP_TX_LEVEL_2,
    _DISPLAY_DP_TX_LEVEL_3,
} EnumDisplayDPTxSignalLevel;

//****************************************************************************
// Enumerations of Measure
//****************************************************************************

//--------------------------------------------------
// Enumerations of AutoFunction Measure Field Select
//--------------------------------------------------
typedef enum
{
    _EVEN_FIELD_MEASURE = 0x00,
    _ODD_FIELD_MEASURE = 0x01,
    _NORMAL_MEASURE = 0x02,
} EnumMeasureFieldSelect;

//--------------------------------------------------
// Enumerations of AutoFunction Measure Boundary Type
//--------------------------------------------------
typedef enum
{
    _FULL_BOUNDARY = 0x00,
    _OVERSCAN_BOUNDARY = 0x01,
} EnumMeasureBoundType;

//****************************************************************************
// Enumerations of Memory
//****************************************************************************
//--------------------------------------------------
// Enumerations of FRC on/off
//--------------------------------------------------
typedef enum
{
    _FRC_DISPLAY_ONOFF = _BIT0,
    _FRC_CAPTURE_ONOFF = _BIT2,
    _FRC_ALL_ONOFF = (_FRC_DISPLAY_ONOFF | _FRC_CAPTURE_ONOFF),
} EnumFRCOnOff;

//--------------------------------------------------
// Enumerations of D-domain Source Select
//--------------------------------------------------
typedef enum
{
    _DDOMAIN_SRC_FRAM_FRC,
    _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE,
} EnumDDomainSourceSelect;

//--------------------------------------------------
// Enumerations of Memory Work
//--------------------------------------------------
typedef enum
{
    _LINE_BUFFER_MODE = 0x00,
    _MEMORY_WORK_MODE,
} EnumMemoryWorkMode;

//--------------------------------------------------
// Enumerations of FIFO Frequency
//--------------------------------------------------
typedef enum
{
    _SCALER_FIFO_FREQ_M2PLL,
    _SCALER_FIFO_FREQ_MPLL,
    _SCALER_FIFO_FREQ_M2PLL_DIV2,
} EnumScalerFIFOFreq;

//****************************************************************************
// Enumerations of MHL
//****************************************************************************
//--------------------------------------------------
// Definitions of MSC Native Commands
//--------------------------------------------------
typedef enum
{
    _MSC_SET_INT = 0x60,
    _MSC_WRITE_STAT = 0x60,
    _MSC_READ_DEVCAP = 0x61,
    _MSC_SET_HPD = 0x64,
    _MSC_CLR_HPD,
    _MSC_WRITE_BURST = 0x6C,
    _MSC_WRITE_XSTAT = 0x70,
    _MSC_READ_XDEVCAP = 0x71,
    _MSC_ABORT = 0x35,
    _MSC_MSG = 0x68,
} EnumMHLMscCommand;

//--------------------------------------------------
// Definitions of MSC Offset
//--------------------------------------------------
typedef enum
{
    _MSC_NULL_ADDRESS = 0x00,

    // Capability Register Required Fields
    _MSC_DEV_STATE_00 = 0x00,
    _MSC_MHL_VERSION_01,
    _MSC_DEV_CAT_02,
    _MSC_ADOPTER_ID_H_03,
    _MSC_ADOPTER_ID_L_04,
    _MSC_VID_LINK_MODE_05,
    _MSC_AUD_LINK_MODE_06,
    _MSC_VIDEO_TYPE_07,
    _MSC_LOG_DEV_MAP_08,
    _MSC_BANDWIDTH_09,
    _MSC_FEATURE_FLAG_0A,
    _MSC_DEVICE_ID_H_0B,
    _MSC_DEVICE_ID_L_0C,
    _MSC_SCRATCHPAD_SIZE_0D,
    _MSC_INT_STAT_SIZE_0E,

    // _MSC_SET_INT
    _MSC_RCHANGE_INT = 0x20,
    _MSC_DCHANGE_INT,

    // _MSC_WRITE_STAT
    _MSC_CONNECTED_RDY = 0x30,
    _MSC_LINK_MODE,
    _MSC_MHL_VERSION_STAT,

    // _MSC_MSG
    _MSC_MSGE = 0x02,
    _MSC_RCP = 0x10,
    _MSC_RCPK,
    _MSC_RCPE,
    _MSC_RAP = 0x20,
    _MSC_RAPK,
    _MSC_RBP,
    _MSC_RBPK,
    _MSC_RBPE,
    _MSC_UCP = 0x30,
    _MSC_UCPK,
    _MSC_UCPE,
    _MSC_RUSB = 0x40,
    _MSC_RUSBK,
    _MSC_RHID,
    _MSC_RHIDK,
    _MSC_ATT = 0x50,
    _MSC_ATTK,
    _MSC_BIST_TRIGGER = 0x60,
    _MSC_REQUEST_STAT,
    _MSC_BIST_READY,
    _MSC_BIST_STOP,

    // MHL 3.0 XDAVCAP
    _MSC_40_SCRATCHPAD_OFFSET = 0x40,
    _MSC_80_ECBUS_SPEEDS = 0x80,
    _MSC_81_TMDS_SPEEDS,
    _MSC_82_ECBUS_DEV_ROLES,
    _MSC_83_LOG_DEV_MAPX,
    _MSC_84_ACRFS_DIV_SUPPORT,
    _MSC_85_RESERVE,
    _MSC_86_RESERVE,
    _MSC_87_RESERVE,
    _MSC_88_RESERVE,
    _MSC_89_RESERVE,
    _MSC_8A_RESERVE,
    _MSC_8B_RESERVE,
    _MSC_8C_RESERVE,
    _MSC_8D_RESERVE,
    _MSC_8E_RESERVE,
    _MSC_8F_RESERVE,

    _MSC_90_CURR_ECBUS_MODE = 0x90,
    _MSC_91_AVLINK_MODE_STATUS,
    _MSC_92_AVLINK_MODE_CONTROL,
    _MSC_93_MULTI_SINK_STATUS,
} EnumMHLMscOffset;

//--------------------------------------------------
// Definitions of MSC Data
//--------------------------------------------------
typedef enum
{
    _MSC_NULL_VALUE,

    // _MSC_RCHANGE_INT = 0x20
    _MSC_DCAP_CHG = 0x01,
    _MSC_DSCR_CHG = 0x02,
    _MSC_REQ_WRT = 0x04,
    _MSC_GRT_WRT = 0x08,
    _MSC_3D_REQ = 0x10,
    _MSC_FEAT_REQ = 0x20,
    _MSC_FEAT_COMPLETE = 0x40,

    // _MSC_DCHANGE_INT = 0x21
    _MSC_EDID_CHG = 0x02,

    // _MSC_CONNECTED_RDY = 0x30
    _MSC_DCAP_RDY = 0x01,
    _MSC_XDEVCAP_SUPP = 0x02,
    _MSC_POW_STAT = 0x04,
    _MSC_PLIM_STAT = 0x38,

    // _MSC_LINK_MODE = 0x31
    _MSC_PATH_EN = 0x08,
    _MSC_MUTED = 0x10,

    // _MSC_MHL_VERSION_STAT = 0x32
    _MSC_MHL_VERSION_3_0 = 0x30,

    // _MSC_90_CURR_ECBUS_MODE = 0x90
    _MSC_ECBUS_S_MODE = 0x04,

    // _MSC_91_AVLINK_MODE_STATUS = 0x91
    _MSC_NO_SIGNAL = 0x00,
    _MSC_CRU_LOCKED = 0x01,
    _MSC_TMDS_NORMAL = 0x02,

    // _MSCE_OPCODE
    _MSCE_NO_ERR = 0x01,
    _MSCE_INVALID_SUB_CMD = 0x01,

    // _MSC_RAPK_OPCODE
    _MSC_RAPK_NO_ERROR = 0x00,
    _MSC_RAPK_UNRECOGNIZE_CODE,
    _MSC_RAPK_UNSUPPORT_CODE,
    _MSC_RAPK_RESPONDER_BUSY,

    // _MSC_RCPE_OPCODE
    _MSC_RCPE_NO_ERROR = 0x00,
    _MSC_RCPE_INEFFECTIVE_CODE,
    _MSC_RCPE_RESPONDER_BUSY,

    // _MSC_RHIDK_OPCODE
    _MSC_RHIDK_NO_ERROR = 0x00,
    _MSC_RHIDK_INVALID_CODE,
    _MSC_RHIDK_DENY,

} EnumMHLMscData;

//--------------------------------------------------
// Definitions of MHL RAP OpCode
//--------------------------------------------------
typedef enum
{
    _MSC_RAP_POLL = 0x00,
    _MSC_RAP_CONTENT_ON = 0x10,
    _MSC_RAP_CONTENT_OFF = 0x11,
    _MSC_RAP_CBUS_MODE_DOWN = 0x20,
    _MSC_RAP_CBUS_MODE_UP = 0x21,
} EnumMHLMscRAPSubComm;

//--------------------------------------------------
// Definitions of MHL RAP OpCode
//--------------------------------------------------
typedef enum
{
    _MSC_RHID_REQUEST_HOST = 0x00,
    _MSC_RHID_RELINQUISH_HOST,
} EnumMHLMscRHIDSubComm;

//--------------------------------------------------
// Definitions of MHL Write Burst Options
//--------------------------------------------------
typedef enum
{
    _MHL_WRITE_BURST_WITH_REQ,
    _MHL_WRITE_BURST_WITHOUT_REQ,
} EnumMHLWriteBurstMode;

//****************************************************************************
// Enumerations of Mode
//****************************************************************************
//--------------------------------------------------
// Enumerations of Mode State
//--------------------------------------------------
typedef enum
{
    _MODE_STATUS_INITIAL = 0x00,
    _MODE_STATUS_SEARCH,
    _MODE_STATUS_DISPLAY_SETTING,
    _MODE_STATUS_ACTIVE,
    _MODE_STATUS_NOSUPPORT,
    _MODE_STATUS_NOSIGNAL,
    _MODE_STATUS_POWER_SAVING,
    _MODE_STATUS_POWER_OFF,
    _MODE_STATUS_FACTORY,
    _MODE_STATUS_NONE = 0xFF,
} EnumModeStatus;


//****************************************************************************
// Enumerations of Power
//****************************************************************************
//--------------------------------------------------
// Enumerations of Power Status/Action
//--------------------------------------------------
typedef enum
{
    _POWER_STATUS_AC_ON = 0x00,
    _POWER_STATUS_OFF,
    _POWER_STATUS_NORMAL,
    _POWER_STATUS_SAVING,
    _POWER_STATUS_NONE = 0x0F,
} EnumPowerStatus;

//--------------------------------------------------
// Enumerations of User Force into Fake Power Saving Status/Action
//--------------------------------------------------
typedef enum
{
    _USER_FORCE_POWER_SAVING = 0x00,
    _USER_FORCE_FAKE_POWER_SAVING,
} EnumUserForceFakePS;

//--------------------------------------------------
// Enumerations of User Force into Fake Power Off Status/Action
//--------------------------------------------------
typedef enum
{
    _USER_FORCE_POWER_OFF = 0x00,
    _USER_FORCE_FAKE_POWER_OFF,
} EnumUserForceFakePowerOff;

//--------------------------------------------------
// Enumerations of Power Action
//--------------------------------------------------
typedef enum
{
    _POWER_ACTION_OFF_TO_NORMAL = 0x00,
    _POWER_ACTION_OFF_TO_FAKE_OFF,
    _POWER_ACTION_AC_ON_TO_NORMAL,
    _POWER_ACTION_AC_ON_TO_OFF,
    _POWER_ACTION_AC_ON_INITIAL,
    _POWER_ACTION_PS_TO_NORMAL,
    _POWER_ACTION_PS_TO_OFF,
    _POWER_ACTION_NORMAL_TO_PS,
    _POWER_ACTION_NORMAL_TO_OFF,
    _POWER_ACTION_NORMAL_TO_FAKE_OFF,
    _POWER_ACTION_SWITCH_INTERFACE_TO_OFF,
    _POWER_ACTION_NORMAL_TO_FAKE_PS,
    _POWER_ACTION_FAKE_PS_TO_NORMAL,
    _POWER_ACTION_FAKE_OFF_TO_NORMAL,
    _POWER_ACTION_NONE = 0xFF,
} EnumPowerAction;

//--------------------------------------------------
// Enumerations of Power Action
//--------------------------------------------------
typedef enum
{
    _MODE_ACTION_NO_RESET_MODE = 0x00,
    _MODE_ACTION_RESET_TO_SEARCH,
    _MODE_ACTION_RESET_TO_DISPLAY_SETTING,
    _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG,
    _MODE_ACTION_RESET_TO_NOSUPPORT,
    _MODE_ACTION_RESET_TO_NOSIGNAL,
    _MODE_ACTION_RESET_TO_POWER_SAVING,
    _MODE_ACTION_RESET_TO_POWER_OFF,
    _MODE_ACTION_RESET_TO_FACTORY_MODE,
    _MODE_ACTION_NONE = 0xFF,
} EnumModeAction;


//****************************************************************************
// Enumerations of Scaling
//****************************************************************************
//--------------------------------------------------
// Enumerations of VSU Type
//--------------------------------------------------
typedef enum
{
    _VSU_2D_4LINE_COEF = 0x00,  // 2D 4line SU
    _VSU_2D_3LINE_COEF = 0x01,  // 2D 3line SU
    _VSU_3D_2LINE_COEF = 0x02,  // 3D 2line SU
    _VSU_3D_3LINE_COEF = 0x03,  // 3D 3line SU
    _VSU_3D_4LINE_COEF = 0x04,  // 3D 4line SU
} EnumVSUCoefType;


//****************************************************************************
// Enumerations of Source
//****************************************************************************
//--------------------------------------------------
// Enumerations of Input Source Type
//--------------------------------------------------
typedef enum
{
    _SOURCE_INPUT_TYPE_VGA = 0x00,
    _SOURCE_INPUT_TYPE_HDMI,
    _SOURCE_INPUT_TYPE_DVI,
    _SOURCE_INPUT_TYPE_DP,
    _SOURCE_INPUT_TYPE_TYPE_C,
} EnumSourceInputType;

//--------------------------------------------------
// Enumerations of Source State
//--------------------------------------------------
typedef enum
{
    _SOURCE_VGA,
    _SOURCE_VIDEO,
    _SOURCE_DVI,
    _SOURCE_HDMI,
    _SOURCE_DP,
    _SOURCE_NONE,
    _SOURCE_AMOUNT = _SOURCE_NONE,
} EnumSourceTypeDef;

//--------------------------------------------------
// Enumerations of Input Port List
//--------------------------------------------------
typedef enum
{
    _A0_INPUT_PORT = 0x00,
    _A1_INPUT_PORT,
    _A2_INPUT_PORT,
    _D0_INPUT_PORT,
    _D1_INPUT_PORT,
    _D2_INPUT_PORT,
    _D3_INPUT_PORT,
    _D4_INPUT_PORT,
    _D5_INPUT_PORT,
    _D6_INPUT_PORT,
    _NO_INPUT_PORT,
} EnumSourceSearchPort;

#define _A0_INPUT_PORT                          0x00
#define _A1_INPUT_PORT                          0x01
#define _A2_INPUT_PORT                          0x02
#define _D0_INPUT_PORT                          0x03
#define _D1_INPUT_PORT                          0x04
#define _D2_INPUT_PORT                          0x05
#define _D3_INPUT_PORT                          0x06
#define _D4_INPUT_PORT                          0x07
#define _D5_INPUT_PORT                          0x08
#define _D6_INPUT_PORT                          0x09
#define _NO_INPUT_PORT                          0x0A

//--------------------------------------------------
// Enumerations of Input Port Type
//--------------------------------------------------
typedef enum
{
    _ADJUST_PORT_VGA,
    _ADJUST_PORT_TMDS,
    _ADJUST_PORT_MHL,
    _ADJUST_PORT_DP,
} EnumSourceAdjustReactiveTimePortType;

// -------------------------------------------------
// Enumerations of CEC Support
// -------------------------------------------------

typedef enum
{
    _CEC_LA_TV = 0x00,
    _CEC_LA_RECORDING_DEVICE_1 = 0x01,
    _CEC_LA_RECORDING_DEVICE_2 = 0x02,
    _CEC_LA_TUNER_1 = 0x03,
    _CEC_LA_PLAYBACK_DEVICE_1 = 0x04,
    _CEC_LA_AUDIO_SYSTEM = 0x05,
    _CEC_LA_TUNER_2 = 0x06,
    _CEC_LA_TUNER_3 = 0x07,
    _CEC_LA_PLAYBACK_DEVICE_2 = 0x08,
    _CEC_LA_RECORDING_DEVICE_3 = 0x09,
    _CEC_LA_TUNER_4 = 0x0A,
    _CEC_LA_PLAYBACK_DEVICE_3 = 0x0B,
    _CEC_LA_RESERVED_1 = 0x0C,
    _CEC_LA_RESERVED_2 = 0x0D,
    _CEC_LA_SPECIFIC = 0x0E,
    _CEC_LA_UNREGISTERED = 0x0F,
    _CEC_LA_BORADCAST = 0x0F,
}EnumCECLogicalAddress;

typedef enum
{
    _CEC_TX_IDLE_STATE = 0,
    _CEC_TX_SENDING_STATE,
} EnumCecTxState;

typedef enum
{
    _CEC_TX_NONE_EVENT = 0,
    _CEC_TX_SENT_EVENT,
    _CEC_TX_LINE_ERROR_EVENT,
    _CEC_TX_HB_NACK_EVENT,
    _CEC_TX_DB_NACK_EVENT,
} EnumCecTxEvent;

// -------------------------------------------------
// Struct for CEC Support
// -------------------------------------------------
typedef struct
{
    BYTE ucReceivedHb;
    BYTE pucReceivedDb[16];
    BYTE ucDbLength;
} StructCecRxReceivedInfo;

typedef struct
{
    BYTE ucTransmitHb;
    BYTE pucTransmitDb[16];
    BYTE ucDbLength;
    BYTE b3RetryCnt : 3;
} StructCecTxTransmitInfo;

typedef struct
{
    WORD usCecPhyAddr;
    BYTE ucCecTxEvent;
    BYTE bReadDone : 1;
    BYTE bCecTxStart : 1;
    BYTE b2CecTxState : 2;
    BYTE bCecFxEnable : 1;
    BYTE bCecRxInfoAnalyzing : 1;
    BYTE bReadFromBackupFifo : 1;
} StructCecGeneralCtrl;

//--------------------------------------------------
// Struct for DP FREESYNC Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DPFREESYNCEnable : 1;
    BYTE b1DPMSTFREESYNCEnable : 1;
    BYTE b1DPRX0FREESYNCCapabilitySwitch : 1;
    BYTE b1DPRX1FREESYNCCapabilitySwitch : 1;
    BYTE b1DPRX2FREESYNCCapabilitySwitch : 1;
    BYTE b1DPRX6FREESYNCCapabilitySwitch : 1;
    BYTE b1DPRX0SPDInfoFrameReceived : 1;
    BYTE b1DPRX1SPDInfoFrameReceived : 1;
    EnumFreeSyncSupport enumDPRX0FREESYNCSupport;
    EnumFreeSyncSupport enumDPRX1FREESYNCSupport;
    EnumFreeSyncSupport enumDPRX2FREESYNCSupport;
    EnumFreeSyncSupport enumDPRX6FREESYNCSupport;
    WORD usDPRX0FREESYNCMSAHtotal;
    WORD usDPRX1FREESYNCMSAHtotal;
    WORD usDPRX0FREESYNCHtotalMargin;
    WORD usDPRX1FREESYNCHtotalMargin;
} StructDPFREESYNCENABLE;

//--------------------------------------------------
// Struct for HDMI FREESYNC Support
//--------------------------------------------------
typedef struct
{
    BYTE b1HDMIFREESYNCEnable : 1;
    BYTE b1HDMIRX0SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX1SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX2SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX3SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX4SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX5SPDInfoFrameReceived : 1;

    EnumFreeSyncSupport enumHDMIRX0FREESYNCSupport;
    EnumFreeSyncSupport enumHDMIRX1FREESYNCSupport;
    EnumFreeSyncSupport enumHDMIRX2FREESYNCSupport;
    EnumFreeSyncSupport enumHDMIRX3FREESYNCSupport;
    EnumFreeSyncSupport enumHDMIRX4FREESYNCSupport;
    EnumFreeSyncSupport enumHDMIRX5FREESYNCSupport;
} StructHDMIFREESYNCENABLE;

//--------------------------------------------------
// Definitions of HDR Flow
//--------------------------------------------------
typedef enum
{
    _DP_GET_RSV0_INFO_INITIAL,
    _DP_GET_RSV0_INFO_ACTIVE,
}EnumDPGetRSV0InfoStatus;

typedef struct
{
    BYTE ucVersion;
    BYTE ucLength;

    BYTE ucEOTF;
    BYTE ucStaticMetadataID;

    WORD usDisplayPrimariesX0;
    WORD usDisplayPrimariesY0;

    WORD usDisplayPrimariesX1;
    WORD usDisplayPrimariesY1;

    WORD usDisplayPrimariesX2;
    WORD usDisplayPrimariesY2;

    WORD usWhitePointX;
    WORD usWhitePointY;

    WORD usMaxDisplayMasteringLv;
    WORD usMinDisplayMasteringLv;
    WORD usMaxCLL;
    WORD usMaxFALL;
} StructHDR10StaticMetaData;

//--------------------------------------------------
// Definitions of HDR Info EOTF
//--------------------------------------------------
typedef enum
{
    _HDR_INFO_EOTF_TRADITIONAL_GAMMA_SDR = 0x00,
    _HDR_INFO_EOTF_TRADITIONAL_GAMMA_HDR = 0x01,
    _HDR_INFO_EOTF_SMPTE_ST_2084 = 0x02,
    _HDR_INFO_EOTF_FUTURE_EOTF = 0x03,
    _HDR_INFO_EOTF_RESERVED = 0x04,
} EnumHDR10InfoEOTF;

//--------------------------------------------------
// Definitions of HDR Max Mastering Lv Type
//--------------------------------------------------
typedef enum
{
    _HDR10_MAX_MASTERING_LV_TYPE_540, // 540 nits
    _HDR10_MAX_MASTERING_LV_TYPE_1200, // 1200 nits
    _HDR10_MAX_MASTERING_LV_TYPE_4000, // 4000 nits
    _HDR10_MAX_MASTERING_LV_TYPE_10000, // 10000 nits
    _HDR10_MAX_MASTERING_LV_TYPE_NOTM, // Tone Mapping by source
} EnumHDR10MaxMasteringLvType;

//--------------------------------------------------
// Definitions of HDR10 Fixed Point Tone Mapping
//--------------------------------------------------
typedef enum
{
    _HDR10_FIXED_POINT_TM_OFF,
    _HDR10_FIXED_POINT_TM_ON,
} EnumHDR10FixedPointToneMappingStatus;

//--------------------------------------------------
// Definitions of HDR10 Mode
//--------------------------------------------------
typedef enum
{
    _HDR10_MODE_OFF,
    _HDR10_MODE_AUTO,
    _HDR10_MODE_FORCE_2084,
}EnumHDR10ModeDef;

//--------------------------------------------------
// Definitions of HDR Setting
//--------------------------------------------------
typedef struct
{
    EnumHDR10InfoEOTF enumHDR10EOTFSetting;
    EnumHDR10MaxMasteringLvType enumHDR10MaxLVSetting;
    EnumHDR10ModeDef enumHDR10RX0Support;
    EnumHDR10ModeDef enumHDR10RX1Support;
    EnumHDR10ModeDef enumHDR10RX2Support;
    EnumHDR10ModeDef enumHDR10RX3Support;
    EnumHDR10ModeDef enumHDR10RX4Support;
    EnumHDR10ModeDef enumHDR10RX5Support;
    EnumHDR10ModeDef enumHDR10RX6Support;
} StructHDR10Setting;

//--------------------------------------------------
// Definitions of HDR10 Fixed Point Tone Mapping
//--------------------------------------------------
typedef enum
{
    _HDR10_USER_ASSIGNED_TABLE_OFF,
    _HDR10_USER_ASSIGNED_TABLE_ON,
} EnumHDR10UserAssignTableStatus;

//--------------------------------------------------
// Structure of User Assigned HDR InputGamma Table Addr & Bank
//--------------------------------------------------
typedef struct
{
    EnumHDR10UserAssignTableStatus enumHDR10UserAssignTableStatus;
    BYTE *pucIGTable;
    BYTE *pucSRGBMatrix;
    BYTE *pucOGTable;
    BYTE ucBank;
}StructHDR10Table;

//--------------------------------------------------
// Definitions of Local dimming Boost Mode
//--------------------------------------------------
typedef enum
{
    _LD_BOOST_KERNAL,
    _LD_BOOST_USER,
} EnumLDBoostMode;

//--------------------------------------------------
// Definitions of HDR Port Setting Info
//--------------------------------------------------
typedef struct
{
    EnumHDR10ModeDef enumHDR10RX0Support;
    EnumHDR10ModeDef enumHDR10RX1Support;
    EnumHDR10ModeDef enumHDR10RX2Support;
    EnumHDR10ModeDef enumHDR10RX3Support;
    EnumHDR10ModeDef enumHDR10RX4Support;
    EnumHDR10ModeDef enumHDR10RX5Support;
    EnumHDR10ModeDef enumHDR10RX6Support;
} StructHDR10PortSettingInfo;

//--------------------------------------------------
// Definitions of Freesync II
//--------------------------------------------------
typedef struct
{
    BYTE b1NativeColorSpaceEnable : 1;
    BYTE b1BacklightControlEnable : 1;
    BYTE b1LocalDimmingDisable : 1;
    BYTE b5EOTFType : 5;
    BYTE ucBacklightControlRatio;
} StructFreeSyncIIInfo;

typedef enum
{
    _FREESYNC_II_NATIVE_COLOR_SPACE_ENABLE,
    _FREESYNC_II_BACKLIGHT_CONTROL_ENABLE,
    _FREESYNC_II_EOTF_TYPE,
    _FREESYNC_II_BACKLIGHT_CONTROL_RATIO,
}EnumFreeSyncIIContent;

//--------------------------------------------------
// Enumerations Load EDID Port Selection
//--------------------------------------------------
typedef enum
{
    _A0_INPUT_PORT_EDID = _A0_INPUT_PORT,
    _D0_INPUT_PORT_EDID = _D0_INPUT_PORT,
    _D1_INPUT_PORT_EDID = _D1_INPUT_PORT,
    _D2_INPUT_PORT_EDID = _D2_INPUT_PORT,
    _D3_INPUT_PORT_EDID = _D3_INPUT_PORT,
    _D4_INPUT_PORT_EDID = _D4_INPUT_PORT,
    _D5_INPUT_PORT_EDID = _D5_INPUT_PORT,
    _D6_INPUT_PORT_EDID = _D6_INPUT_PORT,
    _D0_INPUT_PORT_MHL_EDID,
    _D1_INPUT_PORT_MHL_EDID,
    _D2_INPUT_PORT_MHL_EDID,
    _D3_INPUT_PORT_MHL_EDID,
    _D4_INPUT_PORT_MHL_EDID,
    _D5_INPUT_PORT_MHL_EDID,
} EnumInputPortEdid;

//--------------------------------------------------
// Enumerations of Input Port Priority
//--------------------------------------------------
typedef enum
{
    _INPUT_PORT_PRIORITY_0 = 0x00,
    _INPUT_PORT_PRIORITY_1,
    _INPUT_PORT_PRIORITY_2,
    _INPUT_PORT_PRIORITY_3,
    _INPUT_PORT_PRIORITY_4,
    _INPUT_PORT_PRIORITY_5,
    _INPUT_PORT_PRIORITY_6,
    _INPUT_PORT_PRIORITY_7,
    _INPUT_PORT_PRIORITY_8,
    _INPUT_PORT_PRIORITY_9,
    _INPUT_PORT_PRIORITY_NONE,
} EnumSourceSearchPortPriority;

//--------------------------------------------------
// Enumerations of Input Port Search Group List
//--------------------------------------------------
typedef enum
{
    _INPUT_PORT_GROUP_0 = 0x00,
    _INPUT_PORT_GROUP_1,
    _INPUT_PORT_GROUP_2,
    _INPUT_PORT_GROUP_3,
    _INPUT_PORT_GROUP_4,
    _INPUT_PORT_GROUP_5,
    _INPUT_PORT_GROUP_6,
    _INPUT_PORT_GROUP_7,
    _INPUT_PORT_GROUP_8,
    _INPUT_PORT_GROUP_9,
    _INPUT_PORT_GROUP_NONE,
} EnumSourceSearchGroup;

//--------------------------------------------------
// Enumerations of Port Type List
//--------------------------------------------------
typedef enum
{
    _PORT_NONE = 0x00,
    _PORT_VGA,
    _PORT_DVI,
    _PORT_HDMI,
    _PORT_DP,
    _PORT_MHL,
    _PORT_HDMI20,
    _PORT_DUAL_DVI,
} EnumInputPortType;

#define _PORT_NONE                              0x00
#define _PORT_VGA                               0x01
#define _PORT_DVI                               0x02
#define _PORT_HDMI                              0x03
#define _PORT_DP                                0x04
#define _PORT_MHL                               0x05
#define _PORT_HDMI20                            0x06
#define _PORT_DUAL_DVI                          0x07

//--------------------------------------------------
// Structure of Input Port Cable Status
//--------------------------------------------------
typedef struct
{
    BYTE b1A0CableDetect : 1;
    BYTE b1A1CableDetect : 1;
    BYTE b1A2CableDetect : 1;
    BYTE b1D0CableDetect : 1;
    BYTE b1D1CableDetect : 1;
    BYTE b1D2CableDetect : 1;
    BYTE b1D3CableDetect : 1;
    BYTE b1D4CableDetect : 1;
    BYTE b1D5CableDetect : 1;
    BYTE b1D6CableDetect : 1;
    BYTE b1D0MHLCableDetect : 1;
    BYTE b1D1MHLCableDetect : 1;
    BYTE b1D2MHLCableDetect : 1;
    BYTE b1D3MHLCableDetect : 1;
    BYTE b1D4MHLCableDetect : 1;
    BYTE b1D5MHLCableDetect : 1;
} StructPortCableStatus;

//****************************************************************************
// Enumerations of Timer
//****************************************************************************
//--------------------------------------------------
// Enumerations of Timer Operation
//--------------------------------------------------
typedef enum
{
    _TIMER_OPERATION_INITIAL_MODE,
    _TIMER_OPERATION_POWER_NORMAL_MODE,
    _TIMER_OPERATION_POWER_SAVING_MODE,
    _TIMER_OPERATION_POWER_SAVING_FAST_MODE,
    _TIMER_OPERATION_POWER_IDLE_MODE,
    _TIMER_OPERATION_OSD_MODE,
} EnumScalerTimerOperationMode;


//****************************************************************************
// Enumerations of Timing Info
//****************************************************************************
//--------------------------------------------------
// Enumerations of Timing Info
//--------------------------------------------------
typedef enum
{
    _HPOLARITY = 0x00,
    _VPOLARITY,
    _INTERLACE,
    _IHFREQ,
    _IHTOTAL,
    _IHWIDTH,
    _IHSTART,
    _IVFREQ,
    _IVTOTAL,
    _IVHEIGHT,
    _IVSTART,
    _IVSYNC_WIDTH,
    _MISC,
} EnumTimingInfoSelect;

//--------------------------------------------------
// Enumerations of Display Timing Data Info
//--------------------------------------------------
typedef enum
{
    _DISPLAY_TIMING_HTOTAL,
    _DISPLAY_TIMING_VTOTAL,
    _DISPLAY_TIMING_HSTART,
    _DISPLAY_TIMING_VSTART,
    _DISPLAY_TIMING_HWIDTH,
    _DISPLAY_TIMING_VHEIGHT,
} EnumDispTimingDataType;

//--------------------------------------------------
// Definitions of Signature Enum
//--------------------------------------------------
typedef enum
{
    _SIGN_FILE,
    _SIGN_NKEY,
    _SIGN_RRMODN,
    _SIGN_NPINV,
    _SIGN_EKEY,
} EnumSignKeyInfo;

//****************************************************************************
// Enumerations of Audio
//****************************************************************************
//--------------------------------------------------
// Enumerations of Audio State
//--------------------------------------------------
typedef enum
{
    _AUDIO_STATUS_POWER_OFF,
    _AUDIO_STATUS_PREPARING,
    _AUDIO_STATUS_PLAYBACK,
} EnumAudioState;

//--------------------------------------------------
// Enumerations of Audio DAC State
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OFF,
    _AUDIO_DAC_INITIAL,
    _AUDIO_DAC_CHARGE,
    _AUDIO_DAC_DEPOP,
    _AUDIO_DAC_READY,
} EnumAudioDACState;

//--------------------------------------------------
// Enumerations of Audio DAC Output
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUTPUT_NONE,
    _AUDIO_DAC_OUTPUT_SPEAKER,
    _AUDIO_DAC_OUTPUT_HEADPHONE,
    _AUDIO_DAC_OUTPUT_BOTH,
} EnumAudioDACOutput;

//--------------------------------------------------
// Enumerations of Audio DAC Dither Level
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_DITHER_LEVEL_OFF = 0x00,
    _AUDIO_DAC_DITHER_LEVEL_1,
    _AUDIO_DAC_DITHER_LEVEL_2,
    _AUDIO_DAC_DITHER_LEVEL_3,
} EnumAudioDACDitherLevel;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Type
//--------------------------------------------------
typedef enum
{
    _AUDIO_FREQ_NO_AUDIO = 0x00,
    _AUDIO_FREQ_32K,
    _AUDIO_FREQ_44_1K,
    _AUDIO_FREQ_48K,
    _AUDIO_FREQ_64K,
    _AUDIO_FREQ_88_2K,
    _AUDIO_FREQ_96K,
    _AUDIO_FREQ_128K,
    _AUDIO_FREQ_176_4K,
    _AUDIO_FREQ_192K,
    _AUDIO_FREQ_256K,
    _AUDIO_FREQ_352_8K,
    _AUDIO_FREQ_384K,
    _AUDIO_FREQ_512K,
    _AUDIO_FREQ_705_6K,
    _AUDIO_FREQ_768K,
} EnumAudioSamplingFreqType;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Packet Number
//--------------------------------------------------
typedef enum
{
    _AUDIO_FREQ_PACKET_NO_AUDIO = 0,
    _AUDIO_FREQ_PACKET_32K = 32,
    _AUDIO_FREQ_PACKET_44_1K = 44,
    _AUDIO_FREQ_PACKET_48K = 48,
    _AUDIO_FREQ_PACKET_64K = 64,
    _AUDIO_FREQ_PACKET_88_2K = 88,
    _AUDIO_FREQ_PACKET_96K = 96,
    _AUDIO_FREQ_PACKET_128K = 128,
    _AUDIO_FREQ_PACKET_176_4K = 176,
    _AUDIO_FREQ_PACKET_192K = 192,
    _AUDIO_FREQ_PACKET_256K = 256,
    _AUDIO_FREQ_PACKET_352_8K = 352,
    _AUDIO_FREQ_PACKET_384K = 384,
    _AUDIO_FREQ_PACKET_512K = 512,
    _AUDIO_FREQ_PACKET_705_6K = 705,
    _AUDIO_FREQ_PACKET_768K = 768,
} EnumAudioSamplingFreqPacket;

//--------------------------------------------------
// Enumerations of Audio Sampling Frequency in SPDIF Format
//--------------------------------------------------
typedef enum
{
    _AUDIO_SPDIF_FS_22_05KHZ = _BIT2,
    _AUDIO_SPDIF_FS_24KHZ = (_BIT2 | _BIT1),
    _AUDIO_SPDIF_FS_32KHZ = (_BIT1 | _BIT0),
    _AUDIO_SPDIF_FS_44_1KHZ = 0x00,
    _AUDIO_SPDIF_FS_48KHZ = _BIT1,
    _AUDIO_SPDIF_FS_88_2KHZ = _BIT3,
    _AUDIO_SPDIF_FS_96KHZ = (_BIT3 | _BIT1),
    _AUDIO_SPDIF_FS_176_4KHZ = (_BIT3 | _BIT2),
    _AUDIO_SPDIF_FS_192KHZ = (_BIT3 | _BIT2 | _BIT1),
    _AUDIO_SPDIF_FS_NOT_INDICATED = _BIT0,
} EnumAudioSpdifSamplingFrequencyType;

//--------------------------------------------------
// Enumerations of Audio input Source
//--------------------------------------------------
typedef enum
{
    _LINE_IN_AUDIO,
    _DIGITAL_AUDIO,
    _NO_AUDIO_SOURCE = 0xFF,
} EnumAudioInputSource;

//--------------------------------------------------
// Enumerations of Digital Audio Source
//--------------------------------------------------
typedef enum
{
    _DIGITAL_AUDIO_SOURCE_NONE,
    _DIGITAL_AUDIO_SOURCE_HDMI,
    _DIGITAL_AUDIO_SOURCE_DP,
} EnumAudioDigitalSource;

//--------------------------------------------------
// Enumerations of Audio Input Port
//--------------------------------------------------
typedef enum
{
    _AUDIO_FROM_D0_PORT = 0x00,
    _AUDIO_FROM_D1_PORT,
    _AUDIO_FROM_D2_PORT,
    _AUDIO_FROM_D3_PORT,
    _AUDIO_FROM_D4_PORT,
    _AUDIO_FROM_D5_PORT,
    _AUDIO_FROM_ADC_PORT,
} EnumAudioInputPort;

//--------------------------------------------------
// Enumerations of Audio Output Port
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUT = 0x00,
    _AUDIO_I2S_OUT,
    _AUDIO_SPDIF_OUT,
    _AUDIO_DPTX_OUT,
    _AUDIO_EDPTX0_OUT,
    _AUDIO_EDPTX1_OUT,
    _AUDIO_EDPTX2_OUT,
    _AUDIO_EDPTX3_OUT,
} EnumAudioOutputType;

//--------------------------------------------------
// Enumerations of Audio DAC Output Gain
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUTPUT_GAIN_0_DB = 0x00,
    _AUDIO_DAC_OUTPUT_GAIN_1_5_DB = 0x01,
    _AUDIO_DAC_OUTPUT_GAIN_3_DB = 0x02,
    _AUDIO_DAC_OUTPUT_GAIN_4_5_DB = 0x03,
    _AUDIO_DAC_OUTPUT_GAIN_6_DB = 0x04,
    _AUDIO_DAC_OUTPUT_GAIN_7_5_DB = 0x05,
    _AUDIO_DAC_OUTPUT_GAIN_9_DB = 0x06,
    _AUDIO_DAC_OUTPUT_GAIN_10_5_DB = 0x07,
} EnumAudioDacOutputGain;

//--------------------------------------------------
// Enumerations of Audio Channel Count
//--------------------------------------------------
typedef enum
{
    _AUDIO_CHANNEL_COUNT_MONO = 0x00,
    _AUDIO_CHANNEL_COUNT_2,
    _AUDIO_CHANNEL_COUNT_3,
    _AUDIO_CHANNEL_COUNT_4,
    _AUDIO_CHANNEL_COUNT_5,
    _AUDIO_CHANNEL_COUNT_6,
    _AUDIO_CHANNEL_COUNT_7,
    _AUDIO_CHANNEL_COUNT_8,
} EnumAudioChannelCount;

//--------------------------------------------------
// Definitions of Aspect Ratio Type Status
//--------------------------------------------------
typedef enum
{
/*
    _ASPECT_RATIO_FULL,
    _ASPECT_RATIO_FIXED,
    _ASPECT_RATIO_USER,
    _ASPECT_RATIO_ORIGIN,*/
    _ASPECT_RATIO_FULL,
    _ASPECT_RATIO_ORIGIN,
    _ASPECT_RATIO_FIXED,
    _ASPECT_RATIO_1280x960,
    _ASPECT_RATIO_1024x768,
    _ASPECT_RATIO_800x600,
    _ASPECT_RATIO_640x480,
    _ASPECT_RATIO_MAXIMAGE,
    _ASPECT_RATIO_HMAXIMAGE,
    _ASPECT_RATIO_VMAXIMAGE,
    _ASPECT_RATIO_17Inch_Full,
    _ASPECT_RATIO_17Inch_4x3,
    _ASPECT_RATIO_17Inch_5x4,
    _ASPECT_RATIO_1400x1050,
    _ASPECT_RATIO_1280x1024,
    _ASPECT_RATIO_870x625,
    _ASPECT_RATIO_USER,
    _ASPECT_RATIO_AMOUNT = _ASPECT_RATIO_USER,
} EnumAspectRatioType;

//--------------------------------------------------
// Definitions of Rotation Type Status
//--------------------------------------------------
typedef enum
{
    _ROT_DISABLE = 0x00,
    _ROT_CW90,
    _ROT_CW180,
    _ROT_CW270,
    _ROT_HOR_MIRROR,
    _ROT_VER_MIRROR,
} EnumRotationType;

//--------------------------------------------------
// Definitions of Rotation Display Type Status
//--------------------------------------------------
typedef enum
{
    _ROT_FULL = 0x00,
    _ROT_PIXEL_BY_PIXEL,
    _ROT_KEEP_SRC_ASPECT_RATIO,
} EnumRotationDisplayType;

//--------------------------------------------------
// Definitions of D Domain Request
//--------------------------------------------------
typedef enum
{
    _1_LINE_AFTER_DVS,
    _64_PIXELS_AFTER_DVS,
    _7_LINES_BEFORE_DEN,
} EnumDDomainRequest;

//------------------------------------------------------------
// Definitions of Pin Share Config type that user can adjust
//------------------------------------------------------------
typedef enum
{
    _GPI,
    _GPO_OD,
    _GPO_PP,
    _PWM0_OD,
    _PWM0_PP,
    _PWM1_OD,
    _PWM1_PP,
    _PWM2_OD,
    _PWM2_PP,
    _PWM3_OD,
    _PWM3_PP,
    _PWM4_OD,
    _PWM4_PP,
    _PWM5_OD,
    _PWM5_PP,
    _WS,
    _SCK,
    _MCK,
    _SD0,
    _SD1,
    _SD2,
    _SD3,
    _USB_SPI,
    _TCON_11,
} EnumPinConfigType;

//------------------------------------------------------------
// Definitions of Flash Drive Config type that user can Pin
//------------------------------------------------------------
typedef enum
{
    _CONFIG_PIN_SPI_CLK,
    _CONFIG_PIN_SPI_SI_SO_CEB,
} EnumConfigSPIPinType;

//------------------------------------------------------------
// Definitions of Flash Drive Config type that user can Drive
//------------------------------------------------------------
typedef enum
{
    _SPI_DRIVE_3_0MA,
    _SPI_DRIVE_3_5MA,
    _SPI_DRIVE_4_0MA,
    _SPI_DRIVE_4_5MA,
    _SPI_DRIVE_5_0MA,
    _SPI_DRIVE_5_5MA,
} EnumFlashDriveConfigType;

//--------------------------------------------------
// Definitions of Rotation Status
//--------------------------------------------------
typedef struct
{
    EnumRotationType enumRotationType;
    EnumRotationDisplayType enumRotationDispSize;
} StructRotationStatus;

//--------------------------------------------------
// Definitions of AVI Info Frame Contents
//--------------------------------------------------
typedef enum
{
    _AVI_INFO_COLOR_SPACE,
    _AVI_INFO_COLORIMETRY,
    _AVI_INFO_EXTENDED_COLORIMETRY,
    _AVI_INFO_YCC_QUANTIZATION,
    _AVI_INFO_RGB_QUANTIZATION,
    _AVI_INFO_SCAN_INFO,
    _AVI_INFO_IT_CONTENT,
    _AVI_INFO_PIXEL_REPETITION,
    _AVI_INFO_AR,
    _AVI_INFO_VIC,
} EnumAviInfoContent;

typedef enum
{
    _CHECK_ADC_SAVE,
    _CHECK_ADC_LOAD,
    _CHECK_SYSTEM_DATA_SAVE,
    _CHECK_SYSTEM_DATA_LOAD,
    _CHECK_MODE_USER_DATA_SAVE,
    _CHECK_MODE_USER_DATA_LOAD,
    _CHECK_SYSTEM_ITEM_COUNT,
} EnumNvramCheckType;

typedef enum
{
    _H_V_SU_128TAPS_NORMAL,
    _H_V_SU_96TAPS_NORMAL,
    _H_SU_128TAPS_1_TO_1,
    _H_SU_96TAPS_1_TO_1,
    _H_SU_128TAPS_NORMAL,
    _H_SU_96TAPS_NORMAL,
    _V_SU_128TAPS_NORMAL,
    _V_SU_96TAPS_NORMAL,    
} EnumSUCoefType;

typedef enum
{
    _SPD_INFO_OUI,
    _SPD_INFO_FREESYNC_SUPPORT,
    _SPD_INFO_FREESYNC_ENABLE,
    _SPD_INFO_FREESYNC_ACTIVE,
    _SPD_INFO_FREESYNC_MIN_VFREQ,
    _SPD_INFO_FREESYNC_MAX_VFREQ,
} EnumAmdSpdInfoContent;

//--------------------------------------------------
// Definitions of HDR Max Mastering Lv Type
//--------------------------------------------------
typedef enum
{
    _HDR_MAX_MASTERING_LV_TYPE_1200, // 1200 nits
    _HDR_MAX_MASTERING_LV_TYPE_4000, // 4000 nits
    _HDR_MAX_MASTERING_LV_TYPE_10000, // 10000 nits
    _HDR_MAX_MASTERING_LV_TYPE_540, // 540 nits
} EnumHDRMaxMasteringLvType;

//--------------------------------------------------
// Definitions of HDR Color Matrix
//--------------------------------------------------
typedef enum
{
    _HDR_COLOR_MATRIX_SRGB,
    _HDR_COLOR_MATRIX_ADOBE,
    _HDR_COLOR_MATRIX_DCIP3_D65,
    _HDR_COLOR_MATRIX_BT2020,
} EnumHDRColorMatrix;

//--------------------------------------------------
// Definitions of OSD Position Offset Type
//--------------------------------------------------
typedef enum
{
    _OSD_POSITION_OFFSET_GLOBAL,
    _OSD_POSITION_OFFSET_WINDOW,
} EnumOsdPositionOffsetType;

//--------------------------------------------------
// Definitions of VSU initial phase
//--------------------------------------------------
typedef enum
{
    _VSU_3_LINE = 0x03,
    _VSU_4_LINE = 0x04,
} EnumVsuInitPhaseLines;

//--------------------------------------------------
// Definitions of SPI controller
//--------------------------------------------------
typedef enum
{
    _SPI_TIMING_MODE0 = 0x00,
    _SPI_TIMING_MODE1 = 0x1E,
    _SPI_TIMING_MODE2 = 0x01,
    _SPI_TIMING_MODE3 = 0x1F,
} EnumSpiTimingMode;

typedef enum
{
    _CLK_SOURCE_XTAL,
    _CLK_SOURCE_M2PLL,
    _CLK_SOURCE_EPLL,
} EnumSpiMasterClkSource;

//--------------------------------------------------
// Definitions of Type-C ADC Channels
//--------------------------------------------------
typedef enum
{
    _TYPE_C_UFP_VMON = 0x00,
    _TYPE_C_UFP_IMON = 0x01,
    _TYPE_C_LOC_PW = 0x02,
    _TYPE_C_DFP_VMON = 0x03,
    _TYPE_C_DFP_IMON = 0X04,
}EnumTypeCAdcChannel;

//--------------------------------------------------
// Definitions of USB Speed
//--------------------------------------------------
#define _USB_SPEED_NOT_SUPPORT                  0x00
#define _USB_SPEED_5G                           0x01
#define _USB_SPEED_10G                          0x02

//--------------------------------------------------
// Definitions of DDCCI Command Source Type
//--------------------------------------------------
typedef enum
{
    _DDCCI_CMD_SRC_I2C = 0x00,
    _DDCCI_CMD_SRC_MST = 0x01,
} EnumDdcciCmdSrc;

//--------------------------------------------------
// Definitions of AIO Modern Standby Mode
//--------------------------------------------------
typedef enum
{
    _AIO_MODERN_STANDBY_MODE_ENABLE = 0x00,
    _AIO_MODERN_STANDBY_MODE_DISABLE = 0x01,
} EnumAIOModernStandbyMode;

//--------------------------------------------------
// Definitions of DP HPD Toggle Mode Control By User
//--------------------------------------------------
typedef enum
{
    _DP_HPD_TOGGLE_NORMAL = 0x00,
    _DP_HPD_TOGGLE_NONE = 0x01,
} EnumDpHpdToggleMode;

//--------------------------------------------------
// Definitions of Motion Blur Reduction
//--------------------------------------------------
typedef enum
{
    _RTK_ADV_MBR_USER_DISABLE = _OFF,
    _RTK_ADV_MBR_USER_ENABLE,
} EnumRtkAdvMbrUserStatus;

typedef enum
{
    _BACKLIGHT_MODE_CONSTANT,
    _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR,
    _BACKLIGHT_MODE_STROBE_DRR_MBR,
    _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR,
} EnumMbrBacklightMode;

typedef enum
{
    _MBR_DRR_MODE_OFF,
    _MBR_DRR_MODE_STROBE,
    _MBR_DRR_MODE_CONSTANT,
    _MBR_DRR_MODE_STROBE_TO_CONSTANT,
    _MBR_DRR_MODE_CONSTANT_TO_STROBE,
} EnumMbrDrrBacklightMode;

//--------------------------------------------------
// Definitions of Tcon
//--------------------------------------------------
typedef enum
{
    _TCON4_ALT_WITH_TCON3 = _TCON4,
    _TCON5_ALT_WITH_TCON4 = _TCON5,
    _TCON6_ALT_WITH_TCON5 = _TCON6,
    _TCON9_ALT_WITH_TCON8 = _TCON9,
    _TCON10_ALT_WITH_TCON9 = _TCON10,
    _TCON11_ALT_WITH_TCON10 = _TCON11,
    _TCON12_ALT_WITH_TCON11 = _TCON12,
    _TCON13_ALT_WITH_TCON12 = _TCON13,
} EnumTconAlternateSet;

typedef enum
{
    _TCON3_LOGICAL_OP = _TCON3,
    _TCON4_LOGICAL_OP = _TCON4,
    _TCON5_LOGICAL_OP = _TCON5,
    _TCON6_LOGICAL_OP = _TCON6,
    _TCON7_LOGICAL_OP = _TCON7,
    _TCON8_LOGICAL_OP = _TCON8,
    _TCON9_LOGICAL_OP = _TCON9,
    _TCON10_LOGICAL_OP = _TCON10,
    _TCON11_LOGICAL_OP = _TCON11,
    _TCON12_LOGICAL_OP = _TCON12,
    _TCON13_LOGICAL_OP = _TCON13,
} EnumTconLogicalOpSet;

typedef enum
{
    _TCON_LOGICAL_OP_AND,
    _TCON_LOGICAL_OP_OR,
    _TCON_LOGICAL_OP_XOR,
    _TCON_TOGGLE_OP_NORMAL,
    _TCON_TOGGLE_OP_AND,
    _TCON_TOGGLE_OP_OR,
} EnumTconLogicalOp;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructPortCableStatus g_stPortCableStatus;
extern BYTE g_ucD6SwitchSelect;
extern bit g_bD6SwitchPowerStatus;
extern BYTE g_ucDpEmbeddedSwitchSelect;
extern BYTE g_ucDpEmbeddedSwitchTarget;
extern bit g_bDpEmbeddedSwitchEvent;
extern bit g_bDpAutoSearchSwitch;
extern BYTE g_uDclkSpreadSpeed;
extern BYTE g_uDclkSpreadRange;

#endif // End of #ifndef __GLOBAL_H__
