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
// ID Code      : RTD2014UserInterfaceLocalDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_LOCAL_DIMMING__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD) && (_LOCAL_DIMMING_SUPPORT == _ON))

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
EnumLDActionMode UserInterfaceGetLocaldimmingActionMode(void);
EnumLDStatus UserInterfaceGetLocalDimmingStatus(void);
BYTE UserInterfaceGetLocalDimmingPWMSmoothLevel(void);
void UserInterfaceLocalDimmingAdjustPCM(void);

EnumLDStatus UserInterfaceGetLocalDimmingNoSupportStatus(void);
EnumLDPCHDRMode UserInterfaceGetPCHDRVerifyMode(void);
#if(_UNIFORMITY_SUPPORT == _ON)
EnumUniformityStatus UserInterfaceGetUniformityStatus(void);
#endif

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
void UserInterfaceTunnelPatternDetectOff(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : System (1P only)
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumLDActionMode UserInterfaceGetLocaldimmingActionMode(void)
{
    if(ScalerOsdGetOsdEnable() == _ON)
    {
        return _LD_ACTION_MODE_NORNAL;
    }

    return _LD_ACTION_MODE_DIMMING;
}

//--------------------------------------------------
// Description  : Get Local Dimming OSD Status
// Input Value  : void
// Output Value : On or OFF
//--------------------------------------------------
EnumLDStatus UserInterfaceGetLocalDimmingStatus(void)
{
    // if sdr don't support local dimming, user should return _LD_DISABLE in sdr case.
    if(GET_OSD_LOCAL_DIMMING() == _ON)
    {
        return _LD_ENABLE;
    }

    return _LD_DISABLE;
}

//--------------------------------------------------
// Description  : Set Led Driver Pwm Frequency
// Input Value  : None
// Output Value : 0 ~ 100
//--------------------------------------------------
BYTE UserInterfaceGetLocalDimmingPWMSmoothLevel(void)
{
    return GET_OSD_LD_ADJ(); // recommend 50 or the value will pass corner pattern
}

//--------------------------------------------------
// Description  : Adjust PCM in Local Dimming Mode
// Input Value  : None
// Output Value : void
//--------------------------------------------------
void UserInterfaceLocalDimmingAdjustPCM(void)
{
#if(_SDR_TO_HDR_SUPPORT == _ON)
    UserAdjustSDRToHDR(GET_OSD_SDR_TO_HDR());
#else
#if(_PCM_FUNCTION == _ON)
    OsdFuncColorPcmAdjust();
#endif
#endif
}

//--------------------------------------------------
// Description  : Local Dimming must support in OGC/OCC
// Input Value  : None
// Output Value : _LD_DISABLE /_LD_ENABLE
//--------------------------------------------------
EnumLDStatus UserInterfaceGetLocalDimmingNoSupportStatus(void)
{
#if(_SDR_TO_HDR_SUPPORT == _ON)
    // SDRtoHDR can support local dimming
    if(GET_OSD_SDR_TO_HDR() == _ON)
    {
        return _LD_DISABLE;
    }
#endif

    // Non OCC/OGC Mode can't supprt local dimming(Ex. user define gamma/ X-rite)
    if(UserInterfaceSDROCCOGCMode() == _SDR_NONE_CALIBRATION_BY_OGC_TOOL)
    {
        return _LD_DISABLE;
    }

    return _LD_ENABLE;
}

//--------------------------------------------------
// Description  : Get PCHDR verify Mode
// Input Value  : None
// Output Value : PCHDR verify mode/ PCHDR normal mode
//--------------------------------------------------
EnumLDPCHDRMode UserInterfaceGetPCHDRVerifyMode(void)
{
    return _LD_PCHDR_NORMAL_MODE;
}

#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get uniformity OSD ON/OFF
// Input Value  : None
// Output Value : _PANEL_UNIFORMITY_ON/ _PANEL_UNIFORMITY_OFF
//--------------------------------------------------
EnumUniformityStatus UserInterfaceGetUniformityStatus(void)
{
    if(GET_OSD_PANEL_UNIFORMITY() == _ON)
    {
        return _PANEL_UNIFORMITY_ON;
    }
    else
    {
        return _PANEL_UNIFORMITY_OFF;
    }
}
#endif

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust All High Light Window Effect Space
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceTunnelPatternDetectOff(void)
{
    // Set previous HLW effect space
    UserAdjustHighLightWindowEffectSpace();
    UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());

#if(_DCR_SUPPORT== _ON)
    // Set previous DCR
    UserAdjustDCRTHD();
#endif
}
#endif // End of #if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD) && (_LOCAL_DIMMING_SUPPORT == _ON))

