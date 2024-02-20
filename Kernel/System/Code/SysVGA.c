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
// ID Code      : SysVGA.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_VGA__

#include "SysInclude.h"

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of mode search status
//--------------------------------------------------
#define _VGA_MODE_NOSUPPORT                             254

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
BYTE SysVgaScanInputPort(BYTE ucInputPort);

#if(_UNDERSCAN_SUPPORT == _ON)
void SysVgaAdjustUnderScan(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Scan VGA Port
// Input Value  : ucIntputPort
// Output Value : Source Type
//--------------------------------------------------
BYTE SysVgaScanInputPort(BYTE ucInputPort)
{
    BYTE ucModeNo = 0;

    if(ScalerSyncProcPreDetect(ucInputPort) == _FALSE)
    {
        return _SOURCE_NONE;
    }

    if(ScalerSyncProcTypeAutoRun() != _NO_SYNC_STATE)
    {
        SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_VGA);

        // Initial ADC Clock.
        if(ScalerSyncProcAdcClkInitial() == _FALSE)
        {
            DebugMessageAnalog("Apll initial Fail", 0);

            return _SOURCE_NONE;
        }

        CLR_INPUT_TIMING_DOUBLE_CHECK();

#if(_VGA_CAPTURE_SUPPORT == _ON)
        // Set VGATOP VGIP
        ScalerVgaTopInputInitial();
#endif

        // Get Measure Info.
        if(ScalerMeasureVgaInputInfo() == _FALSE)
        {
            DebugMessageSystem("VGA Measure Fail", 0);

            return _SOURCE_NONE;
        }

        DebugMessageSystem("VGA Measure Measure Info", 0);
        DebugMessageSystem("Input Timing H Polarity", GET_INPUT_TIMING_H_POLARITY());
        DebugMessageSystem("Input Timing V Polarity", GET_INPUT_TIMING_V_POLARITY());
        DebugMessageSystem("Input Timing InterLace", GET_INPUT_TIMING_INTERLACE_FLG());
        DebugMessageSystem("Input Timing HFreq", GET_INPUT_TIMING_HFREQ());
        DebugMessageSystem("Input Timing HTotal", GET_INPUT_TIMING_HTOTAL());
        DebugMessageSystem("Input Timing HStart", GET_INPUT_TIMING_HSTART());
        DebugMessageSystem("Input Timing HWidth", GET_INPUT_TIMING_HWIDTH());
        DebugMessageSystem("Input Timing HSyncWidth", GET_INPUT_TIMING_HSYNCWIDTH());
        DebugMessageSystem("Input Timing VFreq", GET_INPUT_TIMING_VFREQ());
        DebugMessageSystem("Input Timing VTotal", GET_INPUT_TIMING_VTOTAL());
        DebugMessageSystem("Input Timing VStart", GET_INPUT_TIMING_VSTART());
        DebugMessageSystem("Input Timing VHeight", GET_INPUT_TIMING_VHEIGHT());
        DebugMessageSystem("Input Timing VSyncSWidth", GET_INPUT_TIMING_VSYNCWIDTH());

        // Mode No. match
        ucModeNo = UserCommonModeSearchModeVGA();

        DebugMessageAnalog("9. ucModeNo = ", ucModeNo);

#if(_VGA_FORCE_DISPLAY == _ON)

        if(ucModeNo == _VGA_MODE_NOSUPPORT)
        {
            ucModeNo = UserInterfaceModeSearchModeVGA();
        }
#endif
        if(ucModeNo == _VGA_MODE_NOSUPPORT)
        {
            SET_INPUT_TIMING_HWIDTH(0);
            SET_INPUT_TIMING_VHEIGHT(0);
        }
        else
        {
            // Confirm Clamp Position Setting.
            ScalerSyncProcClampPosCheck(UserCommonModeSearchGetModeVideoType(ucModeNo));

            // Color format setting.
            ScalerADCClampMode(ScalerColorGetColorSpace());

            if(ScalerSyncProcAdcClkSetting() == _FALSE)
            {
                return _SOURCE_NONE;
            }

            // Set VGATOP capture
            ScalerVgaTopSetCapture();

#if(_UNDERSCAN_SUPPORT == _ON)
            SysVgaAdjustUnderScan();
#endif

            // SOG0 DC Restore Disable
            ScalerADCDCRestoreEn(_OFF);

            // SOG Clamp Enable
            ScalerADCSOGClampEn(_ON);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
            // Initial porch voltage check
            ScalerSyncProcSetPorchVoltage();
#endif

            // Double-check for VS synchronize edge
            ScalerVgaTopModifyVsLatchEdge(_WAIT);

            // Clear Sync Changed Status flag bit.
            ScalerSyncProcClearSyncChangeStatus();

#if(_YPBPR_SUPPORT == _ON)
            if(ScalerColorGetColorSpace() == _COLOR_SPACE_YPBPR)
            {
                ScalerColorSetColorimetry(UserCommonInterfaceCheckHDTVMode(ucModeNo));
            }
#endif // End of #if (_YPBPR_SUPPORT == _ON)

            // Re-start off-line measure after APLL clock adjust
            ScalerMeasureSetOfflineMeasure(_SOURCE_VGA, _A0_INPUT_PORT);
        }

        // Set Timing Confirm Flag.
        SET_MODE_TIMING_CONFIRM();
        SET_INPUT_TIMING_DOUBLE_CHECK();

        return _SOURCE_VGA;
    }

    // Check sync is invalid
    return _SOURCE_NONE;
}

#if(_UNDERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Underscan
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysVgaAdjustUnderScan(void)
{
    WORD usUnderScanVHeight = 0;

    if(UserInterfaceAdjustUnderScan() == _FALSE)
    {
        return;
    }

    if(GET_INPUT_TIMING_VHEIGHT() < GET_UNDERSCAN_VHEIGHT())
    {
        // Adjust VgaTop Vstart for underscan; Default center-positioned
        usUnderScanVHeight = (GET_UNDERSCAN_VHEIGHT() - GET_INPUT_TIMING_VHEIGHT()) / 2;

        if(GET_INPUT_TIMING_VSTART() < (usUnderScanVHeight + ScalerIDomainVgipGetVCaptureStartMinValue()))
        {
            SET_INPUT_TIMING_VSTART(usUnderScanVHeight + ScalerIDomainVgipGetVCaptureStartMinValue());
        }

        if((GET_INPUT_TIMING_VSTART() + GET_INPUT_TIMING_VHEIGHT() + 3) > GET_INPUT_TIMING_VTOTAL())
        {
            SET_INPUT_TIMING_VSTART(GET_INPUT_TIMING_VTOTAL() - GET_INPUT_TIMING_VHEIGHT() - 3);
        }

        ScalerVgaTopSetCaptureVStartPosition(GET_INPUT_TIMING_VSTART() - 2);

#if(_ADCNR_SUPPORT == _ON)
        // Disable ADCNR when underscan
        ScalerADCNREn(_DISABLE);
#endif
    }
}
#endif
#endif // End of #if(_VGA_SUPPORT == _ON)
