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
// ID Code      : RL6432_Series_MHLRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX1_ADOPTER_ID_HBYTE()                  (g_ucMHLRx1AdopterIDH)
#define GET_MHL_RX1_ADOPTER_ID_LBYTE()                  (g_ucMHLRx1AdopterIDL)
#define CLR_MHL_RX1_ADOPTER_ID_HBYTE()                  (g_ucMHLRx1AdopterIDH = 0xFF)
#define CLR_MHL_RX1_ADOPTER_ID_LBYTE()                  (g_ucMHLRx1AdopterIDL = 0xFF)

#define GET_MHL_RX1_PROCESS_STATE()                     (g_stMHLRx1Process.b4MHLProcessState)
#define SET_MHL_RX1_PROCESS_STATE(x)                    (g_stMHLRx1Process.b4MHLProcessState = (x))

#define GET_MHL_RX1_READY_TO_TRANSMIT()                 (g_stMHLRx1Process.b1MHLTransmitStatus)
#define SET_MHL_RX1_READY_TO_TRANSMIT()                 (g_stMHLRx1Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX1_READY_TO_TRANSMIT()                 (g_stMHLRx1Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX1_READY_TO_RESEND()                   (g_stMHLRx1Process.b1MHLResendStatus)
#define SET_MHL_RX1_READY_TO_RESEND()                   (g_stMHLRx1Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX1_READY_TO_RESEND()                   (g_stMHLRx1Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx1Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx1Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx1Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx1AdopterIDH;
extern BYTE g_ucMHLRx1AdopterIDL;
extern StructMHLProcessInfo g_stMHLRx1Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHLRx1ModeMHLSetting(void);
extern void ScalerMHLRx1ModeHdmiSetting(void);
extern void ScalerMHLRx1InitialSettings(void);
extern void ScalerMHLRx1CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx1CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx1CBUSResetProc(void);
extern void ScalerMHLRx1PowerOffProc(void);
extern bit ScalerMHLRx1DetectClkMode(void);
extern BYTE ScalerMHLRx1DetectClkMode_EXINT0(void);
extern void ScalerMHLRx1IntHandler_EXINT0(void);
extern bit ScalerMHLRx1MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx1MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
extern void ScalerMHLRx1MscCheckDeviceINT(void);
extern void ScalerMHLRx1SetDevCapReg(void);
extern bit ScalerMHLRx1MscHandler(BYTE ucActivePort, BYTE ucModeState);
extern bit ScalerMHLRx1MscRAPHandler(void);
extern bit ScalerMHLRx1MscRCPGetCommand(BYTE *pucKeyCode);

#if(_MHL_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx1MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx1PSPreDetect(void);
extern bit ScalerMHLRx1NormalPreDetect(void);
extern void ScalerMHLRx1TimerEventProc(EnumScalerTimerEventID enumEventID);

#endif  // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

