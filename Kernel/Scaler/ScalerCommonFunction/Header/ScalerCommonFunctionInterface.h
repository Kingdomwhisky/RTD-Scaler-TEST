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
// ID Code      : ScalerCommonFunctionInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Series_Common_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6432_SERIES)
#include "RL6432_Series_Common_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6449_SERIES)
#include "RL6449_Series_Common_FunctionInterface.h"
#elif(_SCALER_TYPE == _RL6492_SERIES)
#include "RL6492_Series_Common_FunctionInterface.h"
#endif

#include "ScalerCommonRegInterface.h"
#include "ScalerCommonDebugInterface.h"
#include "ScalerCommonPowerInterface.h"
#include "ScalerCommonIOSCInterface.h"
#include "ScalerCommonMcuInterface.h"
#include "ScalerCommonTimerFunctionInterface.h"
#include "ScalerCommonSyncInterface.h"
#include "ScalerCommonMeasureInterface.h"
#include "ScalerCommonPLLInterface.h"
#include "ScalerCommonColorInterface.h"
#include "ScalerCommonFunctionLibInterface.h"
#include "ScalerCommonDPRx0Interface.h"
#include "ScalerCommonDPRx1Interface.h"
#include "ScalerCommonDPRxMSTInterface.h"
#include "ScalerCommonDPTxInterface.h"
#include "ScalerCommonDPTxMSTInterface.h"
#include "ScalerCommonDPTxAuxInterface.h"
#include "ScalerCommonNVRamInterface.h"
#include "ScalerCommonHDCP2Interface.h"
#include "ScalerCommonTMDSInterface.h"
#include "ScalerCommonDPRx0HDCP2Interface.h"
#include "ScalerCommonDPRx1HDCP2Interface.h"
#include "ScalerCommonDPTxHDCP2Interface.h"
#include "ScalerCommonFreeSyncInterface.h"

