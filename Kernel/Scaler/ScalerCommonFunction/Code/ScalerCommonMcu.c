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
// ID Code      : ScalerCommonMcu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_MCU__

#include "ScalerCommonFunctionInclude.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions DDCCI Protocol Items
//--------------------------------------------------
#define _DDCCI_LENGTH                       1

//--------------------------------------------------
// Definitions of Hardware IIC
//--------------------------------------------------
#define _HW_IIC_BUFFER_SIZE                 24
#define _HW_IIC_DELAY_TIME                  5

//--------------------------------------------------
// Definitions of Software IIC
//--------------------------------------------------
#define _IIC_POLLING_TIME                   240

#if((_INSTANT_TIMER_EVENT_1 == _ON) && (_UART_SUPPORT == _ON))
#error "Instant Timer1 cannot be used when UART is supported"
#endif

//--------------------------------------------------
// Definitions DDCCI Protocol Items
//--------------------------------------------------
#define _DDCCI_BUFFER_SIZE                  32

// If User Don't Want to Save Tx Buf Size, Reduce the Available DDCCI Buf Size
#if(_DDCCI_TXBUF_LENGTH < _DDCCI_BUFFER_SIZE)
#undef _DDCCI_BUFFER_SIZE
#define _DDCCI_BUFFER_SIZE                  _DDCCI_TXBUF_LENGTH
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_HW_IIC_SUPPORT == _ON)
StructHwI2cSettingData code tHwI2cSetting[] =
{
    // KERNAL _HW_IIC_LOW_SPEED_100K PARAMETWRS
    {0x26, 0x22, 0x2F, 0x2F, 0x36, 0x47, 0x03, 0x01, 0x02,},
    // KERNAL _HW_IIC_HIGH_SPEED_400K PARAMETWRS
    {0x0C, 0x04, 0x0E, 0x06, 0x09, 0x23, 0x03, 0x01, 0x02,},

#if(_HW_IIC_PAR_BY_USER_SUPPORT == _ON)
// Incldue User Paramters Setting
#include _USER_HW_IIC_PAR_INCLUDE
#endif
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//sfr CKCON = 0x8E;

BYTE idata g_ucDdcciCountEXINT;

BYTE data g_ucDelay5usN_Base = 1;
BYTE data g_ucDelayXusN_Base = 1;
BYTE data g_ucDelay5usI = 1;
BYTE data g_ucDelay5usI_EXINT = 1;
BYTE data g_ucDelayXus_Counter = 1;
BYTE data g_ucDelayXus_Counter_EXINT = 1;

bit g_bRunDdcciCommand = _FAIL;
#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
bit g_bReceiveDdcciCmdNotFinish = _FAIL;
#endif
EnumDdcciCmdSrc g_enumDdcciCommandSrc = _DDCCI_CMD_SRC_I2C;

BYTE g_pucDdcciRxBuf[_DDCCI_RXBUF_LENGTH];
BYTE g_pucDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

#if(_SW_IIC_SUPPORT == _ON)
BYTE idata g_ucSwIICStatus;
WORD g_wSwIIC_SCLRegAddr;
WORD g_wSwIIC_SDARegAddr;
BYTE g_uSwIIC_SFRControl;
#endif

#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
BYTE data g_ucBankOffset                               _at_     0x30;
#endif

#if(_HW_IIC_SUPPORT == _ON)
BYTE g_ucHwI2cSettingIndex = _HW_IIC_SPEED;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMcuCacheControl(bit bControl);
void ScalerMcuDdcciSendData(BYTE *pucWriteArray);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
void ScalerMcuDdcciSetData(BYTE *pucReadArray, BYTE ucLength, EnumDdcciCmdSrc enumDdcciCmdSrc);
#endif

#if(_DDCCI_CODE_REDUCTION == _OFF)
BYTE ScalerMcuDdcciGetBufferSize(void);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
BYTE ScalerMcuDdcciGetInputPort_EXINT1(void);
#endif
#endif
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
BYTE ScalerMcuDdcciIntGetData_EXINT1(BYTE *pucReadArray);
#endif

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv);
void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable);
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
void ScalerMcuIntoIdle(void);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
void ScalerMcuSarAdcClkSel(EnumClkSel enumClock);
#endif

#if(_PWM_FUNCTION_SUPPORT == _ON)
void ScalerMcuPwmClockSel(EnumClkSel enumClock);
void ScalerMcuPwmAdjustResetByDvs(BYTE ucPwmType, bit bStatus);
bit ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency);
#endif

void ScalerMcu5usDelayCalc(EnumClkSel enumClock);

#if(_SW_IIC_SUPPORT == _ON)
BYTE ScalerMcuIICStart(BYTE ucSlaveAddr);
void ScalerMcuIICStop(void);
BYTE ScalerMcuIICGetAck(void);
void ScalerMcuIICSendAck(void);
void ScalerMcuIICSendNoAck(void);
BYTE ScalerMcuIICGetByte(void);
BYTE ScalerMcuIICSendByte(BYTE ucValue);
bit ScalerMcuIICWriteStart(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr);
#endif
bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

#if(_HW_IIC_SUPPORT == _ON)
void ScalerMcuHwIICConfigSetting(EnumHWIICParType enumParType);
void ScalerMcuHwIICInitial(void);
void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

#if(_UART_SUPPORT == _ON)
bit ScalerMcuUartWrite(BYTE ucValue);
#endif

void ScalerMcuIspInitial(void);

#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
void ScalerMcuBootInitial(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Cache Control
// Input Value  : bControl
// Output Value : None
//--------------------------------------------------
void ScalerMcuCacheControl(bit bControl)
{
    if(bControl == _ENABLE)
    {
        // Enable Cache
        MCU_FDA0_CACHE_FUNCTION |= _BIT0;
    }
    else
    {
        // Disable Cache
        MCU_FDA0_CACHE_FUNCTION &= ~_BIT0;
    }
}

//--------------------------------------------------
// Description  : Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
//                usTimeOutCnt --> Timeout
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    // Enable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DDCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FF29_IIC_STATUS2 & _BIT2) == 0)
        {
            MCU_FF26_IIC_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set DDC Data
// Input Value  : *pucReadArray, ucLength, enumDdcciCmdSrc
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSetData(BYTE *pucReadArray, BYTE ucLength, EnumDdcciCmdSrc enumDdcciCmdSrc)
{
    memcpy(g_pucDdcciRxBuf, pucReadArray, ucLength);

    SET_RUN_DDCCI_COMMAND(_SUCCESS);
    SET_RUN_DDCCI_COMMAND_SRC(enumDdcciCmdSrc);
}
#endif

#if(_DDCCI_CODE_REDUCTION == _OFF)
//--------------------------------------------------
// Description  : Get DDC Buffer Size
// Input Value  : None
// Output Value : DDCCI Buffer Size
//--------------------------------------------------
BYTE ScalerMcuDdcciGetBufferSize(void)
{
    return _DDCCI_BUFFER_SIZE;
}

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
BYTE ScalerMcuDdcciGetInputPort_EXINT1(void) using 2
{
    BYTE ucInput = _NO_INPUT_PORT;

    switch(GET_DDC_CHANNEL())
    {
        case _VGA_DDC2:
        case _VGA_DDC:
            ucInput = _A0_INPUT_PORT;
            break;

        case _DDC0:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0))
            ucInput = _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC0))
            ucInput = _D1_INPUT_PORT;
#elif(((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC0)) ||\
      ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC0)))
            ucInput = _D2_INPUT_PORT;
#elif(((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC0)) ||\
      ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC0)))
            ucInput = _D3_INPUT_PORT;
#elif(((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC0)) ||\
      ((_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC0)))
            ucInput = _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC0))
            ucInput = _D5_INPUT_PORT;
#endif
            break;

        case _DDC1:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC1))
            ucInput = _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1))
            ucInput = _D1_INPUT_PORT;
#elif(((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC1)) ||\
      ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC1)))
            ucInput = _D2_INPUT_PORT;
#elif(((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC1)) ||\
      ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC1)))
            ucInput = _D3_INPUT_PORT;
#elif(((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC1)) ||\
      ((_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC1)))
            ucInput = _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC1))
            ucInput = _D5_INPUT_PORT;
#endif
            break;

        case _DDC2:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC2))
            ucInput = _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC2))
            ucInput = _D1_INPUT_PORT;
#elif(((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC2)) ||\
      ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC2)))
            ucInput = _D2_INPUT_PORT;
#elif(((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC2)) ||\
      ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC2)))
            ucInput = _D3_INPUT_PORT;
#elif(((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC2)) ||\
      ((_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC2)))
            ucInput = _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC2))
            ucInput = _D5_INPUT_PORT;
#endif
            break;

        case _DDC3:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC3))
            ucInput = _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC3))
            ucInput = _D1_INPUT_PORT;
#elif(((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC3)) ||\
      ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC3)))
            ucInput = _D2_INPUT_PORT;
#elif(((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC3)) ||\
      ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC3)))
            ucInput = _D3_INPUT_PORT;
#elif(((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC3)) ||\
      ((_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC3)))
            ucInput = _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC3))
            ucInput = _D5_INPUT_PORT;
#endif
            break;

        case _DDC4:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC4))
            ucInput = _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC4))
            ucInput = _D1_INPUT_PORT;
#elif(((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC4)) ||\
      ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC4)))
            ucInput = _D2_INPUT_PORT;
#elif(((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC4)) ||\
      ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC4)))
            ucInput = _D3_INPUT_PORT;
#elif(((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC4)) ||\
      ((_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC4)))
            ucInput = _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC4))
            ucInput = _D5_INPUT_PORT;
#endif
            break;

        case _DDC5:
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC5))
            ucInput = _D0_INPUT_PORT;
#elif((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC5))
            ucInput = _D1_INPUT_PORT;
#elif(((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _DDC5)) ||\
      ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC5)))
            ucInput = _D2_INPUT_PORT;
#elif(((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _DDC5)) ||\
      ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC5)))
            ucInput = _D3_INPUT_PORT;
#elif(((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _DDC5)) ||\
      ((_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC5)))
            ucInput = _D4_INPUT_PORT;
#elif((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _DDC5))
            ucInput = _D5_INPUT_PORT;
#endif
            break;

        default:
            ucInput = _NO_INPUT_PORT;
            break;
    }

    return ucInput;
}
#endif
#endif
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#include _OSD_INCLUDE
#include _FACTORY_INCLUDE

//--------------------------------------------------
// Description  : Get DDC-CI Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcciIntGetData_EXINT1(BYTE *pucReadArray) using 2
{
    // Get DDC-CI Source Address
    if((MCU_FF27_IIC_STATUS & _BIT1) == _BIT1)
    {
        g_ucDdcciCountEXINT = 0;

        // Save Address
        pucReadArray[g_ucDdcciCountEXINT++] = MCU_FF24_IIC_SUB_IN;

        // Clear Flag
        MCU_FF27_IIC_STATUS &= ~_BIT1;
    }

    if((MCU_FF27_IIC_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FF29_IIC_STATUS2 & _BIT1) == 0)
        {
            if(g_ucDdcciCountEXINT >= _DDCCI_RXBUF_LENGTH)
            {
                // Reset data buffer
                MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

                g_ucDdcciCountEXINT = 0;

                break;
            }

            pucReadArray[g_ucDdcciCountEXINT++] = MCU_FF25_IIC_DATA_IN;
            //Kernel_updata_20151014 start
#if(_USER_ADJUST_GAMMA_FOR_BEACON == _ON)
#if (_USER_SHOW_DEBUG_OSD == _ON)
            //memcpy(g_ucDebugValue,pucReadArray,39);
#endif
            if(pucReadArray[0] != 0x51)
            {
                if(g_ucDdcciCountEXINT == 2)
                {
                    if((pucReadArray[1] == (IIC_COM_ADDRESS^pucReadArray[0])))
                    {
                        if(pucReadArray[0]==READ_HARDWAREINFO)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = _HARDWARE_VERSION;
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^_HARDWARE_VERSION;
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_SOFTWAREINFO)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = _SOFTWARE_VERSION;
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^_SOFTWARE_VERSION;
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_POWER_STATE)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_IIC_POWER_FLAG();//GET_POWERSTATUS();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^GET_IIC_POWER_FLAG();//GET_POWERSTATUS();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_BACKLIGHT)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_OSD_BACKLIGHT();//stSystemData.BackLight;
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^GET_OSD_BACKLIGHT();//stSystemData.BackLight;
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_CONTRAST)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_OSD_CONTRAST();//(stConBriData.Contrast - 78);
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^GET_OSD_CONTRAST();//(stConBriData.Contrast - 78);
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_GAMMA)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_OSD_GAMMA();//GET_GammaType();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^GET_OSD_GAMMA();//GET_GammaType();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_COLORTEMP)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_COLOR_TEMP_TYPE();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ GET_COLOR_TEMP_TYPE();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_SCREENSAVERS_STATE)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = (GET_IIC_POWER_FLAG() == _POWER_STATUS_SAVING);//GET_ScreenPowerSaving();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ (GET_IIC_POWER_FLAG() == _POWER_STATUS_SAVING);//GET_ScreenPowerSaving();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_COMMAND_EXECUTION)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_COMMAND_STATE();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ GET_COMMAND_STATE();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_CHECK_OK)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_CHECK_STATE();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^GET_CHECK_STATE();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            CLR_CHECK_STATE();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==READ_CHECK_STATE)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_CHECK_STATE();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ GET_CHECK_STATE();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            CLR_CHECK_STATE();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==GET_SN)
                        {
                            BYTE xdata cnt;
                            BYTE xdata checksum = 0;
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            for(cnt = 0; cnt < _MONITOR_SN_LENGTH; cnt++)
                            {
                                MCU_FF26_IIC_DATA_OUT = ucMonitorSn[cnt];
                                checksum = checksum^ucMonitorSn[cnt];
                            }
                            MCU_FF26_IIC_DATA_OUT = checksum^IIC_COM_ADDRESS;
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            CLR_CHECK_STATE();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==GET_SN_CHECK)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_MONITOR_SN_STATE();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ GET_MONITOR_SN_STATE();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            CLR_MONITOR_SN_STATE();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0]==GET_TEMP_SENSOR_PWM)
                        {
                        #if 0
                            //BYTE Temperature;
                            #if(_BACKLIGHT_SENSOR == _ON) 
                            extern WORD Value2561;
                            extern WORD GetTargetSensorValue;
                            #endif
                            //extern WORD GetBlkTargetSensorValue(void);
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            
                            #if(_BACKLIGHT_SENSOR == _ENABLE) 
                            MCU_FF26_IIC_DATA_OUT = pData[0] = 0;        //Temperature
                            MCU_FF26_IIC_DATA_OUT = pData[1] = (BYTE)(Value2561>>8);    //backlightsensor high byte
                            MCU_FF26_IIC_DATA_OUT = pData[2] = (BYTE)(Value2561&0xFF);  //backlightsensor low byte
                            MCU_FF26_IIC_DATA_OUT = pData[3] = (BYTE)(GET_TARGET_SENSOR()>>8);  //Target value high byte
                            MCU_FF26_IIC_DATA_OUT = pData[4] = (BYTE)(GET_TARGET_SENSOR()&0xFF);  //Target value low byte
                            #elif(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
                            MCU_FF26_IIC_DATA_OUT = pData[0] = 0;        //Temperature
                            MCU_FF26_IIC_DATA_OUT = pData[1] = (BYTE)(GET_CURRENT_SENSOR()>>8);    //backlightsensor high byte
                            MCU_FF26_IIC_DATA_OUT = pData[2] = (BYTE)(GET_CURRENT_SENSOR()&0xFF);  //backlightsensor low byte
                            MCU_FF26_IIC_DATA_OUT = pData[3] = (BYTE)(GET_TARGET_SENSOR()>>8);  //Target value high byte
                            MCU_FF26_IIC_DATA_OUT = pData[4] = (BYTE)(GET_TARGET_SENSOR()&0xFF);  //Target value low byte
                            #else
                            MCU_FF26_IIC_DATA_OUT = pData[0] = 0x00;
                            MCU_FF26_IIC_DATA_OUT = pData[1] = 0x00;
                            MCU_FF26_IIC_DATA_OUT = pData[2] = 0x00;
                            MCU_FF26_IIC_DATA_OUT = pData[3] = 0x00;
                            MCU_FF26_IIC_DATA_OUT = pData[4] = 0x00;
                            #endif
                            
                            #if(_BACKLIGHT_PWM_INVERSE == _ON)
                            MCU_FF26_IIC_DATA_OUT = pData[5] = (4095 - MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))>>8;                           //PWM high byte
                            MCU_FF26_IIC_DATA_OUT = pData[6] = (4095 - MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))&0xff;  //PWM low byte
                            #else
                            MCU_FF26_IIC_DATA_OUT = pData[5] = MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM)>>8;
                            MCU_FF26_IIC_DATA_OUT = pData[6] = MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM)&0xff;
                            #endif
                            
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^pData[0]^pData[1]^pData[2]^pData[3]^pData[4]^pData[5]^pData[6];
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
             
                        #endif

                            SET_SEND_SENSOR_DATA();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;                            
                        }
#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _OFF) 
                        else if(pucReadArray[0]==CMD_GET_COMPLETE_STATUS)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_AUTO_COMPLETE();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ GET_AUTO_COMPLETE();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            CLR_AUTO_COMPLETE();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
#endif
#if(_GAMMA_IN_FLASH_BANK == _ON) 
#if(BEACON_GAMMA_TYPE != Gamma_default)

#else
#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)                                          
                        else if(pucReadArray[0] == GET_TOTAL_CHECKSUM_STATUS)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_CheckSum_OK_OF_FLASH();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ GET_CheckSum_OK_OF_FLASH();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            CLR_CheckSum_OK_OF_FLASH();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }
                        else if(pucReadArray[0] ==  CMD_GET_COMPLETE_STATUS)
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x60;
                            MCU_FF26_IIC_DATA_OUT = GET_SaveGamma_OK_OF_FLASH();
                            MCU_FF26_IIC_DATA_OUT = IIC_COM_ADDRESS^ GET_SaveGamma_OK_OF_FLASH();
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);
                            CLR_SaveGamma_OK_OF_FLASH();
                            g_ucDdcciCountEXINT = 0;
                            return _FAIL;
                        }                        
#endif
#endif
#endif                       
                        else if(pucReadArray[0]==SET_BACKLIGHT_ADD)
                        {
                            if(GET_OSD_BACKLIGHT()<_OSD_BriCon_RANGE)
                                GET_OSD_BACKLIGHT()++;
                            else
                                GET_OSD_BACKLIGHT()=_OSD_BriCon_RANGE;
                            
                            SET_CHECK_STATE();
                            SET_BACKLIGHT_COM();
                        }
                        else if(pucReadArray[0]==SET_BACKLIGHT_REDUCE)
                        {
                            if(GET_OSD_BACKLIGHT()>0)
                                GET_OSD_BACKLIGHT()--;
                            else
                                GET_OSD_BACKLIGHT()=0;
                            
                            SET_CHECK_STATE();
                            SET_BACKLIGHT_COM();
                        }
                        else if(pucReadArray[0]==SET_CONTRAST_ADD)
                        {
                            if(GET_OSD_CONTRAST()<_OSD_BriCon_RANGE)
                                GET_OSD_CONTRAST()++;
                            else
                                GET_OSD_CONTRAST()=_OSD_BriCon_RANGE;
                            
                            SET_CHECK_STATE();
                            SET_CONTRAST_COM();
                        }
                        else if(pucReadArray[0]==SET_CONTRAST_REDUCE)
                        {
                            if(GET_OSD_CONTRAST()>0)
                                GET_OSD_CONTRAST()--;
                            else
                                GET_OSD_CONTRAST()=0;
                            
                            SET_CHECK_STATE();
                            SET_CONTRAST_COM();
                        }
                        else if(pucReadArray[0] ==SET_BRIGHTNESS_REDUCE)
                        {
                            CLR_CHECK_STATE();
                            if(GET_OSD_BRIGHTNESS()>0)
                                GET_OSD_BRIGHTNESS()--;
                            else
                                GET_OSD_BRIGHTNESS()=0;
                            
                            SET_CHECK_STATE();
                            SET_BRIGHTNESS_COM();
                            CLR_COMMAND_STATE();
                            SET_IIC_DONE_STATE();
                        }
                        else if(pucReadArray[0] ==SET_BRIGHTNESS_ADD)
                        {
                            CLR_CHECK_STATE();
                            if(GET_OSD_BRIGHTNESS()<_OSD_BriCon_RANGE)
                                GET_OSD_BRIGHTNESS()++;
                            else
                                GET_OSD_BRIGHTNESS()=_OSD_BriCon_RANGE;
                            
                            SET_CHECK_STATE();
                            SET_BRIGHTNESS_COM();
                            CLR_COMMAND_STATE();
                            SET_IIC_DONE_STATE();
                        }
                        else if(pucReadArray[0]==SET_DEFAULT)
                        {
                            GET_OSD_BACKLIGHT() = _DEFAULT_BACKLIGHT;
                            GET_OSD_CONTRAST() = _DEFAULT_CONTRAST;
                            GET_OSD_BRIGHTNESS() = _DEFAULT_BRIGHTNESS;
                            SET_CHECK_STATE();
                            SET_DEFAULT_COM();
                        }
                        else if(pucReadArray[0]==SET_POWER_ON)
                        {
                            SET_CHECK_STATE();
                            /*
                            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
                            {
                            SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                            }*/
                            SET_IIC_POWER_SWITCH_COM();
                            SET_IIC_POWER_FLAG();
                            CLR_COMMAND_STATE();
                        }
                        else if(pucReadArray[0]==SET_POWER_OFF)
                        {
                            SET_CHECK_STATE();/*
                            if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
                            {
                            SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
                            }*/
                            SET_IIC_POWER_SWITCH_COM();
                            CLR_IIC_POWER_FLAG();
                            CLR_COMMAND_STATE();
                        }
                        else if(pucReadArray[0]==COMMAND_SET_AUTO_ADJUST_FOR_GAMMA_ADJ)
                        {
                            CLR_CHECK_STATE();
                            SET_CHECK_STATE();
                            SET_AutoAdjust();
                            CLR_COMMAND_STATE();
                            //SET_IIC_DONE_STATE();
                        } 
                        else if(pucReadArray[0]==COMMAND_SET_AUTO_COLOR_FOR_GAMMA_ADJ)
                        {
                            CLR_CHECK_STATE();
                            SET_CHECK_STATE();
                            SET_AutoColor();
                            CLR_COMMAND_STATE();
                            //SET_IIC_DONE_STATE();
                        }
                        
                        CLR_COMMAND_STATE();

                        // All data are received
                        // Reset data buffer
                        // If we want to send data, please don't reset data buffer.
                        // It waiting for pc to read.
                        // MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
                        if(GET_CHECK_STATE())
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

                            g_ucDdcciCountEXINT = 0;

                            memset(pucReadArray, 0, _DDCCI_RXBUF_LENGTH);//Clear_g_ucDdcciRxBuf_20151016

                            return _FAIL;
                        }
                    }
                }
                else if(g_ucDdcciCountEXINT>2)
                {
                    if(pucReadArray[0]==Set_GAMMA_RGB)
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[7] == (IIC_COM_ADDRESS^pucReadArray[6]^pucReadArray[5]^pucReadArray[4]^pucReadArray[3]^pucReadArray[2]^pucReadArray[1]^pucReadArray[0])))
                        {
                            stGammaRGBdata.tR = (WORD)pucReadArray[1]|(WORD)(pucReadArray[2]<<8);
                            stGammaRGBdata.tG = (WORD)pucReadArray[3]|(WORD)(pucReadArray[4]<<8);
                            stGammaRGBdata.tB = (WORD)pucReadArray[5]|(WORD)(pucReadArray[6]<<8);
                            SET_CHECK_STATE();
                            SET_GAMMA_ZERO();
                            CLR_COMMAND_STATE();
                            //SET_IIC_DONE_STATE();
                        }
                    }
                    else if(pucReadArray[0]==SET_SCREENSAVERS_STATE)
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                            //modify yh_wang 13.12.27 start{
                            if(pucReadArray[1] == 1)
                            {
                                SET_SCREENSAVERS_FLAG(1);
                                SET_CHECK_STATE();
                                SET_SCREENSAVE_COM();
                                CLR_COMMAND_STATE();
                            }
                            else
                            {
                                SET_SCREENSAVERS_FLAG(0);
                                SET_CHECK_STATE();
                                SET_SCREENSAVE_OFF_COM();
                                CLR_COMMAND_STATE();
                            }
                            SET_IIC_DONE_STATE();
                            /*
                            SET_SCREENSAVERS_FLAG(Rx[1]);
                            SET_CHECK_STATE();
                            SET_SCREENSAVE_COM();
                            CLR_COMMAND_STATE();
                            */
                            //modify yh_wang 13.12.27 end}
                        }
                    }// break;
                    else if((pucReadArray[0]==SET_GAMMA)||(pucReadArray[0]==SET_GAMMA_FOR_GAMMA))
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                            if((pucReadArray[1]!=0)&&(pucReadArray[1]!=1)&&(pucReadArray[1]!=2)
                            &&(pucReadArray[1]!=3)&&(pucReadArray[1]!=4)&&(pucReadArray[1]!=5)
                            &&(pucReadArray[1]!=6))
                                pucReadArray[1]=0;
                                  
                            SET_OSD_GAMMA(pucReadArray[1]+1);
                            SET_CHECK_STATE();
                            SET_GAMMA_COM();
                            CLR_COMMAND_STATE();
                        }
                    }// break;
                    else if((pucReadArray[0]==SET_BACKLIGHT)||(pucReadArray[0]==SET_BACKLIGHT_FOR_GAMMA))
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                            if(pucReadArray[1] <= (_OSD_BriCon_RANGE-0))
                            {
                                GET_OSD_BACKLIGHT() = pucReadArray[1];
                                SET_CHECK_STATE();
                                SET_BACKLIGHT_COM();
                                CLR_COMMAND_STATE();
                                //SET_IIC_DONE_STATE();
                            }
                        }
                    }//break;
                    else if((pucReadArray[0]==SET_CONTRAST)||(pucReadArray[0]==SET_CONTRAST_FOR_GAMMA))
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                            if(pucReadArray[1] <= (_OSD_BriCon_RANGE-0))
                            {
                                GET_OSD_CONTRAST()= pucReadArray[1];
                                SET_CHECK_STATE();
                                SET_CONTRAST_COM();
                                CLR_COMMAND_STATE();
                                //SET_IIC_DONE_STATE();
                            }
                        }
                    }//break;
                    else if(pucReadArray[0] ==SET_BRIGHTNESS)
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                            if(pucReadArray[1] <= (_OSD_BriCon_RANGE-0))
                            {
                                GET_OSD_BRIGHTNESS()= pucReadArray[1];
                                SET_CHECK_STATE();
                                SET_BRIGHTNESS_COM();
                                CLR_COMMAND_STATE();
                                //SET_IIC_DONE_STATE();
                            }
                        }
                    }
                    else if((pucReadArray[0]==SET_COLORTEMP)||(pucReadArray[0]==SET_COLORTEMP_FOR_GAMMA))
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                            if((pucReadArray[1]!=0)&&(pucReadArray[1]!=1)&&(pucReadArray[1]!=2))//for CL1008T //	if((Rx[1]!=_CT_14000)&&(Rx[1]!=_CT_11000))
                                pucReadArray[1]=_DEFAULT_COLOR_TEMP;
                            
                            GET_COLOR_TEMP_TYPE() = pucReadArray[1];
                            SET_CHECK_STATE();
                            SET_COLORTEMP_COM();
                            CLR_COMMAND_STATE();
                            //SET_IIC_DONE_STATE();
                        }
                    }
                    else if(pucReadArray[0]==SET_BACKLIGHT_L) //case SET_BACKLIGHT_L:
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                           if(pucReadArray[1]<=255)
                           {
                    #if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
                                if(GET_IIC_SENSOR_BACKLIGHT_MID_STATE())
                                {
                                    //wait...
                                }
                                else if(!GET_IIC_SENSOR_BACKLIGHT_STOP_STATE())
                                {
                                    SET_BRIGHTPION();
                                    CLR_COMMAND_STATE();
                                }
                                else
                    #endif
                                {
                            #if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                                    SET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE(),pucReadArray[1]);
                                #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
                                #else
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN(GET_COLOR_TEMP_TYPE())));
                                #endif                               
                            #else
                                    SET_FACTORY_BACKLIGHT_REG_MIN(pucReadArray[1]);
                                #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MIN()));
                                #else
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MIN()));
                                #endif
                            #endif

                            #if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
                                    SET_OLED_BACKLIGHT_MIN_STATE();
                            #else
                                    SET_CHECK_STATE();
                            #endif
                                    SET_BRIGHTPION();
                                    CLR_COMMAND_STATE();
                                    //SET_IIC_DONE_STATE();
                                }
                           }
                        }
                    }// break;
                    else if(pucReadArray[0]==SET_BACKLIGHT_M)// case SET_BACKLIGHT_M:
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                           if(pucReadArray[1]<=255)
                           {
                        #if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                                SET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE(),pucReadArray[1]);
                            #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
                            #else
                                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID(GET_COLOR_TEMP_TYPE())));
                            #endif                               
                        #else
                                SET_FACTORY_BACKLIGHT_REG_MID(pucReadArray[1]);
                            #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MID()));
                            #else
                                PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MID()));
                            #endif
                        #endif

                        #if((_BACKLIGHT_SENSOR == _ON) || (_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON))
                                SET_IIC_SENSOR_BACKLIGHT_MID_STATE();
                        #endif                        

                        #if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
                                SET_OLED_BACKLIGHT_MID_STATE();
                        #else                     
                                SET_CHECK_STATE();
                        #endif
                                SET_BRIGHTPION();
                                CLR_COMMAND_STATE();
                                //SET_IIC_DONE_STATE();
                           }
                        }
                    }// break;
                    else if(pucReadArray[0]==SET_BACKLIGHT_H)// case SET_BACKLIGHT_H:
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                           if(pucReadArray[1]<=255)
                           {
                    #if(_NEW_BACKLIGHT_SENSOR_FUN_EN == _ON)
                                if(GET_IIC_SENSOR_BACKLIGHT_MID_STATE())
                                {
                                    //wait...
                                }
                                else if(!GET_IIC_SENSOR_BACKLIGHT_STOP_STATE())
                                {
                                    SET_BRIGHTPION();
                                    CLR_COMMAND_STATE();
                                }
                                else
                    #endif                           
                                {
                            #if(_SECOND_COLORTEMP_THREE_POINT == _ON)
                                    SET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE(),pucReadArray[1]);
                                #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
                                #else
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX(GET_COLOR_TEMP_TYPE())));
                                #endif                               
                            #else
                                    SET_FACTORY_BACKLIGHT_REG_MAX(pucReadArray[1]);
                                #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(255 - GET_FACTORY_BACKLIGHT_REG_MAX()));
                                #else
                                    PCB_BACKLIGHT_PWM(CAL_8BIT_PWM_TO_REAL_PWM(GET_FACTORY_BACKLIGHT_REG_MAX()));
                                #endif
                            #endif
     
                            #if(_OLED_PANEL_BACKLIGHT_AUX_CONTROL == _ON)
                                    SET_OLED_BACKLIGHT_MAX_STATE();
                            #else
                                    SET_CHECK_STATE();
                            #endif
                                    SET_BRIGHTPION();
                                    CLR_COMMAND_STATE();
                                    //SET_IIC_DONE_STATE();
                                }
                           }
                        }
                    }// 	break;
                    else if(pucReadArray[0]==Set_GAMMA_PASS)//	case Set_GAMMA_PASS:
                    {
                        CLR_CHECK_STATE();
                        if((pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[1]^pucReadArray[0])))
                        {
                            g_bGammaByPass = (bit)pucReadArray[1];
                            SET_CHECK_STATE();
                            SET_GAMMA_COM();
                            CLR_COMMAND_STATE();
                            //SET_IIC_DONE_STATE();
                        }
                    }// 	break;
                    else if(pucReadArray[0]==COMMAND_SET_CALIBRATION)// case COMMAND_SET_CALIBRATION:
                    {
                        if(g_ucDdcciCountEXINT == 3)//(i == 2) Add_g_ucDdcciCount_20151015
                        {
                            if(pucReadArray[2] == (IIC_COM_ADDRESS^pucReadArray[0]^pucReadArray[1]))
                            {
                                if(pucReadArray[1] == 1)
                                    SET_CALIBRATION_STRAT();
                                else
                                    CLR_CALIBRATION_STRAT();
                                
                                SET_CHECK_STATE();
                            }
                        }
                    }// 	break;
                    else if(pucReadArray[0]==SET_SN)
                    {
                        //if(g_ucDdcciCount == _MONITOR_SN_LENGTH + 2)
                        if(g_ucDdcciCountEXINT == pucReadArray[1] + 2)
                        {
                            memcpy(ucMonitorSn,pucReadArray+2,_MONITOR_SN_LENGTH);
                            //memcpy(ucMonitorSn,pucReadArray+2,pucReadArray[1]);

                            SET_MONITOR_SN_SAVE_COM();
                            SET_CHECK_STATE();
                            SET_MONITOR_SN_STATE();
                        }
                    }
#if(_GAMMA_IN_FLASH_BANK == _ON)
#if(BEACON_GAMMA_TYPE != Gamma_default)

#else
#if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
                    else if(pucReadArray[0]==Set_TRANSMIT_GAMMA_DATA_OF_FLASH)
                    {                   
                        WORD usDataIndex;
                        BYTE  ucGammaIndex,ucDataCount;
                        static BYTE ucCheckSum = 0;
                        BYTE i;
                        if(g_ucDdcciCountEXINT == pucReadArray[3] + 4) 
                        {
                            g_ucGammaIndex = ucGammaIndex   = ((pucReadArray[1]&0xf0)>>4);        
                            g_usDataIndex = usDataIndex     = (WORD)((pucReadArray[1]&0x0f)<<8)+pucReadArray[2]; 
                            g_ucDataCount = ucDataCount     = pucReadArray[3];
                            for( i = 0; i++; i<ucDataCount)
                            {       
                                ucCheckSum ^= pucReadArray[4 + i];
                            }
                            if(((usDataIndex + ucDataCount)== 768) && (ucCheckSum == pucReadArray[4 + ucDataCount -1]))
                            {
                                SET_CheckSum_OK_OF_FLASH();
                                
                                SET_SaveGamma_OK_OF_FLASH();
                                ucCheckSum = 0;
                                g_ucDataCount =  ucDataCount - 1;
                                //break;
                            }
                            SET_SaveGammaOneTime_OK_OF_FLASH();
                            //UserCommonFlashSaveGamma(ucGammaIndex, usDataIndex, ucDataCount, pReadArray + 4);
                            SET_CHECK_STATE();
                            CLR_COMMAND_STATE();
                            //if((usDataIndex + ucDataCount) >= 768)
                        }

                        
                    }
#endif
#endif
#endif
                    
                    // All data are received
                    // Reset data buffer
                #if(_SAVE_GAMMA_TO_FLASH_ON_LINE == _ON)
                    if((GET_CHECK_STATE() && !GET_SaveGammaOneTime_OK_OF_FLASH())||(g_ucDdcciCountEXINT >=_DDCCI_RXBUF_LENGTH))
                #else
                    if(GET_CHECK_STATE()||(g_ucDdcciCountEXINT >=_DDCCI_RXBUF_LENGTH))
                #endif
                    {
                #if (_USER_SHOW_DEBUG_OSD == _ON)
                        //memcpy(g_ucDebugValue+16,pucReadArray,8);
                #endif
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

                        g_ucDdcciCountEXINT = 0;

                        memset(pucReadArray, 0, _DDCCI_RXBUF_LENGTH);//Clear_g_ucDdcciRxBuf_20151016

                        return _FAIL;
                    }
                }
                /*
                MCU_I2C_STATUS_FF27 &= 0x0c;
                //to disable iic data buffer underflow as a interrupt
                MCU_I2C_STATUS2_FF29 = 0x00;
                EX1 = 1;

                */
            }
            else//if(pucReadArray[0] == 0x51)
#endif
			//Kernel_updata_20151014 end

            // All data are received
            if(((pucReadArray[_DDCCI_LENGTH] & 0x7F) + 3) == g_ucDdcciCountEXINT)
            {
                // Reset data buffer and Enable mcu write
                MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucDdcciCountEXINT = 0;

                for(pData_EXINT[0] = 32; pData_EXINT[0] > 0; pData_EXINT[0] --)
                {
                    MCU_FF26_IIC_DATA_OUT = 0;
                }

                // Disable mcu write
                MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;

                // Reset data buffer
                MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl_EXINT1();
                }
#endif
                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
//--------------------------------------------------
// Description  : Set Flash Clock Divider.
// Input Value  : ClkDiv --> Flash Clock Divider
// Output Value : None
//--------------------------------------------------
void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv)
{
    enumClkDiv &= 0x0F;
    enumClkDiv = (enumClkDiv << 2);
    enumClkDiv |= (MCU_FFED_MCU_CONTROL & 0xC3);
    MCU_FFED_MCU_CONTROL = enumClkDiv;
}

//--------------------------------------------------
// Description  : Set Flash & Mcu Divider when OSD is running.
// Input Value  : Fast or Low Speed
// Output Value : None
//--------------------------------------------------
void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable)
{
    // Only Take Effect when Flash Clk is From M2PLL
    if((MCU_FFED_MCU_CONTROL & _BIT1) == _BIT1)
    {
        if(bEnable == _ENABLE)
        {
            // Don't Switch Again If It's Already Using Fast Div
            if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) != _FLASH_CLK_FAST_DIV)
            {
                // Switch Flash and MCU Clock to high speed
                ScalerMcuFlashClockDiv(_FLASH_CLK_FAST_DIV);

                // Reload Timer Count
                ScalerTimerSetTimerCount(_TIMER_OPERATION_OSD_MODE);
            }
        }
        else if(bEnable == _DISABLE)
        {
            // Don't Switch Again If It's Already Using Normal Div
            if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) != _FLASH_CLK_DIV)
            {
                // Switch Flash and MCU Clock to low speed
                ScalerMcuFlashClockDiv(_FLASH_CLK_DIV);

                // Reload Timer Count
                ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_NORMAL_MODE);
            }
        }
    }
}
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable MCU Into Idle Mode
// Input Value  : None.
// Output Value : None
//--------------------------------------------------
void ScalerMcuIntoIdle(void)
{
    // Enable MCU into idle mode.
    PCON |= _BIT0;
}
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SARADC Clock Select.
// Input Value  : enumClock --> _M2PLL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuSarAdcClkSel(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // ADC clk from external Xtal and div by 4 to obtain clk target 3MHz
        MCU_FF0D_ADC_CLK_DIV = 0x04;
    }
    else
    {
        // ADC clk from IOSC(27M) and div by 9 to obtain clk target 3MHz
        MCU_FF0D_ADC_CLK_DIV = 0x09;
    }
}

#endif  // End of #if(_LOW_SPEED_ADC_SUPPORT == _ON)

#if(_PWM_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PWM Clock Switch.
// Input Value  : Clock --> _M2PLL_CLK/_EXT_XTAL_CLK(_IOSC_CLK)
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmClockSel(EnumClkSel enumClock)
{
    WORD usCLKDiv = 0;
    WORD usFrequency = 0;

    ////////////////////////////////
    // Adjust PWMx divider: M & N //
    ////////////////////////////////

#if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))

    // Get PWM0 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF3E_PWM0_N_LSB) + 1)
    usCLKDiv = (0x01 << (MCU_FF3B_PWM03_M & (_BIT1 | _BIT0))) * (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF3E_PWM0_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT0) == _BIT0)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT0;
    }
    else
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT0;
    }

    ScalerMcuPwmAdjustFrequency(_PWM0, usFrequency);

#endif // End of #if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))

#if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))

    // Get PWM1 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT3 | _BIT2)))
    // N = (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 8) | MCU_FF3F_PWM1_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3B_PWM03_M & (_BIT3 | _BIT2)) >> 2)) * (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF3F_PWM1_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT1) == _BIT1)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT1;
    }
    else
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT1;
    }

    ScalerMcuPwmAdjustFrequency(_PWM1, usFrequency);

#endif // End of #if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))

#if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))

    // Get PWM2 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT5 | _BIT4)))
    // N = (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF41_PWM2_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3B_PWM03_M & (_BIT5 | _BIT4)) >> 4)) * (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF41_PWM2_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT2) == _BIT2)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT2;
    }
    else
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT2;
    }

    ScalerMcuPwmAdjustFrequency(_PWM2, usFrequency);

#endif // End of #if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))

#if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))

    // Get PWM3 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT7 | _BIT6)))
    // N = (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF42_PWM3_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3B_PWM03_M & (_BIT7 | _BIT6)) >> 6)) * (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF42_PWM3_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT3) == _BIT3)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT3;
    }
    else
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT3;
    }

    ScalerMcuPwmAdjustFrequency(_PWM3, usFrequency);

#endif // End of #if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))

#if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))

    // Get PWM4 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3C_PWM45_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 8) | MCU_FF44_PWM4_N_LSB) + 1)
    usCLKDiv = (0x01 << (MCU_FF3C_PWM45_M & (_BIT1 | _BIT0))) * (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF44_PWM4_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT4) == _BIT4)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT4;
    }
    else
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT4;
    }

    ScalerMcuPwmAdjustFrequency(_PWM4, usFrequency);

#endif // End of #if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))

#if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))

    // Get PWM5 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3C_PWM45_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF44_PWM4_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3C_PWM45_M & (_BIT3 | _BIT2)) >> 2)) * (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF45_PWM5_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT5) == _BIT5)
    {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
        // Calculate N Divider for M2PLL / 2
        // HW Using M2Pll / 2 as PWM Reference Clock Source
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION / _DIV_2;
#else
        // Calculate N Divider for M2PLL
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
#endif
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _M2PLL_CLK)
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT5;
    }
    else
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT5;
    }

    ScalerMcuPwmAdjustFrequency(_PWM5, usFrequency);

#endif // End of #if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))
}

//--------------------------------------------------
// Description  : Adjust PWM reset by DVS
// Input Value  : ucPwmType --> _BACKLIGHT_PWM/_AUDIO_VOLUME...
//                bStatus --> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmAdjustResetByDvs(BYTE ucPwmType, bit bStatus)
{
    BYTE ucMask = 0;

    switch(ucPwmType)
    {
        case _PWM0:
            ucMask = _BIT0;
            break;
        case _PWM1:
            ucMask = _BIT1;
            break;
        case _PWM2:
            ucMask = _BIT2;
            break;
        case _PWM3:
            ucMask = _BIT3;
            break;
        case _PWM4:
            ucMask = _BIT4;
            break;
        case _PWM5:
            ucMask = _BIT5;
            break;
        default:
            break;
    }

    if(ucMask != 0)
    {
        if(bStatus == _ENABLE)
        {
            MCU_FF47_PWM_VS_CTRL |= ucMask;
        }
        else
        {
            MCU_FF47_PWM_VS_CTRL &= ~ucMask;
        }
    }
}

//--------------------------------------------------
// Description  : PWM Clock Switch.
// Input Value  : ucPwmType --> _BACKLIGHT_PWM/_AUDIO_VOLUME...
//                ucFrequency --> Frequency
// Output Value : None
//--------------------------------------------------
bit ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency)
{
    BYTE ucPWM_M = 0;
    WORD usPWM_N = 0;
    bit bCheckResult = _FALSE;

    // Set limit for Pwm frequency
    if((MCU_FF3A_PWM_CK_SEL & ucPwmType) == ucPwmType)
    {
        // Set limit for Pwm frequency
        if(usFrequency < _PWM_ACT_MODE_FREQ_LOW_BOUND)
        {
            usFrequency = _PWM_ACT_MODE_FREQ_LOW_BOUND;
            bCheckResult = _FALSE;
        }
        else if(usFrequency > _PWM_ACT_MODE_FREQ_UPPER_BOUND)
        {
            usFrequency = _PWM_ACT_MODE_FREQ_UPPER_BOUND;
            bCheckResult = _FALSE;
        }
        else
        {
            bCheckResult = _TRUE;
        }
    }
    else
    {
        // Set limit for Pwm frequency
        if(usFrequency < _PWM_PSPD_MODE_FREQ_LOW_BOUND)
        {
            usFrequency = _PWM_PSPD_MODE_FREQ_LOW_BOUND;
            bCheckResult = _FALSE;
        }
        else if(usFrequency > _PWM_PSPD_MODE_FREQ_UPPER_BOUND)
        {
            usFrequency = _PWM_PSPD_MODE_FREQ_UPPER_BOUND;
            bCheckResult = _FALSE;
        }
        else
        {
            bCheckResult = _TRUE;
        }
    }

#if(_PWM_FREQ_DVSRST_CHECK == _ON)
    if(usFrequency >= _PWM_FREQ_DVSRST_BOUND)
    {
        // Disable PWM reset by DVS
#if(_BACKLIGHT_PWM == _PWM0)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT0;

#elif(_BACKLIGHT_PWM == _PWM1)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT1;

#elif(_BACKLIGHT_PWM == _PWM2)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT2;

#elif(_BACKLIGHT_PWM == _PWM3)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT3;

#elif(_BACKLIGHT_PWM == _PWM4)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT4;

#elif(_BACKLIGHT_PWM == _PWM5)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT5;
#endif
    }
    else
    {
        // Enable PWM reset by DVS
#if(_BACKLIGHT_PWM == _PWM0)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM0_RST_EN);

#elif(_BACKLIGHT_PWM == _PWM1)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM1_RST_EN << 1);

#elif(_BACKLIGHT_PWM == _PWM2)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM2_RST_EN << 2);

#elif(_BACKLIGHT_PWM == _PWM3)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM3_RST_EN << 3);

#elif(_BACKLIGHT_PWM == _PWM4)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM4_RST_EN << 4);

#elif(_BACKLIGHT_PWM == _PWM5)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM5_RST_EN << 5);
#endif
    }
#endif

    // Check if PWM clk is M2PLL or IOSC
    if((MCU_FF3A_PWM_CK_SEL & ucPwmType) == ucPwmType)
    {
        for(ucPWM_M = 0; ucPWM_M < 4; ucPWM_M++)
        {
#if(_HW_MCU_PWM_HW_REF_HALF_OF_M2PLL == _ON)
            // Calculate N Divider for M2PLL / 2
            // HW Using M2Pll / 2 as PWM Reference Clock Source
            usPWM_N = ((DWORD)(((((DWORD)_M2PLL_CLK_KHZ * 1000) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);
#else
            // Calculate N Divider for Define [_M2PLL_CLK_KHZ]
            usPWM_N = ((DWORD)(((((DWORD)_M2PLL_CLK_KHZ * 1000 * 2) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);
#endif

            if(usPWM_N < 4096)
            {
                break;
            }
        }
    }
    else
    {
        for(ucPWM_M = 0; ucPWM_M < 4; ucPWM_M++)
        {
            // Calculate N Divider for IOSC clock
            usPWM_N = ((DWORD)(((((DWORD)_INTERNAL_OSC_XTAL * 1000 * 2) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);

            if(usPWM_N < 4096)
            {
                break;
            }
        }
    }

    // Load M/N divider to corresponding register
    switch(ucPwmType)
    {
#if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))
        case _PWM0:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT1 | _BIT0)) | (ucPWM_M);
            MCU_FF3D_PWM01_N_MSB &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
            MCU_FF3D_PWM01_N_MSB |= (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            MCU_FF3E_PWM0_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT0;

            break;
#endif

#if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))
        case _PWM1:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT3 | _BIT2)) | (ucPWM_M << 2);
            MCU_FF3D_PWM01_N_MSB &= ~(_BIT7 | _BIT6 | _BIT5 | _BIT4);
            MCU_FF3D_PWM01_N_MSB |= (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            MCU_FF3F_PWM1_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT1;

            break;
#endif

#if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))
        case _PWM2:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT5 | _BIT4)) | (ucPWM_M << 4);
            MCU_FF40_PWM23_N_MSB &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
            MCU_FF40_PWM23_N_MSB |= (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            MCU_FF41_PWM2_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT2;

            break;
#endif

#if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))
        case _PWM3:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT7 | _BIT6)) | (ucPWM_M << 6);
            MCU_FF40_PWM23_N_MSB &= ~(_BIT7 | _BIT6 | _BIT5 | _BIT4);
            MCU_FF40_PWM23_N_MSB |= (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            MCU_FF42_PWM3_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT3;

            break;
#endif

#if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))
        case _PWM4:

            MCU_FF3C_PWM45_M = (MCU_FF3C_PWM45_M & ~(_BIT1 | _BIT0)) | (ucPWM_M);
            MCU_FF43_PWM45_N_MSB &= ~(_BIT7 | _BIT6 | _BIT5 | _BIT4);
            MCU_FF43_PWM45_N_MSB |= (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            MCU_FF44_PWM4_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT4;

            break;
#endif

#if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))
        case _PWM5:

            MCU_FF3C_PWM45_M = (MCU_FF3C_PWM45_M & ~(_BIT3 | _BIT2)) | (ucPWM_M << 2);
            MCU_FF43_PWM45_N_MSB &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
            MCU_FF43_PWM45_N_MSB |= (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            MCU_FF45_PWM5_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT5;

            break;
#endif
        default:

            break;
    }
    return bCheckResult;
}
#endif // End of #if(_PWM_FUNCTION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : 5us Delay Calculation
// Input Value  : Clock --> _M2PLL_CLK/_IOSC_CLK
// Output Value : ucValue --> N
//--------------------------------------------------
void ScalerMcu5usDelayCalc(EnumClkSel enumClock)
{
    BYTE ucMcuDiv = 0;

    ucMcuDiv = ((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) * ((MCU_FFEE_MCU_CLOCK_CONTROL & 0x3C) >> 2);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Chart :                                                                                                      //
    //                                                                                                              //
    //  INOSC                                                                                                       //
    //    14.318MHz ---|   |      |IOSC|            |   |                                                           //
    //                 |Mux|------|DIV | -----------|   |                                                           //
    //    27MHz     ---|   |      |    |            |   |  EMCU Crystal |   |                                       //
    //                CR0B[0]   Page6 CRA0[1:0]     |Mux|---------------|   |                                       //
    //                                              |   |               |   |                                       //
    //                   external-crystal-----------|   |               |   |       |Flash|      |MCU|              //
    //                                              |   |               |Mux|-------|DIV  |------|DIV|------8051    //
    //                                             CR09[3]              |   |       |     |   |  |   |              //
    //                                                                  |   |     0xFFED[5:2] | 0xFFEE[5:2]         //
    //                                                M2PLL-------------|   |                 |                     //
    //                                                                  |   |                 |--|Flash|            //
    //                                                                0xFFED[1]                  |DIV2 |-----Flash  //
    //                                                                                          0xFFE9[3:0]         //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(enumClock == _M2PLL_CLK)
    {
        g_ucDelay5usN_Base = _M2PLL_DELAY6US_CNT;
        g_ucDelayXusN_Base = _M2PLL_DELAY4US_CNT;
    }
    else if(enumClock == _IOSC_CLK)
    {
        g_ucDelay5usN_Base = _IOSC_DELAY6US_CNT;
        g_ucDelayXusN_Base = _IOSC_DELAY4US_CNT;
    }
    else // For Xtal
    {
        g_ucDelay5usN_Base = _XTAL_DELAY6US_CNT;
        g_ucDelayXusN_Base = _XTAL_DELAY4US_CNT;
    }
}

#if(_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Software IIC Start
// Input Value  : ucSlaveAddr --> Slave Address
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuIICStart(BYTE ucSlaveAddr)
{
    BYTE ucTemp = 0;
    WORD usTimeOut = 6;

    PCB_SW_IIC_SCL_SET();
    PCB_SW_IIC_SDA_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CHK(ucTemp);

    while(ucTemp == _LOW)
    {
        if(usTimeOut > 0)
        {
            usTimeOut--;
            SW_IIC_DELAY_TIME();
        }
        else
        {
            return _FAIL;
        }

        PCB_SW_IIC_SCL_CHK(ucTemp);
    }

    PCB_SW_IIC_SDA_CLR();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CLR();

    SW_IIC_DELAY_TIME();

    return ScalerMcuIICSendByte(ucSlaveAddr);
}

//--------------------------------------------------
// Description  : Software IIC Stop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICStop(void)
{
    PCB_SW_IIC_SDA_CLR();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SDA_SET();
}

//--------------------------------------------------
// Description  : Software IIC Get Acknowledge
// Input Value  : None
// Output Value : ucAck --> 0: Ack / 1: Nack
//--------------------------------------------------
BYTE ScalerMcuIICGetAck(void)
{
    BYTE ucAck = 0;

    PCB_SW_IIC_SDA_SET();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SDA_CHK(ucAck);

    PCB_SW_IIC_SCL_CLR();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SDA_SET();

    return ucAck;
}

//--------------------------------------------------
// Description  : Software IIC Send Acknowledge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICSendAck(void)
{
    PCB_SW_IIC_SDA_CLR();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CLR();

    SW_IIC_DELAY_TIME();
}

//--------------------------------------------------
// Description  : Software IIC Send No-Acknowledge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICSendNoAck(void)
{
    PCB_SW_IIC_SDA_SET();
    PCB_SW_IIC_SCL_SET();

    SW_IIC_DELAY_TIME();

    PCB_SW_IIC_SCL_CLR();

    SW_IIC_DELAY_TIME();
}

//--------------------------------------------------
// Description  : Software IIC Read 1 Byte
// Input Value  : None
// Output Value : ucValue --> Received Byte
//--------------------------------------------------
#pragma save
#pragma OT(8)
BYTE ScalerMcuIICGetByte(void)
{
    BYTE ucTemp = 0;
    BYTE ucCnt = 0;
    BYTE ucValue = 0;

    PCB_SW_IIC_SDA_SET();

    for(ucCnt = 0; ucCnt < 8; ucCnt++)
    {
        PCB_SW_IIC_SCL_SET();

        SW_IIC_DELAY_TIME();

        PCB_SW_IIC_SDA_CHK(ucTemp);

        ucValue = (ucValue << 1) | ucTemp;

        PCB_SW_IIC_SCL_CLR();

        SW_IIC_DELAY_TIME();
    }

    return ucValue;
}
#pragma restore

//--------------------------------------------------
// Description  : SoftWare IIC Write 1 Byte
// Input Value  : ucValue --> Data to be transmitted
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
BYTE ScalerMcuIICSendByte(BYTE ucValue)
{
    BYTE ucCnt = 0;

    for(ucCnt = 0; ucCnt < 8; ucCnt++)
    {
        if((bit)(ucValue & _BIT7) == _HIGH)
        {
            PCB_SW_IIC_SDA_SET();
        }
        else
        {
            PCB_SW_IIC_SDA_CLR();
        }

        PCB_SW_IIC_SCL_SET();

        SW_IIC_DELAY_TIME();

        PCB_SW_IIC_SCL_CLR();

        if((MCU_FFED_MCU_CONTROL & _BIT1) == _BIT1)
        {
            SW_IIC_DELAY_TIME();
        }

        ucValue = ucValue << 1;
    }

    if(ScalerMcuIICGetAck() == _HIGH)
    {
        ScalerMcuIICStop();

        return _FAIL;
    }

    return _SUCCESS;
}
#pragma restore

//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICWriteStart(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr)
{
    if(ScalerMcuIICStart(ucSlaveAddr | _WRITE) == _FAIL)
    {
        return _FAIL;
    }

    switch(ucSubAddrLength)
    {
        case 1:

            if(ScalerMcuIICSendByte((BYTE)(usSubAddr)) == _FAIL)
            {
                return _FAIL;
            }

            break;

        case 2:

            if(ScalerMcuIICSendByte((BYTE)((usSubAddr & 0xFF00) >> 8)) == _FAIL)
            {
                return _FAIL;
            }
            else
            {
                if(ScalerMcuIICSendByte((BYTE)(usSubAddr)) == _FAIL)
                {
                    return _FAIL;
                }
            }

            break;

        default:

            break;
    }
    return _SUCCESS;
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr)
{
    if(ScalerMcuIICStart(ucSlaveAddr | _WRITE) == _FAIL)
    {
        return _FAIL;
    }

    ScalerMcuIICStop();

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Read data from the selected device by Software IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    if(usLength == 0)
    {
        return _FAIL;
    }

    if(ucSubAddrLength != 0)
    {
        // Write Slave address and Sub-address
        if(ScalerMcuIICWriteStart(ucSlaveAddr, ucSubAddrLength, usSubAddr) == _FAIL)
        {
            return _FAIL;
        }
    }

    // Write Slave address to read
    if(ScalerMcuIICStart(ucSlaveAddr | _READ) == _FAIL)
    {
        return _FAIL;
    }

    // Save received data
    while(--usLength)
    {
        *pucReadArray++ = ScalerMcuIICGetByte();

        ScalerMcuIICSendAck();
    }

    *pucReadArray++ = ScalerMcuIICGetByte();

    ScalerMcuIICSendNoAck();

    ScalerMcuIICStop();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by Software IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    if(usLength == 0)
    {
        return _FAIL;
    }

    // Write Slave address and Sub-address
    if(ScalerMcuIICWriteStart(ucSlaveAddr, ucSubAddrLength, usSubAddr) == _FAIL)
    {
        return _FAIL;
    }

    // Send data
    while(usLength--)
    {
        if(ScalerMcuIICSendByte(*pucWriteArray++) == _FAIL)
        {
            return _FAIL;
        }
    }

    ScalerMcuIICStop();

    return _SUCCESS;
}
#pragma restore

#endif    // End of #if(_SW_IIC_SUPPORT == _ON)

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hardware IIC Parameters Alter Setting By Use Case
// Input Value  : enumParType --> HW IIC Parameter Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIICConfigSetting(EnumHWIICParType enumParType)
{
    g_ucHwI2cSettingIndex = enumParType;

    ScalerMcuHwIICInitial();

    if(GET_REG_XTAL_CLK_SEL() == _EXT_XTAL_CLK)
    {
        // Select at external Xtal.
        ScalerMcuHwIICSetFreqDiv(_EXT_XTAL_CLK);
    }
    else
    {
        // Select at internal Xtal.
        ScalerMcuHwIICSetFreqDiv(_IOSC_CLK);
    }
}

//--------------------------------------------------
// Description  : Hardware IIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIICInitial(void)
{
    // Reset IIC module
    MCU_FF55_I2CM_CR0 &= ~_BIT7;

    // Enable IIC module and disable TOR
    MCU_FF55_I2CM_CR0 |= _BIT7;
    MCU_FF55_I2CM_CR0 &= ~_BIT0;

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    MCU_FF56_I2CM_CR1 = _HW_IIC_TOR;

    // Disable burst mode
    MCU_FF57_I2CM_CR2 = 0x00;

    // Clear interrupts
    MCU_FF58_I2CM_CR3 = 0x00;

    // Set fall time period count
    MCU_FF59_I2CM_STR0 = _HW_IIC_FTPC;

    // Set STA setup time period count
    MCU_FF5A_I2CM_STR1 = _HW_IIC_STA_SUGPIO_C;

    // Set SCL high period count
    MCU_FF5B_I2CM_STR2 = _HW_IIC_SHPC_14318K;

    // Set SCL low period count
    MCU_FF5C_I2CM_STR3 = _HW_IIC_SLPC_14318K;

    // Set frequency divisor: ref = xtal/(FD10+1)
    MCU_FF5F_I2CM_CCR = _HW_IIC_FD10_14318K;
}

//--------------------------------------------------
// Description  : Hardware IIC Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        MCU_FF5F_I2CM_CCR = _HW_IIC_FD10_14318K;

        // Set STA setup time period count
        MCU_FF5A_I2CM_STR1 = _HW_IIC_STA_SUGPIO_C;

        // Set SCL high period count
        MCU_FF5B_I2CM_STR2 = _HW_IIC_SHPC_14318K;

        // Set SCL low period count
        MCU_FF5C_I2CM_STR3 = _HW_IIC_SLPC_14318K;
    }
    else
    {
        // Set freq. divisor: ref = IOSC/(FD10+1) = 9.3M(ref should be approx 10MHz)
        MCU_FF5F_I2CM_CCR = _HW_IIC_FD10_28000K;

        // Set STA setup time period count
        MCU_FF5A_I2CM_STR1 = _HW_IIC_STA_SUGPIO_C;

        // Set SCL high period count
        MCU_FF5B_I2CM_STR2 = _HW_IIC_SHPC_28000K;

        // Set SCL low period count
        MCU_FF5C_I2CM_STR3 = _HW_IIC_SLPC_28000K;
    }
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum)
{
    BYTE ucSubAddress = 0x00;
    BYTE ucLength = 0;
    BYTE ucTimeOutCnt = _IIC_POLLING_TIME;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    MCU_FF55_I2CM_CR0 &= ~_BIT7;

    // Enable IIC module
    MCU_FF55_I2CM_CR0 |= _BIT7;

    // Set 1 byte for FRSIB
    MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);

    // Set no repeat start
    MCU_FF58_I2CM_CR3 &= ~(_BIT4 | _BIT3);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while((MCU_FF5D_I2CM_SR & _BIT5) != _BIT5)
    {
        if(ucTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            ucTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

    MCU_FF55_I2CM_CR0 &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);

    switch(ucSubAddrLength)
    {
        case 0:

            break;

        case 1:

            // Set data length
            MCU_FF55_I2CM_CR0 |= ucLength << 1;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(ucSubAddress);

            break;

        case 2:

            // Set data length
            MCU_FF55_I2CM_CR0 |= (ucLength + 1) << 1;

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSubAddress;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSubAddress;

            break;

        default:

            break;
    }

    // IIC command Start
    MCU_FF55_I2CM_CR0 |= _BIT6;

    // Wait until Master Transmit Complete
    ucTimeOutCnt = _IIC_POLLING_TIME;

    while((MCU_FF5D_I2CM_SR & 0x01) != 0x01)
    {
        ucTimeOutCnt--;

        DELAY_5US();

        if(ucTimeOutCnt == 0x00)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
    }

    // Clear all flags
    MCU_FF5D_I2CM_SR |= 0x07;

    return _SUCCESS;
}
#endif // End of #if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Read data from the selected device by IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    MCU_FF55_I2CM_CR0 &= ~_BIT7;

    // Enable IIC module
    MCU_FF55_I2CM_CR0 |= _BIT7;

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while((MCU_FF5D_I2CM_SR & _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);

            // Set no repeat start
            MCU_FF58_I2CM_CR3 &= ~(_BIT4 | _BIT3);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 1:

            // Set 2 bytes for FRSIB
            MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);
            MCU_FF57_I2CM_CR2 |= _BIT0;

            // Set one repeat start
            MCU_FF58_I2CM_CR3 &= ~_BIT4;
            MCU_FF58_I2CM_CR3 |= _BIT3;

            // Load Slave Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 2:

            // Set 3 bytes for FRSIB
            MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);
            MCU_FF57_I2CM_CR2 |= _BIT1;

            // Set one repeat start
            MCU_FF58_I2CM_CR3 &= ~_BIT4;
            MCU_FF58_I2CM_CR3 |= _BIT3;

            // Load Slave Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        default:

            break;
    }

    // Set data length
    MCU_FF55_I2CM_CR0 &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);
    MCU_FF55_I2CM_CR0 |= (ucDataLength - 1) << 1;

    // IIC command Start
    MCU_FF55_I2CM_CR0 |= _BIT6;

    // Wait until Master Receive Complete
    usTimeOutCnt = 600;

    while((MCU_FF5D_I2CM_SR & 0x02) != 0x02)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Wait I2C Fifo Clk Switch to Mcu Clk
    usTimeOutCnt = 600;

    while((MCU_FF5D_I2CM_SR & _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = MCU_FF5E_I2CM_TD;
        pucReadArray++;
    }

    // Clear all flags
    MCU_FF5D_I2CM_SR |= 0x07;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;
    BYTE ucTempLength = 0;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Reset(Block) IIC module
    MCU_FF55_I2CM_CR0 &= ~_BIT7;

    // Enable IIC module
    MCU_FF55_I2CM_CR0 |= _BIT7;

    // Set 1 byte for FRSIB
    MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);

    // Set no repeat start
    MCU_FF58_I2CM_CR3 &= ~(_BIT4 | _BIT3);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while((MCU_FF5D_I2CM_SR & _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xA1);

            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Load Slave Address to IIC Buffer
    MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

    MCU_FF55_I2CM_CR0 &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);

    if(ucDataLength > 16)
    {
        pData[0] = 16;
    }
    else
    {
        pData[0] = ucDataLength;
    }

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    if(ucDataLength <= 16)
    {
        // Load data to IIC buffer for transmission
        for(ucI = 0; ucI < pData[0]; ucI++)
        {
            MCU_FF5E_I2CM_TD = *pucWriteArray;
            pucWriteArray++;
        }

        // Send IIC command Start
        MCU_FF55_I2CM_CR0 = 0xC0 + ucTempLength;
    }
    else
    {
        // Disable HW TOR
        MCU_FF55_I2CM_CR0 &= ~_BIT0;

        // Enable Burst Mode
        MCU_FF57_I2CM_CR2 |= _BIT6;

        // Calcualte Burst Command
        pData[1] = (ucDataLength / 16) + ((ucDataLength % 16) ? 1 : 0);

        for(pData[2] = 0; pData[2] < pData[1]; pData[2]++)
        {
            usTimeOutCnt = 600;

            // Wait I2C Fifo Clk Switch to Mcu Clk
            while((MCU_FF5D_I2CM_SR & _BIT5) != _BIT5)
            {
                if(usTimeOutCnt == 0)
                {
                    DebugMessageScaler("- IIC Write Time Out: FIFO Clock", 0xA2);

                    // Reset(Block) IIC module
                    MCU_FF55_I2CM_CR0 &= ~_BIT7;

                    // Enable IIC module
                    MCU_FF55_I2CM_CR0 |= _BIT7;

                    // Disable Burst Mode
                    MCU_FF57_I2CM_CR2 &= ~_BIT6;

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    DELAY_5US();
                }
            }

            // Load data to IIC buffer for transmission
            for(ucI = 0; ucI < pData[0]; ucI++)
            {
                MCU_FF5E_I2CM_TD = *pucWriteArray;
                pucWriteArray++;
            }

            if(pData[2] != 0)
            {
                // Set data length
                ucTempLength = ((pData[0] - 1) << 1) & (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);
            }

            // Set Length and First Burst Command Start, Must Keep FF55[6] = 1 until Burst Mode end
            MCU_FF55_I2CM_CR0 = 0xC0 + ucTempLength;

            // Update Remaider Data Length
            ucDataLength = ucDataLength - pData[0];

            if(ucDataLength > 16)
            {
                pData[0] = 16;
            }
            else
            {
                pData[0] = ucDataLength;
            }

            if(pData[2] == (pData[1] - 1))
            {
                // Disable Burst Write
                MCU_FF57_I2CM_CR2 &= ~_BIT6;

                // Burst write again
                MCU_FF5D_I2CM_SR |= (_BIT4 | _BIT3);

                break;
            }
            else if(pData[2] != 0)
            {
                // Burst write again
                MCU_FF5D_I2CM_SR |= (_BIT4 | _BIT3);
            }

            usTimeOutCnt = 600;

            // Wait into Burst Wait State
            while((MCU_FF5D_I2CM_SR & _BIT3) != _BIT3)
            {
                if(usTimeOutCnt == 0)
                {
                    DebugMessageScaler("- IIC Write Time Out: Burst Mode", 0xA3);

                    // Reset(Block) IIC module
                    MCU_FF55_I2CM_CR0 &= ~_BIT7;

                    // Enable IIC module
                    MCU_FF55_I2CM_CR0 |= _BIT7;

                    // Disable Burst Mode
                    MCU_FF57_I2CM_CR2 &= ~_BIT6;

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    DELAY_5US();
                }
            }
        }
    }

    usTimeOutCnt = 600;

    // Wait until Master Transmit Complete
    while((MCU_FF5D_I2CM_SR & 0x01) != 0x01)
    {
        if(usTimeOutCnt == 0)
        {
            DebugMessageScaler("- IIC Write Time Out: Transmit", 0xA4);

            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            // Disable Burst Mode
            MCU_FF57_I2CM_CR2 &= ~_BIT6;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            DELAY_5US();
        }
    }

    // Clear all flags
    MCU_FF5D_I2CM_SR |= 0x07;

    return _SUCCESS;
}
#pragma restore

#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

#if(_UART_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Write data to the selected device by UART
// Input Value  : ucValue --> Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuUartWrite(BYTE ucValue)
{
    WORD usTimeOut = 1800;

    // Disable Serial Port IRQ
    ES = _DISABLE;

    // Clear Flag
    TI = 0;

    // Load Data to Serial Port Buffer
    SBUF = ucValue;

    do
    {
        DELAY_5US();
    }
    while((TI == 0) && (--usTimeOut != 0));

    // Enable Serial Port IRQ
    ES = _ENABLE;

    return ((TI != 0) && (usTimeOut != 0)) ? _TRUE : _FALSE;
}
#endif

//--------------------------------------------------
// Description  : ISP Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIspInitial(void)
{
    // Keep mcu peripheral(timer) running while mcu stopped by spi flash access
    MCU_FFEE_MCU_CLOCK_CONTROL |= _BIT6;
}

#if((_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT) && (_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_OFF))
//--------------------------------------------------
// Description  : MCU boot code initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuBootInitial(void)
{
    // Disable watchdog timer
    MCU_FFEA_WATCHDOG_TIMER &= ~(_BIT7);

    // Enable global XRAM and XFR, use Pbank_switch, enable bankswitching function
    MCU_FFFC_BANK_SWICH_CONTROL |= (_BIT3 | _BIT2 | _BIT1 | _BIT0);

    // Set Mcu/Flash Clock to External Xtal
    ScalerMcuFlashClockGroupSetting(_EXT_XTAL_CLK);

    // Disable all interrupts
    IE = 0x00;
}
#endif

