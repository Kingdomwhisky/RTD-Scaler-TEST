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
// ID Code      : RL6410_Series_MeasureInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define CHECK_MEASURE_FROM_VGA()                        (ScalerGetBit(P30_00_SYNC_SELECT, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT1 | _BIT0))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMeasureInterfaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort *penumSourceSearchPort);
extern bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerMeasureSetOfflineMeasure(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourcePort);

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern bit ScalerMeasureFinalSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
#endif

extern void ScalerMeasureUpdateInputTimingPolarity(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, StructMeasureSyncData *pstMeasureSyncHV);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend);
extern void ScalerMeasureCheckFirstLineShift(EnumSourceSearchPort enumSourceSearchPort, WORD usFrameHwidth);

#if(_DUAL_DVI_SUPPORT == _ON)
extern bit ScalerMeasureDualDviMergedCheck(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerMeasureDualDviOfflineCheck(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerMeasureDualDviOnlineCheck(void);
#endif

#endif

extern void ScalerMeasureInterlaceInitial(BYTE ucSourceType, EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerMeasureInterlaceCheck(BYTE ucSourceType, EnumSourceSearchPort enumSourceSearchPort);

extern bit ScalerMeasureCheckVsBypass(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
