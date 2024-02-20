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
// ID Code      : UserCommonHDRInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDR Max Mastering Lv
//--------------------------------------------------
#define _HDR10_MAX_MASTERING_LV_540                             540
#define _HDR10_MAX_MASTERING_LV_1200                            1200
#define _HDR10_MAX_MASTERING_LV_4000                            4000
#define _HDR10_MAX_MASTERING_LV_10000                           10000


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDR Flow
//--------------------------------------------------
typedef enum
{
    _HDR_FLOW_COLOR_PROC_INITIAL,
    _HDR_FLOW_MODE_STATUS_ACTIVE,
    _HDR_FLOW_OSD_MODE_CHANGE,
    _HDR_FLOW_OSD_DARK_ENHANCE,
}EnumHDRFlowStatus;

//--------------------------------------------------
// Definitions of HDR Target Status
//--------------------------------------------------
typedef enum
{
    _HDR_TARGET_STATUS_DO_NOTHING,
    _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR,
    _HDR_TARGET_STATUS_SMPTE_ST_2084,
    _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR,
} EnumHDRTargetStatus;

//--------------------------------------------------
// Definitions of HDR Change Mode
//--------------------------------------------------
typedef enum
{
    _HDR10_INFO_NO_CHANGE = 0x00,
    _HDR10_INFO_EOTF_CHANGE = 0x01,
    _HDR10_INFO_PRIMARIES_CHANGE = 0x02,
    _HDR10_INFO_MAX_LV_CHANGE = 0x03,
}EnumHDR10ChangeStatus;

//--------------------------------------------------
// Definitions of FreeSync II Change Mode
//--------------------------------------------------
typedef enum
{
    _FREESYNC_II_INFO_NO_CHANGE = 0x00,
    _FREESYNC_II_COLOR_SPACE_CHANGE = _BIT0,
    _FREESYNC_II_BACKLIGHT_CONTROL_CHANGE = _BIT1,
    _FREESYNC_II_LOCAL_DIMMING_CHANGE = _BIT2,
    _FREESYNC_II_EOTF_TYPE_CHANGE = _BIT3,
    _FREESYNC_II_BACKLIGHT_RATIO_CHANGE = _BIT4,
}EnumFreeSyncIIChangeStatus;

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDR10 Status
//--------------------------------------------------
typedef enum
{
    _HDR10_OFF,
    _HDR10_ON,
}EnumHDR10Status;

//--------------------------------------------------
// Definitions of HD10R Demo Mode
//--------------------------------------------------
typedef enum
{
    _HDR10_DEMO_OFF,
    _HDR10_DEMO_ON,
}EnumHDR10DemoStatus;

//--------------------------------------------------
// Definitions of HDR Color Matrix
//--------------------------------------------------
typedef enum
{
    _HDR10_COLOR_MATRIX_SRGB,
    _HDR10_COLOR_MATRIX_ADOBE,
    _HDR10_COLOR_MATRIX_DCIP3_D65,
    _HDR10_COLOR_MATRIX_BT2020,
} EnumHDR10ColorMatrix;

//--------------------------------------------------
// Definitions of HDR Dark Enhance
//--------------------------------------------------
typedef enum
{
    _HDR10_DARK_ENHANCE_OFF,
    _HDR10_DARK_ENHANCE_ON,
}EnumHDR10DarkEnhanceStatus;

//--------------------------------------------------
// Definitions of HDR Light Enhance Status
//--------------------------------------------------
typedef enum
{
    _HDR10_LIGHTENHANCE_OFF,
    _HDR10_LIGHTENHANCE_ON,
}EnumHDR10LightEnhanceStatus;

//--------------------------------------------------
// Definitions of HDR Light Enhance Max Mastering Lv
//--------------------------------------------------
typedef enum
{
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_540, // 540 nits
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_1200, // 1200 nits
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_4000, // 4000 nits
    _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_10000, // 10000 nits
}EnumHDR10LightEnhanceMaxMasteringLv;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of FreeSync II Info
//--------------------------------------------------
typedef enum
{
    _FREESYNC_II_EOTF_NO_SUPPORT = 0x00,
    _FREESYNC_II_EOTF_SRGB = _BIT0,
    _FREESYNC_II_EOTF_BT709 = _BIT1,
    _FREESYNC_II_EOTF_GAMMA_22 = _BIT2,
    _FREESYNC_II_EOTF_GAMMA_26 = _BIT3,
    _FREESYNC_II_EOTF_PQ_INTERIM = _BIT4,
}EnumFreeSyncIIEOTFType;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_HDR10_SUPPORT == _ON)
extern StructHDR10Setting g_stHDR10Setting;
extern StructHDR10PortSettingInfo g_stHDR10PortSettingInfo;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
extern StructFreeSyncIIInfo g_stFreeSyncIISetting;
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_ULTRA_HDR_SUPPORT == _ON)

extern void UserCommonHDRHandler(void);
extern void UserCommonHDRAdjust(EnumHDRFlowStatus enumHDRFlowStatus);

#if(_HDR10_SUPPORT == _ON)
extern EnumHDR10Status UserCommonHDRGetHDR10Status(void);
extern EnumHDR10MaxMasteringLvType UserCommonHDRGetHDR10LvType(void);
extern void UserCommonHDR10SupportSwitch(void);

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
extern void UserCommonHDRAdjustHDR10ColorMatrix(void);
#endif

#if(_CONTRAST_SUPPORT == _ON)
extern void UserCommonHDRAdjustHDR10Contrast(BYTE ucContrast);
#endif

#if(_DCC_FUNCTION == _ON)
extern EnumHDR10LightEnhanceMaxMasteringLv UserCommonHDRGetHDR10LvTypeForLightEnhance(void);
#endif

extern void UserCommonHDRAdjustHDR10ColorEffect(void);
extern WORD UserCommonHDRGetHDR10ColorMatrix(void);
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
extern bit UserCommonHDRGetFreesynIIStatus(void);
extern BYTE UserCommonHDRFreeSyncIIChangeStatus(void);
extern void UserCommonHDRFreeSyncIIMode(void);
extern void UserCommonHDRFreeSyncIIProc(void);
extern bit UserCommonHDRGetFreeSyncIILDDisable(void);
extern BYTE UserCommonHDRGetFreeSyncIIEOTFType(void);
#endif

#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

