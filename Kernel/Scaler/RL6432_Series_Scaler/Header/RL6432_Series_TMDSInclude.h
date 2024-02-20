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
// ID Code      : RL6432_Series_TMDSInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define CHECK_TMDS_DPHY_SWITCH(port)                (\
                                                        ((((port) == _D1_INPUT_PORT) && (ScalerGetBit_EXINT(P7B_30_ANA_CDR_06, _BIT3) == _BIT3))) ||\
                                                        ((((port) == _D2_INPUT_PORT) && (ScalerGetBit_EXINT(P7B_30_ANA_CDR_06, _BIT3) == 0x00))) ||\
                                                        ((((port) == _D3_INPUT_PORT) && (ScalerGetBit_EXINT(P7C_30_ANA_CDR_06, _BIT3) == 0x00)))\
                                                    )

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerTMDSInitial(BYTE ucInputPort);
extern void ScalerTMDSInterruptInitial(BYTE ucInputPort);
extern void ScalerTMDSVideoDetectEvent(EnumScalerTimerEventID enumEventID);
extern void ScalerTMDSResetProc(void);

#if(_HDMI_SUPPORT == _ON)

extern void ScalerTMDSHdmiAVMuteProc(void);
extern void ScalerTMDSHdmiWatchDog(BYTE ucWDType, bit bEnable);
extern void ScalerTMDSHdmiPacketDetectEvent(EnumScalerTimerEventID enumEventID);

#if(_HDMI_2_0_SUPPORT == _ON)
extern void ScalerTMDSHdmiReadRequestTimerEnable_WDINT(bit bEnable);
extern void ScalerTMDSHdmi2FormatResetEvent(EnumScalerTimerEventID enumEventID);
#endif

#endif

extern void ScalerTMDSFreqDetectDisable(void);
extern void ScalerTMDSFirstActiveProc(BYTE ucInputPort, BYTE ucSourceType);
extern bit ScalerTMDSHdcpEnabled(BYTE ucInputPort);
extern void ScalerTMDSHotPlugEvent(BYTE ucPortSelect);
extern void ScalerTMDSBeforeHotPlugEventProc(BYTE ucPortSelect);
extern void ScalerTMDSHotPlugLowProc(BYTE ucPortSelect);
extern void ScalerTMDSHotPlugHighProc(BYTE ucPortSelect, WORD usHpdTime);
extern void ScalerTMDSAfterHotPlugEventProc(BYTE ucPortSelect);

#if(_TMDS_Z0_POWER_SAVING_TOGGLE_SUPPORT == _ON)
extern void ScalerTMDSClkLaneZ0StartToggle(void);
extern void ScalerTMDSClkLaneZ0LowProc(void);
extern void ScalerTMDSClkLaneZ0HighProc(void);
extern void ScalerTMDSClkLaneZ0StopToggle(void);
#endif

#endif
