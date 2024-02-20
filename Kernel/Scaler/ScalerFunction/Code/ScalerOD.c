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
// ID Code      : ScalerOD.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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
#if(_OD_SUPPORT == _ON)
#if(_FRC_SUPPORT == _ON)
BYTE g_ucODCurrDynamicStatus;
#endif
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_OD_SUPPORT == _ON)
BYTE ScalerODGetCompressionBitNum(DWORD ulMemoryRemainSpace, WORD usMemoryRemainBW);
bit ScalerODGetSupportStatus(void);
EnumFunctionOnOFF ScalerODGetStatus(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OD compression bit number
//                according to available memory space & BW.
// Input Value  : Remaining space & BW
// Output Value : OD compression bit number(10x)
//--------------------------------------------------
BYTE ScalerODGetCompressionBitNum(DWORD ulMemoryRemainSpace, WORD usMemoryRemainBW)
{
    WORD usODUseSpace = 0;
    WORD usODUseBW = 0;

    DebugMessageMemory("4. Remaining BW for OD", usMemoryRemainBW);
    DebugMessageMemory("4. Remaining Space for OD", ulMemoryRemainSpace);
    //=============================================
    // OD compression bit num: 7.5bits / pixel
    //=============================================
    if(CHECK_OD_MODE_AVAILABLE(_OD_SUPERPIXEL1X2_75BIT_BIT_NUM) == _TRUE)
    {
        usODUseSpace = ScalerMDomainODCalculateMemoryUseSpace(_OD_SUPERPIXEL1X2_75BIT_BIT_NUM);
        usODUseBW = ScalerMDomainODCalculateMemoryUseBW(_OD_SUPERPIXEL1X2_75BIT_BIT_NUM);

        DebugMessageMemory("4. 7_5_bit OD BW", usODUseBW);
        DebugMessageMemory("4. 7_5_bit OD Size", usODUseSpace);
        if((usODUseSpace < ulMemoryRemainSpace) && (usODUseBW < usMemoryRemainBW))
        {
            return _OD_SUPERPIXEL1X2_75BIT_BIT_NUM;
        }
    }
    //=============================================
    // OD compression bit num: 6 bits / pixel
    //=============================================
    if(CHECK_OD_MODE_AVAILABLE(_OD_SUPERPIXEL1X4_60BIT_BIT_NUM) == _TRUE)
    {
        usODUseSpace = ScalerMDomainODCalculateMemoryUseSpace(_OD_SUPERPIXEL1X4_60BIT_BIT_NUM);
        usODUseBW = ScalerMDomainODCalculateMemoryUseBW(_OD_SUPERPIXEL1X4_60BIT_BIT_NUM);

        DebugMessageMemory("4. 6_0_bit OD BW", usODUseBW);
        DebugMessageMemory("4. 6_0_bit OD Size", usODUseSpace);
        if((usODUseSpace < ulMemoryRemainSpace) && (usODUseBW < usMemoryRemainBW))
        {
            return _OD_SUPERPIXEL1X4_60BIT_BIT_NUM;
        }
    }
    //=============================================
    // Otherwise, OD off
    //=============================================
    return _OFF;
}

//--------------------------------------------------
// Description  : Get OD kernel Useability
// Input Value  : None
// Output Value : _OFF/_ON
//--------------------------------------------------
bit ScalerODGetSupportStatus(void)
{
    return ((GET_OD_USE_BIT() == _OFF) ? (_OFF) : (_ON));
}

//--------------------------------------------------
// Description  : Get OD real-time enable status
// Input Value  : None
// Output Value : _FUNCTION_OFF/_FUNCTION_ON
//--------------------------------------------------
EnumFunctionOnOFF ScalerODGetStatus(void)
{
#if(_FRC_SUPPORT == _ON)
    if(GET_OD_CURR_DYNAMIC_STATUS() == _ENABLE)
    {
        return _FUNCTION_ON;
    }

#endif
    return (ScalerGetBit(P3_A1_LS_CTRL0, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) ? _FUNCTION_ON : _FUNCTION_OFF;
}
#endif
