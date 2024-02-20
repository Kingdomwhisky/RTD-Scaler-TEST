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
// ID Code      : RL6492_Series_DPInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
#define _DP_FREESYNC_IVSTART                            1
#endif

//--------------------------------------------------
//  DP LEQ RELOAD Define
//--------------------------------------------------
#define _DP_RELOAD_LEQ_INITIAL                          0
#define _DP_RELOAD_LEQ_LARGE                            1
#define _DP_RELOAD_LEQ_DEFAULT                          2

//--------------------------------------------------
//  DP HDCP Ctrl DPCD Switch
//--------------------------------------------------
#define SET_REG_DP_RX0_DPCD_CTRL_BY_HDCP()              {\
                                                            ScalerSetBit(PBA_FA_DUMMY_0, ~_BIT4, 0x00);\
                                                            ScalerSetBit(PB7_FA_DUMMY_0, ~_BIT4, _BIT4);\
                                                        }

#define SET_REG_DP_RX1_DPCD_CTRL_BY_HDCP()              {\
                                                            ScalerSetBit(PB7_FA_DUMMY_0, ~_BIT4, 0x00);\
                                                            ScalerSetBit(PBA_FA_DUMMY_0, ~_BIT4, _BIT4);\
                                                        }


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpSecDataReset(BYTE ucInputPort);
extern void ScalerDpHDCPUnplugReset(BYTE ucInputPort);
extern bit ScalerDpHdcpCheckValid(BYTE ucInputPort);
extern void ScalerDpFirstActiveProc(BYTE ucInputPort);
extern void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction);

extern void ScalerDpFakeLinkTrainingSetting(BYTE ucInputPort);
extern void ScalerDpLowPowerProc(void);
extern void ScalerDpResetProc(void);
extern void ScalerDpTimerEventProc(EnumScalerTimerEventID enumEventID);

#if(_DP_HDCP_ARBITER_SUPPORT == _ON)
extern void ScalerDpHdcpCapSwitch(BYTE ucInputPort);
extern void ScalerDpHdcpCtrlDpcdSwitch(BYTE ucInputPort);
#endif
#endif
