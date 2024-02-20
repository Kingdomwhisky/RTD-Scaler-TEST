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
// ID Code      : ScalerDualLinkDVI.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DUALLINKDVI__

#include "ScalerFunctionInclude.h"

#if(_DUAL_DVI_SUPPORT == _ON)
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
bit ScalerDualLinkDVIGetDualDVIMode(EnumSourceSearchPort enumInputPort);
bit ScalerDualLinkDVIDoubleCheck(EnumSourceSearchPort enumSourceSearchPort, WORD usHwidth, WORD usVHeight);
void ScalerDualLinkDVIClockInvert(void);
void ScalerDualLinkDVIScanInitial(BYTE ucInputPort);
bit ScalerDualLinkDVIPSPreDetect(BYTE ucInputPort);
bit ScalerDualLinkDVINormalPreDetect(BYTE ucInputPort);
BYTE ScalerDualLinkDVIScanInputPort(BYTE ucInputPort);

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
void ScalerDualLinkDVIRx2ScanInitial(void);
bit ScalerDualLinkDVIRx2PSPreDetect(void);
bit ScalerDualLinkDVIRx2NormalPreDetect(void);
BYTE ScalerDualLinkDVIRx2ScanInputPort(void);
void ScalerDualLinkDVIRx2Switch(bit bEnable);
bit ScalerDualLinkDVIRx2Check(void);
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
void ScalerDualLinkDVIRx3ScanInitial(void);
bit ScalerDualLinkDVIRx3PSPreDetect(void);
bit ScalerDualLinkDVIRx3NormalPreDetect(void);
BYTE ScalerDualLinkDVIRx3ScanInputPort(void);
void ScalerDualLinkDVIRx3Switch(bit bEnable);
bit ScalerDualLinkDVIRx3Check(void);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
void ScalerDualLinkDVIRx4ScanInitial(void);
bit ScalerDualLinkDVIRx4PSPreDetect(void);
bit ScalerDualLinkDVIRx4NormalPreDetect(void);
BYTE ScalerDualLinkDVIRx4ScanInputPort(void);
void ScalerDualLinkDVIRx4Switch(bit bEnable);
bit ScalerDualLinkDVIRx4Check(void);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get whether this port is dual DVI Port
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
bit ScalerDualLinkDVIGetDualDVIMode(EnumSourceSearchPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        case _D2_INPUT_PORT:
            return ScalerDualLinkDVIRx2GetDualDVIMode();
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
        case _D3_INPUT_PORT:
            return ScalerDualLinkDVIRx3GetDualDVIMode();
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        case _D4_INPUT_PORT:
            return ScalerDualLinkDVIRx4GetDualDVIMode();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether Current Timing is Reasonable
// Input Value  : Hwidth and VHeight
// Output Value : TRUE => OK
//--------------------------------------------------
bit ScalerDualLinkDVIDoubleCheck(EnumSourceSearchPort enumSourceSearchPort, WORD usHwidth, WORD usVHeight)
{
    if(usHwidth > usVHeight)
    {
        // For Normal Aspect Ratio
        if((usHwidth >> 1) < usVHeight)
        {
            return _TRUE;
        }
        else
        {
            PDATA_WORD(0) = ((DWORD)usHwidth * 100 / usVHeight);

            // For 21:9 Aspect
            if((PDATA_WORD(0) > 230) && (PDATA_WORD(0) < 240))
            {
                return _TRUE;
            }

            // Ignore Interlace Timing
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if((enumSourceSearchPort == _D3_INPUT_PORT) && (ScalerDualLinkDVIRx2GetDualDVIMode() == _FALSE) &&
               ((usVHeight == 240) || (usVHeight == 288) || (usVHeight == 384) || (usVHeight == 517) || (usVHeight == 518) || (usVHeight == 540)))
            {
                return _TRUE;
            }
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            if((enumSourceSearchPort == _D4_INPUT_PORT) && (ScalerDualLinkDVIRx3GetDualDVIMode() == _FALSE) &&
               ((usVHeight == 240) || (usVHeight == 288) || (usVHeight == 384) || (usVHeight == 517) || (usVHeight == 518) || (usVHeight == 540)))
            {
                return _TRUE;
            }
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if((enumSourceSearchPort == _D5_INPUT_PORT) && (ScalerDualLinkDVIRx4GetDualDVIMode() == _FALSE) &&
               ((usVHeight == 240) || (usVHeight == 288) || (usVHeight == 384) || (usVHeight == 517) || (usVHeight == 518) || (usVHeight == 540)))
            {
                return _TRUE;
            }
#endif
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Invert duali phy-to-MAC 1x clock
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIClockInvert(void)
{
    switch(ScalerGetBit(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
    {
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        case (_BIT7):                 // D2 dual DVI
            ScalerSetBit(P71_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P71_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            ScalerSetBit(P72_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P72_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
        case (_BIT7 | _BIT5):         // D3 dual DVI
            ScalerSetBit(P72_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P72_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            ScalerSetBit(P73_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P73_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        case (_BIT7 | _BIT6):         // D4 dual DVI
            ScalerSetBit(P73_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P73_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            ScalerSetBit(P74_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P74_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            break;
#endif

        default:
            return;
    }
}

//--------------------------------------------------
// Description  : Dual DVI Scan Initial
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIScanInitial(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            ScalerDualLinkDVIRx2ScanInitial();
#endif

            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            ScalerDualLinkDVIRx3ScanInitial();
#endif

            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            ScalerDualLinkDVIRx4ScanInitial();
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dual DVI PS Predetect
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDualLinkDVIPSPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx2PSPreDetect();
#endif

            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx3PSPreDetect();
#endif

            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx4PSPreDetect();
#endif

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dual DVI Normal Predetect
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
bit ScalerDualLinkDVINormalPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx2NormalPreDetect();
#endif

            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx3NormalPreDetect();
#endif

            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx4NormalPreDetect();
#endif

            break;

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dual DVI ScaninputPort
// Input Value  : ucInputPort, ucInputType
// Output Value : None
//--------------------------------------------------
BYTE ScalerDualLinkDVIScanInputPort(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx2ScanInputPort();
#endif

            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx3ScanInputPort();
#endif

            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            return ScalerDualLinkDVIRx4ScanInputPort();
#endif

            break;

        default:

            break;
    }

    return _SOURCE_NONE;
}

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Initial Setting for Dual DVI Scanning Port(Power Normal)
// Input Value  : Input Port(D2, Dual DVI)
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIRx2ScanInitial(void)
{
    // Both Initial D2 Port & D3 Port TMDS
    ScalerTMDSRx2Initial();
    ScalerTMDSRx3Initial();

    // Both Initial D2 Port & D3 Port Interrupt Initial
    ScalerTMDSRx2InterruptInitial();
    ScalerTMDSRx3InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for Dual DVI(Power Saving)
// Input Value  : Input Port(D2, Dual DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDualLinkDVIRx2PSPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX2_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx2("7. PowerSaving D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
    {
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear D2 Port Freq. Stable Flag
    ScalerSetBit(P71_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear D2 Port Unstable Flag
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 10 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P71_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P71_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for Dual DVI(Power Normal)
// Input Value  : Input Port(D2, Dual DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDualLinkDVIRx2NormalPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX2_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx2("7. Normal D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
    {
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
    }

    ScalerTimerDelayXms(6);

    if((GET_TMDS_RX2_PHY_SET() == _TRUE) && (GET_TMDS_RX3_PHY_SET() == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port(D2, Dual DVI)
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source DUAL_DVI --- > DUAL DVI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDualLinkDVIRx2ScanInputPort(void)
{
    bit bDualDviMode = _FALSE;

    if((GET_TMDS_RX2_PHY_SET() == _TRUE) && (GET_TMDS_RX3_PHY_SET() == _TRUE))
    {
        BYTE ucTMDSType = _SOURCE_NONE;

        BYTE ucTMDSRx2VideoDataType = _TMDS_VIDEO_DATA_NONE;
        BYTE ucTMDSRx3VideoDataType = _TMDS_VIDEO_DATA_NONE;

#if(_D3_HDMI_SUPPORT == _ON)
        WORD usInputPixelClk = 0;
#endif

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

        ucTMDSRx2VideoDataType = ScalerTMDSRx2TMDSVideoDetect(_WAIT);

        if((ucTMDSRx2VideoDataType != _TMDS_VIDEO_DATA_NONE) && (ScalerDualLinkDVIRx2Check() == _TRUE))
        {
            if((ScalerTMDSRx2CheckCDRStable(g_usTMDSRx2ClkCount) == _FALSE) || (ScalerTMDSRx2CheckDataDFE() == _FALSE) ||
               (ScalerTMDSRx3CheckCDRStable(g_usTMDSRx3ClkCount) == _FALSE) || (ScalerTMDSRx3CheckDataDFE() == _FALSE))
            {
                //-------- Set Port2 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P71_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P71_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P71_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P71_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P71_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P71_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P71_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port2 Stable Bound End ----//

                //-------- Set Port3 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P72_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P72_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P72_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port3 Stable Bound End ----//

                CLR_TMDS_RX2_PHY_SET();
                CLR_TMDS_RX3_PHY_SET();

                // Disable port2 Freq. Unstable IRQ
                ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port2 Freq. Stable IRQ
                ScalerSetBit(P71_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Disable Port3 Freq. Unstable IRQ
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port3 Freq. Stable IRQ
                ScalerSetBit(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _TRUE;
        }
        else
        {
            if((ScalerTMDSRx3CheckCDRStable(g_usTMDSRx3ClkCount) == _FALSE) || (ScalerTMDSRx3CheckDataDFE() == _FALSE))
            {
                //-------- Set Port3 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P72_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P72_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P72_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port3 Stable Bound End ----//

                CLR_TMDS_RX3_PHY_SET();

                // Disable Port3 Freq. Unstable IRQ
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port3 Freq. Stable IRQ
                ScalerSetBit(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _FALSE;
        }

        DebugMessageRx2("9. Freq Check Pass => Pixel Clock", GET_INPUT_PIXEL_CLK());

        // Clear Port2 RGBHV Flag
        ScalerSetBit(P71_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear port2 Info Packet SRAM
        ScalerSetBit(P71_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P71_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port2 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P71_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P71_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        // Clear Port3 RGBHV Flag
        ScalerSetBit(P72_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Port3 Info Packet SRAM
        ScalerSetBit(P72_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P72_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port3 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P72_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P72_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        if(ScalerTMDSRx3FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx2("Format Detect HDMI", 0x00);

            ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT1, _BIT1);

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
            return _SOURCE_NONE;
#else

            ucTMDSRx3VideoDataType = ScalerTMDSRx3TMDSVideoDetect(_WAIT);

            if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx2("DE Only Mode", 0x00);

                return _SOURCE_NONE;
            }
            else if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }

            ucTMDSType = _SOURCE_HDMI;
#endif // End of #if(_HDMI_FROM_DVI_CONNECT == _OFF)
        }
        else
        {
            ScalerSetDataPortBit(P71_C3_HDCP_AP, _P71_C4_PT_40_PORT_PAGE71_BCAPS, ~_BIT1, 0x00);
            ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT1, 0x00);

            ScalerSetBit(P71_AF_TMDS_WDC, ~_BIT0, _BIT0);

            if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
#if(_D2_HDMI_2_0_SUPPORT == _ON)
                if(ScalerGetBit(P71_00_HDMI_CTRL_00, _BIT0) == _BIT0)
                {
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_HDMI2_FORMAT_RESET_WAIT);
                }
#endif
                // Set Format Detect HW Auto Mode
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
            }
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            else
            {
                // Manual Set to DVI Mode
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
            }
#endif

            ucTMDSRx2VideoDataType = ScalerTMDSRx2TMDSVideoDetect(_NOT_WAIT);
            ucTMDSRx3VideoDataType = ScalerTMDSRx3TMDSVideoDetect(_NOT_WAIT);

            DebugMessageRx2("D2 Video Detect", ucTMDSRx2VideoDataType);
            DebugMessageRx2("D3 Video Detect", ucTMDSRx3VideoDataType);

            if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx2("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
                // Enable D2 DE Only Mode
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P71_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
#else
                return _SOURCE_NONE;
#endif
            }
            else if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P71_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
            }
            else
            {
                return _SOURCE_NONE;
            }
        }

        DebugMessageRx2("Source Type", ucTMDSType);

        // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
        // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
        if(bDualDviMode == _TRUE)
        {
            ScalerSetBit(P7B_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7B_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7B_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }

        ScalerSetBit(P7C_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7C_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7C_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_D3_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSRx3HdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx3HdmiVideoSetting();

            SET_COLOR_DEPTH(ScalerTMDSRx3HdmiGetColorDepth());

            if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS))
            {
                DebugMessageRx2("Deep Color Mode Detected", GET_COLOR_DEPTH());

                // Backup Input Pixel clk
                usInputPixelClk = GET_INPUT_PIXEL_CLK();

                SET_INPUT_PIXEL_CLK((GET_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH());

                if(ScalerTMDSRx3HdmiDeepColorProc(g_usTMDSRx3ClkCount) == _FALSE)
                {
                    // Restore Input Pixel clk
                    SET_INPUT_PIXEL_CLK(usInputPixelClk);

                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);
            }
        }
        else
        {
            CLR_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
            CLR_HDMI_RX3_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_RX2_GCP_RECEIVED();
            CLR_HDMI_RX3_GCP_RECEIVED();

            // Disable D2 Port All WD when DVI
            ScalerTMDSRx2HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // Disable D3 Port All WD when DVI
            ScalerTMDSRx3HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // D2 Port DVI Setting
            ScalerTMDSRx2DviVideoSetting();

            // D3 Port DVI Setting
            ScalerTMDSRx3DviVideoSetting();

            SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

            // Turn off D2 Port Deep Color Block
            ScalerSetBit(P71_B5_TMDS_UDC0, ~_BIT7, 0x00);

            // Turn off D3 Port Deep Color Block
            ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSRx3DviVideoSetting();

        SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        if(bDualDviMode == _TRUE)
        {
            ScalerDualLinkDVIRx2Switch(_ENABLE);
        }
        else
        {
            ScalerDualLinkDVIRx2Switch(_DISABLE);
        }

        return ucTMDSType;
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Switch Dual DVI
// Input Value  : _Enable/ Disable
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIRx2Switch(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Disable D2 Port All WD when DVI
        ScalerTMDSRx2DviVideoSetting();

        // Turn off D2 Port Deep Color Block
        ScalerSetBit(P71_B5_TMDS_UDC0, ~_BIT7, 0x00);

        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, _BIT2);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, 0x00);

        // Enable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

        // Enable Dual DVI Output from D2 + D3 Port
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

        // Enable Video Output
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_80_PORT_PAGE71_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P71_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Enable Video Output
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_80_PORT_PAGE72_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P72_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
    else
    {
        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, _BIT2);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, 0x00);

        // Disable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT7 | _BIT5), 0x00);

        // Disable Dual DVI Output from D2 + D3 Port
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT7, 0x00);

        // Enable Video Output
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_80_PORT_PAGE72_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P72_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : TMDS Check Dual DVI Format
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDualLinkDVIRx2Check(void)
{
    SBYTE pchTMDSRx2Vth[3];
    SBYTE pchTMDSRx3Vth[3];
    SBYTE pchTMDSRx2Tap0[3];
    SBYTE pchTMDSRx3Tap0[3];

    // Disable Rx2 DFE Vth Adapt
    ScalerSetBit(P7B_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7B_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7B_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    // Disable Rx3 DFE Vth Adapt
    ScalerSetBit(P7C_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7C_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7C_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    // Read Out Rx2 DFE VTH Value
    ScalerSetBit(P7B_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx2Vth[0] = (ScalerGetByte(P7B_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx2Vth[1] = (ScalerGetByte(P7B_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx2Vth[2] = (ScalerGetByte(P7B_F1_COEF_2) & 0x0F);

    // Read Out Rx3 DFE VTH Value
    ScalerSetBit(P7C_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx3Vth[0] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx3Vth[1] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx3Vth[2] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Read Out Rx2 DFE Tap0 Value
    ScalerSetBit(P7B_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx2Tap0[0] = ScalerGetByte(P7B_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx2Tap0[1] = ScalerGetByte(P7B_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx2Tap0[2] = ScalerGetByte(P7B_F1_COEF_2);

    // Read Out Rx3 DFE Tap0 Value
    ScalerSetBit(P7C_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx3Tap0[0] = ScalerGetByte(P7C_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx3Tap0[1] = ScalerGetByte(P7C_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx3Tap0[2] = ScalerGetByte(P7C_F1_COEF_2);

    // Check 2 Dual Port Vth Adapt Value
    if((abs(pchTMDSRx3Vth[0] - pchTMDSRx2Vth[0]) < 4) &&
       (abs(pchTMDSRx3Vth[1] - pchTMDSRx2Vth[1]) < 4) &&
       (abs(pchTMDSRx3Vth[2] - pchTMDSRx2Vth[2]) < 4))
    {
        // Double Check Tap0
        if((abs(pchTMDSRx2Tap0[0] - pchTMDSRx3Tap0[0]) < 10) &&
           (abs(pchTMDSRx2Tap0[1] - pchTMDSRx3Tap0[1]) < 10) &&
           (abs(pchTMDSRx2Tap0[2] - pchTMDSRx3Tap0[2]) < 10))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Initial Setting for Dual DVI Scanning Port(Power Normal)
// Input Value  : Input Port(D3, Dual DVI)
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIRx3ScanInitial(void)
{
    // Both Initial D3 Port & D4 Port TMDS
    ScalerTMDSRx3Initial();
    ScalerTMDSRx4Initial();

    // Both Initial D3 Port & D4 Port Interrupt Initial
    ScalerTMDSRx3InterruptInitial();
    ScalerTMDSRx4InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for Dual DVI(Power Saving)
// Input Value  : Input Port(D3, Dual DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDualLinkDVIRx3PSPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX3_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx3("7. PowerSaving D0 DDC", 0);

        CLR_TMDS_RX3_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX3_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE72_DDC3_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX3_DDC_DETECTED() != _TRUE))
    {
        MCU_FE72_DDC3_EDID_IRQ |= _BIT2;
        MCU_FE72_DDC3_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear D3 Port Freq. Stable Flag
    ScalerSetBit(P72_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear D3 Port Unstable Flag
    ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 10 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P72_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P72_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX3_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for Dual DVI(Power Normal)
// Input Value  : Input Port(D3, Dual DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDualLinkDVIRx3NormalPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX3_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx3("7. Normal D0 DDC", 0);

        CLR_TMDS_RX3_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE72_DDC3_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX3_DDC_DETECTED() != _TRUE))
    {
        MCU_FE72_DDC3_EDID_IRQ |= _BIT2;
        MCU_FE72_DDC3_EDID_IRQ |= _BIT3;
    }

    ScalerTimerDelayXms(6);

    if((GET_TMDS_RX3_PHY_SET() == _TRUE) && (GET_TMDS_RX4_PHY_SET() == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port(D3, Dual DVI)
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source DUAL_DVI --- > DUAL DVI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDualLinkDVIRx3ScanInputPort(void)
{
    bit bDualDviMode = _FALSE;

    if((GET_TMDS_RX3_PHY_SET() == _TRUE) && (GET_TMDS_RX4_PHY_SET() == _TRUE))
    {
        BYTE ucTMDSType = _SOURCE_NONE;

        BYTE ucTMDSRx3VideoDataType = _TMDS_VIDEO_DATA_NONE;
        BYTE ucTMDSRx4VideoDataType = _TMDS_VIDEO_DATA_NONE;

#if(_D4_HDMI_SUPPORT == _ON)
        WORD usInputPixelClk = 0;
#endif

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

        ucTMDSRx3VideoDataType = ScalerTMDSRx3TMDSVideoDetect(_WAIT);

        if((ucTMDSRx3VideoDataType != _TMDS_VIDEO_DATA_NONE) && (ScalerDualLinkDVIRx3Check() == _TRUE))
        {
            if((ScalerTMDSRx3CheckCDRStable(g_usTMDSRx3ClkCount) == _FALSE) || (ScalerTMDSRx3CheckDataDFE() == _FALSE) ||
               (ScalerTMDSRx4CheckCDRStable(g_usTMDSRx4ClkCount) == _FALSE) || (ScalerTMDSRx4CheckDataDFE() == _FALSE))
            {
                //-------- Set Port3 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P72_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P72_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P72_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port3 Stable Bound End ----//

                //-------- Set Port4 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port4 Stable Bound End ----//

                CLR_TMDS_RX3_PHY_SET();
                CLR_TMDS_RX4_PHY_SET();

                // Disable port3 Freq. Unstable IRQ
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port3 Freq. Stable IRQ
                ScalerSetBit(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Disable Port4 Freq. Unstable IRQ
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port4 Freq. Stable IRQ
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _TRUE;
        }
        else
        {
            if((ScalerTMDSRx4CheckCDRStable(g_usTMDSRx4ClkCount) == _FALSE) || (ScalerTMDSRx4CheckDataDFE() == _FALSE))
            {
                //-------- Set Port4 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port4 Stable Bound End ----//

                CLR_TMDS_RX4_PHY_SET();

                // Disable Port4 Freq. Unstable IRQ
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port4 Freq. Stable IRQ
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _FALSE;
        }

        DebugMessageRx3("9. Freq Check Pass => Pixel Clock", GET_INPUT_PIXEL_CLK());

        // Clear Port3 RGBHV Flag
        ScalerSetBit(P72_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear port3 Info Packet SRAM
        ScalerSetBit(P72_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P72_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port3 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P72_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P72_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        // Clear Port4 RGBHV Flag
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Port4 Info Packet SRAM
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port4 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P73_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P73_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        if(ScalerTMDSRx4FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx3("Format Detect HDMI", 0x00);

            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, _BIT1);

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
            return _SOURCE_NONE;
#else

            ucTMDSRx4VideoDataType = ScalerTMDSRx4TMDSVideoDetect(_WAIT);

            if(ucTMDSRx4VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx3("DE Only Mode", 0x00);

                return _SOURCE_NONE;
            }
            else if(ucTMDSRx4VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }

            ucTMDSType = _SOURCE_HDMI;
#endif // End of #if(_HDMI_FROM_DVI_CONNECT == _OFF)
        }
        else
        {
            ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT1, 0x00);
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, 0x00);

            ScalerSetBit(P72_AF_TMDS_WDC, ~_BIT0, _BIT0);

            if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
#if(_D3_HDMI_2_0_SUPPORT == _ON)
                if(ScalerGetBit(P72_00_HDMI_CTRL_00, _BIT0) == _BIT0)
                {
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_HDMI2_FORMAT_RESET_WAIT);
                }
#endif
                // Set Format Detect HW Auto Mode
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
            }
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            else
            {
                // Manual Set to DVI Mode
                ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_00_PORT_PAGE72_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
            }
#endif

            ucTMDSRx3VideoDataType = ScalerTMDSRx3TMDSVideoDetect(_NOT_WAIT);
            ucTMDSRx4VideoDataType = ScalerTMDSRx4TMDSVideoDetect(_NOT_WAIT);

            DebugMessageRx3("D3 Video Detect", ucTMDSRx3VideoDataType);
            DebugMessageRx3("D4 Video Detect", ucTMDSRx4VideoDataType);

            if(ucTMDSRx4VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx3("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
                // Enable D3 DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
#else
                return _SOURCE_NONE;
#endif
            }
            else if(ucTMDSRx4VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
            }
            else
            {
                return _SOURCE_NONE;
            }
        }

        DebugMessageRx3("Source Type", ucTMDSType);

        // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
        // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
        if(bDualDviMode == _TRUE)
        {
            ScalerSetBit(P7C_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7C_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7C_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }

        ScalerSetBit(P7D_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7D_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7D_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_D4_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSRx4HdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx4HdmiVideoSetting();

            SET_COLOR_DEPTH(ScalerTMDSRx4HdmiGetColorDepth());

            if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS))
            {
                DebugMessageRx3("Deep Color Mode Detected", GET_COLOR_DEPTH());

                // Backup Input Pixel clk
                usInputPixelClk = GET_INPUT_PIXEL_CLK();

                SET_INPUT_PIXEL_CLK((GET_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH());

                if(ScalerTMDSRx4HdmiDeepColorProc(g_usTMDSRx4ClkCount) == _FALSE)
                {
                    // Restore Input Pixel clk
                    SET_INPUT_PIXEL_CLK(usInputPixelClk);

                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);
            }
        }
        else
        {
            CLR_HDMI_RX3_AVI_INFO_FRAME_RECEIVED();
            CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_RX3_GCP_RECEIVED();
            CLR_HDMI_RX4_GCP_RECEIVED();

            // Disable D3 Port All WD when DVI
            ScalerTMDSRx3HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // Disable D4 Port All WD when DVI
            ScalerTMDSRx4HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // D3 Port DVI Setting
            ScalerTMDSRx3DviVideoSetting();

            // D4 Port DVI Setting
            ScalerTMDSRx4DviVideoSetting();

            SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

            // Turn off D3 Port Deep Color Block
            ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);

            // Turn off D4 Port Deep Color Block
            ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSRx4DviVideoSetting();

        SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        if(bDualDviMode == _TRUE)
        {
            ScalerDualLinkDVIRx3Switch(_ENABLE);
        }
        else
        {
            ScalerDualLinkDVIRx3Switch(_DISABLE);
        }

        return ucTMDSType;
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Switch Dual DVI
// Input Value  : _Enable/ Disable
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIRx3Switch(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Disable D3 Port All WD when DVI
        ScalerTMDSRx3DviVideoSetting();

        // Turn off D3 Port Deep Color Block
        ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);

        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, _BIT1);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, 0x00);

        // Enable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

        // Enable Dual DVI Output from D3 + D4 Port
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), (_BIT7 | _BIT5 | _BIT3));

        // Enable Video Output
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_80_PORT_PAGE72_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P72_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Enable Video Output
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
    else
    {
        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, _BIT1);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, 0x00);

        // Disable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT6 | _BIT4), 0x00);

        // Disable Dual DVI Output from D3 + D4 Port
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT7, 0x00);

        // Enable Video Output
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : TMDS Double Check Dual DVI Format
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDualLinkDVIRx3Check(void)
{
    SBYTE pchTMDSRx3Vth[3];
    SBYTE pchTMDSRx4Vth[3];
    SBYTE pchTMDSRx3Tap0[3];
    SBYTE pchTMDSRx4Tap0[3];

    // Disable Rx3 DFE Vth Adapt
    ScalerSetBit(P7C_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7C_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7C_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    // Disable Rx4 DFE Vth Adapt
    ScalerSetBit(P7D_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7D_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7D_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    // Read Out Rx3 DFE VTH Value
    ScalerSetBit(P7C_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx3Vth[0] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx3Vth[1] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx3Vth[2] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Read Out Rx4 DFE VTH Value
    ScalerSetBit(P7D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx4Vth[0] = (ScalerGetByte(P7D_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx4Vth[1] = (ScalerGetByte(P7D_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx4Vth[2] = (ScalerGetByte(P7D_F1_COEF_2) & 0x0F);

    // Read Out Rx3 DFE Tap0 Value
    ScalerSetBit(P7C_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx3Tap0[0] = ScalerGetByte(P7C_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx3Tap0[1] = ScalerGetByte(P7C_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx3Tap0[2] = ScalerGetByte(P7C_F1_COEF_2);

    // Read Out Rx4 DFE Tap0 Value
    ScalerSetBit(P7D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx4Tap0[0] = ScalerGetByte(P7D_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx4Tap0[1] = ScalerGetByte(P7D_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx4Tap0[2] = ScalerGetByte(P7D_F1_COEF_2);

    // Check 2 Dual Port Vth Adapt Value
    if((abs(pchTMDSRx4Vth[0] - pchTMDSRx3Vth[0]) < 4) &&
       (abs(pchTMDSRx4Vth[1] - pchTMDSRx3Vth[1]) < 4) &&
       (abs(pchTMDSRx4Vth[2] - pchTMDSRx3Vth[2]) < 4))
    {
        // Double Check Tap0
        if((abs(pchTMDSRx3Tap0[0] - pchTMDSRx4Tap0[0]) < 10) &&
           (abs(pchTMDSRx3Tap0[1] - pchTMDSRx4Tap0[1]) < 10) &&
           (abs(pchTMDSRx3Tap0[2] - pchTMDSRx4Tap0[2]) < 10))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Initial Setting for Dual DVI Scanning Port(Power Normal)
// Input Value  : Input Port(D4, Dual DVI)
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIRx4ScanInitial(void)
{
    // Both Initial D4 Port & D5 Port TMDS
    ScalerTMDSRx4Initial();
    ScalerTMDSRx5Initial();

    // Both Initial D4 Port & D5 Port Interrupt Initial
    ScalerTMDSRx4InterruptInitial();
    ScalerTMDSRx5InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for Dual DVI(Power Saving)
// Input Value  : Input Port(D4, Dual DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDualLinkDVIRx4PSPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX4_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx4("7. PowerSaving D4 DDC", 0);

        CLR_TMDS_RX4_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX4_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE7B_DDC4_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX4_DDC_DETECTED() != _TRUE))
    {
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear D4 Port Freq. Stable Flag
    ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear D4 Port Unstable Flag
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 10 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P73_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P73_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX4_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for Dual DVI(Power Normal)
// Input Value  : Input Port(D4, Dual DVI)
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDualLinkDVIRx4NormalPreDetect(void)
{
    // DDC handshake Detected
    if(GET_TMDS_RX4_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx4("7. Normal D4 DDC", 0);

        CLR_TMDS_RX4_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE7B_DDC4_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX4_DDC_DETECTED() != _TRUE))
    {
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT3;
    }

    ScalerTimerDelayXms(6);

    if((GET_TMDS_RX4_PHY_SET() == _TRUE) && (GET_TMDS_RX5_PHY_SET() == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port(D4, Dual DVI)
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source DUAL_DVI --- > DUAL DVI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDualLinkDVIRx4ScanInputPort(void)
{
    bit bDualDviMode = _FALSE;

    if((GET_TMDS_RX4_PHY_SET() == _TRUE) && (GET_TMDS_RX5_PHY_SET() == _TRUE))
    {
        BYTE ucTMDSType = _SOURCE_NONE;

        BYTE ucTMDSRx4VideoDataType = _TMDS_VIDEO_DATA_NONE;
        BYTE ucTMDSRx5VideoDataType = _TMDS_VIDEO_DATA_NONE;

#if(_D5_HDMI_SUPPORT == _ON)
        WORD usInputPixelClk = 0;
#endif

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

        ucTMDSRx4VideoDataType = ScalerTMDSRx4TMDSVideoDetect(_WAIT);

        if((ucTMDSRx4VideoDataType != _TMDS_VIDEO_DATA_NONE) && (ScalerDualLinkDVIRx4Check() == _TRUE))
        {
            if((ScalerTMDSRx4CheckCDRStable(g_usTMDSRx4ClkCount) == _FALSE) || (ScalerTMDSRx4CheckDataDFE() == _FALSE) ||
               (ScalerTMDSRx5CheckCDRStable(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerTMDSRx5CheckDataDFE() == _FALSE))
            {
                //-------- Set Port4 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port4 Stable Bound End ----//

                //-------- Set Port5 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P74_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port5 Stable Bound End ----//

                CLR_TMDS_RX4_PHY_SET();
                CLR_TMDS_RX5_PHY_SET();

                // Disable port4 Freq. Unstable IRQ
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port4 Freq. Stable IRQ
                ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Disable Port5 Freq. Unstable IRQ
                ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port5 Freq. Stable IRQ
                ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _TRUE;
        }
        else
        {
            if((ScalerTMDSRx5CheckCDRStable(g_usTMDSRx5ClkCount) == _FALSE) || (ScalerTMDSRx5CheckDataDFE() == _FALSE))
            {
                //-------- Set Port5 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P74_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port5 Stable Bound End ----//

                CLR_TMDS_RX5_PHY_SET();

                // Disable Port5 Freq. Unstable IRQ
                ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter(Toggle)
                ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port5 Freq. Stable IRQ
                ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _FALSE;
        }

        DebugMessageRx4("9. Freq Check Pass => Pixel Clock", GET_INPUT_PIXEL_CLK());

        // Clear Port4 RGBHV Flag
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear port4 Info Packet SRAM
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port4 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P73_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P73_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        // Clear Port5 RGBHV Flag
        ScalerSetBit(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Port5 Info Packet SRAM
        ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port5 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P74_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P74_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        if(ScalerTMDSRx5FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx4("Format Detect HDMI", 0x00);

            ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, ~_BIT1, _BIT1);

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
            return _SOURCE_NONE;
#else

            ucTMDSRx5VideoDataType = ScalerTMDSRx5TMDSVideoDetect(_WAIT);

            if(ucTMDSRx5VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx4("DE Only Mode", 0x00);

                return _SOURCE_NONE;
            }
            else if(ucTMDSRx5VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }

            ucTMDSType = _SOURCE_HDMI;
#endif // End of #if(_HDMI_FROM_DVI_CONNECT == _OFF)
        }
        else
        {
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, 0x00);
            ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, ~_BIT1, 0x00);

            ScalerSetBit(P73_AF_TMDS_WDC, ~_BIT0, _BIT0);

            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
#if(_D4_HDMI_2_0_SUPPORT == _ON)
                if(ScalerGetBit(P73_00_HDMI_CTRL_00, _BIT0) == _BIT0)
                {
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT);
                }
#endif
                // Set Format Detect HW Auto Mode
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
            }
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            else
            {
                // Manual Set to DVI Mode
                ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
            }
#endif

            ucTMDSRx4VideoDataType = ScalerTMDSRx4TMDSVideoDetect(_NOT_WAIT);
            ucTMDSRx5VideoDataType = ScalerTMDSRx5TMDSVideoDetect(_NOT_WAIT);

            DebugMessageRx4("D4 Video Detect", ucTMDSRx4VideoDataType);
            DebugMessageRx4("D5 Video Detect", ucTMDSRx5VideoDataType);

            if(ucTMDSRx5VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx4("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
                // Enable D4 DE Only Mode
                ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
#else
                return _SOURCE_NONE;
#endif
            }
            else if(ucTMDSRx5VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
            }
            else
            {
                return _SOURCE_NONE;
            }
        }

        DebugMessageRx4("Source Type", ucTMDSType);

        // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
        // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
        if(bDualDviMode == _TRUE)
        {
            ScalerSetBit(P7D_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7D_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7D_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }

        ScalerSetBit(P7E_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7E_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7E_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_D5_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSRx5HdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx5HdmiVideoSetting();

            SET_COLOR_DEPTH(ScalerTMDSRx5HdmiGetColorDepth());

            if((GET_COLOR_SPACE() != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH() != _COLOR_DEPTH_8_BITS))
            {
                DebugMessageRx4("Deep Color Mode Detected", GET_COLOR_DEPTH());

                // Backup Input Pixel clk
                usInputPixelClk = GET_INPUT_PIXEL_CLK();

                SET_INPUT_PIXEL_CLK((GET_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH());

                if(ScalerTMDSRx5HdmiDeepColorProc(g_usTMDSRx5ClkCount) == _FALSE)
                {
                    // Restore Input Pixel clk
                    SET_INPUT_PIXEL_CLK(usInputPixelClk);

                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, 0x00);
            }
        }
        else
        {
            CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();
            CLR_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_RX4_GCP_RECEIVED();
            CLR_HDMI_RX5_GCP_RECEIVED();

            // Disable D4 Port All WD when DVI
            ScalerTMDSRx4HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // Disable D5 Port All WD when DVI
            ScalerTMDSRx5HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // D4 Port DVI Setting
            ScalerTMDSRx4DviVideoSetting();

            // D5 Port DVI Setting
            ScalerTMDSRx5DviVideoSetting();

            SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

            // Turn off D4 Port Deep Color Block
            ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);

            // Turn off D5 Port Deep Color Block
            ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSRx5DviVideoSetting();

        SET_COLOR_DEPTH(_COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P74_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        if(bDualDviMode == _TRUE)
        {
            ScalerDualLinkDVIRx4Switch(_ENABLE);
        }
        else
        {
            ScalerDualLinkDVIRx4Switch(_DISABLE);
        }

        return ucTMDSType;
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Switch Dual DVI
// Input Value  : _Enable/ Disable
// Output Value : None
//--------------------------------------------------
void ScalerDualLinkDVIRx4Switch(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Disable D4 Port All WD when DVI
        ScalerTMDSRx4DviVideoSetting();

        // Turn off D4 Port Deep Color Block
        ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);

        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, _BIT1);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, 0x00);

        // Enable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT6 | _BIT4), (_BIT6 | _BIT4));

        // Enable Dual DVI Output from D4 + D5 Port
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3), (_BIT7 | _BIT6 | _BIT3));

        // Enable Video Output
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Enable Video Output
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_30_PORT_PAGE74_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_80_PORT_PAGE74_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P74_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
    else
    {
        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, _BIT1);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT1, 0x00);

        // Disable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT6 | _BIT4), 0x00);

        // Disable Dual DVI Output from D4 + D5 Port
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~(_BIT7 | _BIT1), 0x00);

        // Enable Video Output
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_30_PORT_PAGE74_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_80_PORT_PAGE74_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P74_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : TMDS Check Dual DVI Format
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDualLinkDVIRx4Check(void)
{
    SBYTE pchTMDSRx4Vth[3];
    SBYTE pchTMDSRx5Vth[3];
    SBYTE pchTMDSRx4Tap0[3];
    SBYTE pchTMDSRx5Tap0[3];

    // Disable Rx4 DFE Vth Adapt
    ScalerSetBit(P7D_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7D_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7D_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    // Disable Rx5 DFE Vth Adapt
    ScalerSetBit(P7E_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7E_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7E_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    // Read Out Rx4 DFE VTH Value
    ScalerSetBit(P7D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx4Vth[0] = (ScalerGetByte(P7D_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx4Vth[1] = (ScalerGetByte(P7D_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx4Vth[2] = (ScalerGetByte(P7D_F1_COEF_2) & 0x0F);

    // Read Out Rx5 DFE VTH Value
    ScalerSetBit(P7E_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx5Vth[0] = (ScalerGetByte(P7E_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx5Vth[1] = (ScalerGetByte(P7E_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx5Vth[2] = (ScalerGetByte(P7E_F1_COEF_2) & 0x0F);

    // Read Out Rx4 DFE Tap0 Value
    ScalerSetBit(P7D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx4Tap0[0] = ScalerGetByte(P7D_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx4Tap0[1] = ScalerGetByte(P7D_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx4Tap0[2] = ScalerGetByte(P7D_F1_COEF_2);

    // Read Out Rx5 DFE Tap0 Value
    ScalerSetBit(P7E_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx5Tap0[0] = ScalerGetByte(P7E_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx5Tap0[1] = ScalerGetByte(P7E_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7E_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx5Tap0[2] = ScalerGetByte(P7E_F1_COEF_2);

    // Check 2 Dual Port Vth Adapt Value
    if((abs(pchTMDSRx5Vth[0] - pchTMDSRx4Vth[0]) < 4) &&
       (abs(pchTMDSRx5Vth[1] - pchTMDSRx4Vth[1]) < 4) &&
       (abs(pchTMDSRx5Vth[2] - pchTMDSRx4Vth[2]) < 4))
    {
        // Double Check Tap0
        if((abs(pchTMDSRx4Tap0[0] - pchTMDSRx5Tap0[0]) < 10) &&
           (abs(pchTMDSRx4Tap0[1] - pchTMDSRx5Tap0[1]) < 10) &&
           (abs(pchTMDSRx4Tap0[2] - pchTMDSRx5Tap0[2]) < 10))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}

#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

#endif // End of #if(_DUAL_DVI_SUPPORT == _ON)

