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
// ID Code      : ScalerCommonFreeSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COMMON_FREESYNC__

#include "ScalerCommonFunctionInclude.h"

#if(_FREESYNC_SUPPORT == _ON)
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
BYTE ScalerFreeSyncGetFreeSyncInfo(EnumSourceSearchPort enumSearchPort, EnumAmdSpdInfoContent enumContent);
void ScalerFreeSyncSPDInfoReceive(EnumSourceSearchPort enumSearchPort);

#if(_TRANSLATOR_SUPPORT == _OFF)
void ScalerFreeSyncSupportSwitch(EnumSourceSearchPort enumSourcePort, EnumFreeSyncSupport enumSupport);
#endif

#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
WORD ScalerFreeSyncDpGetHSPeriod(EnumSourceSearchPort enumSourceSearchPort);
WORD ScalerFreeSyncDpGetHSW(EnumSourceSearchPort enumSourceSearchPort);
WORD ScalerFreeSyncDpGetVFreq(EnumSourceSearchPort enumSourceSearchPort);
WORD ScalerFreeSyncDpGetVSPeriod(EnumSourceSearchPort enumSourceSearchPort);
void ScalerFreeSyncDpGetSourceInfo(EnumSourceSearchPort enumSearchPort, StructDpFreeSyncSourceInfo *pstSourceInfo);
bit ScalerFreeSyncDpEdidAnalysisCheckBoundry(const StructDpFreeSyncEdidInfo *pstEdidInfo, const StructDpFreeSyncEdidRefInfo *pstEdidRefInfo);
void ScalerFreeSyncDpEdidAnalysisGetRefInfo(StructDpFreeSyncEdidRefInfo *pstEdidRefInfo, WORD usPixelClk, const StructDpFreeSyncSourceInfo *pstSourceInfo);
EnumDrrFreeSyncDpGetIVF ScalerFreeSyncDpEdidAnalysisGetVfreqMax(BYTE *pucReadArray, WORD usPixelClk, const StructDpFreeSyncSourceInfo *pstSourceInfo, WORD *pusVfreqMax);

#if(_D0_DP_EXIST == _ON)
BYTE ScalerFreeSyncDpRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
WORD ScalerFreeSyncDpRx0GetBStoHSDelay(WORD usDpHtotal);
WORD ScalerFreeSyncDpRx0GetHPeriod(void);
WORD ScalerFreeSyncDpRx0GetHSW(void);
WORD ScalerFreeSyncDpRx0GetVFreq(void);
WORD ScalerFreeSyncDpRx0GetVPeriod(void);
void ScalerFreeSyncDpRx0GetSPDVfreqMaxMin(void);
#endif

#if(_D1_DP_EXIST == _ON)
BYTE ScalerFreeSyncDpRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
WORD ScalerFreeSyncDpRx1GetBStoHSDelay(WORD usDpHtotal);
WORD ScalerFreeSyncDpRx1GetHPeriod(void);
WORD ScalerFreeSyncDpRx1GetHSW(void);
WORD ScalerFreeSyncDpRx1GetVFreq(void);
WORD ScalerFreeSyncDpRx1GetVPeriod(void);
void ScalerFreeSyncDpRx1GetSPDVfreqMaxMin(void);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
void ScalerFreeSyncDpSupportSwitch(EnumSourceSearchPort enumSourcePort, EnumFreeSyncSupport enumSupport);
#endif
#endif // End of #if(_DP_FREESYNC_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) &&\
    (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
EnumFreeSyncSupport ScalerFreeSyncHDMIGetFreeSyncSupport_EXINT1(EnumSourceSearchPort enumSourcePort);
#endif

#if(_HDMI_MAC_PAGE2_USE == _ON)
BYTE ScalerFreeSyncHDMIRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE71_USE == _ON)
BYTE ScalerFreeSyncHDMIRx2GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, bit bD1Combo);
#endif

#if(_HDMI_MAC_PAGE72_USE == _ON)
BYTE ScalerFreeSyncHDMIRx3GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE73_USE == _ON)
BYTE ScalerFreeSyncHDMIRx4GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_HDMI_MAC_PAGE74_USE == _ON)
BYTE ScalerFreeSyncHDMIRx5GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
void ScalerFreeSyncHDMISupportSwitch(EnumSourceSearchPort enumSourcePort, EnumFreeSyncSupport enumSupport);
#endif
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)
#endif // End of #if(_HDMI_SUPPORT == _ON)


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get AMD SPD info
// Input Value  : enumContent -> enumSearchPort -> Port Type, AMD Info Type
// Output Value : None
//--------------------------------------------------
BYTE ScalerFreeSyncGetFreeSyncInfo(EnumSourceSearchPort enumSearchPort, EnumAmdSpdInfoContent enumContent)
{
    BYTE ucFreeSyncInfo = 0;

    switch(enumSearchPort)
    {
        case _D0_INPUT_PORT:
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_DPRX0_AMD_SPD_INFO(enumContent);
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_HDMIRX0_AMD_SPD_INFO(enumContent);
#endif
            break;


        case _D1_INPUT_PORT:
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_DPRX1_AMD_SPD_INFO(enumContent);
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_HDMIRX1_AMD_SPD_INFO(enumContent);
#endif
            break;


        case _D2_INPUT_PORT:
#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_DPRX2_AMD_SPD_INFO(enumContent);
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_HDMIRX2_AMD_SPD_INFO(enumContent);
#endif
            break;


        case _D3_INPUT_PORT:
#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_HDMIRX3_AMD_SPD_INFO(enumContent);
#endif
            break;


        case _D4_INPUT_PORT:
#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_HDMIRX4_AMD_SPD_INFO(enumContent);
#endif
            break;


        case _D5_INPUT_PORT:
#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ucFreeSyncInfo = GET_HDMIRX5_AMD_SPD_INFO(enumContent);
#endif
            break;


        default:
            ucFreeSyncInfo = 0;
            break;
    }

    switch(enumContent)
    {
        case _SPD_INFO_FREESYNC_ENABLE:
            ucFreeSyncInfo = ScalerSyncGetFREESYNCEnable();
            break;


        case _SPD_INFO_FREESYNC_MIN_VFREQ:
            break;


        case _SPD_INFO_FREESYNC_MAX_VFREQ:
            break;

        default:
            break;
    }

    return ucFreeSyncInfo;
}

//--------------------------------------------------
// Description  : Get AMD SPD info
// Input Value  : enumSearchPort -> Port Type
// Output Value : None
//--------------------------------------------------
void ScalerFreeSyncSPDInfoReceive(EnumSourceSearchPort enumSearchPort)
{
    switch(enumSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_DP_RX0_SPD_INFO_FRAME_RECEIVED());
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_HDMI_FREESYNC_ENABLED());
#endif

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_DP_RX1_SPD_INFO_FRAME_RECEIVED());
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_HDMI_FREESYNC_ENABLED());
#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_DP_RX1_SPD_INFO_FRAME_RECEIVED());
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_HDMI_FREESYNC_ENABLED());
#endif

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_HDMI_FREESYNC_ENABLED());
#endif

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_HDMI_FREESYNC_ENABLED());
#endif

            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            SET_FREESYNC_SPD_INFO_FRAME_RECEIVED(GET_HDMI_FREESYNC_ENABLED());
#endif

            break;
#endif

        default:
            break;
    }
}

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : HDMI freesync initial
// Input Value  : support or not
// Output Value :
//--------------------------------------------------
void ScalerFreeSyncSupportSwitch(EnumSourceSearchPort enumSourcePort, EnumFreeSyncSupport enumSupport)
{
    enumSupport = enumSupport;

    switch(enumSourcePort)
    {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncDpSupportSwitch(enumSourcePort, enumSupport);
#elif((_D0_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncHDMISupportSwitch(enumSourcePort, enumSupport);
#endif

            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncDpSupportSwitch(enumSourcePort, enumSupport);
#elif((_D1_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncHDMISupportSwitch(enumSourcePort, enumSupport);
#endif

            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if((_D2_INPUT_PORT_TYPE == _D2_DP_PORT) && (_DP_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncDpSupportSwitch(enumSourcePort, enumSupport);
#elif((_D2_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncHDMISupportSwitch(enumSourcePort, enumSupport);
#endif

            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if((_D3_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncHDMISupportSwitch(enumSourcePort, enumSupport);
#endif

            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if((_D4_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncHDMISupportSwitch(enumSourcePort, enumSupport);
#endif

            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if((_D5_HDMI_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
            ScalerFreeSyncHDMISupportSwitch(enumSourcePort, enumSupport);
#endif

            break;
#endif

        default:
            break;
    }
}
#endif

#if(_DP_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current DP H Period
// Input Value  : enumSourceSearchPort --> Source Search Port
// Output Value : H period in nano sec
//--------------------------------------------------
WORD ScalerFreeSyncDpGetHSPeriod(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return GET_DPRX0_H_PERIOD();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return GET_DPRX1_H_PERIOD();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            return GET_DPRX2_H_PERIOD();
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Current DP H Sync Width
// Input Value  : enumSourceSearchPort --> Source Search Port
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerFreeSyncDpGetHSW(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return ((DWORD)GET_DPRX0_HSW() * _MEASURE_CLK / GET_INPUT_PIXEL_CLK() / 100);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return ((DWORD)GET_DPRX1_HSW() * _MEASURE_CLK / GET_INPUT_PIXEL_CLK() / 100);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            return ((DWORD)GET_DPRX2_HSW() * _MEASURE_CLK / GET_INPUT_PIXEL_CLK() / 100);
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Dp Get Vfreq
// Input Value  : enumSourceSearchPort --> Source Search Port
// Output Value : VFreq in 0.1Hz
//--------------------------------------------------
WORD ScalerFreeSyncDpGetVFreq(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return GET_DPRX0_V_FREQ();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return GET_DPRX1_V_FREQ();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            return GET_DPRX2_V_FREQ();
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Current DP V Period
// Input Value  : enumSourceSearchPort --> Source Search Port
// Output Value : V period in line
//--------------------------------------------------
WORD ScalerFreeSyncDpGetVSPeriod(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return GET_DPRX0_V_PERIOD();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return GET_DPRX1_V_PERIOD();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            return GET_DPRX2_V_PERIOD();
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get DP Freesync Htotal Margin
// Input Value  : enumInputPort --> Source Search Port
// Output Value : Htotal Margin & Htotal
//--------------------------------------------------
void ScalerFreeSyncDpGetSourceInfo(EnumSourceSearchPort enumSearchPort, StructDpFreeSyncSourceInfo *pstSourceInfo)
{
    pstSourceInfo->ucColorSapce = GET_COLOR_SPACE();

    switch(enumSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            pstSourceInfo->usHtotal = GET_DP_RX0_HTOTAL();
            pstSourceInfo->usHtotalMargin = GET_DP_RX0_HTOTAL_MARGIN();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            pstSourceInfo->usHtotal = GET_DP_RX1_HTOTAL();
            pstSourceInfo->usHtotalMargin = GET_DP_RX1_HTOTAL_MARGIN();
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : EDID Analysis Check Hwidth/ Vheight/ Hblanking/ Pixel
// Input Value  : Hwidth/ Vheight/ Hblanking/ Pixel
// Output Value : _TRUE: Find
//--------------------------------------------------
bit ScalerFreeSyncDpEdidAnalysisCheckBoundry(const StructDpFreeSyncEdidInfo *pstEdidInfo, const StructDpFreeSyncEdidRefInfo *pstEdidRefInfo)
{
    // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
    if((pstEdidInfo->usHwidth == pstEdidRefInfo->usRefHwidth) && (pstEdidInfo->usVheight == pstEdidRefInfo->usRefVheight) &&
       ((pstEdidInfo->usHblank <= pstEdidRefInfo->usRefHblankHBound) && (pstEdidInfo->usHblank >= pstEdidRefInfo->usRefHblankLBound)) &&
       ((pstEdidInfo->usPixelClk <= pstEdidRefInfo->usPixelClkHBound) && (pstEdidInfo->usPixelClk >= pstEdidRefInfo->usPixelClkLBound)))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : EDID Analysis Get Ref Timing Info
// Input Value  : usPixelClk/ pstHtotalInfo(Htotal & Htotal margin)
// Output Value : pstEdidRefInfo
//--------------------------------------------------
void ScalerFreeSyncDpEdidAnalysisGetRefInfo(StructDpFreeSyncEdidRefInfo *pstEdidRefInfo, WORD usPixelClk, const StructDpFreeSyncSourceInfo *pstSourceInfo)
{
    WORD usClkMargin = ((DWORD)usPixelClk * _DP_FREESYNC_CLK_MARGIN / 100);

    pstEdidRefInfo->usRefHwidth = GET_INPUT_TIMING_HWIDTH();
    pstEdidRefInfo->usRefVheight = GET_INPUT_TIMING_VHEIGHT();
    pstEdidRefInfo->usRefHblankHBound = (pstSourceInfo->usHtotal - GET_INPUT_TIMING_HWIDTH() + pstSourceInfo->usHtotalMargin);
    pstEdidRefInfo->usRefHblankLBound = (pstSourceInfo->usHtotal - GET_INPUT_TIMING_HWIDTH() - pstSourceInfo->usHtotalMargin);
    pstEdidRefInfo->usPixelClkHBound = (usPixelClk + usClkMargin);
    pstEdidRefInfo->usPixelClkLBound = (usPixelClk - usClkMargin);
}

//--------------------------------------------------
// Description  : Get DP Freesync Vfreq from EDID Analysis
// Input Value  : pucReadArray: EDID address, usPixelClk: Input pixel clk(0.1M)
// Output Value : _TRUE: Get IVF, unit: 0.1Hz
//--------------------------------------------------
EnumDrrFreeSyncDpGetIVF ScalerFreeSyncDpEdidAnalysisGetVfreqMax(BYTE *pucReadArray, WORD usPixelClk, const StructDpFreeSyncSourceInfo *pstSourceInfo, WORD *pusVfreqMax)
{
    EnumDrrFreeSyncDpGetIVF enumDrrFreeSyncDPGetIVF = _DP_FREESYNC_WITHOUT_IVF_MAX;

    // === Misc ===
    DWORD ulCandidatedPixelRate = 0; // 0.1 MHz
    WORD usCandidatedVfreq = 0; // 0.1 Hz

    WORD pusCtaDataBlockAddr[_CTA_TOTAL_DB] = {0};
    WORD pusDidDataBlockAddr[_DID_TOTAL_DB] = {0};

    WORD usStartAddr = 0;
    WORD usIndex = 0;
    BYTE ucCnt = 0;

    // === Edid Info ===
    StructDpFreeSyncEdidInfo stEdidInfo;
    StructDpFreeSyncEdidRefInfo stEdidRefInfo;
    memset(&stEdidInfo, 0, sizeof(stEdidInfo));
    memset(&stEdidRefInfo, 0, sizeof(stEdidRefInfo));

    ScalerFreeSyncDpEdidAnalysisGetRefInfo(&stEdidRefInfo, usPixelClk, pstSourceInfo);

    // Get DB start addr from Edid Data
    ScalerSyncGetCtaExtDbAddress(pusCtaDataBlockAddr, pucReadArray);
    ScalerSyncGetDidExtDbAddress(pusDidDataBlockAddr, pucReadArray);

    // -----------------------------------------------------------
    // EDID: DTD Capture
    // -----------------------------------------------------------
    // Base DTD
    for(ucCnt = 0; ucCnt < 4; ucCnt++)
    {
        // Set Start addr to DTD start location
        usStartAddr = (0x36 + (ucCnt * 18));

        // Check DTD or not
        if((pucReadArray[usStartAddr] != 0x00) && (pucReadArray[usStartAddr + 1] != 0x00))
        {
            // Catch DTD's Hblank/ Hactive/ Vactive
            stEdidInfo.usHwidth = (((WORD)(pucReadArray[usStartAddr + 4] & 0xF0) << 4) | pucReadArray[usStartAddr + 2]);
            stEdidInfo.usHblank = (((WORD)(pucReadArray[usStartAddr + 4] & 0x0F) << 8) | pucReadArray[usStartAddr + 3]);
            stEdidInfo.usVheight = (((WORD)(pucReadArray[usStartAddr + 7] & 0xF0) << 4) | pucReadArray[usStartAddr + 5]);
            stEdidInfo.usPixelClk = ((((DWORD)pucReadArray[usStartAddr + 1] << 8) | pucReadArray[usStartAddr]) / 10); // 0.1 MHz

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerFreeSyncDpEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    stEdidInfo.usVtotal = stEdidInfo.usVheight + (((WORD)(pucReadArray[usStartAddr + 7] & 0x0F) << 8) | pucReadArray[usStartAddr + 6]);
                    stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;

                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;
                    usCandidatedVfreq = ((GET_DWORD_MUL_DIV(stEdidInfo.usPixelClk, 1000000, stEdidInfo.usVtotal) + (stEdidInfo.usHtotal / 2)) / stEdidInfo.usHtotal);

                    DebugMessageScaler("Get Candidated Vfreq from EDID Base DTD", 0);
                }
            }
        }
    }

    // Extension DTD
    if(pucReadArray[0x7E] != 0x00)
    {
        for(usIndex = 0; usIndex < pucReadArray[0x7E]; usIndex++)
        {
            // Stop Extension Analysis if Not CEA Type, Check tag = 0x02
            if(pucReadArray[(usIndex + 1) * 0x80] == 0x02)
            {
                // Set Start addr to DTD start location
                usStartAddr = (0x80 * (usIndex + 1)) + pucReadArray[(0x80 * (usIndex + 1)) + 0x02];

                for(ucCnt = 0; ucCnt < 6; ucCnt++)
                {
                    if(usStartAddr > ((0x80 * (usIndex + 1)) + 0x7E))
                    {
                        break;
                    }

                    // Check DTD or not
                    if((pucReadArray[usStartAddr] != 0x00) && (pucReadArray[usStartAddr + 1] != 0x00))
                    {
                        // Catch DTD's Hblank/ Hactive/ Vactive
                        stEdidInfo.usHwidth = (((WORD)(pucReadArray[usStartAddr + 4] & 0xF0) << 4) | pucReadArray[usStartAddr + 2]);
                        stEdidInfo.usHblank = (((WORD)(pucReadArray[usStartAddr + 4] & 0x0F) << 8) | pucReadArray[usStartAddr + 3]);
                        stEdidInfo.usVheight = (((WORD)(pucReadArray[usStartAddr + 7] & 0xF0) << 4) | pucReadArray[usStartAddr + 5]);
                        stEdidInfo.usPixelClk = ((((WORD)pucReadArray[usStartAddr + 1] << 8) | pucReadArray[usStartAddr]) / 10); // 0.1 MHz

                        // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
                        if(ScalerFreeSyncDpEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
                        {
                            // Check & take the large Pixel
                            if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                            {
                                stEdidInfo.usVtotal = stEdidInfo.usVheight + (((WORD)(pucReadArray[usStartAddr + 7] & 0x0F) << 8) | pucReadArray[usStartAddr + 6]);
                                stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;

                                ulCandidatedPixelRate = stEdidInfo.usPixelClk;
                                usCandidatedVfreq = ((GET_DWORD_MUL_DIV(stEdidInfo.usPixelClk, 1000000, stEdidInfo.usVtotal) + (stEdidInfo.usHtotal / 2)) / stEdidInfo.usHtotal);

                                DebugMessageScaler("Get Candidated Vfreq from EDID EXT DTD", 0);
                            }
                        }
                    }

                    usStartAddr += 0x12;
                }
            }
        } // End of Extension Block Analysis For Loop
    }

    // -----------------------------------------------------------
    // EDID: DB Capature
    // -----------------------------------------------------------
    // VDB
    if(pusCtaDataBlockAddr[_CTA_VDB] != 0x00)
    {
        BYTE ucVicIndex = 0;
        BYTE ucDblength = 0;

        // Set Start addr to VDB start location
        usStartAddr = pusCtaDataBlockAddr[_CTA_VDB];
        ucDblength = (pucReadArray[usStartAddr] & 0x1F);

        for(usIndex = 0; usIndex < ucDblength; usIndex++)
        {
            ucVicIndex = pucReadArray[usStartAddr + 1 + usIndex];

            // depart native / non-native factor & fit index to Code table below
            if(((1 <= ucVicIndex) && (ucVicIndex <= 64)) ||
               ((129 <= ucVicIndex) && (ucVicIndex <= 192)))
            {
                ucVicIndex = (ucVicIndex & 0x7F) - 1;
            }
            else
            {
                ucVicIndex -= 1;
            }

            stEdidInfo.usHwidth = tVIC_HACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usHblank = tVIC_HBLANK_TABLE[ucVicIndex];
            stEdidInfo.usVheight = tVIC_VACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usPixelClk = tVIC_PIXEL_RATE_TABLE[ucVicIndex]; // 0.1 MHz

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerFreeSyncDpEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;
                    usCandidatedVfreq = (WORD)tVIC_VFREQ_TABLE[ucVicIndex] * 10;

                    DebugMessageScaler("Get Candidated Vfreq from EDID VDB", 0);
                }
            }
        }
    }

    // 420 VDB
    if((pusCtaDataBlockAddr[_CTA_420VDB] != 0x00) && (pstSourceInfo->ucColorSapce == _COLOR_SPACE_YCBCR420))
    {
        BYTE ucVicIndex = 0;
        BYTE ucDblength = 0;

        // Set Start addr to 420VDB start location
        usStartAddr = pusCtaDataBlockAddr[_CTA_420VDB];
        ucDblength = (pucReadArray[usStartAddr] & 0x1F);

        for(usIndex = 0; usIndex < ucDblength; usIndex++)
        {
            ucVicIndex = pucReadArray[usStartAddr + 2 + usIndex];

            // depart native / non-native factor & fit index to Code table below
            if(((1 <= ucVicIndex) && (ucVicIndex <= 64)) ||
               ((129 <= ucVicIndex) && (ucVicIndex <= 192)))
            {
                ucVicIndex = (ucVicIndex & 0x7F) - 1;
            }
            else
            {
                ucVicIndex -= 1;
            }

            stEdidInfo.usHwidth = tVIC_HACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usHblank = tVIC_HBLANK_TABLE[ucVicIndex];
            stEdidInfo.usVheight = tVIC_VACTIVE_TABLE[ucVicIndex];
            stEdidInfo.usPixelClk = tVIC_PIXEL_RATE_TABLE[ucVicIndex]; // 0.1 MHz

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerFreeSyncDpEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;
                    usCandidatedVfreq = (WORD)tVIC_VFREQ_TABLE[ucVicIndex] * 10;

                    DebugMessageScaler("Get Candidated Vfreq from EDID 420VDB", 0);
                }
            }
        }
    }

    // -----------------------------------------------------------
    // DID: Timing I DB
    // -----------------------------------------------------------
    if(pusDidDataBlockAddr[_DID_T1_DB] != 0x00)
    {
        BYTE ucTimingNum = (pucReadArray[pusDidDataBlockAddr[_DID_T1_DB] + 2] / 20);

        // Catch each Timing from Timing1 DB
        for(usIndex = 0; usIndex < ucTimingNum; usIndex++)
        {
            // Set start addr to Timing 1 's Descriptor unit
            usStartAddr = (pusDidDataBlockAddr[_DID_T1_DB] + 3 + (20 * usIndex));

            // Catch Timing1's Hblank/ Hactive/ Vactive  (Timing 1's range is 1~xxx)
            stEdidInfo.usHwidth = (((WORD)pucReadArray[usStartAddr + 5] << 8) | pucReadArray[usStartAddr + 4]) + 1;
            stEdidInfo.usHblank = (((WORD)pucReadArray[usStartAddr + 7] << 8) | pucReadArray[usStartAddr + 6]) + 1;
            stEdidInfo.usVheight = (((WORD)pucReadArray[usStartAddr + 13] << 8) | pucReadArray[usStartAddr + 12]) + 1;
            stEdidInfo.usPixelClk = (((((DWORD)pucReadArray[usStartAddr + 2] << 16) | ((DWORD)pucReadArray[usStartAddr + 1] << 8) | pucReadArray[usStartAddr]) + 1) / 10); // 0.1 MHz

            // Check Hactive/ Vactive/ Hblank match & PixelRate inside the Boundary
            if(ScalerFreeSyncDpEdidAnalysisCheckBoundry(&stEdidInfo, &stEdidRefInfo) == _TRUE)
            {
                // Check & take the large Pixel
                if(stEdidInfo.usPixelClk > ulCandidatedPixelRate)
                {
                    stEdidInfo.usVtotal = stEdidInfo.usVheight + (((WORD)pucReadArray[usStartAddr + 15] << 8) | pucReadArray[usStartAddr + 14]);
                    stEdidInfo.usHtotal = stEdidInfo.usHwidth + stEdidInfo.usHblank;

                    ulCandidatedPixelRate = stEdidInfo.usPixelClk;
                    usCandidatedVfreq = ((GET_DWORD_MUL_DIV(stEdidInfo.usPixelClk, 1000000, stEdidInfo.usVtotal) + (stEdidInfo.usHtotal / 2)) / stEdidInfo.usHtotal);

                    DebugMessageScaler("Get Candidated Vfreq from DID Timing1", 0);
                }
            }
        }
    }

    if(usCandidatedVfreq != 0x00)
    {
        enumDrrFreeSyncDPGetIVF = _DP_FREESYNC_WITH_IVF_MAX;

        *pusVfreqMax = usCandidatedVfreq;
    }

    return enumDrrFreeSyncDPGetIVF;
}

#if(_D0_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerFreeSyncDpRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    BYTE pucDPRSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];
    bit bCheckFreeSync = _FALSE;

#if(_DP_HDR10_SUPPORT == _ON)
    memcpy(pucDPRSV0Data, g_pucDPRx0RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);

    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        bCheckFreeSync = _TRUE;
    }
#else
    memset(pucDPRSV0Data, 0, sizeof(pucDPRSV0Data));

    ScalerDpRx0GetInfoFrameRSV0(pucDPRSV0Data);

    if(ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0) == _SPD_INFO_TYPE)
    {
        bCheckFreeSync = _TRUE;
    }
#endif

    if(bCheckFreeSync == _TRUE)
    {
        // Check AMD OUI
        if((pucDPRSV0Data[1] == 0x1A) && (pucDPRSV0Data[2] == 0x00) && (pucDPRSV0Data[3] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return (((pucDPRSV0Data[6] & _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return (((pucDPRSV0Data[6] & _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return (((pucDPRSV0Data[6] & _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    if(((WORD)pucDPRSV0Data[7] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pucDPRSV0Data[7] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pucDPRSV0Data[7] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pucDPRSV0Data[7] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 1);
                    }

                    return pucDPRSV0Data[7];
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    if(((WORD)pucDPRSV0Data[8] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pucDPRSV0Data[8] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pucDPRSV0Data[8] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pucDPRSV0Data[8] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 1);
                    }

                    return pucDPRSV0Data[8];
                    break;

                default:
                    return 0x00;
                    break;
            }
        }

        return 0x00;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : DP BS to HS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
WORD ScalerFreeSyncDpRx0GetBStoHSDelay(WORD usDpHtotal)
{
    WORD usFifoOffset = 0;
    WORD usHStart = 0;
    WORD usHActive = 0;

    pData[15] = GET_COLOR_DEPTH();

    // DP fifo size = 256 x 96bit or 128 x 96bit
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (fifo size) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (fifo size) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // Get Hstart
    usHStart = (((WORD)ScalerGetByte(PB5_43_MN_DPF_HST_M) << 8) | (ScalerGetByte(PB5_44_MN_DPF_HST_L)));

    // Get Hactive
    usHActive = (((WORD)ScalerGetByte(PB5_45_MN_DPF_HWD_M) << 8) | (ScalerGetByte(PB5_46_MN_DPF_HWD_L)));

    // De Only Mode HW constraint: BS2HS delay < Htotal => 1/2 FIFO < H Width, Enough Margin = 1/2 H Width
    if(usFifoOffset > (usHActive >> 1))
    {
        usFifoOffset = (usHActive >> 1);
    }

    // H Blanking = HTotal - HActive
    PDATA_WORD(0) = usDpHtotal - usHActive;

    // Set BS to HS delay to (HBlanking + 1/2 FIFO - HStart), BS2HS delay: 2 pixel mode
    return ((WORD)((PDATA_WORD(0) + usFifoOffset - usHStart) >> 1));
}

//--------------------------------------------------
// Description  : Get Current DP H Period
// Input Value  : None
// Output Value : H period in nano sec
//--------------------------------------------------
WORD ScalerFreeSyncDpRx0GetHPeriod(void)
{
    WORD usHBs2BsCount = 0;

    // Pop up The result
    SET_DP_RX0_MEASURE_POP_UP();

    // HBs2Bs count in Link Clk / 2
    usHBs2BsCount = (((WORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | (ScalerGetByte(PB5_5C_MN_MEAS_HLN_L));

    return (((DWORD)usHBs2BsCount * 1000) / (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2));
}

//--------------------------------------------------
// Description  : Get Current DP H Sync Width
// Input Value  : None
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerFreeSyncDpRx0GetHSW(void)
{
    WORD usHSWidth = 0;

    usHSWidth = ((((WORD)ScalerGetByte(PB5_47_MN_DPF_HSW_M) << 8) | (ScalerGetByte(PB5_48_MN_DPF_HSW_L))) & 0x7FFF);

    return usHSWidth;
}

//--------------------------------------------------
// Description  : Get Current DP V Freq
// Input Value  : None
// Output Value : VFreq in 0.1Hz
//--------------------------------------------------
WORD ScalerFreeSyncDpRx0GetVFreq(void)
{
    DWORD ulVBs2BsCount = 0;

    // Pop up The result
    SET_DP_RX0_MEASURE_POP_UP();

    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));

    return (DWORD)_GDI_CLK_KHZ * 1000 / (ulVBs2BsCount / 10);
}

//--------------------------------------------------
// Description  : Get Current DP V Period
// Input Value  : None
// Output Value : V period in line
//--------------------------------------------------
WORD ScalerFreeSyncDpRx0GetVPeriod(void)
{
    DWORD ulVBs2BsCount = 0;
    WORD usHBs2BsCount = 0;

    // Pop up The result
    SET_DP_RX0_MEASURE_POP_UP();

    // VBs2BS count in GDI clk
    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));

    // HBs2Bs count in Link Clk / 2
    usHBs2BsCount = (((DWORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5C_MN_MEAS_HLN_L));

    // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
    return (ulVBs2BsCount * (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ);
}

//--------------------------------------------------
// Description  : Set Freesync AMD SPD info Vfreq max and min
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFreeSyncDpRx0GetSPDVfreqMaxMin(void)
{
    BYTE pucDPRSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];

#if(_DP_HDR10_SUPPORT == _ON)
    memcpy(pucDPRSV0Data, g_pucDPRx0RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
#else
    memset(pucDPRSV0Data, 0, sizeof(pucDPRSV0Data));

    ScalerDpRx0GetInfoFrameRSV0(pucDPRSV0Data);
#endif

    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        if(GET_DPRX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
        {
            // For IMD calculate DVtotal and BW when Freesync mode
            SET_DP_RX0_SPD_INFO_FRAME_RECEIVED();

            // Get DP DRR SPD Vmax
            g_usFREESYNCVFreq_max = (WORD)GET_DPRX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10;
            g_usFREESYNCVFreq_min = (WORD)GET_DPRX0_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10;
        }
        else
        {
            CLR_DP_RX0_SPD_INFO_FRAME_RECEIVED();

            g_usFREESYNCVFreq_max = _PANEL_FREESYNC_MAX_FRAME_RATE;
            g_usFREESYNCVFreq_min = _PANEL_FREESYNC_MIN_FRAME_RATE;
            DebugMessageRx0("DP DRR without SPD info", 0x00);
        }
    }
    else
    {
        CLR_DP_RX0_SPD_INFO_FRAME_RECEIVED();
    }

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    // Check AMD OUI
    if((pucDPRSV0Data[1] == 0x1A) && (pucDPRSV0Data[2] == 0x00) && (pucDPRSV0Data[3] == 0x00))
    {
        // For Freesync2 or HDR10 check receive, only check OUI
        SET_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED();
    }
    else
    {
        CLR_DP_RX0_AMD_SPD_INFO_FRAME_RECEIVED();
    }
#endif
}
#endif // End of #if(_D0_DP_EXIST == _ON)
#if(_D1_DP_EXIST == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerFreeSyncDpRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    BYTE pucDPRSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];
    bit bCheckFreeSync = _FALSE;

#if(_DP_HDR10_SUPPORT == _ON)
    memcpy(pucDPRSV0Data, g_pucDPRx1RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);

    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        bCheckFreeSync = _TRUE;
    }
#else
    memset(pucDPRSV0Data, 0, sizeof(pucDPRSV0Data));

    ScalerDpRx1GetInfoFrameRSV0(pucDPRSV0Data);

#if(_D1_DP_MAC_USE == _PAGEB8)
    if(ScalerGetByte(PB9_2C_DP_INFO_FM_RSV0) == _SPD_INFO_TYPE)
#elif(_D1_DP_MAC_USE == _PAGEB5)
    if(ScalerGetByte(PB6_2C_DP_INFO_FM_RSV0) == _SPD_INFO_TYPE)
#endif
    {
        bCheckFreeSync = _TRUE;
    }
#endif

    if(bCheckFreeSync == _TRUE)
    {
        // Check AMD OUI
        if((pucDPRSV0Data[1] == 0x1A) && (pucDPRSV0Data[2] == 0x00) && (pucDPRSV0Data[3] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return (((pucDPRSV0Data[6] & _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return (((pucDPRSV0Data[6] & _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return (((pucDPRSV0Data[6] & _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    if(((WORD)pucDPRSV0Data[7] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pucDPRSV0Data[7] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pucDPRSV0Data[7] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pucDPRSV0Data[7] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pucDPRSV0Data[7];
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    if(((WORD)pucDPRSV0Data[8] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pucDPRSV0Data[8] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pucDPRSV0Data[8] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pucDPRSV0Data[8] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pucDPRSV0Data[8];
                    break;

                default:
                    return 0x00;
                    break;
            }
        }

        return 0x00;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : DP BS to HS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
WORD ScalerFreeSyncDpRx1GetBStoHSDelay(WORD usDpHtotal)
{
    WORD usFifoOffset = 0;
    WORD usHStart = 0;
    WORD usHActive = 0;

    pData[15] = GET_COLOR_DEPTH();

    // DP fifo size = 256 x 96bit or 128 x 96bit
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (fifo size) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (fifo size) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

#if(_D1_DP_MAC_USE == _PAGEB8)
    // Get Hstart
    usHStart = (((WORD)ScalerGetByte(PB8_43_MN_DPF_HST_M) << 8) | (ScalerGetByte(PB8_44_MN_DPF_HST_L)));

    // Get Hactive
    usHActive = (((WORD)ScalerGetByte(PB8_45_MN_DPF_HWD_M) << 8) | (ScalerGetByte(PB8_46_MN_DPF_HWD_L)));

#elif(_D1_DP_MAC_USE == _PAGEB5)
    // Get Hstart
    usHStart = (((WORD)ScalerGetByte(PB5_43_MN_DPF_HST_M) << 8) | (ScalerGetByte(PB5_44_MN_DPF_HST_L)));

    // Get Hactive
    usHActive = (((WORD)ScalerGetByte(PB5_45_MN_DPF_HWD_M) << 8) | (ScalerGetByte(PB5_46_MN_DPF_HWD_L)));
#endif

    // De Only Mode HW constraint: BS2HS delay < Htotal => 1/2 FIFO < H Width, Enough Margin = 1/2 H Width
    if(usFifoOffset > (usHActive >> 1))
    {
        usFifoOffset = (usHActive >> 1);
    }

    // H Blanking = HTotal - HActive
    PDATA_WORD(0) = usDpHtotal - usHActive;

    // Set BS to HS delay to (HBlanking + 1/2 FIFO - HStart), BS2HS delay: 2 pixel mode
    return ((WORD)((PDATA_WORD(0) + usFifoOffset - usHStart) >> 1));
}

//--------------------------------------------------
// Description  : Get Current DP H Period
// Input Value  : None
// Output Value : H period in nano sec
//--------------------------------------------------
WORD ScalerFreeSyncDpRx1GetHPeriod(void)
{
    WORD usHBs2BsCount = 0;

    // Pop up The result
    SET_DP_RX1_MEASURE_POP_UP();

    // HBs2Bs count in Link Clk / 2
#if(_D1_DP_MAC_USE == _PAGEB8)
    usHBs2BsCount = (((WORD)ScalerGetByte(PB8_5B_MN_MEAS_HLN_M)) << 8) | (ScalerGetByte(PB8_5C_MN_MEAS_HLN_L));
#elif(_D1_DP_MAC_USE == _PAGEB5)
    usHBs2BsCount = (((WORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | (ScalerGetByte(PB5_5C_MN_MEAS_HLN_L));
#endif

    return (((DWORD)usHBs2BsCount * 1000) / (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2));
}

//--------------------------------------------------
// Description  : Get Current DP H Sync Width
// Input Value  : None
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerFreeSyncDpRx1GetHSW(void)
{
    WORD usHSWidth = 0;

#if(_D1_DP_MAC_USE == _PAGEB8)
    usHSWidth = ((((WORD)ScalerGetByte(PB8_47_MN_DPF_HSW_M) << 8) | (ScalerGetByte(PB8_48_MN_DPF_HSW_L))) & 0x7FFF);
#elif(_D1_DP_MAC_USE == _PAGEB5)
    usHSWidth = ((((WORD)ScalerGetByte(PB5_47_MN_DPF_HSW_M) << 8) | (ScalerGetByte(PB5_48_MN_DPF_HSW_L))) & 0x7FFF);
#endif

    return usHSWidth;
}

//--------------------------------------------------
// Description  : Get Current DP V Freq
// Input Value  : None
// Output Value : VFreq in 0.1Hz
//--------------------------------------------------
WORD ScalerFreeSyncDpRx1GetVFreq(void)
{
    DWORD ulVBs2BsCount = 0;

    // Pop up The result
    SET_DP_RX1_MEASURE_POP_UP();

#if(_D1_DP_MAC_USE == _PAGEB8)
    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));
#elif(_D1_DP_MAC_USE == _PAGEB5)
    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));
#endif

    return (DWORD)_GDI_CLK_KHZ * 1000 / (ulVBs2BsCount / 10);
}

//--------------------------------------------------
// Description  : Get Current DP V Period
// Input Value  : None
// Output Value : V period in line
//--------------------------------------------------
WORD ScalerFreeSyncDpRx1GetVPeriod(void)
{
    DWORD ulVBs2BsCount = 0;
    WORD usHBs2BsCount = 0;

    // Pop up The result
    SET_DP_RX1_MEASURE_POP_UP();

#if(_D1_DP_MAC_USE == _PAGEB8)

    // VBs2BS count in GDI clk
    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));

    // HBs2Bs count in Link Clk / 2
    usHBs2BsCount = (((DWORD)ScalerGetByte(PB8_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5C_MN_MEAS_HLN_L));

#elif(_D1_DP_MAC_USE == _PAGEB5)

    // VBs2BS count in GDI clk
    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB5_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB5_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5A_MN_MEAS_VLN_L)));

    // HBs2Bs count in Link Clk / 2
    usHBs2BsCount = (((DWORD)ScalerGetByte(PB5_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB5_5C_MN_MEAS_HLN_L));
#endif

    // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
    return (ulVBs2BsCount * (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ);
}

//--------------------------------------------------
// Description  : Set Freesync AMD SPD info Vfreq max and min
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFreeSyncDpRx1GetSPDVfreqMaxMin(void)
{
    BYTE pucDPRSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];

#if(_DP_HDR10_SUPPORT == _ON)
    memcpy(pucDPRSV0Data, g_pucDPRx1RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH);
#else
    memset(pucDPRSV0Data, 0, sizeof(pucDPRSV0Data));

    ScalerDpRx1GetInfoFrameRSV0(pucDPRSV0Data);
#endif

    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        if(GET_DPRX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
        {
            // For IMD calculate DVtotal and BW when Freesync mode
            SET_DP_RX1_SPD_INFO_FRAME_RECEIVED();

            // Get DP DRR SPD Vmax
            g_usFREESYNCVFreq_max = (WORD)GET_DPRX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10;
            g_usFREESYNCVFreq_min = (WORD)GET_DPRX1_AMD_SPD_INFO(_SPD_INFO_FREESYNC_MIN_VFREQ) * 10;
        }
        else
        {
            CLR_DP_RX1_SPD_INFO_FRAME_RECEIVED();

            g_usFREESYNCVFreq_max = _PANEL_FREESYNC_MAX_FRAME_RATE;
            g_usFREESYNCVFreq_min = _PANEL_FREESYNC_MIN_FRAME_RATE;
            DebugMessageRx1("DP DRR without SPD info", 0x00);
        }
    }
    else
    {
        CLR_DP_RX1_SPD_INFO_FRAME_RECEIVED();
    }

#if(_DP_ULTRA_HDR_SUPPORT == _ON)
    // Check AMD OUI
    if((pucDPRSV0Data[1] == 0x1A) && (pucDPRSV0Data[2] == 0x00) && (pucDPRSV0Data[3] == 0x00))
    {
        // For Freesync2 or HDR10 check receive, only check OUI
        SET_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
    }
    else
    {
        CLR_DP_RX1_AMD_SPD_INFO_FRAME_RECEIVED();
    }
#endif
}
#endif // End of #if(_D1_DP_EXIST == _ON)

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Switch DP FREESYNC Support
// Input Value  : Hotplug Type and FREESYNC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerFreeSyncDpSupportSwitch(EnumSourceSearchPort enumSourcePort, EnumFreeSyncSupport enumSupport)
{
    switch(enumSourcePort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            if(GET_DP_RX0_FREESYNC_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_RX0_FREESYNC_CAPABILITY_SWITCH();
                SET_DP_RX0_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if(GET_DP_RX1_FREESYNC_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_RX1_FREESYNC_CAPABILITY_SWITCH();
                SET_DP_RX1_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DP_PORT)
        case _D2_INPUT_PORT:

            if(GET_DP_RX2_FREESYNC_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_RX2_FREESYNC_CAPABILITY_SWITCH();
                SET_DP_RX2_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:

            if(GET_DP_RX6_FREESYNC_SUPPORT() != enumSupport)
            {
                SET_DP_RX_CAPABILITY_SWITCHED();
                SET_DP_RX6_FREESYNC_CAPABILITY_SWITCH();
                SET_DP_RX6_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

        default:
            break;
    }
}
#endif

#endif // End of #if(_DP_FREESYNC_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_HDMI_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if((_DEBUG_MESSAGE_SUPPORT == _OFF) &&\
    (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get HDMI FreeSync Support
// Input Value  : enumSourcePort
// Output Value : _FREESYNC_SUPPORT_ON/ _FREESYNC_SUPPORT_OFF
//--------------------------------------------------
EnumFreeSyncSupport ScalerFreeSyncHDMIGetFreeSyncSupport_EXINT1(EnumSourceSearchPort enumSourcePort) using 2
{
    EnumFreeSyncSupport enumFreeSyncSupport = _FREESYNC_SUPPORT_OFF;

    switch(enumSourcePort)
    {
        case _D0_INPUT_PORT:
            enumFreeSyncSupport = GET_TMDS_RX0_FREESYNC_SUPPORT();
            break;

        case _D1_INPUT_PORT:
            enumFreeSyncSupport = GET_TMDS_RX1_FREESYNC_SUPPORT();
            break;

        case _D2_INPUT_PORT:
            enumFreeSyncSupport = GET_TMDS_RX2_FREESYNC_SUPPORT();
            break;

        case _D3_INPUT_PORT:
            enumFreeSyncSupport = GET_TMDS_RX3_FREESYNC_SUPPORT();
            break;

        case _D4_INPUT_PORT:
            enumFreeSyncSupport = GET_TMDS_RX4_FREESYNC_SUPPORT();
            break;

        case _D5_INPUT_PORT:
            enumFreeSyncSupport = GET_TMDS_RX5_FREESYNC_SUPPORT();
            break;

        default:
            break;
    }

    return enumFreeSyncSupport;
}
#endif

#if(_HDMI_MAC_PAGE2_USE == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerFreeSyncHDMIRx0GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P2_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);

        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return ((ScalerGetDataPortBit(P2_CD_HDMI_PSAP, 0x95, _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return ((ScalerGetDataPortBit(P2_CD_HDMI_PSAP, 0x95, _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return ((ScalerGetDataPortBit(P2_CD_HDMI_PSAP, 0x95, _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:
                    ScalerGetDataPortByte(P2_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:
                    ScalerGetDataPortByte(P2_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx0("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                default:
                    return 0x00;
                    break;
            }
        }
    }

    return 0x00;
}
#endif

#if(_HDMI_MAC_PAGE71_USE == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerFreeSyncHDMIRx2GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, bit bD1Combo)
{
#if(_ERROR_PRONE_CODE == _TRUE)
    if(((GET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED() == _TRUE) && (bD1Combo == _ON)) ||
       ((GET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED() == _TRUE) && (bD1Combo == _OFF)))
#endif
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);

        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return ((ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x95, _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return ((ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x95, _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return ((ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x95, _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:
                    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:
                    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                default:
                    return 0x00;
                    break;
            }
        }
    }

    return 0x00;
}
#endif

#if(_HDMI_MAC_PAGE72_USE == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerFreeSyncHDMIRx3GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(GET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P72_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);

        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return ((ScalerGetDataPortBit(P72_CD_HDMI_PSAP, 0x95, _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return ((ScalerGetDataPortBit(P72_CD_HDMI_PSAP, 0x95, _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return ((ScalerGetDataPortBit(P72_CD_HDMI_PSAP, 0x95, _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:
                    ScalerGetDataPortByte(P72_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx3("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx3("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:
                    ScalerGetDataPortByte(P72_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx3("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx3("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                default:
                    return 0x00;
                    break;
            }
        }
    }

    return 0x00;
}
#endif

#if(_HDMI_MAC_PAGE73_USE == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerFreeSyncHDMIRx4GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P73_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);

        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return ((ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x95, _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return ((ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x95, _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return ((ScalerGetDataPortBit(P73_CD_HDMI_PSAP, 0x95, _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:
                    ScalerGetDataPortByte(P73_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx4("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx4("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:
                    ScalerGetDataPortByte(P73_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx4("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx4("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                default:
                    return 0x00;
                    break;
            }
        }
    }

    return 0x00;
}
#endif

#if(_HDMI_MAC_PAGE74_USE == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerFreeSyncHDMIRx5GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(GET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P74_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);

        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:
                    return ((ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x95, _BIT0) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ENABLE:
                    return ((ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x95, _BIT1) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_ACTIVE:
                    return ((ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x95, _BIT2) != 0x00) ? _ON : _OFF);
                    break;

                case _SPD_INFO_FREESYNC_MIN_VFREQ:
                    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                case _SPD_INFO_FREESYNC_MAX_VFREQ:
                    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];
                    break;

                default:
                    return 0x00;
                    break;
            }
        }
    }

    return 0x00;
}
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Switch DP FREESYNC Support
// Input Value  : Hotplug Type and FREESYNC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerFreeSyncHDMISupportSwitch(EnumSourceSearchPort enumSourcePort, EnumFreeSyncSupport enumSupport)
{
    switch(enumSourcePort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                break;
            }
#endif

            if(GET_TMDS_RX0_FREESYNC_SUPPORT() != enumSupport)
            {
                if(GET_D0_CABLE_STATUS() == _TRUE)
                {
                    SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                }

                SET_TMDS_RX0_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                break;
            }
#endif

            if(GET_TMDS_RX1_FREESYNC_SUPPORT() != enumSupport)
            {
                if(GET_D1_CABLE_STATUS() == _TRUE)
                {
                    SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                }

                SET_TMDS_RX1_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                break;
            }
#endif

            if(GET_TMDS_RX2_FREESYNC_SUPPORT() != enumSupport)
            {
                if(GET_D2_CABLE_STATUS() == _TRUE)
                {
                    SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                }

                SET_TMDS_RX2_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                break;
            }
#endif

            if(GET_TMDS_RX3_FREESYNC_SUPPORT() != enumSupport)
            {
                if(GET_D3_CABLE_STATUS() == _TRUE)
                {
                    SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                }

                SET_TMDS_RX3_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                break;
            }
#endif

            if(GET_TMDS_RX4_FREESYNC_SUPPORT() != enumSupport)
            {
                if(GET_D4_CABLE_STATUS() == _TRUE)
                {
                    SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                }

                SET_TMDS_RX4_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                break;
            }
#endif

            if(GET_TMDS_RX5_FREESYNC_SUPPORT() != enumSupport)
            {
                if(GET_D5_CABLE_STATUS() == _TRUE)
                {
                    SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
                }

                SET_TMDS_RX5_FREESYNC_SUPPORT(enumSupport);
            }

            break;
#endif

        default:
            break;
    }
}
#endif

#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)
#endif // End of #if(_HDMI_SUPPORT == _ON)
#endif // End of #if(_FREESYNC_SUPPORT == _ON)

