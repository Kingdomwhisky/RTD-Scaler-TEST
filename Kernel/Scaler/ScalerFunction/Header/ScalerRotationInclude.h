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
// ID Code      : ScalerRotationInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DISPLAY_ROTATION_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_ROT_TYPE()                                  (g_stRotationStatus.enumRotationType)
#define SET_ROT_TYPE(x)                                 (g_stRotationStatus.enumRotationType = (x))

#define GET_ROT_DISP_SIZE()                             (g_stRotationStatus.enumRotationDispSize)
#define SET_ROT_DISP_SIZE(x)                            (g_stRotationStatus.enumRotationDispSize = (x))

#if(_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_I)
#if(_MEMORY_BANK == 8)
#define _PICT_SET_WIDTH_SCALE                           (16)        // Max: 32
#define _BLOCK_UNIT_WIDTH                               (512)       // 64*8 = 512, Unit: Byte
#else
#define _PICT_SET_WIDTH_SCALE                           (32)
#define _BLOCK_UNIT_WIDTH                               (256)       // 4 Bank, 64*4 = 256
#endif

#define _ROTATION_LINE_BUFFER                           (2176) // 1088 * 60 = 2176 @ 30bit

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructRotationStatus g_stRotationStatus;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerRotationCheckVideoCompensation(void);
extern bit ScalerRotationCheckStatus(void);

#if(_DISPLAY_ROTATION_TYPE == _DISPLAY_ROTATION_GEN_I)
extern void ScalerRotationFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
extern void ScalerRotationFRCInputCtrl(WORD usHorSize, WORD usVerSize);
extern void ScalerRotationInitial(void);
extern void ScalerRotationSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);
extern void ScalerRotationSetFRCEn(EnumFRCOnOff enumCapDispOnOff, bit bEn);
extern void ScalerRotationSetInfo(WORD usHSize, WORD usVSize);
extern void ScalerRotationSetPictSet(WORD usWidth, WORD usHeight);
#endif
#endif

