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
// ID Code      : BeaconUserInterfaceLocalDimming.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_GLOBAL_DIMMING__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _BEACON_OSD) && (_GLOBAL_DIMMING_SUPPORT == _ON))

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
void UserInterfaceGlobalDimmingAdjustPWM(WORD usPWMValue);
void UserInterfaceGlobalDimmingAdjustPCM(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : 0~ 2048
// Output Value :
//--------------------------------------------------
void UserInterfaceGlobalDimmingAdjustPWM(WORD usPWMValue)
{
    WORD usNormPWM = 0;
#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
    usNormPWM = ((DWORD)usPWMValue * _DEVICE_LED_DRIVER_PWM_MAX) / _GD_PANEL_PWM_MAX;
    ExternalDeviceInterfaceLedDriverPwm(_PANEL_PWM_LOCAL_ALL, usNormPWM, _DEVICE_CALI_OFF);
#else
    usNormPWM = ((DWORD)usPWMValue * _BACKLIGHT_MAX) / _GD_PANEL_PWM_MAX;
    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(usNormPWM);
#endif
}

//--------------------------------------------------
// Description  : Adjust PCM in Global Dimming Mode
// Input Value  : void
// Output Value : void
//--------------------------------------------------
void UserInterfaceGlobalDimmingAdjustPCM(void)
{
#if(_SDR_TO_HDR_SUPPORT == _ON)

    UserAdjustSDRToHDR(GET_OSD_SDR_TO_HDR());

#else

#if(_PCM_FUNCTION == _ON)
    UserAdjustPCM(GET_OSD_PCM_STATUS());
#endif

#endif
}

//--------------------------------------------------
// Description  : Get Global Dimming OSD Status
// Input Value  : void
// Output Value : _GD_ENABLE or _GD_DISABLE
//--------------------------------------------------
EnumGDStatus UserInterfaceGetGlobalDimmingStatus(void)
{
    return _GD_ENABLE;
}
#endif // End of #if((_OSD_TYPE == _BEACON_OSD) && (_Global_DIMMING_SUPPORT == _ON))

