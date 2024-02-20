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
// ID Code      : UserCommonHDR.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_HDR__

#include "UserCommonInclude.h"

#if(_ULTRA_HDR_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
#define _LIGHTENHANCE_IAPSGAIN_540NIT           0x160C
#define _LIGHTENHANCE_IAPSGAIN_1200NIT          0x18CC
#define _LIGHTENHANCE_IAPSGAIN_4000NIT          0x1CEA
#define _LIGHTENHANCE_IAPSGAIN_10000NIT         0x2000
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonHDRHandler(void);
void UserCommonHDRAdjust(EnumHDRFlowStatus enumHDRFlowStatus);
EnumHDRTargetStatus UserCommonHDRGetTargetStatus(EnumHDRFlowStatus enumHDRFlowStatus, EnumHDR10ModeDef enumHDR10ModeStatus, EnumFreeSyncSupport enumFreesyncIIModeStatus);
void UserCommonHDRAdjustSDRProc(void);

#if(_HDR10_SUPPORT == _ON)
EnumHDR10Status UserCommonHDRGetHDR10Status(void);
EnumHDR10ChangeStatus UserCommonHDRGetHDR10ChangeStatus(void);
EnumHDR10MaxMasteringLvType UserCommonHDRGetHDR10LvType(void);
EnumHDR10MaxMasteringLvType UserCommonHDRGetHDR10ModifyLvType(EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType, WORD usMaxPanelLv);
void UserCommonHDRAdjustHDR10AutoMode(void);
void UserCommonHDRAdjustHDR10ForceMode(EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType, EnumHDR10ColorMatrix enumHDR10ColorMatrix);
void UserCommonHDRAdjustHDR10Proc(void);
WORD UserCommonHDRGetHDR10ColorMatrix(void);
void UserCommonHDR10SupportSwitch(void);

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
void UserCommonHDRAdjustHDR10ColorMatrix(void);
#endif

#if(_CONTRAST_SUPPORT == _ON)
void UserCommonHDRAdjustHDR10Contrast(BYTE ucContrast);
#endif

#if(_DCC_FUNCTION == _ON)
EnumHDR10LightEnhanceMaxMasteringLv UserCommonHDRGetHDR10LvTypeForLightEnhance(void);
#endif

void UserCommonHDRAdjustHDR10ColorEffect(void);
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
bit UserCommonHDRGetFreesynIIStatus(void);
BYTE UserCommonHDRFreeSyncIIChangeStatus(void);
void UserCommonHDRFreeSyncIIMode(void);
void UserCommonHDRFreeSyncIIProc(void);
bit UserCommonHDRGetFreeSyncIILDDisable(void);
BYTE UserCommonHDRGetFreeSyncIIEOTFType(void);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDR Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHDRHandler(void)
{
    if(GET_ON_LINE_CALIBRATION_STATUS() != _CALIBRATION_ON)
    {
        UserCommonHDRAdjust(_HDR_FLOW_MODE_STATUS_ACTIVE);
    }
}

//--------------------------------------------------
// Description  : Integrate HDR Auto Mode FW Flow
// Input Value  : EnumDisplayRegion, EnumHDRFlowStatus
// Output Value : none
//--------------------------------------------------
void UserCommonHDRAdjust(EnumHDRFlowStatus enumHDRFlowStatus)
{
    EnumHDR10ModeDef enumHDR10ModeStatus = _HDR10_MODE_OFF;
    EnumFreeSyncSupport enumFreesyncIIModeStatus = _FREESYNC_SUPPORT_OFF;

#if(_HDR10_SUPPORT == _ON)
    enumHDR10ModeStatus = UserInterfaceHDRGetHDR10ModeStatus(SysSourceGetInputPort());
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    enumFreesyncIIModeStatus = UserInterfaceGetFreeSyncEnable(SysSourceGetInputPort());
#endif

    switch(enumHDRFlowStatus)
    {
        case _HDR_FLOW_COLOR_PROC_INITIAL:
        case _HDR_FLOW_OSD_MODE_CHANGE:
        case _HDR_FLOW_MODE_STATUS_ACTIVE:

            if(enumHDR10ModeStatus == _HDR10_MODE_FORCE_2084)
            {
                if(enumHDRFlowStatus != _HDR_FLOW_MODE_STATUS_ACTIVE)
                {
#if(_HDR10_SUPPORT == _ON)
                    UserCommonHDRAdjustHDR10ForceMode(UserInterfaceHDRGetHDR10ForceModeMaxMasteringLv(), UserInterfaceHDRGetHDR10ForceModeColorMatrix());
                    UserCommonHDRAdjustHDR10Proc();
#endif
                }
            }
            else// if((enumHDR10ModeStatus == _HDR10_MODE_OFF) || (enumHDR10ModeStatus == _HDR10_MODE_AUTO))
            {
                switch(UserCommonHDRGetTargetStatus(enumHDRFlowStatus, enumHDR10ModeStatus, enumFreesyncIIModeStatus))
                {
#if(_HDR10_SUPPORT == _ON)

                    case _HDR_TARGET_STATUS_SMPTE_ST_2084:

                        UserCommonHDRAdjustHDR10AutoMode();
                        UserCommonHDRAdjustHDR10Proc();

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
                        SET_HDR10_UPDATE_COLORIMETRY();
#endif

                        break;
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
                    case _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR:

                        UserCommonHDRFreeSyncIIMode();
                        UserCommonHDRFreeSyncIIProc();

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
                        SET_FREESYNCII_UPDATE_COLORIMETRY();
#endif

                        break;
#endif

                    case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:

                        UserCommonHDRAdjustSDRProc();

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
                        SET_SDR_UPDATE_COLORIMETRY();
#endif

                        break;

                    case _HDR_TARGET_STATUS_DO_NOTHING:
                    default:

                        break;
                }
            }
            break;

#if(_HDR10_SUPPORT == _ON)

        case _HDR_FLOW_OSD_DARK_ENHANCE:

            switch(enumHDR10ModeStatus)
            {
                case _HDR10_MODE_AUTO:

                    if(GET_HDR10_EOTF_SETTING() == _HDR_INFO_EOTF_SMPTE_ST_2084)
                    {
                        UserCommonHDRAdjustHDR10AutoMode();
                    }

                    break;

                case _HDR10_MODE_FORCE_2084:

                    UserCommonHDRAdjustHDR10ForceMode(UserInterfaceHDRGetHDR10ForceModeMaxMasteringLv(), UserInterfaceHDRGetHDR10ForceModeColorMatrix());

                    break;

                case _HDR10_MODE_OFF:

                    UserCommonHDRAdjustSDRProc();

                    break;

                default:

                    break;
            }

            break;
#endif
        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check HDR target status to set HDR 2084, SDR or do nothing
// Input Value  : EnumDisplayRegion
// Output Value : EnumHDRTargetStatus
//--------------------------------------------------
EnumHDRTargetStatus UserCommonHDRGetTargetStatus(EnumHDRFlowStatus enumHDRFlowStatus, EnumHDR10ModeDef enumHDR10ModeStatus, EnumFreeSyncSupport enumFreesyncIIModeStatus)
{
    EnumHDRTargetStatus enumHDRTargetStatus = _HDR_TARGET_STATUS_DO_NOTHING;
    EnumHDR10ChangeStatus enumHDR10ChangeStatus = _HDR10_INFO_NO_CHANGE;
    BYTE ucFreeSyncIIChangeStatus = _FREESYNC_II_INFO_NO_CHANGE;

    enumHDR10ModeStatus = enumHDR10ModeStatus;
    enumFreesyncIIModeStatus = enumFreesyncIIModeStatus;

    switch(enumHDRFlowStatus)
    {
        case _HDR_FLOW_COLOR_PROC_INITIAL:
        case _HDR_FLOW_OSD_MODE_CHANGE:

#if(_FREESYNC_II_SUPPORT == _ON)
            SET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(g_stFreeSyncIIMetadata.b1NativeColorSpaceEnable);
            SET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(g_stFreeSyncIIMetadata.b1BacklightControlEnable);
            SET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(g_stFreeSyncIIMetadata.b1LocalDimmingDisable);
            SET_FREESYNC_II_EOTF_TYPE_SETTING(g_stFreeSyncIIMetadata.b5EOTFType);
            SET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING(g_stFreeSyncIIMetadata.ucBacklightControlRatio);

            DebugMessageHDR("Native Color Space Enable", g_stFreeSyncIIMetadata.b1NativeColorSpaceEnable);
            DebugMessageHDR("Backlight Control Enable", g_stFreeSyncIIMetadata.b1BacklightControlEnable);
            DebugMessageHDR("Local Dimming Disable", g_stFreeSyncIIMetadata.b1LocalDimmingDisable);
            DebugMessageHDR("EOTF Type", g_stFreeSyncIIMetadata.b5EOTFType);
            DebugMessageHDR("Backlight Control Ratio", g_stFreeSyncIIMetadata.ucBacklightControlRatio);
#endif

#if(_HDR10_SUPPORT == _ON)
            SET_HDR10_EOTF_SETTING(g_stHDR10SaticMetadata.ucEOTF);
            SET_HDR10_MAX_LV_SETTING(UserCommonHDRGetHDR10LvType());

            DebugMessageHDR("Initial HDR10 Metadata EOTF", (g_stHDR10SaticMetadata.ucEOTF));

            DebugMessageHDR("Initial HDR10 Metadata X0", (g_stHDR10SaticMetadata.usDisplayPrimariesX0));
            DebugMessageHDR("Initial HDR10 Metadata Y0", (g_stHDR10SaticMetadata.usDisplayPrimariesY0));

            DebugMessageHDR("Initial HDR10 Metadata X1", (g_stHDR10SaticMetadata.usDisplayPrimariesX1));
            DebugMessageHDR("Initial HDR10 Metadata Y1", (g_stHDR10SaticMetadata.usDisplayPrimariesY1));

            DebugMessageHDR("Initial HDR10 Metadata X2", (g_stHDR10SaticMetadata.usDisplayPrimariesX2));
            DebugMessageHDR("Initial HDR10 Metadata Y2", (g_stHDR10SaticMetadata.usDisplayPrimariesY2));

            DebugMessageHDR("Initial HDR10 Metadata Wx", (g_stHDR10SaticMetadata.usWhitePointX));
            DebugMessageHDR("Initial HDR10 Metadata Wy", (g_stHDR10SaticMetadata.usWhitePointY));

            DebugMessageHDR("Initial HDR10 Metadata Max Mastering Lv", (g_stHDR10SaticMetadata.usMaxDisplayMasteringLv));
            DebugMessageHDR("Initial HDR10 Metadata Min Mastering Lv", (g_stHDR10SaticMetadata.usMinDisplayMasteringLv));

            DebugMessageHDR("Initial HDR10 Metadata Max CLL", (g_stHDR10SaticMetadata.usMaxCLL));
            DebugMessageHDR("Initial HDR10 Metadata Max FALL", (g_stHDR10SaticMetadata.usMaxFALL));

            if((enumHDR10ModeStatus == _HDR10_MODE_AUTO) &&
               (GET_HDR10_EOTF_SETTING() == _HDR_INFO_EOTF_SMPTE_ST_2084))
            {
                DebugMessageHDR("HDR Target Status HDR2084", 0x00);
                enumHDRTargetStatus = _HDR_TARGET_STATUS_SMPTE_ST_2084;
                break;
            }
            else
#endif
            {
#if(_FREESYNC_II_SUPPORT == _ON)
                if((enumFreesyncIIModeStatus == _FREESYNC_SUPPORT_ON) &&
                   (GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING() == _ON))
                {
                    DebugMessageHDR("HDR Target Status Freesync2", 0x00);
                    enumHDRTargetStatus = _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR;
                    break;
                }
#endif
            }

            DebugMessageHDR("HDR Target Status SDR", 0x00);
            enumHDRTargetStatus = _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR;
            break;

        case _HDR_FLOW_MODE_STATUS_ACTIVE:

#if(_HDR10_SUPPORT == _ON)
            enumHDR10ChangeStatus = UserCommonHDRGetHDR10ChangeStatus();
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
            ucFreeSyncIIChangeStatus = UserCommonHDRFreeSyncIIChangeStatus();

            if((enumFreesyncIIModeStatus == _FREESYNC_SUPPORT_ON) &&
               ((ucFreeSyncIIChangeStatus != _FREESYNC_II_INFO_NO_CHANGE) ||
                (enumHDR10ChangeStatus != _HDR10_INFO_NO_CHANGE)))
            {
                DebugMessageHDR("Native Color Space Enable", g_stFreeSyncIIMetadata.b1NativeColorSpaceEnable);
                DebugMessageHDR("Backlight Control Enable", g_stFreeSyncIIMetadata.b1BacklightControlEnable);
                DebugMessageHDR("Local Dimming Disable", g_stFreeSyncIIMetadata.b1LocalDimmingDisable);
                DebugMessageHDR("EOTF Type", g_stFreeSyncIIMetadata.b5EOTFType);
                DebugMessageHDR("Backlight Control Ratio", g_stFreeSyncIIMetadata.ucBacklightControlRatio);
                if(GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING() == _ON)
                {
                    DebugMessageHDR("HDR Target Status Freesync2", 0x00);
                    enumHDRTargetStatus = _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR;
                }
                else
                {
                    DebugMessageHDR("HDR Target Status SDR", 0x00);
                    enumHDRTargetStatus = _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR;
                }
            }
#endif

#if(_HDR10_SUPPORT == _ON)
            if((enumHDR10ModeStatus == _HDR10_MODE_AUTO) &&
               ((enumHDR10ChangeStatus != _HDR10_INFO_NO_CHANGE) ||
                (ucFreeSyncIIChangeStatus != _FREESYNC_II_INFO_NO_CHANGE)))
            {
                DebugMessageHDR("HDR10 Metadata EOTF", (g_stHDR10SaticMetadata.ucEOTF));

                DebugMessageHDR("HDR10 Metadata X0", (g_stHDR10SaticMetadata.usDisplayPrimariesX0));
                DebugMessageHDR("HDR10 Metadata Y0", (g_stHDR10SaticMetadata.usDisplayPrimariesY0));

                DebugMessageHDR("HDR10 Metadata X1", (g_stHDR10SaticMetadata.usDisplayPrimariesX1));
                DebugMessageHDR("HDR10 Metadata Y1", (g_stHDR10SaticMetadata.usDisplayPrimariesY1));

                DebugMessageHDR("HDR10 Metadata X2", (g_stHDR10SaticMetadata.usDisplayPrimariesX2));
                DebugMessageHDR("HDR10 Metadata Y2", (g_stHDR10SaticMetadata.usDisplayPrimariesY2));

                DebugMessageHDR("HDR10 Metadata Wx", (g_stHDR10SaticMetadata.usWhitePointX));
                DebugMessageHDR("HDR10 Metadata Wy", (g_stHDR10SaticMetadata.usWhitePointY));

                DebugMessageHDR("HDR10 Metadata Max Mastering Lv", (g_stHDR10SaticMetadata.usMaxDisplayMasteringLv));
                DebugMessageHDR("HDR10 Metadata Min Mastering Lv", (g_stHDR10SaticMetadata.usMinDisplayMasteringLv));

                DebugMessageHDR("HDR10 Metadata Max CLL", (g_stHDR10SaticMetadata.usMaxCLL));
                DebugMessageHDR("HDR10 Metadata Max FALL", (g_stHDR10SaticMetadata.usMaxFALL));

                if(GET_HDR10_EOTF_SETTING() == _HDR_INFO_EOTF_SMPTE_ST_2084) // HDR SMPTE ST 2084
                {
                    DebugMessageHDR("HDR Target Status HDR2084", 0x00);
                    enumHDRTargetStatus = _HDR_TARGET_STATUS_SMPTE_ST_2084;

                    if(enumHDR10ChangeStatus == _HDR10_INFO_NO_CHANGE)
                    {
                        DebugMessageHDR("HDR Target Status Do Nothing", 0x00);
                        enumHDRTargetStatus = _HDR_TARGET_STATUS_DO_NOTHING;
                    }
                }
                else
                {
                    if(enumHDRTargetStatus != _HDR_TARGET_STATUS_FREESYNC_II_NATIVE_COLOR)
                    {
                        DebugMessageHDR("HDR Target Status SDR", 0x00);
                        enumHDRTargetStatus = _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR;
                    }
                }
            }
#endif

            break;

        default:

            break;
    }

    return enumHDRTargetStatus;
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHDRAdjustSDRProc(void)
{
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
    if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
    {
        UserCommonAdjustRGBQuantizationRange();

        SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);
    }
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    UserInterfaceAdjustUltraVividProc(_DB_APPLY_NO_POLLING);
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
    ScalerColorIAPSGainEnable(_FUNCTION_OFF);
#endif

    UserInterfaceHDRAdjustSDRProc();
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return applying HDR parameter or PCM parameter
// Input Value  : None
// Output Value : _ON(HDR), _OFF(PCM)
//--------------------------------------------------
EnumHDR10Status UserCommonHDRGetHDR10Status(void)
{
    if(UserInterfaceHDRGetHDR10ModeStatus(SysSourceGetInputPort()) == _HDR10_MODE_FORCE_2084)
    {
        return _HDR10_ON;
    }
    else
    {
#if(_HDR10_SUPPORT == _ON)
        if((UserInterfaceHDRGetHDR10ModeStatus(SysSourceGetInputPort()) != _HDR10_MODE_OFF) && (GET_HDR10_EOTF_SETTING() == _HDR_INFO_EOTF_SMPTE_ST_2084))
        {
            return _HDR10_ON;
        }
        else
#endif
        {
            return _HDR10_OFF;
        }
    }

    return _HDR10_OFF;
}

//--------------------------------------------------
// Description  : Check HDR change status according to EOTF, (primaries color), max mastering luminance
// Input Value  : EnumDisplayRegion
// Output Value : HDR chagne status
//--------------------------------------------------
EnumHDR10ChangeStatus UserCommonHDRGetHDR10ChangeStatus(void)
{
    // Check if info changed
    if(GET_HDR10_EOTF_SETTING() != (g_stHDR10SaticMetadata.ucEOTF))
    {
        SET_HDR10_EOTF_SETTING(g_stHDR10SaticMetadata.ucEOTF);

        if(GET_HDR10_EOTF_SETTING() == _HDR_INFO_EOTF_SMPTE_ST_2084)
        {
            SET_HDR10_MAX_LV_SETTING(UserCommonHDRGetHDR10LvType());
        }

        return _HDR10_INFO_EOTF_CHANGE;
    }

    if((GET_HDR10_EOTF_SETTING() == _HDR_INFO_EOTF_SMPTE_ST_2084) &&
       (GET_HDR10_MAX_LV_SETTING() != (UserCommonHDRGetHDR10LvType())))
    {
        SET_HDR10_MAX_LV_SETTING(UserCommonHDRGetHDR10LvType());
        return _HDR10_INFO_MAX_LV_CHANGE;
    }

    return _HDR10_INFO_NO_CHANGE;
}

//--------------------------------------------------
// Description  : Return HDR Max Mastering Lv Type by infoframe mastering Lv
// Input Value  : EnumDisplayRegion
// Output Value : HDR max mastering Lv type
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserCommonHDRGetHDR10LvType(void)
{
    BYTE pucTemp[4];
    WORD usHDR10MaxMasteringLvNoTMUB = 0x0000;
    memset(pucTemp, 0, sizeof(pucTemp));

    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_NOTM_BOUND_ADDRESS), 4, pucTemp);
    usHDR10MaxMasteringLvNoTMUB = ((WORD)pucTemp[2] << 8) + pucTemp[3];

    if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) > 0)
    {
        if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) <= usHDR10MaxMasteringLvNoTMUB)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_NOTM;
        }
        else if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) <= _HDR10_MAX_MASTERING_LV_540)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_540;
        }
        else if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) <= _HDR10_MAX_MASTERING_LV_1200)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_1200;
        }
        else if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) <= _HDR10_MAX_MASTERING_LV_4000)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_4000;
        }
        else
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_10000;
        }
    }
    else
    {
        return UserCommonHDRGetHDR10ModifyLvType(UserInterfaceHDRGetHDR10MaxMasteringLv0Type(), usHDR10MaxMasteringLvNoTMUB);
    }

    return _HDR10_MAX_MASTERING_LV_TYPE_1200;
}

//--------------------------------------------------
// Description  : Protect User-assigned Mastering Lv Type from being lower than Panel Max Lv
// Input Value  : None
// Output Value : EnumHDR10MaxMasteringLvType
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserCommonHDRGetHDR10ModifyLvType(EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType, WORD usMaxPanelLv)
{
    WORD usMateringLv = _HDR10_MAX_MASTERING_LV_540;

    if(enumHDR10MaxMasteringLvType != _HDR10_MAX_MASTERING_LV_TYPE_NOTM)
    {
        switch(enumHDR10MaxMasteringLvType)
        {
            case _HDR10_MAX_MASTERING_LV_TYPE_540:
                usMateringLv = _HDR10_MAX_MASTERING_LV_540;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                usMateringLv = _HDR10_MAX_MASTERING_LV_1200;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                usMateringLv = _HDR10_MAX_MASTERING_LV_4000;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                usMateringLv = _HDR10_MAX_MASTERING_LV_10000;
                break;

            default:
                break;
        }

        if(usMateringLv <= usMaxPanelLv)
        {
            return _HDR10_MAX_MASTERING_LV_TYPE_NOTM;
        }
        else
        {
            return enumHDR10MaxMasteringLvType;
        }
    }

    return _HDR10_MAX_MASTERING_LV_TYPE_NOTM;
}

//--------------------------------------------------
// Description  : Adjust HDR by enumDisplayRegion
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonHDRAdjustHDR10AutoMode(void)
{
    WORD usHDRInputGammaFlashAddress = 0x0000;
    StructHDR10Table stHDR10Table;
    memset(&stHDR10Table, 0, sizeof(StructHDR10Table));
    UserInterfaceHDRGetHDR10UserAssignTable(&stHDR10Table);

    if(stHDR10Table.enumHDR10UserAssignTableStatus == _HDR10_USER_ASSIGNED_TABLE_OFF)
    {
        // Input Gamma Setting
#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
        EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus = UserInterfaceHDRGetHDR10FixedPointTMStatus();
#else
        EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus = _HDR10_FIXED_POINT_TM_OFF;
#endif
        switch(UserCommonHDRGetHDR10LvType())
        {
            case _HDR10_MAX_MASTERING_LV_TYPE_1200:

                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_1200_NOR_ADDRESS));
                DebugMessageHDR("HDR apply type 1200 parameter", 0x00);

                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_4000:

                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_4000_NOR_ADDRESS));
                DebugMessageHDR("HDR apply type 4000 parameter", 0x00);

                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_10000:

                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_10000_NOR_ADDRESS));
                DebugMessageHDR("HDR apply type 10000 parameter", 0x00);

                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_540:

                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_540_NOR_ADDRESS));
                DebugMessageHDR("HDR apply type 540 parameter", 0x00);

                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_NOTM:

                usHDRInputGammaFlashAddress = _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS;
                DebugMessageHDR("HDR10 apply type no tone mapping parameter", 0x00);

                break;

            default:

                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_1200_NOR_ADDRESS));
                DebugMessageHDR("HDR apply type 1200 parameter default", 0x00);

                break;
        }

        if(UserInterfaceHDRGetHDR10DarkEnhanceStatus() == _HDR10_DARK_ENHANCE_ON)
        {
            usHDRInputGammaFlashAddress += _OGC_HDR10_IG_TABLE_SIZE;
            DebugMessageHDR("HDR apply Dark Enhance parameter", 0x00);
        }

#if((_LOCAL_DIMMING_SUPPORT == _ON) && (_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1))
        if((UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE) && (UserCommonHDRGetHDR10LvType() == _HDR10_MAX_MASTERING_LV_TYPE_NOTM))
        {
            usHDRInputGammaFlashAddress = _OGC_HDR10_IG_NOTM_DISPLAY_HDR_1_1_ADDRESS;
        }
#endif

        stHDR10Table.pucIGTable = g_pucDISP_CALIBRATION_FLASH + usHDRInputGammaFlashAddress;

        // Color Matrix Setting
        stHDR10Table.pucSRGBMatrix = g_pucDISP_CALIBRATION_FLASH + UserCommonHDRGetHDR10ColorMatrix();

        // OutputGamma Setting
        stHDR10Table.pucOGTable = g_pucDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS;

        stHDR10Table.ucBank = _OGC_FLASH_BANK;
    }
    else // User Assign HDR10 PCM Table
    {
        DebugMessageHDR("HDR apply User Assigned PCM Table!!", 0x00);
    }

    UserCommonAdjustPCM(_PCM_HDR_2084, stHDR10Table.pucIGTable, stHDR10Table.pucOGTable, stHDR10Table.pucSRGBMatrix, stHDR10Table.ucBank, _OCC_COLORMATRIX_TABLE_SIZE);
}

//--------------------------------------------------
// Description  : Adjust HDR 2084 force mode
// Input Value  : EnumSelRegion, EnumHDR10MaxMasteringLvType, EnumHDR10ColorMatrix
// Output Value : None
//--------------------------------------------------
void UserCommonHDRAdjustHDR10ForceMode(EnumHDR10MaxMasteringLvType enumHDR10MaxMasteringLvType, EnumHDR10ColorMatrix enumHDR10ColorMatrix)
{
    WORD usHDRInputGammaFlashAddress = 0x0000;
    WORD usHDRColorMatrixFlashAddress = 0x0000;
    StructHDR10Table stHDR10Table;
    memset(&stHDR10Table, 0, sizeof(StructHDR10Table));
    UserInterfaceHDRGetHDR10UserAssignTable(&stHDR10Table);

    if(stHDR10Table.enumHDR10UserAssignTableStatus == _HDR10_USER_ASSIGNED_TABLE_OFF)
    {
#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
        EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus = UserInterfaceHDRGetHDR10FixedPointTMStatus();
#else
        EnumHDR10FixedPointToneMappingStatus enumHDR10FixedPointToneMappingStatus = _HDR10_FIXED_POINT_TM_OFF;
#endif

        switch(enumHDR10MaxMasteringLvType)
        {
            case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_1200_NOR_ADDRESS));
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_4000_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_4000_NOR_ADDRESS));
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_10000_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_10000_NOR_ADDRESS));
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_540:
                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_540_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_540_NOR_ADDRESS));
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_NOTM:
                usHDRInputGammaFlashAddress = _OGC_HDR10_IG_NOTM_PEAK_NOR_ADDRESS;
                break;

            default:
                usHDRInputGammaFlashAddress = ((enumHDR10FixedPointToneMappingStatus == _HDR10_FIXED_POINT_TM_ON) ? (_OGC_HDR10_IG_1200_FIXED_POINT_NOR_ADDRESS) : (_OGC_HDR10_IG_1200_NOR_ADDRESS));
                break;
        }

        if(UserInterfaceHDRGetHDR10DarkEnhanceStatus() == _HDR10_DARK_ENHANCE_ON)
        {
            usHDRInputGammaFlashAddress += _OGC_HDR10_IG_TABLE_SIZE;
        }

#if((_LOCAL_DIMMING_SUPPORT == _ON) && (_DISPLAY_HDR_VERSION == _DISPLAY_HDR_VERSION_1_1))
        if((UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE) && (enumHDR10MaxMasteringLvType == _HDR10_MAX_MASTERING_LV_TYPE_NOTM))
        {
            usHDRInputGammaFlashAddress = _OGC_HDR10_IG_NOTM_DISPLAY_HDR_1_1_ADDRESS;
        }
#endif

        stHDR10Table.pucIGTable = g_pucDISP_CALIBRATION_FLASH + usHDRInputGammaFlashAddress;

        // Color Matrix Setting
        switch(enumHDR10ColorMatrix)
        {
            case _HDR10_COLOR_MATRIX_SRGB:
                usHDRColorMatrixFlashAddress = _OCC_HDR10_SRGB_MATRIX_ADDRESS;
                break;

            case _HDR10_COLOR_MATRIX_ADOBE:
                usHDRColorMatrixFlashAddress = _OCC_HDR10_ADOBE_MATRIX_ADDRESS;
                break;

            case _HDR10_COLOR_MATRIX_DCIP3_D65:
                usHDRColorMatrixFlashAddress = _OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS;
                break;

            case _HDR10_COLOR_MATRIX_BT2020:
                usHDRColorMatrixFlashAddress = _OCC_HDR10_BT2020_MATRIX_ADDRESS;
                break;

            default:
                usHDRColorMatrixFlashAddress = _OCC_HDR10_BT2020_MATRIX_ADDRESS;
                break;
        }

        stHDR10Table.pucSRGBMatrix = g_pucDISP_CALIBRATION_FLASH + usHDRColorMatrixFlashAddress;

        // OutputGamma Setting
        stHDR10Table.pucOGTable = g_pucDISP_CALIBRATION_FLASH + _OCC_HDR10_GAMMA10_ADDRESS;

        stHDR10Table.ucBank = _OGC_FLASH_BANK;
    }
    else
    {
        DebugMessageHDR("HDR apply User Assigned PCM Table!!", 0x00);
    }

    UserCommonAdjustPCM(_PCM_HDR_2084, stHDR10Table.pucIGTable, stHDR10Table.pucOGTable, stHDR10Table.pucSRGBMatrix, stHDR10Table.ucBank, _OCC_COLORMATRIX_TABLE_SIZE);
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHDRAdjustHDR10Proc(void)
{
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) && (_RGB_QUANTIZATION_DEFAULT_RANGE_JUDGE_BY_USER == _ON))
    if(ScalerColorGetColorSpaceRGB(UserCommonInterfaceGetColorFormat()) == _TRUE)
    {
        UserCommonAdjustRGBQuantizationRange();

        SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);
    }
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
    UserInterfaceAdjustUltraVividProc(_DB_APPLY_NO_POLLING);
#endif

    UserCommonHDRAdjustHDR10ColorEffect();
    UserInterfaceHDRAdjustHDR10Proc();
}

//--------------------------------------------------
// Description  : Get HDR10 Color Matrix Flash Address
// Input Value  : void
// Output Value : ColorMatrixFlashAddress
//--------------------------------------------------
WORD UserCommonHDRGetHDR10ColorMatrix(void)
{
    WORD usHDRColorMatrixFlashAddress = 0x0000;
    switch(ScalerColorGetColorimetry())
    {
        case _COLORIMETRY_RGB_SRGB:
        case _COLORIMETRY_RGB_XRRGB:
        case _COLORIMETRY_RGB_SCRGB:
        case _COLORIMETRY_YCC_SMPTE_170M:
        case _COLORIMETRY_YCC_ITUR_BT601:
        case _COLORIMETRY_YCC_ITUR_BT709:
        case _COLORIMETRY_YCC_XVYCC601:
        case _COLORIMETRY_YCC_XVYCC709:

            usHDRColorMatrixFlashAddress = _OCC_HDR10_SRGB_MATRIX_ADDRESS;
            DebugMessageHDR("HDR apply SRGB matrix", 0x00);

            break;

        case _COLORIMETRY_RGB_ADOBERGB:

            usHDRColorMatrixFlashAddress = _OCC_HDR10_ADOBE_MATRIX_ADDRESS;
            DebugMessageHDR("HDR apply AdobeRGB matrix", 0x00);

            break;

        case _COLORIMETRY_RGB_DCI_P3:

            usHDRColorMatrixFlashAddress = _OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS;
            DebugMessageHDR("HDR apply DCIP3_D65 matrix", 0x00);

            break;

        case _COLORIMETRY_EXT:

            switch(ScalerColorGetExtColorimetry())
            {
                case _COLORIMETRY_EXT_RGB_SRGB:
                case _COLORIMETRY_EXT_RGB_XRRGB:
                case _COLORIMETRY_EXT_RGB_SCRGB:
                case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                case _COLORIMETRY_EXT_YCC_XVYCC601:
                case _COLORIMETRY_EXT_YCC_XVYCC709:
                case _COLORIMETRY_EXT_YCC_SYCC601:

                    usHDRColorMatrixFlashAddress = _OCC_HDR10_SRGB_MATRIX_ADDRESS;
                    DebugMessageHDR("HDR apply SRGB matrix EXT", 0x00);

                    break;

                case _COLORIMETRY_EXT_RGB_ADOBERGB:
                case _COLORIMETRY_EXT_YCC_ADOBEYCC601:

                    usHDRColorMatrixFlashAddress = _OCC_HDR10_ADOBE_MATRIX_ADDRESS;
                    DebugMessageHDR("HDR apply AdobeRGB matrix EXT", 0x00);

                    break;

                case _COLORIMETRY_EXT_RGB_DCI_P3:

                    usHDRColorMatrixFlashAddress = _OCC_HDR10_DCIP3_D65_MATRIX_ADDRESS;
                    DebugMessageHDR("HDR apply DCIP3_D65 matrix EXT", 0x00);

                    break;

#if(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2)
                case _COLORIMETRY_EXT_RGB_ITUR_BT2020:
                case _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL:
                case _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL:

                    usHDRColorMatrixFlashAddress = _OCC_HDR10_BT2020_MATRIX_ADDRESS;
                    DebugMessageHDR("HDR apply BT2020 matrix", 0x00);

                    break;
#endif
                default:

                    usHDRColorMatrixFlashAddress = _OCC_HDR10_BT2020_MATRIX_ADDRESS;
                    DebugMessageHDR("HDR apply BT2020 matrix EXT default", 0x00);

                    break;
            }

            break;

        default:

            usHDRColorMatrixFlashAddress = _OCC_HDR10_BT2020_MATRIX_ADDRESS;
            DebugMessageHDR("HDR apply BT2020 matrix default", 0x00);

            break;
    }

    return usHDRColorMatrixFlashAddress;
}

//--------------------------------------------------
// Description  : HDR Support Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHDR10SupportSwitch(void)
{
#if(((_D0_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
    ScalerColorHDR10SupportSwitch(_D0_INPUT_PORT, UserInterfaceHDRGetHDR10ModeStatus(_D0_INPUT_PORT));
#endif

#if(((_D1_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
    ScalerColorHDR10SupportSwitch(_D1_INPUT_PORT, UserInterfaceHDRGetHDR10ModeStatus(_D1_INPUT_PORT));
#endif

#if(((_D2_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_HDR10_SUPPORT == _ON)))
    ScalerColorHDR10SupportSwitch(_D2_INPUT_PORT, UserInterfaceHDRGetHDR10ModeStatus(_D2_INPUT_PORT));
#endif

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    ScalerColorHDR10SupportSwitch(_D3_INPUT_PORT, UserInterfaceHDRGetHDR10ModeStatus(_D3_INPUT_PORT));
#endif

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    ScalerColorHDR10SupportSwitch(_D4_INPUT_PORT, UserInterfaceHDRGetHDR10ModeStatus(_D4_INPUT_PORT));
#endif

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_HDR10_SUPPORT == _ON))
    ScalerColorHDR10SupportSwitch(_D5_INPUT_PORT, UserInterfaceHDRGetHDR10ModeStatus(_D5_INPUT_PORT));
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_DP_HDR10_SUPPORT == _ON))
    ScalerColorHDR10SupportSwitch(_D6_INPUT_PORT, UserInterfaceHDRGetHDR10ModeStatus(_D6_INPUT_PORT));
#endif
}

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust HDR10 Color Matrix
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserCommonHDRAdjustHDR10ColorMatrix(void)
{
    WORD usHDRColorMatrixFlashAddress = 0x0000;
    usHDRColorMatrixFlashAddress = UserCommonHDRGetHDR10ColorMatrix();
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorPCMSRGBAdjust(_SRGB_1_BIT_SHIFT_LEFT, (g_pucDISP_CALIBRATION_FLASH + usHDRColorMatrixFlashAddress), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
}
#endif

#if(_CONTRAST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust HDR Contrast
// Input Value  : 0~100 , default value is 0
// Output Value : void
//--------------------------------------------------
void UserCommonHDRAdjustHDR10Contrast(BYTE ucContrast)
{
    WORD pusData[4] = {0};

    pusData[3] = 0x800;

    pusData[0] = (WORD)(((DWORD)pusData[3] * (ucContrast + 200) / 200) > 4095) ? 4095 : (WORD)((DWORD)pusData[3] * (ucContrast + 200) / 200);
    pusData[1] = pusData[0];
    pusData[2] = pusData[0];

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorContrastAdjust(_CONTRAST_COEF_A, pusData);
    ScalerColorContrastEnable(_FUNCTION_ON);
}
#endif

#if(_DCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Return HDR Max Mastering Lv Type for Light Enhance (540/1200/4000/10000/NOTM nit)
// Input Value  : None
// Output Value : HDR Max Mastering Lv Type for Light Enhance (540/1200/4000/10000/NOTM nit)
//--------------------------------------------------
EnumHDR10LightEnhanceMaxMasteringLv UserCommonHDRGetHDR10LvTypeForLightEnhance(void)
{
    BYTE pucTemp[2];
    WORD usHDR10MaxMasteringLvNoTMUB = 0x0000;
    memset(pucTemp, 0, sizeof(pucTemp));

    if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) > 0)
    {
        if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) <= _HDR10_MAX_MASTERING_LV_540)
        {
            return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_540;
        }
        else if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) <= _HDR10_MAX_MASTERING_LV_1200)
        {
            return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_1200;
        }
        else if((g_stHDR10SaticMetadata.usMaxDisplayMasteringLv) <= _HDR10_MAX_MASTERING_LV_4000)
        {
            return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_4000;
        }
        else
        {
            return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_10000;
        }
    }
    else
    {
        ScalerFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR10_NOTM_BOUND_ADDRESS + 2), 2, pucTemp);
        usHDR10MaxMasteringLvNoTMUB = ((WORD)pucTemp[0] << 8) + pucTemp[1];

        switch(UserCommonHDRGetHDR10ModifyLvType(UserInterfaceHDRGetHDR10MaxMasteringLv0Type(), usHDR10MaxMasteringLvNoTMUB))
        {
            case _HDR10_MAX_MASTERING_LV_TYPE_540:
                return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_540;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_1200:
                return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_1200;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_4000:
                return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_4000;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_10000:
                return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_10000;
                break;

            case _HDR10_MAX_MASTERING_LV_TYPE_NOTM:

                if(usHDR10MaxMasteringLvNoTMUB <= _HDR10_MAX_MASTERING_LV_540)
                {
                    return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_540;
                }
                else if(usHDR10MaxMasteringLvNoTMUB <= _HDR10_MAX_MASTERING_LV_1200)
                {
                    return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_1200;
                }
                else if(usHDR10MaxMasteringLvNoTMUB <= _HDR10_MAX_MASTERING_LV_4000)
                {
                    return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_4000;
                }
                else
                {
                    return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_10000;
                }
                break;

            default:
                return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_540;
                break;
        }
    }

    return _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_1200;
}
#endif

//--------------------------------------------------
// Description  : Integrate HDR10 Light Enhance, HDR10 Color Enhance and ColorEffect Mode FW Flow
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserCommonHDRAdjustHDR10ColorEffect(void)
{
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        // In the process of color function off, for being effective simultaneously, the order should be ICM -> IAPS -> DCC.
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_ICM_SUPPORT == _ON)
        ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
        ScalerColorIAPSGainEnable(_FUNCTION_OFF);
#endif

#if(_DCC_FUNCTION == _ON)
        ScalerColorDCCEnable(_FUNCTION_OFF);
#endif

#if(_ICM_SUPPORT == _ON)
        ScalerColorICMLoadTable(UserInterfaceHDRGetHDR10ICMTable(), UserInterfaceHDRGetHDR10ICMTableBank());
#endif

#if(_DCC_FUNCTION == _ON)
        ScalerColorDCCAdjust(UserInterfaceHDRGetHDR10DCCTable(UserCommonHDRGetHDR10LvTypeForLightEnhance()), UserInterfaceHDRGetHDR10DCCTableBank());
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
        if(UserInterfaceHDRGetHDR10LightEnhanceStatus() != _HDR10_LIGHTENHANCE_OFF)
        {
            ScalerColorIAPSGainSoftClampAdjust(0x00);

            switch(UserCommonHDRGetHDR10LvTypeForLightEnhance())
            {
                case _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_540:
                    ScalerColorIAPSGainValueAdjust(_LIGHTENHANCE_IAPSGAIN_540NIT);
                    break;

                case _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_1200:
                    ScalerColorIAPSGainValueAdjust(_LIGHTENHANCE_IAPSGAIN_1200NIT);
                    break;

                case _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_4000:
                    ScalerColorIAPSGainValueAdjust(_LIGHTENHANCE_IAPSGAIN_4000NIT);
                    break;

                case _HDR10_LIGHTENHANCE_MAX_MASTERING_LV_10000:
                    ScalerColorIAPSGainValueAdjust(_LIGHTENHANCE_IAPSGAIN_10000NIT);
                    break;

                default:
                    ScalerColorIAPSGainValueAdjust(_LIGHTENHANCE_IAPSGAIN_540NIT);
                    break;
            }
        }
#endif

        // In the process of color function on, for being effective simultaneously, the order should be ICM -> IAPS -> DCC.
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if(_ICM_SUPPORT == _ON)
        if(UserInterfaceHDRGetHDR10ICMTable() != NULL)
        {
            ScalerColorICMEnable(_FUNCTION_ON);
        }
#endif

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
        if(UserInterfaceHDRGetHDR10LightEnhanceStatus() != _HDR10_LIGHTENHANCE_OFF)
        {
            ScalerColorIAPSGainEnable(_FUNCTION_ON);
        }
#endif

#if(_DCC_FUNCTION == _ON)
        if(UserInterfaceHDRGetHDR10DCCTable(UserCommonHDRGetHDR10LvTypeForLightEnhance()) != NULL)
        {
            ScalerColorDCCEnable(_FUNCTION_ON);
        }
#endif
    }
}
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : return applying Freesync II parameter or PCM parameter
// Input Value  : bit
// Output Value : _ON(Freesync II), _OFF(PCM)
//--------------------------------------------------
bit UserCommonHDRGetFreesynIIStatus(void)
{
    if((UserInterfaceGetFreeSyncEnable(SysSourceGetInputPort()) != _FREESYNC_SUPPORT_OFF) && (GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING() == _ON))
    {
        return _ON;
    }
    else
    {
        return _OFF;
    }
}
//--------------------------------------------------
// Description  : Check AMD HDR change status
// Input Value  : EnumSourceSearchPort
// Output Value : HDR chagne status
//--------------------------------------------------
BYTE UserCommonHDRFreeSyncIIChangeStatus(void)
{
    BYTE ucFreeSyncIIChangeStatus = _FREESYNC_II_INFO_NO_CHANGE;

    if(GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING() != (g_stFreeSyncIIMetadata.b1NativeColorSpaceEnable))
    {
        SET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING(g_stFreeSyncIIMetadata.b1NativeColorSpaceEnable);
        ucFreeSyncIIChangeStatus |= _FREESYNC_II_COLOR_SPACE_CHANGE;
    }

    if(GET_FREESYNC_II_COLOR_SPACE_ENABLE_SETTING() == _ON)
    {
        if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING() != (g_stFreeSyncIIMetadata.b1BacklightControlEnable))
        {
            SET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING(g_stFreeSyncIIMetadata.b1BacklightControlEnable);
            ucFreeSyncIIChangeStatus |= _FREESYNC_II_BACKLIGHT_CONTROL_CHANGE;
        }

        if(GET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING() != (g_stFreeSyncIIMetadata.b1LocalDimmingDisable))
        {
            SET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING(g_stFreeSyncIIMetadata.b1LocalDimmingDisable);
            ucFreeSyncIIChangeStatus |= _FREESYNC_II_LOCAL_DIMMING_CHANGE;
        }

        if(GET_FREESYNC_II_EOTF_TYPE_SETTING() != (g_stFreeSyncIIMetadata.b5EOTFType))
        {
            SET_FREESYNC_II_EOTF_TYPE_SETTING(g_stFreeSyncIIMetadata.b5EOTFType);
            ucFreeSyncIIChangeStatus |= _FREESYNC_II_EOTF_TYPE_CHANGE;
        }

        if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING() == _ON)
        {
            if(GET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING() != (g_stFreeSyncIIMetadata.ucBacklightControlRatio))
            {
                SET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING(g_stFreeSyncIIMetadata.ucBacklightControlRatio);
                ucFreeSyncIIChangeStatus |= _FREESYNC_II_BACKLIGHT_RATIO_CHANGE;
            }
        }
    }

    return ucFreeSyncIIChangeStatus;
}

//--------------------------------------------------
// Description  : Adjust AMD HDR by EOTF Type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHDRFreeSyncIIMode(void)
{
    WORD usFreesyncIIInputGammaFlashAddress = 0x0000;

    // Input Gamma Setting
    switch(GET_FREESYNC_II_EOTF_TYPE_SETTING())
    {
        case _FREESYNC_II_EOTF_SRGB:
            usFreesyncIIInputGammaFlashAddress = _FREESYNC_II_IG_SRGB_ADDRESS;
            break;

        case _FREESYNC_II_EOTF_BT709:
            usFreesyncIIInputGammaFlashAddress = _FREESYNC_II_IG_BT709_ADDRESS;
            break;

        case _FREESYNC_II_EOTF_GAMMA_22:
            usFreesyncIIInputGammaFlashAddress = _FREESYNC_II_IG_GAMMA22_ADDRESS;
            break;

        case _FREESYNC_II_EOTF_GAMMA_26:
            usFreesyncIIInputGammaFlashAddress = _FREESYNC_II_IG_GAMMA26_ADDRESS;
            break;

        case _FREESYNC_II_EOTF_PQ_INTERIM:
            usFreesyncIIInputGammaFlashAddress = _FREESYNC_II_IG_PQINTERIM_ADDRESS;
            break;

        default:
            usFreesyncIIInputGammaFlashAddress = _FREESYNC_II_IG_SRGB_ADDRESS;
            break;
    }

#if(_BRIGHTNESS_SUPPORT == _ON)
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_CONTRAST_SUPPORT == _ON)
    ScalerColorContrastEnable(_FUNCTION_OFF);
#endif

#if(_LOCAL_DIMMING_SUPPORT == _ON)
    if(UserCommonLocalDimmingGetEnableStatus() == _LD_ENABLE)
    {
        ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
    }
#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)

#if(_PCM_FUNCTION == _ON)
    UserCommonAdjustPCM(_PCM_HDR_2084,
                        (g_pucDISP_FREESYNC_II_CALIBRATION_FLASH + usFreesyncIIInputGammaFlashAddress),
                        (g_pucDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_OCC_GAMMA10_ADDRESS),
                        (g_pucDISP_FREESYNC_II_CALIBRATION_FLASH + _FREESYNC_II_PANEL_NATIVE_MATRIX_ADDRESS),
                        _FREESYNC_II_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
#endif
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonHDRFreeSyncIIProc(void)
{
#if(_FREESYNC_II_GLOBAL_BACKLIGHT_SUPPORT == _ON)
    if(GET_FREESYNC_II_BACKLIGHT_CONTROL_ENABLE_SETTING() == _ON)
    {
        UserInterfaceAdjustBacklight(((DWORD)GET_FREESYNC_II_BACKLIGHT_CONTROL_RATIO_SETTING() * (255 - _PANEL_FREESYNC_II_MIN_BACKLIGHT)) / 100 + _PANEL_FREESYNC_II_MIN_BACKLIGHT);
    }
    else
#endif
    {
        UserInterfaceAdjustBacklight(255);
    }

    UserInterfaceHDRAdjustFreeSyncIIProc();
}

//--------------------------------------------------
// Description  : Get FreeSync II Local Dimming Support Status
// Input Value  : Display Region
// Output Value : Local Dimming Support
//--------------------------------------------------
bit UserCommonHDRGetFreeSyncIILDDisable(void)
{
    return GET_FREESYNC_II_LOCAL_DIMMING_DISABLE_SETTING();
}

//--------------------------------------------------
// Description  : Get FreeSync II EOTF Type
// Input Value  : Display Region
// Output Value : EOTF Type
//--------------------------------------------------
BYTE UserCommonHDRGetFreeSyncIIEOTFType(void)
{
    EnumFreeSyncIIEOTFType enumFreeSyncIIEOTFType = _FREESYNC_II_EOTF_NO_SUPPORT;
    enumFreeSyncIIEOTFType = GET_FREESYNC_II_EOTF_TYPE_SETTING();
    return enumFreeSyncIIEOTFType;
}
#endif // End of #if(_FREESYNC_II_SUPPORT == _ON)

#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)
