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
// ID Code      : RL6449_Series_MHLInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_MHL_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 eCBUS Start-Up
//--------------------------------------------------
#define _MHL3_SOURCE_ECBUS_FWD_COMMA2_TMOUT_MAX         60
#define _MHL3_SOURCE_ECBUS_FWD_COMMA2_TMOUT_MIN         10
#define _MHL3_SOURCE_ECBUS_FWD_AVTIVE_TMOUT_MAX         60
#define _MHL3_SOURCE_ECBUS_FWD_AVTIVE_TMOUT_MIN         10


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of MHL Port Valid
//--------------------------------------------------
#define _MHL_PORT_VALID                                 ((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) + (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) + (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) + (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))

//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX2_ADOPTER_ID_HBYTE()                  (g_ucMHLRx2AdopterIDH)
#define GET_MHL_RX2_ADOPTER_ID_LBYTE()                  (g_ucMHLRx2AdopterIDL)
#define CLR_MHL_RX2_ADOPTER_ID_HBYTE()                  (g_ucMHLRx2AdopterIDH = 0xFF)
#define CLR_MHL_RX2_ADOPTER_ID_LBYTE()                  (g_ucMHLRx2AdopterIDL = 0xFF)

#define GET_MHL_RX3_ADOPTER_ID_HBYTE()                  (g_ucMHLRx3AdopterIDH)
#define GET_MHL_RX3_ADOPTER_ID_LBYTE()                  (g_ucMHLRx3AdopterIDL)
#define CLR_MHL_RX3_ADOPTER_ID_HBYTE()                  (g_ucMHLRx3AdopterIDH = 0xFF)
#define CLR_MHL_RX3_ADOPTER_ID_LBYTE()                  (g_ucMHLRx3AdopterIDL = 0xFF)

#define GET_MHL_RX4_ADOPTER_ID_HBYTE()                  (g_ucMHLRx4AdopterIDH)
#define GET_MHL_RX4_ADOPTER_ID_LBYTE()                  (g_ucMHLRx4AdopterIDL)
#define CLR_MHL_RX4_ADOPTER_ID_HBYTE()                  (g_ucMHLRx4AdopterIDH = 0xFF)
#define CLR_MHL_RX4_ADOPTER_ID_LBYTE()                  (g_ucMHLRx4AdopterIDL = 0xFF)

#define GET_MHL_RX5_ADOPTER_ID_HBYTE()                  (g_ucMHLRx5AdopterIDH)
#define GET_MHL_RX5_ADOPTER_ID_LBYTE()                  (g_ucMHLRx5AdopterIDL)
#define CLR_MHL_RX5_ADOPTER_ID_HBYTE()                  (g_ucMHLRx5AdopterIDH = 0xFF)
#define CLR_MHL_RX5_ADOPTER_ID_LBYTE()                  (g_ucMHLRx5AdopterIDL = 0xFF)

#define GET_MHL_PORT_ACTIVE()                           (g_ucMHLPortActive)
#define SET_MHL_PORT_ACTIVE(x)                          (g_ucMHLPortActive = (x))

#define _MHL_MSC_COMMAND_POLLING_MESSAGE                _OFF
//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructMHLProcessInfo g_pstMHLProcess[_MHL_PORT_VALID];

extern BYTE g_ucMHLRx2AdopterIDH;
extern BYTE g_ucMHLRx2AdopterIDL;

extern BYTE g_ucMHLRx3AdopterIDH;
extern BYTE g_ucMHLRx3AdopterIDL;

extern BYTE g_ucMHLRx4AdopterIDH;
extern BYTE g_ucMHLRx4AdopterIDL;

extern BYTE g_ucMHLRx5AdopterIDH;
extern BYTE g_ucMHLRx5AdopterIDL;

extern BYTE g_ucMHLPortActive;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHLCBUSPhySwitch(BYTE ucPortSelect, bit bSelect);
extern void ScalerMHLCBUSResetProc(BYTE ucInputPort);
extern void ScalerMHLPowerOffProc(BYTE ucInputPort);
extern void ScalerMHLTimerEventProc(EnumScalerTimerEventID enumEventID);

#endif // End of #if(_MHL_SUPPORT == _ON)
