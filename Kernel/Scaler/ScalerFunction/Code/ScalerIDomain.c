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
// ID Code      : ScalerIDomain.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IDOMAIN__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//#define GET_VGIP_INITIAL_VDELAY()                   (g_usVgipVDelayInitial)
//#define SET_VGIP_INITIAL_VDELAY(x)                  (g_usVgipVDelayInitial = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usVgipVDelayInitial;

#if(_UNDERSCAN_SUPPORT == _ON)
WORD g_usUnderScanIVheight;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerIDomainVgipSetInputCapture(void);
void ScalerIDomainVgipIVDelayIVstStepAdjust(WORD usInitialIVDelay);
WORD ScalerIDomainVgipIHCaptureMaxEstimate(WORD usHPosition);
void ScalerIDomainVgipAdjustIHVDelay(void);
void ScalerIDomainFineTuneHCaptureStart(WORD usDeltaIHCapture);
void ScalerIDomainScalingDownInitial(void);

#if(_UNDERSCAN_SUPPORT == _ON)
WORD ScalerIDomainVgipGetVCaptureStartMinValue(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set VGIP Capture Window
// Input Value  : Capture Type, H/V Active and Start
// Output Value : None
//--------------------------------------------------
void ScalerIDomainVgipSetInputCapture(void)
{
    // Enable VGIP capture
    ScalerVgipCaptureEnable(_ENABLE);

    SET_VGIP_INITIAL_VDELAY(0);

    if(ScalerIDomainCheckDigitalCapture() == _TRUE)
    {
        // Set Digital Capture
        ScalerVgipSetDigitalCaptureStatus(_ENABLE);

        // Set VGIP H Capture Width
        ScalerVgipSetCaptureHWidth(GET_MDOMAIN_INPUT_HWIDTH());

        // Set VGIP V Capture Heigth
        ScalerVgipSetCaptureVHeight(GET_MDOMAIN_INPUT_VHEIGHT());

        // Set VGIP H capture start position
        if(GET_MDOMAIN_INPUT_HSTART() > GET_INPUT_TIMING_HSTART())
        {
            ScalerVgipSetCaptureHStartPosition(GET_MDOMAIN_INPUT_HSTART() - GET_INPUT_TIMING_HSTART());
        }
        else
        {
            ScalerVgipSetCaptureHStartPosition(0x00);
        }

        // Set VGIP V capture start position
        if(GET_MDOMAIN_INPUT_VSTART() > GET_INPUT_TIMING_VSTART())
        {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
            {
                ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART() - (GET_INPUT_TIMING_VSTART() - (GET_INPUT_TIMING_VSTART() % 2)));
            }
            else
#endif
            {
                ScalerVgipSetCaptureVStartPosition(GET_MDOMAIN_INPUT_VSTART() - GET_INPUT_TIMING_VSTART());
            }
        }
        else
        {
            ScalerVgipSetCaptureVStartPosition(0x00);
        }

        // Set VGIP H/V capture delay
        ScalerVgipSetCaptureHDelay(0);
        ScalerVgipSetCaptureVDelay(0);
    }
    else
    {
        WORD usIHDelay = 0;

        // Set VGIP H Capture Width
        ScalerVgipSetCaptureHWidth(g_stMDomainInputData.usHWidth);

        // Set VGIP V Capture Heigth
        ScalerVgipSetCaptureVHeight(g_stMDomainInputData.usVHeight);

        if(g_stMDomainInputData.usHStart <= _VGIP_IH_CAPTURE_MIN_VALUE)
        {
            g_stMDomainInputData.usHStart = _VGIP_IH_CAPTURE_MIN_VALUE + 1;
        }

        usIHDelay = g_stMDomainInputData.usHStart - ScalerIDomainVgipIHCaptureMaxEstimate(g_stMDomainInputData.usHStart);

        g_stMDomainInputData.usHStart = ScalerIDomainVgipIHCaptureMaxEstimate(g_stMDomainInputData.usHStart);

        // Set VGIP H Capture Start Position
        ScalerVgipSetCaptureHStartPosition(g_stMDomainInputData.usHStart);

        // Front Porch is Not Enough
        if(g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight + _VGIP_V_FRONT_PORCH_MIN_VALUE >= g_stMDomainInputData.usVTotal)
        {
            // Increase Front Porch by VDelay
            SET_VGIP_INITIAL_VDELAY(g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight + _VGIP_V_FRONT_PORCH_MIN_VALUE - g_stMDomainInputData.usVTotal);
            g_stMDomainInputData.usVStart -= GET_VGIP_INITIAL_VDELAY();
        }
        else
        {
            SET_VGIP_INITIAL_VDELAY(0);
        }

        // Check if V capture start exceeds maximum value
        if(g_stMDomainInputData.usVStart > _VGIP_IV_CAPTURE_MAX_VALUE)
        {
            SET_VGIP_INITIAL_VDELAY(GET_VGIP_INITIAL_VDELAY() + (BYTE)(g_stMDomainInputData.usVStart - _VGIP_IV_CAPTURE_MAX_VALUE));
            g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MAX_VALUE;
        }

        // Set VGIP capture delay
        ScalerVgipSetCaptureHDelay(usIHDelay);

        if(ScalerMDomainGetFrameSyncMode() == _FRAME_SYNC_MODE)
        {
            ScalerIDomainVgipIVDelayIVstStepAdjust(GET_VGIP_INITIAL_VDELAY());
        }
        else
        {
            // Set VGIP V Capture  Start Position
            ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);

            ScalerVgipSetCaptureVDelay(GET_VGIP_INITIAL_VDELAY());
        }
    }

    DebugMessageScaler("9. Set Capture usHWidth", g_stMDomainInputData.usHWidth);
    DebugMessageScaler("9. Set Capture usHStart", g_stMDomainInputData.usHStart);
    DebugMessageScaler("9. Set Capture usVHeight", g_stMDomainInputData.usVHeight);
    DebugMessageScaler("9. Set Capture usVStart", g_stMDomainInputData.usVStart);
}

//--------------------------------------------------
// Description  : IVSdelay need to setting several times
// Input Value  : Initial IVS delay
// Output Value : N.A.
//--------------------------------------------------
void ScalerIDomainVgipIVDelayIVstStepAdjust(WORD usInitialIVDelay)
{
    WORD usIVDelayStep = 1;
    WORD usIVDelayTemp = 0;
    BYTE ucSettingCounter = 0;

    WORD usDVtotal = GET_MDOMAIN_OUTPUT_VTOTAL();

    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

    GET_DVTOTAL_LASTLINE(usDVtotal);
    SET_MDOMAIN_OUTPUT_VTOTAL(usDVtotal);

    if(g_stMDomainOutputData.usVTotal > (g_stMDomainOutputData.usVBackStart + g_stMDomainOutputData.usVBackHeight + _PANEL_FRONT_PORCH_LIMIT))
    {
        usIVDelayStep = (g_stMDomainOutputData.usVTotal - g_stMDomainOutputData.usVBackStart - g_stMDomainOutputData.usVBackHeight - _PANEL_FRONT_PORCH_LIMIT);
        usIVDelayStep = GET_DWORD_MUL_DIV(usIVDelayStep, g_stMDomainInputData.usVTotal, g_stMDomainOutputData.usVTotal);

        if(usIVDelayStep < 1)
        {
            usIVDelayStep = 1;
        }
    }
    else
    {
        DebugMessageFS("warning !!! Aspect ratio/ overscan maybe have garbage", 0);
    }

    ucSettingCounter = (abs(usInitialIVDelay - ScalerVgipGetCaptureVDelay()) / usIVDelayStep) + 1;

    do
    {
        if(usInitialIVDelay > ScalerVgipGetCaptureVDelay())
        {
            // Set VGIP V delay
            ScalerVgipSetCaptureVDelay(usInitialIVDelay);

            // Set VGIP V Capture  Start Position
            ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);
        }
        else
        {
            if((ScalerVgipGetCaptureVDelay() - usInitialIVDelay) <= usIVDelayStep)
            {
                // Set VGIP V delay
                ScalerVgipSetCaptureVDelay(usInitialIVDelay);

                // Set VGIP V Capture  Start Position
                ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);
            }
            else
            {
                usIVDelayTemp = ScalerVgipGetCaptureVDelay() - usIVDelayStep;

                // Step adjust IVdelay
                ScalerVgipSetCaptureVDelay(usIVDelayTemp);

                // Step adjust IVstart
                ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart + usInitialIVDelay - usIVDelayTemp);
            }

            DebugMessageFS("IVDelay step step", ScalerVgipGetCaptureVDelay());
        }

        ScalerGlobalIDomainDBApply(_DB_APPLY_POLLING);

        ucSettingCounter--;
    }
    while((usInitialIVDelay != ScalerVgipGetCaptureVDelay()) && (ucSettingCounter > 0));
}

//--------------------------------------------------
// Description  : Estimate Max Allowable H Capture Start
// Input Value  : Current H Start
// Output Value : Max Allowable H Start
//--------------------------------------------------
WORD ScalerIDomainVgipIHCaptureMaxEstimate(WORD usHPosition)
{
    if(usHPosition <= (_VGIP_IH_DELAY_MAX_VALUE + _VGIP_IH_CAPTURE_MIN_VALUE - (_MAX_H_POSITION_RANGE / 2)))
    {
        return _VGIP_IH_CAPTURE_MIN_VALUE;
    }
    else
    {
        return (usHPosition - (_VGIP_IH_DELAY_MAX_VALUE - (_MAX_H_POSITION_RANGE / 2)));
    }
}

//--------------------------------------------------
// Description  : Adjust IVS/IHS Delay to Gain Largest Position-Adjusting Range
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIDomainVgipAdjustIHVDelay(void)
{
    WORD usIV2DVdelay = 0;
    BYTE ucIVSdelayExtend = 0;

    // Bypass IHV delay in digital capture
    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        return;
    }

    if(ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1)
    {
        usIV2DVdelay = (ScalerMemoryGetIVS2DVSDelayPixel() - (g_stMDomainInputData.usHTotal / 2)) / g_stMDomainInputData.usHTotal;
    }
    else
    {
        usIV2DVdelay = ScalerMemoryGetIVS2DVSDelayPixel() / g_stMDomainInputData.usHTotal;
    }

#if(_FRC_SUPPORT == _ON)
    if((GET_MEMORY_SELECT() != _FRAME_SYNC_LINE_BUFFER) && (GET_MEMORY_SELECT() != _FREE_RUN_NO_INPUT))
    {
        // Set IVS Delay
        if((g_stMDomainInputData.usVStart + GET_VGIP_INITIAL_VDELAY()) > _VGIP_IV_CAPTURE_MIN_VALUE)
        {
            ScalerVgipSetCaptureVDelay(g_stMDomainInputData.usVStart - _VGIP_IV_CAPTURE_MIN_VALUE + GET_VGIP_INITIAL_VDELAY());
            SET_VGIP_INITIAL_VDELAY(g_stMDomainInputData.usVStart - _VGIP_IV_CAPTURE_MIN_VALUE + GET_VGIP_INITIAL_VDELAY());
        }
        else
        {
            ScalerVgipSetCaptureVDelay(0);
            SET_VGIP_INITIAL_VDELAY(0);
        }

        // Set V Start
        g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MIN_VALUE;
        ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);
    }
    else
#endif
    {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus() == _TRUE)
        {
            // Remain IVSt = Raw IVSt - IVSDelay
            g_stMDomainInputData.usVStart = g_stMDomainInputData.usVStart - usIV2DVdelay;


            if(g_stMDomainInputData.usVStart <= (_VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2))
            {
                DebugMessageScaler("VStart too Small", g_stMDomainInputData.usVStart);

                // Get Difference of Remain IVSt and _VGIP_IV_CAPTURE_MIN_VALUE
                ucIVSdelayExtend = (_VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2) - g_stMDomainInputData.usVStart;
                g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MIN_VALUE + _VGIP_IV_CAPTURE_MIN_VALUE % 2;
            }
            else
            {
                ucIVSdelayExtend = g_stMDomainInputData.usVStart % 2;
                g_stMDomainInputData.usVStart += g_stMDomainInputData.usVStart % 2;
            }
        }
        else
#endif
        {
            // Remain IVSt = Raw IVSt - IVSDelay
            g_stMDomainInputData.usVStart = g_stMDomainInputData.usVStart - usIV2DVdelay;

            if(g_stMDomainInputData.usVStart <= _VGIP_IV_CAPTURE_MIN_VALUE)
            {
                DebugMessageScaler("VStart too Small", g_stMDomainInputData.usVStart);

                // Get Difference of Remain IVSt and _VGIP_IV_CAPTURE_MIN_VALUE
                ucIVSdelayExtend = _VGIP_IV_CAPTURE_MIN_VALUE - g_stMDomainInputData.usVStart;
                g_stMDomainInputData.usVStart = _VGIP_IV_CAPTURE_MIN_VALUE;
            }
            else
            {
                ucIVSdelayExtend = 0;
            }
        }

        // Move Delay to ivs to dvs
        ScalerVgipSetCaptureVStartPosition(g_stMDomainInputData.usVStart);

        // Set IVS to DVS Delay
        ScalerVgipSetCaptureVDelay((WORD)(usIV2DVdelay - ucIVSdelayExtend + GET_VGIP_INITIAL_VDELAY()));

        PDATA_DWORD(0) = ScalerMemoryGetIVS2DVSDelayPixel() - (DWORD)(usIV2DVdelay - ucIVSdelayExtend) * g_stMDomainInputData.usHTotal;
        ScalerMemoryUpdateIVS2DVSLineDelay(PDATA_DWORD(0));
    }
}

//--------------------------------------------------
// Description  : Modify H Capture
// Input Value  : IH Capture Shift
// Output Value : None
//--------------------------------------------------
void ScalerIDomainFineTuneHCaptureStart(WORD usDeltaIHCapture)
{
    ScalerVgipSetCaptureHStartPosition(usDeltaIHCapture + ScalerVgipGetCaptureHStartPosition() - 2);

// What is this?
//    ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, (ScalerGetByte(P0_41_IVS2DVS_DLY_TUNE_ODD) + ((BYTE)(usDeltaIHCapture / 16))));
//    ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, (ScalerGetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN) + ((BYTE)(usDeltaIHCapture / 16))));
}

//--------------------------------------------------
// Description  : Set Scaling Down Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIDomainScalingDownInitial(void)
{
    // Disable Scaling Down
    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Disable Scaling Down
    ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
#endif
}

#if(_UNDERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Vgip VCaptureStart Min Value
// Input Value  : None
// Output Value : Vgip VCaptureStart Min Value
//--------------------------------------------------
WORD ScalerIDomainVgipGetVCaptureStartMinValue(void)
{
    return _VGIP_IV_CAPTURE_MIN_VALUE;
}
#endif
