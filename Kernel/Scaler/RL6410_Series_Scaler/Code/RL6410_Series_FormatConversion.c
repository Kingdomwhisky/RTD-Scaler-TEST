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
// ID Code      : RL6410_Series_FormatConversion.c No.0000
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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort);

#if(_HDMI_2_0_SUPPORT == _ON)
void ScalerFmtCnv420To422FinalSetting(void);
void ScalerFmtCnv420To422D2Setting(WORD usHStart, WORD usHWidth);
void ScalerFmtCnv420To422D3Setting(WORD usHStart, WORD usHWidth);
#endif

void ScalerFmtCnvFinalSetting(void);
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(void);

void ScalerFmtCnvFtoPControl(bit bEnable);
bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(void);

#if(_DIGITAL_PORT_SUPPORT == _ON)
void ScalerFmtCnvSetBackgroundColor(void);
#endif

void ScalerFmtCnvFtoPSetFifo(WORD usHwidth, WORD usVstart);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize for format conversion
// Input Value  : enumSourceSearchPort --> input port
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _A0_INPUT_PORT:

            // Set source index to A0
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_ADC << 4));
            break;

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            // Set source index to D0
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D0 << 4));
            break;

        case _D1_INPUT_PORT:

            // Set source index to D1
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D1 << 4));
            break;

        case _D2_INPUT_PORT:

            // Set source index to D2
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D2 << 4));

#if(_D2_HDMI_2_0_SUPPORT == _ON)
            // Disble 420-to-422
            ScalerColor420To422D2Enable(_FUNCTION_OFF);
#endif
            break;

        case _D3_INPUT_PORT:

            // Set source index to D3
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D3 << 4));

#if(_D3_HDMI_2_0_SUPPORT == _ON)
            // Disble 420-to-422
            ScalerColor420To422D3Enable(_FUNCTION_OFF);
#endif
            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(ScalerDualLinkDVIRx4GetDualDVIMode() == _TRUE)
            {
                // Set source index to DUAL DVI
                ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_DUAL_DVI << 4));
            }
            else
#endif
            {
                // Set source index to D4
                ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D4 << 4));
            }
            break;

        case _D5_INPUT_PORT:

            // Set source index to D5
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D5 << 4));
            break;

        default:
            break;
    }

#if(_VGA_SUPPORT == _ON)
    // Disable VS edge align for VGA
    if(enumSourceSearchPort == _A0_INPUT_PORT)
    {
        ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
        {
            // Disable delay 2T for HS after CTS FIFO for M1/M2
            ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
    }
    else
#endif
    {
        ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
        {
            // Enable delay 2T for HS after CTS FIFO for M1/M2
            ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
    }

    // Duplicate M2 source from M1
    ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> 4));

    // Check input pixel rate
    if(ScalerSyncGetInputPixelClk() > _DATA_PATH_SPEED_LIMIT)
    {
        ScalerFmtCnvHalfSDSetFirstPixel(0);

        // Enable 1/2 scaling down
        ScalerFmtCnvHalfSDControl(_ENABLE);
    }
    else
    {
        // Disable 1/2 scaling down
        ScalerFmtCnvHalfSDControl(_DISABLE);
    }

    // Disable F-to-P
    ScalerFmtCnvFtoPControl(_DISABLE);

    // Enable clock gating for sub
    ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
}

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Final YCBCR 420 setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422FinalSetting(void)
{
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        if(ScalerFmtCnvGetSourceType() == _FC_SOURCE_D2)
        {
            // Update actual 420-422 state
            if(ScalerFmtCnvHalfSDGetStatus() == _TRUE)
            {
                ScalerFmtCnv420To422D2Setting(GET_ACTIVE_H_START() << 1, GET_ACTIVE_H_WIDTH() << 1);
            }
            else
            {
                ScalerFmtCnv420To422D2Setting(GET_ACTIVE_H_START(), GET_ACTIVE_H_WIDTH());
            }
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerColor420To422D2Enable(_FUNCTION_ON);
        }
        else if(ScalerFmtCnvGetSourceType() == _FC_SOURCE_D3)
        {
            // Update actual 420-422 state
            if(ScalerFmtCnvHalfSDGetStatus() == _TRUE)
            {
                ScalerFmtCnv420To422D3Setting(GET_ACTIVE_H_START() << 1, GET_ACTIVE_H_WIDTH() << 1);
            }
            else
            {
                ScalerFmtCnv420To422D3Setting(GET_ACTIVE_H_START(), GET_ACTIVE_H_WIDTH());
            }
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerColor420To422D3Enable(_FUNCTION_ON);
        }
    }
}

//--------------------------------------------------
// Description  : 420To422 parameter setting for D2 source
// Input Value  : usHStart, usHWidth
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D2Setting(WORD usHStart, WORD usHWidth)
{
    if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
    {
        ScalerSetBit(P31_31_YUV420_TO_422_CTL_D2D3, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P31_31_YUV420_TO_422_CTL_D2D3, ~_BIT7, 0x00);
    }

    if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
    {
        // Hstart should be modify when FC delay 2T enable
        if(ScalerGetBit(P31_0F_VS_DELAY_CTRL, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            usHStart += 2;
        }
    }

    ScalerSetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, ~(_BIT5 | _BIT4 | _BIT3), (HIBYTE(usHStart) & 0x07) << 3);
    ScalerSetByte(P31_35_YUV420_TO_YUV422_HSTL0_D2D3, LOBYTE(usHStart));
    ScalerSetBit(P31_37_YUV420_TO_YUV422_HWIDM0_D2D3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (HIBYTE(usHWidth) & 0x0F) << 4);
    ScalerSetByte(P31_38_YUV420_TO_YUV422_HWIDL0_D2D3, LOBYTE(usHWidth));

#if(_HW_TMDS_YUV420_DUPLICATE_MODE_SUPPORT == _ON)
    if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
    {
        if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
        {
            ScalerSetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, ~_BIT7, _BIT7);
        }
        else
        {
            ScalerSetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, ~_BIT7, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : 420To422 parameter setting for D3 source
// Input Value  : usHStart, usHWidth
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D3Setting(WORD usHStart, WORD usHWidth)
{
    if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
    {
        ScalerSetBit(P31_31_YUV420_TO_422_CTL_D2D3, ~_BIT5, _BIT5);
    }
    else
    {
        ScalerSetBit(P31_31_YUV420_TO_422_CTL_D2D3, ~_BIT5, 0x00);
    }

    if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
    {
        // Hstart should be modify when FC delay 2T enable
        if(ScalerGetBit(P31_0F_VS_DELAY_CTRL, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            usHStart += 2;
        }
    }

    ScalerSetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, ~(_BIT2 | _BIT1 | _BIT0), (HIBYTE(usHStart) & 0x07));
    ScalerSetByte(P31_36_YUV420_TO_YUV422_HSTL1_D2D3, LOBYTE(usHStart));
    ScalerSetBit(P31_37_YUV420_TO_YUV422_HWIDM0_D2D3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHWidth) & 0x0F));
    ScalerSetByte(P31_39_YUV420_TO_YUV422_HWIDL1_D2D3, LOBYTE(usHWidth));

#if(_HW_TMDS_YUV420_DUPLICATE_MODE_SUPPORT == _ON)
    if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
    {
        if(GET_COLOR_DEPTH() > _COLOR_DEPTH_8_BITS)
        {
            ScalerSetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, ~_BIT6, _BIT6);
        }
        else
        {
            ScalerSetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, ~_BIT6, 0x00);
        }
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Final format conversion setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFinalSetting(void)
{
#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType() == _FC_SOURCE_ADC)
    {
        // Enable VS edge align
        ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
#endif

#if(_HDMI_2_0_SUPPORT == _ON)
    if(GET_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)
    {
        // Set main F-to-P FIFO
        ScalerFmtCnvFtoPSetFifo((GET_INPUT_TIMING_HWIDTH() << 1), GET_INPUT_TIMING_VSTART());
    }
    else
#endif
    {
        // Set main F-to-P FIFO
        ScalerFmtCnvFtoPSetFifo(GET_INPUT_TIMING_HWIDTH(), GET_INPUT_TIMING_VSTART());
    }

    if(ScalerFmtCnvHalfSDGetStatus() == _TRUE)
    {
        // Disable 1/2 scaling down
        ScalerFmtCnvHalfSDControl(_DISABLE);
    }

    // Enable main F-to-P
    ScalerFmtCnvFtoPControl(_ENABLE);

#if(_AIO_MODERN_STANDBY_SUPPORT == _ON)
    if(GET_AIO_MODERN_STANDBY_MODE() != _TRUE)
#endif
    {
        if(ScalerFmtCnvGetSourceType() != _FC_SOURCE_ADC)
        {
            // Wait 4 IVS after format conversion setting
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);
            ScalerTimerWaitForEvent(_EVENT_IVS);

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        }
    }

    // Enable clock gating for M2
    ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT1, 0x00);
}

//--------------------------------------------------
// Description  : Show format conversion input source
// Input Value  : NONE
// Output Value : Current format conversino source
//--------------------------------------------------
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(void)
{
    return (EnumFormatConversionSourceType)(ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
}

//--------------------------------------------------
// Description  : Control for even/odd
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPControl(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if(_VGA_SUPPORT == _ON)
        if(ScalerFmtCnvGetSourceType() != _FC_SOURCE_ADC)
#endif
        {
#if(_HDMI_FREESYNC_ENLARGE_FRONT_PORCH == _ON)
            if(GET_HDMI_FREESYNC_ENABLED() == _TRUE)
            {
                // Enable VS delay 4 line to enlarge front porch, 2 is margin
                if(GET_ACTIVE_V_START() >= (2 + 2 * (_HDMI_FREESYNC_ENLARGE_FRONT_PORCH_LINE + 1)))
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT1, _BIT1);

                    // Vsync delay 4 line
                    ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT5 | _BIT4), (_HDMI_FREESYNC_ENLARGE_FRONT_PORCH_LINE << 4));
                }
            }
            else
#endif
            {
                // Enable VS delay 8 line to enlarge front porch
                if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT1, _BIT1);

                    // Vsync delay 8 line
                    ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
                }
            }
        }

        // Enable F-to-P
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, _BIT7);

        if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
        {
            // Set interlace for E/O mode
            ScalerFmtCnvFtoPInterlaceSetting();
        }
    }
    else
    {
        // Disable VS delay 8 line
        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT7 | _BIT6 | _BIT3 | _BIT1), 0x00);

        // Vsync delay 8 line
        ScalerSetBit(P31_0F_VS_DELAY_CTRL, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

        // Set E/O H width to 0
        ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, 0x00);

        // Disable F-to-P
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set format conversion Single Mode & D-domain E/O Mode
// Input Value  : NA
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(void)
{
#if(_FORMAT_CONVERSION_FORCE_EO_MODE == _ON)

    // Force E/O mode
    return _FALSE;

#else

#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType() != _FC_SOURCE_ADC)
#endif
    {
        // Check if H-Width is ODD integer, Select Single Path
        if((GET_INPUT_TIMING_HWIDTH() % 2) != 0x00)
        {
            return _TRUE;
        }

        if((ScalerSyncGetInputPixelClk() <= _DATA_PATH_SPEED_LIMIT) &&
           ((LOBYTE(GET_INPUT_TIMING_VHEIGHT()) % 2) != 0x00))
        {
            g_stActiveRegion.usVActiveEnd += 1;
            return _TRUE;
        }
    }

    return _FALSE;

#endif // End of #if(_FORMAT_CONVERSION_FORCE_EO_MODE == _ON)
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set background color for format conversion
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetBackgroundColor(void)
{
    // M1 M2 porch color enable
    ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    if(GET_COLOR_SPACE_RGB(GET_COLOR_SPACE()) == _TRUE)
    {
        ScalerSetByte(P31_51_PORCH_COLOR_R_M1, 0x00);
        ScalerSetByte(P31_52_PORCH_COLOR_G_M1, 0x00);
        ScalerSetByte(P31_53_PORCH_COLOR_B_M1, 0x00);

        ScalerSetByte(P31_54_PORCH_COLOR_R_M2, 0x00);
        ScalerSetByte(P31_55_PORCH_COLOR_G_M2, 0x00);
        ScalerSetByte(P31_56_PORCH_COLOR_B_M2, 0x00);
    }
    else
    {
        ScalerSetByte(P31_51_PORCH_COLOR_R_M1, 0x80);
        ScalerSetByte(P31_52_PORCH_COLOR_G_M1, 0x00);
        ScalerSetByte(P31_53_PORCH_COLOR_B_M1, 0x80);

        ScalerSetByte(P31_54_PORCH_COLOR_R_M2, 0x80);
        ScalerSetByte(P31_55_PORCH_COLOR_G_M2, 0x00);
        ScalerSetByte(P31_56_PORCH_COLOR_B_M2, 0x80);
    }
}
#endif

//--------------------------------------------------
// Description  : Set even/odd resolution
// Input Value  : usHwidth, usVstart  --> resolution for even/odd
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPSetFifo(WORD usHwidth, WORD usVstart)
{
    if((LOBYTE(usVstart) & _BIT0) == _BIT0)
    {
        // Set vertical start field = even
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Set vertical start field = odd
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT4, 0x00);
    }

    // Toggle vertical start field for VS bypass
    if(ScalerGetBit(P0_11_M1_VGIP_SIGINV, _BIT6) == _BIT6)
    {
        ScalerSetByte(P31_06_FC_EO_LINE_CTRL, (ScalerGetByte(P31_06_FC_EO_LINE_CTRL) ^ _BIT4));
    }

#if(_HW_TMDS_YUV420_DUPLICATE_MODE_SUPPORT == _ON)
    if(ScalerGlobalGetIDCode() >= _RL6410_VER_E_ID_CODE)
    {
        // Toggle vertical start field for 420 duplicate mode
        if(((ScalerFmtCnvGetSourceType() == _FC_SOURCE_D2) &&
            (ScalerGetBit(P31_32_YUV420_TO_YUV422_D2, _BIT7) == _BIT7) &&
            (ScalerGetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, _BIT7) == _BIT7)) ||
           ((ScalerFmtCnvGetSourceType() == _FC_SOURCE_D3) &&
            (ScalerGetBit(P31_33_YUV420_TO_YUV422_D3, _BIT7) == _BIT7) &&
            (ScalerGetBit(P31_34_YUV420_TO_YUV422_HSTM0_D2D3, _BIT6) == _BIT6)))
        {
            ScalerSetByte(P31_06_FC_EO_LINE_CTRL, (ScalerGetByte(P31_06_FC_EO_LINE_CTRL) ^ _BIT4));
        }
    }
#endif

    // Set horizontal width
    ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x1F));
    ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, LOBYTE(usHwidth));
}


