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
// ID Code      : ScalerCommonMcuInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Macros of MCU Watch Dog
//--------------------------------------------------
#define CLR_MCU_WATCH_DOG()                            (MCU_FFEA_WATCHDOG_TIMER |= _BIT6)

//--------------------------------------------------
// Macros of DDC-CI
//--------------------------------------------------
#define GET_DDCCI_SLAVE_ADDRESS()                      (MCU_FF23_IIC_SET_SLAVE & 0xFE)
#define GET_DDCCI_SUBADDRESS()                         (MCU_FF24_IIC_SUB_IN)
#define GET_DDCCI_DATA_IN()                            (MCU_FF25_IIC_DATA_IN)
#define GET_DDCCI_STATUS1()                            (MCU_FF27_IIC_STATUS)
#define GET_DDCCI_STATUS2()                            (MCU_FF29_IIC_STATUS2)
#define GET_DDCCI_IRQ_STATUS()                         (MCU_FF2A_IIC_IRQ_CONTROL2)

#define SET_DDCCI_SLAVE_ADDRESS(x)                     (MCU_FF23_IIC_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI_DATA_OUT(x)                          (MCU_FF26_IIC_DATA_OUT = (x))
#define CLR_DDCCI_STATUS1(x)                           (MCU_FF27_IIC_STATUS &= ~(x))
#define SET_DDCCI_STATUS2(x)                           (MCU_FF29_IIC_STATUS2 = (x))
#define SET_DDCCI_IRQ_STATUS(x)                        (MCU_FF2A_IIC_IRQ_CONTROL2 = (x))

//--------------------------------------------------
// MACRO for RUN DDCCI Command
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND()                        (g_bRunDdcciCommand)
#define SET_RUN_DDCCI_COMMAND(x)                       (g_bRunDdcciCommand = (x))

//--------------------------------------------------
// MACRO for Receive DDCCI Command
//--------------------------------------------------
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
#define GET_RECEIVE_DDCCI_CMD_NOT_FINISH()             (g_bReceiveDdcciCmdNotFinish)
#define SET_RECEIVE_DDCCI_CMD_NOT_FINISH()             (g_bReceiveDdcciCmdNotFinish = _TRUE)
#define CLR_RECEIVE_DDCCI_CMD_NOT_FINISH()             (g_bReceiveDdcciCmdNotFinish = _FALSE)
#endif

//--------------------------------------------------
// MACRO for RUN DDCCI Command Source
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND_SRC()                    (g_enumDdcciCommandSrc)
#define SET_RUN_DDCCI_COMMAND_SRC(x)                   (g_enumDdcciCommandSrc = (x))

//--------------------------------------------------
// Macros of 5us Delay
//--------------------------------------------------
#define ScalerDelay5us()                               {\
                                                           g_ucDelay5usI = g_ucDelay5usN_Base;\
                                                           while(--g_ucDelay5usI) {};\
                                                       }

//--------------------------------------------------
// Macros of SW IIC Status
//--------------------------------------------------
#if(_SW_IIC_SUPPORT == _ON)
#define GET_SW_IIC_STATUS()                            (g_ucSwIICStatus)
#define SET_SW_IIC_STATUS(x)                           (g_ucSwIICStatus = (x))
#define GET_SW_IIC_SCLREGADDR()                        (g_wSwIIC_SCLRegAddr)
#define SET_SW_IIC_SCLREGADDR(x)                       (g_wSwIIC_SCLRegAddr = (x))
#define GET_SW_IIC_SDAREGADDR()                        (g_wSwIIC_SDARegAddr)
#define SET_SW_IIC_SDAREGADDR(x)                       (g_wSwIIC_SDARegAddr = (x))
#define GET_SW_IIC_SFR_CONTROL()                       (g_uSwIIC_SFRControl)
#define SET_SW_IIC_SFR_CONTROL(x)                      (g_uSwIIC_SFRControl = (x))
#endif

//--------------------------------------------------
// Macros of UART Status
//--------------------------------------------------
#if(_UART_SUPPORT == _ON)
#define GET_UART_TRANSMIT_STATUS()                     (TI)
#define CLR_UART_TRANSMIT_STATUS()                     (TI = 0)

#define GET_UART_RECEIVE_STATUS()                      (RI)
#define CLR_UART_RECEIVE_STATUS()                      (RI = 0)

#define GET_UART_DATA()                                (SBUF)
#endif

//--------------------------------------------------
// Macros of DDC-CI
//--------------------------------------------------
#define GET_DDCCI_AUTO_SWITCH()                        ((bit)(MCU_FF2A_IIC_IRQ_CONTROL2 & _BIT4))
#define SET_DDCCI_AUTO_SWITCH()                        (MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT4)
#define CLR_DDCCI_AUTO_SWITCH()                        (MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT4)

//--------------------------------------------------
// Macros of relocatable user bank
//--------------------------------------------------
#define SET_BANK_SWITCH_OFFSET(x)                      (g_ucBankOffset = (x))


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
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

#if(_D6_EMBEDDED_DDCRAM_MAX_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D6[_D6_EMBEDDED_DDCRAM_MAX_SIZE];
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

extern BYTE g_pucDdcciRxBuf[_DDCCI_RXBUF_LENGTH];
extern BYTE g_pucDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
extern BYTE data g_ucBankOffset;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMcuCacheControl(bit bControl);
extern void ScalerMcuDdcciSendData(BYTE *pucWriteArray);

#if(_DDCCI_CODE_REDUCTION == _OFF)
extern BYTE ScalerMcuDdcciGetBufferSize(void);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE ScalerMcuDdcciGetInputPort_EXINT1(void);
#endif
#endif
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern BYTE ScalerMcuDdcciIntGetData_EXINT1(BYTE *pucReadArray);
#endif

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
extern void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable);
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
extern void ScalerMcuIntoIdle(void);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
extern void ScalerMcuSarAdcClkSel(EnumClkSel enumClock);
#endif

#if(_PWM_FUNCTION_SUPPORT == _ON)
extern void ScalerMcuPwmClockSel(EnumClkSel enumClock);
extern void ScalerMcuPwmAdjustResetByDvs(BYTE ucPwmType, bit bStatus);
extern bit ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency);
#endif

extern void ScalerMcu5usDelayCalc(EnumClkSel enumClock);

#if(_SW_IIC_SUPPORT == _ON)
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr);
#endif
extern bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

#if(_HW_IIC_SUPPORT == _ON)
extern void ScalerMcuHwIICConfigSetting(EnumHWIICParType enumParType);
extern void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
extern bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
extern bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

#if(_UART_SUPPORT == _ON)
extern bit ScalerMcuUartWrite(BYTE ucValue);
#endif

#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
extern void ScalerMcuBootInitial(void);
#endif

