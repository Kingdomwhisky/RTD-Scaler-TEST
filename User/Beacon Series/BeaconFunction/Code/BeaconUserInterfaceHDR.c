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
// ID Code      : BeaconUserInterfaceHDR.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_HDR__

#include "UserCommonInclude.h"

#if(_ULTRA_HDR_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


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
void UserInterfaceHDRAdjustSDRProc(void);

#if(_HDR10_SUPPORT == _ON)
EnumHDR10ModeDef UserInterfaceHDRGetHDR10ModeStatus(EnumSourceSearchPort enumSourcePort);
void UserInterfaceHDRAdjustHDR10Proc(void);
EnumHDR10MaxMasteringLvType UserInterfaceHDRGetHDR10ForceModeMaxMasteringLv(void);
EnumHDR10ColorMatrix UserInterfaceHDRGetHDR10ForceModeColorMatrix(void);
EnumHDR10MaxMasteringLvType UserInterfaceHDRGetHDR10MaxMasteringLv0Type(void);
EnumHDR10DarkEnhanceStatus UserInterfaceHDRGetHDR10DarkEnhanceStatus(void);

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
EnumHDR10LightEnhanceStatus UserInterfaceHDRGetHDR10LightEnhanceStatus(void);
#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
BYTE UserInterfaceHDRGetHDR10LightEnhanceGain(void);
#endif
#endif

#if(_DCC_FUNCTION == _ON)
BYTE UserInterfaceHDRGetHDR10DCCTableBank(void);
code BYTE *UserInterfaceHDRGetHDR10DCCTable(EnumHDR10LightEnhanceMaxMasteringLv enumHDR10LightEnhanceMaxMasteringLv);
#endif

#if(_ICM_SUPPORT == _ON)
BYTE UserInterfaceHDRGetHDR10ICMTableBank(void);
code BYTE *UserInterfaceHDRGetHDR10ICMTable(void);
#endif

#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
EnumHDR10FixedPointToneMappingStatus UserInterfaceHDRGetHDR10FixedPointTMStatus(void);
#endif

extern void UserInterfaceHDRGetHDR10UserAssignTable(StructHDR10Table *pstHDR10Table);
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
void UserInterfaceHDRAdjustFreeSyncIIProc(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust HDR to SDR flow
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserInterfaceHDRAdjustSDRProc(void)
{
#if(_SDR_TO_HDR_SUPPORT == _ON)
    if(GET_OSD_SDR_TO_HDR() == _ON)
    {
        UserAdjustSDRToHDR(_ON);
    }
    else
#endif
    {
#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON))
        UserAdjustColorEffectMode();
#endif
        OsdFuncColorPcmAdjust();
    }
    UserAdjustBacklight(GET_OSD_BACKLIGHT());
}

#if(_HDR10_SUPPORT == _ON)
//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumHDR10ModeDef UserInterfaceHDRGetHDR10ModeStatus(EnumSourceSearchPort enumSourcePort)
{
    enumSourcePort = enumSourcePort;

    if(GET_OSD_HDR_MODE() == _HDR10_MODE_OFF)
    {
        // HDR always OFF
        return _HDR10_MODE_OFF;
    }
    else if(GET_OSD_HDR_MODE() == _HDR10_MODE_AUTO)
    {
        // HDR Check Data
        return _HDR10_MODE_AUTO;
    }
    else if(GET_OSD_HDR_MODE() == _HDR10_MODE_FORCE_2084)
    {
        // HDR always ON
        return _HDR10_MODE_FORCE_2084;
    }

    return _HDR10_MODE_OFF;
}

//--------------------------------------------------
// Description  : Adjust SDR to HDR flow
// Input Value  : void
// Output Value : None
//--------------------------------------------------
void UserInterfaceHDRAdjustHDR10Proc(void)
{
#if(_CONTRAST_SUPPORT == _ON)
    UserCommonHDRAdjustHDR10Contrast(GET_OSD_HDR_CONTRAST());
#endif
    UserAdjustBacklight(_BACKLIGHT_MAX);
}

//--------------------------------------------------
// Description  : Get HDR10 Force Mode - Max Mastering Lv Type
// Input Value  : None
// Output Value : EnumHDR10MaxMasteringLvType
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserInterfaceHDRGetHDR10ForceModeMaxMasteringLv(void)
{
    return _HDR10_MAX_MASTERING_LV_TYPE_1200;
}


//--------------------------------------------------
// Description  : Get HDR10 Force Mode - Color Matrix
// Input Value  : None
// Output Value : EnumHDR10ColorMatrix
//--------------------------------------------------
EnumHDR10ColorMatrix UserInterfaceHDRGetHDR10ForceModeColorMatrix(void)
{
    return _HDR10_COLOR_MATRIX_BT2020;
}

//--------------------------------------------------
// Description  : Get HDR10 Max Mastering Lv 0 - Max Mastering Lv Type
// Input Value  : None
// Output Value : EnumHDR10MaxMasteringLvType
//--------------------------------------------------
EnumHDR10MaxMasteringLvType UserInterfaceHDRGetHDR10MaxMasteringLv0Type(void)
{
    return _HDR10_MAX_MASTERING_LV_TYPE_540;
}

//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumHDR10DarkEnhanceStatus UserInterfaceHDRGetHDR10DarkEnhanceStatus(void)
{
    if(GET_OSD_DARK_ENHANCE_STATUS()== _ON)
    {
        return _HDR10_DARK_ENHANCE_ON;
    }
    else
    {
        return _HDR10_DARK_ENHANCE_OFF;
    }
}

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR10 Light Enhance Status
// Input Value  : None
// Output Value : EnumHDR10LightEnhanceStatus
//--------------------------------------------------
EnumHDR10LightEnhanceStatus UserInterfaceHDRGetHDR10LightEnhanceStatus(void)
{
    if(GET_OSD_HDR_LIGHT_ENHANCE() != _HDR10_LIGHTENHANCE_NONE)
    {
        return _HDR10_LIGHTENHANCE_ON;
    }
    else
    {
        return _HDR10_LIGHTENHANCE_OFF;
    }
}

#if(_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR10 Light Enhance Gain Value, user should return value corresponded to Light Enhance table used.
// Input Value  : None
// Output Value : HDR10 Light Enhance Gain Value / 100, e.g. return 160 when actual gain value is 1.60, and Gain Value range should be 100 ~ 160!!
//--------------------------------------------------
BYTE UserInterfaceHDRGetHDR10LightEnhanceGain(void)
{
    if(UserCommonHDRGetHDR10Status() == _HDR10_ON)
    {
        switch(GET_OSD_HDR_LIGHT_ENHANCE())
        {
            default:
            case _HDR10_LIGHTENHANCE_NONE:
                return 100;

            case _HDR10_LIGHTENHANCE_TYPE_120:
                return 120;

            case _HDR10_LIGHTENHANCE_TYPE_140:
                return 140;

            case _HDR10_LIGHTENHANCE_TYPE_160:
                return 160;
        }
    }

    return 100;
}
#endif
#endif

#if(_DCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Get HDR10 DCC Table Bnak
// Input Value  : None
// Output Value : HDR10 DCC table bank
//--------------------------------------------------
BYTE UserInterfaceHDRGetHDR10DCCTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

//--------------------------------------------------
// Description  : Get HDR10 DCC Table Address
// Input Value  : Max MasteringLv Type --> 540 / 1200 / 4000 / 10000 nit
// Output Value : HDR10 DCC table address
//--------------------------------------------------
code BYTE *UserInterfaceHDRGetHDR10DCCTable(EnumHDR10LightEnhanceMaxMasteringLv enumHDR10LightEnhanceMaxMasteringLv)
{
    enumHDR10LightEnhanceMaxMasteringLv = enumHDR10LightEnhanceMaxMasteringLv;

#if(_HDR10_LIGHT_ENHANCE_SUPPORT == _ON)
    switch((EnumHDR10LightEnhanceType)GET_OSD_HDR_LIGHT_ENHANCE())
    {
        case _HDR10_LIGHTENHANCE_NONE:
            break;

        case _HDR10_LIGHTENHANCE_TYPE_120:
            return tDCC_LIGHTENHANCE_120_TABLE[enumHDR10LightEnhanceMaxMasteringLv];

        case _HDR10_LIGHTENHANCE_TYPE_140:
            return tDCC_LIGHTENHANCE_140_TABLE[enumHDR10LightEnhanceMaxMasteringLv];

        case _HDR10_LIGHTENHANCE_TYPE_160:
            return tDCC_LIGHTENHANCE_160_TABLE[enumHDR10LightEnhanceMaxMasteringLv];

        default:
            return tDCC_LIGHTENHANCE_120_TABLE[enumHDR10LightEnhanceMaxMasteringLv];
    }
#endif

    if(GET_OSD_COLOR_EFFECT() != _COLOREFFECT_USER)
    {
        return tDCC_HDR10_TABLE[GET_OSD_COLOR_EFFECT()];
    }

    return tDCC_HDR10_TABLE[0];
}
#endif

#if(_ICM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR10 ICM Table Bnak
// Input Value  : None
// Output Value : HDR10 ICM table bank
//--------------------------------------------------
BYTE UserInterfaceHDRGetHDR10ICMTableBank(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

//--------------------------------------------------
// Description  : Get HDR10 ICM Table Address
// Input Value  : None
// Output Value : HDR10 ICM table address
//--------------------------------------------------
code BYTE *UserInterfaceHDRGetHDR10ICMTable(void)
{
#if(_HDR10_COLOR_ENHANCE_SUPPORT == _ON)
    EnumHDR10ColorEnhanceType enumHDR10ColorEnhanceType = GET_OSD_HDR_COLOR_ENHANCE();

    if(enumHDR10ColorEnhanceType != _HDR10_COLORENHANCE_OFF)
    {
        switch(enumHDR10ColorEnhanceType)
        {
            case _HDR10_COLORENHANCE_TYPE_1:
                return tICM_COLORENHANCE_TABLE[0];
                break;

            case _HDR10_COLORENHANCE_TYPE_2:
                return tICM_COLORENHANCE_TABLE[1];
                break;

            case _HDR10_COLORENHANCE_TYPE_3:
                return tICM_COLORENHANCE_TABLE[2];
                break;

            default:
                return tICM_COLORENHANCE_TABLE[0];
                break;
        }
    }
#endif
    if(GET_OSD_COLOR_EFFECT() != _COLOREFFECT_USER)
    {
        return tICM_HDR10_TABLE[GET_OSD_COLOR_EFFECT()];
    }
    else
    {
        return tICM_HDR10_TABLE[0];
    }
}
#endif

#if(_HDR10_FIXED_POINT_TONEMAPPING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get HDR10 Fixed Point Tone Mapping Status
// Input Value  : None
// Output Value : EnumHDR10FixedPointToneMappingStatus
//--------------------------------------------------
EnumHDR10FixedPointToneMappingStatus UserInterfaceHDRGetHDR10FixedPointTMStatus(void)
{
    return _HDR10_FIXED_POINT_TM_OFF;
}
#endif

//--------------------------------------------------
// Description  : Get HDR10 User assigned PCM Table Status. If status is on, please assigned PCM table addr & bank;
// Input Value  : None
// Output Value : StructHDR10UserAssignTable
//--------------------------------------------------
void UserInterfaceHDRGetHDR10UserAssignTable(StructHDR10Table *pstHDR10Table)
{
    pstHDR10Table->enumHDR10UserAssignTableStatus = _HDR10_USER_ASSIGNED_TABLE_OFF;
}
#endif // End of #if(_HDR10_SUPPORT == _ON)

#if(_FREESYNC_II_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust SDR to FreeSync II flow
// Input Value  : void
// Output Value : None
//--------------------------------------------------
void UserInterfaceHDRAdjustFreeSyncIIProc(void)
{
}
#endif // End of #if(_FREESYNC_II_SUPPORT == _ON)
#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)

