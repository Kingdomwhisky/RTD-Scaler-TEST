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
// ID Code      : RTD2014OsdFontProp.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFONTPROP__

#include "UserCommonInclude.h"
#include "RTD2014OsdTextTableBody.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#ifndef _OSD_FONT_MODE_FORCE_256_511
#define _OSD_FONT_MODE_FORCE_256_511                _ON
#endif
#define GET_OSD_INFO_MAP_FONT_BASE_ADDRESS()        g_usFontTableStart

#define GET_OSD_INFO_FONT_POINTER_0()               g_ucFontPointer0
#define GET_OSD_INFO_FONT_POINTER_1()               g_ucFontPointer1
#define GET_OSD_INFO_FONT_POINTER_2()               g_ucFontPointer2

#define SET_OSD_INFO_FONT_POINTER_0(x)              g_ucFontPointer0 = (x)
#define SET_OSD_INFO_FONT_POINTER_1(x)              g_ucFontPointer1 = (x)
#define SET_OSD_INFO_FONT_POINTER_2(x)              g_ucFontPointer2 = (x)

#if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_1)
#define _OSD_MODE_BYTE0                             0x8C
#define _OSD_MODE_BYTE0_256_511                     0x2C
#elif(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_2)
#define _OSD_MODE_BYTE0                             0x4C
#define _OSD_MODE_BYTE0_256_511                     0x6C
#endif // End of #if(_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_1)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
WORD code tSTRING_RESOLUTION_TABLE[][6]=
{
    {   _,   _,   _,   _,   _,   _},
    { 240, _4_, _8_, _0_, _i_,   _},
    { 480, _4_, _8_, _0_, _p_,   _},
    { 288, _5_, _7_, _6_, _i_,   _},
    { 576, _5_, _7_, _6_, _p_,   _},
    { 720, _7_, _2_, _0_, _p_,   _},
    { 540, _1_, _0_, _8_, _0_, _i_},
    {1080, _1_, _0_, _8_, _0_, _p_},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE *g_pucShowNumberAddress;
BYTE g_pucModeInfoData[28];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
void OsdPropGetShowInputPortStringAddress(BYTE ucInputPort);
void OsdPropGetShowVFreqStringAddress(void);
void OsdPropGetShowHFreqPClkStringAddress(void);



#if(_DIGITAL_PORT_SUPPORT == _ON)
void OsdPropGetShowHDCPEnable(BYTE ucVersion);
#endif
void OsdPropGetShowResolutionStringAddress(void);
#if(_FREESYNC_SUPPORT == _ON)
void OsdPropShowFreeSyncVFreqRange(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor, BYTE ucLanguage);
#endif
#if(_DP_DEBUG_MSG == _ON)
void OsdPropGetShowDpInfoStringAddress(BYTE Index);
#endif

BYTE OsdPropGetFontPointer(BYTE ucPointerSelect);
BYTE OsdPropVideoResolution(void);
BYTE OsdPropSetFontPointer(BYTE ucPointerSelect, BYTE ucPointer);
void OsdPropFontDataToSram(BYTE ucFptsSelect, BYTE *ucpArray, BYTE ucRotateType);

void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
BYTE *OsdPropGetStringTableAddress(BYTE ucString);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowInputPortStringAddress(BYTE ucInputPort)
{
    BYTE ucI = 0;

    if(ucInputPort == _A0_PORT)
    {
        g_pucModeInfoData[0] = _A_;
        g_pucModeInfoData[1] = _0_;
    }
    else
    {
        g_pucModeInfoData[0] = _D_;
        g_pucModeInfoData[1] = (ucInputPort - _D0_PORT) + _0_;
    }

    switch(ucInputPort)
    {
        case _A0_PORT:
            ucI = _A0_INPUT_TYPE;
            break;
        case _D0_PORT:
            ucI = _D0_INPUT_TYPE;
            break;
        case _D1_PORT:
            ucI = _D1_INPUT_TYPE;
            break;
        case _D2_PORT:
            ucI = _D2_INPUT_TYPE;
            break;
        case _D3_PORT:
            ucI = _D3_INPUT_TYPE;
            break;
        case _D4_PORT:
            ucI = _D4_INPUT_TYPE;
            break;
        case _D5_PORT:
            ucI = _D5_INPUT_TYPE;
            break;
        case _D6_PORT:
            ucI = _D6_INPUT_TYPE;
            break;

        default:
            break;
    }

    g_pucModeInfoData[2] = _COLON_;

    switch(ucI)
    {
        case _ICON_INPUT_VGA:
            g_pucModeInfoData[3] = _;
            g_pucModeInfoData[4] = _V_;
            g_pucModeInfoData[5] = _G_;
            g_pucModeInfoData[6] = _A_;
            g_pucModeInfoData[7] = _END_;
            break;


        case _ICON_INPUT_DVI:
            g_pucModeInfoData[3] = _;
            g_pucModeInfoData[4] = _D_;
            g_pucModeInfoData[5] = _V_;
            g_pucModeInfoData[6] = _I_;
            g_pucModeInfoData[7] = _END_;
            break;


        case _ICON_INPUT_HDMI:
            g_pucModeInfoData[3] = _;
            g_pucModeInfoData[4] = _H_;
            g_pucModeInfoData[5] = _D_;
            g_pucModeInfoData[6] = _M_;
            g_pucModeInfoData[7] = _I_;
            g_pucModeInfoData[8] = _END_;
            break;

        case _ICON_INPUT_DP:
            g_pucModeInfoData[3] = _;
            g_pucModeInfoData[4] = _D_;
            g_pucModeInfoData[5] = _P_;
            g_pucModeInfoData[6] = _;
            g_pucModeInfoData[7] = _END_;
            break;

        case _ICON_INPUT_MHL:
            g_pucModeInfoData[3] = _;
            g_pucModeInfoData[4] = _M_;
            g_pucModeInfoData[5] = _H_;
            g_pucModeInfoData[6] = _L_;
            g_pucModeInfoData[7] = _END_;
            break;

        case _ICON_INPUT_NO_PORT:
            g_pucModeInfoData[3] = _;
            g_pucModeInfoData[4] = _N_;
            g_pucModeInfoData[5] = _O_;
            g_pucModeInfoData[6] = _N_;
            g_pucModeInfoData[7] = _E_;
            g_pucModeInfoData[8] = _END_;
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
BYTE *OsdPropGetShowPixelClockStringAddress(void)
{
    BYTE ucI = 0;
    WORD usFreq = ScalerSyncGetInputPixelClk();

    g_pucModeInfoData[0] = _P_;
    g_pucModeInfoData[1] = _C_;
    g_pucModeInfoData[2] = _L_;
    g_pucModeInfoData[3] = _K_;
    g_pucModeInfoData[4] = _COLON_;
    g_pucModeInfoData[5] = ___;
    g_pucModeInfoData[6] = ___;

    ucI = 10;

    while(_TRUE)
    {
        if(ucI == 9)
        {
            g_pucModeInfoData[ucI] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usFreq % 10 + _0_;
            usFreq /= 10;
        }

        if(usFreq <= 0)
        {
            break;
        }
        ucI--;
    }

    g_pucModeInfoData[11] = _M_;
    g_pucModeInfoData[12] = _H_;
    g_pucModeInfoData[13] = _z_;
    g_pucModeInfoData[14] = _END_;

    return g_pucModeInfoData;
}
*/
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowVFreqStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = 0;

    usTemp = GET_INPUT_TIMING_VFREQ();

    g_pucModeInfoData[0] = _V_;
    g_pucModeInfoData[1] = _COLON_;
    g_pucModeInfoData[2] = _;

    ucI = 6;

    while(_TRUE)
    {
        if(ucI == 5)
        {
            g_pucModeInfoData[5] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;
        }

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }
    g_pucModeInfoData[7] = _H_;
    g_pucModeInfoData[8] = _z_;
    g_pucModeInfoData[9] = _END_;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowHFreqPClkStringAddress(void)
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    WORD usFreq = ScalerSyncGetInputPixelClk();
    WORD usTemp = GET_INPUT_TIMING_HFREQ();

    g_pucModeInfoData[0] = _H_;
    g_pucModeInfoData[1] = _COLON_;
    g_pucModeInfoData[2] = _;

    ucI = 6;

    while(_TRUE)
    {
        if(ucI == 5)
        {
            g_pucModeInfoData[5] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;
        }

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }

    g_pucModeInfoData[7] = _K_;
    g_pucModeInfoData[8] = _H_;
    g_pucModeInfoData[9] = _z_;

    g_pucModeInfoData[10] = _;
    g_pucModeInfoData[11] = _;
    g_pucModeInfoData[12] = _;

    g_pucModeInfoData[13] = _P_;
    g_pucModeInfoData[14] = _C_;
    g_pucModeInfoData[15] = _L_;
    g_pucModeInfoData[16] = _K_;
    g_pucModeInfoData[17] = _COLON_;
    g_pucModeInfoData[18] = _;
    g_pucModeInfoData[19] = _;

    ucJ = 23;

    while(_TRUE)
    {
        if(ucJ == 22)
        {
            g_pucModeInfoData[ucJ] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucJ] = usFreq % 10 + _0_;
            usFreq /= 10;
        }

        if(usFreq <= 0)
        {
            break;
        }
        ucJ--;
    }

    g_pucModeInfoData[24] = _M_;
    g_pucModeInfoData[25] = _H_;
    g_pucModeInfoData[26] = _z_;
    g_pucModeInfoData[27] = _END_;

    //return g_pucModeInfoData;
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowHDCPEnable(BYTE ucVersion)
{
    g_pucModeInfoData[0] = _H_;
    g_pucModeInfoData[1] = _D_;
    g_pucModeInfoData[2] = _C_;
    g_pucModeInfoData[3] = _P_;
    g_pucModeInfoData[4] = _;

    if(ucVersion == _OFF)
    {
        g_pucModeInfoData[5] = _D_;
        g_pucModeInfoData[6] = _i_;
        g_pucModeInfoData[7] = _s_;
        g_pucModeInfoData[8] = _a_;
        g_pucModeInfoData[9] = _b_;
        g_pucModeInfoData[10] = _l_;
        g_pucModeInfoData[11] = _e_;
        g_pucModeInfoData[12] = _d_;
        g_pucModeInfoData[13] = _END_;
    }
    else
    {
        if((ucVersion & 0x7F) == 0x14)
        {
            g_pucModeInfoData[5] = _1_;
            g_pucModeInfoData[6] = _DOT_;
            g_pucModeInfoData[7] = _4_;
            g_pucModeInfoData[8] = _;

        }
        else if((ucVersion & 0x7F) == 0x22)
        {
            g_pucModeInfoData[5] = _2_;
            g_pucModeInfoData[6] = _DOT_;
            g_pucModeInfoData[7] = _2_;
            g_pucModeInfoData[8] = _;
        }
        g_pucModeInfoData[9] = _E_;
        g_pucModeInfoData[10] = _n_;
        g_pucModeInfoData[11] = _a_;
        g_pucModeInfoData[12] = _b_;
        g_pucModeInfoData[13] = _l_;
        g_pucModeInfoData[14] = _e_;
        g_pucModeInfoData[15] = _d_;

        if((ucVersion & 0x80) == 0x80)
        {
            g_pucModeInfoData[16] = _;
            g_pucModeInfoData[17] = _R_;
            g_pucModeInfoData[18] = _e_;
            g_pucModeInfoData[19] = _p_;
            g_pucModeInfoData[20] = _e_;
            g_pucModeInfoData[21] = _a_;
            g_pucModeInfoData[22] = _t_;
            g_pucModeInfoData[23] = _e_;
            g_pucModeInfoData[24] = _r_;
            g_pucModeInfoData[25] = _END_;
        }
        else
        {
            g_pucModeInfoData[16] = _;
            g_pucModeInfoData[17] = _S_;
            g_pucModeInfoData[18] = _i_;
            g_pucModeInfoData[19] = _n_;
            g_pucModeInfoData[20] = _k_;
            g_pucModeInfoData[21] = _END_;
        }
    }
    //return g_pucModeInfoData;
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowResolutionStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = OsdPropVideoResolution();

    if(ucI != 0)
    {
        g_pucModeInfoData[0] = tSTRING_RESOLUTION_TABLE[ucI][1];
        g_pucModeInfoData[1] = tSTRING_RESOLUTION_TABLE[ucI][2];
        g_pucModeInfoData[2] = tSTRING_RESOLUTION_TABLE[ucI][3];
        g_pucModeInfoData[3] = tSTRING_RESOLUTION_TABLE[ucI][4];
        g_pucModeInfoData[4] = tSTRING_RESOLUTION_TABLE[ucI][5];
        // g_pucModeInfoData[5] = _END_;

        g_pucModeInfoData[5] = _AT_0_;
        g_pucModeInfoData[6] = _AT_1_;

        usTemp = GET_INPUT_TIMING_VFREQ();

        ucI = 8;
        g_pucModeInfoData[9] = _DOT_;
        g_pucModeInfoData[10] = usTemp % 10 + _0_;
        g_pucModeInfoData[11] = _H_;
        g_pucModeInfoData[12] = _z_;
        g_pucModeInfoData[13] = _END_;

        usTemp /= 10;

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }
    }
    else
    {
        if(GET_INPUT_TIMING_HWIDTH() >= 1000)
        {
            ucI = 3;
        }
        else
        {
            ucI = 2;
        }

        usTemp = GET_INPUT_TIMING_HWIDTH();
        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }

        if(GET_INPUT_TIMING_HWIDTH() >= 1000)
        {
            g_pucModeInfoData[4] = _x_;
        }
        else
        {
            g_pucModeInfoData[3] = _x_;
        }

        usTemp = GET_INPUT_TIMING_VHEIGHT();

        if((GET_INPUT_TIMING_HWIDTH() >= 1000) && (GET_INPUT_TIMING_VHEIGHT() >= 1000))
        {
            ucI = 8;
            g_pucModeInfoData[9] = _AT_0_;
            g_pucModeInfoData[10] = _AT_1_;

        }
        else if((GET_INPUT_TIMING_HWIDTH() < 1000) && (GET_INPUT_TIMING_VHEIGHT() < 1000))
        {
            ucI = 6;
            g_pucModeInfoData[7] = _AT_0_;
            g_pucModeInfoData[8] = _AT_1_;
        }
        else
        {
            ucI = 7;
            g_pucModeInfoData[8] = _AT_0_;
            g_pucModeInfoData[9] = _AT_1_;
        }

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }

        usTemp = GET_INPUT_TIMING_VFREQ();

        if((GET_INPUT_TIMING_HWIDTH() >= 1000) && (GET_INPUT_TIMING_VHEIGHT() >= 1000))
        {
            ucI = 12;
        }
        else if((GET_INPUT_TIMING_HWIDTH() < 1000) && (GET_INPUT_TIMING_VHEIGHT() < 1000))
        {
            ucI = 10;
        }
        else
        {
            ucI = 11;
        }

        // Modify V freq. string position for V freq. > 100Hz
        if(usTemp >= 1000)
        {
            ++ucI;
        }

        g_pucModeInfoData[ucI + 1] = _DOT_;
        g_pucModeInfoData[ucI + 2] = (usTemp % 10) + _0_;
        g_pucModeInfoData[ucI + 3] = _H_;
        g_pucModeInfoData[ucI + 4] = _z_;
        g_pucModeInfoData[ucI + 5] = _END_;

        usTemp /= 10;

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }
    }

    //return g_pucModeInfoData;
}
#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowFreeSyncVFreqRange(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucColor, BYTE ucLanguage)
{
    WORD usTemp = 0;
    BYTE ucI = 0;

    usTemp = ScalerFreeSyncGetFreeSyncInfo(SysSourceGetInputPort(), _SPD_INFO_FREESYNC_MIN_VFREQ);

    if(usTemp == 0)
    {
        usTemp = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
    }

    g_pucModeInfoData[0] = _F_;
    g_pucModeInfoData[1] = _r_;
    g_pucModeInfoData[2] = _e_;
    g_pucModeInfoData[3] = _e_;
    g_pucModeInfoData[4] = _S_;
    g_pucModeInfoData[5] = _y_;
    g_pucModeInfoData[6] = _n_; // clear
    g_pucModeInfoData[7] = _c_; // clear
    g_pucModeInfoData[8] = _; // clear
    g_pucModeInfoData[9] = _R_;
    g_pucModeInfoData[10] = _a_;
    g_pucModeInfoData[11] = _n_;
    g_pucModeInfoData[12] = _g_;
    g_pucModeInfoData[13] = _e_;
    g_pucModeInfoData[14] = _COLON_;
    g_pucModeInfoData[15] = _;
    g_pucModeInfoData[16] = _; // clear
    g_pucModeInfoData[17] = _; // clear
    g_pucModeInfoData[18] = _; // clear
    ucI = 18;

    while(_TRUE)
    {
        g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
        usTemp /= 10;

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }

    usTemp = ScalerFreeSyncGetFreeSyncInfo(SysSourceGetInputPort(), _SPD_INFO_FREESYNC_MAX_VFREQ);

    if(usTemp == 0)
    {
        usTemp = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
    }

    g_pucModeInfoData[19] = _SLINE_;
    g_pucModeInfoData[20] = _; // clear
    g_pucModeInfoData[21] = _; // clear
    g_pucModeInfoData[22] = _; // clear
    g_pucModeInfoData[23] = _; // clear
    ucI = 23;

    while(_TRUE)
    {
        g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
        usTemp /= 10;

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }
    g_pucModeInfoData[24] = _H_;
    g_pucModeInfoData[25] = _z_;
    g_pucModeInfoData[26] = _END_;
    OsdPropPutString(ucRow, ucCol, ucFptsSelect, _STRING_FREESYNC_SUPPORT_V_RANGE,  ucColor,  ucLanguage);
}
#endif
#if(_DP_DEBUG_MSG == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropGetShowDpInfoStringAddress(BYTE Index)
{
    BYTE ucI = 0;
    BYTE ucIndex = 0;
    EnumSourceSearchPort ucPortSel = SysSourceGetInputPort();
    if(SysModeGetModeState() != _MODE_STATUS_ACTIVE)
    {
        ucPortSel = GET_OSD_POWER_SAVING_SHOW_DP_INFO_PORT();

        if(Index == _STRING_DP_INFO)
        {
            g_pucModeInfoData[ucIndex++] = _P_;
            g_pucModeInfoData[ucIndex++] = _W_0;
            g_pucModeInfoData[ucIndex++] = _W_1;
            g_pucModeInfoData[ucIndex++] = _COLON_;
            g_pucModeInfoData[ucIndex++] = _0_ + ScalerDpGetPowerStatus(ucPortSel);
            g_pucModeInfoData[ucIndex++] = _COMMA_;
        }
    }

    if(Index == _STRING_DP_INFO)
    {
        switch(ScalerDpGetLaneCount(ucPortSel))
        {
            case _DP_LINK_1_LANE:
                g_pucModeInfoData[ucIndex++] = _1_;
                break;
            case _DP_LINK_2_LANE:
                g_pucModeInfoData[ucIndex++] = _2_;
                break;
            case _DP_LINK_4_LANE:
                g_pucModeInfoData[ucIndex++] = _4_;
                break;
            default:
                g_pucModeInfoData[ucIndex++] = _0_;
                break;
        }
        g_pucModeInfoData[ucIndex++] = _L_;
        g_pucModeInfoData[ucIndex++] = _a_;
        g_pucModeInfoData[ucIndex++] = _n_;
        g_pucModeInfoData[ucIndex++] = _e_;
        switch(ScalerDpGetLinkRate(ucPortSel))
        {
            case _DP_LINK_RBR:
                g_pucModeInfoData[ucIndex++] = _R_;
                g_pucModeInfoData[ucIndex++] = _B_;
                g_pucModeInfoData[ucIndex++] = _R_;
                break;
            case _DP_LINK_HBR:
                g_pucModeInfoData[ucIndex++] = _H_;
                g_pucModeInfoData[ucIndex++] = _B_;
                g_pucModeInfoData[ucIndex++] = _R_;
                break;
            case _DP_LINK_HBR2:
                g_pucModeInfoData[ucIndex++] = _H_;
                g_pucModeInfoData[ucIndex++] = _B_;
                g_pucModeInfoData[ucIndex++] = _R_;
                g_pucModeInfoData[ucIndex++] = _2_;
                break;
             default:
                g_pucModeInfoData[ucIndex++] = _X_;
                g_pucModeInfoData[ucIndex++] = _X_;
                g_pucModeInfoData[ucIndex++] = _X_;
                g_pucModeInfoData[ucIndex++] = _X_;
                break;
        }

        g_pucModeInfoData[ucIndex++] = _COMMA_;
    }
    else if(Index == _STRING_DP_INFO_2)
    {
        g_pucModeInfoData[ucIndex++] = _S_;
        g_pucModeInfoData[ucIndex++] = _w_0;
        g_pucModeInfoData[ucIndex++] = _w_1;
        g_pucModeInfoData[ucIndex++] = _i_;
        g_pucModeInfoData[ucIndex++] = _n_;
        g_pucModeInfoData[ucIndex++] = _g_;
        g_pucModeInfoData[ucIndex++] = _;
        for(ucI=_DP_LANE_0 ; ucI<=_DP_LANE_3 ;ucI++)
        {
            g_pucModeInfoData[ucIndex++] = _LEFT_BRACE_;
            switch(ScalerDpGetLaneVoltageSwingLv(ucPortSel,ucI))
            {
                case _DP_LINK_VOLTAGE_SWING_LEVEL_0:
                    g_pucModeInfoData[ucIndex++] = _0_+0;
                    break;
                case _DP_LINK_VOLTAGE_SWING_LEVEL_1:
                    g_pucModeInfoData[ucIndex++] = _0_+1;
                    break;
                case _DP_LINK_VOLTAGE_SWING_LEVEL_2:
                    g_pucModeInfoData[ucIndex++] = _0_+2;
                    break;
                case _DP_LINK_VOLTAGE_SWING_LEVEL_3:
                    g_pucModeInfoData[ucIndex++] = _0_+3;
                    break;
                default:
                break;
            }
            g_pucModeInfoData[ucIndex++] = _COMMA_;
            switch(ScalerDpGetLanePreEmpLv(ucPortSel,ucI))
            {
                case _DP_LINK_PREEMPHASIS_LEVEL_0:
                    g_pucModeInfoData[ucIndex++] = _0_+0;
                    break;
                case _DP_LINK_PREEMPHASIS_LEVEL_1:
                    g_pucModeInfoData[ucIndex++] = _0_+1;
                    break;
                case _DP_LINK_PREEMPHASIS_LEVEL_2:
                    g_pucModeInfoData[ucIndex++] = _0_+2;
                    break;
                case _DP_LINK_PREEMPHASIS_LEVEL_3:
                    g_pucModeInfoData[ucIndex++] = _0_+2;
                    break;
                default:
                break;
            }
            g_pucModeInfoData[ucIndex++] = _RIGHT_BRACE_;
        }
    }

    g_pucModeInfoData[ucIndex++] = _END_;

    //return g_pucModeInfoData;
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropGetFontPointer(BYTE ucPointerSelect)
{
    BYTE ucPointer = 0;

    if(ucPointerSelect == _PFONT_PAGE_0)
    {
        ucPointer = GET_OSD_INFO_FONT_POINTER_0();
    }
    else if(ucPointerSelect == _PFONT_PAGE_1)
    {
        ucPointer = GET_OSD_INFO_FONT_POINTER_1();
    }
    else if(ucPointerSelect == _PFONT_PAGE_2)
    {
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_1)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_1);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_2)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_2);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_3)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_3);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_4)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_4);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_5)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_5);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_6)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_6);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_7)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_7);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_8)
    {
        SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_8);
        ucPointer = GET_OSD_INFO_FONT_POINTER_2();
    }
    else if(ucPointerSelect == _PFONT_PAGE_INFORMATION)
    {
        ucPointer = GET_OSD_INFO_FONT_POINTER_1();
    }

    return ucPointer;
}


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropVideoResolution(void)
{
    bit bVideoTiming = _FALSE;
    BYTE ucI = 0;

    if(GET_INPUT_TIMING_VFREQ() > 620)
    {
        return _FALSE;
    }

    if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
    {
        bVideoTiming = _TRUE;
    }
#if(_VGA_SUPPORT == _ON)
    else if(SysSourceGetSourceType() == _SOURCE_VGA)
    {
        if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_YPBPR)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif
#if(_DVI_SUPPORT == _ON)
    else if((SysSourceGetSourceType() == _SOURCE_DVI))
    {
#if(_DIGITAL_PORT_SUPPORT == _ON)
        if(ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort()) == _HDCP_NONE)
        {
            bVideoTiming = _FALSE;
        }
        else
        {
            bVideoTiming = _TRUE;
        }
#endif
    }
#endif
#if(_HDMI_SUPPORT == _ON)
    else if(SysSourceGetSourceType() == _SOURCE_HDMI)
    {
        if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _FALSE)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif
#if(_DP_SUPPORT == _ON)
    else if(SysSourceGetSourceType() == _SOURCE_DP)
    {
        if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace()) == _FALSE)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif

    if(bVideoTiming == _TRUE)
    {
        for(ucI = 1; ucI < 8; ucI++)
        {
            if(GET_INPUT_TIMING_VHEIGHT() == tSTRING_RESOLUTION_TABLE[ucI][0])
            {
                if((tSTRING_RESOLUTION_TABLE[ucI][0] == 480) && (GET_INPUT_TIMING_HWIDTH() == 848))
                {
                    return _FALSE;
                }

                if(((tSTRING_RESOLUTION_TABLE[ucI][0] == 240) ||
                    (tSTRING_RESOLUTION_TABLE[ucI][0] == 288) ||
                    (tSTRING_RESOLUTION_TABLE[ucI][0] == 540)) &&
                   (GET_INPUT_TIMING_INTERLACE_FLG() == _FALSE))
                {
                    return _FALSE;
                }

                return ucI;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropSetFontPointer(BYTE ucPointerSelect, BYTE ucPointer)
{
    ucPointer++;

    if(ucPointerSelect == _PFONT_PAGE_0)
    {
        if(ucPointer > _OSD_PAGE_0_END)
        {
            ucPointer = _OSD_PAGE_0_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_1)
    {
        if(ucPointer > _OSD_PAGE_1_END)
        {
            ucPointer = _OSD_PAGE_1_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_2)
    {
        if(ucPointer > _OSD_PAGE_2_END)
        {
            ucPointer = _OSD_PAGE_2_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_1)
    {
        if(ucPointer > _SUB_PAGE_ITEM_1_END)
        {
            ucPointer = _SUB_PAGE_ITEM_1;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_2)
    {
        if(ucPointer > _SUB_PAGE_ITEM_2_END)
        {
            ucPointer = _SUB_PAGE_ITEM_2;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_3)
    {
        if(ucPointer > _SUB_PAGE_ITEM_3_END)
        {
            ucPointer = _SUB_PAGE_ITEM_3;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_4)
    {
        if(ucPointer > _SUB_PAGE_ITEM_4_END)
        {
            ucPointer = _SUB_PAGE_ITEM_4;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_5)
    {
        if(ucPointer > _SUB_PAGE_ITEM_5_END)
        {
            ucPointer = _SUB_PAGE_ITEM_5;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_6)
    {
        if(ucPointer > _SUB_PAGE_ITEM_6_END)
        {
            ucPointer = _SUB_PAGE_ITEM_6;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_7)
    {
        if(ucPointer > _SUB_PAGE_ITEM_7_END)
        {
            ucPointer = _SUB_PAGE_ITEM_7;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_8)
    {
        if(ucPointer > _SUB_PAGE_ITEM_8_END)
        {
            ucPointer = _SUB_PAGE_ITEM_8;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_INFORMATION)
    {
        if(ucPointer > _OSD_PAGE_INFORMATION_END)
        {
            ucPointer = _OSD_PAGE_INFORMATION_START;
        }
    }

    return ucPointer;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropFontDataToSram(BYTE ucFptsSelect, BYTE *ucpArray, BYTE ucRotateType)
{
    if(ucFptsSelect == _PFONT_PAGE_0)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_0() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_0() >= _OSD_PAGE_0_END)
        {
            SET_OSD_INFO_FONT_POINTER_0(_OSD_PAGE_0_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_0(GET_OSD_INFO_FONT_POINTER_0() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_1)
    {

        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_1() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_1() >= _OSD_PAGE_1_END)
        {
            SET_OSD_INFO_FONT_POINTER_1(_OSD_PAGE_1_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_1(GET_OSD_INFO_FONT_POINTER_1() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_2)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _OSD_PAGE_2_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_OSD_PAGE_2_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_1)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_1_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_1);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_2)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_2_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_2);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_3)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_3_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_3);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_4)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_4_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_4);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_5)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_5_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_5);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_6)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_6_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_6);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_7)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_7_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_7);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_ITEM_8)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_2() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_2() >= _SUB_PAGE_ITEM_8_END)
        {
            SET_OSD_INFO_FONT_POINTER_2(_SUB_PAGE_ITEM_8);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_2(GET_OSD_INFO_FONT_POINTER_2() + 1);
        }
    }
    else if(ucFptsSelect == _PFONT_PAGE_INFORMATION)
    {
        ScalerOsdHardwareCompression(ucpArray, 27, GET_CURRENT_BANK_NUMBER(), (GET_OSD_INFO_FONT_POINTER_1() + 256 * _OSD_FONT_MODE_FORCE_256_511) , GET_OSD_INFO_MAP_FONT_BASE_ADDRESS(), ucRotateType, _BURSTWRITE_FROM_XRAM);

        if(GET_OSD_INFO_FONT_POINTER_1() >= _OSD_PAGE_INFORMATION_END)
        {
            SET_OSD_INFO_FONT_POINTER_1(_OSD_PAGE_INFORMATION_START);
        }
        else
        {
            SET_OSD_INFO_FONT_POINTER_1(GET_OSD_INFO_FONT_POINTER_1() + 1);
        }
    }
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage)
{
    BYTE *pucArray = OsdPropGetStringTableAddress(ucString);
    bit bCenterFlag = _FALSE;
    bit bNextLineFlag = _FALSE;
    BYTE pucpTemp[27] = {0};
    BYTE ucElementCount = 0;
    BYTE ucColBackup = ucCol;

    pData[0] = ucLanguage;
    while(pData[0] != 0)
    {
        if(pucArray[0] == _END_)
        {
            pData[0]--;
        }
        pucArray++;
    }

    do
    {
        bNextLineFlag = _FALSE;
        memset(pData, 0x00, _DATA_ITEM_LENGTH);
        ucElementCount = 0;

        PDATA_WORD(5) = OsdPropGetFontPointer(ucFptsSelect);

        if(GET_OSD_INFO_STRING_MODE_LENGTH() != 0)
        {
            while((*(pucArray + ucElementCount) != _END_) &&
                  (*(pucArray + ucElementCount) != _NEXT_LINE))// calculate totwl string width
            {
                pData[2] = *(pucArray + ucElementCount);

                switch(pData[2])
                {
                    default:
                        PDATA_WORD(6) = 0;
                        break;

                    case _FONT_SELECT_EXT1:
                        PDATA_WORD(6) = _FONT_SELECT_OFFSET1;
                        break;

                    case _FONT_SELECT_EXT2:
                        PDATA_WORD(6) = _FONT_SELECT_OFFSET2;
                        break;

                    //if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                    /*case _FONT_SELECT_EXT3:
                        PDATA_WORD(6) = _FONT_SELECT_OFFSET3;
                        break;*/
                }

                if(PDATA_WORD(6) != 0)
                {
                    ucElementCount++;
                    pData[2] = *(pucArray + ucElementCount);
                }

                if((PDATA_WORD(6) + pData[2]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                {
                    pData[1] += tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[2] + PDATA_WORD(6)];
                }
                else
                {
                    pData[1] += tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                }

                ucElementCount++;
            }

            // String col size
            pData[0] = (pData[1] / 12) + (((pData[1] % 12) > 0) ? 1 : 0); // total pixels / 12 (round up)

            if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)// center-aligned
            {
                // add one font if centered width and actual sting width is not both even or both odd
                if((((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 0) && ((pData[0] % 2) == 1)) ||
                   (((GET_OSD_INFO_STRING_MODE_LENGTH() % 2) == 1) && ((pData[0] % 2) == 0)))
                {
                    pData[0]++;
                }

                pData[9] = ((pData[0] * 12) - pData[1]) / 2;// total center-aligned pixels - total string pixels / 2
            }
            else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)// right aligned
            {
                pData[9] = (pData[0] * 12) - pData[1];// count right-aligned pixels
            }

            if(pData[9] != 0)// left-aligned
            {
                bCenterFlag = _TRUE;
            }
        }
        ucElementCount = pData[1] = pData[0] = 0;

        // reorder
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT6);
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~(_BIT7 | _BIT5)));

        while((*(pucArray + ucElementCount) != _END_) &&
              (*(pucArray + ucElementCount) != _NEXT_LINE))
        {
            switch(*(pucArray + ucElementCount))
            {
                case _END_:
                    break;

                default:
                    if(pData[5] == 0)// pixel count = 0 ????
                    {
                        pData[2] = *(pucArray + ucElementCount);

                        if(pData[2] == _FONT_BLANK_PIXEL)
                        {
                            pData[5] = *(pucArray + ucElementCount + 1);

                            pData[2] = _;
                        }

                        if(bCenterFlag == _TRUE)
                        {
                            pData[2] = _;
                        }
                    }
                    else
                    {
                        pData[2] = _;
                    }

                    switch(pData[2])
                    {
                        default:
                            PDATA_WORD(6) = 0;
                            break;

                        case _FONT_SELECT_EXT1:
                            PDATA_WORD(6) = _FONT_SELECT_OFFSET1;
                            break;

                        case _FONT_SELECT_EXT2:
                            PDATA_WORD(6) = _FONT_SELECT_OFFSET2;
                            break;

                        //if _FONT_SELECT_EXT"N" is defined in XXXOsdTextTableDefine.h, new case should be added, for example
                        /*case _FONT_SELECT_EXT3:
                            PDATA_WORD(6) = _FONT_SELECT_OFFSET3;
                            break;*/
                    }

                    if(PDATA_WORD(6) != 0)
                    {
                        ucElementCount++;
                        pData[2] = *(pucArray + ucElementCount);
                    }

                    if((PDATA_WORD(6) + pData[2]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[2] + PDATA_WORD(6)];

                            if(bCenterFlag == _TRUE)
                            {
                                pData[3] = pData[9];
                            }
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                            pData[5] -= pData[3];
                        }
                    }
                    else
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];

                            if(bCenterFlag == _TRUE)
                            {
                                pData[3] = pData[9];
                            }
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                            pData[5] -= pData[3];
                        }
                    }

                    if(pData[5] == 0)
                    {
                        if((*(pucArray + ucElementCount) != _FONT_BLANK_PIXEL))
                        {
                            ucElementCount++;

                            if(bCenterFlag == _TRUE)
                            {
                                ucElementCount = 0;
                            }
                        }
                        else
                        {
                            ucElementCount += 2;
                        }
                    }
                    break;
            }

            if(pData[6] == 0)
            {
                pData[6] = pData[3];
            }


            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);    // first bits shift direction: left shift
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2)); // left bits shift direction: rigth shift
            SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pData[3] - pData[6]) << 4) | pData[6]); // first bits shift and second bits shift

            pData[8] = ucElementCount;
            pData[7] = pData[6];

            for(pData[0] = 0; pData[0] < 9; pData[0]++)
            {
                SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0); // restart from last three bytes

                if(PDATA_WORD(6) == _GLOBAL_FONT_END_OFFSET)
                {
                    if(pData[2] >= _GLOBAL_FONT_END)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                    }
                    else
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 2)));
                    }
                }
                else if(PDATA_WORD(6) > _GLOBAL_FONT_END_OFFSET)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[2] + PDATA_WORD(6) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                }
                else// if(ucOffset[0] < _GLOBAL_FONT_END_OFFSET)
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3))));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 1)));
                    SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[2] + PDATA_WORD(6)) * 27) + (pData[0] * 3) + 2)));
                }

                ucElementCount = pData[8];
                pData[6] = pData[7];

                if((pData[6] == 12) || (*(pucArray + ucElementCount) == _END_) || (*(pucArray + ucElementCount) == _NEXT_LINE))
                {
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                    SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                }

                while((pData[6] < 12) &&
                      (*(pucArray + ucElementCount) != _END_) &&
                      (*(pucArray + ucElementCount) != _NEXT_LINE))
                {
                    SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pData[6] << 4) | pData[6]); // third bits shift and left bits shift

                    if(pData[5] == 0)
                    {
                        pData[1] = *(pucArray + ucElementCount);

                        if(pData[1] == _FONT_BLANK_PIXEL)
                        {
                            pData[5] = *(pucArray + ucElementCount + 1);

                            pData[1] = _;
                        }
                    }
                    else
                    {
                        pData[1] = _;
                    }

                    if((pData[1] == _FONT_SELECT_EXT1) ||
                       (pData[1] == _FONT_SELECT_EXT2))
                    {
                        PDATA_WORD(7) = (pData[1] == _FONT_SELECT_EXT1) ? _FONT_SELECT_OFFSET1 : _FONT_SELECT_OFFSET2;
                        ucElementCount++;
                        pData[1] = *(pucArray + ucElementCount);
                    }
                    else
                    {
                        PDATA_WORD(7) = 0;
                    }

                    if((PDATA_WORD(7) + pData[1]) < (_GLOBAL_FONT_END_OFFSET + _GLOBAL_FONT_END))
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[0][pData[1] + PDATA_WORD(7)];
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                        }
                    }
                    else
                    {
                        if(pData[5] == 0)
                        {
                            pData[3] = tOSD_TABLE_LANGUAGE_FONT_WIDTH[ucLanguage + 1][pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET];
                        }
                        else
                        {
                            pData[3] = (pData[5] > 12) ? 12 : pData[5];
                        }
                    }

                    ucElementCount ++;
                    pData[6] += pData[3];

                    if(PDATA_WORD(7) == _GLOBAL_FONT_END_OFFSET)
                    {
                        if(pData[1] >= _GLOBAL_FONT_END)
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                        }
                        else
                        {
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3))));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 1)));
                            SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 2)));
                        }
                    }
                    else if(PDATA_WORD(7) > _GLOBAL_FONT_END_OFFSET)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable((ucLanguage + 1), (((pData[1] + PDATA_WORD(7) - _GLOBAL_FONT_END - _GLOBAL_FONT_END_OFFSET) * 27) + (pData[0] * 3) + 2)));
                    }
                    else// if(ucOffset[1] < _GLOBAL_FONT_END_OFFSET)
                    {
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3))));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 1)));
                        SCALEROSD_FONT_ROTATE_INPUT_SET(OsdPutStringPropFontTable(0, (((pData[1] + PDATA_WORD(7)) * 27) + (pData[0] * 3) + 2)));
                    }
                }

                pucpTemp[pData[0] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucpTemp[pData[0] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
                pucpTemp[pData[0] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            }

            if(pData[6] <= 12)
            {
                pData[6] = 0;
            }
            else
            {
                pData[6] = pData[6] - 12;

                if(ucElementCount >= 1)
                {
                    ucElementCount--;
                }
                if(ucElementCount != 0)
                {
                    pData[1] = *(pucArray + ucElementCount - 1);

                    if((pData[1] == _FONT_SELECT_EXT1) ||
                       (pData[1] == _FONT_SELECT_EXT2))
                    {
                        ucElementCount--;
                    }
                }
            }

            // Write the pro font data to sram
            OsdPropFontDataToSram(ucFptsSelect, pucpTemp, GET_OSD_ROTATE_STATUS());

            // Record the length (coloumn) of prop string
            pData[4]++;

            // Only shift for the first word
            bCenterFlag = _FALSE;

        }// End of while(*(pArray + stringcnt) != _END_)



        if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_CENTER)
        {
            ucCol = ucColBackup  + ((((GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]) / 2) < 0) ? 0 : ((GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]) / 2));
        }
        else if(GET_OSD_INFO_STRING_MODE() == _PUT_STRING_RIGHT)
        {
            ucCol = ucColBackup  + (((GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]) < 0) ? 0 : (GET_OSD_INFO_STRING_MODE_LENGTH() - pData[4]));
        }

        ScalerOsdSramAddressCount(ucRow, ucCol, _OSD_BYTEALL);
        for(pData[0] = 0; pData[0] < pData[4]; pData[0]++)
        {
#if(_OSD_FONT_MODE_FORCE_256_511 == _ON)
            ScalerOsdDataPort(_OSD_MODE_BYTE0_256_511);
#else
            ScalerOsdDataPort((PDATA_WORD(5) < 256) ? _OSD_MODE_BYTE0 : _OSD_MODE_BYTE0_256_511);
#endif // End of #if(_OSD_FONT_MODE_FORCE_256_511 == _ON)
            ScalerOsdDataPort(PDATA_WORD(5) & 0xFF);
            ScalerOsdDataPort(ucColor);

            PDATA_WORD(5) = OsdPropSetFontPointer(ucFptsSelect, PDATA_WORD(5));
        }


        if(*(pucArray + ucElementCount) == _NEXT_LINE)
        {
            // Start the next line from pArray
            pucArray += ucElementCount + 1;
            ucRow++;

            bNextLineFlag = _TRUE;
        }

    }while(bNextLineFlag == _TRUE);

    CLR_OSD_INFO_STRING_MODE();
    CLR_OSD_INFO_STRING_MODE_LENGTH();
}



//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage)
{
    SET_OSD_INFO_STRING_MODE(_PUT_STRING_CENTER);
    SET_OSD_INFO_STRING_MODE_LENGTH(ucWidth);

    OsdPropPutString(ucRow, ucCol, ucFptsSelect, ucString, ucColor, ucLanguage);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = 0;
    BYTE ucI = 0;
    BYTE pucDataSN[16] = {0};

    pucDataSN[5] = (_0_ + (ulValue / 100000));
    pucDataSN[4] = (_0_ + (ulValue % 100000 / 10000));
    pucDataSN[3] = (_0_ + (ulValue % 10000) / 1000);
    pucDataSN[2] = (_0_ + (ulValue % 1000) / 100);
    pucDataSN[1] = (_0_ + (ulValue % 100) / 10);
    pucDataSN[0] = (_0_ + (ulValue % 10));

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(pucDataSN[5 - ucIndex] != ((bit)(ucPar & _BIT1) ? _ : _0_))
        {
            ucIndex = 5 - ucIndex;
            break;
        }
    }

    if((ulValue == 0) && ((bit)(ucPar & 0x02) == 0))
    {
        ucIndex = 0;
    }

    if((bit)(ucPar & _BIT1) != 0)
    {
        ucTemp = (ucPar & 0x70) >> 4;
        ucIndex = (ucPar & 0x70) >> 4;
    }
    else
    {
        ucTemp = (ucPar & 0x70) >> 4;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;
        }
    }

    for(ucI = 0; ucI <= ucTemp; ucI++)
    {
        if(ucIndex >= ucTemp)
        {
            pucDataSN[ucI + 8] = pucDataSN[ucIndex - ucI];
        }
        else
        {
            if(ucI < (ucTemp - ucIndex))
            {
                pucDataSN[ucI + 8] = 0x00;
            }
            else
            {
                pucDataSN[ucI + 8] = pucDataSN[ucIndex - (ucI - (ucTemp - ucIndex))];
            }
        }
    }
    if((ucPar & 0x01) == _ALIGN_LEFT) // Align Right
    {
        pucDataSN[8 + ucTemp + 1] = _; // clear
        pucDataSN[8 + ucTemp + 2] = _; // clear
        pucDataSN[8 + ucTemp + 3] = _END_;
    }
    else
    {
        pucDataSN[8 + ucTemp + 1] = _END_;
    }
    g_pucShowNumberAddress = &pucDataSN[8];

    if((ucPar & 0x01) == _ALIGN_RIGHT)        // Align Right
    {
        OsdPropPutString(ucRow, ROW(ucCol - ucTemp), ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
    else
    {
        OsdPropPutString(ucRow, ucCol, ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
}


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetStringTableAddress(BYTE ucString)
{
    BYTE *pucArray = tsOsdNull;

    switch(ucString)
    {
        case _STRING_PICTURE:
            pucArray = tsOsdPicture;
            break;
        case _STRING_DISPLAY:
            pucArray = tsOsdDisplay;
            break;
        case _STRING_COLOR:
            pucArray = tsOsdColor;
            break;
        case _STRING_ADVANCE:
            pucArray = tsOsdAdvance;
            break;
        case _STRING_INPUT:
            pucArray = tsOsdInput;
            break;
        case _STRING_AUDIO:
            pucArray = tsOsdAudio;
            break;
        case _STRING_OTHER:
            pucArray = tsOsdOther;
            break;
        case _STRING_INFORMATION:
            pucArray = tsOsdInformation;
            break;
        case _STRING_FACTORY:
            pucArray = tsOsdFactory;
            break;

        // picture
        case _STRING_BACKLIGHT:
            pucArray = tsOsdBacklight;
            break;
        case _STRING_BRIGHTNESS:
            pucArray = tsOsdBrightness;
            break;
        case _STRING_CONTRAST:
            pucArray = tsOsdContrast;
            break;
        case _STRING_SHARPNESS:
            pucArray = tsOsdSharpness;
            break;

        // display
        case _STRING_AUTO_ADJUST:
            pucArray = tsOsdAutoAdjust;
            break;
        case _STRING_HPOS:
            pucArray = tsOsdHPosition;
            break;
        case _STRING_VPOS:
            pucArray = tsOsdVPosition;
            break;
        case _STRING_CLOCK:
            pucArray = tsOsdClock;
            break;
        case _STRING_PHASE:
            pucArray = tsOsdPhase;
            break;

        case _STRING_DISP_ROTATE:
            pucArray = tsOsdDispRotate;
            break;

        case _STRING_LATENCY:
            pucArray = tsOsdDispLatency;
            break;

        // color
        case _STRING_PANEL_UNIFORMITY:
            pucArray = tsOsdPanelUniformity;
            break;

        case _STRING_GAMMA:
            pucArray = tsOsdGamma;
            break;
        case _STRING_COLOR_TEMP:
            pucArray = tsOsdTemperature;
            break;
        case _STRING_COLOR_EFFECT:
            pucArray = tsOsdColorEffect;
            break;
        case _STRING_DEMO:
            pucArray = tsOsdDemo;
            break;
        case _STRING_COLOR_FORMAT:
            pucArray = tsOsdColorFormat;
            break;
        case _STRING_PCM:
            pucArray = tsOsdPcm;
            break;
        case _STRING_HUE:
            pucArray = tsOsdHue;
            break;
        case _STRING_SATURATION:
            pucArray = tsOsdSaturation;
            break;
        // advance
        case _STRING_ASPECT_RATIO:
            pucArray = tsOsdAspectRatio;
            break;
        case _STRING_OVER_SCAN:
            pucArray = tsOsdOverScan;
            break;
        case _STRING_OVER_DRIVE:
            pucArray = tsOsdOverDrive;
            break;
        case _STRING_DCR:
            pucArray = tsOsdDcr;
            break;
        case _STRING_DDCCI:
            pucArray = tsOsdDdcci;
            break;
        case _STRING_ULTRA_VIVID:
            pucArray = tsOsdUltraVivid;
            break;
        case _STRING_DP_OPTION:
            pucArray = tsOsdDpOption;
            break;
        case _STRING_DP_MST:
            pucArray = tsOsdDpMst;
            break;
        case _STRING_DP_RESOLUTION:
            pucArray = tsOsdDpResolution;
            break;
        case _STRING_CLONE:
            pucArray = tsOsdCloneMode;
            break;
        case _STRING_FREESYNC:
#if(_FREESYNC_II_SUPPORT == _ON)
            pucArray = tsOsdFreeSync2;
#else
            pucArray = tsOsdFreeSync;
#endif //#if(_FREESYNC_II_SUPPORT == _ON)
            break;
        case _STRING_FREEZE:
            pucArray = tsOsdFreeze;
            break;

#if(_DP_TYPE_C_CONNECTOR_SUPPORT == _ON)
        case _STRING_TYPE_C_MODE:
            pucArray = tsOsdTypeCConfig;
            break;
#endif

#if(_HDR10_SUPPORT == _ON)
        case _STRING_ULTRA_HDR:
            pucArray = tsOsdUltraHdr;
            break;
        case _STRING_ULTRA_HDR_MODE:
            pucArray = tsOsdUltraHdrMode;
            break;
        case _STRING_DARK_ENHANCE:
            pucArray = tsOsdDarkEnhance;
            break;
        case _STRING_SHARPNESS_ENHANCE:
            pucArray = tsOsdSharpnessEnhance;
            break;
        case _STRING_COLOR_ENHANCE:
            pucArray = tsOsdColorEnhance;
            break;
        case _STRING_LIGHT_ENHANCE:
            pucArray = tsOsdLightEnhance;
            break;
#endif
#if(_OSD_LOCAL_DIMMING_SUPPORT == _ON)
        case _STRING_LOCAL_DIMMING:
            pucArray = tsOsdLocalDimming;
            break;
#endif
#if (_PIXEL_SHIFT_SUPPORT == _ON)
        case _STRING_PIXEL_SHIFT:
            pucArray = tsOsdPixelShifting;
            break;
#endif
        case _STRING_HDMI_VERSION:
            pucArray = tsOsdHdmiVersion;
            break;
#if(_SDR_TO_HDR_SUPPORT == _ON)
        case _STRING_SDR_TO_HDR:
            pucArray = tsOsdSdrToHdr;
            break;
#endif
#if(_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        case _STRING_MBR:
        case _STRING_MBR_MODE:
            pucArray = tsOsdMbr;
            break;
        case _STRING_DUTY:
            pucArray = tsOsdDuty;
            break;
        case _STRING_POSTION:
            pucArray = tsOsdPosition;
            break;
#endif
        // audio
        case _STRING_VOLUME:
            pucArray = tsOsdVolume;
            break;
        case _STRING_MUTE:
            pucArray = tsOsdMute;
            break;
        case _STRING_STAND_ALONG:
            pucArray = tsOsdStandAlong;
            break;
        case _STRING_AUDIO_SOURCE:
            pucArray = tsOsdAudioSource;
            break;
        case _STRING_SOUND_MODE:
            pucArray = tsOsdSoundMode;
            break;
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
        case _STRING_AUDIO_SELF_TEST:
            pucArray = tsOsdAudioSelfTest;
            break;
#endif
        // other
        case _STRING_RESET:
            pucArray = tsOsdReset;
            break;
        case _STRING_MENU_TIME:
            pucArray = tsOsdMenuTime;
            break;
        case _STRING_OSD_HPOS:
            pucArray = tsOsdOsdHPosition;
            break;
        case _STRING_OSD_VPOS:
            pucArray = tsOsdOsdVPosition;
            break;
        case _STRING_LANGUAGE:
            pucArray = tsOsdLanguage;
            break;
        case _STRING_TRANSPARENCY:
            pucArray = tsOsdTransparency;
            break;
        case _STRING_ROTATE:
            pucArray = tsOsdRotate;
            break;
        case _STRING_SHOW_NUMBER:
            pucArray = g_pucShowNumberAddress;
            break;

        // information
        case _STRING_HFREQPCLK:
            OsdPropGetShowHFreqPClkStringAddress();
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_VFREQUENCY:
            OsdPropGetShowVFreqStringAddress();
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_VGA_USER_MODE:
            pucArray = tsOsdUserMode;
            break;
        case _STRING_VGA_PRESET_MODE:
            pucArray = tsOsdPresetMode;
            break;

        case _STRING_HDCP_MODE:
#if(_DIGITAL_PORT_SUPPORT == _ON)
            OsdPropGetShowHDCPEnable(ScalerSyncHdcpCheckEnabled(SysSourceGetInputPort()));
            pucArray = g_pucModeInfoData;

#endif
            break;

        // Adjust message
        case _STRING_PLEASE_WAIT:
            pucArray = tsOsdPleaseWait;
            break;

        case _STRING_NO_SIGNAL:
            pucArray = tsOsdNoSignal;
            break;

        case _STRING_NO_CABLE:
            pucArray = tsOsdNoCable;
            break;

        case _STRING_NO_SUPPORT:
            pucArray = tsOsdNoSupport;
            break;

        case _STRING_GO_TO_POWER_SAVING_MODE:
            pucArray = tsOsdGoToPowerSaving;
            break;

        case _STRING_NOW_RESOLUTION:
            OsdPropGetShowResolutionStringAddress();
            pucArray = g_pucModeInfoData;
            break;

        case _STRING_AUTO_COLOR:
            pucArray = tsOsdAutoColor;
            break;

        case _STRING_AUTO_SELECT:
            pucArray = tsOsdAutoSelect;
            break;

        case _STRING_PASS:
            pucArray = tsOsdPass;
            break;

        case _STRING_FAIL:
            pucArray = tsOsdFail;
            break;
#if(_FREESYNC_SUPPORT == _ON)
        case _STRING_FREESYNC_SUPPORT_V_RANGE:
            //OsdPropGetShowFreeSyncVFreqRangeStringAddress();
            pucArray = g_pucModeInfoData;
            break;
#endif
        case _STRING_A0_PORT:
        case _STRING_D0_PORT:
        case _STRING_D1_PORT:
        case _STRING_D2_PORT:
        case _STRING_D3_PORT:
        case _STRING_D4_PORT:
        case _STRING_D5_PORT:
        case _STRING_D6_PORT:
            OsdPropGetShowInputPortStringAddress(ucString - _STRIN_END);
            pucArray = g_pucModeInfoData;
            break;
#if(_DP_DEBUG_MSG == _ON)
        case _STRING_DP_INFO:
            OsdPropGetShowDpInfoStringAddress(_STRING_DP_INFO);
            pucArray = g_pucModeInfoData;
            break;
        case _STRING_DP_INFO_2:
            OsdPropGetShowDpInfoStringAddress(_STRING_DP_INFO_2);
            pucArray = g_pucModeInfoData;
            break;
#endif

        default:
            break;
    }

    return pucArray;
}
#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)

