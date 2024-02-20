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
// ID Code      : ScalerCommonDebug.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_DEBUG__

#include "ScalerCommonFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DATA_OUT_COUNT                       0x05

#define _SCALER_DEBUG_BUF_LEN                 0x20 // 32
#define _SCALER_DEBUG_DATA_COUNT              0x18 // 24

// Scaler Command Define
#define _SCALER_WRITE_REGISTERS_CMD           0xBA
#define _SCALER_READ_REGISTERS_CMD            0xBB

// Error code
#define _SCALER_DEBUG_NO_ERROR                0x00
#define _SCALER_DEBUG_DATA_LEN_ERROR          0xE1
#define _SCALER_DEBUG_CHECKSUM_ERROR          0xE2


#if(_DEBUG_MESSAGE_SUPPORT == _ON)
#warning "NOTE: DEBUG MESSAGE SUPPORT ON!!"
#endif

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
#warning "NOTE: _DEBUG_IIC_BY_USERINTERFACE ON!!"
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
bit g_bRunCommand = _FALSE;
BYTE g_pucDdcciData[_SCALER_DEBUG_BUF_LEN];
BYTE g_ucDdcciCommandNumber;
EnumDDCCIDebugMode g_enumDDCCIDebugMode = _DEBUG_MODE;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
bit g_bDebugMessageEven = _FALSE;
WORD g_usFilterPro;
bit g_bFwHalt = _FALSE;
bit g_bDebugMessageStart = _FALSE;
BYTE idata g_pucDebugMessageBUF[4];
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
bit g_bDdcciSwitchState = _FALSE;
#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDebugSelectDDCCIDebugMode(EnumDDCCIDebugMode enumMode);
EnumDDCCIDebugMode ScalerDebugGetDDCCIDebugMode(void);

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
void ScalerDebugMessage(BYTE *pucArray1, DWORD ulArray2);
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

void ScalerDebugIntProc_EXINT1(void);
void ScalerDebug(void);

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
BYTE ScalerDebugGetDdcciSwitchState_EXINT1(void);
void ScalerDebugClrDdcciSwitchState(void);
#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
void ScalerDebugSetDdcciSwitchState(void);
#endif
#endif
void ScalerDebugSendData(BYTE ucLen, BYTE *pucSendArray);
void ScalerDebugGetRegisters(void);
void ScalerDebugSetRegisters(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDC-CI or Debug mode Select
// Input Value  : enumMode --> _DEBUG_MODE / _DDCCI_MODE
// Output Value : None
//--------------------------------------------------
void ScalerDebugSelectDDCCIDebugMode(EnumDDCCIDebugMode enumMode)
{
    g_enumDDCCIDebugMode = enumMode;
}

//--------------------------------------------------
// Description  : Get DDC-CI or Debug mode
// Input Value  : None
// Output Value : enumMode --> _DEBUG_MODE / _DDCCI_MODE
//--------------------------------------------------
EnumDDCCIDebugMode ScalerDebugGetDDCCIDebugMode(void)
{
    return g_enumDDCCIDebugMode;
}

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Debug Message process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugMessage(BYTE *pucArray1, DWORD ulArray2)
{
    BYTE ucCnt = 0;
    BYTE ucLength = 0;
    BYTE ucCheckSum = 0;
    BYTE ucIndex = 0;

    if(g_pucDdcciData[0] == 0x55)
    {
        g_bDebugMessageEven = _TRUE;
    }

    if(g_bDebugMessageEven == _FALSE)
    {
        return;
    }

    if(*pucArray1 == 0)
    {
        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;
        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40; // Reset IIC Data Buffer
        MCU_FF26_IIC_DATA_OUT = 0xFC;
        return;
    }

    if((g_usFilterPro & 0xF800) == 0xC800)
    {
        if((pucArray1[0] >= '0') && (pucArray1[0] <= '9'))
        {
            if((g_usFilterPro & (1 << (pucArray1[0] - '0'))) == 0)
            {
                MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;
                MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40; // Reset IIC Data Buffer
                MCU_FF26_IIC_DATA_OUT = 0xFC;

                return;
            }
        }
        else
        {
            if((g_usFilterPro & (_BIT2 << 8)) == 0)
            {
                MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;
                MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40; // Reset IIC Data Buffer
                MCU_FF26_IIC_DATA_OUT = 0xFC;

                return;
            }
        }
    }

    g_bDebugMessageStart = 0;
    g_bFwHalt = 1;

    MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;
    MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40; // Reset IIC Data Buffer
    MCU_FF26_IIC_DATA_OUT = 0xF1;

    for(ucCheckSum = 0; ucCheckSum < 4; ucCheckSum++)
    {
        g_pucDebugMessageBUF[ucCheckSum] = 0;
    }

    do
    {
        if(g_bRunCommand == _TRUE)
        {
            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;
            ucCnt = 0;

            switch(g_pucDdcciData[0])
            {
                case 0x20: // Handshake Setting
                case 0x55:

                    if(g_pucDdcciData[1] == 0x5A)
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xE7;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }
                    else if(g_pucDdcciData[1] == 0xA5)
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xEC;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }
                    else
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xF1;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }

                    break;

                case 0x25: // Debug Message Start

                    if(g_pucDdcciData[1] == 0)
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            ucLength = 0; // Total Length
                            ucIndex = 0;
                            ucCheckSum = 0x00; // Initial checksum

                            do
                            {
                                ucCheckSum += pucArray1[ucLength];
                            }
                            while((pucArray1[ucLength++] != 0) && (ucLength < 240)); // To count the length of pArray1 and checksum

                            g_pucDebugMessageBUF[0] = (BYTE)(ulArray2 >> 24);
                            g_pucDebugMessageBUF[1] = (BYTE)(ulArray2 >> 16);
                            g_pucDebugMessageBUF[2] = (BYTE)(ulArray2 >> 8);
                            g_pucDebugMessageBUF[3] = (BYTE)(ulArray2);
                            ucLength = ucLength - 1;

                            MCU_FF26_IIC_DATA_OUT = 0xFA;
                            MCU_FF26_IIC_DATA_OUT = 0xF5;
                            MCU_FF26_IIC_DATA_OUT = ucLength;
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[0];
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[1];
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[2];
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[3];

                            ucIndex = ucCheckSum;
                            ucCheckSum = 0x0F;
                            ucCheckSum = ucCheckSum + ucLength + g_pucDebugMessageBUF[0] + g_pucDebugMessageBUF[1] + g_pucDebugMessageBUF[2] + g_pucDebugMessageBUF[3];

                            g_pucDebugMessageBUF[0] = ucCheckSum + ucIndex; // Save checksum for all string and data
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[0]; // Checksum for all string and data
                            MCU_FF26_IIC_DATA_OUT = ucCheckSum + g_pucDebugMessageBUF[0];
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x09) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }
                    else
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            ucIndex = (g_pucDdcciData[1] - 1) * 15;
                            ucCheckSum = g_pucDdcciData[1] + 0x0F;
                            g_pucDebugMessageBUF[0] = 1;

                            do
                            {
                                MCU_FF26_IIC_DATA_OUT = pucArray1[ucIndex];
                                ucCheckSum += pucArray1[ucIndex];
                                ucIndex++;
                                g_pucDebugMessageBUF[0] = g_pucDebugMessageBUF[0] + 1;
                            }
                            while((ucIndex < (g_pucDdcciData[1] * 15)) && (pucArray1[ucIndex] != 0));

                            MCU_FF26_IIC_DATA_OUT = ucCheckSum;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != g_pucDebugMessageBUF[0]) && ((ucCnt++) < _DATA_OUT_COUNT));
                        g_bDebugMessageStart = 1;
                    }

                    break;

                case 0x2A: // Debug Message End

                    if(g_bDebugMessageStart == _TRUE)
                    {
                        g_bDebugMessageStart = 0; // Debug Message End
                        g_bFwHalt = 0;
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xF7;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }

                    break;

                case 0x2F: // Debug Message Event finsih

                    do
                    {
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                        MCU_FF26_IIC_DATA_OUT = 0xF5;
                    }
                    while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                    g_bDebugMessageEven = 0;
                    g_bFwHalt = 0;
                    MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xBF;
                    break;

                default:
                    break;
            }

            g_bRunCommand = 0;
            g_ucDdcciCommandNumber = 0;

            MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xDF;

            // Delay Time us [30,x] Avoid MCU Clock too fast lead to Tool Communication Fail.
            DELAY_30US();

// Release SCL Pin
#if(_DEBUG_DDC_CHANNEL_SEL == _DDC5)
            MCU_FE81_DDC5_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC4)
            MCU_FE78_DDC4_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC3)
            MCU_FE6F_DDC3_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC2)
            MCU_FE66_DDC2_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
            MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
            MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT0;
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) || (_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC2))
            CLR_VGADDC_SCL_FORCE_LOW();
#endif
        }
    }
    while(g_bFwHalt != 0);

    g_bDebugMessageStart = 0;
    g_bFwHalt = 0;
}
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDebugIntProc_EXINT1(void) using 2
{
    BYTE ucTempBuf = 0;

    MCU_FF29_IIC_STATUS2 &= 0xCF;

    if(g_bRunCommand == _FALSE)
    {
        ucTempBuf = MCU_FF27_IIC_STATUS;

        if((ucTempBuf & 0x02) != 0x00)
        {
            // Clear SUB_I Flag
            MCU_FF27_IIC_STATUS = 0xBD;

            g_ucDdcciCommandNumber = 0;
            g_pucDdcciData[0] = MCU_FF24_IIC_SUB_IN;

            // Host write Enable
            MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xDF;
        }

        if((ucTempBuf & 0x04) != 0x00)
        {
            while((MCU_FF29_IIC_STATUS2 & _BIT1) == 0)
            {
                // Avoid buffer overflow
                if((g_ucDdcciCommandNumber + 1) < sizeof(g_pucDdcciData))
                {
                    g_ucDdcciCommandNumber++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

                    g_ucDdcciCommandNumber = 0;

                    break;
                }

                g_pucDdcciData[g_ucDdcciCommandNumber] = MCU_FF25_IIC_DATA_IN;
            }

            // Clear D_IN_I Flag
            MCU_FF27_IIC_STATUS = 0xBB;
        }

        if((ucTempBuf & _BIT4) == _BIT4)
        {
            MCU_FF27_IIC_STATUS = 0xAF;

            if(g_ucDdcciCommandNumber > 0)
            {
// Hold Scl Pin
#if(_DEBUG_DDC_CHANNEL_SEL == _DDC5)
                MCU_FE81_DDC5_DDC_CONTROL_2 |= _BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC4)
                MCU_FE78_DDC4_DDC_CONTROL_2 |= _BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC3)
                MCU_FE6F_DDC3_DDC_CONTROL_2 |= _BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT0;
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) || (_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC2))
                SET_VGADDC_SCL_FORCE_LOW();
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)

                if(g_pucDdcciData[0] == 0x55)
                {
                    if(g_pucDdcciData[1] == 0x00)
                    {
                        g_usFilterPro = 0;
                    }
                    else
                    {
                        g_usFilterPro = ((g_pucDdcciData[1] << 8) + g_pucDdcciData[2]);
                    }
                }

                if((g_pucDdcciData[0] == 0x2F) && (g_bDebugMessageEven == _TRUE))
                {
                    g_bDebugMessageEven = _FALSE;
                    g_bFwHalt = _FALSE;
                }
                else if((g_pucDdcciData[0] == 0x55) && (g_bDebugMessageEven != _TRUE))
                {
                    g_bDebugMessageEven = _TRUE;
                }
#endif

                MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;
                g_bRunCommand = _TRUE;
            }
        }
    }
    else
    {
        MCU_FF27_IIC_STATUS = 0xA9;
    }
}

//--------------------------------------------------
// Description  : IC Debug Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebug(void)
{
    BYTE ucHalt = 0;
    BYTE ucCnt = 0;
    BYTE ucResult = 0;
    WORD usAddress = 0;

    if(g_enumDDCCIDebugMode == _DEBUG_MODE)
    {
        do
        {
            if(g_bRunCommand == _TRUE)
            {
                ucCnt = 0;

                switch(g_pucDdcciData[0])
                {
                    case 0x80:
                        ucHalt = g_pucDdcciData[1];
                        break;

                    case 0x41:
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

                        // CScalerRead
                        MCU_FFF3_SCA_INF_CONTROL |= 0x20;
                        MCU_FFF4_SCA_INF_ADDR = g_pucDdcciData[1];
                        ucResult = MCU_FFF5_SCA_INF_DATA;

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = ucResult;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        break;

                    case 0x44:
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
                        if(UserInterfaceDebugIIC(_READ, g_pucDdcciData, &ucResult) == _FALSE)
#endif
                        {
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

                            SET_SW_IIC_STATUS(_IIC_SYS_EEPROM);                       
                        #ifdef SW_IIC_REG_SECECT
                            SW_IIC_REG_CONTROL_SECECT();
                        #endif

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                            ScalerMcuIICRead(g_pucDdcciData[2], 1, g_pucDdcciData[1], 1, &ucResult);
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
                            ScalerMcuIICRead(g_pucDdcciData[2], 2, ((g_pucDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDdcciData[1]) & 0x00FF), 1, &ucResult);
#endif

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                            ScalerMcuHwIICRead(g_pucDdcciData[2], 1, g_pucDdcciData[1], 1, &ucResult, _PCB_SYS_EEPROM_IIC);
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
                            ScalerMcuHwIICRead(g_pucDdcciData[2], 2, ((g_pucDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDdcciData[1]) & 0x00FF), 1, &ucResult, _PCB_SYS_EEPROM_IIC);
#endif

#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)
                        }

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = ucResult;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        break;

                    case 0x45:
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

#if((_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO))

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                        ScalerMcuHwIICRead(g_pucDdcciData[2], 1, g_pucDdcciData[1], 1, &ucResult, _NO_IIC_PIN);
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
                        ScalerMcuHwIICRead(g_pucDdcciData[2], 2, ((g_pucDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDdcciData[1]) & 0x00FF), 1, &ucResult, _NO_IIC_PIN);
#endif

#endif // End of #if(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO)

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = ucResult;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        break;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                    case 0x2F: // Debug Message Event finsih
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xBF; // Reset IIC Data Buffer
                            MCU_FF26_IIC_DATA_OUT = 0xF5;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xDF;
                        g_bDebugMessageStart = 0;
                        g_bFwHalt = _FALSE;
                        g_bDebugMessageEven = 0;
                        break;
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

                    case 0x3A:
                        // Read flash(if the address is max than 0xFF00, read mcu register)
                        MCU_FF26_IIC_DATA_OUT = ScalerGetByte((g_pucDdcciData[2] << 8) + g_pucDdcciData[1]);
                        break;

                    case 0x3B:
                        // Write flash(if the address is max than 0xFF00, write mcu register)
                        ScalerSetByte((g_pucDdcciData[2] << 8) + g_pucDdcciData[1], g_pucDdcciData[3]);
                        break;

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
                    case 0x71:
                        // Set DDCCI INT to Bypass Judge OSD Flag
                        SET_DDCCI_SWITCH_STATE();
                        // Switch DDCCI to DDCCI Mode, No Matter Which Port as Auto-Switch
                        ScalerMcuDdcciSwitchPort(_DDCCI_MODE, _A0_INPUT_PORT);
                        break;
#endif

                    case _SCALER_READ_REGISTERS_CMD:
                        ScalerDebugGetRegisters();
                        break;

                    case _SCALER_WRITE_REGISTERS_CMD:
                        ScalerDebugSetRegisters();
                        break;

                    default:
                        switch(g_pucDdcciData[0] & 0x0F) // Write command
                        {
                            case 0x00:

                                // ScalerSetByte(g_pucDdcciData[2], g_pucDdcciData[1]);
                                // MCU_FFF3_SCA_INF_CONTROL |= 0x20;
                                // MCU_FFF4_SCA_INF_ADDR = g_pucDdcciData[2];
                                // MCU_FFF5_SCA_INF_DATA = g_pucDdcciData[1];

                                MCU_FFF3_SCA_INF_CONTROL |= 0x20;
                                MCU_FFF4_SCA_INF_ADDR = 0x9F;
                                usAddress = MCU_FFF5_SCA_INF_DATA;
                                usAddress = (usAddress << 8) + g_pucDdcciData[2];
                                ScalerSetByte(usAddress, g_pucDdcciData[1]);
                                break;

                            case 0x01:
                            case 0x02: // For RTD & I2c Device
                                g_pucDdcciData[2] = g_pucDdcciData[1];
                                break;

                            case 0x06:
                            case 0x03: // For I2c Device
                                g_pucDdcciData[3] = g_pucDdcciData[1];
                                break;

                            case 0x05:
                                g_pucDdcciData[4] = g_pucDdcciData[1];
                                break;

                            case 0x04: // For I2c Device

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
                                if(UserInterfaceDebugIIC(_WRITE, g_pucDdcciData, &ucResult) == _FALSE)
#endif
                                {
                                    // Disable EEPROM Write Protect
                                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

                                    SET_SW_IIC_STATUS(_IIC_SYS_EEPROM);                           
                                #ifdef SW_IIC_REG_SECECT
                                    SW_IIC_REG_CONTROL_SECECT();
                                #endif

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                                    ScalerMcuIICWrite(g_pucDdcciData[2], 1, g_pucDdcciData[1], 1, g_pucDdcciData + 3);
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
                                    ScalerMcuIICWrite(g_pucDdcciData[2], 2, ((g_pucDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDdcciData[1]) & 0x00FF), 1, g_pucDdcciData + 3);
#endif

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)  // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                                    ScalerMcuHwIICWrite(g_pucDdcciData[2], 1, g_pucDdcciData[1], 1, g_pucDdcciData + 3, _PCB_SYS_EEPROM_IIC);
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
                                    ScalerMcuHwIICWrite(g_pucDdcciData[2], 2, ((g_pucDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDdcciData[1]) & 0x00FF), 1, g_pucDdcciData + 3, _PCB_SYS_EEPROM_IIC);
#endif

#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

                                    // Enable EEPROM Write Protect
                                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
                                }

                                break;

                            case 0x0F: // For I2c Device

                                // Disable EEPROM Write Protect
                                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

#if((_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO))

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                                ScalerMcuHwIICWrite(g_pucDdcciData[2], 1, g_pucDdcciData[1], 1, g_pucDdcciData + 3, _NO_IIC_PIN);
#elif(_EEPROM_TYPE == _EEPROM_24WC64)
                                ScalerMcuHwIICWrite(g_pucDdcciData[2], 2, ((g_pucDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDdcciData[1]) & 0x00FF), 1, g_pucDdcciData + 3, _NO_IIC_PIN);
#endif

#endif // End of #if(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO)

                                // Enable EEPROM Write Protect
                                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                                break;

                            default:
                                break;
                        }
                        break;
                }

                g_bRunCommand = 0;
                g_ucDdcciCommandNumber = 0;

                // Host write Enable
                MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);

                // Delay Time us [30,x] Avoid MCU Clock too fast lead to Tool Communication Fail.
                DELAY_30US();

// Release Scl Pin
#if(_DEBUG_DDC_CHANNEL_SEL == _DDC5)
                MCU_FE81_DDC5_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC4)
                MCU_FE78_DDC4_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC3)
                MCU_FE6F_DDC3_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE66_DDC2_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT0;
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) || (_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC2))
                CLR_VGADDC_SCL_FORCE_LOW();
#endif
            }
        }
        while(ucHalt != 0);
    }
}

#if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)
//--------------------------------------------------
// Description  : Get Current DDCCI Switch State
// Input Value  : None
// Output Value : Bit State
//--------------------------------------------------
BYTE ScalerDebugGetDdcciSwitchState_EXINT1(void) using 2
{
    return GET_DDCCI_SWITCH_STATE();
}

//--------------------------------------------------
// Description  : Clr Current DDCCI Switch State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugClrDdcciSwitchState(void)
{
    CLR_DDCCI_SWITCH_STATE();
}

#if((_CODE_DIGITAL_SIGNATURE_SUPPORT == _SIGNATURE_TYPE_INTERNAL) && (_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT))
//--------------------------------------------------
// Description  : Set Current DDCCI Switch State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSetDdcciSwitchState(void)
{
    SET_DDCCI_SWITCH_STATE();
}
#endif

#endif // End of #if(_CODE_DIGITAL_SIGNATURE_SUPPORT != _SIGNATURE_TYPE_OFF)

//--------------------------------------------------
// Description  : Scaler Debug Send Data
// Input Value  : ucLen:  Send Data Len
// Output Value : None
//--------------------------------------------------
void ScalerDebugSendData(BYTE ucLen, BYTE *pucSendArray)
{
    BYTE ucIndex = 0;
    WORD usTimeOutCnt = 0;
    bit bReleaseScl = _FALSE;

    // Enable mcu write and reset buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucIndex < (ucLen))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FF29_IIC_STATUS2 & _BIT2) == 0)
        {
            MCU_FF26_IIC_DATA_OUT = pucSendArray[ucIndex];
            ucIndex++;
            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            // Release Scl for Tool to read
            if(bReleaseScl == _FALSE)
            {
                bReleaseScl = _TRUE;
// Release Scl Pin
#if(_DEBUG_DDC_CHANNEL_SEL == _DDC5)
                MCU_FE81_DDC5_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC4)
                MCU_FE78_DDC4_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC3)
                MCU_FE6F_DDC3_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC2)
                MCU_FE66_DDC2_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
                MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT0;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
                MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT0;
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) || (_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC2))
                CLR_VGADDC_SCL_FORCE_LOW();
#endif
            }
            ScalerTimerDelayXms(2);
            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Scaler Debug Read Registers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGetRegisters(void)
{
    BYTE ucLen = 0;
    BYTE ucChecksum = 0;
    bit bAutoIncrease = _FALSE;
    WORD usAddress = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN];

    // read date
    ucLen = g_pucDdcciData[3];
    bAutoIncrease = (bit)g_pucDdcciData[4];
    usAddress = ((WORD)g_pucDdcciData[1] << 8) + g_pucDdcciData[2];

    memset(pucDdcciOutData, 0, sizeof(pucDdcciOutData));

    // Length Error
    if(ucLen > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_READ_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < 5; ucIndex++)
    {
        ucChecksum += g_pucDdcciData[ucIndex];
    }

    // Check sum Error
    if(ucChecksum != g_pucDdcciData[5])
    {
        pucDdcciOutData[0] = _SCALER_READ_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    pucDdcciOutData[0] = _SCALER_READ_REGISTERS_CMD;
    pucDdcciOutData[1] = ucLen;
    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        pucDdcciOutData[2 + ucIndex] = ScalerGetByte(usAddress);
        ucChecksum += pucDdcciOutData[2 + ucIndex];
        if(bAutoIncrease == _TRUE)
        {
            usAddress++;
        }
    }
    pucDdcciOutData[ucLen + 2] = ucChecksum;
    ScalerDebugSendData(ucLen + 3, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Write Registers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSetRegisters(void)
{
    BYTE ucLen = 0;
    BYTE ucChecksum = 0;
    bit bAutoIncrease = _FALSE;
    WORD usAddress = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN];

    // Write date
    ucLen = g_pucDdcciData[3];
    bAutoIncrease = (bit)g_pucDdcciData[4];
    usAddress = ((WORD)g_pucDdcciData[1] << 8) + g_pucDdcciData[2];

    memset(pucDdcciOutData, 0, sizeof(pucDdcciOutData));

    // Length Error
    if(ucLen > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_WRITE_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < (ucLen + 5); ucIndex++)
    {
        ucChecksum += g_pucDdcciData[ucIndex];
    }

    // Check sum Error
    if(ucChecksum != g_pucDdcciData[5 + ucLen])
    {
        pucDdcciOutData[0] = _SCALER_WRITE_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    // Checksum OK do write option
    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        ScalerSetByte(usAddress, g_pucDdcciData[5 + ucIndex]);
        if(bAutoIncrease == _TRUE)
        {
            usAddress++;
        }
    }

    pucDdcciOutData[0] = _SCALER_WRITE_REGISTERS_CMD;
    pucDdcciOutData[1] = _SCALER_DEBUG_NO_ERROR;
    ScalerDebugSendData(2, pucDdcciOutData);
}

