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
// ID Code      : ScalerFunctionCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "Global.h"
#include "Scaler_List.h"
#include "Project_List.h"
#include "Debug.h"

#if(_SCALER_TYPE == _RL6369_SERIES)
#include "RL6369_Gen_Option.h"
#include "RL6369_Series_FunctionCommonInclude.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Gen_Option.h"
#include "RL6410_Series_Common_FunctionCommonInclude.h"
#include "RL6410_Series_FunctionCommonInclude.h"
#elif(_SCALER_TYPE == _RL6432_SERIES)
#include "RL6432_Gen_Option.h"
#include "RL6432_Series_Common_FunctionCommonInclude.h"
#include "RL6432_Series_FunctionCommonInclude.h"
#elif(_SCALER_TYPE == _RL6449_SERIES)
#include "RL6449_Gen_Option.h"
#include "RL6449_Series_Common_FunctionCommonInclude.h"
#include "RL6449_Series_FunctionCommonInclude.h"
#elif(_SCALER_TYPE == _RL6463_SERIES)
#include "RL6463_Gen_Option.h"
#include "RL6463_Series_FunctionCommonInclude.h"
#elif(_SCALER_TYPE == _RL6492_SERIES)
#include "RL6492_Gen_Option.h"
#include "RL6492_Series_Common_FunctionCommonInclude.h"
#include "RL6492_Series_FunctionCommonInclude.h"
#endif

#include "ScalerVGATopCommonInclude.h"
#include "ScalerADCCommonInclude.h"

#include "ScalerAutoFuncCommonInclude.h"

#include "ScalerDisplayCommonInclude.h"

#include "ScalerDisplayDPTxCommonInclude.h"

#include "ScalerCommonDPRx0CommonInclude.h"

#include "ScalerCommonDPTxAuxCommonInclude.h"

#include "ScalerFRCCommonInclude.h"
#include "ScalerMemoryCommonInclude.h"
#include "ScalerODCommonInclude.h"
#include "ScalerOsdCommonInclude.h"

#include "ScalerPinshareCommonInclude.h"

#include "ScalerCommonRegCommonInclude.h"
#include "ScalerRegCommonInclude.h"

#include "ScalerSyncProcCommonInclude.h"

#include "ScalerCommonDebugCommonInclude.h"

#include "ScalerCommonPowerCommonInclude.h"
#include "ScalerPowerCommonInclude.h"


#include "ScalerCommonIOSCCommonInclude.h"

#include "ScalerCommonMcuCommonInclude.h"
#include "ScalerMcuCommonInclude.h"

#include "ScalerCommonTimerFunctionCommonInclude.h"
#include "ScalerTimerFunctionCommonInclude.h"

#include "ScalerGlobalCommonInclude.h"

#include "ScalerDDR1CommonInclude.h"
#include "ScalerDDR3CommonInclude.h"
#include "ScalerSDRAMCommonInclude.h"

#include "ScalerCommonSyncCommonInclude.h"
#include "ScalerSyncCommonInclude.h"

#include "ScalerCommonMeasureCommonInclude.h"
#include "ScalerMeasureCommonInclude.h"

#include "ScalerIDomainCommonInclude.h"

#include "ScalerMDomainCommonInclude.h"
#include "ScalerDDomainCommonInclude.h"

#include "ScalerCommonPLLCommonInclude.h"
#include "ScalerPLLCommonInclude.h"

#include "ScalerAudioCommonInclude.h"

#include "ScalerCommonColorCommonInclude.h"
#include "ScalerColorCommonInclude.h"

#include "ScalerCommonDPRxMSTCommonInclude.h"
#include "ScalerDPRxMSTCommonInclude.h"

#include "ScalerCommonDPTxCommonInclude.h"
#include "ScalerDPTxCommonInclude.h"

#include "ScalerCommonDPTxMSTCommonInclude.h"

#include "ScalerGDIPhyTxCommonInclude.h"

#include "ScalerRotationCommonInclude.h"

#include "ScalerDualLinkDVICommonInclude.h"


#include "ScalerCommonNVRamCommonInclude.h"

#include "ScalerIRCommonInclude.h"
#include "ScalerDPRx0HDCP2CommonInclude.h"
#include "ScalerDPRx1HDCP2CommonInclude.h"

#include "ScalerFormatConversionCommonInclude.h"
#include "ScalerVGIPCommonInclude.h"
#include "ScalerDPRx0CommonInclude.h"
#include "ScalerCommonHDCP2CommonInclude.h"
#include "ScalerCommonTMDSCommonInclude.h"

#include "ScalerCommonSpiCommonInclude.h"
#include "ScalerCommonTypeCCommonInclude.h"

#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES))

#include "ScalerAudio_SeptPhyCommonInclude.h"
#include "ScalerDP_SeptPhyCommonInclude.h"
#include "ScalerDPRx0_SeptPhyCommonInclude.h"
#include "ScalerDPRx0_INT_SeptPhyCommonInclude.h"
#include "ScalerDPRx1_SeptPhyCommonInclude.h"
#include "ScalerDPRx1_INT_SeptPhyCommonInclude.h"
#include "ScalerDPRx1HDCP2_SeptPhyCommonInclude.h"
#include "ScalerMHL3Rx2_SeptPhyCommonInclude.h"
#include "ScalerMHL3Rx3_SeptPhyCommonInclude.h"
#include "ScalerMHLRx2_SeptPhyCommonInclude.h"
#include "ScalerMHLRx3_SeptPhyCommonInclude.h"
#include "ScalerMHLRx4_SeptPhyCommonInclude.h"
#include "ScalerMHLRx5_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx1_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx1HDCP2_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx2_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx2HDCP2_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx3_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx3HDCP2_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx4_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx4HDCP2_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx5_SeptPhyCommonInclude.h"
#include "ScalerTMDSRx5HDCP2_SeptPhyCommonInclude.h"
#include "ScalerCommonDPRx1CommonInclude.h"

#elif((_SCALER_TYPE == _RL6369_SERIES) ||\
      (_SCALER_TYPE == _RL6463_SERIES))

#include "ScalerAudio_ComboPhyCommonInclude.h"
#include "ScalerDP_ComboPhyCommonInclude.h"
#include "ScalerDPRx0_ComboPhyCommonInclude.h"
#include "ScalerDPRx0_INT_ComboPhyCommonInclude.h"
#include "ScalerTMDS_ComboPhyCommonInclude.h"

#elif(_SCALER_TYPE == _RL6492_SERIES)

#include "ScalerAudio_ComboPhyCommonInclude.h"
#include "ScalerTMDS_ComboPhyCommonInclude.h"

#endif
#include "ScalerDPRxMST_SeptPhyCommonInclude.h"
