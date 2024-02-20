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
// ID Code      : RL6432_Series_MHLRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX3_ADOPTER_ID_HBYTE()                  (g_ucMHLRx3AdopterIDH)
#define GET_MHL_RX3_ADOPTER_ID_LBYTE()                  (g_ucMHLRx3AdopterIDL)
#define CLR_MHL_RX3_ADOPTER_ID_HBYTE()                  (g_ucMHLRx3AdopterIDH = 0xFF)
#define CLR_MHL_RX3_ADOPTER_ID_LBYTE()                  (g_ucMHLRx3AdopterIDL = 0xFF)

#define GET_MHL_RX3_PROCESS_STATE()                     (g_stMHLRx3Process.b4MHLProcessState)
#define SET_MHL_RX3_PROCESS_STATE(x)                    (g_stMHLRx3Process.b4MHLProcessState = (x))

#define GET_MHL_RX3_READY_TO_TRANSMIT()                 (g_stMHLRx3Process.b1MHLTransmitStatus)
#define SET_MHL_RX3_READY_TO_TRANSMIT()                 (g_stMHLRx3Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX3_READY_TO_TRANSMIT()                 (g_stMHLRx3Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX3_READY_TO_RESEND()                   (g_stMHLRx3Process.b1MHLResendStatus)
#define SET_MHL_RX3_READY_TO_RESEND()                   (g_stMHLRx3Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX3_READY_TO_RESEND()                   (g_stMHLRx3Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx3Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx3Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx3Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx3AdopterIDH;
extern BYTE g_ucMHLRx3AdopterIDL;
extern StructMHLProcessInfo g_stMHLRx3Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHLRx3ModeMHLSetting(void);
extern void ScalerMHLRx3ModeHdmiSetting(void);
extern void ScalerMHLRx3InitialSettings(void);
extern void ScalerMHLRx3CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx3CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx3CBUSResetProc(void);
extern void ScalerMHLRx3PowerOffProc(void);
extern bit ScalerMHLRx3DetectClkMode(void);
extern BYTE ScalerMHLRx3DetectClkMode_EXINT0(void);
extern void ScalerMHLRx3IntHandler_EXINT0(void);
extern bit ScalerMHLRx3MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx3MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
extern void ScalerMHLRx3MscCheckDeviceINT(void);

extern bit ScalerMHLRx3MscHandler(BYTE ucActivePort, BYTE ucModeState);
extern bit ScalerMHLRx3MscRAPHandler(void);

#if(_MHL_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx3MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx3PSPreDetect(void);
extern bit ScalerMHLRx3NormalPreDetect(void);

#endif  // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

