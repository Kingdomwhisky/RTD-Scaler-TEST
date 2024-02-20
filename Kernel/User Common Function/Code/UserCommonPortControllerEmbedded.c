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
// ID Code      : UserCommonPortControllerEmbedded.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLEREMBEDDED__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)

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
#if(_USB3_RETIMER_SUPPORT == _ON)
EnumUSBPSSupportStatus UserCommonPortControllerGetUsbPSStatus(void);
EnumUSBPDSupportStatus UserCommonPortControllerGetUsbPDStatus(void);
#endif
#if(_DP_USB_HUB_SUPPORT == _ON)
EnumHubInputPort UserCommonPortControllerGetHubInputPort(BYTE ucInputPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_USB3_RETIMER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get USB3 Retimer PS Support Status
// Input Value  : void
// Output Value : EnumUSBPDSupportStatus
//--------------------------------------------------
EnumUSBPSSupportStatus UserCommonPortControllerGetUsbPSStatus(void)
{
    // Set USB Power Saving Status for Retimer Power Switch Use
    ScalerUSB3RetimerSetPSStatus(UserInterfaceGetUSBPSSupportStatus());

    return ScalerUSB3RetimerGetPSStatus();
}

//--------------------------------------------------
// Description  : Get USB3 Retimer PS Support Status
// Input Value  : void
// Output Value : EnumUSBPDSupportStatus
//--------------------------------------------------
EnumUSBPDSupportStatus UserCommonPortControllerGetUsbPDStatus(void)
{
    // Set USB Power Off Status for Retimer Power Switch Use
    ScalerUSB3RetimerSetPDStatus(UserInterfaceGetUSBPDSupportStatus());

    return ScalerUSB3RetimerGetPDStatus();
}
#endif

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Return Hub Input Port to Kernel
// Input Value  : ucInputPort
// Output Value : EnumHubInputPort
//--------------------------------------------------
EnumHubInputPort UserCommonPortControllerGetHubInputPort(BYTE ucInputPort)
{
    EnumHubInputPort enumHubInputPort = _HUB_UFP_TYPE_C_INPUT_PORT;

    switch(ucInputPort)
    {
#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
        case _D0_INPUT_PORT:

            enumHubInputPort = UserInterfaceTypeCHubInputPort(_D0_INPUT_PORT);

            break;
#endif

        default:

            break;
    }

    return enumHubInputPort;
}
#endif
#endif // End of #if(_PORT_CONTROLLER_EMBEDDED_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_PORT_CTRL_SUPPORT == _ON)
