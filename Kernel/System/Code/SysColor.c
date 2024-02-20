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
// ID Code      : SysColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_COLOR__

#include "SysInclude.h"

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
void SysColorHandler(void);
#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
void SysColorDCCHistogramHandler(void);
#endif
#if(_COLOR_IP_DCR == _ON)
void SysColorDCRHandler(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Color Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysColorHandler(void)
{
    switch(GET_MODE_STATE())
    {
        case _MODE_STATUS_ACTIVE:

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
            SysColorDCCHistogramHandler();
#endif

#if(_COLOR_IP_DCR == _ON)
            SysColorDCRHandler();
#endif

#if(_COLORIMETRY_SEAMLESS_CHANGE_SUPPORT == _ON)
            UserCommonSeamlessChgHandler();
#endif

#if((_MOTION_BLUR_REDUCTION_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
            UserCommonInterfaceMbrDrrHandler();
#endif
            break;

        default:
            break;
    }
}

#if(_COLOR_IP_DCC_HISTOGRAM == _ON)
//--------------------------------------------------
// Description  : Color DCC Histogram Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysColorDCCHistogramHandler(void)
{
    if(ScalerColorDCCGetDataReadyStatus() == _TRUE)
    {
        // Clear DCC data ready status.
        ScalerColorDCCClrDataReadyStatus();

        SET_DCC_READY_STATUS();
    }

    if(GET_DCC_READY_STATUS() == _TRUE)
    {
#if(_DCC_HISTOGRM_INFO == _ON)
        UserInterfaceDCCHistogramHandler();
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
        UserCommonHDRHandler();
#endif
    }

    CLR_DCC_READY_STATUS();
}
#endif

#if(_COLOR_IP_DCR == _ON)
//--------------------------------------------------
// Description  : Color DCR Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysColorDCRHandler(void)
{
    if(ScalerColorDCRGetDataReadyStatus() == _TRUE)
    {
        // Clear DCR data ready status.
        ScalerColorDCRClrDataReadyStatus();

        SET_DCR_READY_STATUS();

        // freeze DCR data
        ScalerColorDCRDataRefreshControl(_DISABLE);

#if(_LOCAL_DIMMING_SUPPORT == _ON)
        if(ScalerColorDCRGetLocalDimmingHistoEnable() == _TRUE)
        {
            ScalerColorDCRLocalDimmingStoreResult();

            // release DCR data
            ScalerColorDCRDataRefreshControl(_ENABLE);
        }
#endif
    }

    if(GET_DCR_READY_STATUS() == _TRUE)
    {
#if(_DCR_SUPPORT == _ON)
        UserInterfaceAdjustDCRHandler();
#endif

#if(_IAPS_SUPPORT == _ON)
        UserInterfaceAdjustIAPSHandler();
#endif

#if(_LOCAL_DIMMING_SUPPORT == _ON)
        UserCommonLocalDimmingHandler();
#endif

#if(_GLOBAL_DIMMING_SUPPORT == _ON)
        UserCommonGlobalDimmingHandler();
#endif
    }

    CLR_DCR_READY_STATUS();

    // release DCR data
    ScalerColorDCRDataRefreshControl(_ENABLE);
}
#endif

