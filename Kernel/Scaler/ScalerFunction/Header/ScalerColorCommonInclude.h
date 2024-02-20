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
// ID Code      : ScalerColorCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of DCC Ready Flag
//--------------------------------------------------
#define GET_DCC_READY_STATUS()                      (g_bDCCReadyStatus)
#define SET_DCC_READY_STATUS()                      (g_bDCCReadyStatus = _TRUE)
#define CLR_DCC_READY_STATUS()                      (g_bDCCReadyStatus = _FALSE)

//--------------------------------------------------
// Macro of DCR Ready Flag
//--------------------------------------------------
#define GET_DCR_READY_STATUS()                      (g_bDCRReadyStatus)
#define SET_DCR_READY_STATUS()                      (g_bDCRReadyStatus = _TRUE)
#define CLR_DCR_READY_STATUS()                      (g_bDCRReadyStatus = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDCCReadyStatus;
extern bit g_bDCRReadyStatus;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);
