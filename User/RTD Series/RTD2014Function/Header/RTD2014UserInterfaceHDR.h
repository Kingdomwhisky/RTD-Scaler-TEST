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
// ID Code      : RTD2014UserInterfaceHDR.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDR Light Enhance
//--------------------------------------------------
typedef enum
{
    _HDR10_LIGHTENHANCE_NONE,
    _HDR10_LIGHTENHANCE_TYPE_120,
    _HDR10_LIGHTENHANCE_TYPE_140,
    _HDR10_LIGHTENHANCE_TYPE_160,
}EnumHDR10LightEnhanceType;

//--------------------------------------------------
// Definitions of HDR10 Color Enhance
//--------------------------------------------------
typedef enum
{
    _HDR10_COLORENHANCE_OFF,
    _HDR10_COLORENHANCE_TYPE_1,
    _HDR10_COLORENHANCE_TYPE_2,
    _HDR10_COLORENHANCE_TYPE_3,
}EnumHDR10ColorEnhanceType;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#ifndef __USER_INTERFACE_HDR__

#if(_ULTRA_HDR_SUPPORT == _ON)

extern void UserInterfaceHDRAdjustSDRProc(void);

#if(_HDR10_SUPPORT == _ON)
extern EnumHDR10ModeDef UserInterfaceHDRGetHDR10ModeStatus(EnumSourceSearchPort enumSourcePort);
extern void UserInterfaceHDRAdjustHDR10Proc(void);
extern EnumHDR10MaxMasteringLvType UserInterfaceHDRGetHDR10ForceModeMaxMasteringLv(void);
extern EnumHDR10ColorMatrix UserInterfaceHDRGetHDR10ForceModeColorMatrix(void);
extern EnumHDR10MaxMasteringLvType UserInterfaceHDRGetHDR10MaxMasteringLv0Type(void);
extern EnumHDR10DarkEnhanceStatus UserInterfaceHDRGetHDR10DarkEnhanceStatus(void);

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
extern EnumHDR10LightEnhanceStatus UserInterfaceHDRGetHDR10LightEnhanceStatus(void);
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
extern BYTE UserInterfaceHDRGetHDR10LightEnhanceGain(void);
#endif
#endif

#if(_DCC_FUNCTION == _ON)
extern BYTE UserInterfaceHDRGetHDR10DCCTableBank(void);
extern code BYTE *UserInterfaceHDRGetHDR10DCCTable(EnumHDR10LightEnhanceMaxMasteringLv enumHDR10LightEnhanceMaxMasteringLv);
#endif

#if(_ICM_SUPPORT == _ON)
extern BYTE UserInterfaceHDRGetHDR10ICMTableBank(void);
extern code BYTE *UserInterfaceHDRGetHDR10ICMTable(void);
#endif

#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
extern EnumHDR10FixedPointToneMappingStatus UserInterfaceHDRGetHDR10FixedPointTMStatus(void);
#endif

extern void UserInterfaceHDRGetHDR10UserAssignTable(StructHDR10Table *pstHDR10Table);
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
extern void UserInterfaceHDRAdjustFreeSyncIIProc(void);
#endif
#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

#endif // End of __USER_INTERFACE_HDR__

