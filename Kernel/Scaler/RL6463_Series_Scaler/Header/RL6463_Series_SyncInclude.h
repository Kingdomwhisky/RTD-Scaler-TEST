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
// ID Code      : RL6463_Series_SyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of DP FreeSync AMD SPD Info
//--------------------------------------------------
#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DPRX0_AMD_SPD_INFO(x)                           (ScalerFreeSyncDpRx0GetAmdSpdInfo(x))
#define GET_DPRX1_AMD_SPD_INFO(x)                           (ScalerFreeSyncDpRx0GetAmdSpdInfo(x))

#define GET_DPRX0_BS_TO_HS_DELAY(x)                         (ScalerFreeSyncDpRx0GetBStoHSDelay(x))
#define GET_DPRX1_BS_TO_HS_DELAY(x)                         (ScalerFreeSyncDpRx0GetBStoHSDelay(x))

#define GET_DPRX0_H_PERIOD()                                (ScalerFreeSyncDpRx0GetHPeriod())
#define GET_DPRX1_H_PERIOD()                                (ScalerFreeSyncDpRx0GetHPeriod())

#define GET_DPRX0_HSW()                                     (ScalerFreeSyncDpRx0GetHSW())
#define GET_DPRX1_HSW()                                     (ScalerFreeSyncDpRx0GetHSW())

#define GET_DPRX0_V_FREQ()                                  (ScalerFreeSyncDpRx0GetVFreq())
#define GET_DPRX1_V_FREQ()                                  (ScalerFreeSyncDpRx0GetVFreq())

#define GET_DPRX0_V_PERIOD()                                (ScalerFreeSyncDpRx0GetVPeriod())
#define GET_DPRX1_V_PERIOD()                                (ScalerFreeSyncDpRx0GetVPeriod())
#endif

//--------------------------------------------------
// Definitions of HDMI FreeSync AMD SPD Info
//--------------------------------------------------
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#define GET_HDMIRX0_AMD_SPD_INFO(x)                         (ScalerFreeSyncHDMIRx0GetAmdSpdInfo(x))
#define GET_HDMIRX1_AMD_SPD_INFO(x)                         (ScalerFreeSyncHDMIRx0GetAmdSpdInfo(x))
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
extern BYTE idata g_pucHdcpBksvBackup[5];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern WORD ScalerSyncGetInputPixelClk(void);

#if(_FREESYNC_SUPPORT == _ON)
extern void ScalerSyncFREESYNCTestPinEnable(void);
#endif

