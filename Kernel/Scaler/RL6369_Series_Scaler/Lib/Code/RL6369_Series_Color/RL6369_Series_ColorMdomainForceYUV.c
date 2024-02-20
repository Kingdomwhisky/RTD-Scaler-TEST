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
// ID Code      : RL6369_Series_ColorMdomainForceYUV.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6369_Series_ColorLibInternalInclude.h"

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
void ScalerColorMdomainForceYUV(EnumColorSpace enumColorSpace, EnumDBApply enumDBApply);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Force YUV Color Format to M-domain
// Input Value  : Input Color Space, EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorMdomainForceYUV(EnumColorSpace enumColorSpace, EnumDBApply enumDBApply)
{
    BYTE ucDVSCnt = ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle();

    //////////////////////////////
    // I-Domain Color Conversion//
    //////////////////////////////
    if(GET_COLOR_SPACE_RGB(enumColorSpace) == _TRUE)
    {
        // Enable I-Domain RGB2YUV
        ScalerSetBit(P0_9C_RGB2YCC_CTRL, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
    }
    else
    {
        // Disable I-Domain RGB2YUV
        ScalerSetBit(P0_9C_RGB2YCC_CTRL, ~(_BIT4 | _BIT0), 0x00);
    }

    //////////////////////////////
    // D-Domain Color Conversion//
    //////////////////////////////

    ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(ucDVSCnt);

    // Load D-Domain YUV2RGB Table
    ScalerColorSpaceLoadYuv2RgbTable(enumColorSpace, _OFF);

    // Enable D-Domain YUV2RGB
    ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL, ~(_BIT4 | _BIT0), _BIT0);

    if(GET_MEMORY_FRAME_BUFFER() != _MEMORY_1_5_FRAME_BUFFER)
    {
        if(GET_INTERLACED_MODE() == _TRUE)
        {
            ScalerGlobalIDomainDBApply(enumDBApply);
            ScalerGlobalDDomainDBApply(enumDBApply);
        }
        else
        {
            ScalerGlobalIDDomainDBApply(enumDBApply);
        }
    }
}

