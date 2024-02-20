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
// ID Code      : RTD2014UserInterDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_DIMMING__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD) && (_BACKLIGHT_DIMMING_SUPPORT == _ON))

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
EnumSDRCalibrationType UserInterfaceSDROCCOGCMode(void);
EnumSDRPCMStatus UserInterfaceGetSDRPCMMode(void);
EnumSDROGCStatus UserInterfaceGetSDROGCMode(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : whether SDR mode calibrated by OCC/OGC
// Input Value  : void
// Output Value : _SDR_CALIBRATION_BY_OGC_TOOL / _SDR_NONE_CALIBRATION_BY_OGC_TOOL,
//--------------------------------------------------
EnumSDRCalibrationType UserInterfaceSDROCCOGCMode(void)
{
    if((GET_OSD_PCM_STATUS() == _PCM_OSD_NATIVE) &&
       (GET_OSD_GAMMA() == _GAMMA_OFF))
    {
        return _SDR_NONE_CALIBRATION_BY_OGC_TOOL;
    }
    else
    {
        return _SDR_CALIBRATION_BY_OGC_TOOL;
    }
}

//--------------------------------------------------
// Description  : which SDR mode calibrated by OCC selected
// Input Value  : void
// Output Value : EnumSDRPCMStatus
//--------------------------------------------------
EnumSDRPCMStatus UserInterfaceGetSDRPCMMode(void)
{
#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS() != _PCM_OSD_NATIVE)
    {
        switch(GET_OSD_PCM_STATUS())
        {
#if(_OCC_SUPPORT == _ON)
            case _PCM_OSD_SRGB:
                return _SDR_SRGB;

            case _PCM_OSD_ADOBE_RGB:
                return _SDR_ADOBE_RGB;
#endif
            default:
                return _SDR_NONE_OCC;
        }
    }
#endif // End of #if(_PCM_FUNCTION == _ON)
    return _SDR_NONE_OCC;
}


//--------------------------------------------------
// Description  : which SDR mode calibrated by OGC be selected
// Input Value  : void
// Output Value : EnumSDROGCStatus
//--------------------------------------------------
EnumSDROGCStatus UserInterfaceGetSDROGCMode(void)
{
    switch(GET_OSD_GAMMA())
    {
#if(_OGC_SUPPORT == _ON)
        case _GAMMA_18:
            return _SDR_OGC_CASE_1;
#if(_OGC_TOTAL_GAMMA > 1)
        case _GAMMA_20:
            return _SDR_OGC_CASE_2;
#if(_OGC_TOTAL_GAMMA > 2)
        case _GAMMA_22:
            return _SDR_OGC_CASE_3;
#if(_OGC_TOTAL_GAMMA > 3)
        case _GAMMA_24:
            return _SDR_OGC_CASE_4;
#endif
#endif
#endif
#endif
        default:
            return _SDR_NONE_OGC;
    }
}

#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD) && (_BACKLIGHT_DIMMING_SUPPORT == _ON))

