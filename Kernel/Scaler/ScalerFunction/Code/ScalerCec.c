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
// ID Code      : ScalerCec.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_CEC__

#include "ScalerFunctionInclude.h"

#if(_HDMI_CEC_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _CEC_BOARDCAST_LA                      0xF
#define _CEC_RX_BACKUP_FIFO_SIZE               30

// CEC receiver duration setting
#define _CEC_RX_START_LOW_TIME                 0x74
#define _CEC_RX_START_PERIOD_TIME              0xBC
#define _CEC_RX_DATA_SAMPLE_TIME               0x2A
#define _CEC_RX_DATA_PERIOD_TIME               0x52
#define _CEC_RX_START_HIGH_TIME                0xA0

// CEC transmitter duration setting
#define _CEC_TX_START_LOW_TIME                 0x94
#define _CEC_TX_START_HIGH_TIME                0x20
#define _CEC_TX_DATA_LOW_TIME                  0x18
#define _CEC_TX_DATA_WIDTH_TIME                0x24
#define _CEC_TX_DATA_HIGH_TIME                 0x24

#define _CEC_LANG_ENGLISH                      "eng"
#define _CEC_LANG_FRENCH                       "fre"
#define _CEC_LANG_GERMAN                       "ger"
#define _CEC_LANG_SPANISH                      "spa"
#define _CEC_LANG_CHINESE                      "chi"
#define _CEC_LANG_JAPANESE                     "jpn"

#define GET_CEC_TX_EVENT()                     (g_stCecGeneralCtrl.ucCecTxEvent)
#define SET_CEC_TX_EVENT(x)                    (g_stCecGeneralCtrl.ucCecTxEvent = (x))
#define CLR_CEC_TX_EVENT()                     (g_stCecGeneralCtrl.ucCecTxEvent = _CEC_TX_NONE_EVENT)

#define GET_CEC_TX_STATE()                     (g_stCecGeneralCtrl.b2CecTxState)
#define SET_CEC_TX_STATE(x)                    (g_stCecGeneralCtrl.b2CecTxState = (x))

#define GET_CEC_TX_START()                     (g_stCecGeneralCtrl.bCecTxStart)
#define SET_CEC_TX_START()                     (g_stCecGeneralCtrl.bCecTxStart = 1)
#define CLR_CEC_TX_START()                     (g_stCecGeneralCtrl.bCecTxStart = 0)

#define GET_CEC_RX_MSG_ANALYZING()             (g_stCecGeneralCtrl.bCecRxInfoAnalyzing)
#define SET_CEC_RX_MSG_ANALYZING()             (g_stCecGeneralCtrl.bCecRxInfoAnalyzing = 1)
#define CLR_CEC_RX_MSG_ANALYZING()             (g_stCecGeneralCtrl.bCecRxInfoAnalyzing = 0)

#define GET_CEC_RX_READ_FROM_BACKUP_FIFO()     (g_stCecGeneralCtrl.bReadFromBackupFifo)
#define SET_CEC_RX_READ_FROM_BACKUP_FIFO()     (g_stCecGeneralCtrl.bReadFromBackupFifo = _TRUE)
#define CLR_CEC_RX_READ_FROM_BACKUP_FIFO()     (g_stCecGeneralCtrl.bReadFromBackupFifo = _FALSE)

#define GET_CEC_TX_DEST_LA_TO_SEND()           ((g_stCecTxTransmitInfo.ucTransmitHb) & 0x0F)
#define GET_CEC_TX_INIT_LA_TO_SEND()           (((g_stCecTxTransmitInfo.ucTransmitHb) & 0xF0) >> 4)

#define GET_CEC_FUNCTION_ENABLE()              (g_stCecGeneralCtrl.bCecFxEnable)
#define SET_CEC_FUNCTION_ENABLE()              (g_stCecGeneralCtrl.bCecFxEnable = 1)
#define CLR_CEC_FUNCTION_ENABLE()              (g_stCecGeneralCtrl.bCecFxEnable = 0)

#define GET_CEC_TX_DEST_LA_TO_SEND()           ((g_stCecTxTransmitInfo.ucTransmitHb) & 0x0F)
#define GET_CEC_TX_INIT_LA_TO_SEND()           (((g_stCecTxTransmitInfo.ucTransmitHb) & 0xF0) >> 4)

#define GET_EDID_CEC_PHY_ADDRESS()             (g_stCecGeneralCtrl.usCecPhyAddr)
#define SET_EDID_CEC_PHY_ADDRESS(x)            (g_stCecGeneralCtrl.usCecPhyAddr = (x))

#define GET_CEC_RX_READ_DONE()                 (g_stCecGeneralCtrl.bReadDone)
#define SET_CEC_RX_READ_DONE()                 (g_stCecGeneralCtrl.bReadDone = 1)
#define CLR_CEC_RX_READ_DONE()                 (g_stCecGeneralCtrl.bReadDone = 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile StructCecRxReceivedInfo g_stCecRxReceivedInfo;
StructCecTxTransmitInfo g_stCecTxTransmitInfo;
volatile StructCecGeneralCtrl g_stCecGeneralCtrl;

volatile BYTE g_ucCecRxBackupFifoWaterLevel;
BYTE g_pucCecRxBackupFifo[_CEC_RX_BACKUP_FIFO_SIZE];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerCecInitial(void);
void ScalerCecRxProcess(void);

void ScalerCecRxReadOutFromBackupFifo(void);
void ScalerCecFunctionEnable(bit bEnable);
void ScalerCecRxWriteIntoBackupFifo(void);
void ScalerCecRxClrIMsgAnalyzingFlag(void);
bit ScalerCecRxGetMsgAnalyzingFlag(void);
#if(_CEC_RX_INT_SUPPORT == _OFF)
void ScalerCecRxMsgReceiving(void);
bit ScalerCecCheckRxSituation(void);
#else
void ScalerCecPollingMsgReceiving(void);
BYTE ScalerCecCheckRxSituation_EXINT0(void);
void ScalerCecRxMsgReceiving_EXINT0(void);
void ScalerCecRxWriteIntoBackupFifo_EXINT0(void);
void ScalerCecRxWriteIntoRxInfoStruct_EXINT0(void);
#endif
void ScalerCecTxProcess(void);
EnumCecTxEvent ScalerCecTxGetTransmitResult(void);
EnumCecTxState ScalerCecGetTxState(void);
void ScalerCecRxWriteIntoRxInfoStruct(void);
// void ScalerCecReset(void);
void ScalerCecSendNewFx(void);
bit ScalerCecIsSending(void);
void ScalerCecIntHandler_EXINT0(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize CEC setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecInitial(void)
{
    DebugMessageCEC("CEC Initial", 0x00);

    // Disable CEC
    ScalerSetBit(P18_A0_CEC1_CR0_1, ~(_BIT7 | _BIT6), 0x00);

    // CEC input clock : iosc (28 MHz)
    // ScalerSetBit(P18_A1_CEC1_CR0_2, ~_BIT7, 0x00);

    // M2PLL 351MHz
    if(ScalerGetBit(P18_A1_CEC1_CR0_2, _BIT7) == _BIT7)
    {
        // -- 3/75(=0x4B) = 0.04Mhz
        ScalerSetByte(P18_A3_CEC1_CR0_4, 0x4B);
        // -- 351.0/117(=0x75) = 3.0Mhz
        ScalerSetByte(P18_A4_CEC1_CR0_5, 0x75);
    }
    else
    {
        // iosc 28MHz
        // -- 1/25(=0x19) = 0.04Mhz
        ScalerSetByte(P18_A3_CEC1_CR0_4, 0x19);
        // -- 28.0/28(=0x1C) = 1.0Mhz
        ScalerSetByte(P18_A4_CEC1_CR0_5, 0x1C);
    }

    // close pad rising time
    // ScalerSetByte(P18_A5_CEC1_CR0_6, 0x00);

    // change power source
    // ScalerSetByte(P19_F1_CEC1_POWER_SELECT, 0x84);

    // Physical Signal Property Setting
    // Cec Rx
    ScalerSetByte(P18_E5_CEC1_RXTCR0_1, _CEC_RX_START_LOW_TIME);
    ScalerSetByte(P18_E6_CEC1_RXTCR0_2, _CEC_RX_START_PERIOD_TIME);
    ScalerSetByte(P18_E7_CEC1_RXTCR0_3, _CEC_RX_DATA_SAMPLE_TIME);
    ScalerSetByte(P18_E8_CEC1_RXTCR0_4, _CEC_RX_DATA_PERIOD_TIME);
    ScalerSetByte(P18_E9_CEC1_RXTCR0_5, _CEC_RX_START_HIGH_TIME);

    // Cec Tx
    ScalerSetByte(P18_EF_CEC1_TXTCR0_1, _CEC_TX_START_LOW_TIME);
    ScalerSetByte(P18_F1_CEC1_TXTCR0_2, _CEC_TX_START_HIGH_TIME);
    ScalerSetByte(P18_F2_CEC1_TXTCR1_1, _CEC_TX_DATA_LOW_TIME);
    ScalerSetByte(P18_F3_CEC1_TXTCR1_2, _CEC_TX_DATA_WIDTH_TIME);
    ScalerSetByte(P18_F4_CEC1_TXTCR1_3, _CEC_TX_DATA_HIGH_TIME);

    // Set Tx ack reference (due to HW 5T debounce)
    ScalerSetBit(P18_F5_CEC1_RXTCR1_ACK_0, ~_BIT5, _BIT5);
    ScalerSetByte(P18_F6_CEC1_RXTCR1_ACK_1, _CEC_TX_DATA_LOW_TIME - 5);

    // Enable CEC
    ScalerSetBit(P19_F4_CEC_RESERVED, ~(_BIT1 | _BIT0), _BIT0);  // Revise cec drv to 90uA
    ScalerSetBit(P19_F0_GDI_CEC1_ANALOG_1, ~_BIT7, _BIT7);
    ScalerSetBit(P18_A0_CEC1_CR0_1, ~(_BIT7 | _BIT6), _BIT6);

    // CEC Rx/Tx LA Set to LA = 0
    ScalerSetBit(P18_A0_CEC1_CR0_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _CEC_LA_TV);
    ScalerSetBit(P18_B4_CEC1_TXCR0_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | (_CEC_LA_TV << 3)));

    // Cec Rx reset
    ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);

    // Cec Tx reset
    ScalerSetBit(P18_B4_CEC1_TXCR0_1, ~(_BIT2 | _BIT1), _BIT1);

    // Clear interrupt flag
    ScalerSetBit(P18_B1_CEC1_RXCR0_2, ~_BIT6, _BIT6);
    ScalerSetBit(P18_B5_CEC1_TXCR0_2, ~_BIT1, _BIT1);
    ScalerSetBit(P19_E0_CEC1_POWER_SAVING_MODE, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1));
    ScalerSetBit(P19_E4_CEC1_INTCR_02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Disable interrupt
    ScalerSetBit(P19_E0_CEC1_POWER_SAVING_MODE, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

#if(_CEC_RX_INT_SUPPORT == _ON)
    ScalerSetBit(P19_E0_CEC1_POWER_SAVING_MODE, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6));
    ScalerSetBit(P18_B1_CEC1_RXCR0_2, ~_BIT6, _BIT6);
    ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6 | _BIT4), (_BIT4));
#endif
}

//--------------------------------------------------
// Description  : Cec Rx Received MSG Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxProcess(void)
{
    if(GET_CEC_FUNCTION_ENABLE() == _FALSE)
    {
        return;
    }

    // Check && Load to Struct Fifo
    ScalerCecRxReadOutFromBackupFifo();

#if(_CEC_RX_INT_SUPPORT == _OFF)
    if(ScalerCecCheckRxSituation() == _FALSE)
    {
        return;
    }

    ScalerCecRxMsgReceiving();
#else
    ScalerCecPollingMsgReceiving();
#endif
}

//--------------------------------------------------
// Description  : Set Cec Rx struct from Cec Rx BackupUp Fifo
// Input Value  : None
// Output Value : Bit
//--------------------------------------------------
void ScalerCecRxReadOutFromBackupFifo(void)
{
    CLR_CEC_RX_READ_FROM_BACKUP_FIFO();

    // Polling Backup Buffer
    if((GET_CEC_RX_MSG_ANALYZING() == _FALSE) && (g_ucCecRxBackupFifoWaterLevel != 0x00))
    {
        BYTE pucBackupFifoTemp[_CEC_RX_BACKUP_FIFO_SIZE];

        // Fill CEC RX Info into xdata
        g_stCecRxReceivedInfo.ucDbLength = g_pucCecRxBackupFifo[0];
        g_stCecRxReceivedInfo.ucReceivedHb = g_pucCecRxBackupFifo[1];

        DebugMessageCEC("<= Cec0 Rx Backup Fifo: HB ", g_stCecRxReceivedInfo.ucReceivedHb);

        memset(g_stCecRxReceivedInfo.pucReceivedDb, 0, 16);
        for(pData[0] = 0; pData[0] < g_stCecRxReceivedInfo.ucDbLength; pData[0]++)
        {
            g_stCecRxReceivedInfo.pucReceivedDb[pData[0]] = g_pucCecRxBackupFifo[2 + pData[0]];
            DebugMessageCEC("<= Cec0 Rx Backup Fifo: DB ", g_stCecRxReceivedInfo.pucReceivedDb[pData[0]]);
        }

        DebugMessageCEC("CEC0 RX Backup Fifo Finished", 0x00);
        SET_CEC_RX_READ_DONE();

        // Shift Cec Rx Backup buffer
        memset(pucBackupFifoTemp, 0, _CEC_RX_BACKUP_FIFO_SIZE);
        memcpy(pucBackupFifoTemp, &g_pucCecRxBackupFifo[g_stCecRxReceivedInfo.ucDbLength + 2], (_CEC_RX_BACKUP_FIFO_SIZE - (g_stCecRxReceivedInfo.ucDbLength + 2)));
        memcpy(g_pucCecRxBackupFifo, &pucBackupFifoTemp, _CEC_RX_BACKUP_FIFO_SIZE);

        g_ucCecRxBackupFifoWaterLevel -= (g_stCecRxReceivedInfo.ucDbLength + 2);

        SET_CEC_RX_READ_FROM_BACKUP_FIFO();
    }
}

//--------------------------------------------------
// Description  : CEC Function Enable Flag Set/ Clear
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerCecFunctionEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        SET_CEC_FUNCTION_ENABLE();
    }
    else
    {
        CLR_CEC_FUNCTION_ENABLE();
    }
}

//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to Cec Rx BackupUp Fifo
// Input Value  : None
// Output Value : Bit
//--------------------------------------------------
void ScalerCecRxWriteIntoBackupFifo(void)
{
#if(_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)
    BYTE ucHbInfo = ScalerGetByte(P18_E3_CEC_RX_FIFO_RSV_0);
#else
    BYTE ucHbInfo = ((ScalerGetByte(P18_B0_CEC1_RXCR0_1) & 0x0F) << 4);
#endif

    // Backup fifo size check
    if((_CEC_RX_BACKUP_FIFO_SIZE - g_ucCecRxBackupFifoWaterLevel) < (ScalerGetBit(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) + 2))
    {
        // Set CEC Rx force Nack/ Negative Ack
        ScalerSetBit(P18_A6_CEC1_CR0_7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT5 | _BIT4));

        return;
    }

    // Fill CEC RX Info into Backup buffer
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] = ScalerGetBit(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 1] = ucHbInfo;

    DebugMessageCEC("Cec Rx Read: HB (load to backup)", g_stCecRxReceivedInfo.ucReceivedHb);

    for(pData[0] = 0; pData[0] < g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel]; pData[0]++)
    {
        g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 2 + pData[0]] = ScalerGetByte(P18_D3_CEC1_RXDR1_1 + pData[0]);
        DebugMessageCEC("Cec Rx Read: DB (load to backup)", g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 2 + pData[0]]);
    }

    g_ucCecRxBackupFifoWaterLevel += (ScalerGetBit(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) + 2);
}

//--------------------------------------------------
// Description  : Clr Cec Rx Msg Analyzing Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxClrIMsgAnalyzingFlag(void)
{
    CLR_CEC_RX_MSG_ANALYZING();
}

//--------------------------------------------------
// Description  : Get Cec Rx Msg Analyzing Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerCecRxGetMsgAnalyzingFlag(void)
{
    return GET_CEC_RX_MSG_ANALYZING();
}

#if(_CEC_RX_INT_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Cec Rx Receive MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxMsgReceiving(void)
{
#if(_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)
    BYTE ucDestLa = (ScalerGetByte(P18_E3_CEC_RX_FIFO_RSV_0) & 0x0F);
#else
    BYTE ucDestLa = 0xFF;
#endif

    if(GET_CEC_TX_STATE() != _CEC_TX_SENDING_STATE)
    {
        // Check incoming msg available
        // Avaiable Message: 1. <Polling Message> w/ ack  2. Others mesage (DB# > 0)
        if((ScalerGetBit(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00) ||
           (ucDestLa == _CEC_LA_TV))
        {
            // if Last CEC RX MSG hasn't been analyzed done by user
            if(GET_CEC_RX_MSG_ANALYZING() == _TRUE)
            {
                // Load Cec Rx Received MSG to backup fifo
                ScalerCecRxWriteIntoBackupFifo();
            }
            else
            {
                // Check no CEC msg will be sent to RX DPCD from Cec Rx backup fifo
                if((g_ucCecRxBackupFifoWaterLevel == 0x00) && (GET_CEC_RX_READ_FROM_BACKUP_FIFO() == _FALSE))
                {
                    // Load Cec Rx Received MSG to RxInfo struct
                    ScalerCecRxWriteIntoRxInfoStruct();
                }
                else
                {
                    // Load Cec Rx Received MSG to backup fifo
                    ScalerCecRxWriteIntoBackupFifo();
                }

                DebugMessageCEC("Cec RX Read Finished", 0x00);
            }
        }

        // reset
        ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
    }
}

//--------------------------------------------------
// Description  : check Cec Rx situation
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerCecCheckRxSituation(void)
{
    // Check EOM (B1[7]: Rx EOM, B2[7]: Header EOM)
    if((ScalerGetBit(P18_B1_CEC1_RXCR0_2, _BIT7) == 0x00) &&
       (ScalerGetBit(P18_B2_CEC1_RTCR0_RSV_1, _BIT7) == 0x00))
    {
        // B0[7]: Rx en, B1[6]: Rx int flag
        if((ScalerGetBit(P18_B0_CEC1_RXCR0_1, _BIT7) == 0x00) &&
           (ScalerGetBit(P18_B1_CEC1_RXCR0_2, _BIT6) == _BIT6))
        {
            DebugMessageCEC("CEC: Unexpected RX condition.....", 0);

            // reset
            ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
        }

        return _FALSE;
    }

    return _TRUE;
}
#else
//--------------------------------------------------
// Description  : Cec Rx Receive Polling MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecPollingMsgReceiving(void)
{
#if(_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)
    BYTE ucDestLa = (ScalerGetByte(P18_E3_CEC_RX_FIFO_RSV_0) & 0x0F);
#else
    BYTE ucDestLa = 0xFF;
#endif

    // header_eom = 1
    if((ScalerGetBit(P18_B2_CEC1_RTCR0_RSV_1, _BIT7) == _BIT7) && (GET_CEC_TX_STATE() != _CEC_TX_SENDING_STATE))
    {
        // Check incoming msg available
        // Avaiable Message: 1. <Polling Message> w/ ack
        if(ScalerGetBit(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            if(ucDestLa == _CEC_LA_TV)
            {
                // if Last CEC RX MSG hasn't been analyzed done by user
                if(GET_CEC_RX_MSG_ANALYZING() == _TRUE)
                {
                    // Load Cec Rx Received MSG to backup fifo
                    ScalerCecRxWriteIntoBackupFifo();
                }
                else
                {
                    // Check no CEC msg will be sent to RX DPCD from Cec Rx backup fifo
                    if((g_ucCecRxBackupFifoWaterLevel == 0x00) && (GET_CEC_RX_READ_FROM_BACKUP_FIFO() == _FALSE))
                    {
                        // Load Cec Rx Received MSG to RxInfo struct
                        ScalerCecRxWriteIntoRxInfoStruct();
                    }
                    else
                    {
                        // Load Cec Rx Received MSG to backup fifo
                        ScalerCecRxWriteIntoBackupFifo();
                    }

                    DebugMessageCEC("Cec RX Read Finished", 0x00);
                }
            }
        }

        // Reset Cec Rx
        ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
    }
}

//--------------------------------------------------
// Description  : check Cec Rx situation
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE ScalerCecCheckRxSituation_EXINT0(void) using 1
{
    // B1[7] -> data EOM, B2[7] -> header EOM
    // check whether rx_fifo overflow or receive another start-bit when dealing with CEC data
    if((ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, _BIT7) == 0x00) &&
       (ScalerGetBit_EXINT(P18_B2_CEC1_RTCR0_RSV_1, _BIT7) == 0x00))
    {
        // B0[7]: Rx en, B1[6]: Rx int flag
        if((ScalerGetBit_EXINT(P18_B0_CEC1_RXCR0_1, _BIT7) == 0x00) &&
           (ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, _BIT6) == _BIT6))
        {
            // reset
            ScalerSetBit_EXINT(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
            ScalerSetBit_EXINT(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
        }

        return 0x00;
    }

    return 0x01;
}

//--------------------------------------------------
// Description  : Cec Rx Receive MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxMsgReceiving_EXINT0(void) using 1
{
#if(_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)
    BYTE ucDestLa = (ScalerGetByte_EXINT(P18_E3_CEC_RX_FIFO_RSV_0) & 0x0F);
#else
    BYTE ucDestLa = _CEC_LA_TV;
#endif

    // Check incoming msg available
    // Avaiable Message: 1. <Polling Message> w/ ack  2. Others mesage (DB# > 0)
    if((ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != 0x00) ||
       (ucDestLa == _CEC_LA_TV))
    {
        // if Last CEC RX MSG hasn't been read by DP SRC
        if(GET_CEC_RX_MSG_ANALYZING() == _TRUE)
        {
            // Load Cec Rx Received MSG to backup fifo
            ScalerCecRxWriteIntoBackupFifo_EXINT0();
        }
        else
        {
            // Check no CEC msg will be sent to RX DPCD from Cec Rx backup fifo
            if((g_ucCecRxBackupFifoWaterLevel == 0x00) && (GET_CEC_RX_READ_FROM_BACKUP_FIFO() == _FALSE))
            {
                // Load Cec Rx Received MSG to RxInfo struct
                ScalerCecRxWriteIntoRxInfoStruct_EXINT0();
            }
            else
            {
                // Load Cec Rx Received MSG to backup fifo
                ScalerCecRxWriteIntoBackupFifo_EXINT0();
            }
        }
    }
}

//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to Cec Rx BackupUp Fifo
// Input Value  : None
// Output Value : Bit
//--------------------------------------------------
void ScalerCecRxWriteIntoBackupFifo_EXINT0(void) using 1
{
#if(_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)
    BYTE ucHbInfo = ScalerGetByte_EXINT(P18_E3_CEC_RX_FIFO_RSV_0);
#else
    BYTE ucHbInfo = ((ScalerGetByte_EXINT(P18_B0_CEC1_RXCR0_1) & 0x0F) << 4);
#endif

    // Backup fifo size check
    if((_CEC_RX_BACKUP_FIFO_SIZE - g_ucCecRxBackupFifoWaterLevel) < (ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) + 2))
    {
        // Set CEC Rx force Nack/ Negative Ack
        ScalerSetBit_EXINT(P18_A6_CEC1_CR0_7, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2), (_BIT7 | _BIT5 | _BIT4));

        return;
    }

    // Fill CEC RX Info into Backup buffer
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel] = ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 1] = ucHbInfo;

    for(pData_EXINT[0] = 0; pData_EXINT[0] < g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel]; pData_EXINT[0]++)
    {
        g_pucCecRxBackupFifo[g_ucCecRxBackupFifoWaterLevel + 2 + pData_EXINT[0]] = ScalerGetByte_EXINT(P18_D3_CEC1_RXDR1_1 + pData_EXINT[0]);
    }

    g_ucCecRxBackupFifoWaterLevel += (ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) + 2);
}


//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to CEC RX Info Struct
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxWriteIntoRxInfoStruct_EXINT0(void) using 1
{
    // Fill CEC RX Info into xdata
    g_stCecRxReceivedInfo.ucDbLength = ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)
    g_stCecRxReceivedInfo.ucReceivedHb = ScalerGetByte_EXINT(P18_E3_CEC_RX_FIFO_RSV_0);
#else
    g_stCecRxReceivedInfo.ucReceivedHb = ((ScalerGetByte_EXINT(P18_B0_CEC1_RXCR0_1) & 0x0F) << 4);
#endif

    memset(g_stCecRxReceivedInfo.pucReceivedDb, 0, 16);
    for(pData_EXINT[0] = 0; pData_EXINT[0] < g_stCecRxReceivedInfo.ucDbLength; pData_EXINT[0]++)
    {
        g_stCecRxReceivedInfo.pucReceivedDb[pData_EXINT[0]] = ScalerGetByte_EXINT(P18_D3_CEC1_RXDR1_1 + pData_EXINT[0]);
    }

    SET_CEC_RX_READ_DONE();
}
#endif

//--------------------------------------------------
// Description  : Cec TX Send Msg Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecTxProcess(void)
{
    if(GET_CEC_FUNCTION_ENABLE() == _FALSE)
    {
        return;
    }

    if(GET_CEC_TX_STATE() == _CEC_TX_SENDING_STATE)
    {
        // Check Current CEC TX is avaible to send
        if(ScalerCecIsSending() == _TRUE)
        {
            DebugMessageCEC("CEC TX is Busy", 0x00);

            return;
        }
        else // cec tx free
        {
            if(ScalerGetBit(P18_B5_CEC1_TXCR0_2, _BIT2) == _BIT2)
            {
                // w1c tx_eom
                // ScalerSetBit(P18_B5_CEC1_TXCR0_2, ~(_BIT2 | _BIT1), _BIT2);

                SET_CEC_TX_EVENT(_CEC_TX_SENT_EVENT);
                DebugMessageCEC("CEC TX has been Ack", 0x00);
            }
            else
            {
#if(_HW_HDMI_CEC_GEN >= _HW_CEC_GEN_TYPE_1)
                // Check CEC Line error, Nack Happened?
                if(ScalerGetBit(P18_B7_CEC1_TXCR0_RSV_0, _BIT7) == _BIT7)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_LINE_ERROR_EVENT);
                    DebugMessageCEC("CEC0 TX Line Error Happened!!", 0x00);

                    ScalerSetBit(P18_B7_CEC1_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
                else if(ScalerGetBit(P18_B7_CEC1_TXCR0_RSV_0, _BIT6) == _BIT6)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_HB_NACK_EVENT);
                    DebugMessageCEC("CEC TX HB Nack Happened!!", _CEC_TX_HB_NACK_EVENT);

                    ScalerSetBit(P18_B7_CEC1_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
                else if(ScalerGetBit(P18_B7_CEC1_TXCR0_RSV_0, _BIT5) == _BIT5)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_DB_NACK_EVENT);
                    DebugMessageCEC("CEC TX DB Nack Happened!!", 0x00);

                    ScalerSetBit(P18_B7_CEC1_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
                // FW workaround sol for Cec tx sent finish but none of result below..
                else if(ScalerGetBit(P18_B5_CEC1_TXCR0_2, _BIT1) == _BIT1)
                {
                    SET_CEC_TX_EVENT(_CEC_TX_LINE_ERROR_EVENT);
                    DebugMessageCEC("CEC TX FAKE Line Error Happened Orz.........", 0x00);

                    ScalerSetBit(P18_B7_CEC1_TXCR0_RSV_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
                }
#else
                SET_CEC_TX_EVENT(_CEC_TX_HB_NACK_EVENT);
                DebugMessageCEC("CEC TX has been Nack", 0x00);
#endif
            }

            // Check if CEC TX just sent <Polling Message>, clear header_eom for Tx Rx feedback circuit
            if(g_stCecTxTransmitInfo.ucDbLength == 0)
            {
                // w1c header eom
                ScalerSetBit(P18_B2_CEC1_RTCR0_RSV_1, ~_BIT7, _BIT7);
            }

            // Check Cec Tx finish transmit last message
            SET_CEC_TX_STATE(_CEC_TX_IDLE_STATE);
        }
    }

    if((GET_CEC_TX_START() == _TRUE) && (GET_CEC_TX_STATE() == _CEC_TX_IDLE_STATE))
    {
        // Fill Info into CEC TX Fifo & Send
        ScalerCecSendNewFx();
        DebugMessageCEC("CEC TX MSG Sned!!", 0x00);

        CLR_CEC_TX_START();
        SET_CEC_TX_STATE(_CEC_TX_SENDING_STATE);
    }
}

//--------------------------------------------------
// Description  : Get Result after Cec Tx Transmit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumCecTxEvent ScalerCecTxGetTransmitResult(void)
{
    return GET_CEC_TX_EVENT();
}

//--------------------------------------------------
// Description  : Get Result after Cec Tx Transmit
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumCecTxState ScalerCecGetTxState(void)
{
    return GET_CEC_TX_STATE();
}

//--------------------------------------------------
// Description  : Write Cec Rx Received Msg to CEC RX Info Struct
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecRxWriteIntoRxInfoStruct(void)
{
#if(_HW_HDMI_CEC_GEN == _HW_CEC_GEN_TYPE_2)
    BYTE ucHbInfo = ScalerGetByte(P18_E3_CEC_RX_FIFO_RSV_0);
#else
    BYTE ucHbInfo = ((ScalerGetByte(P18_B0_CEC1_RXCR0_1) & 0x0F) << 4);
#endif

    // Fill CEC RX Info into xdata
    g_stCecRxReceivedInfo.ucDbLength = ScalerGetBit(P18_B1_CEC1_RXCR0_2, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    g_stCecRxReceivedInfo.ucReceivedHb = ucHbInfo;

    DebugMessageCEC("<= Cec Rx Read: HB", g_stCecRxReceivedInfo.ucReceivedHb);

    memset(g_stCecRxReceivedInfo.pucReceivedDb, 0, 16);
    for(pData[0] = 0; pData[0] < g_stCecRxReceivedInfo.ucDbLength; pData[0]++)
    {
        g_stCecRxReceivedInfo.pucReceivedDb[pData[0]] = ScalerGetByte(P18_D3_CEC1_RXDR1_1 + pData[0]);
        DebugMessageCEC("<= Cec Rx Read: DB", g_stCecRxReceivedInfo.pucReceivedDb[pData[0]]);
    }

    SET_CEC_RX_READ_DONE();
}

/*
//--------------------------------------------------
// Description  : Set Cec Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecReset(void)
{
    // Cec rx/ tx xdata reset
    memset(&g_stCecRxReceivedInfo, 0, sizeof(g_stCecRxReceivedInfo));
    memset(&g_stCecTxTransmitInfo, 0, sizeof(g_stCecTxTransmitInfo));

    // FW flag reset
    SET_CEC_TX_STATE(_CEC_TX_IDLE_STATE);
    CLR_CEC_TX_EVENT();
    CLR_CEC_RX_READ_DONE();
    CLR_CEC_TX_START();
    CLR_CEC_FUNCTION_ENABLE();

    CLR_CEC_RX_MSG_ANALYZING();
    CLR_CEC_RX_READ_FROM_BACKUP_FIFO();

    // Cec Rx backup fifo reset
    g_ucCecRxBackupFifoWaterLevel = 0x00;
    memset(g_pucCecRxBackupFifo, 0, _CEC_RX_BACKUP_FIFO_SIZE);

    // CEC RX/ TX LA Reset
    ScalerSetBit(P18_A0_CEC1_CR0_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _CEC_LA_TV);
    ScalerSetBit(P18_B4_CEC1_TXCR0_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | (_CEC_LA_TV << 3)));

    DebugMessageCEC("CEC Reset", 0);
}
*/

//--------------------------------------------------
// Description  : CEC Tx send set (w/ retry cnt)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecSendNewFx(void)
{
    BYTE ucParam = 0;

    // Cec Tx Reset
    ScalerSetBit(P18_B4_CEC1_TXCR0_1, ~(_BIT2 | _BIT1), _BIT1);

    // Set Follower(destination) & Initator LA
    ScalerSetBit(P18_B5_CEC1_TXCR0_2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), (GET_CEC_TX_DEST_LA_TO_SEND() << 3));
    ScalerSetBit(P18_B4_CEC1_TXCR0_1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (GET_CEC_TX_INIT_LA_TO_SEND() << 3));

    // Set length of data fill to CecTx Ffio & Enable CecTx fifo cnt
    ScalerSetBit(P18_B9_CEC1_TXDR0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_stCecTxTransmitInfo.ucDbLength);
    ScalerSetBit(P18_B9_CEC1_TXDR0, ~(_BIT6 | _BIT5), _BIT6); // settle down

    DebugMessageCEC("=> Cec Tx send: HB", g_stCecTxTransmitInfo.ucTransmitHb);

    // Clear & Set message into CEC Tx Fifo
    memset((volatile BYTE xdata *)P18_C0_CEC1_TXDR1_1, 0x00, 16);
    for(ucParam = 0; ucParam < g_stCecTxTransmitInfo.ucDbLength; ucParam += 1)
    {
        ScalerSetByte((P18_C0_CEC1_TXDR1_1 + ucParam), g_stCecTxTransmitInfo.pucTransmitDb[ucParam]);
        DebugMessageCEC("=> Cec Tx send: DB", g_stCecTxTransmitInfo.pucTransmitDb[ucParam]);
    }

    // Set Retry#
    ScalerSetBit(P18_A8_CEC1_RTCR0_1, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_stCecTxTransmitInfo.b3RetryCnt);

    // CecTx Transmit Enable
    ScalerSetBit(P18_B4_CEC1_TXCR0_1, ~(_BIT2 | _BIT1), _BIT2);
}

//--------------------------------------------------
// Description  : CEC is sending
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerCecIsSending(void)
{
    // Check cec_tx_en & EOM
    return ((ScalerGetBit(P18_B4_CEC1_TXCR0_1, _BIT2) == _BIT2) &&
            (ScalerGetBit(P18_B5_CEC1_TXCR0_2, _BIT2) == 0x00));
}

//--------------------------------------------------
// Description  : CEC interrupt routine
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerCecIntHandler_EXINT0(void) using 1
{
#if(_CEC_RX_INT_SUPPORT == _ON)
    // rx_int=1 or DB_EOM received in snooping mode
    if((ScalerGetBit_EXINT(P18_B0_CEC1_RXCR0_1, _BIT4) == _BIT4) && (ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, _BIT6) == _BIT6))
    {
        bit bReturn = 0;

        if((GET_CEC_FUNCTION_ENABLE() == _FALSE) || (ScalerCecCheckRxSituation_EXINT0() == _FALSE))
        {
            bReturn = 1;
        }

        if(bReturn == 0)
        {
            ScalerCecRxMsgReceiving_EXINT0();
        }

        // clr rx_int
        ScalerSetBit_EXINT(P18_B1_CEC1_RXCR0_2, ~_BIT6, _BIT6);

        // clr cec_all_irq_keep & wakeup_irq_keep
        ScalerSetBit_EXINT(P19_E0_CEC1_POWER_SAVING_MODE, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT1));

        // reset
        ScalerSetBit_EXINT(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetBit_EXINT(P18_B0_CEC1_RXCR0_1, ~(_BIT7 | _BIT6), _BIT7);
    }
#endif

/*
    // receive
    if(ScalerGetBit_EXINT(P18_B1_CEC1_RXCR0_2, _BIT6) == _BIT6)
    {
        ScalerSetBit_EXINT(P18_B1_CEC1_RXCR0_2, ~(_BIT6), _BIT6);
    }

    // transmission
    if(ScalerGetBit_EXINT(P18_B5_CEC1_TXCR0_2, _BIT1) == _BIT1)
    {
        ScalerSetBit_EXINT(P18_B5_CEC1_TXCR0_2, ~(_BIT1), _BIT1);
    }

    // overflow

    // clear all CEC interrupts status
    ScalerSetBit_EXINT(P19_E0_CEC1_POWER_SAVING_MODE, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT2 | _BIT1));
    ScalerSetBit_EXINT(P19_E4_CEC1_INTCR_02, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
*/
}
#endif

