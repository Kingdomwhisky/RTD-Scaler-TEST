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
// ID Code      : ScalerFunctionInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerVGATopInterface.h"
#include "ScalerADCInterface.h"
#include "ScalerAutoFuncInterface.h"
#include "ScalerDisplayInterface.h"
#include "ScalerFRCInterface.h"
#include "ScalerMemoryInterface.h"
#include "ScalerODInterface.h"
#include "ScalerOsdInterface.h"
#include "ScalerPinshareInterface.h"
#include "ScalerRegInterface.h"
#include "ScalerSyncProcInterface.h"
#include "ScalerPowerInterface.h"
#include "ScalerMcuInterface.h"
#include "ScalerTimerFunctionInterface.h"
#include "ScalerGlobalInterface.h"
#include "ScalerSDRAMInterface.h"
#include "ScalerDDR1Interface.h"
#include "ScalerDDR3Interface.h"
#include "ScalerSyncInterface.h"
#include "ScalerMeasureInterface.h"
#include "ScalerIDomainInterface.h"
#include "ScalerMDomainInterface.h"
#include "ScalerDDomainInterface.h"
#include "ScalerPLLInterface.h"
#include "ScalerAudioInterface.h"
#include "ScalerColorInterface.h"
#include "ScalerFunctionLibInterface.h"
#include "ScalerDPRxMSTInterface.h"
#include "ScalerDPTxInterface.h"
#include "ScalerGDIPhyTxInterface.h"
#include "ScalerRotationInterface.h"
#include "ScalerDisplayDPTxInterface.h"
#include "ScalerDualLinkDVIInterface.h"
#include "ScalerIRInterface.h"
#include "ScalerDPRx0HDCP2Interface.h"
#include "ScalerDPRx1HDCP2Interface.h"
#include "ScalerDPTxHDCP2Interface.h"
#include "ScalerCecInterface.h"


#include "ScalerCommonSpiInterface.h"
#include "ScalerCommonTypeCInterface.h"

#include "ScalerMbrInterface.h"

#if(_SCALER_TYPE == _RL6369_SERIES)
#include "RL6369_Series_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Series_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6432_SERIES)
#include "RL6432_Series_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6449_SERIES)
#include "RL6449_Series_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6463_SERIES)
#include "RL6463_Series_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6492_SERIES)
#include "RL6492_Series_FunctionInterface.h"
#endif

#include "ScalerFormatConversionInterface.h"
#include "ScalerVGIPInterface.h"
#include "ScalerDPRx0Interface.h"


#if((_SCALER_TYPE == _RL6410_SERIES) ||\
    (_SCALER_TYPE == _RL6432_SERIES) ||\
    (_SCALER_TYPE == _RL6449_SERIES))

#include "ScalerAudio_SeptPhyInterface.h"
#include "ScalerDP_SeptPhyInterface.h"
#include "ScalerDPRx0_SeptPhyInterface.h"
#include "ScalerDPRx0_INT_SeptPhyInterface.h"
#include "ScalerDPRx1_SeptPhyInterface.h"
#include "ScalerDPRx1_INT_SeptPhyInterface.h"
#include "ScalerDPRx1HDCP2_SeptPhyInterface.h"
#include "ScalerMHL3Rx2_SeptPhyInterface.h"
#include "ScalerMHL3Rx3_SeptPhyInterface.h"
#include "ScalerMHLRx2_SeptPhyInterface.h"
#include "ScalerMHLRx3_SeptPhyInterface.h"
#include "ScalerMHLRx4_SeptPhyInterface.h"
#include "ScalerMHLRx5_SeptPhyInterface.h"
#include "ScalerTMDSRx1_SeptPhyInterface.h"
#include "ScalerTMDSRx1HDCP2_SeptPhyInterface.h"
#include "ScalerTMDSRx2_SeptPhyInterface.h"
#include "ScalerTMDSRx2HDCP2_SeptPhyInterface.h"
#include "ScalerTMDSRx3_SeptPhyInterface.h"
#include "ScalerTMDSRx3HDCP2_SeptPhyInterface.h"
#include "ScalerTMDSRx4_SeptPhyInterface.h"
#include "ScalerTMDSRx4HDCP2_SeptPhyInterface.h"
#include "ScalerTMDSRx5_SeptPhyInterface.h"
#include "ScalerTMDSRx5HDCP2_SeptPhyInterface.h"

#elif((_SCALER_TYPE == _RL6369_SERIES) ||\
      (_SCALER_TYPE == _RL6463_SERIES))

#include "ScalerAudio_ComboPhyInterface.h"
#include "ScalerDP_ComboPhyInterface.h"
#include "ScalerDPRx0_ComboPhyInterface.h"
#include "ScalerDPRx0_INT_ComboPhyInterface.h"
#include "ScalerTMDS_ComboPhyInterface.h"

#elif(_SCALER_TYPE == _RL6492_SERIES)

#include "ScalerAudio_ComboPhyInterface.h"
#include "ScalerTMDS_ComboPhyInterface.h"

#endif

#include "ScalerDPRxMST_SeptPhyInterface.h"
