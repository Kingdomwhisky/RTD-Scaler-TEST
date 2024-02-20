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
// ID Code      : SysInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern BYTE xdata g_ucSignalUnstable;
extern BYTE xdata g_ucIssueState;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from SysMain.c
//----------------------------------------------------------------------------------------
extern void SysStartUpCheck(void);
#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
extern void SysMainStartUserCode(BYTE ucBankAddress);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from SysPower.c
//----------------------------------------------------------------------------------------
extern bit SysPowerCheckFakeSaving(void);

//----------------------------------------------------------------------------------------
// Extern functions from SysMode.c
//----------------------------------------------------------------------------------------
extern BYTE SysModeGetModeState(void);
extern bit SysModeGetTimingConfirm(void);
extern void SysModeClrModeStateChange(void);
extern void SysModeSetFreeRun(void);
extern bit SysModeGetModeStateChange(void);
extern void SysModeSetResetTarget(EnumModeAction enumResetTarget);
extern void SysModeColorSpaceConvert(EnumColorSpace enumColorFormat, EnumDBApply enumDBApply);
extern void SysModeSetupIDomainIniValue(void);
extern void SysModeDisplayTimingInitial(void);
#if(_FREESYNC_SUPPORT == _ON)
extern void SysModeDrrSetMdomainInfo(void);
extern WORD SysModeDrrGetIVFreq(EnumSourceSearchPort enumSearchPort);

#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
extern WORD SysModeFreeSyncDpGetDDCRamAddress(EnumSourceSearchPort enumSearchPort);
#endif
#endif
#endif

//----------------------------------------------------------------------------------------
// Extern functions from SysPower.c
//----------------------------------------------------------------------------------------
extern BYTE SysPowerGetPowerStatus(void);
extern void SysPowerSetTargetPowerStatus(EnumPowerStatus enumPorStatus);

//----------------------------------------------------------------------------------------
// Extern functions from SysSource.c
//----------------------------------------------------------------------------------------
extern BYTE SysSourceGetSourceType(void);
extern BYTE SysSourceGetInputPort(void);
extern BYTE SysSourceGetSpecificInputPort(BYTE ucIndex);
extern BYTE SysSourceGetInputPortType(BYTE ucInputPort);
extern BYTE SysSourceGetJudge(BYTE ucInputPort);
extern bit SysSourceGetPreDetect(BYTE ucInputPort);

extern void SysSourceSwitchInputPort(BYTE ucInputPort);

#if(_DP_EMBEDDED_SWITCH_SUPPORT_TYPE == _DP_EMBEDDED_SWITCH_2_DP)
extern void SysSourceEmbeddedDpSwitch(EnumSourceSearchPort enumDpPort);
#endif

extern bit SysSourceCheckTargetTimes(BYTE ucTargetTimes);
extern void SysSourceSetScanType(BYTE ucScanType);
extern BYTE SysSourceGetScanType(void);
extern BYTE SysSourceConvertSearchPort(BYTE ucInputPort);
extern bit SysSourceGetCableDetect(BYTE ucInputPort);
extern bit SysSourceGetCableStatusChange(BYTE ucInputPort);
extern void SysSourceSetSearchPriority(EnumSourceSearchPort enumPort, EnumSourceSearchPortPriority enumSourcePriority);
extern void SysSourceSetSearchGroup(EnumSourceSearchPort enumPort, EnumSourceSearchGroup enumSourceGroup);
extern void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime);
extern void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime);

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_EIZO_STYLE)
extern void SysSourceEizoSetPowerSavingSupport(bit bOn);
extern bit SysSourceGetSourceSwitchFinish(void);
#endif

#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
extern bit SysSourceHpGetSourceJudge(void);
extern BYTE SysSourceHpGetTargetSourceType(BYTE ucSearchIndex);
extern BYTE SysSourceHpGetTargetSearchTimes(void);
extern bit SysSourceHpGetSwitchPortNoCable(void);
extern bit SysSourceHpGetTargetPortNoSignal(void);
#endif

#if(_SOURCE_BACKGROUND_DETECT_SUPPORT == _ON)
extern BYTE SysSourceBgGetInputPort(void);
extern bit SysSourceBgGetJudge(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from SysAudio.c
//----------------------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)
extern EnumAudioState SysAudioGetAudioState(void);
extern void SysAudioPowerProc(EnumPowerAction enumSwitch);
extern void SysAudioMuteProc(bit bMute);
extern void SysAudioChangeAudioState(EnumAudioState enumAudioState);

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
extern BYTE SysSourceGetAudioPlaybackPort(void);
#endif

#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
extern void SysAudioInternalGenTestProc(bit bOn);
#endif
#endif


//----------------------------------------------------------------------------------------
// Extern functions from SysType.c
//----------------------------------------------------------------------------------------
#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern void SysTypeCSetPortCtrlRequest(BYTE ucInputPort);
extern EnumTypeCPowerRole SysTypeCGetPortControllerPowerRole(BYTE ucInputPort);
extern BYTE SysTypeCGetPartnerPdoCnt(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole);
extern StructTypeCUserPDO SysTypeCGetPartnerPdo(BYTE ucInputPort, EnumTypeCPowerRole enumPowerRole, BYTE ucPdoIndex);
extern bit SysTypeCGetPdoStatus(BYTE ucInputPort, BYTE *pucVoltage, BYTE *pucCurrent);
extern bit SysTypeCGetCcAttach(BYTE ucInputPort);
extern bit SysTypeCGetAltModeReady(BYTE ucInputPort);
extern EnumTypeCPinCfgType SysTypeCGetPinAssignment(BYTE ucInputPort);
extern BYTE SysTypeCGetTypeCIndex(BYTE ucInputPort);
extern void SysTypeCSetCapabilityChangeFlag(BYTE ucInputPort, EnumTypeCCapChgStatus enumCapability);

#if(_TYPE_C_PORT_CTRL_MODAL_OPERATION_SUPPORT == _ON)
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_LENOVO_ALT_MODE)
extern EnumTypeCLenovoAltModeStatus SysTypeCGetLenovoAltModeReady(BYTE ucInputPort);
extern EnumTypeCLenovoDeviceType SysTypeCGetLenovoDeviceType(BYTE ucInputPort);
#endif
#if(_TYPE_C_VENDOR_ALT_MODE == _TYPE_C_HP_ALT_MODE)
extern EnumTypeCHpAltModeStatus SysTypeCGetHpAltModeReady(BYTE ucInputPort);
#endif
#endif

#if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
extern void SysTypeCOsdHubProc(void);
#endif // End of #if(_DP_TYPE_C_HUB_COMMUNICATION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
