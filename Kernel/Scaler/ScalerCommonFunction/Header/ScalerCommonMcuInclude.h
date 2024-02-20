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
// ID Code      : ScalerCommonMcuInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Macros of HW IIC Setting
//--------------------------------------------------
#define _HW_IIC_SLPC_14318K                 (tHwI2cSetting[g_ucHwI2cSettingIndex].ucSLPC_14318K)
#define _HW_IIC_SHPC_14318K                 (tHwI2cSetting[g_ucHwI2cSettingIndex].ucSHPC_14318K)
#define _HW_IIC_SLPC_28000K                 (tHwI2cSetting[g_ucHwI2cSettingIndex].ucSLPC_28000K)
#define _HW_IIC_SHPC_28000K                 (tHwI2cSetting[g_ucHwI2cSettingIndex].ucSHPC_28000K)
#define _HW_IIC_STA_SUGPIO_C                (tHwI2cSetting[g_ucHwI2cSettingIndex].ucSTA_SUGPIO_C)
#define _HW_IIC_TOR                         (tHwI2cSetting[g_ucHwI2cSettingIndex].ucTOR)
#define _HW_IIC_FTPC                        (tHwI2cSetting[g_ucHwI2cSettingIndex].ucFTPC)
#define _HW_IIC_FD10_14318K                 (tHwI2cSetting[g_ucHwI2cSettingIndex].ucFD10_14318K)
#define _HW_IIC_FD10_28000K                 (tHwI2cSetting[g_ucHwI2cSettingIndex].ucFD10_28000K)

//--------------------------------------------------
// Macros of 5us Delay
//--------------------------------------------------
#define DELAY_5US()                         {\
                                                g_ucDelay5usI = (g_ucDelay5usN_Base);\
                                                while(--g_ucDelay5usI) {};\
                                            }

#define DELAY_5US_EXINT()                   {\
                                                g_ucDelay5usI_EXINT = (g_ucDelay5usN_Base);\
                                                while(--g_ucDelay5usI_EXINT) {};\
                                            }

#define DELAY_10US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_10US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_15US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_15US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_20US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_20US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_25US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_25US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_30US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_30US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_35US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_35US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_40US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_40US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_45US()                        {\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                                DELAY_5US();\
                                            }

#define DELAY_45US_EXINT()                  {\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                                DELAY_5US_EXINT();\
                                            }

#define DELAY_XUS_BASE()                    {\
                                                g_ucDelay5usI = (g_ucDelayXusN_Base);\
                                                while(--g_ucDelay5usI) {};\
                                            }

#define DELAY_XUS_BASE_EXINT()              {\
                                                g_ucDelay5usI_EXINT = (g_ucDelayXusN_Base);\
                                                while(--g_ucDelay5usI_EXINT) {};\
                                            }

// Delay 50~1000 us
#define DELAY_XUS(N)                        {\
                                                g_ucDelayXus_Counter = (N) >> 2;\
                                                do\
                                                {\
                                                    DELAY_XUS_BASE();\
                                                }\
                                                while(--g_ucDelayXus_Counter);\
                                            }

#define DELAY_XUS_EXINT(N)                  {\
                                                g_ucDelayXus_Counter_EXINT = (N) >> 2;\
                                                do\
                                                {\
                                                    DELAY_XUS_BASE_EXINT();\
                                                }\
                                                while(--g_ucDelayXus_Counter_EXINT);\
                                            }

//--------------------------------------------------
// Macros of MCU Watch Dog
//--------------------------------------------------
#define CLR_MCU_WATCH_DOG()                 (MCU_FFEA_WATCHDOG_TIMER |= _BIT6)

//--------------------------------------------------
// Macros of SW IIC Status
//--------------------------------------------------
#if(_SW_IIC_SUPPORT == _ON)
#define GET_SW_IIC_STATUS()                 (g_ucSwIICStatus)
#define SET_SW_IIC_STATUS(x)                (g_ucSwIICStatus = (x))
#define GET_SW_IIC_SCLREGADDR()             (g_wSwIIC_SCLRegAddr)
#define SET_SW_IIC_SCLREGADDR(x)            (g_wSwIIC_SCLRegAddr = (x))
#define GET_SW_IIC_SDAREGADDR()             (g_wSwIIC_SDARegAddr)
#define SET_SW_IIC_SDAREGADDR(x)            (g_wSwIIC_SDARegAddr = (x))
#define GET_SW_IIC_SFR_CONTROL()            (g_uSwIIC_SFRControl)
#define SET_SW_IIC_SFR_CONTROL(x)           (g_uSwIIC_SFRControl = (x))

#if(_SW_IIC_CLK_DIV == _DIV_1)
#define SW_IIC_DELAY_TIME()                 {DELAY_5US();}
#elif(_SW_IIC_CLK_DIV == _DIV_2)
#define SW_IIC_DELAY_TIME()                 {DELAY_10US();}
#elif(_SW_IIC_CLK_DIV == _DIV_3)
#define SW_IIC_DELAY_TIME()                 {DELAY_15US();}
#elif(_SW_IIC_CLK_DIV == _DIV_4)
#define SW_IIC_DELAY_TIME()                 {DELAY_20US();}
#elif(_SW_IIC_CLK_DIV == _DIV_5)
#define SW_IIC_DELAY_TIME()                 {DELAY_25US();}
#elif(_SW_IIC_CLK_DIV == _DIV_6)
#define SW_IIC_DELAY_TIME()                 {DELAY_30US();}
#else
#define SW_IIC_DELAY_TIME()                 {DELAY_35US();}
#endif

#endif

//--------------------------------------------------
// MACRO for RUN DDCCI Command
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND()             (g_bRunDdcciCommand)
#define SET_RUN_DDCCI_COMMAND(x)            (g_bRunDdcciCommand = (x))

//--------------------------------------------------
// MACRO for Receive DDCCI Command
//--------------------------------------------------
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
#define GET_RECEIVE_DDCCI_CMD_NOT_FINISH()  (g_bReceiveDdcciCmdNotFinish)
#define SET_RECEIVE_DDCCI_CMD_NOT_FINISH()  (g_bReceiveDdcciCmdNotFinish = _TRUE)
#define CLR_RECEIVE_DDCCI_CMD_NOT_FINISH()  (g_bReceiveDdcciCmdNotFinish = _FALSE)
#endif

//--------------------------------------------------
// MACRO for RUN DDCCI Command Source
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND_SRC()         (g_enumDdcciCommandSrc)
#define SET_RUN_DDCCI_COMMAND_SRC(x)        (g_enumDdcciCommandSrc = (x))

//--------------------------------------------------
// Macros of TypeC IRQ Control
//--------------------------------------------------
#define SET_TYPE_C_GLOBAL_IRQ_ENABLE(x)     {\
                                                if((x) == _ENABLE)\
                                                {\
                                                    MCU_FD29_UFP_DPF_IRQ_STATUS |= (_BIT7 | _BIT6);\
                                                }\
                                                else\
                                                {\
                                                    MCU_FD29_UFP_DPF_IRQ_STATUS &= ~_BIT6;\
                                                }\
                                            }
#define CLR_TYPE_C_GLOBAL_IRQ()             (MCU_FD29_UFP_DPF_IRQ_STATUS |= _BIT7)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DDCCI Auto Switch DDC Channel
//--------------------------------------------------
typedef enum
{
    _DDCCI_ADC_DDC = 0x00,
    _DDCCI_DDC0,
    _DDCCI_DDC1,
    _DDCCI_DDC2,
    _DDCCI_DDC3,
    _DDCCI_DDC4,
    _DDCCI_DDC5,
    _DDCCI_ADC_DDC2 = 0x08,
} EnumDdcciAutoSwitchDdcChannel;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern BYTE data g_ucDelay5usN_Base;
extern BYTE data g_ucDelayXusN_Base;
extern BYTE data g_ucDelay5usI;
extern BYTE data g_ucDelay5usI_EXINT;
extern BYTE data g_ucDelayXus_Counter;
extern BYTE data g_ucDelayXus_Counter_EXINT;
extern bit g_bRunDdcciCommand;
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
extern bit g_bReceiveDdcciCmdNotFinish;
#endif
extern EnumDdcciCmdSrc g_enumDdcciCommandSrc;

#if(_SW_IIC_SUPPORT == _ON)
extern BYTE idata g_ucSwIICStatus;
extern WORD g_wSwIIC_SCLRegAddr;
extern WORD g_wSwIIC_SDARegAddr;
extern BYTE g_uSwIIC_SFRControl;
#endif

#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_A0[_A0_EMBEDDED_DDCRAM_MAX_SIZE];
#endif

#if(_D0_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D0[_D0_EMBEDDED_DDCRAM_MAX_SIZE];
#endif

#if(_D1_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D1[_D1_EMBEDDED_DDCRAM_MAX_SIZE];
#endif

#if(_D2_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D2[_D2_EMBEDDED_DDCRAM_MAX_SIZE];
#endif

#if(_D3_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D3[_D3_EMBEDDED_DDCRAM_MAX_SIZE];
#endif

#if(_D4_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D4[_D4_EMBEDDED_DDCRAM_MAX_SIZE];
#endif

#if(_D5_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D5[_D5_EMBEDDED_DDCRAM_MAX_SIZE];
#endif


#if(_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D0[_D0_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D1[_D1_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D2[_D2_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D3[_D3_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D4[_D4_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D5[_D5_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D6[_D6_EMBEDDED_DDCRAM_MAX_SIZE];
#endif // End of #if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)


extern BYTE g_pucDdcciRxBuf[_DDCCI_RXBUF_LENGTH];
extern BYTE g_pucDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

#if(_HW_IIC_SUPPORT == _ON)
extern BYTE g_ucHwI2cSettingIndex;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern void ScalerMcuDdcciSetData(BYTE *pucReadArray, BYTE ucLength, EnumDdcciCmdSrc enumDdcciCmdSrc);
#endif

extern void ScalerMcu5usDelayCalc(EnumClkSel enumClock);

#if(_SW_IIC_SUPPORT == _ON)
extern bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

#if(_HW_IIC_SUPPORT == _ON)
extern void ScalerMcuHwIICConfigSetting(EnumHWIICParType enumParType);
extern void ScalerMcuHwIICInitial(void);
extern bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
extern bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

extern void ScalerMcuIspInitial(void);
