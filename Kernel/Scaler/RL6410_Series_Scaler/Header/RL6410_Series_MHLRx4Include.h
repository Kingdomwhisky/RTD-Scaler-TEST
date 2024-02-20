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
// ID Code      : RL6410_Series_MHLRx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX4_ADOPTER_ID_HBYTE()                  (g_ucMHLRx4AdopterIDH)
#define GET_MHL_RX4_ADOPTER_ID_LBYTE()                  (g_ucMHLRx4AdopterIDL)
#define CLR_MHL_RX4_ADOPTER_ID_HBYTE()                  (g_ucMHLRx4AdopterIDH = 0xFF)
#define CLR_MHL_RX4_ADOPTER_ID_LBYTE()                  (g_ucMHLRx4AdopterIDL = 0xFF)

#define GET_MHL_RX4_PROCESS_STATE()                     (g_stMHLRx4Process.b4MHLProcessState)
#define SET_MHL_RX4_PROCESS_STATE(x)                    (g_stMHLRx4Process.b4MHLProcessState = (x))

#define GET_MHL_RX4_READY_TO_TRANSMIT()                 (g_stMHLRx4Process.b1MHLTransmitStatus)
#define SET_MHL_RX4_READY_TO_TRANSMIT()                 (g_stMHLRx4Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX4_READY_TO_TRANSMIT()                 (g_stMHLRx4Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX4_READY_TO_RESEND()                   (g_stMHLRx4Process.b1MHLResendStatus)
#define SET_MHL_RX4_READY_TO_RESEND()                   (g_stMHLRx4Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX4_READY_TO_RESEND()                   (g_stMHLRx4Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx4Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx4Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx4Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx4AdopterIDH;
extern BYTE g_ucMHLRx4AdopterIDL;
extern StructMHLProcessInfo g_stMHLRx4Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHLRx4ModeMHLSetting(void);
extern void ScalerMHLRx4ModeHdmiSetting(void);
extern void ScalerMHLRx4InitialSettings(void);
extern void ScalerMHLRx4CBUSPhySwitch(bit bSelect);
extern void ScalerMHLRx4CBUSSwitchClk(EnumClkSel enumClockSel);
extern void ScalerMHLRx4CBUSResetProc(void);
extern void ScalerMHLRx4PowerOffProc(void);
extern bit ScalerMHLRx4DetectClkMode(void);
extern BYTE ScalerMHLRx4DetectClkMode_EXINT0(void);
extern void ScalerMHLRx4IntHandler_EXINT0(void);
extern bit ScalerMHLRx4MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx4MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
extern void ScalerMHLRx4MscCheckDeviceINT(void);
extern void ScalerMHLRx4SetDevCapReg(void);

extern bit ScalerMHLRx4MscHandler(BYTE ucActivePort, BYTE ucModeState);
extern bit ScalerMHLRx4MscRAPHandler(void);

#if(_MHL_UCP_SUPPORT == _ON)
extern BYTE ScalerMHLRx4MscUCPGetCommand(BYTE *pucKeyCode);
#endif

extern bit ScalerMHLRx4PSPreDetect(void);
extern bit ScalerMHLRx4NormalPreDetect(void);

#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
