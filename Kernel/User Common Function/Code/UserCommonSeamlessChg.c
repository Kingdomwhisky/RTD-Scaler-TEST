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
// ID Code      : UserCommonSeamlessChg.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_SEAMLESS_CHG__

#include "UserCommonInclude.h"

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)

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
StructColorimetrySetting g_stColorimetrySetting;
StructColorimetryUpdate g_stColorimetryUpdate;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonSeamlessChgHandler(void);
void UserCommonSeamlessChgAdjust(EnumSeamlessFlowStatus enumSeamlessFlowStatus);
EnumColorimetryChangeStatus UserCommonSeamlessChgGetChangeStatus(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Seamless Change Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonSeamlessChgHandler(void)
{
    UserCommonSeamlessChgAdjust(_SEAMLESS_PROC_ACTIVE);
}

//--------------------------------------------------
// Description  : Seamless Change Adjust
// Input Value  : EnumDisplayRegion, EnumSeamlessFlowStatus
// Output Value : none
//--------------------------------------------------
void UserCommonSeamlessChgAdjust(EnumSeamlessFlowStatus enumSeamlessFlowStatus)
{
    if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
    {
        return;
    }

    switch(enumSeamlessFlowStatus)
    {
        case _SEAMLESS_BACKUP_SETTING:
        case _SEAMLESS_FLOW_CHANGE:
        default:

            SET_COLORIMETRY_SETTING(ScalerColorGetColorimetry());
            SET_EXT_COLORIMETRY_SETTING(ScalerColorGetExtColorimetry());
            break;

        case _SEAMLESS_PROC_ACTIVE:

            if(UserCommonSeamlessChgGetChangeStatus() == _COLORIMETRY_CHANGE)
            {
                SysModeColorSpaceConvert(UserCommonInterfaceGetColorFormat(), _DB_APPLY_NO_POLLING);

#if(_HDR10_SUPPORT == _ON)
                if(GET_HDR10_UPDATE_COLORIMETRY() == _FALSE)
                {
                    if((UserInterfaceHDRGetHDR10ModeStatus(SysSourceGetInputPort()) == _HDR10_MODE_AUTO) && (GET_HDR10_EOTF_SETTING() == _HDR_INFO_EOTF_SMPTE_ST_2084))
                    {
                        UserCommonHDRAdjustHDR10ColorMatrix();
                        DebugMessageHDR("HDR10 color matrix seamless change ", 0x00);
                    }
                }
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
                if(GET_FREESYNCII_UPDATE_COLORIMETRY() == _FALSE)
                {
                }
#endif

                if(GET_SDR_UPDATE_COLORIMETRY() == _FALSE)
                {
                }
            }

            break;
    }

#if(_HDR10_SUPPORT == _ON)
    CLR_HDR10_UPDATE_COLORIMETRY();
#endif

#if(_FREESYNC_II_SUPPORT == _ON)
    CLR_FREESYNCII_UPDATE_COLORIMETRY();
#endif

    CLR_SDR_UPDATE_COLORIMETRY();
}

//--------------------------------------------------
// Description  : Check Colorimetry change status
// Input Value  : EnumDisplayRegion
// Output Value : Colorimetry chagne status
//--------------------------------------------------
EnumColorimetryChangeStatus UserCommonSeamlessChgGetChangeStatus(void)
{
    if((GET_COLORIMETRY_SETTING() != ScalerColorGetColorimetry()) ||
       (GET_EXT_COLORIMETRY_SETTING() != ScalerColorGetExtColorimetry()))
    {
        SET_COLORIMETRY_SETTING(ScalerColorGetColorimetry());
        SET_EXT_COLORIMETRY_SETTING(ScalerColorGetExtColorimetry());

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            return _COLORIMETRY_CHANGE;
        }
    }

    return _COLORIMETRY_NO_CHANGE;
}
#endif // End of #if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
