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
// ID Code      : BeaconUserInterfaceLocalDimming.h No.0000
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


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_LOCAL_DIMMING_SUPPORT == _ON)

#ifndef __USER_INTERFACE_LOCAL_DIMMING__
extern EnumLDActionMode UserInterfaceGetLocaldimmingActionMode(void);
extern EnumLDStatus UserInterfaceGetLocalDimmingStatus(void);
extern BYTE UserInterfaceGetLocalDimmingPWMSmoothLevel(void);
extern void UserInterfaceLocalDimmingAdjustPCM(void);
extern EnumLDStatus UserInterfaceGetLocalDimmingNoSupportStatus(void);
extern EnumLDPCHDRMode UserInterfaceGetPCHDRVerifyMode(void);

#if(_UNIFORMITY_SUPPORT == _ON)
extern EnumUniformityStatus UserInterfaceGetUniformityStatus(void);
#endif

#if(_LD_TUNNEL_DETECT_SUPPORT == _ON)
extern void UserInterfaceTunnelPatternDetectOff(void);
#endif

#endif // End of __USER_INTERFACE_LOCAL_DIMMING__

#endif // End of #if(_LOCAL_DIMMING_SUPPORT == _ON)