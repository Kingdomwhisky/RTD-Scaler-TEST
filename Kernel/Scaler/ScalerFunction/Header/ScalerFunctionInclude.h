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
// ID Code      : ScalerFunctionInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "Global.h"
#include "Project.h"

#include "ScalerFunctionCommonInclude.h"

#include "ScalerCommonFunctionLibInclude.h"
#include "ScalerFunctionLibInclude.h"

#include "ScalerCommonSyncInclude.h"
#include "ScalerSyncInclude.h"

#include "ScalerCommonDPTxInclude.h"
#include "ScalerDPTxInclude.h"

#include "ScalerGDIPhyTxInclude.h"

#include "ScalerDisplayDPTxInclude.h"

#include "ScalerCommonDPRx0Include.h"

#include "ScalerCommonTMDSInclude.h"

#include "ScalerCommonTimerFunctionInclude.h"
#include "ScalerTimerFunctionInclude.h"

#include "ScalerCommonHDCP2Include.h"

#include "ScalerAudioInclude.h"

#include "ScalerDPRx0HDCP2Include.h"
#include "ScalerDPRx1HDCP2Include.h"
#include "ScalerCommonDPRx0HDCP2Include.h"
#include "ScalerCommonDPRx1HDCP2Include.h"
#include "ScalerCommonDPTxHDCP2Include.h"
#include "ScalerCommonFreeSyncInclude.h"

#if(_SCALER_TYPE == _RL6369_SERIES)
#include "RL6369_Series_FunctionInclude.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "ScalerCommonDPRx1Include.h"
#include "RL6410_Series_Common_FunctionInclude.h"
#include "RL6410_Series_FunctionInclude.h"
#elif(_SCALER_TYPE == _RL6432_SERIES)
#include "ScalerCommonDPRx1Include.h"
#include "RL6432_Series_Common_FunctionInclude.h"
#include "RL6432_Series_FunctionInclude.h"
#elif(_SCALER_TYPE == _RL6449_SERIES)
#include "ScalerCommonDPRx1Include.h"
#include "RL6449_Series_Common_FunctionInclude.h"
#include "RL6449_Series_FunctionInclude.h"
#elif(_SCALER_TYPE == _RL6463_SERIES)
#include "RL6463_Series_FunctionInclude.h"
#elif(_SCALER_TYPE == _RL6492_SERIES)
#include "RL6492_Series_Common_FunctionInclude.h"
#include "RL6492_Series_FunctionInclude.h"
#endif

#include "ScalerVGATopInclude.h"
#include "ScalerADCInclude.h"

#include "ScalerAutoFuncInclude.h"

#include "ScalerDisplayInclude.h"
#include "ScalerSDRAMInclude.h"
#include "ScalerDDR1Include.h"
#include "ScalerDDR3Include.h"
#include "ScalerFRCInclude.h"
#include "ScalerMemoryInclude.h"
#include "ScalerODInclude.h"
#include "ScalerOsdInclude.h"

#include "ScalerPinshareInclude.h"

#include "ScalerCommonRegInclude.h"
#include "ScalerRegInclude.h"

#include "ScalerSyncProcInclude.h"

#include "ScalerCommonDebugInclude.h"

#include "ScalerCommonPowerInclude.h"
#include "ScalerPowerInclude.h"

#include "ScalerCommonIOSCInclude.h"

#include "ScalerCommonMcuInclude.h"
#include "ScalerMcuInclude.h"

#include "ScalerGlobalInclude.h"

#include "ScalerCommonMeasureInclude.h"
#include "ScalerMeasureInclude.h"

#include "ScalerIDomainInclude.h"

#include "ScalerMDomainInclude.h"
#include "ScalerDDomainInclude.h"

#include "ScalerCommonPLLInclude.h"
#include "ScalerPLLInclude.h"

#include "ScalerCommonColorInclude.h"
#include "ScalerColorInclude.h"

#include "ScalerCecInclude.h"

#include "ScalerCommonDPRxMSTInclude.h"
#include "ScalerDPRxMSTInclude.h"

#include "ScalerCommonDPTxMSTInclude.h"

#include "ScalerCommonDPTxAuxInclude.h"

#include "ScalerRotationInclude.h"

#include "ScalerDualLinkDVIInclude.h"


#include "ScalerCommonNVRamInclude.h"

#include "ScalerIRInclude.h"

#include "ScalerFormatConversionInclude.h"
#include "ScalerVGIPInclude.h"

#include "ScalerDPRx0Include.h"
#include "ScalerCommonSpiInclude.h"

#include "ScalerCommonTypeCInclude.h"

#include "ScalerMbrInclude.h"

#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES))

#include "ScalerAudio_SeptPhyInclude.h"
#include "ScalerDP_SeptPhyInclude.h"
#include "ScalerDPRx0_SeptPhyInclude.h"
#include "ScalerDPRx0_INT_SeptPhyInclude.h"
#include "ScalerDPRx1_SeptPhyInclude.h"
#include "ScalerDPRx1_INT_SeptPhyInclude.h"
#include "ScalerDPRx1HDCP2_SeptPhyInclude.h"
#include "ScalerMHL3Rx2_SeptPhyInclude.h"
#include "ScalerMHL3Rx3_SeptPhyInclude.h"
#include "ScalerMHLRx2_SeptPhyInclude.h"
#include "ScalerMHLRx3_SeptPhyInclude.h"
#include "ScalerMHLRx4_SeptPhyInclude.h"
#include "ScalerMHLRx5_SeptPhyInclude.h"
#include "ScalerTMDSRx1_SeptPhyInclude.h"
#include "ScalerTMDSRx1HDCP2_SeptPhyInclude.h"
#include "ScalerTMDSRx2_SeptPhyInclude.h"
#include "ScalerTMDSRx2HDCP2_SeptPhyInclude.h"
#include "ScalerTMDSRx3_SeptPhyInclude.h"
#include "ScalerTMDSRx3HDCP2_SeptPhyInclude.h"
#include "ScalerTMDSRx4_SeptPhyInclude.h"
#include "ScalerTMDSRx4HDCP2_SeptPhyInclude.h"
#include "ScalerTMDSRx5_SeptPhyInclude.h"
#include "ScalerTMDSRx5HDCP2_SeptPhyInclude.h"

#elif((_SCALER_TYPE == _RL6369_SERIES) ||\
      (_SCALER_TYPE == _RL6463_SERIES))

#include "ScalerAudio_ComboPhyInclude.h"
#include "ScalerDP_ComboPhyInclude.h"
#include "ScalerDPRx0_INT_ComboPhyInclude.h"
#include "ScalerDPRx0_ComboPhyInclude.h"
#include "ScalerTMDS_ComboPhyInclude.h"

#elif(_SCALER_TYPE == _RL6492_SERIES)

#include "ScalerAudio_ComboPhyInclude.h"
#include "ScalerTMDS_ComboPhyInclude.h"

#endif

#include "ScalerDPRxMST_SeptPhyInclude.h"

#if(_CUSTOMER == _CUS_MINDRAY)
extern StructUserDataInflashType g_stUserDataInFlash; 
#endif

