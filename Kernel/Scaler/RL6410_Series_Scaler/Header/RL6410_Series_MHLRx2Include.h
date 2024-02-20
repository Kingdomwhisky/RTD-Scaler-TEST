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
// ID Code      : RL6410_Series_MHLRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX2_ADOPTER_ID_HBYTE()                  (g_ucMHLRx2AdopterIDH)
#define GET_MHL_RX2_ADOPTER_ID_LBYTE()                  (g_ucMHLRx2AdopterIDL)
#define CLR_MHL_RX2_ADOPTER_ID_HBYTE()                  (g_ucMHLRx2AdopterIDH = 0xFF)
#define CLR_MHL_RX2_ADOPTER_ID_LBYTE()                  (g_ucMHLRx2AdopterIDL = 0xFF)

#define GET_MHL_RX2_PROCESS_STATE()                     (g_stMHLRx2Process.b4MHLProcessState)
#define SET_MHL_RX2_PROCESS_STATE(x)                    (g_stMHLRx2Process.b4MHLProcessState = (x))

#define GET_MHL_RX2_READY_TO_TRANSMIT()                 (g_stMHLRx2Process.b1MHLTransmitStatus)
#define SET_MHL_RX2_READY_TO_TRANSMIT()                 (g_stMHLRx2Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX2_READY_TO_TRANSMIT()                 (g_stMHLRx2Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX2_READY_TO_RESEND()                   (g_stMHLRx2Process.b1MHLResendStatus)
#define SET_MHL_RX2_READY_TO_RESEND()                   (g_stMHLRx2Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX2_READY_TO_RESEND()                   (g_stMHLRx2Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx2Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx2Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx2Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx2AdopterIDH;
extern BYTE g_ucMHLRx2AdopterIDL;
extern StructMHLProcessInfo g_stMHLRx2Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHLRx2ModeMHLSetting(void);
extern void ScalerMHLRx2ModeHdmiSetting(void);
extern void ScalerMHLRx2InitialSettings(void);
extern void ScalerMHLRx2CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx2CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx2CBUSResetProc(void);
extern void ScalerMHLRx2PowerOffProc(void);
extern bit ScalerMHLRx2DetectClkMode(void);
extern BYTE ScalerMHLRx2DetectClkMode_EXINT0(void);
extern void ScalerMHLRx2IntHandler_EXINT0(void);
extern bit ScalerMHLRx2MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx2MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
extern void ScalerMHLRx2MscCheckDeviceINT(void);

extern bit ScalerMHLRx2MscHandler(BYTE ucActivePort, BYTE ucModeState);
extern bit ScalerMHLRx2MscRAPHandler(void);

#if(_MHL_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx2MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx2PSPreDetect(void);
extern bit ScalerMHLRx2NormalPreDetect(void);

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

