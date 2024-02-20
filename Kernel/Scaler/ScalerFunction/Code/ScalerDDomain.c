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
// ID Code      : ScalerDDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DDOMAIN__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_FREESYNC_OD_MEASURE == _ON)
#define _FREESYNC_OD_MEASURE_GL_ENABLE_REG    P7_F3_DISP_PG_R_INITIAL
#define _FREESYNC_OD_MEASURE_GL_VALUE_REG     P7_F4_DISP_PG_G_INITIAL
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PANEL_EXIST_MULTIPANEL == _ON)
BYTE g_ucDDomainPanelIndex;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDDomainPatternGenEnable(bit bEnable);
void ScalerDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
#if(_OGC_GEN_TYPE == _OGC_GEN_1)
#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
void ScalerDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue);
#endif
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
void ScalerDDomainFREESYNCODSetBackgroundGrayLevel(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Display Pattern Gen Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable D Domain PG
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable D Domain PG
        ScalerSetBit(P7_F0_DISP_PG_R_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Display Pattern Gen Color
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenAdjustColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, ucRed);
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, ucGreen);
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, ucBlue);
    ScalerSetBit(P7_FC_D_PG_INITIAL_M_STEP_L, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

#if(_OGC_GEN_TYPE == _OGC_GEN_1)
#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Display Pattern Gen Color (10bit)
// Input Value  : RGB Color
// Output Value : None
//--------------------------------------------------
void ScalerDDomainPatternGenAdjustColor10bit(WORD usRed, WORD usGreen, WORD usBlue) // 10bit
{
    ScalerSetByte(P7_F3_DISP_PG_R_INITIAL, (usRed >> 2));
    ScalerSetByte(P7_F4_DISP_PG_G_INITIAL, (usGreen >> 2));
    ScalerSetByte(P7_F5_DISP_PG_B_INITIAL, (usBlue >> 2));
    ScalerSetByte(P7_FC_D_PG_INITIAL_M_STEP_L, ((usRed & 0x03) << 4) | ((usGreen & 0x03) << 2) | (usBlue & 0x03));
    ScalerSetByte(P7_FD_D_PG_INITIAL_L_CTRL, 0x00);
}
#endif
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set Background to Gray Level
//                Specified by OD Calibration Tool
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDomainFREESYNCODSetBackgroundGrayLevel(void)
{
    static BYTE sucSelectedBGGrayLevel = 0x00;
    static BYTE sucPreviousBGGrayLevel = 0x00;

    // This function borrows two registers from "D-domain pattern generator"
    // 1. P7_F3_DISP_PG_R_INITIAL served as "specified gray level"
    // 2. _BIT7 of P7_F4_DISP_PG_G_INITIAL served as "function enable" control bit
    // OD calibration tool will use these two registers to communicate with firmware

    // Enable Background
    ScalerDDomainBackgroundEnable(_ENABLE);

    if(ScalerGetBit(_FREESYNC_OD_MEASURE_GL_ENABLE_REG, _BIT7) == _BIT7)
    {
        sucPreviousBGGrayLevel = sucSelectedBGGrayLevel;
        sucSelectedBGGrayLevel = ScalerGetByte(_FREESYNC_OD_MEASURE_GL_VALUE_REG);

        if(sucPreviousBGGrayLevel != sucSelectedBGGrayLevel)
        {
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            ScalerDDomainBackgroundSetColor(sucSelectedBGGrayLevel, sucSelectedBGGrayLevel, sucSelectedBGGrayLevel);
        }
    }
    else
    {
        // Enable Red Background
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerDDomainBackgroundSetColor(0xFF, 0x00, 0x00);
    }
}
#endif

